# NOTES OF DEMOS AND EXERCISES

## DESCRIPTION

This file contains descriptions/notes of demo and exercise in the repo.

&nbsp;

---

&nbsp;

## DEMOSTRATIONS

### DEMO 01 - HELLO

Hello multiple threading!!!

You learn how to create a thread, and how to join a thread.

&nbsp;

### DEMO 02 - PASSING ARGUMENTS

You learn how to pass arguments to a thread:

- Passing various data types of variables.
- Passing some special types (such as C++ references).

&nbsp;

### DEMO 03 - SLEEP

Making a thread sleep for a while.

&nbsp;

### DEMO 08 - DETACH

When a thread is created, one of its attributes defines whether it is joinable or detached. Only threads that are created as joinable can be joined. If a thread is created as detached, it can never be joined.

&nbsp;

### DEMO 11A - RACE CONDITION

A race condition or race hazard is the condition of an electronics, software, or other system where the system's substantive behavior is dependent on the sequence or timing of other uncontrollable events.

This program illustrates race condition: Each time you run the program, the results displayed are different.

&nbsp;

### DEMO 11B - DATA RACE

Data race specifically refers to the non-synchronized conflicting "memory accesses" (or actions, or operations) to the same memory location.

&nbsp;

### DEMO 11C - RACE CONDITION AND DATA RACE

Many people are confused about race condition and data race.

- There is a case that race condition appears without data race. That is demo A.
- There is also a case that data race appears without race condition. That is demo B.

Ususally, race condition happens together with data race. A race condition often occurs when two or more threads need to perform operations on the same memory area (data race) but the results of computations depends on the order in which these operations are performed.

Concurrent accesses to shared resources can lead to unexpected or erroneous behavior, so parts of the program where the shared resource is accessed need to be protected in ways that avoid the concurrent access. This protected section is the critical section or critical region.

&nbsp;

### DEMO 12 - MUTEX

Mutexes are used to prevent data inconsistencies due to race conditions.

Mutexes are used for serializing shared resources. Anytime a global resource is accessed by more than one thread the resource should have a Mutex associated with it.

One can apply a mutex to protect a segment of memory ("critical region") from other threads. Mutexes can be applied only to threads in a single process and do not work between processes as do semaphores.

&nbsp;

### DEMO 13 - DEADLOCK

There are 2 workers "foo" and "bar".

They try to access resource A and B (which are protected by mutResourceA and mutResourceB).

Scenario:

```text
foo():
    synchronized:
        access resource A

        synchronized:
            access resource B

bar():
    synchronized:
        access resource B

        synchronized:
            access resource A
```

After foo accessing A and bar accessing B, foo and bar might wait other together ==> Deadlock occurs.

&nbsp;

### DEMO 15 - REENTRANT LOCK (RECURSIVE MUTEX)

The reason for using reentrant lock is to avoid a deadlock due to e.g. recursion.

A reentrant lock is a synchronization primitive that may be acquired multiple times by the same thread. Internally, it uses the concepts of "owning thread" and "recursion level" in addition to the locked/unlocked state used by primitive locks.

In the locked state, some thread owns the lock; in the unlocked state, no thread owns it.

&nbsp;

### DEMO 16 - BARRIER

In cases where you must wait for a number of tasks to be completed before an overall task can proceed, barrier synchronization can be used.

&nbsp;

### DEMO 17 - READ-WRITE LOCK

In many situations, data is read more often than it is modified or written. In these cases, you can allow threads to read concurrently while holding the lock and allow only one thread to hold the lock when data is modified. A multiple-reader single-writer lock (or read/write lock) does this.

A read/write lock is acquired either for reading or writing, and then is released. The thread that acquires the read-write lock must be the one that releases it.

&nbsp;

### DEMO 18A - SEMAPHORE

#### Version A01

In an exam, each candidate is given a couple of 2 scratch papers. Write a program to illustrate this scenario.

The program will combine 2 scratch papers into one test package, concurrenly.

&nbsp;

#### Version A02

The problem in version 01 is:

- When "makeOnePaper" produces too fast, there are a lot of pending papers...

This version 02 solves the problem:

- Use a semaphore to restrict "makeOnePaper": Only make papers when a package is finished.

&nbsp;

#### Version A03

The problem in this version is DEADLOCK, due to a mistake of semaphore synchronization.

&nbsp;

### DEMO 18B - SEMAPHORE

A car is manufactured at each stop on a conveyor belt in a car factory.

A car is constructed from thefollowing parts: chassis, tires. Thus there are 2 tasks in manufacturing a car. However, 4 tires cannot be added until the chassis is placed on the belt.

There are:

- 2 production lines (i.e. 2 threads) of making tires.
- 1 production line (i.e. 1 thread) of making chassis.

Write a program to illustrate this scenario.

&nbsp;

---

&nbsp;

## EXERCISES

### EX01 - MAX DIV

Problem statement: Find the integer in the range 1 to 100000 that has the largest number of divisors.

&nbsp;

#### Version A

The solution without multithreading.

&nbsp;

#### Version B

This source code file contains the solution using multithreading.

There are 2 phases:

- Phase 1:
  - Each worker finds result on a specific range.
  - This phase uses multiple threads.

- Phase 2:
  - Based on multiple results from workers, main function get the final result with maximum numDiv.
  - This phase uses a single thread (i.e. main function).

&nbsp;

#### Version C

The difference between version C and version B is:

- Each worker finds result on a specific range, and then update final result itself.
- So, main function does nothing.

&nbsp;

### EX02 - THE PRODUCER-CONSUMER PROBLEM

The producer–consumer problem (also known as the bounded-buffer problem) is a classic example of a multi-process synchronization problem. The first version of which was proposed by Edsger W. Dijkstra in 1965.

In the producer-consumer problem, there is one producer that is producing something and there is one consumer that is consuming the products produced by the producer. The producers and consumers share the same memory buffer that is of fixed-size.

The job of the producer is to generate the data, put it into the buffer, and again start generating data. While the job of the consumer is to consume the data from the buffer.

In the later formulation of the problem, Dijkstra proposed multiple producers and consumers sharing a finite collection of buffers.

**What are the problems here?**

- The producer and consumer should not access the buffer at the same time.

- The producer should produce data only when the buffer is not full.
  - If the buffer is full, then the producer shouldn't be allowed to put any data into the buffer.

- The consumer should consume data only when the buffer is not empty.
  - If the buffer is empty, then the consumer shouldn't be allowed to take any data from the buffer.

&nbsp;

### EX03 - THE READERS-WRITERS PROBLEM

#### Problem statement

Consider a situation where we have a file shared between many people.

If one of the people tries editing the file, no other person should be reading or writing at the same time, otherwise changes will not be visible to him/her. However if some person is reading the file, then others may read it at the same time.

Precisely in Computer Science we call this situation as the readers-writers problem.

**What are the problems here?**

- One set of data is shared among a number of processes.
- Once a writer is ready, it performs its write. Only one writer may write at a time.
- If a process is writing, no other process can read it.
- If at least one reader is reading, no other process can write.

&nbsp;

#### Problem variations

##### Second readers-writers problem

The first solution is suboptimal, because it is possible that a reader R1 might have the lock, a writer W be waiting for the lock, and then a reader R2 requests access.

It would be unfair for R2 to jump in immediately, ahead of W; if that happened often enough, W would STARVE. Instead, W should start as soon as possible.

This is the motivation for the second readers–writers problem, in which the constraint is added that no writer, once added to the queue, shall be kept waiting longer than absolutely necessary. This is also called writers-preference.

##### Third readers-writers problem

In fact, the solutions implied by both problem statements can result in starvation - the first one may starve writers in the queue, and the second one may starve readers.

Therefore, the third readers–writers problem is sometimes proposed, which adds the constraint that no thread shall be allowed to starve; that is, the operation of obtaining a lock on the shared data will always terminate in a bounded amount of time.

Solution:

- The idea is using a semaphore "serviceQueue" to preserve ordering of requests (signaling must be FIFO).

&nbsp;

### EX04 - THE DINING PHILOSOPHERS PROBLEM

#### Problem statement

The dining philosophers problem states that there are 5 philosophers sharing a circular table and they eat and think alternatively. There is a bowl of rice for each of the philosophers and 5 chopsticks.

A philosopher needs both their right and left chopstick to eat.

A hungry philosopher may only eat if there are both chopsticks available.

Otherwise a philosopher puts down their chopstick and begin thinking again.

&nbsp;

#### Solution

A solution of the dining philosophers problem is to use a semaphore to represent a chopstick.

A chopstick can be picked up by executing a wait operation on the semaphore and released by executing a signal semaphore.

The structure of a random philosopher ```i``` is given as follows:

```pseudocode
while true do
    wait( chopstick[i] );
    wait( chopstick[ (i+1) % 5] );

    EATING THE RICE

    signal( chopstick[i] );
    signal( chopstick[ (i+1) % 5] );

    THINKING
```

**What are the problems here?**

- Deadlock.
- Starvation.

The above solution makes sure that no two neighboring philosophers can eat at the same time. But this solution can lead to a deadlock. This may happen if all the philosophers pick their left chopstick simultaneously. Then none of them can eat and deadlock occurs.

Some of the ways to avoid deadlock are as follows:

- An even philosopher should pick the right chopstick and then the left chopstick while an odd philosopher should pick the left chopstick and then the right chopstick.
- A philosopher should only be allowed to pick their chopstick if both are available at the same time.

&nbsp;

### EX06 - MATRIX PRODUCTION

#### Version A: Matrix-vector multiplication

For an example:

Matrix A:

```text
|   1   2   3   |
|   4   5   6   |
|   7   8   9   |
```

Vector b:

```text
|   3   |
|   -1  |
|   0   |
```

The multiplication of A and b is the vector:

```text
|   1   |
|   7   |
|   13  |
```

**Solution:**

- Separate matrix A into list of rows.
- For each row, calculate scalar product with vector b.
- We can process each row individually. Therefore multithreading will get the job done.

&nbsp;

#### Version B: Matrix-matrix production (dot product)

For an example:

Matrix A:

```text
|   1   3   5   |
|   2   4   6   |
```

Matrix B:

```text
|   1   0   1   0   |
|   0   1   0   1   |
|   1   0   0   -2  |
```

The result of dot(A, B) is the matrix:

```text
|   6   3   1   -7  |
|   8   4   2   -8  |
```

&nbsp;