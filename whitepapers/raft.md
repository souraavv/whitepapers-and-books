
## RAFT: In search of an Understandable Consensus Algorithm
- Diego Ongaro and John Ousterhout (Standford University) : May 20, 2014

### Introduction

- Consensus algorithm allows
    - A collection of machines to work as a coherent group
    - Survive the failures of some members

- Gains?
    - Reliable large-scale software system

- What is RAFT ?
    - Consensus algorithm for managing a replicated log
    - Much easier to understand compare to classic consensus algo **Paxos** (by Leslie Lamport)
        - Paxos is complex to understand + less intuitive
        - RAFT is easier to understand 
            - Breakdown to smaller problems

- RAFT claims ? 
    - Strong leader
        - Flow of log entry only from leader to other servers
        - Simplified management of log
    - Leader Election
        - randomized itmers to resolve conflicts (else indefinite waiting)
    - Membership change 

### Replicated State Machines

- What is Replicated State Machine ?
    - Implemented using a replicated log
        ```mermaid
        graph LR
            A(State s[i]) --(log[i])--> B(State s[i + 1])
            B --(log[i + 1])--> C(State s[i + 2])
        ```

- Logs contains ?
    - Sequence of commands

- Commands are present in the same sequence in each log present on each compute

- Properties of State Machine
    - Deterministic 
        - Initial State S; apply log L; Final State D

- What is the role of Raft algorithm here ?
    - Keep these logs **consistent**

- Hallucination 
    - RAFT make client believe server as a single, highly reliable state machine

- Consensus algorithm arise in the context of Replicated State Machines
    - Same state on multiple servers

### Must-have properties of a consensus algorithm 

- What gurantee RAFT provides ?
    - **Safety**
        - Never return an incorrect result (under all non-Byzantine conditions)
    - **Available**
        - As long as majority is there (n / 2 + 1)
    - **Not depend on Timing**
        - Indepent of timing to ensure the consistency. Why ? 
            - Faulty clocks
            - Extereme message delays 

### Main GOAL of RAFT ?
- Musts
    - Provide complete and practical foundation for system building
    - Safe under all operating conditions

- Apart from **MUST** the **MAIN** goal of RAFT was *Designing for Understandability*
    - Paxos is complex, Raft is simpler
    - Raft simplify the state space by reducing the number of states to consider
        - Makes system more coherent
    - Eliminating non-determinism wherever possible
        - At some places it helped (randomization helped Raft leader election algo)


### The Raft Consensus Algorithm

- Raft manages replicated logs
- Raft implements consensus 
    - Electing distinguised leader
    - Information flow is always from leader to followers; client always talks with leader
    - Leader accepts logs from client and replicate then on other server 
    - Leader tells servers when it is safe to apply log entries to their state machines

- Leaders simplify the data flow
- If leader gets disconnected/fails; then a new leader got elected 

#### Decomposition of Consensus Problem 

- Leader Election
    - A new leader must be chosen when an existing leader fails
- Log replication
    - Leader must accept log entries from client and replicate them across the cluster
    - Force other logs to agree with its own 
- Safety 
    - State Machine Safety
        - If any server has applied a particular log entry to it state machine, then no other server may apply a different command for the same log index
    - Ensured through election restrictions


### Raft Basics

- Raft cluster consists of servers (typically 5 servers)
    - Survive two server failures
- At a given time server is in three states
    - Leader
    - Follower
    - Candidate
- Normal scenario
    - one leader, rest all are followers
- Client always talks with leader
    - If client talks with a follower, the follower redirect client to the leader

- Raft divides times into *terms* of arbitary length
- Terms are numbered with consecutive integers
- Each term begin with an election, in which one or more candidate attempts to become leader
    - If candidate wins, then leader for the entire term
    - Split votes (tie)
        - Term left out with no leader (election from next term)
    



