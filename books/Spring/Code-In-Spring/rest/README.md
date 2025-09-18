- `mvn spring:boot:run`
- `mvn -Dspring-boot.run.profiles=local spring-boot:run`
- CommandLineRunner is an interface that has run() method. Which is used to execute some code just after the spring boot application has started. The main application should implement this interface and override its run method. In this run method, we write code like initializing our database with some value or any other logic which should be executed just after the app starts.
- A more useful way to consume a REST web service is programmatically. To help you with that task, Spring provides a convenient template class called RestTemplate. RestTemplate makes interacting with most RESTful services a one-line incantation. And it can even bind that data to custom domain types.

