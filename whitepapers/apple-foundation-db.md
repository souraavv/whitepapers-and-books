- [FoundationDB: A distributed Key-Value Store](#foundationdb-a-distributed-key-value-store)
  - [Abstract](#abstract)
    - [Hey FoundationDB, Introduce yourself](#hey-foundationdb-introduce-yourself)
    - [Why should we read this paper ?](#why-should-we-read-this-paper-)

# FoundationDB: A distributed Key-Value Store
Author: J Zhou, Published @ SIGMOD'21

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

