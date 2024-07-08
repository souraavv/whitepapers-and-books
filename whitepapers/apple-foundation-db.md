- [FoundationDB: A distributed Key-Value Store](#foundationdb-a-distributed-key-value-store)
  - [Abstract](#abstract)
    - [Hey FoundationDB, Introduce yourself](#hey-foundationdb-introduce-yourself)
    - [Why should we read this paper ?](#why-should-we-read-this-paper-)
  - [Introduction](#introduction)
  - [Contribution of this paper](#contribution-of-this-paper)
  - [Design](#design)
    - [Design Principle](#design-principle)
    - [System Interface](#system-interface)
    - [Architecture](#architecture)

# FoundationDB: A distributed Key-Value Store
Author: J Zhou, Published @ SIGMOD'21
[Paper link](https://www.foundationdb.org/files/fdb-paper.pdf)

## Abstract
### Hey FoundationDB, Introduce yourself
- I was born and brought up at Apple 
- I'm transactional key-value store and offers consistency, robustness and availability for storing user data, system metadata and configuration
- I'm one of the first system which combines 
  -  flexibility & scalability from NoSQL
  -  ACID power from SQL 
- I'm the underpinning(आधार/नींव) of cloud Infra @Apple, @Snowflake
  
### Why should we read this paper ? 
- FDB adopts an unbundled architecture that decouples 
  - In-memory transactional management system
  - Distributed storage system
  - Built-in distributed configuration system 
- Each sub-system can be independently provision and configured to achieve
  - Scalability
  - High-availability
  - Fault tolerant property 
- Integrates a deterministic simulation framework
  - Used to test every new features
  - Rigorous testing makes FoundationDB extremely stable
- Offers minimal and carefully chosen feature set
  - This has enabled a range of disparate system (विभिन्न प्रणालियाँ) from semi-relational database, document and object store

## Introduction
- Cloud services relies on scalable, distributed storage backend for persisting application state
- Such storage system must be 
  - fault tolerant,
  - highly scalable (scale to billions of user, petabyte or exabyte of data, and million of requests per second)
- Tradeoff b/w Relation model vs NoSQL (Document model)
  - Both are extreme; One worry about transactions nature and other sacrifices it.
  - FDB is try to balance and avoid this tradeoff
    - By providing serializable transactions 
    - More advanced features like - consistent secondary indices and referential integrity check
- Unlike most database where they bundle storage engine, data model and query language, forcing users to choose all three or none. 
  - FDB takes modular approach (unbundled architecture: control plane + data plane)
  - Control plane: Manages metadata of the cluster 
  - Data plane: consists of transactional management system
- FDB defaults to strict serializable transactions, it allows these semantics for application that don't require them with flexible, fine-grained control over conflicts
  - Strict serializability through a combination of OSS(Optimistic concurrency control) and MVCC (Multi-version concurrency control)
- Lock free architecture
- FDB can tolerate f faults in f + 1 replicas (rather than 2f + 1)
- FDB doesn't relies on quorums to mask failures, but rather tries to proactively detect and recover from them

## Contribution of this paper 
- Open source distributed storage system
- Deterministic simulation framework 
- Careful chosen feature set
- Unique approach to transaction processing
  
## Design 
- A production database needs to solve many problem 
  - Data persistence
  - Data partitioning
  - Load balancing
  - Membership 
  - Failure detection
  - Failure recovery
  - Replica placement
  - Synchronization
  - Overload control
  - Scaling
  - Concurrency 
  - Job Scheduling
  - System monitoring
  - Alerting
  - Backup
  - System upgrade
  - Deployment 
  - Configuration management
  - Bas bhai

### Design Principle
- *Divide-and-Conquer* (or separation of concerns)
  - FDB decouples write path (transaction management system) from read path (distributed storage)
  - This allow scape them independently 
  - Within transaction management system, processes are assigned various roles representing different aspects of transaction management
    - Timestamp management
    - Accepting commits
    - Conflict detection
    - logging
    - Cluster-wide orchestration 
      - Over load control
      - Load balancing 
      - Failure recovery 
  
- *Make failure a common case*
  - For distributed system, failure is a norm rather than an exception
- *Fast fail and recover fast*
  - Minimize Mean Time to Recover (MTTR)
- *Simulation testing*

### System Interface 
- The `get()`, `set()` operations for read and write single key-value pair 
- `getRange()` returns a sorted list of keys-value pairs
- `clear()` deletes all key-value pair within a range or starting with a certain key prefix 
- A FDB transaction 
  - Modifies a snapshot of the database at a certain version (in-memory instance)
    - A transaction's write (i.e., `set()` and `clear()` calls) are buffered by FDB client until final `commit` is called
  - Only write to the persistent storage when transaction commits; 
- For performance
  - Key size <= 10KB, value size <= 100KB and transaction size <= 10MB

### Architecture 

![Architecture of Foundation DB](./images/foundation-db/foundationdb-architecture.jpg)

- **Control Plane**
  - Responsibility 
    - Persisting critical system metadata 
      - e.g. Configuration of transaction systems on *Coodinators*
      - These Coodinators forms a disk Paxos group and selects a singleton 
        *ClusterController* 
      - ClusterController monitors all servers in the cluster and recruits three singleton processes 
        - *Sequencer* 
          - Assign read & commmit version to the transactions 
        - *DataDistributor*
          - Monitoring failures and balancing data among StorageServers 
        - *RateKeeper*
          - Overload protection to the cluster 
      - In case of crash re-recruited if they fail or crash 
- **Data Plane**
  - Handles OLTP workloads (read-mostly, read and write a small set of keys, 
    low contention and requires scalability)
  - Maintains 
    - A *log system* (LS) for Write-AHead-Log (WAL) for TS
      - Log system contains a set of *LogServers*
      - LogServers act as replicated, shared, distributed persistent queue, where 
        each queue store WAL data for a StorageServer
    - *Distributed Storage System* (SS) for storing data and servicing reads 
      - Contains number of *StorageServers* for serving client reads, where each storage server let the 
        data shard i.e., contiguous key ranges 
      - StorageServers are the majority of the processes in the system, and together they form a distribute B tree 
      - FDB uses modified version of SQLite as the storage engine on each server (with enh which add supports to async programming, defer deletion to a background task)
  - TS provides transaction processing and consists of 
    - *Sequencer*
      - Assigns read & commit version to the transaction 
    - *Proxies* 
      - Offers MVCC(MultiVersion Concurrency Control) read version to the client 
        orchestrate transaction commits 
    - *Resolvers* 
      - Checks for conflict b/w transactions 
  - All of the three are stateless processes (cool!!)
