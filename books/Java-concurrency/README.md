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
- Whenever more than one thread accesses a given state variable, and one of them might write to it, they all must coordinate their access to it using synchronization.
- The primary mechanism for synchronization in Java is the `synchronized` keyword, which provides exclusive locking
  - But it also includes - `volatile` variables, explicit locks, and atmoic variable
- If multiple threads access the same mutable state variable without appropriate synchronization, your program is broken. There are three ways to fix it:
  - Don't share the state variable across threads;
  - Make the state variable immutable; or
  - Use synchronization whenever accessing the state variable.
- It is far easier to design a class to be thread-safe than to retrofit it for thread safety later.
- When designing thread-safe classes, good object-oriented techniques—encapsulation, immutability, and clear specification of invariants—are your best friends.

### What is Thread Safety?

>[!NOTE]
> A class is thread-safe if it behaves correctly when accessed from multiple threads, regardless of the scheduling or interleaving of the execution of those threads by the runtime environment, and with no additional synchronization or other coordination on the part of the calling code.

>[!IMPORTANT]
> No set of operations performed sequentially or concurrently on instances of a thread-safe class can cause an instance to be in an invalid state.

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
- The transient state for a particular computation exists solely in local variables that are stored on the thread's stack and are accessible only to the executing thread.
- One thread accessing a StatelessFactorizer cannot influence the result of another thread accessing the same StatelessFactorizer; because the two threads do not share state, it is as if they were accessing different instances.

>[!INFO]
> Stateless objects are always thread-safe.


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
>[!INFO]
> A race condition occurs when the correctness of a computation depends on the relative timing or interleaving of multiple threads by the runtime; in other words, when getting the right answer relies on lucky timing.
>
> The most common type of race condition is *check-then-act*, where a potentially stale observation is used to make a decision

>[!WARNING]
> The term race condition is often confused with the related term data race, which arises when synchronization is not used to coordinate all access to a shared nonfinal field.

#### Example: Race Conditions in Lazy Initialization
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
- Like most concurrency errors, race conditions don't always result in failure: some unlucky timing is also required. But race conditions can cause serious problems.

#### Compound Actions
- Both `LazyInitRace` and `UnsafeCountingFactorizer` contained a sequence of operations that needed to be atomic, or indivisible, relative to other operations on the same state.
- To avoid race conditions, there must be a way to prevent other threads from using a variable while we're in the middle of modifying it, so we can ensure that other threads can observe or modify the state only before we start or after we finish, but not in the middle.
>[!IMPORTANT]
> Operations A and B are atomic with respect to each other if, from the perspective of a thread executing A, when another thread executes B, either all of B has executed or none of it has. An atomic operation is one that is atomic with respect to all operations, including itself, that operate on the same state.

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
- By replacing the `long` counter with an `AtomicLong`, we ensure that all actions that access the counter state are atomic
>[!INFO]
> When a single element of state is added to a stateless class, the resulting class will be thread-safe if the state is entirely managed by a thread-safe object. 

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
- These built-in locks are called intrinsic locks or monitor locks
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
- Reentrancy facilitates encapsulation of locking behavior, and thus simplifies the development of object-oriented concurrent code. 
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

> [!WARNING]
> Without reentrant locks, the very natural-looking code, in which a subclass overrides a synchronized method and then calls the superclass method, would deadlock. Because the doSomething methods in Widget and LoggingWidget are both synchronized, each tries to acquire the lock on the Widget before proceeding. 
> 
> But if intrinsic locks were not reentrant, the call to super.doSomething would never be able to acquire the lock because it would be considered already held, and the thread would permanently stall waiting for a lock it can never acquire. Reentrancy saves us from deadlock in situations like this.

### Guarding State with Locks

- Locks enables serialized access to the code path they guard
- Compound actions on shared state, such as incrementing a hit counter or lazy init, must be atomic to avoid *race conditions*
- It is a common mistake to assume that synchronization needs to be used only when writing to shared variables; this is simply not true.  (will discuss later)
- For each mutable state variable that may be accessed by more than one thread, all accesses to that variable must be performed with the same lock held. In this case, we say that the variable is guarded by that lock.
- Every shared, mutable variable should be guarded by exactly one lock. Make it clear to maintainers which lock that is.

>[!IMPORTANT]
> Each object in Java has built-in intrinsic lock 
> 
> The fact that every object has a built-in lock is just a convenience so that you needn't explicitly create lock objects. 

- When a variable is guarded by a lock—meaning that every access to that variable is performed with that lock held—you've ensured that only one thread at a time can access that variable. 
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
- While synchronized methods can make individual operations atomic, additional locking is requiredwhen multiple operations are combined into a compound action.
- 
### Liveness and Performance




