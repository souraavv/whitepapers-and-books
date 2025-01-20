- [Java Concurrency in Practice](#java-concurrency-in-practice)
  - [Chapter 1. Introduction](#chapter-1-introduction)
    - [Benefits of Threads](#benefits-of-threads)
      - [Exploiting Multiple Processors](#exploiting-multiple-processors)
    - [Risks of Threads](#risks-of-threads)
      - [Safety Hazards](#safety-hazards)
      - [Liveness Hazards](#liveness-hazards)
      - [Performance Hazards](#performance-hazards)
  - [Chapter 2. Thread Safety](#chapter-2-thread-safety)
    - [What is Thread Safety?](#what-is-thread-safety)
      - [Example: A Stateless Servlet](#example-a-stateless-servlet)
    - [Atomicity](#atomicity)
      - [Example: Race Conditions in Lazy Initialization](#example-race-conditions-in-lazy-initialization)
      - [Compound Actions](#compound-actions)
      - [Java's builtin mechanism for ensuring atomicity.](#javas-builtin-mechanism-for-ensuring-atomicity)
    - [Locking](#locking)
      - [Intrinsic Locks](#intrinsic-locks)
      - [Reentracy](#reentracy)
    - [Guarding State with Locks](#guarding-state-with-locks)
    - [Liveness and Performance](#liveness-and-performance)
  - [Chapter 3. Sharing Objects](#chapter-3-sharing-objects)
    - [Visibility](#visibility)
      - [Stale Data](#stale-data)
      - [Nonatomic 64-bit Operations](#nonatomic-64-bit-operations)
      - [Locking and Visibility](#locking-and-visibility)
      - [Volatile Variables](#volatile-variables)
    - [Publication and Escape](#publication-and-escape)
    - [Thread Confinement](#thread-confinement)
      - [Stack Confinement](#stack-confinement)
      - [ThreadLocal](#threadlocal)
    - [Immutability](#immutability)
      - [Final Fields](#final-fields)
    - [Safe Publication](#safe-publication)
      - [Caching the Last Result Using a Volatile Reference to an Immutable Holder Object.](#caching-the-last-result-using-a-volatile-reference-to-an-immutable-holder-object)
      - [Safe Publication Idioms](#safe-publication-idioms)
    - [Summary](#summary)
  - [Chapter 4. Composing Objects](#chapter-4-composing-objects)
    - [Designing a Thread-safe Class](#designing-a-thread-safe-class)
      - [State-dependent Operations](#state-dependent-operations)
      - [State Ownership](#state-ownership)
      - [Instance Confinement](#instance-confinement)
      - [The Java Monitor Pattern](#the-java-monitor-pattern)
      - [Example: Tracking Fleet Vehicles](#example-tracking-fleet-vehicles)
      - [Example: Vehicle Tracker Using Delegation](#example-vehicle-tracker-using-delegation)
      - [When Delegation Fails](#when-delegation-fails)
    - [Publishing underlying state variables](#publishing-underlying-state-variables)
    - [Adding Functionality to Existing Thread-safe Classes](#adding-functionality-to-existing-thread-safe-classes)
      - [Client-side Locking](#client-side-locking)
  - [Chapter 5. Building Blocks](#chapter-5-building-blocks)
    - [Synchronized Collections](#synchronized-collections)
      - [Problems with Synchronized Collections](#problems-with-synchronized-collections)
      - [Iterators and ConcurrentModificationException](#iterators-and-concurrentmodificationexception)
      - [Hidden Iterators](#hidden-iterators)
    - [Concurrent collections](#concurrent-collections)
      - [ConcurrentHashMap](#concurrenthashmap)
      - [Additional Atomic Map Operations](#additional-atomic-map-operations)
      - [CopyOnWriteArrayList](#copyonwritearraylist)
    - [Blocking Queues \& The Producer-Consumer pattern](#blocking-queues--the-producer-consumer-pattern)
      - [Serial thread confinement](#serial-thread-confinement)
      - [Deques and work stealing](#deques-and-work-stealing)
    - [Blocking and interruptible methods](#blocking-and-interruptible-methods)
    - [Synchronizers](#synchronizers)
      - [Latches](#latches)
      - [FutureTask](#futuretask)
      - [Semaphores](#semaphores)
  - [Chapter 6. Task Execution](#chapter-6-task-execution)
    - [Executing Tasks in Threads](#executing-tasks-in-threads)
      - [Executing Tasks Sequentially](#executing-tasks-sequentially)
      - [Explicitly Creating Threads for Tasks](#explicitly-creating-threads-for-tasks)
      - [Disadvantages of Unbounded Thread Creation](#disadvantages-of-unbounded-thread-creation)
    - [The Executor Framework](#the-executor-framework)
      - [Execution Policies](#execution-policies)
      - [Thread Pools](#thread-pools)
      - [Executor Lifecycle](#executor-lifecycle)
      - [Delayed and Periodic Tasks](#delayed-and-periodic-tasks)


# Java Concurrency in Practice

Book - Java Concurrency in Practice By Brian Goetz et. al.
The text in the book revolves around Java (pre-req) 

## Chapter 1. Introduction

- Writing correct programs is hard; writing correct concurrent programs is harder.
- So, why do we bother with concurrency? 
  - Threads are the easiest way to tap the computing power of multiprocessor systems

### Benefits of Threads
#### Exploiting Multiple Processors

### Risks of Threads
#### Safety Hazards
#### Liveness Hazards
#### Performance Hazards


## Chapter 2. Thread Safety
- Thread safety
    - at it's core, managing access to **shared mutable state**
    - **shared** : variable accessed by multiple threads
    - **mutable** : variable could change during it's lifetime
    - **state** : an object's state is the one that could affect it's externally visible behaviour
> [!NOTE] 
> Thread safety is a term applied to code but it's about state, could be applied to entire body of code that encapsulates it's state, that may be an object or entire program
- If multiple threads access the same mutable state variable without appropriate synchronization, your program is broken. There are three ways to fix it:
  1. **unshared** : Don't share the state variable across threads;
  2. **immutable** : Make the state variable immutable; or
  3. **synchronization** : Use synchronization whenever accessing the state variables 
>[!TIP] 
> Whenever more than one thread accesses a given state variable, and one of them might write to it, they all must coordinate their access to it using synchronization.
- Synchronization mechnaism's in java
    - `synchronized` keyword
    - Explicit locks
    - `volatile` variables
    - Atomic variables
- It is far easier to design a class to be thread-safe than to retrofit it for thread safety later.
- When designing thread-safe classes, good object-oriented techniques are our best friends
    - Encapsulation, 
    - Immutability, and 
    - Clear specification of invariants

### What is Thread Safety?
-  A class is thread-safe if it behaves correctly when accessed from multiple threads, regardless of the scheduling or interleaving of the execution of those threads by the runtime environment, and with no additional synchronization or other coordination on the part of the calling code
    -  **Correctness** : class conforms to it's specification
    -  **Specification** : defines invariants constraining an object's state and postconditions describing the effects of its operations

> [!NOTE]
>  **thread-safe class** encapsulate any needed synchronization so that clients need not provide their own 

>[!IMPORTANT]
> No set of operations performed sequentially or concurrently on instances of a thread-safe class can cause an instance to be in an invalid state (i.e correctness)

#### Example: A Stateless Servlet

- StatelessFactorizer is, like most servlets, stateless: it has no fields and references no fields from other classes
    ```java
    @ThreadSafe 
    public class StatelessFactorizer implements Servlet {
        public void service(ServletRequest req, ServletResponse resp) {
            BigInteger i = extractFromRequest(req);
            BigInteger[] factors = factor(i);
            encodeIntoResponse(resp, factors);
        }
    }
    ```
- Stateless objects are always thread-safe ? 
    - The transient state for a particular computation exists solely in local variables that are stored on the thread's stack and are accessible only to the executing thread.
    - One thread accessing a `StatelessFactorizer` cannot influence the result of another thread accessing the same `StatelessFactorizer`; because the two threads do not share state, it is as if they were accessing different instances.
- When servlets wants to remember things from one request to another thread safety requirements becomes an issue.

### Atomicity
- What happen when we add one element of state to what was a stateless object ? 
    ```java
    @NotThreadSafe 
    public class UnsafeCountingFactorizer implements Servlet {

        private int count = 0;
        public long getCount() {
            return count;
        }

        public void service(ServletRequest req, ServletResponse resp) {
            BigInteger i = extractFromRequest(req);
            BigInteger[] factors = factor(i);
            ++count;
            encodeIntoResponse(resp, factors);
        }
    }
    ```
- Unfortunately, `UnsafeCountingFactorizer` is not thread-safe, even though it would work just fine in a single-threaded environment. 
- It is susceptible to lost updates 
- While `++count`, may look like a single action because of compact syntax, it is not *atomic*, it is a set of three discrete operations: fetch the current value, add one to it, and write the new value back.
  - Example of *read-modify-write* 

- The possibility of incorrect results in the presence of unlucky timing is so important in concurrent programming that it has a name: a **race condition**.
>[!NOTE]
> A **race condition** occurs when the correctness of a computation depends on the relative timing or interleaving of multiple threads by the runtime; in other words, when getting the right answer relies on lucky timing.

- **check-then-act** :
    - Most common type of race condition, happens because of invalidation of observations
    - Potentially stale observation is used to make a decision (which becomes invalid by the time we acted on it)
    - Eg : You observe something to be true (file X doesn't exist) and then take action based on that observation (create X); but in fact the observation could have become invalid between the time you observed it and the time you acted on it (someone else created X in the meantime), causing a problem (unexpected exception, overwritten data, file corruption).

>[!WARNING]
> **Race Condition v/s Data Race**
> 
> - The term race condition is often confused with the related term data race, which arises when synchronization is not used to coordinate all access to a shared nonfinal field.
> - Not all race conditions are data races, and not all data races are race conditions, but they both can cause concurrent programs to fail in unpredictable ways. 

#### Example: Race Conditions in Lazy Initialization
- Lazy Initialization (specification required to ensure correctness in multi-threaded environment):
    1. defer initializing object until it is actually needed
    2. ensuring it is initialized only once
- Race Condition in Lazy Initialization. Don't do this.
    ```java
    @NotThreadSafe
    public class LazyInitRace {
        private ExpensiveObject instance = null;

        public ExpensiveObject getInstance() {
            if (instance == null) {
                instance = new ExpensiveObject();
            }
            return instance;
        }
    }
    ```
- `LazyInitRace` has race conditions that can undermine its correctness. 
    - Eg : Threads A and B execute `getInstance` at the same time. A and B both sees `instance` as `null`, callers of `getInstance` may receive two different results. This will lead to inconsistent state.
- Like most concurrency errors, race conditions don't always result in failure: some unlucky timing is also required. But race conditions can cause serious problems.

#### Compound Actions
- Sequences of operations that must be executed atomically in order to remain thread-safe.
- Both `LazyInitRace` and `UnsafeCountingFactorizer` contained a sequence of operations that needed to be atomic, or indivisible, relative to other operations on the same state.
- To avoid race conditions, there must be a way to prevent other threads from using a variable while we're in the **middle of modifying it**, so we can ensure that other threads can observe or modify the state only before we start or after we finish, but not in the middle.

>[!IMPORTANT]
> Operations A and B are atomic with respect to each other if, from the perspective of a thread executing A, when another thread executes B, either all of B has executed or none of it has. 

- An **atomic operation** is one that is atomic with respect to all operations, including itself, that operate on the same state.

#### Java's builtin mechanism for ensuring atomicity.

```java
import java.util.concurrent.atomic;

@ThreadSafe 
public class UnsafeCountingFactorizer implements Servlet {

    private final AtomicLong count = new AtomicLong(0);

    public long getCount() { count.get() };

    public void service(ServletRequest req, ServletResponse resp) {
        BigInteger i = extractFromRequest(req);
        BigInteger[] factors = factor(i);
        count.incrementAndGet();
        encodeIntoResponse(resp, factors);
    }
}
```

- The `java.util.concurrent.atomic` package contains atomic variable classes for effecting atomic state transitions on numbers and object references.
- By replacing the `long` counter with an `AtomicLong`, we ensure that all actions that access the counter state are atomic.

>[!NOTE]
> When a single element of state is added to a stateless class, the resulting class will be thread-safe if the state is entirely managed by a thread-safe object. In the previous example, single element of state is added i.e `count` which is entirely managed by thread-safe object i.e `AtomicLong`

### Locking

- [Q] We were able to add one state variable to our servlet while maintaining thread safety by using a thread-safe object to manage the entire state of the servlet. But if we want to add more state to our servlet, can we just add more thread-safe state variables?
    ```java

    @NotThreadSafe 
    public class UnsafeCachingFactorization implements Servlet {

        private final AtomicReference<BigInteger> lastNumber = 
                new AtomicReference<BigInteger>();
        private final AtomicReference<BigInteger>[] lastFactors = 
                new AtomicReference<BigInteger[]>();

        public void service(ServletRequest req, ServletRequest resp) {
            BigInteger i = extractFromRequest();
            if (i.equals(lastNumber.get())) {
                encodeIntoResponse(resp, lastFactors.get());
            } else {
                BigInteger[] factors = factor(i);
                lastNumber.set(i);
                lastFactors.set(factors);
                encodeIntoResponse(resp, factors);
            }
        }
    }
    ```

- Unfortunately, this approach does not work. Even though the atomic references are individually thread-safe, UnsafeCachingFactorizer has race conditions that could make it produce the wrong answer, why ?
  - When multiple variables participate in an invariant, they are not independent: the value of one constrains the allowed value(s) of the others. Thus when updating one, you must update the others in the same atomic operation.

>[!IMPORTANT]
> To preserve state consistency, update related state variables in a single atomic operation.

#### Intrinsic Locks
- Java provides a built-in locking mechanism for enforcing atomicity: the `synchronized` block. 
    ```java
    synchronized(lock) {
        // Access to modify shared state guarded by lock
    }
    ```
- A `synchronized` block has two parts: a reference to an object that will serve as the lock, and a block of code to be guarded by that lock.
-  A `synchronized` method is a shorthand for a `synchronized` block that spans an entire method body, and whose lock is the object on which the method is being invoked. 
-  Static `synchronized` methods use the `Class` object for the lock
-  Every Java object can implicitly act as a lock for purposes of synchronization;
-   The lock is automatically acquired by the executing thread before entering a `synchronized` block and automatically released when control exits the synchronized block, whether by the normal control path or by throwing an exception out of the block. 
- These built-in locks are called **intrinsic locks** or **monitor locks**
- Intrinsic locks in Java act as mutexes (or mutual exclusion locks), which means that at most one thread may own the lock.
  - When thread A attempts to acquire a lock held by thread B, A must wait, or block, until B releases it. If B never releases the lock, A waits forever.
  - Execute as a single, indivisible unit
    ```java

    @ThreadSafe
    public class SynchronizedFactorizer implements Servlet {

        @GuardedBy("this") private BigInteger lastNumber;
        @GuardedBy("this") private BigInteger[] lastFactors;

        public synchronized void service(ServletRequest req, 
                ServletResponse resp) {
            BigInteger i = extractFromRequest(req);
            if (i.equals(lastNumber)) {
                encodeIntoResponse(resp, lastFactors);
            } else {
                BigInteger[] factors = factor(i);
                lastNumber = i;
                lastFactors = factors;
                encodeIntoResponse(resp, factors);
            }
        }
    }
    ```
- The above will result in unacceptably poor responsiveness. This problem—which is a performance problem, not a thread safety problem (will fix later)

#### Reentracy
- When a thread requests a lock that is already held by another thread, the requesting thread blocks.
- But because intrinsic locks are reentrant, if a thread tries to acquire a lock that it already holds, the request succeeds.
>[!IMPORTANT]
> Reentrancy means that locks are acquired on a per-thread rather than per-invocation basis.
> 
> This differs from the default locking behavior for pthreads (POSIX threads) mutexes, which are granted on a per-invocation basis.
- Reentrancy is implemented by associating with each lock an acquisition count and an owning thread. 
    - When the count is zero, the lock is considered unheld.
    - When a thread acquires a previously unheld lock, the JVM records the owner and sets the acquisition count to one
    - If that same thread acquires the lock again, the count is incremented, and when the owning thread exits the `synchronized` block, the count is decremented. When the count reaches zero, the lock is released.
- Reentrancy facilitates encapsulation of locking behavior, and thus **simplifies the development of object-oriented concurrent code**.
    ```java

    public class Widget {
        public synchronized void doSomething() {
            ...
        }
    }

    public class LoggingWidget extends Widget {
        public synchronized void doSomething() {
            super.doSomething();
        }
    }
    ```
    - Without reentrant locks, the very natural-looking code, in which a subclass overrides a synchronized method and then calls the superclass method, would deadlock. Because the doSomething methods in Widget and LoggingWidget are both synchronized, each tries to acquire the lock on the Widget before proceeding. 
    - But if intrinsic locks were not reentrant, the call to `super.doSomething` would never be able to acquire the lock because it would be considered already held, and the thread would permanently stall waiting for a lock it can never acquire.

### Guarding State with Locks

- Locks enables serialized access to the code path they guard
- Compound actions on shared state, such as incrementing a hit counter (read-modify-write) or lazy init (check-then-act), must be atomic to avoid *race conditions*
- Synchronization using `synchronized` method : It is a common mistake to assume that synchronization needs to be used only when writing to shared variables; this is simply not true.  (will discuss later)
- Synchronization using explicit locks : For each mutable state variable that may be accessed by more than one thread, all accesses to that variable must be performed with the same lock held. In this case, we say that the **variable is guarded by that lock**.
    - Every shared, mutable variable should be guarded by exactly one lock. Make it clear to maintainers which lock that is.
    - When a variable is guarded by a lock—meaning that every access to that variable is performed with that lock held—you've ensured that only one thread at a time can access that variable. 

>[!TIP]
> Each object in Java has built-in intrinsic lock 
> 
> The fact that every object has a built-in lock is just a convenience so that you needn't explicitly create lock objects. 

- When a class has invariants that involve more than one state variable, there is an additional requirement: each variable participating in the invariant must be guarded by the same lock. 
    - This allows you to access or update them in a single atomic operation, preserving the invariant
- If synchronization is the cure for race conditions, why not just declare every method synchronized? 
  - It turns out that such indiscriminate application of synchronized might be either too much or too little synchronization.
  - Merely synchronizing every method, as Vector does, is not enough to render compound actions on a Vector atomic:
    ```java
    if (!vector.contains(element)) {
        vector.add(element)
    }
    ```
    - This attempt at a put-if-absent operation has a race condition, even though both contains and add are atomic. 
    - While synchronized methods can make individual operations atomic, additional locking is required when multiple operations are combined into a compound action.
  - Synchronizing every method can lead to performance or liveness problems

### Liveness and Performance
- Using `synchronized` method can hurt the liveness and performance
- Operations that do not impact the shared state and consume a lot of CPU cycles can be optimized by using fine-grained control over the synchronized block.
- At the same time, we don’t want a synchronization block to be so small that it breaks the isolation of the shared state or introduces additional overhead of acquiring & releasing locks.

    ```java

    @ThreadSafe
    public class CacheFactorizer implements Servlet {
        @GuardedBy("this") private BigInteger lastNumber;
        @GuardedBy("this") private BigInteger[] lastFactors;
        @GuardedBy("this") private long hits;
        @GuardedBy("this") private long cacheHits;

        public synchronized long getHits() {
            return hits;
        }
        public synchronized double getCacheHitRatio() {
            return (double) cacheHits / (double) hits;
        }

        public void service(ServletRequest req, ServletResponse resp) {
            BigInteger i = extraFromRequest(req);
            BigInteger[] factors = null;
            synchronized(this) {
                ++hits;
                if (i.equals(lastNumber)) {
                    ++cacheHits;
                    factors = lastFactors.clones();
                }
            }
            if (factors == null) {
                factors = factor(i);
                synchronized(this) {
                    lastNumber = i;
                    lastFactors = factors.clone();
                }
            }
            encodeIntoResponse(resp, factors);
        }
    }
    ```

- There is frequently a tension between simplicity and performance. When implementing a synchronization policy, resist the temptation to prematurely sacriflce simplicity (potentially compromising safety) for the sake of performance.
- Whenever you use locking, you should be aware of what the code in the block is doing and how likely it is to take a long time to execute. Holding a lock for a long time, either because you are doing something compute-intensive or because you execute a potentially blocking operation, introduces the **risk of liveness** or **performance** problems.
>[!IMPORTANT]
> Avoid holding locks during lengthy computations or operations at risk of not completing quickly such as network or console I/O.


## Chapter 3. Sharing Objects
- In chapter 2. we learned primarily about managing **access** to shared, mutable state.
  - We used `synchronized` to prevent multiple threads from accessing the same data at the same time.
- This chapter examines techniques for **sharing and publishing** objects so they can be safely accessed by multiple threads
- We have seen how `synchronized` blocks and methods can ensure that operations execute atomically, but it is a common misconception that `synchronized` is only about atomicity or demarcating “critical sections”. 
    - Synchronization also has another significant, and subtle, aspect: **memory visibility**. 
>[!IMPORTANT]
> We want not only to prevent one thread from modifying the state of an object when another is using it i.e **Atomicity**, but also to ensure that when a thread modifies the state of an object, other threads can actually see the changes that were made i.e **Memory Visibility**

### Visibility
- Visibility is subtle because the things that can go wrong are so counterintuitive.
-  In a single-threaded environment, if you write a value to a variable and later read that variable with no intervening writes, you can expect to get the same value back. 
   - But when the reads and writes occur in different threads, this is simply not the case
    ```java
    public class NoVisibility {
        private static boolean ready;
        private static int number;

        private static class ReaderThread extends Thread {
            public void run() {
                while (!ready) {
                    Thread.yield();
                }
                log.info(number);
            }
        }

        public static void main(String[] args) {
            new ReaderThread().start();
            number = 42;
            ready = true;
        }
    }
    ```

- `NoVisibility` could loop forever because the value of ready might never become visible to the reader thread. 
- Even more strangely, `NoVisibility` could print zero because the write to ready might be made visible to the reader thread before the write to `number`, a phenomenon known as **reordering**. 
    - This may seem like a broken design, but it is meant to allow JVMs to take full advantage of the performance of modern multiprocessor hardware. 
    - For example, in the absence of synchronization, the Java Memory Model permits the compiler to reorder operations and cache values in registers, and permits CPUs to reorder operations and cache values in processor-specific caches. 
- **Reordering :** There is no guarantee that operations in one thread will be performed in the order given by the program, as long as the reordering is not detectable from within that thread—even if the reordering is apparent to other threads.

> [!WARNING]
> Always use the proper synchronization whenever data is shared across threads.


#### Stale Data
- Last example shows insufficiently synchronized programs can cause surprising results: *stale data*
- Stale data can cause serious and confusing failures such as unexpected exceptions, corrupted data structures, inaccurate computations, and infinite loops.
- Reading data without synchronization is analogous to using the `READ_UNCOMMITTED` isolation level in a database, where you are willing to trade accuracy for performance.
> [!CAUTION]
> In the case of unsynchronized reads, we are trading away a greater degree of accuracy, since the visible value for a shared variable can be arbitrarily stale.
```java
@ThreadSafe
public class SyncInteger {
    @GuardedBy("this") private int value;

    public synchronized int get() {
        return value;
    }
    public synchronized void set(int value) {
        this.value = value;
    }
}
```
#### Nonatomic 64-bit Operations
- Safety guarantee provided by unsynchronized reads of a variable is called *out-of-thin-air* safety.
    - When a thread reads a variable without synchronization, it may see a stale value, but at least it sees a value that was actually placed there by some thread rather than some random value. 
- **Out-of-thin-air** safety applies to all variables, with one exception: 64-bit numeric variables (`double` and `long`) that are not declared volatile
>[!WARNING]
> The Java Memory Model requires fetch and store operations to be atomic, but for nonvolatile long and double variables, the JVM is permitted to treat a 64-bit read or write as two separate 32-bit operations. If the reads and writes occur in different threads, it is therefore possible to read a nonvolatile long and get back the high 32 bits of one value and the low 32 bits of another.
>
> When the Java Virtual Machine Specification was written, many widely used processor architectures could not efficiently provide atomic 64-bit arithmetic operations.
- Thus, even if you don't care about stale values, it is not safe to use shared mutable long and double variables in multithreaded programs unless they are declared volatile or guarded by a lock.

#### Locking and Visibility

>[!IMPORTANT]
> We can now give the other reason for the rule requiring all threads to synchronize on the same lock when accessing a shared mutable variable—to guarantee that values written by one thread are made visible to other threads. Otherwise, if a thread reads a variable without holding the appropriate lock, it might see a stale value.

- Locking is not just about mutual exclusion; it is also about **memory visibility**. To ensure that all threads see the most up-to-date values of shared mutable variables, the reading and writing threads must synchronize on a common lock.
    - *Intrinsic locking* can be used to guarantee that one thread sees the effects of another in a predictable manner.

> [!TIP]
> Everything thread A did *in or prior* to a synchronized block is visible to thread B when it executes a synchronized block guarded by the same lock.

#### Volatile Variables
- The Java language also provides an alternative, weaker form of synchronization, *volatile variables*, to ensure that updates to a variable are propagated predictably to other threads.
  
>[!NOTE]
>  1. **No Reordering** : When a field is declared `volatile`, the compiler and runtime are put on notice that this variable is shared and that operations on it should not be reordered with other memory operations
>
> 2. **No Caching**: Volatile variables are not cached in registers or in caches where they are hidden from other processors, so a read of a volatile variable always returns the most recent write by any thread.

- Yet accessing a `volatile` variable performs no locking and so cannot cause the executing thread to block, making `volatile` variables a **lighter-weight synchronization mechanism** than `synchronized`
    - Visibility effects of volatile variables extend beyond the value of the volatile variable itself.
    - When thread A writes to a volatile variable and subsequently thread B reads that same variable, the values of all variables that were visible to A prior to writing to the volatile variable become visible to B after reading the volatile variable.
    - So from a memory visibility perspective, writing a volatile variable is like exiting a synchronized block and reading a volatile variable is like entering a synchronized block. 

>[!WARNING]
> Use volatile variables only when they simplify implementing and verifying your synchronization policy; avoid using volatile variables when veryfing correctness would require subtle reasoning about visibility. 

- Volatile variables are convenient, but they have limitations
    - The semantics of volatile are not strong enough to make the increment operation (`count++`) atomic, unless you can guarantee that the variable is written only from a single thread.
    - Atomic variables do provide atomic *read-modify-write* support and can often be used as **“better volatile variables”**.
    **Eg :** For example, the semantics of volatile are not strong enough to make the increment operation (`count++`) atomic, unless you can guarantee that the variable is written only from a single thread.

>[!IMPORTANT]
> Locking can guarantee both visibility and atomicity; volatile variables can only guarantee visibility.

- Use volatile variable when all following criteria met:
  - Writes to the variable do not depend on its current value, or you can ensure that only a single thread ever updates the value;
  - The variable does not participate in invariants with other state variables; and
  - Locking is not required for any other reason while the variable is being accessed.

### Publication and Escape
- Publishing an object means making it available to code outside of its current scope, such as 
    - by storing a reference to it where other code can find it, 
    - returning it from a nonprivate method, or 
    - passing it to a method in another class.
- In many situations, we want to ensure that objects and their internals are not published. 
  - In other situations, we do want to publish an object for general use, but doing so in a thread-safe manner may require synchronization. 
- Publishing internal state variables can compromise encapsulation and make it more difficult to preserve invariants.
- Publishing objects before they are fully constructed can compromise thread safety. 
- An object that is published when it should not have been is said to have *escaped*.

> [!WARNING]
> Once an object escapes, you have to assume that another class or thread may, maliciously or carelessly, misuse it.

1. The most blatant form of publication is to store a reference in a public static field, where any class and thread could see it
    ```java
    public static Set<Secret> knownSecrets;
    
    public void initialize() {
        knownSecrets = new HashSet<Secret>();
    }
    ```
2. Publishing one object may indirectly publish others. 
    
    a. If you add a `Secret` to the published `knownSecrets` set, you've also published that `Secret`, because any code can iterate the `Set` and obtain a reference to the new `Secret`.
    b. Similarly, returning a reference from a nonprivate method also publishes the returned object. 
    
    **Eg :**  `UnsafeStates` publishes the supposedly `private` array of state abbreviations. In this case, the states array has escaped its intended scope, because what was supposed to be private state has been effectively made public.
    ```java
    class UnsafeStates {
        private String[] states = new String[] {
            "AK", "AL", ...
        };
        public String[] getState() {
            return states;
        }
    }
    ```

> [!NOTE]
> Any object that is reachable from a published object by following some chain of nonprivate field references and method calls has also been published.

3. Passing an object to an alien method (includes methods of other classes as well as overridable methods which are neither private nor final). 
   - Since you can't know what code will actually be invoked, you don't know that the alien method won't publish the object or retain a reference to it that might later be used from another thread.

4. Publish an inner class instance. Implicitly allowing the `this` reference to escape. !!! 💀 Don't do this 💀 !!!
    ```java
    public class ThisEscape {
        public ThisEscape(EventSource source) {
            source.registerListener(
                new EventListener() {
                    public void onEvent(Event e) {
                        doSomething(e);
                    }
                });
            )
        }
    }
    ```
    - When `ThisEscape` publishes the `EventListener`, it implicitly publishes the enclosing `ThisEscape` instance as well, because *inner class instances contain a hidden reference to the enclosing instance*.
    - An object is in a predictable, consistent state only after its constructor returns, so publishing an object from within its constructor can publish an *incompletely constructed object*. 
    - This is true even if the publication is the last statement in the constructor. If the `this` reference escapes during construction, the object is considered not properly constructed.

> [!TIP]
> Do not allow the this reference to escape during construction.

5. Start a thread from a constructor. 
    - When an object creates a thread from its constructor, it almost always shares its this reference with the new thread, either explicitly (by passing it to the constructor) or implicitly (because the `Thread` or `Runnable` is an inner class of the owning object).
    - The new thread might then be able to see the owning object before it is fully constructed. There's nothing wrong with creating a thread in a constructor, but it is best not to start the thread immediately.

- **Private Constructor and Public Factory :** If you are tempted to register an event listener or start a thread from a constructor, you can avoid the improper construction by using a private constructor and a public factory method, as shown in `SafeListener`
    ```java
    public class SafeListener {

        private final EventListener listener;

        private SafeListener() {
            listener = new EventListener() {
                public void onEvent(Event e) {
                    doSomething(e);
                }
            }
        }

        public static SafeListener newInstance(EventSource source) {
            SafeListener safe = new SafeListener();
            source.registerListener(source);
            return safe;
        }
    }
    ```

### Thread Confinement
- Accessing shared, mutable data requires using synchronization; one way to avoid this requirement is to not share. 
- If data is only accessed from a single thread, no synchronization is needed. This technique, **thread confinement**
- When an object is confined to a thread, such usage is automatically thread-safe even if the confined object itself is not 
- **Eg :** Thread confinement is commonly used in pooled JDBC `Connection` objects, as they are not thread-safe. A thread acquires a connection from the pool, processes a request synchronously, and returns it. The pool ensures the connection isn't shared with other threads during its usage, maintaining confinement.
  - The connection pool implementations provided by application servers are thread-safe; connection pools are necessarily accessed from multiple threads, so a non-thread-safe implementation would not make sense.
- Thread confinement is an element of program's design which must be enforced by its implementation. 
    - The language and core libraries provide mechanisms that can help in maintaining thread confinement : *local variables* and the `ThreadLocal` class.
    - But even with these, it is still the programmer's responsibility to ensure that thread-confined objects do not escape from their intended thread.

#### Stack Confinement
- Local variables are intrinsically confined to the executing thread.
- They exist on the executing thread's stack, which is not accessible to other threads.
- Stack confinement is a special case of thread confinement in which an object can only be reached through local variables.
- Stack confinement also called *within-thread* or *thread-local usage*
    ```java

    public int loadTheArk(Collection<Animal> candidates) {
        SortedSet<Animal> animals;
        int numPairs = 0;
        Animal candidate = null;

        animals = new TreeSet<Animal> (new SpeciesGenderComparator());
        animals.addAll(candidates);
        for (Animal a: animals) {
            if (candidate == null || !candidate.isPotentialMate(a)) {
                candidate = a;
            } else {
                ark.load(new AnimalPair(candidate, a));
                ++numPairs;
                candidate = null;
            }
        }
        return numPairs;
    }
    ```
    - However, if we were to publish a reference to the Set (or any of its internals), the confinement would be violated and the animals would escape.

#### ThreadLocal
- Thread-Local provides get and set accessormethods that maintain a separate copy of the value for each thread that uses it, so a get returns the most recent value passed to set from the currently executing thread.

### Immutability
- The other end-run around the need to synchronize is to use immutable objects
- If an object's state cannot be modified, these risks and complexities simply go away.
- An immutable object is one whose state cannot be changed after construction.
- Immutable objects are inherently thread-safe; their invariants are established by the constructor
>[!NOTE]
> Immutable objects are always thread-safe.
- There is a difference between an object being immutable and the reference to it being immutable
#### Final Fields
- The `final` keyword, a more limited version of the `const` mechanism from C++
- Final fields can't be modified (although the objects they refer to can be modified if they are mutable), but they also have special semantics under the Java Memory Model
- Just as it is a good practice to make all fields private unless they need greater visibility [EJ Item 12], it is a good practice to make all fields final unless they need to be mutable.

### Safe Publication
- So far we have focused on ensuring that an object not be published, such as when it is supposed to be confined to a thread or within another object. 
- Of course, sometimes we do want to share objects across threads, and in this case we must do so safely.
    

#### Caching the Last Result Using a Volatile Reference to an Immutable Holder Object.
```java
@Immutable
Class OneValueCache {
    private final BigInteger lastNumber;
    private final BigInteger[] lastFactors;

    public OneValueCache(BigInteger i, BigInteger[] factors) {
        lastNumber = i
        lastFactors = Arrays.copyOf(factors, factors.length);
    }

    public BigInteger[] getFactors(BigInteger i) {
        if (lastNumber == null || !lastNumber.equals(i)) {
            return null;
        } else {
            return Arrays.copyOf(lastFactors, lastFactors.length);
        }
    }
}

@ThreadSafe 
public class VolatileCacheFactorizer implements Servlet {

    private volatile OneValueCache cache = 
            new OneValueCache(null, null);

    public void service(ServletRequest req, ServletResponse resp) {
        BigInteger i = extractFromRequest(req);
        BigIntger[] factors = cache.getFactors(i);

        if (factors == null) {
            factors = factor(i);
            cache = new OneValueCache(i, factors);
        }
        return factors;
    }
}
```

#### Safe Publication Idioms
- Objects that are mutable must be safely published, which usually entails synchronization by both the publishing and the consuming thread.
<details>
<summary> Example </summary>

```java
class UnsafePublishExample {
    // Shared mutable object (NOT safely published)
    private MutableObject mutableObject;

    public void publishObject() {
        mutableObject = new MutableObject(42); // Publisher thread initializes the object
    }

    public MutableObject getObject() {
        return mutableObject; // Consumer thread retrieves the object
    }
}

class MutableObject {
    private int value;

    public MutableObject(int value) {
        this.value = value; // Initialize the value
    }

    public int getValue() {
        return value;
    }
}


```

- Safe Publication 

```java
class SafePublishExample {
    private MutableObject mutableObject;
    private final Object lock = new Object();

    // Publisher thread
    public void publishObject(int value) {
        synchronized (lock) {
            mutableObject = new MutableObject(value); // Object is published safely
        }
    }

    // Consumer thread
    public MutableObject getObject() {
        synchronized (lock) {
            return mutableObject; // Access is synchronized
        }
    }
}

public class SafePublishDemo {
    public static void main(String[] args) {
        SafePublishExample example = new SafePublishExample();

        // Publisher thread
        new Thread(() -> example.publishObject(42)).start();

        // Consumer thread
        new Thread(() -> {
            MutableObject obj = example.getObject();
            if (obj != null) {
                System.out.println(obj.getValue()); // Safely reads the value
            }
        }).start();
    }
}

```
</details>


### Summary
The most useful policies for using and sharing objects in a concurrent program are:
- **Thread-confined**. A thread-confined object is owned exclusively by and confined to one thread, and can be modifled by its owning thread.
- **Shared read-only**. A shared read-only object can be accessed concurrently by multiple threads without additional synchronization, but cannot be modified by any thread. Shared read-only objects include immutable and effectively immutable objects.
- **Shared thread-safe**. A thread-safe object performs synchronization internally, so multiple threads can freely access it through its public interface without further synchronization.
- **Guarded**. A guarded object can be accessed only with a specific lock held. Guarded objects include those that are encapsulated within other thread-safe objects and published objects that are known to be guarded by a specific lock.


## Chapter 4. Composing Objects
- So far, we've covered the low-level basics of thread safety and synchronization
- But we don't want to have to analyze each memory access to ensure that our program is thread-safe; we want to be able to take thread-safe components and safely compose them into larger components or programs. 
- This chapter covers patterns for structuring classes that can make it easier to make them thread-safe and to maintain them without accidentally undermining their safety guarantees.

### Designing a Thread-safe Class
- Encapsulation makes it possible to determine that a class is thread-safe without having to examine the entire program.
- You cannot ensure thread safety without understanding an object's invariants and postconditions.

>[!IMPORTANT]
> The design process for a thread-safe class should include these three basic elements:
>
> Identify the variables that form the object's state;
>
> Identify the invariants that constrain the state variables;
>
> Establish a policy for managing concurrent access to the object's state.

- The synchronization policy defines how an object coordinates access to its state without violating its invariants or postconditions. 
    ```java
    @ThreadSafe 
    public final class Counter {
        @GuardedBy("this") private long value = 0;

        public synchronized long getValue() {
            return value;
        }

        public synchronized long increment() {
            if (value == Long.MAX_VALUE) {
                throw new IllegalStateException("counter overlfow");
            }
            return ++value;
        }
    }
    ```

>[!NOTE]
>Making a class thread-safe means ensuring that its invariants hold under concurrent access;

- Objects and variables have a *state space*: the range of possible states they can take on. The smaller this state space, the easier it is to reason about.
- By using final fields wherever practical, you make it simpler to analyze the possible states an object can be in. (In the extreme case, immutable objects can only be in a single state.)
- E.g.,  The state space of a long ranges from `Long.MIN_VALUE` to `Long.MAX_VALUE`, but `Counter` places constraints on value; negative values are not allowed.

####  State-dependent Operations
- Example: You cannot remove an item from an empty queue; a queue must be in the “nonempty” state before you can remove an element. Operations with state-based preconditions are called state-dependent
- In a single-threaded program, if a precondition does not hold, the operation has no choice but to fail. 
- But in a concurrent program, the precondition may become true later due to the action of another thread.
- The built-in mechanisms for efficiently waiting for a condition to become true: `wait` and `notify` are tightly bound to intrinsic locking, and can be difficult to use correctly.
- To create operations that wait for a precondition to become true before proceeding, it is often easier to use existing library classes, such as `BlockingQueue` or `Semaphore`, to provide the desired state-dependent behavior.

#### State Ownership
- Ownership is not embodied explicitly in the language, but is instead an element of class design. (Rust - hold my coffee)
  - Java Garbage Collection enabling less-than-precise thinking about ownership.
- In many cases, ownership and encapsulation go together—the object encapsulates the state it owns and owns the state it encapsulates.
- Ownership implies control, but once you publish a reference to a mutable object, you no longer have exclusive control;

#### Instance Confinement 
- Encapsulating data within an object confines access to the data to the object's methods, making it easier to ensure that the data is always accessed with the appropriate lock held.
    ```java
    @ThreadSafe
    public class PersonSet {
        @GuardedBy("this")
        private final Set<Person> mySet = new HashSet<Person>();

        public synchronized void addPerson(Person p) {
            mySet.add(p);
        }

        public synchronized boolean containsPerson(Person p) {
            return mySet.contains(p);
        }
    }
    ```
- The state of `PersonSet` is managed by a `HashSet`, which is not thread-safe. But because `mySet` is `private` and not allowed to escape, the HashSet is confined to the `PersonSet`.
- The only code paths that can access `mySet` are `addPerson` and `containsPerson`, and each of these acquires the lock on the `PersonSet`. 
- All its state is guarded by its intrinsic lock, making `PersonSet` thread-safe.
- Of course, it is still possible to violate confinement by publishing a supposedly confined object;

#### The Java Monitor Pattern
- Java's built-in (intrinsic) locks are sometimes called monitor locks or monitors. 
  - The Java monitor pattern is inspired by Hoare's work on monitors
- The Java monitor pattern is used by many library classes, such as `Vector` and `Hashtable`
- The Java monitor pattern is merely a convention; any lock object could be used to guard an object's state so long as it is used consistently

    ```java
    public class PrivateLock {
        private final Object myLock = new Object();
        @GuardedBy("myLock") Widget widget;

        void someMethod() {
            synchronized(myLock) {

            }
        }
    }
    ```
- There are advantages to using a private lock object instead of an object's intrinsic lock
- Making the lock object private encapsulates the lock so that client code cannot acquire it and thus avoiding liveness problems (if public then client code can also access lock and thus can cause liveness issues by acquiring it)

#### Example: Tracking Fleet Vehicles
- Let's build a slightly less trivial example: a **vehicle tracker** for dispatching fleet vehicles such as taxicabs, police cars, or delivery trucks.
- We'll build it first using the monitor pattern, and then see how to relax some of the encapsulation requirements while retaining thread safety.
- Each `vehicle` is identified by a `String` and has a location represented by (x, y)$ coordinates

```java
@ThreadSafe
public class MonitorVehicleTracker {
    @GuardedBy("this")
    private final Map<String, MutablePoint> locations;

    public MonitorVehicleTracker(Map<String, MutablePoint> locations) {
        this.locations = locations;
    }

    public synchronized Map<String, MutablePoint> getLocations() {
        return deepCopy(locations);
    }

    public synchronized MutablePoint getLocation(String id) {
        MutablePoint loc = locations.get(id);
        return loc == null ? null: new MutablePoint(loc);
    }

    public synchronized void setLocation(String id, int x, int y) {
        MutablePoint loc = locations.get(id);
        if (loc == null) {
            throw new IllegalArgumentException("No such ID: " + id);
        }
        loc.x = x;
        loc.y = y;
    }

    private static Map<String, MutablePoint> deepCopy(
            Map<String, MutablePoint> m) {
        Map<String, MutablePoint> result = 
                new HashMap<String, MutablePoint>();
        for (String id: m.keySet()) {
            result.put(id, new MutablePoint(m.get(id)));
        }
        return Collections.unmodifiableMap(result);
    }
}


@NotThreadSafe
public class MutablePoint {
    public int x, y;
    public MutablePoint() {
        x = 0;
        y = 0;
    }

    public MutablePoint(MutablePoint p) {
        this.x = p.x;
        this.y = p.y;
    }
}

// MutablePoint is not thread safe because: 
// 1. Public scope of int x and int y. Public fields allow uncontrolled access.
// 2. Copy constructor doesn’t ensure thread safety - MutablePoint p can 
//    be accessed by multiple threads

```

- This implementation maintains thread safety in part by copying mutable data before returning it to the client. 
  - This is usually not a performance issue, but could become one if the set of vehicles is very large.
- You might have observed that `deepCopy` is called from a `synchronized` method (`deepCopy` is `private`), the tracker's intrinsic lock is held for the duration of what might be a long-running copy operation, and this could degrade the responsiveness

>[!NOTE]
> Note that `deepCopy` can't just wrap the Map with an `unmodifiableMap`, because that protects only the collection from modification; it does not prevent callers from modifying the mutable objects stored in it. For the same reason, populating the `HashMap` in `deepCopy` via a copy constructor wouldn't work either, because only the references to the points would be copied, not the point objects themselves.

<details>
<summary> EXTRA: Deep Copy vs Shallow Copy - Java </summary>

Shallow Copy:
- Creates a new collection object, but the elements inside are still the same (shared references).
- Changes to the elements in one collection affect the other.

Deep Copy:
- Creates a new collection object, and also creates new copies of the elements inside it, ensuring complete independence.


Problem
- If you use `Collections.unmodifiableMap(map)`, it only makes the `Map` unmodifiable (e.g., you cannot add/remove items to/from it), but does not make the individual objects (values) stored in the Map immutable. Mutable objects can still be modified.

- Similarly, using a copy constructor like `new HashMap<>(originalMap)` only copies the references to the objects, not the actual objects themselves. It still points to the same underlying objects.

```java

import java.awt.Point;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

public class DeepCopyExample {
    public static void main(String[] args) {
        // Original map with mutable Point objects
        Map<String, Point> originalMap = new HashMap<>();
        originalMap.put("A", new Point(1, 1));
        originalMap.put("B", new Point(2, 2));

        // Attempt 1: Unmodifiable map
        Map<String, Point> unmodifiableMap = Collections
                .unmodifiableMap(originalMap);

        // Attempt 2: Shallow copy using HashMap copy constructor
        Map<String, Point> shallowCopy = new HashMap<>(originalMap);

        // Modify the Point object in the original map
        originalMap.get("A").setLocation(5, 5);

        // Observe effects
        System.out.println("Original Map: " + originalMap);
        System.out.println("Unmodifiable Map: " + unmodifiableMap);
        System.out.println("Shallow Copy: " + shallowCopy);
    }
}


/** Ouput: 
 * 
 * Original Map: {A=java.awt.Point[x=5,y=5], B=java.awt.Point[x=2,y=2]}
 * Unmodifiable Map: {A=java.awt.Point[x=5,y=5], B=java.awt.Point[x=2,y=2]}
 * Shallow Copy: {A=java.awt.Point[x=5,y=5], B=java.awt.Point[x=2,y=2]}
 * /

```

- Solution: Deep Copy

```java
public static Map<String, Point> deepCopy(Map<String, Point> original) {
    Map<String, Point> deepCopy = new HashMap<>();
    for (Map.Entry<String, Point> entry : original.entrySet()) {
        // Create a new Point object for each entry
        deepCopy.put(entry.getKey(), new Point(entry.getValue()));
    }
    return deepCopy;
}
```

</details>


#### Example: Vehicle Tracker Using Delegation

Delegating Thread Safety to a `ConcurrentHashMap`

- The example does not use any explicit synchronization; 
  - All access to state is managed by `ConcurrentHashMap`, 
  - And all the keys and values of the `Map` are immutable.

```java

@Immutable 
public class ImmutablePoint {
    private final int x;
    private final int y; 

    public ImmutablePoint(int x, int y) {
        this.x = x;
        this.y = y;
    }

    public ImmutablePoint(ImmutablePoint p) {
        this(p.x, p.y);
    }

    public int getX() { 
        return x; 
    }
    public int getY() { 
        return y; 
    }
}

```

```java
@ThreadSafe
public class DelegatingVehicleTracker {
    
    private final ConcurrentMap<String, ImmutablePoint> locations;
    private final Map<String, ImmutablePoint> unmodifiableMap;
    
    public DelegatingVehicleTracker(Map<String, ImmutablePoint> points) {
        locations = new ConcurrentMap<String, ImmutablePoint>(points);
        unmodifidedMap = Collections.unmodifiedMap(locations);
    }

    public Map<String, ImmutablePoint> getLocations() {
        return unmodifiedMap;
    }

    public Point getLocation(String id) {
        return locations.get(id);
    }

    public void setLocation(String id, int x, int y) {
        if (locations.replace(id, new ImmutablePoint(x, y)) == null) {
            throw new IllegalArgumentException("invalid ID: " + id);
        }
    }
}
```
- `ImmutablePoint` is thread-safe because it is immutable. 
- Immutable values can be freely shared and published, so we no longer need to copy the locations when returning them.
- The delegating version returns an unmodifiable but “live” view of the vehicle locations, while the monitor version returned a snapshot of the locations
  - This means that if thread *A* calls `getLocations` and thread *B* later modifies the location of some of the points, those changes are reflected in the `Map` returned to thread *A*. As we remarked earlier, this can be a benefit (more up-to-date data) or a liability (potentially inconsistent view of the fleet), depending on your requirements.
- If an unchanging view of the fleet is required, getLocations could instead return a shallow copy of the locations map.
    ```java
    public Map<String, Point> getLocations() {
        return Collections.unmodifiableMap(
            new HashMap<String, Point>(locations)
        );
    }
    ```
    - Since the contents of the `Map` are immutable, only the structure of the `Map`, not the contents, must be copied

>[!IMPORTANT]
> The delegation examples so far delegate to a single, thread-safe state variable. 
> 
> We can also delegate thread safety to more than one underlying state variable as long as those underlying state variables are independent, meaning that the composite class does not impose any invariants involving the multiple state variables.

#### When Delegation Fails

```java
@NotThreadSafe
public class NumberRange {
    private final AtomicInteger lower = new AtomicInteger(0);
    private final AtomicInteger upper = new AtomicInteger(0);

    public void setLower(int i) {
        if (i > upper.get()) {
            throw new IllegalArgumentException("l < r");
        }
        lower.set(i);
    }

    public void setUpper(int i) {
        if (i < lower.get()) {
            throw new IllegalArgumentException("r > l");
        }
        upper.set(i);
    }

    public boolean inRange(int i) {
        return (i >= lower.get() && i <= upper.get());
    }
}
```

- `NumberRange` is not thread-safe;
- It does not preserve the invariant that constrains `lower` and `upper`. 
- The `setLower` and `setUpper` methods attempt to respect this invariant, but do so poorly.

>[!IMPORTANT]
> If a class is composed of multiple independent thread-safe state variables and has no operations that have any invalid state transitions, then it can delegate thread safety to the underlying state variables.

### Publishing underlying state variables
- Only if a class is thread-safe and doesn't participate in any class invariants can it be published outside its scope.

```java
@ThreadSafe 
public class SafePoint {
    @GuardedBy("this") private int x, y;

    private SafePoint(int[] a) {
        this(a[0], a[1]);
    }

    public SafePoint(SafePoint p) {
        this(p.get());
    }

    public synchronized int[] get() {
        return new int[] {x, y};
    }

    public synchronized void set(int x, int y) {
        this.x = x;
        this.y = y;
    }
}

```

- `SafePoint` provides a getter that retrieves both the `x` and `y` values at once by returning a two-element array. If we provided separate getters for `x` and `y`, then the values could change between the time one coordinate is retrieved and the other, resulting inconsistent state

```java

@ThreadSafe 
public class PublishingVehicleTracker {
    private final Map<String, SafePoint> locations;
    private final Map<String, SafePoint> unmodifiableMap;

    public PublishingVehicleTracker(Map<String, SafePoint> locations) {
        this.location = new ConcurrentHashMap<String, SafePoint>(locations);
        this.unmodifiableMap = Collecitons.unmodifiableMap(this.locations);
    }

    public Map<String, SafPoint> getLocations() {
        return this.unmodifableMap;
    }

    public SafePoint getLocation(String id) {
        return locations.get(id);
    }

    public void setLocation(String id, int x, int y) {
        if (!locations.containsKey(id)) {
            throw new IllegalArgumentException("invalid vehicle id" + id);
        }
        SafePoint p = locations.get(id)
        p.set(x, y);
    }
}

```

<details>
<summary> Java Unmodifiable Map </summary> 

- An unmodifiable map may still change - It is live view on a modifiable map, and changes in the backing map will be visible through the unmodifiable map. 
- The unmodifiable map only prevents modifications for those who only have the reference to the unmodifiable view

- Ref: https://stackoverflow.com/questions/22636575/unmodifiablemap-java-collections-vs-immutablemap-google

```java


Map<String, String> realMap = new HashMap<String, String>();
realMap.put("A", "B");

Map<String, String> unmodifiableMap = Collections.unmodifiableMap(realMap);

// This is not possible: It would throw an 
// UnsupportedOperationException
//unmodifiableMap.put("C", "D");

// This is still possible:
realMap.put("E", "F");

// The change in the "realMap" is now also visible
// in the "unmodifiableMap". So the unmodifiableMap
// has changed after it has been created.
unmodifiableMap.get("E"); // Will return "F". 

```

</details>

- `PublishingVehicleTracker` derives its thread safety from delegation to an underlying `ConcurrentHashMap`, but this time the contents of the Map are thread-safe mutable points rather than immutable ones.
- The `getLocation` method returns an unmodifiable copy of the underlying `Map`. Callers cannot add or remove vehicles, but could change the location of one of the vehicles by mutating the `SafePoint` values in the returned `Map`


### Adding Functionality to Existing Thread-safe Classes

```java

@ThreadSafe
public class BetterVector<E> extends Vector<E>  {
    public synchronized boolean putIfAbsent(E x) {
        boolean absent = !contains(x);
        if (absent) {
            add(x);
        }
        return absent;
    }
}
```

#### Client-side Locking

- Don't do this 
```java
@NotThreadSafe
public class ListHelper<E> {
    public List<E> list = Collections.synchronizedList(new ArrayList<>());

    public synchronized boolean putIfAbsent(E x) {
        boolean absent = !list.contains(x);
        if (absent) {
            list.add(x);
        }
        return absent;
    }
}
```

- Why wouldn't this work? 
  - After all, `putIfAbsent` is `synchronized`, right? 
  - The problem is that it synchronizes on the wrong lock. Whatever lock the `List` uses to guard its state, it sure isn't the lock on the `ListHelper`. 
  - `ListHelper` provides only the illusion of synchronization; the various list operations, while all `synchronized`, use different locks, which means that `putIfAbsent` is not atomic relative to other operations on the `List`
  - It’s like locking someone else’s door and expecting no robbery to happen in my own room.
  - So there is no guarantee that another thread won't modify the list while putIfAbsent is executing.

- After reading documentation 
```java
@ThreadSafe
public class ListHelper<E> {
    public List<E> list = Collections.synchronizedList(new ArrayList<>());

    public boolean putIfAbsent(E x) {
        synchronized(list) {
            boolean absent = !list.contains(x);
            if (absent) {
                list.add(x);
            }
            return absent;
        }
    }
}

```

- A general recommendation - Avoid above wherever possible. Later if policy change for `List` your code will stop working. Refrain your self from writing this kind of code

>[!IMPORTANT]
> Document a class's thread safety guarantees for its clients; document its synchronization policy for its maintainers.
>
> If you don't want to commit to supporting client-side locking, that's fine, but say so



## Chapter 5. Building Blocks

- The last chapter explored several techniques for constructing thread-safe classes, including delegating thread safety to existing thread-safe classes. 
- This chapter covers the most useful concurrent building blocks, especially those introduced in Java 5.0 and Java 6, and some patterns for using them to structure concurrent applications.

### Synchronized Collections
The `synchronized` wrapper classes created by the `Collections.synchronizedXxx` factory methods

#### Problems with Synchronized Collections
- The synchronized collections are thread-safe
  - But you may sometimes need to use additional client-side locking to guard compound actions. 
- Common compound actions on collections include iteration, navigation (finding an element after current), and conditional operations such as `putIfAbsent`  
- With a `synchronized` collection, these compound actions are still technically thread-safe even without client-side locking, but they may not **behave** as you might expect when other threads can concurrently modify the collection.

```java
public static Object getLast(Vector list) {
    int lastIndex = list.size() - 1;
    return list.get(lastIndex);
}

public static Object deleteLast(Vector list) {
    int lastIndex = list.size() - 1;
    list.remove(lastIndex);
}
```

- Two methods that operate on a `Vector`, `getLast` and `deleteLast`, both of which are check-then-act sequences. 

Correct way to do it:

```java
public static Object getLast(Vector list) {
    synchronized (list) {
        int lastIndex = list.size() - 1;
        return list.get(lastIndex);
    }
}

public static void deleteLast(Vector list) {
    synchronized (list) {
        int lastIndex = list.size() - 1;
        list.remove(lastIndex);
    }
}
```

- Traditional iteration could still produce an `ArrayIndexOutOfBounds` exception:

```java
for (int i = 0; i < vector.size(); i++)
    doSomething(vector.get(i));
```

- A way to handle this is to lock the list while iterating over it. This, however, prevents other threads from accessing it:

```java
synchronized (vector) {
    for (int i = 0; i < vector.size(); i++)
        doSomething(vector.get(i));
}
```


#### Iterators and ConcurrentModificationException
- Modern concurrent collections still have the problem with modification during iteration.
- If you iterate a concurrent list & a modification happens meanwhile, you will get a `ConcurrentModificationException`. Iterator follow *fail-fast* meaning that if they detect that the collection has changed since iteration began, they throw the unchecked exception
- The solution here is also to lock the collection while iterating it, but this introduces risks of deadlock.
- An alternative is to clone the collection & iterate the clone. The cloning operation will still need to be locked.

#### Hidden Iterators


```java
public class HiddenIterator {
    @GuardedBy("this")
    private final Set<Integer> set = new HashSet<Integer>();

    public synchronized void add(Integer i) {
        set.add(i);
    }

    public synchronized void remove(Integer i) {
        set.remove(i);
    }

    public void addTenThings() {
        Random r = new Random();
        for (int i = 0; i < 10; ++i) {
            add(r.nextInt());
        }
        System.out.println("DEBUG: " + set); // culprit line.. but why ?
    }
}

```

- Normally we tends to skip the checking the debugging part because we think what can go wrong there. And there we miss the important part
  - Although the real problem is that `HiddenIterator` is not thread-safe; the `HiddenIterator` lock should be acquired before using set in the `println` call, but debugging and logging code commonly neglect to do this.
  - Iteration could also be invoked when invoking the hashCode method, when passing the collection as a constructor to another object, etc.

### Concurrent collections
- The problem with synchronized collections is that throughput suffers due to their excessive synchronization.
- Use `ConcurrentHashMap` instead of a `synchronized` map and `CopyOnWriteArrayList` instead of a synchronized list.
- Additionally, the new `Queue` class is added along with its `BlockingQueue` derivative and `PriorityQueue`.
  - The blocking queue is very useful in producer-consumer designs.

#### ConcurrentHashMap
- This collection uses a sophisticated locking strategy, which improves performance and throughput compared to its synchronized map counterpart.
- It also doesn't throw a `ConcurrentModificationException` upon modification while iterating. Instead, it offers a weakly consistent iterator, which may or may not reflect modifications in the map. The iterators returned by `ConcurrentHashMap` are weakly consistent instead of fail-fast
  - It uses a finer-grained locking mechanism called *lock striping*
  - Arbitrarily many reading threads can access the map concurrently, readers can access the map concurrently with writers, and a limited number of writers can modify the map concurrently.
- Additionally, `size()` and `isEmpty()` are no longer strongly consistent, but are instead approximations.
  - More focus is on put and get

#### Additional Atomic Map Operations

- Since client-side locking is not supported in concurrent maps, commonly used compound actions (such as putIfAbsent) are explicitly implemented:

```java
public interface ConcurrentMap<K, V> extends Map<K, V> {
    // Insert into map only if no value is mapped from K
    V putIfAbsent(K key, V value);
    // Remove only if K is mapped to V
    boolean remove(K key, V value);
    // Replace value only if K is mapped to oldValue
    boolean replace(K key, V oldValue, V newValue);
    // Replace value only if K is mapped to some value
    V replace(K key, V newValue);
}
```

#### CopyOnWriteArrayList

- This is a concurrent replacement to synchronized list, which derives its thread-safety by relying on an effectively immutable object.
- Whenever modification happens in such an array list, the whole list is copied.
- Hence, when iterating such a list, the iterated collection will not change since the time the iterator was created, even if there are concurrent modifications.
- This, of course, has some additional cost due to the underlying copying. This class was designed for use-cases where iteration is more common than modification.


### Blocking Queues & The Producer-Consumer pattern
- Blocking queues support the operation a normal queue does, but they block on take() if the queue is empty and on put() if the queue is full.
- They are useful for implementing producer-consumer designs where there are a number of producers and a number of consumers as it allows producers and consumers to be decoupled from one another.
- The class library offers several implementations of this interface - `LinkedBlockingQueue` and `ArrayBlockingQueue` are standard concurrent FIFO queues. `PriorityBlockingQueue` allows elements to be ordered.
```java

public class FileCrawler implements Runnable {

    public void run() {
        try {
            crawl(root);
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
        }
    }

    private void crawl(File file) throws InterruptedException {
        File[] entries = root.listFiles(fileFilter);
        if (entries != null) {
            for (File entry: entries) {
                if (entry.isDirectory()) {
                    crawl(entry);
                } else if (!alreadyIndexed(entry)) {
                    fileQueue.put(entry);
                }
            }
        }
    }
}

public class Indexer implements Runnable {

    private final BlockingQueue<File> queue;

    public Indexer(BlockingQueue<File> queue) {
        this.queue = queue;
    }

    public void run() {
        try {
            while (true) {
                indexFile(queue.take());
            } catch (InterruptedException e) {
                Thread.currentThread().interrupt();
            }
        }
    }
}


public static void startIndexing(File[] roots) {
    BlockingQueue<File> queue = new LinkedBlockingQueue<File>(BOUND);

    FileFilter filter = new FileFilter() {
        public boolean accept(File file) {
            return true;
        }
    }

    for (File root: roots) {
        new Thread(new FileCrawler(queue, filter, root)).start();
    }

    for (int i = 0; i < N_CONSUMERS; ++i) {
        new Thread(new Indexer(queue)).start();
    }
}
```

#### Serial thread confinement
- This is a technique, used by blocking queues, for transferring non-thread-safe objects in a thread-safe way between producer and consumer threads.
- What this means is that object ownership is confined to one thread.
- What a blocking queue does is it transfers ownership of a given object to a given thread by ensuring safe publication & by not using it anymore or making it available to other threads.
- As long as a thread doesn't use an object anymore after putting it in a queue, transfer will be thread-safe.


#### Deques and work stealing
- Two more classes are added - `Deque` and `BlockingDeque` which extend `Queue` and `BlockingQueue`.
- These are queues, which support taking work from both the tail and the head.
- They are used in a pattern, related to producer-consumer called work stealing.
- In this design, every worker has his own deque he takes work from. But if his deque is exhausted, a worker will "steal" work from the tail of the deque of another worker.
- This is often more scalable than a standard producer-consumer design as workers are working off their own work queue, instead of using a shared one.


### Blocking and interruptible methods


### Synchronizers
- A synchronizer is a class which manages control flow between multiple threads based on its own state. Blocking queues are an example of a synchronizers but there are more.
#### Latches
- A latch is a synchronizer which makes all threads waiting on it block until a given condition is met.
- Example use-cases:
  - A service is dependent on other services starting beforehand
  - A service is waiting on some resource to get initialized

- The most commonly used latch is the `CountDownLatch`. It allows you to enqueue N events you are waiting for to complete before proceeding.

```java

public class TestHarness {
    public long timeTasks(int nThreads, final Runnable task) 
            throws InterruptedException {
        final CountDownLatch startGate = new CountDownLatch(1);
        final CountDownLatch endGate = new CountDownLatch(nThreads);

        for (int i = 0; i < nThreads; ++i) {
            Thread t = new Thread() {
                public void run() {
                    try {
                        startGate.await();
                        try {
                            task.run();
                        } finally {
                            endGate.countDown();
                        }
                    } catch (InterruptedException ignored) {

                    }
                }
            };
            t.start();
        }
        long start = System.nanoTime();
        startGate.countDown();
        endGate.await();
        long end = System.nanoTime();
        return end - start;
    }
}

```


#### FutureTask
- A `FutureTask` is a synchronizer where a thread waits on the completion of a given task & safely receives the result from it.
- This is used when you want to start a lengthy task before you need the result from it & block on receiving the result (if not received already) when you need it.

```java
public class Preloader {
    private final FutureTask<ProductInfo> future = 
        new FutureTask<ProductInfo>(
            new Callable<ProductInfo>() {
                public ProductInfo call() throw DataLoadException {
                    return loadProductInfo();
                }
    });

    private final Thread thread = new Thread(future);

    public void start() {
        thread.start();
    }

    public ProductInfo get() throws DataLoadException, InterruptedException {
        try {
            return future.get();
        } catch (ExecutionException e) {
            Throwable cause = e.getCause();
            if (cause instanceof DataLoadException) {
                throw (DataLoadException) cause;
            } else {
                throw launderThrowable(cause);
            }
        }
    }
}
```

#### Semaphores

- A semaphore allows one to specify the maximum number of simultaneous threads accessing a given resource. 
- The semaphore works by giving out permits which can be returned when they are not used anymore.
- Whenever someone attempts to get a permit, but the maximum allowed permits are already given out, the operation blocks.
- Semaphores can be used to implement resource pools, such as a database connection pool.

```java
public class BoundedHashSet<T> {
    private final Set<T> set;
    private final Semaphore sem;

    public BoundedHashSet(int bound) {
        this.set = Collections.synchronizedSet(new HashSet<T>);
        sem = new Semaphore(bound);
    }

    public boolean add(T o) throws InterruptedException {
        sem.acquire();
        boolean wasAdded = false;
        try {
            wasAdded = set.add(o);
            return wasAdded;
        } finally {
            if (!wasAdded) 
                sem.release();
        }
    }

    public boolean remove(T o) {
        boolean wasRemoved = set.remove(o);
        if (wasRemoved) {
            sem.release();
        }
        return wasRemoved;
    }
}

```

## Chapter 6. Task Execution

From this chapter onwards we'll understand how to structure Concurrent Applications
- Most concurrent applications are organized around the execution of tasks: **abstract**, **discrete units** of work.
- Dividing the work of an application into tasks simplifies program organization, facilitates error recovery by providing natural transaction boundaries, and promotes concurrency by providing a natural structure for parallelizing work.

### Executing Tasks in Threads
- The first step in organizing a program around task execution is identifying sensible *task boundaries*.
- Ideally, tasks are independent activities: work that doesn't depend on the state, result, or side effects of other tasks.
- Independence facilitates concurrency, as independent tasks can be executed in parallel if there are adequate processing resources. 
- Choosing good task boundaries, coupled with a sensible task execution policy 
- Most server application offers a natural choice of task boundary
  - Individual client request
  - Using individual requests as task boundaries usually offers both independence and appropriate task sizing.
  - For example, the result of submitting a message to a mail server is not affected by the other messages being processed at the same time

#### Executing Tasks Sequentially
- The simplest is to execute tasks sequentially in a single thread.
    ```java
    class SingleThreadWebServer {
        public static void main(String[] args) throws IOException {
            ServerSocket socket = new ServerSocket(80);
            while (true) {
                Socket connection = socket.accept();
                handleRequest(connection);
            }
        }
    }
    ```
- `SingleThreadedWebServer` is simple and theoretically correct, but would perform poorly in production because it can handle only one request at a time
  - While the server is handling a request, new connections must wait until it finishes the current request and calls accept again. 
- In server applications, sequential processing rarely provides either good throughput or good responsiveness.

####  Explicitly Creating Threads for Tasks

- A more responsive approach is to create a new thread for servicing each request
    ```java
    class ThreadPerTaskWebServer {
        public static void main(String[] args) throws IOException {
            ServerSocket socket = new ServerSocket(80);
            while (true) {
                final Socket connection = socket.accept();
                Runnable task = new Runnable() {
                    public void run() {
                        handleRequest(connection);
                    }
                }
                new Thread(task).start();
            }
        }
    }
    ```

- The main thread still alternates between accepting an incoming connection and dispatching the request
- The difference is that for each connection, the main loop creates a new thread
- Three main consequences
  - Task processing is offloaded from the main thread, enabling the main loop to resume waiting for the next incoming connection more quickly.
  - Tasks can be processed in parallel, enabling multiple requests to be serviced simultaneously. May improve throughput if there are multiple processors, or if tasks need to block for any reason such as I/O completion, lock acquisition, or resource availability.
  - Task-handling code must be thread-safe, because it may be invoked concurrently for multiple tasks.

#### Disadvantages of Unbounded Thread Creation
- For production use, however, the thread-per-task approach has some practical drawbacks, especially when a large number of threads may be created:
- **Thread lifecycle overhead** Thread creation and teardown are not free. If requests are frequent and lightweight, as in most server applications, creating a new thread for each request can consume significant computing resources.
- **Resource consumption** Active threads consume system resources, especially memory. When there are more runnable threads than available processors, threads sit idle. If you have enough threads to keep all the CPUs busy, creating more threads won't help and may even hurt.
- **Stability** There is a limit on how many threads can be created. The limit varies by platform. When you hit this limit, the most likely result is an `OutOfMemoryError`. Trying to recover from such an error is very risky; it is far easier to structure your program to avoid hitting this limit.


### The Executor Framework
- Tasks are logical units of work, and threads are a mechanism by which tasks can run asynchronously.
- We have seen two approaches in previous section and both suffers
- In previous chapter 5, we've learned about the bounded queues to prevent overload of an application from running out of memory 
- Thread pool offers the same management for the threads
- The Java provides `Executor` framework under (`java.util.concurrent`) which is a flexible implementation for thread pool 
  - So, the primary abstraction for task execution in the Java class libraries are not `Thread`, but `Executor` 

    ```java
    public interface Executor {
        void execute(Runnable command);
    }
    ```
- The interface might looks simple, but it forms the basis of flexibility and powerful framework for asyn task executions
- It helps in decoupling the task submission from task execution, describe task with `Runnable` 
- The `Executor` implementation also provides lifecycle support and hooks for adding statistics gathering, monitoring and much more
- The design of `Executor` is based on producer and consumer
    - Producer: Produce the unit of work to be done
    - Consumer: Threads that execute the task 

    ```java

    class TaskExecutionWebServer {
        private static final int NTHREADS = 100;
        private static final Executor exec = 
                Executor.newFixedThreadPool(NTHREADS);

        public static void main(String[] args) throws IOException {
            ServerSocket socket = new ServerSocket(80);
            whlie (true) {
                final Socket connection = socket.accept();
                Runnable task = new Runnable() {
                    public void run() {
                        handleRequest(connection);
                    }
                }
            }
            exec.execute(task);
        }
    }
    ```

- We can easily modify to behave like thread per task server
    ```java
    public class ThreadPerTaskExecutor implements Executor {
        public void execute(Runnable r) {
            new Thread(r).start();
        }
    }
    ```

#### Execution Policies

The value of decoupling submission from execution is that it lets you easily specify, and subsequently change without great difficulty, the execution policy for a given class of tasks.

- In what thread will tasks be executed?
- How many tasks may execute concurrently?
- In what order should tasks be executed (FIFO, LIFO, priority order)?
- How many tasks may be queued pending execution?
- If a task has to be rejected because the system is overloaded, which task should be selected as the victim, and how should the application be notified?
- What actions should be taken before or after executing a task?



>[!NOTE]
> Execution policies are a resource management tool, and the optimal policy depends on the available computing resources and your quality-of-service requirements. 
>
> Separating the specification of execution policy from task submission makes it practical to select an execution policy at deployment time that is matched to the available hardware.


>[!WARNING]
> Whenever you see code of the form:
>
> `new Thread(runnable).start()`
>
> and you think you might at some point want a more flexible execution policy, seriously consider replacing it with the use of an Executor.

#### Thread Pools
- A thread pool, as its name suggests, manages a homogeneous pool of worker threads. 
- A thread pool is tightly bound to a work queue holding tasks waiting to be executed. Worker threads have a simple life: request the next task from the work queue, execute it, and go back to waiting for another task.
- Executing tasks in pool threads has a number of advantages 
  -  Reusing an existing thread instead of creating a new one amortizes thread creation and teardown costs over multiple requests
  - The latency associated with thread creation does not delay task execution
- You can create a thread pool by calling one of the static factory methods in `Executors`
  - **newFixedThreadPool** A fixed-size thread pool creates threads as tasks are submitted, up to the maximum pool size, and then attempts to keep the pool size constant (adding new threads if a thread dies due to an unexpected `Exception`).
  - **newCachedThreadPool** A cached thread pool has more flexibility to reap idle threads when the current size of the pool exceeds the demand for processing, and to add new threads when demand increases, but places no bounds on the size of the pool.
  - **newSingleThreadExecutor** A single-threaded executor creates a single worker thread to process tasks, replacing it if it dies unexpectedly. Tasks are guaranteed to be processed sequentially according to the order imposed by the task queue (FIFO, LIFO, priority order)
  - **newScheduledThreadPool**  A fixed-size thread pool that supports delayed and periodic task execution, similar to `Timer`.

####  Executor Lifecycle
- JVM can't exit until all the (nondaemon) threads have terminated, so failing to shut down an `Executor` could prevent the JVM from exiting.
- Task can be in any status - Running, Queued, completed
- In shutting down an application, there is a spectrum
  - Graceful shutdown (finish what you've started but don't accept any new work) 
  - Abrupt shutdown (turn off the power to the machine room)
- Since `Executor`s provide a service to applications, they should be able to be shut down as well, both gracefully and abruptly, and feed back information to the application about the status of tasks that were affected by the shutdown.

- To address the issue of execution service lifecycle, the `ExecutorService` interface extends `Executor`
    ```java 
    public interface ExecutorService extends Executor {
        void shutdown();
        List<Runnable> shutdownNow();
        boolean isShutdown();
        boolean isTerminated();
        boolean awaitTermination(long timeout, TimeUnit unit) throws
                InterruptedException;
        //.. and many more
    }
    ```

#### Delayed and Periodic Tasks 
- The `Timer` facility manages the execution of deferred (“run this task in 100 ms”) and periodic (“run this task every 10 ms”) tasks
  - However, `Timer` has some drawbacks, and `ScheduledThreadPoolExecutor` should be thought of as its replacement
- 

