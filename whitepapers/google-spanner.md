- [Spanner: Google's Globally-Distributed Database](#spanner-googles-globally-distributed-database)
    - [Pre-req for this whitepaper](#pre-req-for-this-whitepaper)
    - [Goals](#goals)
    - [Configurable Parameters](#configurable-parameters)
    - [Open Source Implementation](#open-source-implementation)
    - [What was the motivating use case?](#what-was-the-motivating-use-case)
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
    - [Paxos Leader Leases](#paxos-leader-leases)
    - [Assigning TimeStamps to RW Transactions](#assigning-timestamps-to-rw-transactions)
    - [Serving Reads at a Timestamp](#serving-reads-at-a-timestamp)
    - [Assigning Timestamps to RO Transactions](#assigning-timestamps-to-ro-transactions)
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

### Open Source Implementation 
- CockroachDB

### What was the motivating use case?
- Google F1 advertising database
- Previously sharded over many MySQL and BigTable DBs;
- Needed:
  - Better (synchronous) replication.
  - More flexible sharding.
  - Cross-shard transactions.
- Workload is dominated by read-only transactions 
- Strong consistency is required.
  - External consistency / linearizability / serializability.

Reference: [MIT 6.5840 2023 Spanner Notes](http://nil.csail.mit.edu/6.5840/2023/notes/l-spanner.txt)

### Challenges
- Building a scalable distributive database with consistency is difficult to achieve
  - You can, but the cost you pay is the throughput
- Availability comes from replication, and replication cost the consistency
  
This paper tries to achieve

- **Externally consistent** - Read/Write in a Distributive Database
  - External Consistency (or Strict Serializability)
    - Why named External ?
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
  - In both of the above cases, no partial writes are visible from either of the transactions. This means that with serial execution, we can always guarantee that the two transactions are isolated and consistent (assuming the application writer maintains consistency).
  - In the real world, we can't always perform operations serially. The reason is that multi-core processors are not utilized efficiently, and even in single-core systems, if a transaction is busy with I/O, the CPU cycles are underutilized.
  - For throughput, we will always have interleaving of operations, which brings us to the question: How can we ensure isolation and consistency when operations are interleaved?
    - One thing to note is that context switches are not under our control, and when transactions are running concurrently, there’s no way to deterministically determine which operation will occur when. In general, the ordering cannot be guaranteed.
    - This brings us to the point that our definition of isolation should be independent of real-time constraints on the ordering of transactions.
    - If any interleaved order produced same result as one of the $`T1T2`$ or $`T2T1`$ then we can say the order of execution was "Serializable"

### Serializability is the "I", or isolation, in the ACID
- Multi-operation, multi-object, arbitrary total order
- Serializability is a guarantee about transactions, or groups of one or more operations over one or more objects. It guarantees that the execution of a set of transactions (usually containing read and write operations) over multiple items is equivalent to some serial execution (total ordering) of the transactions.
- Serializability is the traditional “I,” or isolation, in *ACID*. If users’ transactions each preserve application correctness (“C,” or consistency, in ACID), a serializable execution also preserves correctness. Therefore, serializability is a mechanism for guaranteeing database correctness.
- Serializability is also not composable (Two serializable systems combined aren't guaranteed to remain serializable.)
- Serializability does not imply any kind of deterministic order—it simply requires that some equivalent serial execution exists.

### Linearizability is the "AC", or Atomicity Consistency, in the ACID
- Linearizability is a guarantee about single operations on single objects. It provides a real-time (i.e., wall-clock) guarantee on the behavior of a set of single operations (often reads and writes) on a single object (e.g., distributed register or data item).
- In plain English, under linearizability, writes should appear to be instantaneous. Imprecisely, once a write completes, all later reads (where “later” is defined by wall-clock start time) should return the value of that write or the value of a later write. Once a read returns a particular value, all later reads should return that value or the value of a later write.
- We say linearizability is composable (or “local”) because, if operations on each object in a system are linearizable, then all operations in the system are linearizable.


## Strict Serializability: Why don’t we have both?

- Combining serializability and linearizability yields strict serializability: transaction behavior is equivalent to some serial execution, and the serial order corresponds to real time. For example, say I begin and commit transaction $`T1`$, which writes to item $`x`$, and you later begin and commit transaction $`T2`$, which reads from $`x`$. A database providing strict serializability for these transactions will place $`T1`$ before $`T2`$ in the serial ordering, and $`T2`$ will read $`T1`$’s write. A database providing serializability (but not strict serializability) could order $`T2`$ before $`T1$
- linearizability can be viewed as a special case of strict serializability where transactions are restricted to consist of a single operation applied to a single object

Reference: [Peter Bailis Notes - MIT](http://www.bailis.org/blog/linearizability-versus-serializability/)

## Two Phase Commit 

- In two-phase commits, RW transactions are executed in two phases. Transaction coordinator (TC) asks all shards to return all relevant values and prepare to write by taking the write locks. The values are sent back to the client. The client sends back the new values to write. TC asks all shards to commit the values and release all locks.

Read more at [COL-733 IIT Delhi - Prof. Abhliash Notes](https://github.com/codenet/col733-cloud/blob/main/storage-spanner.md#:~:text=on%20multiple%20machines.-,Two%2Dphase%20commit,-In%20two%2Dphase)

## Coordination costs and real-world deployments
- Neither linearizability nor serializability is achievable without coordination. That is we can’t provide either guarantee with availability (i.e., CAP “AP”) under an asynchronous network


## Implementation

- The following mapping is maintained $`(key: string, timestamp: int64) -> String`$
  - Timestamp enables the multi-version database than a key-value store
  - The entity which stores these is called as **tablet**
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
    | $`TT.now()`$ | TTinterval: $`[earliest, latest]`$ |
    | $`TT.after(t)`$ | true if $`t`$ has definitely passed | 
    | $`TT.before(t)`$ | true if $`t`$ has definitely not arrived |
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

In this section - How TrueTime is used to guarantee the correctness properties around concurrency control, and how those properties are used to implement features such as **external consistent transaction**, **lock-free read-only** transaction, and **non-blocking reads** in the past. This feature allow to audit the database at a timestamp $`t`$ will see exactly the effects of every transaction that has commited as of $`t`$.

### Paxos Leader Leases
- Spanner Paxos implementation uses timed leases to make leadership long-lived (10 seconds by default)
- A potential leader sends requests for timed lease votes; upon receiving a quorum of lease votes the leader knows it has a lease.
- A replica extends its lease vote implicitly on a successful write, and the leader requests lease-vote extensions if they are near expiration
- Define a leader's *lease interval* as starting when it discovers it has a quorum of lease votes, and as ending when it no longer has a quorum of lease votes (because some have expired).
- Spanner depends on following **Disjointness Invariant**: For each Paxos group, each Paxox leader's lease interval is disjoint from every other leaders's. (Will discuss later how this invariant is enforced)
- Define $`s_{max}`$ to be the maximum timestamp used by a leader. Later we will see how $`s_{max}`$ is advanced. 
- Spanner implementation permits a Paxos leader to abdicate by releasing its slaves from their lease votes. To ensure that disjointness invariant still holds, Spanner puts constraint when abdication is permissible. Before abdicating, a leader must wait $`TT.after(s_{max})`$ is $`true`$.

### Assigning TimeStamps to RW Transactions 
- Transaction reads and writes use **two-phase locking**
- Each transaction can be assigned timestamps at any time when all locks have been acquired, but before any locks have been released
- Spanner assigns it the timestamp that Paxos assigns to the Paxos write that represents the transaction commit.
- Spanner depends on the following **monotonicity invariant** within each Paxos group
  - Spanner assigns timestamps to Paxos write in monotonically increasing (strictly increasing), even across leaders.
  - A single leader replica can trivially assign timestamps in monotoincally increasing order. 
  - This invariant is enforced across leaders by making use of **disjointness invariant** 
  - A leader must only assign timestamps within the interval of its leader lease.
  - Note that whenever a timestamp $`s`$ is assigned, $`s_{max}`$ is advanced to $`s`$ to preserve disjointness
- Remember Spanner also enforces the following **external consistency invariant**
  - If the start of transaction $`T_{2}`$ occurs after the commit of a transaction $`T_{1}`$, then the commit timestamp of $`T_{2}`$ must be greater than the commit timestamp of $`T_{1}`$.
- Define the start and commit events of a txn $`T_{i}`$ by $`e_{i}^{start}`$ and $`e_{i}^{commit}`$; and the commit timestamp of a txn $`T_{i}`$ by $`s_{i}`$
  - The invariant becomes $`t_{abs}(e_{1}^{commit}) \lt t_{abs}(e_{2}^{start}) \implies s_{1} \lt s_{2}`$
- The protocol for executing txns and assigning timestamps obey two rules, which together guarantee this invariant.
- Define the arrival event of a commmit request at the coordinator leader for a write $`T_{i}`$ to be $`e_{i}^{server}`$
- **Start**
  - The coordinator leader for a write $`T_{i}`$ assigns a commit timestmap $`s_{i}`$ no less than the value of $`TT.now().latest`$, computed after $`e_{i}^{server}`$
- **Commit Wait**
  - The coordinator leader ensures that clients cannot see any data committed by $`T_{i}`$ until $`TT.after(s_{i})`$ is $`true`$ 
  - Commit wait ensures that $`s_{i}`$ is less than absolute commit time of $`T_{i}`$, or $`s_{i} \lt t_{abs}(e_{i}^{commit})`$

$$
\begin{split}
s_{1} &< t_{abs}(e_{1}^{commit}) \quad (\text{commit wait}) \\
t_{abs}(e_{1}^{commit}) &< t_{abs}(e_{2}^{start}) \quad (\text{assumption}) \\
t_{abs}(e_{2}^{start}) &\leq t_{abs}(e_{2}^{server}) \quad (\text{causality}) \\
t_{abs}(e_{2}^{server}) &\leq s_{2} \quad (\text{start}) \\
s_{1} &< s_{2} \quad (\text{transitivity}) \\
\end{split}
$$


### Serving Reads at a Timestamp
- Every replica tracks a value called *safe time* $`t_{safe}`$ which is the maximum timestamp at which a replica is up-to-date.
- A replica can satisfy a read at a timestamp $`t`$ if $`t \leq t_{safe}`$
- Define $`t_{safe} = min(t_{safe}^{Paxos}, t_{safe}^{TM})`$, where each Paxos state machine has a safe time $`t_{safe}^{Paxos}`$ and each transactino manager (TM) has a safe time $`t_{safe}^{TM}`$
-  $`t_{safe}^{Paxos}`$ is simpler: it is the timestamp of the highest-applied Paxos write. Because timestamps increase monotonically and writes are applied in order, writes will no longer occur at or below  $`t_{safe}^{Paxos}`$ with respect to Paxos.
- $`t_{safe}^{TM}`$ is $`\infty`$ at a replica if there are zero prepared (but not committed) transactions - that is, txn in between the two phases of two-phase commit
  - For participant slave, $`t_{safe}^{TM}`$ actually refers to the replica's leader's TM
  - 
### Assigning Timestamps to RO Transactions
- A read-only txn executes in two phases: assign a timestamp $`s_{read}`$, and then execute the txns read as snapshot read at $`s_{read}`$. 
- The snapshot read can execute at any replicas that are sufficiently up-to-date.
- $`s_{read} = TT.now().latest`$ , at any time after a txn start, preserving external consistency by an argument analogous to described in section (Assigning Timestamps to RW Transactions) 



## References

- [Google Spanner Whitepaper](http://nil.csail.mit.edu/6.5840/2023/papers/spanner.pdf)
- [Linearizability versus Serializability: Peter Bailis Notes - MIT](http://www.bailis.org/blog/linearizability-versus-serializability/)
- [When is "ACID" ACID? rarely](http://www.bailis.org/blog/when-is-acid-acid-rarely/)
- [Weak vs Strong Memory Models](https://preshing.com/20120930/weak-vs-strong-memory-models/)
- [COL-733 IIT D Notes - Prof. Abhilash](https://github.com/codenet/col733-cloud/blob/main/storage-spanner.md)
- [Testing Distributed System for Linearizability](https://anishathalye.com/testing-distributed-systems-for-linearizability/)
- [MIT 6.5840 2023 Lecture 9. Consistency, Linearizability](http://nil.csail.mit.edu/6.5840/2023/notes/l-linearizability.txt)
- [MIT 6.5840 2023 Spanner Notes](http://nil.csail.mit.edu/6.5840/2023/notes/l-spanner.txt) Art of writing notes
- [MIT 6.5840 2023 Spanner FAQ](http://nil.csail.mit.edu/6.5840/2023/papers/spanner-faq.txt)
- [MIT 6.5840 FaRM, Optimstic Concurrency Control](http://nil.csail.mit.edu/6.5840/2023/notes/l-farm.txt)
