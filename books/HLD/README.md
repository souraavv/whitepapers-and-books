
- [Acing the System Design Interview](#acing-the-system-design-interview)
- [Part 1](#part-1)
  - [Chapter 1. A walkthrough of system design concepts](#chapter-1-a-walkthrough-of-system-design-concepts)
    - [A discussion about tradeoffs](#a-discussion-about-tradeoffs)
    - [Should you read this book?](#should-you-read-this-book)

# Acing the System Design Interview 

The books is written by Zhiyong Tan 
- As the demand for robust and scalable systems continues to soar, companies are increasingly prioritizing system design expertise in their hiring process
- An effective system design interview not only assesses a candidate’s technical prowess but also evaluates their ability to think critically, make informed decisions, and solve complex problems. 
- This book is a roadmap that takes readers through each step of the system design interview process
- This book is an essential companion that will empower you to tackle even the most complex system design challenges with confidence and finesse.
- Software development is a world of continuous everything
  - Continuous improvement, continuous delivery, continuous monitoring, and continuous re-evaluation of user needs and capacity expectations are the hallmarks of any significant software system
  - **If you want to succeed as a software engineer, you must have a passion for continuous learning and personal growth**
  - With passion, software engineers can literally change how our society connects with each other, how we share knowledge, and how we manage our lifestyles.
- Part 1 of the book begins with an informative survey of critical aspects of system design
- In part 2, ride along for 11 distinct system design problems, from text messaging to Airbnb


*Taking a deep breath and closing your eyes to reflect, you realize that there is so much you can improve in those 45 minutes that you had to discuss your system design. (Even though each interview is one hour, between introductions and Q&A, you essentially have only 45 minutes to design a complex system that typically evolves over years.) Chatting with your fellow engineer friends confirms your hypothesis. You did not thoroughly clarify the system requirements. You assumed that what was needed was a minimum viable product for a backend that serves mobile apps in storing and sharing photos, and you started jotting down sample API specifications. The interviewer had to interrupt you to clarify that it should be scalable to a billion users. You drew a system design diagram that included a CDN, but you didn’t discuss the tradeoffs and alternatives of your design choices. You were not proactive in suggesting other possibilities beyond the narrow scope that the interviewer gave you at the beginning of the interview, such as analytics to determine the most popular photos or personalization to recommend photos to share with a user. You didn’t ask the right questions, and you didn’t mention important concepts like logging, monitoring, and alerting. You realize that even with your engineering experience and your hard work in studying and reading to keep up with industry best practices and developments, the breath of system design is vast, and you lack much formal knowledge and understanding of many system design components that you’ll never directly touch, like load balancers or certain NoSQL databases, so you cannot create a system design diagram of the level of completeness that the interviewer expects, and you cannot fluently zoom in and out when discussing various levels of the system. Until you learn to do so, you cannot meet the hiring bar, and you cannot truly understand a complex system or ascend to a more senior engineering leadership or mentorship role.*

# Part 1
- There are total six chapters in part 1
- Chapter 1 by walking through a sample system and introducing many system design concepts along the way without explaining them in detail,
- In chapter 2, we discuss one’s experience in a typical system design interview. We’ll learn to clarify the requirements of the question and what aspects of the system to optimize at the expense of others. Then we discuss other common topics, including storing and searching data, operational concerns like monitoring and alerting, and edge cases and new constraints.
- In chapter 3, we dive into non-functional requirements, which are usually not explicitly requested by the customer or interviewer and must be clarified prior to designing a system.
- A large system may serve hundreds of millions of users and receive billions of data read and write requests every day. We discuss in chapter 4 how we can scale our databases to handle such traffic.
- The system may be divided into services, and we may need to write related data to these multiple services, which we discuss in chapter 5.
- Many systems require certain common functionalities. In chapter 6, we discuss how we can centralize such cross-cutting functionalities into services that can serve many other systems.

## Chapter 1. A walkthrough of system design concepts
- This chapter covers
  - Learning the importance of the system design interview  
  - Scaling a service
  - Using cloud hosting vs. bare metal
- A system design interview is a discussion between the candidate and the interviewer about designing a software system that is typically provided over a network.
- The interviewer begins the interview with a *short* and *vague* request to the candidate to design a particular software system.

### A discussion about tradeoffs
- System design interviews are given more weight in interviews for senior positions
- This means that a typical engineer will go through system design interviews many times in their career. So these inevitable and there is no escape. 
- Engineers employed at a highly desirable company will go through even more system design interviews as an interviewer.
- As an interview candidate, you have less than one hour to make the best possible impression, and the other candidates who are your competition are among the smartest and most motivated people in the world.
- System design is an art, not a science. It is not about perfection
- We make tradeoffs and compromises to design the system we can achieve with the given resources and time that most closely suits current and possible future requirements.
- A system design interview is not about the right answer.
- It is about one’s ability to discuss multiple possible approaches and weigh their tradeoffs in satisfying the requirements

### Should you read this book?
- The open-ended nature of system design interviews makes it a challenge to prepare for and know how or what to discuss during an interview
- An engineer or student who searches for online learning materials on system design interviews will find a vast quantity of content that varies in quality and diversity of the topics covered.
- This is confusing and hinders learning
- Moreover, until recently, there were few dedicated books on this topic, though a trickle of such books is beginning to be published.
- This is not an introductory software engineering book. At least intermediate proficiency in coding and SQL is assumed.
- This book is best used after one has acquired a minimal level of industry experience.
- This book discusses how to approach system design interviews and minimizes duplication of introductory material that we can easily find online or in other books
- This book offers a structured and organized approach to start preparing for system design interviews or to fill gaps in knowledge and understanding from studying the large amount of fragmented material.
- Equally valuably, it teaches how to demonstrate one’s engineering maturity and communication skills during a system design interview, such as clearly and concisely articulating one’s ideas, knowledge, and questions to the interviewer within the brief ~50 minutes.
- A system design interview, like any other interview, is also about communication skills, quick thinking, asking good questions, and performance anxiety. 
- From personal experience, with seniority one spends an increasing amount of time in meetings, and essential abilities include quick thinking, being able to ask good questions, steering the discussion to the most critical and relevant topics, and communicating one’s thoughts succinctly
- This book emphasizes that one must effectively and concisely express one’s system design expertise within the <1 hour interview and drive the interview in the desired direction by asking the interviewer the right questions.
- System design interviews are biased in favor of engineers with good verbal communication and against engineers less proficient in verbal communication, even though the latter may have considerable system design expertise and have made valuable system design contributions in the organizations where they worked.

