- [Designing Data Intensive Applications](#designing-data-intensive-applications)
  - [Resources](#resources)
  - [Plethora of buzzwords relating to storage and processing of data](#plethora-of-buzzwords-relating-to-storage-and-processing-of-data)
  - [Preface](#preface)
- [Part 1. Foundation of Data Systems \[Chapter 1 - Chapter 4\]](#part-1-foundation-of-data-systems-chapter-1---chapter-4)
  - [Chapter 0: Trade-Offs in Data System Architecture](#chapter-0-trade-offs-in-data-system-architecture)
    - [OLTP vs OLAP](#oltp-vs-olap)
      - [From data warehouse to data lake](#from-data-warehouse-to-data-lake)
    - [Cloud versus Self-Hosting](#cloud-versus-self-hosting)
    - [Cloud-Native System Architecture](#cloud-native-system-architecture)
    - [Separation of storage and compute](#separation-of-storage-and-compute)
    - [Distributed versus Single-Node Systems](#distributed-versus-single-node-systems)
    - [Problems with Distributed Systems](#problems-with-distributed-systems)
    - [Microservices and Serverless](#microservices-and-serverless)
      - [Microservices](#microservices)
      - [Serverless](#serverless)
    - [Cloud Computing versus Supercomputing](#cloud-computing-versus-supercomputing)
    - [Data Systems, Law, and Society](#data-systems-law-and-society)
  - [Chapter 1 : Reliable, Scalable, and Maintainable Applications](#chapter-1--reliable-scalable-and-maintainable-applications)
    - [Reliability](#reliability)
    - [Scalability](#scalability)
    - [Performance](#performance)
    - [Maintainability](#maintainability)
  - [Chapter 2. Data Models and Query Language](#chapter-2-data-models-and-query-language)
    - [Data models](#data-models)
    - [The Object-Relational Mismatch](#the-object-relational-mismatch)
    - [Many-to-One and Many-To-Many relationships](#many-to-one-and-many-to-many-relationships)
    - [Relational Vs Document database Today ?](#relational-vs-document-database-today-)
    - [Which data model leads to simpler application code?](#which-data-model-leads-to-simpler-application-code)
    - [Graph-Like Data Models](#graph-like-data-models)
      - [Property Graphs](#property-graphs)
    - [Cypher Query Language](#cypher-query-language)
    - [Graph Queries in SQL](#graph-queries-in-sql)
    - [Triple-Store and SPARQL](#triple-store-and-sparql)
    - [Summary](#summary)
  - [Chapter 3. Storage and Retrievals](#chapter-3-storage-and-retrievals)
    - [Hash Indexes](#hash-indexes)
  - [Chapter 4. Encoding and Evolution](#chapter-4-encoding-and-evolution)
- [Part 2. Distributed Data](#part-2-distributed-data)
  - [Chapter 5. Replication](#chapter-5-replication)
    - [Single-Leader Replication](#single-leader-replication)
    - [Sync vs Async Replication](#sync-vs-async-replication)
    - [Setting Up New Followers](#setting-up-new-followers)
      - [Databases Backed by Object Storage](#databases-backed-by-object-storage)
    - [Handling Node Outages](#handling-node-outages)
      - [Follower failure: Catch-up recovery](#follower-failure-catch-up-recovery)
      - [Leader failure: Failover](#leader-failure-failover)
    - [Implementation of Replication Logs](#implementation-of-replication-logs)
      - [Statement-based replication](#statement-based-replication)
      - [Write-ahead log (WAL) shipping](#write-ahead-log-wal-shipping)
      - [Logical (row-based) log replication](#logical-row-based-log-replication)
    - [Problems with Replication Lag](#problems-with-replication-lag)
      - [Reading Your Own Writes](#reading-your-own-writes)
      - [Monotonic Reads](#monotonic-reads)
      - [Consistent Prefix Reads](#consistent-prefix-reads)
      - [Solutions for Replication Lag](#solutions-for-replication-lag)
    - [Multi-Leader Replication](#multi-leader-replication)
      - [Geographically Distributed Operation](#geographically-distributed-operation)
      - [Multi-leader replication topologies](#multi-leader-replication-topologies)
        - [Problems with different topologies](#problems-with-different-topologies)
      - [Sync Engines and Local-First Software](#sync-engines-and-local-first-software)
      - [Real-time collaboration, offline-first, and local-first apps](#real-time-collaboration-offline-first-and-local-first-apps)
        - [Pros and cons of sync engines](#pros-and-cons-of-sync-engines)
      - [Dealing with Conflicting Writes](#dealing-with-conflicting-writes)
        - [Conflict avoidance](#conflict-avoidance)
        - [Last write wins (discarding concurrent writes)](#last-write-wins-discarding-concurrent-writes)
        - [Manual Conflict Resolution](#manual-conflict-resolution)
        - [Automatic conflict resolution](#automatic-conflict-resolution)
      - [CRDTs and Operational Transformation](#crdts-and-operational-transformation)
  - [Chapter 6. Partitioning](#chapter-6-partitioning)
  - [Chapter 7. Transaction](#chapter-7-transaction)
    - [Introduction](#introduction)
    - [The meaning of ACID](#the-meaning-of-acid)
      - [Atomicity](#atomicity)
      - [Consistency](#consistency)
      - [Isolation](#isolation)
      - [Durability](#durability)
    - [Single-Object and Multi-Object Operations](#single-object-and-multi-object-operations)
      - [Single-object writes](#single-object-writes)
      - [The need for multi-object transactions](#the-need-for-multi-object-transactions)
      - [Handling errors and aborts](#handling-errors-and-aborts)
    - [Weak Isolation Levels](#weak-isolation-levels)
    - [Read Committed](#read-committed)
      - [Implementing read committed](#implementing-read-committed)
    - [Snapshot Isolation, repeatable read, and naming confusion](#snapshot-isolation-repeatable-read-and-naming-confusion)
    - [Preventing Lost Updates](#preventing-lost-updates)
      - [Atomic Write Operation](#atomic-write-operation)
      - [Explicity Locking](#explicity-locking)
      - [Automatically detecting lost updates](#automatically-detecting-lost-updates)
      - [Conditional writes (compare-and-set) CAS](#conditional-writes-compare-and-set-cas)
        - [How Replication Handles Lost Updates](#how-replication-handles-lost-updates)
    - [Write Skew and Phantoms](#write-skew-and-phantoms)
      - [What is Write Skew?](#what-is-write-skew)
      - [Why it is tricky to prevent](#why-it-is-tricky-to-prevent)
      - [Possible Solutions](#possible-solutions)
    - [Phantoms(काल्पनिक) Causing Write Skew](#phantomsकाल्पनिक-causing-write-skew)
      - [General Pattern of These Anomalies](#general-pattern-of-these-anomalies)
      - [Phantoms Explained](#phantoms-explained)
      - [ORMs \& Phantoms](#orms--phantoms)
    - [Materializing Conflicts (Workaround)](#materializing-conflicts-workaround)
    - [Serializability](#serializability)
      - [Why it matters ?](#why-it-matters-)
      - [What is Serializability?](#what-is-serializability)
      - [Why Not Always Use It?](#why-not-always-use-it)
    - [Actual Serial Execution](#actual-serial-execution)
      - [Summary of serial execution](#summary-of-serial-execution)
    - [Two-Phase Locking (2PL)](#two-phase-locking-2pl)
      - [2PL is NOT 2PC(ommit)](#2pl-is-not-2pcommit)
      - [Core Idea: Readers and Writers Block Each Other](#core-idea-readers-and-writers-block-each-other)
      - [Performance Problems](#performance-problems)
      - [Phantoms and Predicate Locks](#phantoms-and-predicate-locks)
    - [Serializable Snapshot Isolation (SSI)](#serializable-snapshot-isolation-ssi)
    - [Distributed transactions](#distributed-transactions)
      - [Big picture - what makes distributed transactions hard](#big-picture---what-makes-distributed-transactions-hard)
      - [Two-Phase Commit (2PC) - essentials](#two-phase-commit-2pc---essentials)
        - [Why 2PC can block](#why-2pc-can-block)
        - [Operational consequences](#operational-consequences)
      - [Three-phase commit](#three-phase-commit)
      - [Practical fixes and improvements to vanilla XA/2PC](#practical-fixes-and-improvements-to-vanilla-xa2pc)
    - [Distributed Transactions Across Different Systems](#distributed-transactions-across-different-systems)
      - [Why distributed transactions are controversial ?](#why-distributed-transactions-are-controversial-)
      - [Where the performance cost actually comes from ?](#where-the-performance-cost-actually-comes-from-)
      - [Why we should not dismiss distributed transactions outright ?](#why-we-should-not-dismiss-distributed-transactions-outright-)
      - [Critical distinction - two very different meanings of “distributed transaction”](#critical-distinction---two-very-different-meanings-of-distributed-transaction)
    - [Exactly-once Message Processing - Distributed Transactions](#exactly-once-message-processing---distributed-transactions)
    - [XA Transaction](#xa-transaction)
    - [Summary](#summary-1)
  - [Chapter 8. The Trouble with Distributed Systems](#chapter-8-the-trouble-with-distributed-systems)
  - [Chapter 9. Consistency and Consensus](#chapter-9-consistency-and-consensus)
    - [Consistency Guarantees / Distributed Consistency Models](#consistency-guarantees--distributed-consistency-models)
    - [Linearizability](#linearizability)
      - [What makes a system linearizable ?](#what-makes-a-system-linearizable-)
      - [Relying on Linearizability (Use Cases)](#relying-on-linearizability-use-cases)
      - [Implementing Linearizable Systems](#implementing-linearizable-systems)
      - [Cost of Linearizability](#cost-of-linearizability)
    - [Distributed Transactions and Consensus](#distributed-transactions-and-consensus)
  - [Chapter 10. Batch Processing](#chapter-10-batch-processing)
  - [Chapter 11. Stream Processing](#chapter-11-stream-processing)

# Designing Data Intensive Applications

## Resources

- Author : Martin Kleppmann
- 20 hours of reading (600+ pages book)
[Oreilly Link](https://learning.oreilly.com/library/view/designing-data-intensive-applications/)

## Plethora of buzzwords relating to storage and processing of data
- NoSQL! Big Data! Web-scale! Sharding! Eventual consistency! ACID! CAP theorem! Cloud services! MapReduce! Real-time!

## Preface
- Data intensive 
    - Data as primary challenged - quantity/complexity/changing-nature
    - Store data : Database
    - Expensive opr results : Cache
    - Search by keywords : Search indexes
    - Send msg to another process : Stream processing
    - Accumulated data : batch processing
- Compute intensive 
    - CPU cycles are the bottleneck

- Why read ?
    - If you are Software Engineer/Architect
        - Must have technically accurate and precise understanding of tech 
        - Trade-offs;
    - What about rapid change in tech ?
        - Basic principle remains true 

- Goals ?
    - Navigate the diverse and fast-changing landscape of technologies for **processing** and **storing data**
    - Not just *how*, but also *why* they work that way, and *what* question we need to ask 

- Gains ?
    - Good intuition for what your systems are doing under hood
    - Can reason about their behavior 
    - Good design decision
    - Track down problems that can happen

- Who should read ?
    - If you develop applications that have backend
    - SE, SA and Technical Managers(who loves to code)

- Prereq ?
    - Basic Network/OS
    - Basic relational database

# Part 1. Foundation of Data Systems [Chapter 1 - Chapter 4]

## Chapter 0: Trade-Offs in Data System Architecture 
- Data is central to much application development today
- We call an application data-intensive if data management is one of the primary challenge. While *compute-intensive* the challenge is parallelizing some very large computation
- In DI we worry more about things like storing and processing the data 
- In general many application need to: 
  - Store data so that they can find it later (**databases**)
  - Remember the result of an expensive operation, to speedup reads (**cache**)
  - Allows user to search data by keyword or filter (**search indexes**)
  - Handle events and data changes as soon as they occur (**stream processing**)
  - Periodically crunch a large amount of accumulated data (**batch processing**)

### OLTP vs OLAP
- Online [Transaction|Analytics] Processing
- Both have different pattern of data access. Trasactional queries are more like read, update, delete whereas analytics queries are like aggregation stats rather than individual records

    <img src="./images/ddia/oltpvsolap.png" alt="description" width="800" height="500">

- Initially both OLTP and OLAP were carried out through SQL. Later the term *data warehouse* got coined, which means that analytics data will go on a different kind of storage which is optimal for the analytics queries. 
  - A *data warehouse* is a separate database that analysts can query to their hearts’ content, without affecting OLTP operations

#### From data warehouse to data lake
- A data warehouse often uses a relational data model that is queried through SQL. But this might not be the best for all the analysis use cases e.g., for ML we might require to transform data into features (vectors) 
- Consequently, organizations face a need to make data available in a form that is suitable for use by data scientists. The answer is a data lake:
- The data lake contains data in a “raw” form produced by the operational systems, without the transformation into a relational data warehouse schema. 
  - This approach has the advantage that each consumer of the data can transform the raw data into a form that best suits their needs.

### Cloud versus Self-Hosting
- Ultimately, this is a question about business priorities.
- The received management wisdom is that things that are a core competency or a competitive advantage of your organization should be done in-house, whereas things that are non-core, routine, or commonplace should be left to a vendor
- In-house software, operations provides more control but great investment
- Off-the shelf software, outsourced operations (SaaS, cloud) provides less control but lower investment 
- Cloud services are particularly valuable if the load on your systems varies a lot over time
- The biggest downside of a cloud service is that you have no control over it:
  - If the service shuts down or becomes unacceptably expensive, or if the vendor decides to change their product in a way you don’t like, you are at their mercy
  - Data security 
  - If the service goes down, all you can do is to wait for it to recover.

### Cloud-Native System Architecture
-  The term *cloud-native* is used to describe an architecture that is designed to take advantage of cloud services.
   -  Designed for better performance, faster recovery from failures, being able to quickly scale computing resources to match the load, and supporting larger datasets

    | Category | Self-hosted systems | Cloud-native systems|
    |--|--|--|
    | Operational/OLTP | MySQL, PostgreSQL, MongoDB | AWS Aurora, Azure SQL DB Hyperscale, Google Cloud Spanner |
    | Analytical/OLAP | Teradata, ClickHouse, Spark | Snowflake, Google BigQuery |

### Separation of storage and compute
- In traditional computing, disk storage is regarded as durable; to tolerate the failure of an individual hard disk, RAID is often used to maintain copies of data 
- Cloud-native systems typically treat disks more like an ephemeral cache, and less like long-term storage.
- As an alternative to local disks, cloud services also offer virtual disk storage that can be detached from one instance and attached to a different one. 
- Such a virtual disk is not actually a physical disk, but rather a cloud service provided by a separate set of machines, which emulates the behavior of a disk (a block device, where each block is typically 4 KiB in size). 
  - To address this problem, cloud-native services generally avoid using virtual disks, and instead build on dedicated storage services that are optimized for particular workloads. 
  - Object storage services such as S3 are designed for long-term storage of fairly large files, ranging from hundreds of kilobytes to several gigabytes in size.
- Traditionally same computer is responsible for both storage and compute, but in cloud-native, these two responsibility are disaggregated; e.g., S3 only stores large file; to perform analytics data need to move over network so that computation can be perform on compute nodes
- Moreover, cloud-native systems are often *multitenant* and thus enabling better hardware utilization.


### Distributed versus Single-Node Systems
- A system that involves several machines communicating via a network is called a *distributed system*.
- Each of the processes participating in a distributed system is called a *node*.
- There are various reasons why you might want a system to be distributed:
  - Scalability : Data volume / Computation requirement grow bigger than a single machine can handle 
  - Latency : Request around globe. So put datacenter geographically closer
  - Fault Tolerant / High Availability : Work even when machine fail (or an entire datacenter)
  - Elasticity : Busy at some time/ idle at other (scale up and scale down)
  - Legal compliance : Data within country geography


### Problems with Distributed Systems
- Network failures
- Troubleshooting a distributed system is often difficult
- Data consistency 

### Microservices and Serverless
#### Microservices
- Microservices are primarily a technical solution to a people problem: allowing different teams to make progress independently without having to coordinate with each other. 
  - This is valuable in a large company, but in a small company where there are not many teams, using microservices is likely to be unnecessary overhead, and it is preferable to implement the application in the simplest way possible
- Orchestration frameworks such as Kubernetes have become a popular way of deploying services, since they provide a foundation for this infrastructure. 
- Testing a service during development can be complicated, since you also need to run all the other services that it depends on.
- Microservice APIs can be challenging to evolve. 
  - Clients that call an API expect the API to have certain fields. Developers might wish to add or remove fields to an API as business needs change, but doing so can cause clients to fail. 
  - Worse still, such failures are often not discovered until late in the development cycle when the updated service API is deployed to a staging or production environment. 
  - API description standards such as OpenAPI and gRPC help manage the relationship between client and server APIs;

#### Serverless
- Serverless, or function-as-a-service (FaaS), is another approach to deploying services, in which the management of the infrastructure is outsourced to a cloud vendor
- When using virtual machines, you have to explicitly choose when to start up or shut down an instance; in contrast, with the serverless model, the cloud provider automatically allocates and frees hardware resources as needed, based on the incoming requests to your service 
- Serverless deployment shifts more of the operational burden to cloud providers and enables flexible billing by usage rather than machine instances
- The term “serverless” can also be misleading: each serverless function execution still runs on a server, but subsequent executions might run on a different one.

### Cloud Computing versus Supercomputing
- Cloud computing is not the only way of building large-scale computing systems; an alternative is high-performance computing (HPC), also known as supercomputing. 
  - Supercomputers are typically used for computationally intensive scientific computing tasks
  - A supercomputer typically runs large batch jobs that checkpoint the state of their computation to disk from time to time.
  - Supercomputer nodes typically communicate through shared memory and remote direct memory access (RDMA), which support high bandwidth and low latency, but assume a high level of trust among the users of the system

### Data Systems, Law, and Society
- The architecture of data systems is influenced not only by technical goals and requirements, but also by the human needs of the organizations
- General Data Protection Regulation (GDPR)  has given residents of many European countries greater control and legal rights over their personal data
- Legal considerations are influencing the very foundations of how data systems are being designed
  - For example, the GDPR grants individuals the right to have their data erased on request (sometimes known as the right to be forgotten).
  - However, as we shall see in this book, many data systems rely on immutable constructs such as append-only logs as part of their design; how can we ensure deletion of some data in the middle of a file that is supposed to be immutable? How do we handle deletion of data that has been incorporated into derived datasets such as training data for machine learning models? 
  - Answering these questions creates new engineering challenges.


## Chapter 1 : Reliable, Scalable, and Maintainable Applications
> No such hard boundary b/w databases, queues, caches, etc. because now most tools are coming up with multiple features. Thus we will keep these three under single umbrella
### Reliability
- Tolerating hardware & software faults
    - Redundant components ? 
        - When one component dies, the redundant component can take its place while the broken component is replaced
        - Was OK in older system, but cannot tolerate loss of entire machine
        - More data volume & application compute demand == More machines == More hardware faults
    - Software fault-tolerant 
        - Can tolerate entire machine loss (along with hardware redundancy)
        - Operational advantages
            - Schedules downtime/patching, one node at a time without downtime (rolling upgrade)

- Fault, Failure & Fault Tolerant Systems
  - Fault is defined as one component of the system is deviating from the spec
  - Failure is when system as a whole stops providing required service to the user
  - Fault tolerant systems can anticipate the faults and can cope up with them

- Hardware vs Software
    - We make **assumption** hardware faults are independent and random
        - P(Component A fails | Component B failed) = 0 (or may be ~0 : weak correlations)
    - Another class : Systematic faults
        - Correlated across nodes, types : 
            - Software bug
            - Runaway process - use up shared resources - CPU, memory, disk or network bandwidth
            - Slow down of some service
            - Cascading failures
        - These bugs lie dormant until some event trigger them

- Human Errors
    - To avoid
        - Design system that minimizes opportunities for error : Well-designed abstraction, APIs, Admin interface 
        - Decouple components (high risk, low risk) : sandbox environment for experimentation
        - Quick & easy recovery in case of failures (minimize impact)
        - Clear monitoring (performance metrics, error rates) : tracking what is happening for understanding failures i.e telemetry
        - Good management practices 

### Scalability
- Systems ability to cope with increased load
- Define load ? 
    - Depends on the system architecture (load parameters)
    - Example
        - Number of request/sec to a web server
        - Ratio of read/write
        - Simultaneous user in a chat room
        - Cache hit rate

    - Twitter Example with actual past data
        - Post tweet
            - Can publish a new post (4.6k request/sec on average, 12k max)
        - Home timeline 
            - View post of others (300k request/sec)
        - Now you might think this is simple 12k write/sec is not that hard 
            - Yes, true
            - But Twitter scaling challenge is not due to tweet volume, but due to *fan-out* (each user follow many user)
        - Broadly two implementations we can go with 
            - First
                - ![text](./images/ddia/ddia_0102.png)
                - Insert tweet to some global collection of tweet
                - When a user request 
                    - Get all the tweets to whom I follow, sort and give back to me 
                    - Query may look like below 
                    ```sql
                    select tweets.*, users.* 
                    from tweets
                    join user on tweets.sender_id=user.id
                    join follows on follows.followee_id=user.id
                    where follows.follower_id = current_user
                    ```
                    - Issue ?
                        - Join (too much data movement disk <-> ram)
                        - Struggle to load home timeline
                    - Sample schema
                        - follows(follower_id, followee_id)
                        - tweets(tweet_msg, sender_id, timestamp)
                        - user(id, scree_name, profile_image)
            - Second
                - Maintain a cache for each user's home timeline
                    - User post a tweet, look up all people who follow the user
                        and insert the new tweet into each of their home timeline cache
                    - This made read cheap (already in cache)
                - ![text](./images/ddia/ddia_0103.png)
            - Gains 
                - Approach second is better than first in term of home timeline reads
                - Less work during read
                - Reality check: Tweets are published way less frequent compare to home timeline read
            - Pain 
                - Approach one is better than second in term of publish tweet
                - More work at write in second approach
                    - Assumption Land
                        - Avg distribution of follower per user: 75 followers
                        - Tweets rate: 4.6k
                        - Number of writes : 4.6k * 75 = 345k writes/second
    - In the above Twitter example, the distribution of followers per user(may be weighted by how often those user tweet) is a key load parameter for discussing scalability, since it determine the *fan-out* load

### Performance
- Once load is defined, you can test what happen when the load increases
    - Increase a load parameter and keep the system resources unchanged, impact on performance ?
    - When you increase the load parameter, how much do you need to increase the resource if you want to keep performance unchanged ?
- In batch system throughput weights more. 
- In online system(stream) service response time (client receive - client send)

> Latency Vs Response time : Both are not same. Response time is what client sees (includes network delays, queueing delays). Latency is the duration that a request is waiting to be handled - during which it latent, awaiting service
- Think of response time not as a single number, but as a distribution of values 
    - Percentile is better metric than average
        - ![Percentile](./images/ddia/ddia_0104.png)
    - Average doesn't tell you how long users "typically" have to wait ?
    - Median (sort and then check half point) 
        - Median also known as 50th percentile (p50)

- High percentiles of response times, also know as *tail latencies* like p99 (1 in 100), p99.9 (1 in 1000), p99.99 (1 in 10,000)
    - Imp, because they directly affect customers satisfaction and therefore the sales
    - Ex. Amazon
        - Describe response time requirement for internal service in term of the 99.9th percentile
            - Affects only 1 in 1000 request
        - But customer with the slowest request are often those who have most data on their account because they have made many purchase
- Head-of-line blocking (Queuing delay)
  - small number of slow requests hold up the processing of subsequent requests
  - queueing delay accounts for the large part of response time at high percentiles
  - client for generating artificial load, should keep on sending requests independently of the response time thereby not keeping queues artificially shorter in the test
- High percentile becomes more important in backend services that are called multiple times as part of serving a single end-user request
    - Right way of aggregating response time is to add histograms
    - Single service slow == complete system slow
    ![Several backend calls](./images/ddia/ddia_0105.png)

- Approach for Coping with Load
    - Architecture design for x level of load might not work well for y level of load
    - **Scaling Trade-off**  
        - Scaling up: Vertical or 
        - Scaling out: Horizontal 
    > Distributing load across multiple machine is also known as *shared-nothing* architecture
    - Good architectures often involves mixture of both the scaling approaches
    - Some system are elastic
        - Automatically add compute resources
        - Good if load is unpredictable
    - Some systems needs to be scaled manually
        - Human analyze
        - Fewer operational surprises
    - Stateless services distribution easy across machines
    - Stateful services are hard to move from single node to distributed setup
    - There is no such *magic scaling sauce* 
        - An architecture that scale well for App x is build on assumption set S (load factors)
        - Therefore, architecture of systems that operate at large scale is usually highly specific to the application
    
### Maintainability

- Major cost of software products
- Pain is to fix other mistakes and maintain legacy code
    -  We should design software in such a way that minimize pain during maintenance, and thus avoid creating legacy sofware ourselves
-  Design software to minimize pain during maintenance
    1. Operability : easy for operations team to keep system running
    2. Simplicity : easy for new engineer to understand the system
    3. Evolvability : easy for engineers to make changes to the systems in future
- Operability
  - making routine tasks easy, allowing operations team to focus their efforts on high-value activities
  - having good visibility into system's health & effective ways to manage it
- Simplicity
  - large projects => complex & difficult to understand
    - slows down everyone who need to work on the system
    - increase cost of maintenance
    - increase risk of introducing bugs when making a change
  - **Good abstraction** : avoid **accidental complexity** 
    - hides implementation detail behind a clean, simple-to-understand façade
    - Examples :
      - high-level programming languages are abstractions that hide machine code, CPU registers, and syscalls
      - SQL is an abstraction that hides complex on-disk and in-memory data structures, concurrent requests from other clients, and inconsistencies after crashes
    - **reusability** : allows us to extract part of the large systems into well-defined, reusable components
- Evolvability : agility on the data system level
  - agile systems : allows making change easier
  - goal is to find ways of increasing agility of larger data systems
  - agility of system dependent on its simplicity and its abstractions

## Chapter 2. Data Models and Query Language

### Data models
- Data models decides
    - your thinking to solve the problem
    - the way software will be written

- Decide data model for you app wisely

- Layering of data models
    - All application are built by layering one data model on another
    - Application developer think in term of objects/entities/data structure eg. people, organizations, goods, actions(API to manipulate)
    - Store data on disk - General purpose data models - JSON, XML, tables or graph model
    - Database engineers thinks JSON/XML/Relations/Graph in term of bytes in memory, disk or network
    - One more lower level - hardware engineers (byte in term of electical current, pulses, pulses of light, etc)

- Each layer hides the complexity of the layers below it by providing a clean data model

- Relational Model vs Document Model
    - Relational model popular for
        - Transactions (ACID) : Banking, airline, etc.

- The Birth of NoSQL (2010)
    - Goal: Overthrow the dominance of relational model's dominance
    - Driving forces behind adoption of NoSQL databases
      1. Greater scalability
      2. Free & open-source software
      3. Specialized query operations not supported by relational model
      4. More dynamic & expressive data model, no restriction with relational schemas

### The Object-Relational Mismatch

- Todays app are developed in OOPs languages
- SQL data models seems highly unrelated with OOPs
    - An awkward translation b/w two
    - This disconnect b/w the models is sometime called *impedance mismatch*

- ORM (Object Relational Mapping) frameworks
    - ex. ActiveRecord, Hibernate
        - reduce the amount of boilerplate code for translation layer
        - But can't completely hide the differences

- Example : LinkedIn : Relational vs JSON
    - Relational
    ![Bill Gate Resume on a Relational model](./images/ddia/ddia_0201.png)
    - JSON Document 
        ```json
        {
            "user_id":     251,
            "first_name":  "Bill",
            "last_name":   "Gates",
            "summary":     "Co-chair of the Bill & Melinda Gates... Active blogger.",
            "region_id":   "us:91",
            "industry_id": 131,
            "photo_url":   "/p/7/000/253/05b/308dd6e.jpg",
            "positions": [
                {"job_title": "Co-chair", "organization": "Bill & Melinda Gates Foundation"},
                {"job_title": "Co-founder, Chairman", "organization": "Microsoft"}
            ],
            "education": [
                {"school_name": "Harvard University",       "start": 1973, "end": 1975},
                {"school_name": "Lakeside School, Seattle", "start": null, "end": null}
            ],
            "contact_info": {
                "blog":    "https://www.gatesnotes.com/",
                "twitter": "https://twitter.com/BillGates"
            }
        }
        ```

- Locality is better in JSON 
    - Fetch a profile in relational - perform multiple queries
    - Document-oriented databases uses this data model - CouchDB, RethinkDB, MongoDB, Espresso, etc.
    - Json representation makes this tree (**one-to-many relation**) structure explicit
        ![JSON representation](./images/ddia/ddia_0202.png)

### Many-to-One and Many-To-Many relationships
- Look at the `region_id` and `industry_id`
    - They are not plain text, instead they are IDs
    - Benefits ?
        - Consistent style/Spell check
        - Avoiding ambiguity
        - Ease of updating
        - ID need not to changed but information it identify can be change
    - Removing such duplicates is done in the process of *normalization*

- Normalization data requires Many-To-One relations
    - eg. Many people live in one particular regions
    - M:1 doesn't fit directly to document model 
    - If database doesn't supports join, then emulate than in application code by making multiple queries
        - This shift of code to app might not be good

- More often initial version of application fits well in join-free document model
    - But data becomes more interconnected as more features are introduced which brings many-to-many or many-to-one relations within the data

- Example (Modification to resume)
    - *Organization and school as entities*
        - In example : `organization` and `school_name` are just string
        - Perhaps they should be references to entities instead ?
            - Each org, school, university HAS own web page(logo, news feed)
        - Each resume could -link-> org/school
    - *Recommendations*
        - Add a new feature
            - One user can write recommendation to another
            - Show recommendation on resume of the user, together with name, photo of the user making recommendation
            - If recommender updates their photo
                - All recommendation they have made needs change
                - Therefore recommendation should have reference to the author's profile
            - ![](./images/ddia/ddia_0203.png)
    - Many to Many relation required in above example ?
        - ![](./images/ddia/ddia_0204.png)
        - Data in dotted rectangle can be group into one document
        - References to organizations, schools, and other users represented as references
        - Requires join when queried

### Relational Vs Document database Today ?
- Fault tolerant ? Handling concurrency ? 
- Benefits of using document database
    - Schema flexibility
    - Better performance due to locality
    - Closer to data structure in application
- Benefits of using relational database
    - Support for join
    - M:1, M:N relationship 

### Which data model leads to simpler application code?
- If application has document like structure (a tree of 1:M) and tree is loaded at once, then use document 
    - Major drawback in document : You can't refer directly to a nested item with an document
    - The drawback become a problem if document are deeply nested
    - Poor support for join in document databases may or may not be a problem
        - Problem: If M:N relations exists
        - !Problem: M:N relationship may never needed in an analytical application
    - Reduce use of M:N relations by **denormalizing** your data
        - Denormalization brings more complexity and makes consistency harder

- In fact there is no simple answer to the question; it depends on your application; relationship that exist b/w data items
- Schema flexibility in the document model
    - No schema enforced on data by the JSON/document database
        - Arbitrary key/value can be added
            - Makes migration easy for document database, on the other hand migration in relational database brings downtime
        - Can't say these as schema less, because there is some implicity assumption while reading the data
    
- **Schema-on-read** : Structure of data is implicit and determine at the time of read
    - When to use ? 
        - If data is not homogenous, but heterogeneous.
- **Schema-on-write**: Schema is explicit 
    - If data is homogeneous 

### Graph-Like Data Models
- Usecase : 
  - many-to-many relationships and 
  - complex connections between data
- Consists of two kind of objects
  1. Vertices / Nodes / Entities
  2. Edges / Relationships / Arcs
- Examples
  - Social Graphs
  - The Web Graph
  - Road & Railway Network
- Following figure shows two people, Lucy from Idaho and Alain from Beaune, France. They are married and living in London.
  ![](./images/ddia/ddia_0205.png)
- Provides consistent way of storing completely different types of object in a single datastore
- Different ways of structuring data in graphs
  - Property Graph Model
  - Triple-store Model
- Different ways of querying data in graphs : Declarative languages
  - Cypher
  - SPARQL
  - Datalog
  
#### Property Graphs
- vertex consists of 
  - unique identifier
  - set of outgoing edges
  - set of incoming edges
  - collection of properties (key-value pairs)
- edge consists of 
  - unique identifier
  - label to identify kind of relationship between two vertices
  - vertex at which edge starts (tail vertex)
  - vertex at which edge ends (head vertex)
  - collection of properties (key-value pairs)
- mapped to graphstore with two relational tables, one for vertices & one for edges
```sql
CREATE TABLE vertices (
    vertex_id   integer PRIMARY KEY,
    properties  json
);

CREATE TABLE edges (
    edge_id     integer PRIMARY KEY,
    tail_vertex integer REFERENCES vertices (vertex_id),
    head_vertex integer REFERENCES vertices (vertex_id),
    label       text,
    properties  json
);

CREATE INDEX edges_tails ON edges (tail_vertex);
CREATE INDEX edges_heads ON edges (head_vertex);
```
- important aspects of this data model
  - any vertex can have an edge connecting it with any other vertex
  - efficiently find both incoming and outgoing edges for a given vertex (indexes is maintained on tail_vertex and head_vertex), can traverse the graph both forward & backward
  - different labels can be used for storing different relationships, different information can be stored in a single graph
- graphs are good for evolvability, as we add new features to application graph can easily be extended to accommodate changes in application's data structures

### Cypher Query Language
- declarative query language for property graphs (create for Neo4j graph database)
  - Fact: The name it take from a character in Matrix Movie
- subset of data from figure 2.5 can be represented as Cypher query
```sql
CREATE
  (NAmerica:Location {name:'North America', type:'continent'}),
  (USA:Location      {name:'United States', type:'country'  }),
  (Idaho:Location    {name:'Idaho',         type:'state'    }),
  (Lucy:Person       {name:'Lucy' }),
  (Idaho) -[:WITHIN]->  (USA)  -[:WITHIN]-> (NAmerica),
  (Lucy)  -[:BORN_IN]-> (Idaho)
```
    - Each vertex is given a symbolic name like USA or Idaho
    - Arrow notation `(Idaho) -[:WITHIN]-> (USA)` used to create edge labelled with `WITHIN`
- Example query _find the names of all the people who emigrated from the United States to Europe_
  - Cypher query
  ```sql
  MATCH
  (person) -[:BORN_IN]->  () -[:WITHIN*0..]-> (us:Location {name:'United States'}),
  (person) -[:LIVES_IN]-> () -[:WITHIN*0..]-> (eu:Location {name:'Europe'})
  RETURN person.name
  ```
- there are several ways for executing query, and it's up to query optimizer to select most efficient strategy


### Graph Queries in SQL
- Graph data can be represented in the relational database + you can query it using sql
  - But query writing comes with pain
- Unlike simple joins where you know what to join in advance, here in case of graph you may have to traverse a variable number of edges before reaching the vertex you are looking for
> Read more on recursion in SQL 

### Triple-Store and SPARQL
- Equivalent to property graph model (same idea)
- Three part statement (subject, predicate, object) 
  - Example: (lucy, marriedTo, Alan)
  - ```sql
    @prefix : <urn:example:>.
    _:lucy     a       :Person.
    _:lucy     :name   "Lucy".
    _:lucy     :bornIn _:idaho.
    ```
- When predicate is property eg. `_:lucy :name "Lucy"` then the object becomes `String` 
- When predicate represents an edge e.g `_:idaho :within _:usa` then the object become vertex
- `_:someName` doesn't means anything outside this file
  - This only helps us to tag each triplet with a vertex (or all these triplets belongs to same vertex)
- More concise Example:
  - ```sql
    @prefix : <urn:example:>.
    _:lucy     a :Person;   :name "Lucy";          :bornIn _:idaho.
    _:idaho    a :Location; :name "Idaho";         :type "state";   :within _:usa.
    _:usa      a :Location; :name "United States"; :type "country"; :within _:namerica.
    _:namerica a :Location; :name "North America"; :type "continent".
    ```

### Summary 
- All its started with tree (hierarchical data 1:M)
- Hierarchical data was bad for N:M relations, so Relational data model appeared 
- Then relational didn't fit every where, so document model came(when relationship is rare, and self-contained data)
- Graph database on the other targets the use case where every one can related every other
- All three (document, graph and relational) are widely used today
- Each data model comes with it's own query language or framework
  - SQL, MapReduce, MongoDB's, Cypher, SPARQL, and Datalog
- Future<Research> of data models
  - LHC (Large Hadron Collision - to identify God particle) requires to work with Petabytes of data in seconds
  - Genome data (DNA matching)
  - Full-text search


## Chapter 3. Storage and Retrievals

- One of the most fundamental 
  - A database do 2 things - when you give it data, it store; when you ask, it give the data back to you
- This chapter is written in POV of database
  - But why ? As a developer why does this matter to me ?
    - Right, you will be rarely writing your own storage engine, but you do need to select a storage engine appropriate for your application
    - Even having rough idea will work for you
- We will discuss two family of storage engines
  - *Log-structured*, and
  - *page-oriented* such as B-tree

- A simplest database would be just writing to a file and reading
  - But with a simple file you can't handle concurrency, partial writes, error handlings
  - Apart from correctness, there are performance issues also, your search are slow as file size increases

- How to make search fast ?
  - Indexes ? - true they makes read fast, but what about writes, your writes are slow now.

### Hash Indexes

- Simplest Model for index: `f:key -> value`
- Keep this data structure in-memory (faster access)
- For the simplest database example in prev section
  - If we are just appending data to the file, for each key we can keep the `f:key -> (byte offset in the data file)`



## Chapter 4. Encoding and Evolution 


# Part 2. Distributed Data
- In Part 2 we will discuss:
  - What happen when you start storing data on multiple machine for *scalability*, *fault tolerance*, *latency*, *load*?

- Scaling to Higher Load
  - Simplest approach will be vertical scaling or scaling up 
    - many CPU, many RAM, interconnected memory/disk
    - It is also refer as *shared-memory architecture*, all component can be treated as single component
    - But making hardware 2x powerful, generally cost you >= 2x in term of money, and also gain in performance is < 2x (because of overheads)
  - **Share Nothing Architecture**
    - Horizontal scaling or scaling out
    - Each node has it's own hardware component
      - Nodes talk through n/w 
    - No special hardware required by a shared-nothing system
    - Allows you to pick best price/performance ratio

- Replication Vs Partitioning 
  - Two commons ways
    - Replication (keep a copy on several machine)
    - Partitioning (Split big database into small)
  
- In part2 we will mostly discuss *Share Nothing Architecture* 
  
## Chapter 5. Replication
- Replication means keeping a copy of the same data on multiple machines that are connected via a network.
- Why replication ?
  - Latency - Keep you data geographically closer to your users
  - Availability - Allow system to work even if few goes down
  - Throughput - Scale out the number of machine that can server read queries

- For now we will make some assumptions
  - Data is small enough to fit completely on single machine (not sharding)
- We will further discuss how to dealt with the various kind of fault that can occurs in a replicated data system
- We will discuss three popular algorithms for replicating changes between nodes
  - Single-leader
  - Multi-leader
  - Leaderless replication
- Other tradeoffs in replication
  - Sync vs Async
  - Eventual consistent vs Strict

### Single-Leader Replication 
- Each node that stores a copy of the database is called a replica. With multiple replicas, a question inevitably arises: *how do we ensure that all the data ends up on all the replicas?*
- Every write to the database needs to be processed by every replica; otherwise, the replicas would no longer contain the same data. 
- The most common solution is called leader-based replication, primary-backup, or active/passive.
- One of the replicas is designated the leader
  - When clients want to write to the database, they must send their requests to the leader, which first writes the new data to its local storage.
- The other replicas are known as followers
  - Whenever the leader writes new data to its local storage, it also sends the data change to all of its followers as part of a replication log or change stream.
  - Each follower takes the log from the leader and updates its local copy of the database accordingly, by applying all writes in the same order as they were processed on the leader.
- When a client wants to read from the database, it can query either the leader or any of the followers.
- If the database is sharded, each shard has one leader. Different shards may have their leaders on different nodes, but each shard must nevertheless have one leader node.
  - ![active-passive](./images/ddia/ddia_0501.png)
- The feature of Single-leader replication  is built-in feature of many relational database
  - PostgreSQL, MySQL, Oracle Data Guard, MongoDb, DocumentDB, message broker such as Kafka, replicated block devices, Raft, etcd, RabbitMQ quoram queue, are also based on single leader, and automatically elect a new leader if the old one fails

### Sync vs Async Replication 
- The advantage of synchronous replication is that the follower is guaranteed to have an up-to-date copy of the data that is consistent with the leader. 
  - If the leader suddenly fails, we can be sure that the data is still available on the follower. 
- The disadvantage is that if the synchronous follower doesn’t respond (because it has crashed, or there is a network fault, or for any other reason), the write cannot be processed. 
  - The leader must block all writes and wait until the synchronous replica is available again.
- In practice, if a database offers synchronous replication, it often means that one of the followers is synchronous, and the others are asynchronous.
- If the synchronous follower becomes unavailable or slow, one of the asynchronous followers is made synchronous.(how to ensure it contains latest ? or does leader choose one and make it up-to-date?)
- In some system, a majority (n / 2. + 1) replica, including leader is updated sync and remaining minority is async
  - Quorums for reading and writing
  - Majority Quorums are used in eventually consistent system (chapter 10)
- Sometimes, **leader-based replication** is configured to be completely **asynchronous**. 
  - In this case, if the leader fails and is not recoverable, any writes that have not yet been replicated to followers are lost. 
  - This means that a write is not guaranteed to be durable, even if it has been confirmed to the client. 
  - However, a fully asynchronous configuration has the advantage that the leader can continue processing writes, even if all of its followers have fallen behind.
  - Weakening durability may sound like a bad trade-off, but asynchronous replication is nevertheless widely used, especially if there are many followers or if they are geographically distributed

### Setting Up New Followers
- From time to time, you need to set up new followers—perhaps to increase the number of replicas, or to replace failed nodes. 
  - How do you ensure that the new follower has an accurate copy of the leader’s data?
- Simply copying data files from one node to another is typically not sufficient: clients are constantly writing to the database, and the data is always in flux, so a standard file copy would see different parts of the database at different points in time. The result might not make any sense.
- You could make the files on disk consistent by locking the database (making it unavailable for writes), but that would go against our goal of high availability.
- Fortunately, setting up a follower can usually be done without downtime.
- Conceptually, the process looks like this:
  - Take a consistent snapshot of the leader’s database at some point in time
    - Most databases have this feature, as it is also required for backups
  - Copy the snapshot to the new follower node.
  - The follower connects to the leader and requests all the data changes that have happened since the snapshot was taken
    - This requires that the snapshot is associated with an exact position in the leader’s replication log.
    - That position has various names: for example, PostgreSQL calls it the log sequence number; 
  - When the follower has processed the backlog of data changes since the snapshot, we say it has caught up. 

#### Databases Backed by Object Storage
- Object storage can be used for more than archiving data. Many databases are beginning to use object stores such as Amazon Web Services S3, Google Cloud Storage, and Azure Blob Storage to serve data for live queries.
- Storing database data in object storage has many benefits:
  - Object storage is inexpensive compared to other cloud storage options
  - Store less-often queried data on cheaper, higher-latency storage
  - Serving the working set from memory, SSDs, and NVMe.
  - Object stores also provide multi-zone, dual-region, or multi-region replication with very high durability guarantees.
  - Databases can use an object store’s conditional write feature
    - essentially, a compare-and-set (CAS) operation
    - to implement transactions and leadership election 
- Notably, object stores have much higher read and write latencies than local disks or virtual block devices such as EBS
- Many cloud providers also charge a per-API call fee, which forces systems to batch reads and writes to reduce cost
  - Such batching further increases latency
  - Objects are often immutable, as well, which makes random writes in a large object an extremely resource intensive operation
  - Moreover, many object stores do not offer standard filesystem interfaces
  - Interfaces such as filesystem in userspace (FUSE) allow operators to mount object store buckets as filesystems that applications can use without knowing their data is stored on object storage.
    - Still, many FUSE interfaces to object stores lack POSIX features such as non-sequential writes or symlinks, which systems might depend on

### Handling Node Outages
- Any node in the system can go down
  - Due to faults, or due to planned maintenance (updating kernel security patches)
- How do you achieve high availability with leader-based replication?

#### Follower failure: Catch-up recovery
- On its local disk, each follower keeps a log of the data changes it has received from the leader. 
- If a follower crashes and is restarted, or if the network between the leader and the follower is temporarily interrupted, the follower can recover quite easily:
  - from its log, it knows the last transaction that was processed before the fault occurred.
- Thus, the follower can connect to the leader and request all the data changes that occurred during the time when the follower was disconnected
- Although follower recovery is conceptually simple, it can be challenging in terms of performance: 
  -  if the database has a high write throughput or if the follower has been offline for a long time, there might be a lot of writes to catch up on
- The leader can delete its log of writes once all followers have confirmed that they have processed it, but if a follower is unavailable for a long time, the leader faces a choice
  - either it retains the log until the follower recovers and catches up (at the risk of running out of disk space on the leader),
  -  or it deletes the log that the unavailable follower has not yet acknowledged (in which case the follower won’t be able to recover from the log, and will have to be restored from a backup when it comes back).

#### Leader failure: Failover
- Handling a failure of the leader is trickier
  - one of the followers needs to be promoted to be the new leader
  - clients need to be reconfigured to send their writes to the new leader
  - and the other followers need to start consuming data changes from the new leader
  - This process is called **failover**.
- Failover can happen manually or automatically.
- An automatic failover process usually consists of the following steps:
  - *Determining that the leader has failed*
    -  There are many things that could potentially go wrong: crashes, power outages, network issues, and more.
    -  There is no foolproof way of detecting what has gone wrong, so most systems simply use a timeout: nodes frequently bounce messages back and forth between each other, and if a node doesn’t respond for some period of time—say, 30 seconds—it is assumed to be dead.
     - If the leader is deliberately taken down for planned maintenance, this doesn’t apply since the leader can trigger a safe handoff before shutting dow
  - *Choosing a new leader*
    -  This could be done through an election process
    -  or a new leader could be appointed by a previously established controller node
    -  The best candidate for leadership is usually the replica with the most up-to-date data changes from the old leader
  - *Reconfiguring the system to use the new leader*
    - Clients now need to send their write requests to the new leader
    - If the old leader comes back, it might still believe that it is the leader, not realizing that the other replicas have forced it to step down. 
    - The system needs to ensure that the old leader becomes a follower and recognizes the new leader.

- Failover is fraught(भरा हुआ) with things that can go wrong:
  - Asynchronous Replication and Leader Failure
    - In asynchronous replication, followers may lag behind the leader.
    - When the leader fails, some writes may exist only on the old leader.
    - These writes were:
      - Acknowledged to the client
      - Believed to be committed
      - But never replicated
    - If the old leader rejoins after a new leader is elected, the cluster must decide:
      - What to do with the old leader’s unreplicated writes?
  - Conflicting Writes After Leader Change
    - While the old leader is down:
      - The new leader may accept new writes
      - These writes may conflict with the old leader’s unreplicated data
    - There is no safe automatic merge in most single-leader systems
    - Most common sol - Discard all unreplicated writes from the old leader
    - Consequence
      - Writes that were:
        - Acknowledged
        - Appeared successful
      - Were not durable
      - This breaks a common assumption:
        - Once the DB says OK, the data is safe
  - Split Brain Scenario
    - Split brain occurs when:
      - Two nodes both believe they are the leader
      - Usually due to network partition or delayed failure detection
    - Both leaders may: Accept writes, Modify the same data independently
    - Without conflict resolution: Data loss, Data corruption, Inconsistent state across replicas
    - Safety Mechanisms Against Split Brain
      - Systems may try to: Detect multiple leaders, Force one leader to shut down (fencing) 
      - Shoot The Other Node In The Head (STONITH)
      - If poorly designed: Both nodes may shut down
- Asynchronous replication trades performance for weaker durability
- Leader failover can cause:
  - Silent data loss
  - Reuse of identifiers
  - Cross-system inconsistency (Cache, Database)
- What is the right timeout before the leader is declared dead? A longer timeout means a longer time to recovery in the case where the leader fails
  -  However, if the timeout is too short, there could be unnecessary failovers.
  -  For example, a temporary load spike could cause a node’s response time to increase above the timeout, or a network glitch could cause delayed packets. If the system is already struggling with high load or network problems, an unnecessary failover is likely to make the situation worse, not better.
- There are no easy solutions to these problems. For this reason, some operations teams prefer to perform failovers manually, even if the software supports automatic failover.

### Implementation of Replication Logs
How does leader-based replication work under the hood? 
#### Statement-based replication
- In the simplest case, the leader logs every write request (statement) that it executes and sends that statement log to its followers. 
- For a relational database, this means that every `INSERT`, `UPDATE`, or `DELETE` statement is forwarded to followers, and each follower parses and executes that SQL statement as if it had been received from a client.
- Although this may sound reasonable, there are various ways in which this approach to replication can break down:
  - Any statement that calls a nondeterministic function, such as `NOW()` to get the current date and time or `RAND()` to get a random number, is likely to generate a different value on each replica.
  - If statements use an autoincrementing column, or if they depend on the existing data in the database (e.g., `UPDATE` …​ `WHERE` <some condition>), they must be executed in exactly the same order on each replica, or else they may have a different effect. This can be limiting when there are multiple concurrently executing transactions.
  - Statements that have side effects (e.g., triggers, stored procedures, user-defined functions) may result in different side effects occurring on each replica, unless the side effects are absolutely deterministic.
- It is possible to work around those issues—for example, the leader can replace any nondeterministic function calls with a fixed return value when the statement is logged so that the followers all get the same value.
- The idea of executing deterministic statements in a fixed order is also known as state machine replication

#### Write-ahead log (WAL) shipping
- Idea of WAL is simple yet powerful - *Never modify a data page on disk until you have written a description of that change to the WAL*. 
- So that in case if database crash happen, the first thing database will do is to open WAL. Scan from the last checkpoint. Replays changes (apply x to page y). This will make the on-disk data structure B-Tree into a consistent state.
  - This is called **redo** logs
- WAL can re-build the entire database after a crash. Therefore it must contain all information to construct the data
- We can use the exact same log to build replica on another node: beside writing the log to the disk, the leader can also send it to the network to its followers.
  - When the follower processes this log, it builds a copy of exact same file as found on the leader
- This method of replication is used in PostGres, Oracle
- The main disadvantage is the log describe the data on very low-level: a WAL contains details of which byte were changed on the disk on which block. 
- This makes **replication tighly coupled to the storage engine**.
- If the database changes its storage format from one version to another, it is typically not possible to run different version of the database software on the leader and followers
- That may seem like a minor implementation detail, but it can have a big operational impact.

#### Logical (row-based) log replication
- An alternative is to use different log formats for replication and for the storage engine, which allows the replication log to be **decoupled from the storage engine internals**.
- This kind of replication log is called a logical log, to distinguish it from the storage engine’s (physical) data representation.
- A logical log for a relational database is usually a sequence of records describing writes to database tables at the granularity of a row:
  - For an inserted row, the log contains the new values of all columns.
  - For a deleted row, the log contains enough information to uniquely identify the row that was deleted. Typically this would be the primary key, but if there is no primary key on the table, the old values of all columns need to be logged.
  - For an updated row, the log contains enough information to uniquely identify the updated row, and the new values of all columns (or at least the new values of all columns that changed).
- A transaction that modifies several rows generates several such log records, followed by a record indicating that the transaction was committed. 
- MySQL keeps a separate logical replication log, called the binlog, in addition to the WAL (when configured to use row-based replication).
-  PostgreSQL implements logical replication by decoding the physical WAL into row insertion/update/delete events
-  Since a logical log is decoupled from the storage engine internals, it can more easily be kept backward compatible, allowing the leader and the follower to run different versions of the database software.
   -  This in turn enables upgrading to a new version with minimal downtime
- A logical log format is also easier for external applications to parse.
- This aspect is useful if you want to send the contents of a database to an external system, such as a data warehouse for offline analysis, or for building custom indexes and caches (more in chapter 12 - stream processing)

### Problems with Replication Lag
- The reason we are doing replication - tolerate node failures, scalability (process more request) and latency (placing replicas closer to users)
- Leader-based replication requires all writes to go through a single node, but read-only queries can go to any replica.
  - Attractive chioce in case of - Mostly read and small writes
- In this read-scaling architecture, you can increase the capacity for serving read-only requests simply by adding more followers
- However, this approach only realistically works with asynchronous replication—if you tried to synchronously replicate to all followers, a single node failure or network outage would make the entire system unavailable for writing.
  - And the more nodes you have, the likelier it is that one will be down, so a fully synchronous configuration would be very unreliable.
- Unfortunately, if an application reads from an asynchronous follower, it may see outdated information if the follower has fallen behind.
- This leads to apparent inconsistencies in the database
  - leader and a follower at the same time, you may get different results
- This inconsistency is just a temporary state—if you stop writing to the database and wait a while, the followers will eventually catch up
- The term “eventually” is deliberately vague: in general, there is no limit to how far a replica can fall behind.
- From next section we will highlight - Problems due to lag 

#### Reading Your Own Writes
- Many applications let the user submit some data and then view what they have submitted.
- In case of async replication this view can break. If the read query goes to a node which is lagging behind
- How can we implement read-after-write consistency in a system with leader-based replication?
  - When reading something that the user may have modified, read it from the leader or a **synchronously** updated follower; otherwise, read it from an asynchronously updated follower
  - This requires that you have some way of knowing whether something might have been modified, without actually querying it.
  - For example, user profile information on a social network is normally only editable by the owner of the profile, not by anybody else. Thus, a simple rule is: always read the user’s own profile from the leader, and any other users’ profiles from a follower.
  - If most things in the application are potentially editable by the user, that approach won’t be effective, as most things would have to be read from the leader
  - The client can remember the timestamp of its most recent write - then the system can ensure that the replica serving any reads for that user reflects updates at least until that timestamp
    - The timestamp could be a logical timestamp or the actual system clock
  - Another complication arises when the same user is accessing your service from multiple devices, for example a desktop web browser and a mobile app.
  -  In this case you may want to provide cross-device read-after-write consistency
  -  In this case, there are some additional issues to consider:
     -  Approaches that require remembering the timestamp of the user’s last update become more difficult. This metadata will need to be centralized.
     -  If your replicas are distributed across different regions, there is no guarantee that connections from different devices will be routed to the same region.

#### Monotonic Reads
- Our second example of an anomaly that can occur when reading from asynchronous followers is that it’s possible for a user to see things moving backward in time.
- Monotonic reads is a guarantee that this kind of anomaly does not happen.
- It’s a lesser guarantee than strong consistency, but a stronger guarantee than eventual consistency
- When you read data, you may see an old value; monotonic reads only means that if one user makes several reads in sequence, they will not see time go backward
- One way of achieving monotonic reads is to make sure that each user always makes their reads from the same replica 
  -  However, if that replica fails, the user’s queries will need to be rerouted to another replica.

#### Consistent Prefix Reads
- Violation of causality (happens-before relation)
  - If event A influences event B, then A must be seen before B by everyone.
- Scenario: messaging
  - Alice sends:
    - Message 1 - “I got the job!”
    - Message 2 - “Let’s celebrate” (clearly depends on Message 1)
- Preventing this kind of anomaly requires another type of guarantee: consistent prefix reads
- This guarantee says that if a sequence of writes happens in a certain order, then anyone reading those writes will see them appear in the same order.
- This is a particular problem in sharded (partitioned) databases
- In many distributed databases, different shards operate independently, so there is no global ordering of writes
  - When a user reads from the database, they may see some parts of the database in an older state and some in a newer state.

#### Solutions for Replication Lag
- When working with an eventually consistent system, it is worth thinking about how the application behaves if the replication lag increases to several minutes or even hours. 
-  If the answer is “no problem,” that’s great. 
-  However, if the result is a bad experience for users, it’s important to design the system to provide a stronger guarantee, such as read-after-write.
-  As discussed earlier, there are ways in which an application can provide a stronger guarantee than the underlying database.  However, dealing with these issues in application code is complex and easy to get wrong.
- The simplest programming model for application developers is to choose a database that provides a strong consistency guarantee for replicas such as linearizability 
- Even though scalable, strongly consistent distributed databases are now available, there are still good reasons why some applications choose to use different forms of replication that offer weaker consistency guarantees

> Regions and Availability Zones
> 
> A region is a geographic area that contains multiple datacenters.
>
> Each datacenter within a region is called an availability zone (zone).
>
> Zones are physically separate (independent power, cooling, etc.) but connected with very fast, low-latency networks.
>
> Systems can safely run across multiple zones in the same region to survive zone-level failures.
>
> This setup does not protect against a full regional outage.
>
> To survive regional outages, systems must run across multiple regions, which increases latency, cost, and complexity.

### Multi-Leader Replication
- Single-leader replication has one major downside: all writes must go through the one leader
- A natural extension of the single-leader replication model is to allow more than one node to accept writes. 
- We call this a multi-leader configuration (also known as active/active or bidirectional replication).
- In this setup, each leader simultaneously acts as a follower to the other leaders.
- Synchronous replication practically yields no gain, thus we will not discuss that in the multi-leader replication 

#### Geographically Distributed Operation
- It rarely makes sense to use a multi-leader setup within a single region, because the benefits rarely outweigh the added complexity.
- Imagine you have a database with replicas in several different regions
  - This is known as a geographically distributed, geo-distributed or geo-replicated setup
- With single-leader replication, the leader has to be in one of the regions, and all writes must go through that region.
- In a multi-leader configuration, you can have a leader in each region
    ![Multi leader](./images/ddia/multi-leader.png)
- Let’s compare how the single-leader and multi-leader configurations fare in a multi-region deployment:
  - Performance
    - In a single-leader configuration, every write must go over the internet to the region with the leader. Adds significant latency
    - In a multi-leader configuration, every write can be processed in the local region and is replicated asynchronously to the other regions
  - Tolerance of regional outages
    - In a single-leader configuration, if the region with the leader becomes unavailable, failover can promote a follower in another region to be leader.
    -  In a multi-leader configuration, each region can continue operating independently of the others, and replication catches up when the offline region comes back online.
 -  Tolerance of network problems
    -  Even with dedicated connections, traffic between regions can be less reliable than traffic between zones in the same region or within a single zone
    -  A multi-leader configuration with asynchronous replication can tolerate network problems better: during a temporary network interruption, each region’s leader can continue independently processing writes.
 -  Consistency
    -  A single-leader system can provide strong consistency guarantees, such as serializable transactions (form of isolation)
    -  The biggest downside of multi-leader systems is that the consistency they can achieve is much weaker.
       -  For example, you can’t guarantee that a bank account won’t go negative or that a username is unique
       -  it’s always possible for different leaders to process writes that are individually fine
    -  This is simply a fundamental limitation of distributed systems
    -  If you need to enforce such constraints, you’re therefore better off with a single-leader system
-  Multi-leader replication is less common than single-leader replication, but it is still supported by many databases, including MySQL, Oracle, SQL Server, and YugabyteDB
-  As multi-leader replication is a somewhat retrofitted feature in many databases, there are often subtle configuration pitfalls and surprising interactions with other database features.
   -  For example, autoincrementing keys, triggers, and integrity constraints can be problematic. 
-  Multi-leader replication is often considered dangerous territory that should be avoided if possible

#### Multi-leader replication topologies
- A replication topology describes the communication paths along which writes are propagated from one node to another.
- The most general topology is all-to-all
  - every leader sends its writes to every other leader
- However, more restricted topologies are also used: for example a circular topology in which each node receives writes from one node and forwards those writes (plus any writes of its own) to one other node. 
- Another popular topology has the shape of a star: one designated root node forwards writes to all of the other nodes. The star topology can be generalized to a tree.
- To prevent infinite replication loops, each node is given a unique identifier, and in the replication log, each write is tagged with the identifiers of all the nodes it has passed through

##### Problems with different topologies
- A problem with circular and star topologies is that if just one node fails, it can interrupt the flow of replication messages between other nodes, leaving them unable to communicate until the node is fixed.

#### Sync Engines and Local-First Software
- Another situation in which multi-leader replication is appropriate is if you have an application that needs to continue to work while it is disconnected from the internet.
- The app must work even when there is no internet.
  - You must be able to read data offline
  - You must be able to write data offline
  - Changes must sync later when connectivity returns
- This is called local-first software.
- Why single-leader replication does NOT work here
  - In a classic single-leader database:
  - All writes go to one leader
  - If you cannot reach the leader, you can't write
- Now think about your phone in airplane mode:
  - No network, Leader unreachable
  - So You cannot add a calendar event. This is unacceptable for offline apps.
- The key idea: every device has its own local database
  - Each device: Phone, laptop, Tablet
  - Has: A local database, Stored on disk, Always available
- So when you:
  - Create a calendar event on your phone while offline
    - it is written locally, immediately
  - No server involved at that moment.
- Why “every device is a leader”
  - A leader is simply a node that accepts writes
  - Since your phone accepts writes while offline… your phone must be leader
  - This is multi-leader replication.
- What happens when you go back online?
  - Devices start syncing changes. Sync is asynchronous. No device blocks waiting for another
- Example timeline:
  - Phone (offline):
    - Add meeting “Doctor at 5 PM”
  - Laptop (online):
    - Add meeting “Team sync at 3 PM”
  - Later, phone connects to internet:
    - Phone sends its changes
    - Laptop/server send their changes
  - Both merge updates
- From an architectural point of view, this setup is very similar to multi-leader replication between regions, taken to the extreme: each device is a “region,” and the network connection between them is extremely unreliable.

#### Real-time collaboration, offline-first, and local-first apps
- Moreover, many modern web apps offer real-time collaboration features, such as Google Docs and Sheets for text documents and spreadsheets, Figma for graphics, and Linear for project management.
- What makes these apps so responsive is that user input is immediately reflected in the user interface, without waiting for a network round-trip to the server, and edits by one user are shown to their collaborators with low latency
- This again results in a multi-leader architecture: 
  - each web browser tab that has opened the shared file is a replica, and any updates that you make to the file are asynchronously replicated to the devices of the other users who have opened the same file. 
- Even if the app does not allow you to continue editing a file while offline, the fact that multiple users can make edits without waiting for a response from the server already makes it multi-leader
- Both offline editing and real-time collaboration require a similar replication infrastructure: 
  - the application needs to capture any changes that the user makes to a file, and either send them to collaborators immediately (if online), or store them locally for sending later (if offline)
- Additionally, the application needs to receive changes from collaborators, merge them into the user’s local copy of the file, and update the user interface to reflect the latest version
-  If multiple users have changed the file concurrently, conflict resolution logic may be needed to merge those changes.
-  A software library that supports this process is called a sync engine. 
-  An application that allows a user to continue editing a file while offline is called offline-first
-  For example, Git is a local-first collaboration system since you can sync via GitHub, or any other repository hosting service.

##### Pros and cons of sync engines
- The dominant way of building web apps today is to keep very little persistent state on the client. In contrast sync engine, you have to persistent state on the client
- Having the data locally means the user interface can be much faster to respond than if it had to wait for a service call to fetch some data.
  - Some apps aim to respond to user input in the next frame of the graphics system, which means rendering within 16 ms on a display with a 60 Hz refresh rate.
- Allowing users to continue working while offline is valuable, especially on mobile devices with intermittent connectivity. 
- A sync engine simplifies the programming model for frontend apps, compared to performing explicit service calls in application code. 

#### Dealing with Conflicting Writes
- A conflict happens when: 
  - Two leaders accept writes independently
  - Both writes modify the same piece of data
  - Neither write knows about the other at the time it is made
- Both writes are valid locally, but incompatible globally.
- This problem exists only in multi-leader systems
- For now we will assume that we can detect conflicts, and we want to figure out the best way of resolving them.

##### Conflict avoidance
- One strategy for conflicts is to avoid them occurring in the first place
-  If the application can ensure that all writes for a particular record go through the same leader, then conflicts cannot occur, even if the database as a whole is multi-leader
   -  This approach is not possible in the case of a sync engine client being updated offline (as leader can write independent and that's the design), but it is sometimes possible in geo-replicated server systems
- Conflict avoidance can fail if the designated leader for a record changes, because a write during the transition can create conflicts.
- Leader changes may happen due to region failures or users moving closer to another region.
- Conflict avoidance works only while leader ownership is stable.
- Another example of conflict avoidance: imagine you want to insert new records and generate unique IDs for them based on an auto-incrementing counter
  - Another way to avoid conflicts is partitioning responsibility, such as having two leaders generate IDs from disjoint ranges (e.g., one uses odd numbers, the other even), ensuring no duplicate IDs are created concurrently.

##### Last write wins (discarding concurrent writes)
- When conflicts cannot be avoided, the simplest resolution strategy is last write wins (LWW).
  - Each write is assigned a timestamp, and when replicas detect a conflict, they keep the value with the largest timestamp and discard the others.
- The name last write wins is misleading. In the case of concurrent writes, there is no well-defined “last” write in real time
  - The ordering is effectively arbitrary, so LWW really means that one of the concurrent writes is chosen at random and the others are silently dropped
- LWW guarantees that replicas eventually reach a consistent state, but it does so by losing data
  - This is acceptable only when conflicts are impossible or harmless
- A further problem with LWW arises when physical clocks are used
  -  If one node’s clock is ahead of others, its writes may permanently dominate, causing later writes from other nodes to be ignored even though they occurred later in real time.
  -  This clock-sensitivity can be mitigated by using logical clocks, which avoid reliance on synchronized wall-clock time.

> LWW resolves conflicts by arbitrarily choosing one concurrent write and discarding the rest, ensuring convergence at the cost of potential data loss and sensitivity to clock skew.


##### Manual Conflict Resolution 
- If losing writes (as in last-write-wins) is unacceptable, conflicts can be resolved manually, similar to how version control systems like Git handle merge conflicts.
  - When concurrent updates modify the same data, the conflict must be resolved explicitly.
- In databases, replication cannot pause waiting for a human.
- Instead, the database stores all concurrent versions of a record (called siblings) and returns them together on reads.
- The application then resolves the conflict, either automatically (for example, merging values) or by asking the user, and writes back a single resolved value.
- This approach is used in systems such as CouchDB, but it has several drawbacks:
  - API complexity: a field that was previously a single value now becomes a set of values, which complicates application code.
  - User burden: manual resolution requires extra UI and can confuse users; automatic merging is often preferable.
  - Risky automatic merges: naive merging can cause incorrect behavior. For example, Amazon once merged shopping carts by taking the union of items, which caused removed items to reappear when concurrent updates occurred.
  - Resolution conflicts: if multiple nodes resolve the same conflict independently, their resolutions may differ, creating new conflicts (e.g., merging into “B/C” vs “C/B”), which can cascade into even more confusing results.
- Manual conflict resolution preserves data but increases complexity, can confuse users, and may itself create new conflicts if not handled carefully.


##### Automatic conflict resolution
- The goal is convergence: all replicas that process the same set of writes end up in the same state, regardless of the order in which the writes arrive.
  -  Eventual consistency combined with this guarantee is called strong eventual consistency.
- Text data (e.g., wiki pages): insertions and deletions are tracked and merged so that all edits are preserved. Concurrent inserts at the same position are ordered deterministically.
- Collections (e.g., to-do lists or shopping carts): insertions and deletions are tracked explicitly, so removed items stay removed and do not reappear after merging.
- Counters (e.g., likes): increments and decrements from all replicas are combined correctly, avoiding lost or double-counted updates.
- Key-value maps: conflicts are resolved per key, applying appropriate merge logic to each value independently.
- Nevertheless, automatic conflict resolution is sufficient to build many useful apps. 
  - And if you start from the requirement of wanting to build a collaborative offline-first or local-first app, then conflict resolution is inevitable, and automating it is often the best approach.

#### CRDTs and Operational Transformation
- Two families of algorithms are commonly used to implement automatic conflict resolution
  -  Conflict-free replicated datatypes (CRDTs)
  -  Operational Transformation (OT)

![CRDT and OT](./images/ddia/ot-crdt.png)

- OT 
  - We record the index at which characters are inserted or deleted: “n” is inserted at index 0, and “!” at index 3. 
  - Next, the replicas exchange their operations. The insertion of “n” at 0 can be applied as-is, but if the insertion of “!” at 3 were applied to the state “nice” we would get “nic!e”, which is incorrect. 
  - We therefore need to transform the index of each operation to account for concurrent operations that have already been applied; in this case, the insertion of “!” is transformed to index 4 to account for the insertion of “n” at an earlier index.
- CRDT
  - Most CRDTs give each character a unique, immutable ID and use those to determine the positions of insertions/deletions, instead of indexes.
  - Concurrent insertions at the same position are ordered by the IDs of the characters. This ensures that replicas converge without performing any transformation.
- OT is most often used for real-time collaborative editing of text, e.g. in Google Docs
- CRDTs can be found in distributed databases such as Redis Enterprise, Riak, and Azure Cosmos DB


## Chapter 6. Partitioning

## Chapter 7. Transaction 

### Introduction
- A transaction is a way for an application to group several reads and writes together into a logical unit.
- Conceptually, all the reads and writes in a transaction are executed as one operation: either the entire transaction succeeds (commit) or it fails (abort, rollback). If it fails, the application can safely retry.
- With txn in place error handling becomes much simpler for the applications, because they don't really need to worry about partial failures
- Transactions are not a law of nature; they were created with a purpose, namely to simplify the programming model for applications accessing a database
- How do you figure out whether you need transactions? In order to answer that question, we first need to understand exactly what safety guarantees transactions can provide, and what costs are associated with them. 
- We will go especially deep in the area of concurrency control, discussing various kinds of race conditions that can occur and how databases implement isolation levels such as **read committed**, **snapshot isolation**, and **serializability**.
- We will examine the two-phase commit protocol and the challenge of achieving atomicity in a distributed transaction.

### The meaning of ACID 
- The safety guarantees provided by transactions are often described by the well-known acronym ACID
- However, A programmer should see ACID as *(AC=Linearizability)*, *(I=Serializability)* D. [Read more here](https://github.com/souraavv/whitepapers-and-books/blob/main/whitepapers/google-spanner.md#serializability-versus-linearizability) 

#### Atomicity
- The atomic is used at multiple place and has several meanings
  - Like in multi-threaded program, if one thread execute an atomic operation, that means there is no way the other thread can see the half-finished operations
  - By contrast, in the context of ACID, atomicity is not about concurrency
  - It doesn't describe what happens if several processes try to access the same data at the same time, because that is covered under letter 'I' Isolation 
  - Rather, ACID atomicity describes what happens if a client wants to make several writes, but a fault occurs after some of the writes have been processed
- If the writes are grouped together into an atomic transaction, and the txn cannot complete (i.e., not commited) due to fault, then the txn is aborted and database must discard any write it has made so far in that tx
- Perhaps abortability would have been a better term than atomicity

#### Consistency
- Similar to A, C is also over-loaded
- The idea of ACID **consistency** is that you have certain statements about your data (invariants) that must always be true
- An invariant may be temporarily violated during transaction execution, but it should be satisfied again at transaction commit.
- If you want the database to enforce your invariants, you need to declare them as constraints as part of the schema e.g.,  foreign key constraints, uniqueness constraints, or check constraints
- More complex consistency requirements can sometimes be modeled using triggers or materialized views
- However, complex invariants can be difficult or impossible to model using the constraints that databases usually provide.
- In that case, it’s the application’s responsibility to define its transactions correctly so that they preserve consistency.
- As such, the C in ACID often depends on how the application uses the database, and it’s not a property of the database alone.

#### Isolation
- Most databases are accessed by several clients at the same time. That is no problem if they are reading and writing different parts of the database, but if they are accessing the same database records, you can run into concurrency problems (race conditions).
- Isolation in the sense of ACID means that concurrently executing transactions are isolated from each other: they cannot step on each other’s toes.
- The classic database textbooks formalize isolation as serializability, which means that each transaction can pretend that it is the only transaction running on the entire database.
- The database ensures that when the transactions have committed, the result is the same as if they had run serially (one after another), even though in reality they may have run concurrently 
- However, serializability has a performance cost. In practice, many databases use forms of isolation that are weaker than serializability: that is, they allow concurrent transactions to interfere with each other in limited ways.
-  Oracle, don’t even implement it (Oracle has an isolation level called “serializable,” but it actually implements snapshot isolation, which is a weaker guarantee than serializability)
   - Imagine har transaction ko database ka snapshot milta hai jab wo start hoti hai.
   - Us transaction ke saare reads usi snapshot ke according honge
   - Snapshot Isolation phantoms aur write skew ko nahi pakadta (In later section we will see what is Phantom and write skew issue)

#### Durability
- Durability is the promise that once a transaction has committed successfully, any data it has written will not be forgotten, even if there is a hardware fault or the database crashes
- Many databases therefore use the fsync() system call to ensure the data really has been written to disk. 
- Databases usually also have a write-ahead log or similar, which allows them to recover in the event that a crash occurs part way through a write. [See more](https://github.com/souraavv/whitepapers-and-books/discussions/5#discussioncomment-14540651)
- Perfect durability does not exist: if all your hard disks and all your backups are destroyed at the same time, there’s obviously nothing your database can do to save you.

### Single-Object and Multi-Object Operations
- Multi-object transactions require some way of determining which read and write operations belong to the same transaction
- In relational databases, that is typically done based on the client’s TCP connection to the database server: on any particular connection, everything between a `BEGIN TRANSACTION` and a `COMMIT` statement is considered to be part of the same transaction
- If the TCP connection is interrupted, the transaction must be aborted.
- On the other hand, many nonrelational databases don’t have such a way of grouping operations together. Even if there is a multi-object API (for example, a key-value store may have a multi-put operation that updates several keys in one operation), that doesn’t necessarily mean it has transaction semantics

#### Single-object writes
- Atomicity and isolation also apply when a single object is being changed. For example, imagine you are writing a 20 KB JSON document to a database:
  - If network connection abort ?
  - Power failure where database is running ?
  - Another client read the data ?
- Those issues would be incredibly confusing, so storage engines almost universally aim to provide atomicity and isolation on the level of a single object 
- Atomicity can be implemented using a log for crash recovery 
- And isolation can be implemented using a lock on each object 
- Similarly popular is a conditional write operation, which allows a write to happen only if the value has not been concurrently changed by someone else (compare-and-set)
- Strictly speaking, the term atomic increment uses the word atomic in the sense of multi-threaded programming. In the context of ACID, it should actually be called an isolated or serializable increment, but that’s not the usual term.
- These single-object operations are useful, as they can prevent lost updates when several clients try to write to the same object concurrently (preventing lost updates)

#### The need for multi-object transactions
- There are some use cases in which single-object inserts, updates, and deletes are sufficient. However, in many other cases writes to several different objects need to be coordinated:
  - In a relational data model, a row in one table often has a foreign key reference to a row in another table. 
  - Similarly, in a graph-like data model, a vertex has edges to other vertices. 
  - In databases with secondary indexes (almost everything except pure key-value stores), the indexes also need to be updated every time you change a value. These indexes are different database objects from a transaction point of view: 

#### Handling errors and aborts
- A key feature of a transaction is that it can be aborted and safely retried if an error occurred
- If the transaction actually succeeded, but the network was interrupted while the server tried to acknowledge the successful commit to the client (so it timed out from the client’s point of view), then retrying the transaction causes it to be performed twice—unless you have an additional application-level deduplication mechanism in place.
- If the error is due to overload or high contention between concurrent transactions, retrying the transaction will make the problem worse, not better
  - It is only worth retrying after transient errors (for example due to deadlock, isolation violation, temporary network interruptions, and failover); after a permanent error (e.g., constraint violation) a retry would be pointless.
- If the transaction also has side effects outside of the database, those side effects may happen even if the transaction is aborted. For example, if you’re sending an email, you wouldn’t want to send the email again every time you retry the transaction. 
  - If you want to make sure that several different systems either commit or abort together, two-phase commit can help


### Weak Isolation Levels
- If two transactions don’t access the same data, or if both are read-only, they can safely be run in parallel, because neither depends on the other. 
- Concurrency issues (race conditions) only come into play when one transaction reads data that is concurrently modified by another transaction, or when the two transactions try to modify the same data.
- Concurrency bugs are hard to find by testing, because such bugs are only triggered when you get unlucky with the timing. 
- For that reason, databases have long tried to hide concurrency issues from application developers by providing *transaction isolation*
  - In theory, isolation should make your life easier by letting you pretend that no concurrency is happening
  - serializable isolation means that the database guarantees that transactions have the same effect as if they ran serially (i.e., one at a time, without any concurrency).
- In practice, isolation is unfortunately not that simple.
- Serializable isolation has a performance cost, and many databases don’t want to pay that price 
- In practice several weak isolation levels that are used

### Read Committed
- The most basic level of transaction isolation is read committed. Two gurantees
  - When reading from the database, you will only see data that has been committed (no dirty reads).
  - When writing to the database, you will only overwrite data that has been committed (no dirty writes).
- Some databases support an even weaker isolation level called read uncommitted. It prevents dirty writes, but does not prevent dirty reads. Let’s discuss these two guarantees in more detail

#### Implementing read committed
- Read committed is a very popular isolation level. It is the default setting in Oracle Database, PostgreSQL, SQL Server, and many other databases
- Most commonly, databases prevent dirty writes by using row-level locks: when a transaction wants to modify a particular row (or document or some other object), it must first acquire a lock on that row. 
-  It must then hold that lock until the transaction is committed or aborted.
-  Only one transaction can hold the lock for any given row; if another transaction wants to write to the same row, it must wait until the first transaction is committed or aborted before it can acquire the lock and continue.
- This locking is done automatically by databases in read committed mode (or stronger isolation levels).
- However, the approach of requiring read locks does not work well in practice, because one long-running write transaction can force many other transactions to wait until the long-running transaction has completed, even if the other transactions only read and do not write anything to the database (harms response time)
- A more commonly used approach to preventing dirty reads is the one  for every row that is written, the database remembers both the old committed value and the new value set by the transaction that currently holds the write lock.
- While the transaction is ongoing, any other transactions that read the row are simply given the old value
- Only when the new value is committed do transactions switch over to reading the new value  (MVCC)

### Snapshot Isolation, repeatable read, and naming confusion
- MVCC is a commonly used implementation technique for databases, and often it is used to implement snapshot isolation
- . However, different databases sometimes use different terms to refer to the same thing: for example, snapshot isolation is called "repeatable read" in PostgreSQL, and "serializable" in oracle
- Unfortunately, the SQL standard’s definition of isolation levels is flawed—it is ambiguous, imprecise, and not as implementation-independent as a standard should be

### Preventing Lost Updates
- Happens in read-modify-write cycles
- If two transactions do this concurrently, one modification may be lost (later write overwrites earlier one).

#### Atomic Write Operation 
- Database provide this feature atomic update operations
- Best solution if the update can be expressed as an atomic operation.
- But sometimes operation is not as straight forward, think of scnearios where concurrent writes are happening on Google doc, two user are editing page concurrently, we need CRDT (Conflict-Free Replicated Data Type)
- Atomic operations are usually implemented by taking an exclusive lock on the object when it read so that no other txn can read it until the update has been applied
  - Another option is to simply force all atomic operation to be executed on single thread (this can be trick interview question)
- Unfortunately, ORM (object-relation model) frameworks make it easy to accidently write code that performs unsafe read-modify-write cycles instead of using atomic operation provided by database

#### Explicity Locking
- Another simple option to prevent lost updates
- But remember there are changes of getting into deadlock if multiple object are attempted to lock, although database automatically detect deadlocks, and abort one of the involved txn so that system can make progress

#### Automatically detecting lost updates
- Atomic operations and locks are ways of preventing lost updates by forcing the read-modify-write cycles to happen sequentially.
- An alternative is to allow them to execute in parallel and, if the transaction manager detects a lost update, abort the transaction and force it to retry its read-modify-write cycle.
- Lost update detection is a great feature, because it doesn’t require application code to use any special database features—you may forget to use a lock or an atomic operation and thus introduce a bug, but lost update detection happens automatically and is thus less error-prone. However, you also have to retry aborted transactions at the application level.
  - Something like watch in Redis

#### Conditional writes (compare-and-set) CAS
- Some databases (without full transactions) provide conditional writes.
- Prevents lost updates by allowing update only if value hasn’t changed since last read
- Equivalent to atomic compare-and-set (CAS) at the CPU level.
    ```sql
    UPDATE wiki_pages 
    SET content = 'new content'
    WHERE id = 1234 AND content = 'old content';
    ```
- Must check if update succeeded; if not, retry **read-modify-write** cycle.
- Alternative approach:
  - Use a version number column (incremented on every update).
  - Update applies only if version matches the one you last read.
  - This is known as **optimistic** locking.

>[!IMPORTANT]
> Important MVCC note:
> 
> Under MVCC (Multi-Version Concurrency Control), normally you only see values visible to your snapshot.
> But many implementations make an exception:
> Writes from other concurrent transactions are visible in the WHERE clause of UPDATE/DELETE.
> Otherwise, CAS-style checks would not work.
>

- CAS doesn't work in case of replicated systems
  - Multiple replica may accept write concurrently

##### How Replication Handles Lost Updates
- Allow concurrent writes to create conflicting versions
- Use application logic or special data structures to resolve/merge later.
- If updates are commutative:
  - Order of applying doesn’t matter → safe merge.
  - Examples:
    - Increment counter.
    - Add element to a set.
  - Basis of CRDTs (Conflict-Free Replicated Data Types).
  - Note both of the above operation are monotonic (also called G-SET) in nature i.e., if you allow negation or removal of element of set (also called U-SET) then that will not straight-forward
- Other simplest is LWW (Last Write Win)
  - But prone to lost update
  - But most replicated database implement this 

### Write Skew and Phantoms
- We have already seen dirty write and lost updates (both involves multiple txns updating the same object)
  - Dirty write become serious problem in case if uncommited work by txn which is over-wrote can abort
  - Lost update can misses out the update of one of the writer
- But more subtle anomalies exist when *different objects* are *updated concurrently*
- Example
  - Doctor On-Call Example (Write Skew)
    - Rule: Hospital must always have at least one doctor on call.
    - Doctors A and B are both on call.
    - Both fall sick and independently request leave at the same time.
  - Transaction logic:
    - Each transaction checks: "≥ 2 doctors are on call" → true (both see 2).
    - Each removes themselves.
    - Both commit → result: 0 doctors on call, violating the rule.

#### What is Write Skew?
- Not a dirty write, Not a lost update
- Conflict arises only under concurrency – if run sequentially, second transaction would be blocked.

#### Why it is tricky to prevent
- Atomic single-object ops don’t help (multiple objects involved).
- Requires true serializable isolation to be automatically prevented.

#### Possible Solutions
- Serializable isolation: strongest guarantee, prevents write skew.
- Database constraints:
  - Useful if you can express the rule
  - Or Workarounds: triggers, materialized views
    - Like you can write a rule function `check_on_call`, before update, delete on doctors table (directly validate the invariant on each update.) 
        ```sql
        CREATE OR REPLACE FUNCTION check_on_call()
        RETURNS trigger AS $$
        DECLARE
        cnt INTEGER;
        BEGIN
        -- Count how many doctors would still be on call after this change
        SELECT COUNT(*) INTO cnt
        FROM doctors
        WHERE shift_id = NEW.shift_id
            AND on_call = true
            AND doctor_id <> NEW.doctor_id;

        -- If no one else is left on call, reject this update
        IF cnt = 0 AND NEW.on_call = false THEN
            RAISE EXCEPTION 'Cannot take last doctor off call for shift %', NEW.shift_id;
        END IF;

        RETURN NEW;
        END;
        $$ LANGUAGE plpgsql;

        CREATE TRIGGER enforce_on_call
        BEFORE UPDATE ON doctors
        FOR EACH ROW
        WHEN (OLD.on_call = true AND NEW.on_call = false)
        EXECUTE FUNCTION check_on_call();
        ```
    - Under weaker isolation levels, race conditions can still slip through unless the trigger’s internal query locks rows or forces serialization
    - A materialized view is a stored query result (like a snapshot table) that can be refreshed automatically or transactionally (tracks the invariant explicitly)
        ```sql
        CREATE MATERIALIZED VIEW shift_on_call_counts AS
        SELECT shift_id, COUNT(*) AS num_on_call
        FROM doctors
        WHERE on_call = true
        GROUP BY shift_id;
        ```
    - Then, you enforce a CHECK constraint on this view or on a companion summary table:
        ```sql
        ALTER TABLE shift_on_call_counts
        ADD CONSTRAINT at_least_one_on_call CHECK (num_on_call >= 1);
        ```
- Explicity locking
  - Manually lock all rows your transaction depends on.
  - FOR UPDATE locks rows → ensures no concurrent modification
    ```sql
    BEGIN TRANSACTION;

    SELECT * FROM DOCTORS
    WHERE ON_CALL=TRUE
    AND SHIFT_ID=1234 FOR UPDATE;

    UPDATE DOCTORS
    SET ON_CALL=FALSE
    WHERE NAME='A'
    AND SHIFT_ID=1234

    COMMIT;

    ```
- More example
  - Meeting Room Booking
  - Multiplayer Game
  - Username Claiming
  - Preventing Double-Spending

### Phantoms(काल्पनिक) Causing Write Skew

#### General Pattern of These Anomalies
- Across doctor shifts, meeting bookings, usernames, money accounts, multiplayer games:
  - **Step 1**: A transaction does a SELECT to check some requirement/precondition.
    - Examples:
      - ≥ 2 doctors on call
      - No booking for this room/time.
      - Position not occupied.
      - Username not taken.
      - Balance not negative.
  - **Step 2**: Based on the check, application decides to proceed or abort
  - **Step 3**: Transaction performs a write (`INSERT`, `UPDATE`, `DELETE`).
  - **Step 4**: That write changes the precondition of step 1.
- This is a race condition

#### Phantoms Explained
- A phantom = a situation where one transaction’s write changes the result set of another transaction’s query.
- Not just overwriting an existing row, but creating or deleting rows that match the query condition.
- Example:
  - T1 checks “any booking for noon?” → sees none.
  - T2 concurrently inserts a booking at noon.
  - Now T1’s original query result is invalid – a phantom row appeared.
- Key difference with doctors example:
  - Doctors: locking rows (`SELECT … FOR UPDATE`) can protect the rows read.
  - Phantoms: when query checks for absence of rows, there may be nothing to lock.
    - E.g., “is username X taken?” If the result is empty, `SELECT FOR UPDATE` has nothing to attach to.
  - That’s why phantoms are harder to prevent than write skew involving existing rows.

#### ORMs & Phantoms
- ORM-generated SQL often follows the check-then-insert/update pattern.
- This makes ORM-based code especially vulnerable to phantom-induced write skew.

### Materializing Conflicts (Workaround)
- Problem: When no rows match the condition, there’s nothing to lock and thus phantom risk.
- Solution: Introduce artificial lockable rows.
- Example: Meeting Room Booking
  - Create a table `room_slots(room_id, time_slot)` ahead of time.
  - Rows represent all possible room+time combinations (say for next 6 months, broken into 15 min slots).
  - Now, before booking a room:
    - Transaction locks (`SELECT … FOR UPDATE`) the relevant slot rows.
    - Checks for overlapping bookings.
    - Inserts booking if clear.
  - These rows aren’t actual booking data, they’re just lock objects.
- Why it works ?
  - By “materializing” phantom rows into pre-existing rows, conflicts are converted into standard row-lock conflicts.
  - This forces txns to wait/abort rather than silently overlap.
- Downsides ?
  - Requires careful schema design.
  - Adds maintenance burden
  - Mixes concurrency control into the data model

### Serializability

#### Why it matters ?
- We've seen race conditions - dirty writes, lost updates, write skew, and phantoms
- Lower isolation levels (read committed, snapshot isolation, repeatable read) prevent some, but not all

#### What is Serializability?
- Strongest isolation level.
- Guarantees: Even though transactions may run in parallel, the result is as if they had run one by one, serially.

#### Why Not Always Use It?
- Historically, serializability was too expensive (locks, waiting, deadlocks).
- Newer techniques improved feasibility.
- Today, 3 approaches:
  - Actual Serial Execution (remove concurrency entirely)
    - cons: limits throughput, only for small txns, 
  - Two-Phase Locking (2PL).
  - Optimistic Concurrency Control (e.g., Serializable Snapshot Isolation, SSI)

### Actual Serial Execution
- The simplest way of avoiding concurrency problems is to remove the concurrency entirely: to execute only one transaction at a time, in serial order, on a single thread
  -  If multi-threaded concurrency was considered essential for getting good performance during the previous 30 years, what changed to make single-threaded execution possible?
  -  Two developments caused this rethink:
     -  RAM became cheap enough that for many use cases it is now feasible to keep the entire active dataset in memory
     -  Database designers realized that OLTP transactions are usually short and only make a small number of reads and writes 
     -  By contrast, long-running analytic queries are typically read-only, so they can be run on a consistent snapshot (using snapshot isolation) outside of the serial execution loop.
-  Implemented by Redis, H-Store, VoltDB, Datomic 
-  Limitations ?
   -  Yes, limited to a single CPU core
- Does I need to make any changes to the txn structure so that I can utilize single thread as much possible ? 
  - Yes
  - Encapsulating transaction in stored procedure
    - In the early days of databases, the intention was that a database transaction could encompass an entire flow of user activity.  For example, booking an airline ticket is a multi-stage process (searching for routes, fares, and available seats; deciding on an itinerary; booking seats on each of the flights of the itinerary; entering passenger details; making payment)
    - Database designers thought that it would be neat if that entire process was one transaction so that it could be committed atomically.
    - Unfortunately, humans are very slow to make up their minds and respond. If a database transaction needs to wait for input from a user... Most of the txns will be idle
    - Most databases cannot do that efficiently, and so almost all OLTP applications keep transactions short by avoiding interactively waiting for a user within a transaction.
      - On the web, this means that a transaction is committed within the same HTTP request—​a transaction does not span multiple requests
      - A new HTTP request starts a new transaction.
      - Drawbacks ?
        - Yes, a lot of time spent in network communication between application and the database 
    - For this reason, systems with single-threaded serial transaction processing don’t allow interactive multi-statement transactions. 
    - Instead, the application must either limit itself to transactions containing a single statement, or submit the entire transaction code to the database ahead of time, as a stored procedure
    - ![](./images/ddia/interactive-stored.png)
  - Pros and cons of stored procedures
    - Each database vendor had its own language for stored procedures
    - Code running in a database is difficult to manage: compared to an application server, it’s harder to debug, more awkward to keep in version control and deploy, trickier to test, and difficult to integrate with a metrics collection system for monitoring.
  - Sharding
    - Executing all transactions serially makes concurrency control much simpler, but limits the transaction throughput of the database to the speed of a single CPU core on a single machine
    -  Read-only transactions may execute elsewhere, using snapshot isolation, but for applications with high write throughput, the single-threaded transaction processor can become a serious bottleneck.
    -  In order to scale to multiple CPU cores, and multiple nodes, you can shard your data 
    -  Design shard such that each txn only needs to read/write within a single shard
    -  If required to reach multiple shards, then db must coordinate the txn across all the shards it touches
    -   The stored procedure needs to be performed in lock-step across all shards to ensure serializability across the whole system.
#### Summary of serial execution
- Every transaction must be small and fast
- It is most appropriate in situations where the active dataset can fit in memory. 
- Write throughput must be low enough to be handled on a single CPU core, or else transactions need to be sharded without requiring cross-shard coordination.

### Two-Phase Locking (2PL)
- For ~30 years, the primary way to achieve serializability (strongest isolation) was Two-Phase Locking (2PL), especially the Strong Strict 2PL (SS2PL) variant.
  - It relies heavily on locks on database objects.

#### 2PL is NOT 2PC(ommit)
- 2PL = concurrency control for isolation
- 2PC = a protocol for atomic commit in distributed systems

#### Core Idea: Readers and Writers Block Each Other
- 2PL heavily strengthens lock rules:
  - Reads need Shared locks
    - Multiple readers can share the same lock.
    - If a writer holds an exclusive lock, readers must wait.
  - Writes need Exclusive locks
    - A writer must wait for all readers of the object to finish.
    - Writer blocks readers and other writers.
- Key differences vs Snapshot Isolation (MVCC)
  - 2PL: readers block writers, writers block readers.
  - MVCC: readers never block writers, writers never block readers.
- Because 2PL blocks aggressively, it prevents:
  - Lost updates
  - Phantoms
  - Write skew

- Implementation
  - Used in: MySQL InnoDB (serializable)
- Two phases:
  - Growing phase: acquires locks
  - Shrinking phase: release locks at commit/abort

- Deadlocks
  - Two txn waiting for each others
    - DB detects deadlock cycles
    - Abort one txn
    - Application must retry
  - Deadlock are much more commons under 2PL 

#### Performance Problems
- This is why 2PL is not popular for modern high-throughput systems.
  - High lock overhead
  - Reduced concurrency
  - Readers blocking writers
  - Deadlock retries waste work

#### Phantoms and Predicate Locks
- The phantom problem
  - A transaction reads a set of rows. Another transaction inserts a new row that matches the same condition.
  - This can break serializability (isolation)
- Too complex and many locks, too slow

### Serializable Snapshot Isolation (SSI)
- 2PL don't perform well and serial execution don't scale well
- On other hand we have weak isolation levels that have good performance, but are prone to various race conditions (lost updates, write skew)
- A newer alternative to 2PL that provides:
  - Full serializability
  - Without blocking reads/writes
  - Without single-thread bottlenecks
- Used by
  - PostgreSQL (serializable)
  - CockroachDB
  - FoundationDB
- Pessimistic vs Optimistic Concurrency
  - 2PL = Pessimistic
    - Block as soon as a conflict might happen
    - Safe but kills throughput
  - SSI = Optimistic
    - Let transactions run without blocking
    - Validate at commit
    - Abort if conflicts detected
  - Trade-offs:
    - If contention is high → many aborts → bad performance
    - If contention is moderate → performs better than 2PL

    | Model                                     | Blocking?                   | Phantom protection | Performance                      | Best use                    |
    | ----------------------------------------- | --------------------------- | ------------------ | -------------------------------- | --------------------------- |
    | **2PL**                                   | Heavy blocking (read-write) | Yes                | Poor under load                  | Old-school OLTP             |
    | **Snapshot Isolation (MVCC)**             | None                        | No                 | Fast                             | General workloads           |
    | **Serializable Snapshot Isolation (SSI)** | No                          | Yes                | Near-MVCC speed with correctness | Modern databases            |
    | **Serial Execution**                      | Single-threaded             | Yes                | Fast if in-memory                | High-speed OLTP like VoltDB |


### Distributed transactions
#### Big picture - what makes distributed transactions hard
- In a single-node DB, committing a transaction is a local, atomic event: write data, write a commit record to disk, done
- In a distributed transaction the commit must be coordinated across multiple nodes (multiple shards, replicas, or even different systems).
- The core difficulty is the atomic commitment problem - we want either all participants to commit or all to abort
- If some nodes commit and others abort, the system becomes inconsistent and recovery is painful or impossible.
- Practical failure modes you must handle:
  - Nodes crash during the protocol and recover later with partial state.
  - Network messages (prepare/commit) are lost or delayed.
  - Some participants detect constraint violations while others do not.
  - Coordinator crashes after participants have voted but before broadcasting the final decision.

#### Two-Phase Commit (2PC) - essentials

![2PC](./images/ddia/ddi2_0813.png)
- 2PC guarantees atomic commit by splitting commit into two phases:
  - Phase 1 - prepare: coordinator asks participants "can you commit?" Participants ensure they can commit (durably persist writes) and reply yes/no.
  - Phase 2 - commit/abort: if all said yes, coordinator decides commit and tells everyone to commit; else it tells everyone to abort.
- The safety comes from two promises:
  - A participant voting "yes" promises it can commit later (it has made its local writes durable).
  - The coordinator's final decision is durable and irrevocable once written to its log.

##### Why 2PC can block

![2pc-crash](./images/ddia/2pccrash.png)

- If the coordinator crashes after participants vote "yes" but before sending the final decision, participants are left "in doubt". They must wait for the coordinator to recover - they cannot unilaterally commit or abort without risking inconsistency.
- During this in-doubt period locks and resources are typically held, blocking other transactions and potentially degrading the system.

##### Operational consequences
- Long-held locks while waiting for coordinator recovery can cause large parts of the app to stall.
- Loss or corruption of the coordinator log can produce unrecoverable in-doubt transactions requiring manual intervention.
- These failure modes explain why 2PC is considered "blocking" and operationally expensive.

#### Three-phase commit
- Two-phase commit is called a blocking atomic commit protocol due to the fact that 2PC can become stuck waiting for the coordinator to recover.
- As an alternative to 2PC, an algorithm called three-phase commit (3PC) has been proposed
- However, 3PC assumes a network with bounded delay and nodes with bounded response times; in most practical systems with unbounded network delay 
- A better solution in practice is to replace the single-node coordinator with a fault-tolerant consensus protocol (Chapter 10)

#### Practical fixes and improvements to vanilla XA/2PC
- If you must use distributed commit, design choices can reduce the pain:
  - Replicate the coordinator using a fault-tolerant consensus protocol (Raft/Paxos) so the coordinator itself is highly available and its log is durable across failures.
  - Replicate participants and coordinate with their replication protocols to reduce single-shard faults causing aborts.
  - Integrate atomic commit with the database's concurrency control so deadlocks and conflict detection work across shards.

### Distributed Transactions Across Different Systems
#### Why distributed transactions are controversial ?
- Distributed transactions, especially those implemented using two-phase commit (2PC), have a mixed reputation:
  - Pros
    - Provide strong safety guarantees (notably atomic commit)
    - Enable correctness across multiple systems when partial failure is possible
  - Cons
    - Cause significant operational complexity
    - Often degrade performance

#### Where the performance cost actually comes from ?
- Disk forcing (fsync)
  - Required to ensure crash recovery correctness
  - Forces synchronous, durable writes on the critical path
- Additional network round-trips
  - Coordinator <-> participants communication
  - Latency multiplies with number of participants

#### Why we should not dismiss distributed transactions outright ?
- Despite the drawbacks:
  - Distributed transactions encode important correctness lessons
  - They formalize how to reason about atomicity under partial failure
  - Understanding them helps evaluate alternatives (sagas, compensation, idempotency)
- Rejecting 2PC without understanding it leads to re-inventing weaker, often unsafe mechanisms.

#### Critical distinction - two very different meanings of “distributed transaction”
- A common mistake is conflating two fundamentally different scenarios.
  - Type 1 - Database-internal distributed transactions
    - Def. Transactions that span multiple nodes of the same distributed database
    - Characteristics
      - All participants run the same database software
      - The system controls:
        - Replication
        - Sharding
        - Failure detection
        - Recovery semantics
      - Examples
        - YugabyteDB
        - FoundationDB
        - Spanner
        - Cassandra
        - MySQL Cluster (NDB engine)
    - Why these often work well ?
      - Can apply database-specific optimizations that are impossible in general 2PC
      - These systems are not using “generic” distributed transactions. They are using bespoke, tightly integrated protocols.
      - Database-internal distributed transactions can be efficient and practical because the system controls the entire stack.
  - Type 2 - Heterogeneous distributed transactions
    - Def. Transactions spanning multiple, different systems, such as:
      - Databases from different vendors
      - Databases + message brokers
      - Databases + other stateful services
    - Requirements
      - Must ensure atomic commit across systems
      - Participants may have:
        - Different failure models
        - Different durability guarantees
        - Different transaction semantics
      - Why this is hard
        - No shared implementation assumptions
        - Limited optimization opportunities
        - Failures are harder to reason about and recover from
      - This is where most real-world pain with distributed transactions comes from.
      - Heterogeneous distributed transactions are fundamentally more complex and fragile due to lack of shared assumptions.
      - Criticism of distributed transactions usually applies to the heterogeneous case, but is often (incorrectly) generalized to all distributed transactions.
- Summary
  - Distributed transactions are not inherently broken - they work best inside a single distributed database, and become risky and expensive when forced across heterogeneous systems.

### Exactly-once Message Processing - Distributed Transactions
- In heterogeneous systems, message processing often involves:
  - Consuming a message from a message broker
  - Performing side effects (typically database writes)
- The correctness requirement:
  - A message should be acknowledged if and only if its processing side effects are durably committed
- This avoids:
  - Message loss
  - Duplicate processing
  - Partial side effects

- How distributed transactions enable exactly-once semantics ?
  - Using a heterogeneous distributed transaction, we can:
    - Atomically commit:
      - Message acknowledgment (or offset advance)
      - Database updates
    - Abort both if either fails
  - Outcome:
    - If processing fails → transaction aborts → message is safely redelivered
    - If processing succeeds → both message ack and side effects commit together
  - This creates the illusion of exactly-once processing, even if retries occur internally.
    - Retries are allowed; duplicate effects are not.
- Meaning of “exactly-once semantics”
  - Externally visible side effects occur once
  - Internal retries may happen
  - Partial effects are discarded on abort
- This is stronger than at-least-once, and safer than at-most-once, but relies on strict assumptions.
- Safe retry condition
  - A processing step can be safely retried only if:
    - All side effects are either:
      - Rolled back on abort, or
      - Idempotent
  - If this holds:
    - Retries are indistinguishable from a single execution

### XA Transaction
- XA (X/Open XA) is a standard for two-phase commit (2PC) across heterogeneous systems
- Widely supported by:
  - Databases: PostgreSQL, MySQL, Oracle, SQL Server, Db2
  - Message brokers: ActiveMQ, IBM MQ, MSMQ, HornetQ
- It is a C API specification (not a network protocol)
- Architecture
  - Application code starts a transaction
  - Drivers (JDBC/JMS) decide whether calls belong to an XA transaction
  - Drivers expose callbacks:
    - prepare
    - commit
    - rollback
  - Transaction coordinator:
    - Tracks participants
    - Collects prepare responses
    - Decides commit or abort
    - Persists decision in a local log
  - Where the coordinator lives
    - Typically not a separate service
    - Usually a library loaded inside the application process
    - Uses local disk for logging transaction decisions
- Failure behavior
  - If the application process crashes or the machine dies:
    - The coordinator dies with it
    - Participants that already prepared are left in-doubt
    - Databases cannot contact the coordinator directly
    - Recovery requires:
      - Restarting the application server

### Summary 

| Isolation level        | Dirty reads | Read skew | Phantom reads | Lost updates | Write skew |
|------------------------|-------------|-----------|---------------|--------------|------------|
| Read uncommitted       |  Possible  |  Possible|  Possible    |  Possible   |  Possible |
| Read committed         |  Prevented |  Possible|  Possible    |  Possible   |  Possible |
| Snapshot isolation     |  Prevented |  Prevented|  Prevented   | ? Depends    |  Possible |
| Serializable           |  Prevented |  Prevented|  Prevented   |  Prevented  |  Prevented |

- Dirty reads
  - One client reads another client’s writes before they have been committed. The read committed isolation level and stronger levels prevent dirty reads.

- Dirty writes
  - One client overwrites data that another client has written, but not yet committed. Almost all transaction implementations prevent dirty writes.

- Read skew
  - A client sees different parts of the database at different points in time. Some cases of read skew are also known as nonrepeatable reads. This issue is most commonly prevented with snapshot isolation, which allows a transaction to read from a consistent snapshot corresponding to one particular point in time. It is usually implemented with multi-version concurrency control (MVCC).

- Lost updates
  - Two clients concurrently perform a read-modify-write cycle. One overwrites the other’s write without incorporating its changes, so data is lost. Some implementations of snapshot isolation prevent this anomaly automatically, while others require a manual lock (SELECT FOR UPDATE).

- Write skew
  - A transaction reads something, makes a decision based on the value it saw, and writes the decision to the database. However, by the time the write is made, the premise of the decision is no longer true. Only serializable isolation prevents this anomaly.

- Phantom reads
  - A transaction reads objects that match some search condition. Another client makes a write that affects the results of that search. Snapshot isolation prevents straightforward phantom reads, but phantoms in the context of write skew require special treatment, such as index-range locks.




## Chapter 8. The Trouble with Distributed Systems 
- In this chapter we will turn our pessimism to the maximum and assume that any thing *can go wrong will go wrong*


## Chapter 9. Consistency and Consensus 
- Faults are inevitable in distributed systems :
  - What can go wrong ?
    - packets can be lost, reordered, duplicated or arbitrarily delayed in the network
    - clocks are approximate at best
    - nodes can pause (GC the one-and-only Garbage Collection) or crash at any time
  - So how to deal with them ?
    1. Straight forward solution : Let the entire service fail, and show the error message to the user
    2. Or, Keeping the service functioning correctly by tolerating faults i.e __fault tolerant distributed systems__
- Building fault tolerant systems :
  - Find some general purpose abstractions with useful guarantees.
  - Implement them once and let applications rely on those guarantees. This will allow applications to ignore some of the problems with distributed systems.
- Consensus : one of the most important abstractions for distributed systems
  - Getting all of the nodes to agree on something.
  - What's the catch ? There might be n/w faults or, process failures and this hides 🫣 it from the application
- We need to explore the range of guarantees and abstractions that can be provided in a distributed system in order to understand the scope of what can and cannot be done
  1. Linearizability and examine it's pros & cons
  2. Examine the issue of ordering events in a distributed system
  3. Distributed Trasactions and Consensus, how to atomically commit a distributed transaction, which will finally lead us towards solutions for the consensus problem

### Consistency Guarantees / Distributed Consistency Models
- Timing issues in replicated database (let it be single-leader / multi-leader or leaderless replication)
  - If we look at two db nodes at the same moment in time we are likely to see different data on the two nodes because write requests arrive on different nodes at different times.
- Distributed consistency is all about coordinating the state of the replicas in the face of delays and faults.
1. Eventual Consistency / Convergence
  - If we stop writing to a db and wait for some __unspecified__ length of time, then eventually all read requests will return the same value.
  - Why it's not sufficient ? / Issues 🤔
    - This is a very weak guarantee, it doesn't say anything about when the replicas will converge. Until the time of convergence, read could return anything or nothing.
    - Hard for application developers to adapt, so different from behaviour of variables in a single-threaded program. If we write a value and then immediately read it again, there is no guarantee that we will see the value we just wrote, because the read may be routed to a different replica.
    - Bugs are too subtle and hard to find : Edge cases only become apparent when there is a fault in the system or at high concurrency.
2. Strong Consistency
  - Stronger guarantees with ease of use
  - Not free :
    - May have worse performance.
    - Less fault tolerant than systems with weaker guarantees.
  - Linearizability is one of the strongest consistency models

### Linearizability
- AKA atomic consistency, strong consistency, immediate consistency or external consistency.
- System maintains **illusion for the client** that there is only **one copy of the data**, and **all operations on it are atomic**. With this guarantee, even though there might be multiple replicas in reality, the application does not need to worry about them.
- Linearlizability as a **recency guarantee**, maintaining the illusion of a single copy of the data means guaranteeing that the value read is the most recent, up-to-date value, and doesn't come from a stale cache or replica.
#### What makes a system linearizable ?
- Formal Definition : To test whether the system'e behaviour is linearizable record the timings of requests and responses, and check whether they can be arranged into a valid sequential order.
- Example 1 
  - ![If a read request is concurrent with a write request, it may return either the old or the new value.](images/ddia/ddia_0901.png)
  - Due to variable network delays, a client doesn’t know exactly when the database processed its request. It only knows that it must have happened sometime between the client sending the request and receiving the response (b/w the start and end of a bar)
  - In this example, we perform two types of operations on register :
    1. **read(x) ⇒ v** means the client requested to read the value of register x, and the database returned the value v.
    2. **write(x, v) ⇒ r** means the client requested to set the register x to value v, and the database returned response r (which could be ok or error).
  - First read by client A completed before the write begins, it must definately return the old value 0
  - Last read by client A begins after the write has completed, so it must definately return the new value 1
  - What about the read operations that overlap in time with the write operation ? might return 0 or 1, but the readers might see value flip back and forth between the old and the new value several times while the write is going on. This breaks illusion of _single copy of data_
  - Atomic update : In linearizable we assume that there must be some point in time between the start and the end of the write operation at which the value of x atomically flips from 0 to 1. And therefore if one client read returns the new value of 1, all subsequent reads must also return the new value, even if the write operation has not yet completed (because of n/w delays).
- Example 2 
  - ![Visualizing the points in time at which the reads and writes appear to have taken effect. The final read by B is not linearizable.](images/ddia/ddia_0902.png)
  - In the above figure, we have added a third type of operations besides read and write : 
    3. cas(x, vold, vnew) ⇒ r means the client requested an atomic compare-and-set operation. If the current value of the register x equals vold, it should be atomically set to vnew. If x ≠ vold then the operation should leave the register unchanged and return an error. r is the database’s response (ok or error).
  - Each operation in the figure is marked with a vertical line inside the bar of the operation, this is the time when we think the operation was executed. Those markers are joined up in a sequential order.
  - The requirement of linearizability is that the lines joining up the operation markers always move forward in time (from left to right), never backwards.
  - This model doesn't assume any transaction isolation: another client may change a value at any time. C first reads 1 and then reads 2, because the value was changed by B between the two reads. An atomic CAS operation can be used to check the value hasn't been concurrently changed by another client.
  - Final read by client B is not linearizable. In absence of the other request, it would be okay for B's read to return 2. However, the client A has already read the new value 4 before B's read started, so B is not allowed to read an older value than A.
> **Linearizability v/s Serializability**
> 1. **Linearizability** : 
> - Recency guarantee on reads and writes of a register
> 2. **Serializability** : 
> - Isolation property of transactions, where every transaction may read and write multiple objects (rows, documents, records)
> - It guarantees that transactions behave the same as if they had executed in some serial order
> 
> Database may provide both serializability and linearizability, and this combination is known as strict serializability or strong one-copy serializability. Implementations of serializability like 2PL and actual serial execution are typically linearizable
>
> Serializable snapshot isolation (SSI) is not linearizable. The whole point of consistent snapshot is that it does not include writes that are more recent than the snapshot, and thus reads from the snapshot are not linearizable.

#### Relying on Linearizability (Use Cases)
1. Locking and Leader Election
- In single-leader replication we need to ensure that there is only leader and not several (split brains).
- One way is to use a lock for leader election, every node that starts up tries to acquire the lock, and the one that succeeds becomes the leader.
- Lock implementation must be linearizable : all nodes must agree which node owns the lock; otherwise it is useless.
- Example : Apache Zookeeper and etcd are often used to implement distributed locks and leader election. They uses consensus algorithms to implement linearizable operations in fault-tolerant way.
> [!IMPORTANT]
> Linearizable storage service is the basic foundation for coordination tasks.

2. Constraints and Uniqueness Guarantees
- Uniqueness constraints are common in databases. For example, a username and email address must uniquely identify one user.
- In a file storage service there cannot be two files with the same path and filename.
- These operations are similar to atomic compare-and-set, setting the username to the ID of the user who claimed it, provided that the username is not already taken.
- For enforcing these constraints on the data being writte, we need linearlizability (such that if two people try to concurrently create a user or a file with the same name, one of them will be returned an error).

3. Cross-channel timing dependencies
![The web server and image resizer communicate both through file storage and a message queue, opening the potential for race conditions.](images/ddia/ddia_0903.png)
- Example : Website where users can upload a photo, and a background process resize the photos to a lower resolution for faster downloads
- Image resizer needs to be explicitly instructed to perform a resizing job, and this instruction is sent from web server to the resizer via a message queue. Web server cannot place the entire photo of several megabytes in size on the queue, since most message brokers are designed for small messages
> [!CAUTION]
> If the file storage service is not linearizable, then there is a risk of race condition : the message queue might be faster than the internal replication inside the storage service. In this case, resizer fetches the image, it might see an old version of the image, or nothing at all.

#### Implementing Linearizable Systems
1. Use a single copy of data, but this approach is not fault-tolerant. When single node holding that one copy failed, that data would be lost or at least inaccessible until the nodes was brought up again.

Common approach to make system fault-tolerant is to use **replication** :

2. **Single Leader Replication** 
- Leader has the primary copy of the data that is used for writes and the followers maintain backup copies of the data on other nodes.
- If we make reads from the leader, or from synchronously updated followers, they have the potential to be linearizable.
- Not every single leader database is linearizable either by design (Eg : snapshot isolation) or due to concurrency bugs.
- Using the leader for read relies on the assumption that we know for sure who the leader is, if a delusional leader continues to serve requests, it is likely to voilate linearizability.
3. **Consensus Algorithm**
- Consensus algorithms bear resemblance to single-leader replication. Also they contain measures to prevent split brain and stale replicas.
4. **Mutli-Leader Replication**
- Generally not linearizable, as they concurrently process writes on multiple nodes and asynchronously replicate them to other nodes.
5. **Leaderless Replication**
- Leaderless replication i.e Dynamo style, strict quoram reads and writes (w+r>n) are not always linearizable or strongly consistent.
![A nonlinearizable execution, despite using a strict quorum.](images/ddia/ddia_0904.png)
- The quorum condition is met (w + r > n), but this execution is nevertheless not linearizable: B’s request begins after A’s request completes, but B returns the old value while A returns the new value.
- It is possible to make Dynamo-style quorums linearizable at the cost of reduced performance: a reader must perform read repair synchronously, before returning results to the application, and a writer must read the latest state of a quorum of nodes before sending its writes.
- It is also safest to assume that a leaderless system with Dynamo style replication does not provide linearizability.

#### Cost of Linearizability
- Network disruption between the two datacenters, client can reach out to datacenters, but the datacenters cannot connect to each other
1. Multi-leader replicated database : each datacenter continue to operate normally: since writes from one datacenter are async replicated to the other, the writes are simply queued up and exchanged when network connectivity is restored
2. Single-leader replicated database : leader must be in one of the datacenter. Any writes and any linearizable reads must be sent to the leader. If the application requires linearizable reads and writes, the network interruption causes the application to become unavailable in the datacenters that cannot connect to the leader. They can still reads from the follower, but they might be stale (nonlinearizable).
> The issue isn't specific to multi-datacenter deployments, but can occur on any unreliable network, even within one datacenter.
- The applications that doesn't require linearizability can be more tolerant to network problems. 

- **CAP Theoram** (Consistency, Availability, Partition Tolerance): 
  - Network partitions are kind of fault, they will happen whether we like it or not.
  - At times when the n/w is working correctly, a system can provide consistency (linearizability) and total availability.
  - When n/w fault occurs, we have to choose between either linearizability or total availability aka Consistent or Available when Partitioned. 
  - CAP encouraged database engineers to expore wider design space of distributed shared-nothing systems, which were more suitable for implementing large-scale web services.
  - It only focuses on one kind of fault (n/w partition or nodes that are alive but disconnected from each other) but doesn't say anything about n/w delays, dead nodes or other trade-offs.

> [!IMPORTANT]
> **Performance and Fault Tolerance**
> 
> Many distributed systems choose not to provide linearizability to increase performance, no so much for fault tolerance. 
> Linearizability is slow and this is true all the time, not only during a network fault.
> - Faster algorithm for linearizability does not exist, the response time of read and write requests is at least proportional to the uncertainty of delays in the network.
> - Weaker consistency models can be much faster.

### Distributed Transactions and Consensus
- Situations in which it is important for the nodes to agree.
1. Leader Election Problem
  - In db with single-leader replication, all nodes need to agree on which node is the leader (consensus).
  - If some of the nodes can't communicate with others due to network fault, split brain situation might arise when two nodes both believe themselves to be leader.
  - If there are two leaders, they would both accept writes and their data would diverge, leading to inconsistency and data loss.
2. Atomic Commit Problem
  - Database that supports distributed transactions, i.e transactions spanning across several nodes or partitions.
  - We have a problem that a transaction may fail on some nodes but succeed on others.
  - We have to get all nodes to agree on the outcome of the transaction (consensus) : either they all abort / roll back or they all commit.
> [!TIP]
> **Controversy on FLP Result**
> 
> Named after authors Fischer, Lynch and Paterson which proves that there is no algorithm that is always able to reach consensus, if there 
> is a risk that a node may crash.
>
> But it was proved in the async system model, a very restrictive model that assumes a deterministic algo that cannot use any clocks or timeouts.
>
> If the algo is allowed to use timeouts, or some other way of identifying suspected crashed nodes, then consensus becomes solvable.



## Chapter 10. Batch Processing

## Chapter 11. Stream Processing

