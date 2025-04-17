
Terms:

## Config
- Contains class annotated with @Configuration, @Component, @Autowired, @Value, @EnableResourceServer, @EnableSwagger2, @Bean, 

### Annotations
- `@Controller`
    - Used to mark a class as Spring MVC Controller (Web Controller - as this returns VIEW - JSP, Thymeleaf, HTML)
    - There is a variant to this `@RestController` that returns JSON or XML responses (API response)
    - This class is responsible for handling HTTP requests and returning responses
    - Class level annotation: `@RequestMapping("/endpoint/path")` is also used to map all the request starting with "/endpoint/path" to this controller
    - Method level annotation: `@GetMapping("/user/{id}")` - Method will handle the **HTTP GET** requests 
    - `@PostMapping()`, `@PutMapping("/{id}")`, `@DeleteMapping("/{id}")`
    - The values like ID can be fetch to a Java variable via `@PathVariable` annotation e.g., `public String deleteUser(@PathVariable Long id)`
    - `@RequestBody` - Converts the JSON request body into Java Object
    - `@ResponseBody` - Converts method return value into JSON/XML
    - 
- `@Component`: 

### Controller
### Annotations

### @Component
### @Bean
### @Configuration 
### feign (RequestInterceptors)

## Repository (DAO : Data Access Object) 

## Resources > db/migration (Vi_)
### JWTKeystore.p12
### application.yml
### bootstrap.yml 
### JWT signing public key
### Logback-Spring
## Services
### /impl
### Interfaces

## WEB
### DockerFile
### Dockerize
### mvnw
### mvnw.cmd
### pom.xml 


## Hibernate

### @Entity
### @Table
### @ManyToMany
### @JoinTable
### @Id
### @GeneratedValute
### @GenericGenerator
### @Column()
### @Builder
### @Transactional
### CrudRepository (org.springframework.data.repository)
#### Concept
- Repository pattern ek design pattern ahi jo **data persistence logic** ko business logic se alag karta hai
- Without actual low-level code for database operation, you can operate CRUD on the entities (domain object) 
- Benefits: Abstraction
#### CrudRepository - Interface
- Interface hai jo basic CRUD operations provide karta hai. Jaise ki - 
    - `save(entity)` - 
    - `findById(id)`
    - `findAll()`
    - `delete(entity)`
    - `deleteById(id)`

- From doc
    ```java
    @NoRespositoryBean
    public interface CrudRepository<T, ID> extends Repository<T, ID>
    ```
    - Interfce for generic CRUD operations on a repository for a specific type.
    - E.g., `<S extends T> S save(S entity)` 
- Examples:
```java
// File: /repository/UserRepository.java

@Transactional
public interface UserRespository extends CrudRepository<User, Long> {
    Optional<User> findByUserName(String userName);
    ...
    Boolean existsByEmail(String email);
}
```
- The `CrudRepository` is just an interface.. the implementation comes from some JPA provider (Java Persistence API)
- In Spring Boot, this comes from Hibernate JPA implementation (JPA is a set of specification) 
- Spring creates proxy object, which intercept all the reqeust to the respository created by client (by extending say CrudRespository)
- Whenever you inject `UserRespository` interface, Spring Data JPA proxy object create karta hai. Is proxy object ke pass actual methods ka implementation hota hai, jo internally Hibernate ke through database interaction ko handle karta hai 

```java

@Autowired
private UserRepository userRepository;

public void getUserDetails() {
    List<User> users = userRepository.findByLastName("...");
}
```
- Spring AOP (Aspect Oriented Programming)
    - Purpose: Isolate the aspect from the business logic - like Security, Logging, Caching, Transactional Management
    - Purpose: Increase modularity by allowing the separation of cross-cutting concerns (means those which impact mulitple parts of the application)
- When these cross-cutting concers are brought into separate unit, they are called as **aspect**
- **Advice** - This is the action taken by an aspect at a particual join point. There are five type of advice:
    - Before
    - After: After method (always)
    - AfterReturning: Only when result (no exception)
    - Around
    - AfterThrowing
- **Pointcut** - A predicate that matches the join points. A pointcut expression specifies where an advice should be applied (done via `@PointCut`)
- **Weaving** - The process of linking aspects with the target object. This can occur at compile-time, load-time, or runtime. Spring AOP performs runtime weaving using proxy-based mechanism.

- Annotations
    - `@Aspect`: Marks the class as an aspect (which contains cross-cutting concerns)
    - `@Component`: Register this aspect as a Spring Bean

- Example in Spring AOP 
```java

@Aspect
@Component
public class LoggingAspect {
    
    @Pointcut("execution(public void com.example.service.*.*(..))")
    // Defines a pointcut that matches the execution of any public method in class under
    // com.example.service package
    public void allServicesMethod() {}


    @Before("allServiceMethod()")
    // Advice that runs before the execution of methods matched by the pointcut 
    public void logBefore(JointPoint jointPoint) {
        System.out.println("Before method: " + joinPoint.getSignature().getName());
    }

    @After(...)

    @AfterReturning(pointcut = "allServiceMethods()", returning "result")

    // Advice 
    @Around("allServiceMethods()")





}

```

- There are many popular AOP frameworks
    - AspectJ
    - JBoss AOP
    - Spring AOP  - Proxy-based framework



### JpaRepository 
- Extends `CrudRepository` and `PagingAndSortingRepository` e.g.,

```java
@GetMapping("/users")
public Page<User> getUsers(Pageable pageable) {
    return userRepository.findAll(pageable);
}
```


