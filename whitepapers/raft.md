
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
    - State s[i]; apply log[i]; State s[i + 1]

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
    - Term acts as *logical clocks*
    - Helps servers to detect obsolete information such as stale leaders
- Terms are numbered with consecutive integers
- Each term begin with an election, in which one or more candidate attempts to become leader
    - If candidate wins, then leader for the entire term
    - If Split votes then no leader for the term (term++; election again)
- Raft ensures that there is at *most one* leader each **term**
- Transition b/w terms may be observed at different times 

### State of a Server
- **Persisted state on all servers** (before responsing to RPCs)
    - `currentTerm`
        - Latest term server has seen
        - Initialize to 0 on first boot, increase monotonically
    - `votedFor`
        - Candidate that received vote in current term (or null if none)
    - `log[]`
        - Log entries
        - Each entry contains (command for state machine, term when entry was recieved)
        - one-based indexing
- **Volatile state on all server**
    - `commitIndex`
        - Index of highest entry known to be commited (init = 0; increase monotonically)
    - `lastApplied`
        - Index of highest log entry applied to the state machine (init = 0; increase monotonically)
- **Volatile state on leaders**
    - `nextIndex[]`
        - For each server
            - Index of the next log entry to send to that server 
            - Init = leader last log index + 1
    - `matchIndex[]`
        - For each server 
            - Index of highest log entry known to be replicated on server
            - init = 0; increase monotonically

### AppendEntries RPC
Invoked by leader to replicate log entries + heart beats

| **Arguments** | Meaning | 
|-----| --- |
| term | leader's term| 
| leaderId | so follower can redirect clients |
| prevLogIndex | index of log entry immediately preceding new ones |
| prevLogTerm | term of prevLogIndex entry |
| entries[] | log entries to store (empty in case of heartbeat) | 
| leaderCommit | leader's commitIndex | 

| **Results** | Meaning | 
| ---- | --- |
| term | `currentTerm`, for leader to update itself | 
| success | `true` if follower contained entry matching prevLogIndex and prevLogTerm|

**Receiver Implementation**
1. Reply `false` if `term < currentTerm`.
    - This means that if the leader is operating on an older term than the server's current term, return false.
2. Reply `false` if the log does not contain an entry at prevLogIndex with a term that matches prevLogTerm.
    - This ensures that the server logs can synchronize with the leader's logs.
3. If an existing entry conflicts with a new one (same index but different term), delete the existing entry and all entries that follow it.
    - There is a single source of truth, and the current leader defines that truth.
- Append any new entries that are not already in the log.
- If `leaderCommit > commitIndex`, set `commitIndex` to `min(leaderCommit, index of the last new entry)`.
    - Why safe ? 

### RequestVote RPC
Invoked by candidates to gather vote

| **Argument** | Meaning | 
| --- | --- |
| term | candidate's term |
| candidateId | candidate requesting vote | 
| lastLogIndex | index of candidate's last log entry | 
| lastLogTerm | term of candidate's last log entry | 

| **Results** | Meaning |
| ---- | ---- |
| term | `currentTerm`, for the candidate to update itself |
| voteGranted | `true` means candidate received vote |

**Reciever Implementation**
1. Reply `false` if `term < currentTerm`
2. If `votedFor == null` or `candidateId`, and candidate's log is at least as up-to-date as reciever's log, grant vote

 
### Rules for Servers
    
**All servers**
- If `commitIndex > lastApplied`, then increment `lastApplied`, apply `log[lastApplied]` to state machine
- If RPC request or response contains term `T > currentTerm` set `currentTerm = T`, convert to follower

**Followers**
- Respond to RPCs from candidates and leaders
- If election timeout elapses without receiving AppendEntries RPC from current leader or granting vote to candidate: convert to candidate

**Candidates**
- On conversion to candidate, start election:
    - Increment `currentTerm`
    - Vote for Self (self-obsessed)
    - Reset election timer
    - Send RequestVote RPCs to all other servers
- If vote from majority (promote to leader)
- If AppendEntries RPC received from new leader: convert to follower
- If election timeout elapses: start new election

**Leaders**
- Upon election: send initial empty AppendEntries RPCs (heartbeat) to each server
    - Prevent election timeout
- If command received from client: append entry to local log, respond after entry applied to state machine



