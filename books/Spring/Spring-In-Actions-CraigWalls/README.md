
- [Spring in Actions By Craig Walls](#spring-in-actions-by-craig-walls)
  - [Getting Started with Spring](#getting-started-with-spring)
    - [What is Spring ?](#what-is-spring-)
    - [History](#history)
    - [Init a Spring application](#init-a-spring-application)
    - [Writing a Spring Application](#writing-a-spring-application)
      - [Handling web requests](#handling-web-requests)
      - [Defining the view](#defining-the-view)
      - [Testing the controller](#testing-the-controller)
      - [Building and running the application](#building-and-running-the-application)
      - [Getting to know Spring Boot DevTools](#getting-to-know-spring-boot-devtools)
    - [Spring landscape](#spring-landscape)
      - [Core Spring framework](#core-spring-framework)
      - [Spring Boot](#spring-boot)
      - [Spring Data](#spring-data)
      - [Spring Security](#spring-security)
      - [Spring cloud](#spring-cloud)
      - [Spring Native](#spring-native)

# Spring in Actions By Craig Walls

![Pink Spring in Japan](images/spring-in-japan.webp)
Cherry blossoms bloom, a pink sky's embrace,
Spring whispers in Japan, a fleeting grace

## Getting Started with Spring 
### What is Spring ?
- Application comprises of many components
- Each component owns some functionality and coordinate with the other components to get the job done
- Spring offers containers/Application context 
  - Container creates and manage the application components
  - These components (or beans) are wired together inside the context to make complete application 
  - The act of wiring together these beans is based on pattern known as *dependency injection (DI)*
- Rather than have components create and maintain LCM of other beans they depends on a DI based application relies on a separate entity i.e., container
  - Achieved using i) Constructor args ii) Property accessor methods 
- On top of container Spring offers a full portfolio of related libraries 
  - Web frameworks
  - Variety of data persitent options
  - Security framework
  - Runtime monitoring
  - Microservice support 
  - Reactive programming model 
- You can consider Spring boot as *frameworkless* framework 
  - Benefit of developing with Spring is that you can focus on code that meets the requirements of the application, rather than satisfying the demand of the farmework
  - The code for framework will remain only a small fraction of codebase
### History
- How would you guide Spring application context (container) to wire beans together ? 
  - By providing configuration through xml files 
  - The xml files defines the relationship between beans. An example below, where `productService` depends on `inventoryService`
    ```xml
    <bean id="inventoryService"
      class="com.example.InventoryService" />
 
    <bean id="productService"
        class="com.example.ProductService" >
    <constructor-arg ref="inventoryService" />
    </bean>
    ```
  - Apart from xml file, Java-based configuration is more common. An example below (equivalent to the xml)
    ```java
    @Configuration      // <--- indicates that this a configuration file 
    public class ServiceConfiguration {
        @Bean // <---  Tells that object this method returns should be added as bean in the context 
        public InventoryService inventoryService() {
            return new InventoryService();
        }
        @Bean
        public ProductService productService() {
            return new ProductService(inventoryService());
        }
    }
    ```
  - There are pros and cons of both the approaches
  - Although Spring also offers *autowiring* and *component scaning* for automatic configuration 
    - With component scanning Spring can automatically discover components from the application classpath and create them as beans
    - With autowiring, Spring automatically injects the components with the other beans that they depends on

### Init a Spring application 
- Using **Spring Initializr**. 
  ```java 
    package com.souravsh.taco;

    import org.springframework.boot.SpringApplication;
    import org.springframework.boot.autoconfigure.SpringBootApplication;

    @SpringBootApplication
    public class TacoApplication {

        public static void main(String[] args) {
            SpringApplication.run(TacoApplication.class, args);
        }

    }
  ```
- `@SpringBootApplication` is a composite annotation that combines 
  - `@SpringBootConfiguration` 
    - Designate the class a configuration class (annotation is special case of `@Configuration` annotation)
  - `@EnableAutoConfiguration` 
    - Enables automatic configuration 
  - `@ComponentScan` 
    - Allows you to use/declare classes using `@Component`, `@Controller` and `@Service`
  - The static method `SprigApplication.run` performs the actual bootstrapping of the application, creating Spring context 

### Writing a Spring Application 

#### Handling web requests
- Spring comes with a powerful web framework known as Spring MVC
  - Controller is the class that handles requests and responds with information
  - In case of browser facing application, a controller responds by optionally populating model data and passing the request on to a view to produce HTML that returned to the browser

#### Defining the view
- Under `/resources/template/<view_name>.html`
    ```html
    <!DOCTYPE html>
    <html xmlns="http://www.w3.org/1999/xhtml"
        xmlns:th="http://www.thymeleaf.org">
    <head>
        <title>Taco Cloud</title>
    </head>
    
    <body>
        <h1>Welcome to...</h1>
        <img th:src="@{/images/spring-in-japan.webp}"/>
    </body>
    </html>
    ```

#### Testing the controller
```java

@WebMvcTest(HomeController.class)
public class HomeControllerTest {

    @Autowired
    private MockMvc mockMvc;

    @Test
    public void testHomePage() throws Exception {
        mockMvc.perform(get("/"))
                .andExpect(status().isOk())
                .andExpect(view().name("home"))
                .andExpect(content().string(containsString("Welcome to...")));
    }
}

```

#### Building and running the application
```bash
./mvnw package
./mvnw test 
```
- As application starts, Tomcat started on port(s): 8080(http), which means that you're ready to point your web browser at the home page 
- Spring boot's autoconfiguration library automatically performs
  - Configures the beans in the context to enable MVC
  - Configures the embedded Tomcat server in the context
  
#### Getting to know Spring Boot DevTools
- Automatic application restart when code changes
- Automatic browser refresh when browser-destined resources
- Automatic disabling of template caches

### Spring landscape 
#### Core Spring framework
#### Spring Boot
#### Spring Data
#### Spring Security 
#### Spring cloud
#### Spring Native 
