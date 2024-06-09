## Designing Data Intensive Applications

- Author : Martin Kleppmann
- 20 hours of reading (600+ pages book)


### Plethora of buzzwords relating to storage and processing of data
- NoSQL! Big Data! Web-scale! Sharding! Eventual consistency! ACID! CAP theorem! Cloud services! MapReduce! Real-time!


### Preface
- Data intensive 
    - Data as primary challenged - quanity/complexity/changing-nature
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

## Part 1. Foundation of Data Systems [Chapter 1 - Chapter 4]

### Chapter 1 : Reliable, Scalable, and Maintainable Applications
> No such hard boundary b/w databases, queues, caches, etc. because now most tools are coming up with multiple features. Thus we will keep these three under single umbrella
- Reliability
    - Tolerating hardware & software faults
        - Redundant components ? 
            - Was OK in older system, but in recent when computing demand has increased
            - More compute demand == More machines == More harware faults
        - Sofware fault-tolerant 
            - Can tolerate entire machine loss 
            - Operational advantages
                - Schedules downtime/patching
    - Hardware vs Software
        - We make **assumption** hardware faults are independent and random
            - P(Component A fails | Component B failed) = 0 (or may be ~0 : weak correlations)
        - Another class : Systematic faults
            - Correlated across nodes
                - Software bug
                - Runaway process - use up shared resources - CPU, memory, disk or network bandwidth
                - Slow down of some service
                - Cascading failures
            - These bugs lie dormant until some event trigger them

    - Human Errors
        - To avoid
            - Well-designed abstraction
            - APIs
            - Admin interface 
            - Decouple components (high risk, low risk)
            - Clear monitoring (performance metrics, error rates)
            - Good management practices 

- Scalability
    - Systems ability to cope with increased load.
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
                    - Insert tweet to some global collection of tweet
                    - When a user reqeust 
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
                    - ![text](./images/ddia_0102.png)
                    - ![text](./images/ddia_0103.png)
                - Gains 
                    - Approach second is better than first in term of home timeline reads
                    - Less work during read
                    - Reality check: Tweets are published way less frequent compare to home timeline read
                - Pain 
                    - Approach one is better than second in term of publish tweet
                    - More work at write in second approach
                        - Assumption Land
                            - Avg: 75 followers
                            - Tweets rate: 4.6k
                            - Number of writes : 4.6k * 75 = 345k writes/second
                        - But easily there are people who have more than say 30 Million followers
                            - 30millions writes 😬
                            - Senior dev to Junior Dev
                                - Senior: Why our disk fans making so much noise ? 
                                - Junior: Probably Kohli has open his keypad and typing
                            - So does this mean software engineers are existing because of sportsmen/movies-stars/tik-tokers/policians/ ? 
                            - Basically they can break you code any day.
                            - And you are writing millions of code line just for them :| 


                
            
- Maintainability

