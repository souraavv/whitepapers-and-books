
## RAFT: In search of an Understandable Consensus Algorithm
- Diego Ongaro and John Ousterhout (Standford University) : May 20, 2014

### Introduction

- Consensus algorithm allow 
    - A collection of machines to work as a coherent group
    - Survive the failures of some members

- Gains?
    - Reliable large-scale software system

- What is RAFT ?
    - Consensus algorithm for managing a repliacted log
    - Much easier to understand compare to classic consensus algo **Paxos** (by Leslie Lamport)
        - Paxos is complex to understand and also some parts are less intuitive why they works 
        - RAFT is easier to understand 
            - Breakdown to smaller problems

- What claims does RAFT make ? 
    - Strong leader
        - Flow of log entry only from leader to other servers
        - Simplified management of log
    - Leader Election
        - randomized itmers to resolve conflicts (else indefinite waiting)
    - Membership change 

- RAFT vs PAXOX (Author perspecitve)
    - Superior for both acads + industry
    - Simpler 

### Replicated State Machines

- What is Replicated State Machine ?
    - Implemented using a replicated log

- Logs contains ?
    - sequence of commands
    - Every log on every compute contains command in same sequence

- Property of State Machine
    - Deterministic 
    - This gurantee if from state s, we apply log, then we will always reach to some state d

- What is the role of RAFT here ?
    - Keep these logs **consistent**

- Hallucination 
    - RAFT make client believe server as a single, highly reliable state machine

- Consensus algo arise in the context of RSM

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
- Understandability 
    - Paxos is complex