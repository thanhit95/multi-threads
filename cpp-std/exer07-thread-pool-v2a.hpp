/*
MY THREAD POOL

Version 2A:
- Better synchronization.
- Method "waitTaskDone":
  + uses a semaphore to synchronize.
  + does not consume CPU (compared to version 1).
*/



#ifndef _MY_THREAD_POOL_V2A_HPP_
#define _MY_THREAD_POOL_V2A_HPP_



#include <vector>
#include <list>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <semaphore>



// interface ITask
class ITask {
public:
    virtual ~ITask() = default;
    virtual void run() = 0;
};



class ThreadPoolV2A {

public:
    using TypeSemaphore = std::counting_semaphore<>;


private:
    int numThreads = 0;
    std::vector<std::thread> lstTh;

    std::queue<ITask*> taskPending;
    std::mutex mutTaskPending;
    std::condition_variable condTaskPending;

    std::list<ITask*> taskRunning;
    std::mutex mutTaskRunning;
    TypeSemaphore counterTaskRunning = TypeSemaphore(0);

    volatile bool forceThreadShutdown;


public:
    ThreadPoolV2A() = default;
    ThreadPoolV2A(const ThreadPoolV2A& other) = delete;
    ThreadPoolV2A(const ThreadPoolV2A&& other) = delete;
    void operator=(const ThreadPoolV2A& other) = delete;
    void operator=(const ThreadPoolV2A&& other) = delete;


    void init(int numThreads) {
        shutdown();

        this->numThreads = numThreads;
        lstTh.resize(numThreads);
        forceThreadShutdown = false;

        for (auto&& th : lstTh) {
            th = std::thread(threadRoutine, this);
        }
    }


    void submit(ITask* task) {
        mutTaskPending.lock();
        taskPending.push(task);
        mutTaskPending.unlock();

        condTaskPending.notify_one();
    }


    void waitTaskDone() {
        for (;;) {
            counterTaskRunning.acquire();

            {
                std::lock_guard<std::mutex> lkPending(mutTaskPending);
                std::lock_guard<std::mutex> lkRunning(mutTaskRunning);

                if (0 == taskPending.size() && 0 == taskRunning.size()) {
                    break;
                }
            }
        }
    }


    void shutdown() {
        mutTaskPending.lock();

        forceThreadShutdown = true;
        std::queue<ITask*>().swap(taskPending);

        mutTaskPending.unlock();

        condTaskPending.notify_all();

        for (auto&& th : lstTh) {
            th.join();
        }

        numThreads = 0;
        lstTh.clear();
    }


private:
    static void threadRoutine(ThreadPoolV2A* thisPtr) {
        auto&& taskPending = thisPtr->taskPending;
        auto&& mutTaskPending = thisPtr->mutTaskPending;
        auto&& condTaskPending = thisPtr->condTaskPending;

        auto&& taskRunning = thisPtr->taskRunning;
        auto&& mutTaskRunning = thisPtr->mutTaskRunning;
        auto&& counterTaskRunning = thisPtr->counterTaskRunning;

        auto&& forceThreadShutdown = thisPtr->forceThreadShutdown;

        ITask* task = nullptr;


        for (;;) {
            {
                // WAIT FOR AN AVAILABLE PENDING TASK
                std::unique_lock<std::mutex> lkPending(mutTaskPending);

                while (0 == taskPending.size() && false == forceThreadShutdown) {
                    condTaskPending.wait(lkPending);
                }

                if (forceThreadShutdown) {
                    // lkPending.unlock(); // remember this statement
                    break;
                }

                // GET THE TASK FROM THE PENDING QUEUE
                task = taskPending.front();
                taskPending.pop();

                // PUSH IT TO THE RUNNING QUEUE
                std::lock_guard<std::mutex> lkRunning(mutTaskRunning);
                taskRunning.push_back(task);
            }

            // DO THE TASK
            task->run();

            // REMOVE IT FROM THE RUNNING QUEUE
            {
                std::lock_guard<std::mutex> lkRunning(mutTaskRunning);
                taskRunning.remove(task);
                counterTaskRunning.release();
            }
        }
    }

};



#endif // _MY_THREAD_POOL_V2A_HPP_