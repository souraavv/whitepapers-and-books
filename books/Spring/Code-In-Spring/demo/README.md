### Prereq 
- Requires postgres to be installed
 - for configuration check demo/src/main/resources/*.yml file 
- Java 23
- Maven 3.9.11 

### Start with project

- Use mvn clean compile to compile to just compile
- or mvn clean install to run test, package your complied code to .jar or war and also install the package into you local mvn repo(~/.m2/repository),s o that other project in your repo can use this.

- To start thing run `mvn spring-boot:run` 
- This will launch your main class ie., the one with annotation @SpringBootApplication (in my case DemoApplication)
- Post that it will configure the beans 
- And we have spring-boot-starter-web it will spin the tomcat and then start listenening `server.port=8080` 

### Test 

- use curl/browser/postman to send request 

#### A sample - 
Note to set no proxy if not set explicitly in this command 

##### create
curl --noproxy localhost -X POST http://localhost:8080/api/persons \
  -H "Content-Type: application/json" \
  -d '{"name":"Alice","email":"alice@example.com"}'
  
##### get all
`curl --noproxy localhost http://localhost:8080/api/persons`

##### fetch by id:
`curl --noproxy localhost http://localhost:8080/api/persons/1`

