
- [Acing the System Design Interview](#acing-the-system-design-interview)
- [Part 1](#part-1)

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
