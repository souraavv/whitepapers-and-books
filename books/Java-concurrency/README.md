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

>[!NOTE]
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
>[!NOTE]
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
>[!NOTE]
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

### Liveness and Performance
- Using `synchronized` block at the function method can hurt the liveness and performance
- Operations that do not impact the shared state and consume a lot of CPU cycles can be optimized by using fine-grained control over the synchronized block.
- At the same time, we don’t want a synchronization block to be so small that it breaks the isolation of the shared state.

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
> We want not only to prevent one thread from modifying the state of an object when another is using it, but also to ensure that when a thread modifies the state of an object, other threads can actually see the changes that were made

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

#### Stale Data
- Last example shows insufficiently synchronized programs can cause surprising results: *stale data*
- Stale data can cause serious and confusing failures such as unexpected exceptions, corrupted data structures, inaccurate computations, and infinite loops.
- Reading data without synchronization is analogous to using the `READ_UNCOMMITTED` isolation level in a database, where you are willing to trade accuracy for performance.
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
- When a thread reads a variable without synchronization, it may see a stale value, but at least it sees a value that was actually placed there by some thread rather than some random value. 
- This safety guarantee is called *out-of-thin-air* safety.
- Out-of-thin-air safety applies to all variables, with one exception: 64-bit numeric variables (`double` and `long`) that are not declared volatile
>[!WARNING]
> The Java Memory Model requires fetch and store operations to be atomic, but for nonvolatile long and double variables, the JVM is permitted to treat a 64-bit read or write as two separate 32-bit operations. If the reads and writes occur in different threads, it is therefore possible to read a nonvolatile long and get back the high 32 bits of one value and the low 32 bits of another.
>
> When the Java Virtual Machine Specification was written, many widely used processor architectures could not efficiently provide atomic 64-bit arithmetic operations.

#### Locking and Visibility

>[!IMPORTANT]
> We can now give the other reason for the rule requiring all threads to synchronize on the same lock when accessing a shared mutable variable—to guarantee that values written by one thread are made visible to other threads. Otherwise, if a thread reads a variable without holding the appropriate lock, it might see a stale value.
>
> Locking is not just about mutual exclusion; it is also about **memory visibility**. To ensure that all threads see the most up-to-date values of shared mutable variables, the reading and writing threads must synchronize on a common lock.

#### Volatile Variables
- The Java language also provides an alternative, weaker form of synchronization, *volatile variables*, to ensure that updates to a variable are propagated predictably to other threads.
  
>[!NOTE]
>  When a field is declared `volatile`, the compiler and runtime are put on notice that this variable is shared and that operations on it should not be reordered with other memory operations
>
> Volatile variables are not cached in registers or in caches where they are hidden from other processors, so a read of a volatile variable always returns the most recent write by any thread.

- Yet accessing a `volatile` variable performs no locking and so cannot cause the executing thread to block, making `volatile` variables a lighter-weight synchronization mechanism than `synchronized`

>[!WARNING]
> Use volatile variables only when they simplify implementing and verifying your synchronization policy; avoid using volatile variables when veryfing correctness would require subtle reasoning about visibility. Good uses of volatile variables include ensuring the visibility of their own state, that of the object they refer to, or indicating that an important lifecycle event (such as initialization or shutdown) has occurred.

- Volatile variables are convenient, but they have limitations
- The semantics of volatile are not strong enough to make the increment operation (`count++`) atomic, unless you can guarantee that the variable is written only from a single thread.
- Atomic variables do provide atomic *read-modify-write* support and can often be used as **“better volatile variables”**

>[!IMPORTANT]
> Locking can guarantee both visibility and atomicity; volatile variables can only guarantee visibility.

- You can use volatile variables only when all the following criteria are met:
  - Writes to the variable do not depend on its current value, or you can ensure that only a single thread ever updates the value;
  - The variable does not participate in invariants with other state variables; and
  - Locking is not required for any other reason while the variable is being accessed.

### Publication and Escape
- Publishing an object means making it available to code outside of its current scope, such as by storing a reference to it where other code can find it, returning it from a nonprivate method, or passing it to a method in another class.
- In many situations, we want to ensure that objects and their internals are not published. 
  - In other situations, we do want to publish an object for general use, but doing so in a thread-safe manner may require synchronization. 
- Publishing internal state variables can compromise encapsulation and make it more difficult to preserve invariants;
- Publishing objects before they are fully constructed can compromise thread safety. 
- An object that is published when it should not have been is said to have *escaped*.
- The most blatant form of publication is to store a reference in a public static field, where any class and thread could see it
    ```java
    public static Set<Secret> knownSecrets;
    
    public void initialize() {
        knownSecrets = new HashSet<Secret>();
    }
    ```
- Publishing one object may indirectly publish others. If you add a `Secret` to the published `knownSecrets` set, you've also published that `Secret`, because any code can iterate the `Set` and obtain a reference to the new `Secret`.
- Similarly, returning a reference from a nonprivate method also publishes the returned object. 
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
- `UnsafeStates` publishes the supposedly `private` array of state abbreviations.
- Publishing states in this way is problematic because any caller can modify its contents.
- In this case, the states array has escaped its intended scope, because what was supposed to be private state has been effectively made public.
- Publishing an object also publishes any objects referred to by its nonprivate fields. Or more general this can be a long chain
-  Implicitly Allowing the `this` Reference to Escape. Don't do this.
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
    - When `ThisEscape` publishes the `EventListener`, it implicitly publishes the enclosing `ThisEscape` instance as well, because inner class instances contain a hidden reference to the enclosing instance.
    - `ThisEscape` instance. But an object is in a predictable, consistent state only after its constructor returns, so publishing an object from within its constructor can publish an incompletely constructed object. 
    - This is true even if the publication is the last statement in the constructor. If the `this` reference escapes during construction, the object is considered not properly constructed.
  - Do not allow the this reference to escape during construction.
  - A common mistake that can let the this reference escape during construction is to start a thread from a constructor. 
  - When an object creates a thread from its constructor, it almost always shares its this reference with the new thread, either explicitly (by passing it to the constructor) or implicitly (because the `Thread` or `Runnable` is an inner class of the owning object).
   - The new thread might then be able to see the owning object before it is fully constructed. There's nothing wrong with creating a thread in a constructor, but it is best not to start the thread immediately.
- If you are tempted to register an event listener or start a thread from a constructor, you can avoid the improper construction by using a private constructor and a public factory method, as shown in `SafeListener`
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

>[!NOTE]
> Accessing shared, mutable data requires using synchronization; one way to avoid this requirement is to not share. 
> 
> If data is only accessed from a single thread, no synchronization is needed. This technique, **thread confinement**
>
>  This technique, thread confinement, is one of the simplest ways to achieve thread safety. When an object is confined to a thread, such usage is automatically thread-safe even if the confined object itself is not 

- Thread confinement is commonly used in pooled JDBC `Connection` objects, as they are not thread-safe. A thread acquires a connection from the pool, processes a request synchronously, and returns it. The pool ensures the connection isn't shared with other threads during its usage, maintaining confinement.
  - The connection pool implementations provided by application servers are thread-safe; connection pools are necessarily accessed from multiple threads, so a non-thread-safe implementation would not make sense.

#### Stack Confinement
- Local variables are intrinsically confined to the executing thread;
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

        if (factor == null) {
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
</detials>


### Summary
- The most useful policies for using and sharing objects in a concurrent program are:
- **Thread-confined**. A thread-confined object is owned exclusively by and confined to one thread, and can be modifled by its owning thread.
- **Shared read-only**. A shared read-only object can be accessed concurrently by multiple threads without additional synchronization, but cannot be modified by any thread. Shared read-only objects include immutable and effectively immutable objects.
- **Shared thread-safe**. A thread-safe object performs synchronization internally, so multiple threads can freely access it through its public interface without further synchronization.
- **Guarded**. A guarded object can be accessed only with a specific lock held. Guarded objects include those that are encapsulated within other thread-safe objects and published objects that are known to be guarded by a specific lock.
