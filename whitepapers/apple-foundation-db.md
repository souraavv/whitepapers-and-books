- [FoundationDB: A distributed Key-Value Store](#foundationdb-a-distributed-key-value-store)
  - [Abstract](#abstract)
    - [Hey FoundationDB, Introduce yourself](#hey-foundationdb-introduce-yourself)
    - [Why should we read this paper ?](#why-should-we-read-this-paper-)
  - [Introduction](#introduction)

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
- Unlike most database where they bundle storage engine, data model and query language, forcing users to choose all three or none. FDB takes modular approach 
- FDB defaults to strict serializable transactions, it allows these semantics for application that don't require them with flexible, fine-grained control over conflicts