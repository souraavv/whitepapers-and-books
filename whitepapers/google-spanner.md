- [Spanner: Google's Globally-Distributed Database](#spanner-googles-globally-distributed-database)
    - [Pre-req for this whitepaper](#pre-req-for-this-whitepaper)
    - [Goals](#goals)
    - [Configurable Parameters](#configurable-parameters)
    - [Customers](#customers)
    - [Challenges](#challenges)
    - [Gains for Applications](#gains-for-applications)
  - [Serializability versus Linearizability](#serializability-versus-linearizability)
    - [Serializability is the "I", or isolation, in the ACID](#serializability-is-the-i-or-isolation-in-the-acid)
    - [Linearizability is the "AC", or Atomicity Consistency, in the ACID](#linearizability-is-the-ac-or-atomicity-consistency-in-the-acid)
  - [Strict Serializability: Why don’t we have both?](#strict-serializability-why-dont-we-have-both)
  - [Two Phase Commit](#two-phase-commit)
  - [Coordination costs and real-world deployments](#coordination-costs-and-real-world-deployments)
  - [Implementation](#implementation)
  - [Concurrency Control](#concurrency-control)
  - [References](#references)


# Spanner: Google's Globally-Distributed Database


### Pre-req for this whitepaper 
- [Paxos](https://lamport.azurewebsites.net/pubs/paxos-simple.pdf)/[RAFT](https://github.com/souraavv/whitepapers-and-books/blob/main/whitepapers/raft.md) (must)
- [CAP Theorem](https://groups.csail.mit.edu/tds/papers/Gilbert/Brewer2.pdf) (must)
- [Linearizability and Serializability](http://www.bailis.org/blog/linearizability-versus-serializability/)(must)
- Map Reduce, BigTable, MegaStore (optional) 

### Goals
- Extremely consistent distributed transactions
- High Availability (survive wide-area natural disasters)
- Lock free read-only(RO) transactions 
- Atomic Schema change
- Scalable, Multi-version, Globally distributed, and synchronously-replicated database (fine grain by application)
- Automatic Re-shards data across machines as the amount of data or server changes (even across data centers)
- Automatically migrate database across machines (specially cross data center)

### Configurable Parameters
- Can Specify constrains to control which data center contain which data
- How far data is from its user (to control read latency)
- How far are replica from each other (control write latency)
- How may replicas are maintained (to control durability, availability & read performance)

### Customers 
- Google's Advertisement Backend

### Challenges
- Building a scalable distributive database with consistency is difficult to achieve
  - You can, but the cost you pay is the throughput
- Availability comes from replication, and replication cost the consistency
  
This papers tries to achieve 
- **Externally consistent** - Read/Write in a Distributive Database
  - External Consistency (or Strict Serializability)
    - Why named External ? - 
      - Highlights that the correctness of the system is judged based on how external observers perceive the ordering of operations.
    - [Question to reader] Why External Consistency matters ? Or to be precise in which set of system External consistency matters ? 
- **Globally consistent** - Read across the database at a time-stamp.

### Gains for Applications

All at the global scale, and even in the presence of ongoing transaction.

- Consistent backups
- Consistent MapReduce Executions
- Atomic Schema Updates

## Serializability versus Linearizability

- When can one say two Transaction are isolated to each other ? 
  - $`[T1(start), ... T1(end),.., T2(start), ... T2(end)]`$ or
  - $`[T2(start), ... T2(end),.., T1(start), ... T1(end)]`$
  - In the above two cases no partial writes are visible from either of the txn. This means if we do serial execution then we can always guarantee that two txns are isolated and consistent (if application writer is maintaining consistency)
  - Although in the real world we can't perform operations serially always. Reason - Multi-Cores are not getting utilize property and even for a single core system in case if a txn is busy with I/O we are under utilizing the CPU cycles.
  - So for throughput we will always have interleaving of operations, which brings us to the question - How we can ensure Isolation and Consistency when operations are interleaved.
    - One thing if you notice - context switches are not in our control and if txns are running concurrently then there is no way for us to determine deterministically which operation will happen when (In general, ordering can't be guaranteed)
    - This bring us to a point such that our definition of Isolation should be independent of real-time constraints on the ordering of txns. 
    - If any interleaved order produced same result as one of the T1T2 or T2T1 then we can say the order of execution was "Serializable"

### Serializability is the "I", or isolation, in the ACID
- Multi-operation, multi-object, arbitrary total order
- Serializability is a guarantee about transactions, or groups of one or more operations over one or more objects. It guarantees that the execution of a set of transactions (usually containing read and write operations) over multiple items is equivalent to some serial execution (total ordering) of the transactions.
- Serializability is the traditional “I,” or isolation, in ACID. If users’ transactions each preserve application correctness (“C,” or consistency, in ACID), a serializable execution also preserves correctness. Therefore, serializability is a mechanism for guaranteeing database correctness.
- Serializability is also not composable (Two serializable systems combined aren't guaranteed to remain serializable.)
- Serializability does not imply any kind of deterministic order—it simply requires that some equivalent serial execution exists.

### Linearizability is the "AC", or Atomicity Consistency, in the ACID
- Linearizability is a guarantee about single operations on single objects. It provides a real-time (i.e., wall-clock) guarantee on the behavior of a set of single operations (often reads and writes) on a single object (e.g., distributed register or data item).
- In plain English, under linearizability, writes should appear to be instantaneous. Imprecisely, once a write completes, all later reads (where “later” is defined by wall-clock start time) should return the value of that write or the value of a later write. Once a read returns a particular value, all later reads should return that value or the value of a later write.
- We say linearizability is composable (or “local”) because, if operations on each object in a system are linearizable, then all operations in the system are linearizable.


## Strict Serializability: Why don’t we have both?

- Combining serializability and linearizability yields strict serializability: transaction behavior is equivalent to some serial execution, and the serial order corresponds to real time. For example, say I begin and commit transaction T1, which writes to item x, and you later begin and commit transaction T2, which reads from x. A database providing strict serializability for these transactions will place T1 before T2 in the serial ordering, and T2 will read T1’s write. A database providing serializability (but not strict serializability) could order T2 before T1
- linearizability can be viewed as a special case of strict serializability where transactions are restricted to consist of a single operation applied to a single object

Reference: [Peter Bailis Notes - MIT](http://www.bailis.org/blog/linearizability-versus-serializability/)

## Two Phase Commit 

- In two-phase commits, RW transactions are executed in two phases. Transaction coordinator (TC) asks all shards to return all relevant values and prepare to write by taking the write locks. The values are sent back to the client. The client sends back the new values to write. TC asks all shards to commit the values and release all locks.

Read more at [COL-733 IIT Delhi - Prof. Abhliash Notes](https://github.com/codenet/col733-cloud/blob/main/storage-spanner.md#:~:text=on%20multiple%20machines.-,Two%2Dphase%20commit,-In%20two%2Dphase)

## Coordination costs and real-world deployments
- Neither linearizability nor serializability is achievable without coordination. That is we can’t provide either guarantee with availability (i.e., CAP “AP”) under an asynchronous network


## Implementation

- Following mapping is maintained `(key: string, timestamp: int64) -> String`
  - Timestamp enables the multi-version database than a key-value store
  - The entity which stores these is called as "tablet"
- To support replication, single Paxos state machine on top of each tablet (allows more fine-grained replication)
  - Writes must initiate the Paxos protocol at the leader; 
  - Reads access state directly from the underlying tablet at any replica that is sufficiently up-to-date (will define up-to-date later)
- Each state machine stores its metadata and log in its corresponding tablet
- Lock tables - A leader maintain the lock table
  - Lock table is for the Concurrency Control
  - Table contains the state for two-phase locking; it maps ranges of keys to lock state
- Design choice - Long live leaders with time-based leader lease
  - Why ? Efficiently maintain the lock table 
- Optimistic vs Pessimistic Concurrency Control
  - Optimistic Concurrency Control
    - OCC assumes most transaction do not conflict with each other. Transaction setup watch for different variables. If any variable changes before transaction could commit, the transaction is aborted
    - Performance degrades as more long-live transactions
  - Pessimistic Concurrency Control 
    - PCC assumes most transactions conflict with each other, so they upfront lock variables. If transactions were not conflicting, we unnecessarily pay the locking overhead.
    - Chances of deadlocks with multiple ongoing transactions
    - 
- Each leader also implements a *transaction manager* to support distributed transactions
  - The transaction manager is used to implement a *participant leader*, the other replicas in the group will be referred to as *participant slaves*.
  - Transaction manager is only required when a transaction involves more than one Paxos group, those groups leaders coordinate to perform two-phase commit
    - Two-phase commit generates Paxos write for the prepare phase that has no corresponding Spanner client write
  - One of the participant group is chosen as **coordinator**; the participant leader of that group is called as **coordinator leader**, and the slaves of that group as **coordinator slaves**
  - The state of each transaction manager is stored in the underlying Paxos group (and therefore is replicated) 
- TrueTime
    | Method | Returns | 
    | -- | -- |
    | TT.now() | TTinterval: [earliest, latest] |
    | TT.after(t) | true if t has definitely passed | 
    | TT.before(t) | true if t has definitely not arrived |
  - Note that time uncertainity is bounded (so notion of uncertainity is captured)
    - We will see the power of this concept later. 
  - Lets define ϵ : Instantenous error bounds and ϵ' as average error bound 
  - Let $` t_{abs}(e) `$ the absolute time of an event $`e`$, In more formal TrueTime guarantees that for an invocation $`tt = TT.now(); tt.earliest \leq t_{abs}(e_{now}) \leq tt.latest `$, where $`e_{now}`$ is the invocation event
  - Underlying reference for TrueTime are GPS and Atomic Clocks 

    | Operation | Concurrency Control | Replica Required | 
    | --- | --- | --- | 
    | Read-Write Transaction | Pessimistic | Leader | 
    | Read-Only Transaction | lock-free | leader for timestamp; any for read |
    | Snapshot Read, client-provided timestamp | lock-free | any | 
    | Snapshot Read, Client-provided bound | lock-free | any | 

## Concurrency Control 

In this section - How TrueTime is used to guarantee the correctness properties around concurrency control, and how those properties are used to implement features such as *external consistent transaction*, *lock-free* read-only transaction, and *non-blocking* reads in the past. This feature allow to audit the database at a timestamp *t* will see exactly the effects of every transaction that has commited as of *t*.

### Paxos Leader Leases
### Assigning TimeStamps to RW Transactions 
### Serving Reads at a Timestamp
### Assigning Timestamps to RO Transactions



## References

- [Linearizability versus Serializability: Peter Bailis Notes - MIT](http://www.bailis.org/blog/linearizability-versus-serializability/)
- [When is "ACID" ACID? rarely](http://www.bailis.org/blog/when-is-acid-acid-rarely/)
- [Weak vs Strong Memory Models](https://preshing.com/20120930/weak-vs-strong-memory-models/)
- [COL-733 IIT Delhi Notes - Prof. Abhilash](https://github.com/codenet/col733-cloud/blob/main/storage-spanner.md)

