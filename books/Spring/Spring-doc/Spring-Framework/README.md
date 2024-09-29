- [The IoC container](#the-ioc-container)
  - [Introduction to the Spring IoC Containers and Beans](#introduction-to-the-spring-ioc-containers-and-beans)
  - [Container Overview](#container-overview)
    - [XML as an External Configuration](#xml-as-an-external-configuration)
    - [Composing XML based Configuration Metadata](#composing-xml-based-configuration-metadata)
  - [Bean Overview](#bean-overview)
    - [Naming Beans](#naming-beans)
    - [Instantiating Beans](#instantiating-beans)
    - [Instantiating by Using an Instance Factory Method](#instantiating-by-using-an-instance-factory-method)
  - [Dependency Injection](#dependency-injection)
    - [Constructor argument resolution](#constructor-argument-resolution)
    - [Setter-based DI](#setter-based-di)
    - [Circular Dependencies](#circular-dependencies)
  - [Dependencies and Configuration in Detail](#dependencies-and-configuration-in-detail)
    - [Straight values (Primitive, String, and so on)](#straight-values-primitive-string-and-so-on)


## The IoC container
### Introduction to the Spring IoC Containers and Beans

- __Inversion of Control__ (IoC) is a broader design principle where the control flow of a program is reversed.
  - Instead of the programmer instantiating dependencies, the responsibility is handed over to an external framework.
- __Dependency Injection__ (DI) is a specific form of IoC.
  - DI is a technique used to achieve IoC, where dependencies are injected into a class, rather than the class creating the objects itself.
    <details>
    <summary>Without DI </summary>

    ```java
    public class NotificationService {
        private EmailService emailService = new EmailService();
        
        public void sendNotification(String message) {
            emailService.sendEmail(message);
        }
    }
    ```
    - In the above example `NotifactionService` is tightly coupled with the `EmailService` 
    </details> 

    <details>
    <summary>With DI </summary>
    
    ```java

    public interface MessagingService {
        void sendMessage(String message);
    }

    public class EmailService implements MessagingService {
        @Override
        public void sendMessage(String message) {
            System.out.println("Sending email: " + message);
        }
    }

    public class SmsService implements MessagingService {
        @Override
        public void sendMessage(String message) {
            System.out.println("Sending SMS: " + message);
        }
    }

    public class NotificationService {
        private final MessagingService messagingService;
        
        // Constructor Injection
        public NotificationService(MessagingService messagingService) {
            this.messagingService = messagingService;
        }

        public void sendNotification(String message) {
            emailService.sendEmail(message);
        }
    }

    // Configure the beans
    @Configuration
    public class AppConfig {

        @Bean
        public MessagingService emailService() {
            return new EmailService();
        }

        @Bean
        public NotificationService notificationService(MessagingService messagingService) {
            return new NotificationService(messagingService);
        }
    }

    // Use Spring IoC 
    public class Application {
        public static void main(String[] args) {
            // Configuration is passed using Annotation 
            ApplicationContext context = new AnnotationConfigApplicationContext(AppConfig.class);

            // Spring automatically injects the EmailService into NotificationService
            NotificationService notificationService = context.getBean(NotificationService.class);
            
            notificationService.sendNotification("Hello, Spring DI!");
        }
    }

    ```
    </details> 
  - In case of DI object defines their dependency only through **constructor arguments**, **arguments to a factory method**, or **properties that are set on the object instance after it is constructed**

- The `org.springframework.beans` and `org.springframework.context` packages are the basic of Spring Framework IoC's containers
- The `BeanFactory` interface provides an advanced configuration mechanism capable of managing any type of objects
  - `BeanFactory` provides the configuration framework and basic functionality 
- `ApplicationContext` is a sub-interface of `BeanFactory`
  - `ApplicationContext` adds more enterprise-specific functionality 
  - `ApplicationContext` is a superset of `BeanFactory` 

- In Spring, the objects which are backbone of your application and that are managed by Spring IoC contianers are called as __beans__
- A bean is an object that is instantiated, assembled, and managed by Spring IoC container 


### Container Overview 

- The `org.springframework.context.ApplicationContext` interface represents the Spring IoC container and is responsible for the instantiating, configuring, and assembling the beans
  - Several implementation of this interfaces are part of Spring. In stand-alone application it is common to create `AnnotationConfigApplicationContext` or `ClassPathXmlApplicationContext` 
  - Spring IoC containes consumes a form of configuration
    - __Annotation-based configuration__ 
      - `@Autowired`
    - __Java-based configuration__ 
      - `@Configuration`, `@Bean`, `@DependsOn`, and `@Import` 
      - In a configuration class use bean annotated method 
  
#### XML as an External Configuration 
- Why called external ? Becuase not a part of the code, unlike others i.e., `Annotation` and `Java` based configurations
    <details>
    <summary> XML configuration - sample </summary>

    ```xml
    <?xml version="1.0" encoding="UTF-8"?>
    <beans xmlns="http://www.springframework.org/schema/beans"
        xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
        xsi:schemaLocation="http://www.springframework.org/schema/beans
            https://www.springframework.org/schema/beans/spring-beans.xsd">

        <bean id="..." class="...">  
                <!-- collaborators and configuration for this bean go here -->
        </bean>
    ```
    </details>

- The `id` attribute is a string that identifies the individual bean definition.
  - This can be refer to collaborating objects
- The `class` attribute defines the type of the bean and uses the fully qualified class name. 
    ```java
    ApplicationContext context = new ClassPathXmlApplicationContext("services.xml", "daos.xml");
    ```

<details>
<summary> Sample: services.xml & daos.xml  </summary>

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://www.springframework.org/schema/beans
		https://www.springframework.org/schema/beans/spring-beans.xsd">

	<!-- services -->

	<bean id="petStore" class="org.springframework.samples.jpetstore.services.PetStoreServiceImpl">
		<property name="accountDao" ref="accountDao"/>
		<property name="itemDao" ref="itemDao"/>
		<!-- additional collaborators and configuration for this bean go here -->
	</bean>

	<!-- more bean definitions for services go here -->

</beans>

```

- `ref`: Refers to the bean ID in the Spring container that will be injected as a dependency.
  - These references are also called __collaborators__ or __dependencies__.
- `name`: Refers to the property name of the class that will receive the dependency.

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
	xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
	xsi:schemaLocation="http://www.springframework.org/schema/beans
		https://www.springframework.org/schema/beans/spring-beans.xsd">

	<bean id="accountDao"
		class="org.springframework.samples.jpetstore.dao.jpa.JpaAccountDao">
		<!-- additional collaborators and configuration for this bean go here -->
	</bean>

	<bean id="itemDao" class="org.springframework.samples.jpetstore.dao.jpa.JpaItemDao">
		<!-- additional collaborators and configuration for this bean go here -->
	</bean>

	<!-- more bean definitions for data access objects go here -->

</beans>
```

</details>


#### Composing XML based Configuration Metadata

- Use `import` to load beans definition from another file or files 
    <details>
    <summary> Example of import </summary>

    ```xml
    <beans>
        <import resource="services.xml">
        <import resource="resources/messageSource.xml">
        <import resource="resources/themeSource.xml">

        <bean id="bean1" class="..."/>
        <bean id="bean2" class="..."/>
    </beans>

    ```

    </details>


    #### Using the Container

    ```java

    ApplicationContext context = new ClassPathXmlApplicationContext("services.xml", "daos.xml");

    // Use getBean to retrieve the instance of your bean 
    PetStoreService service = context.getBean("petStore", PetStoreService.class);

    List<String> userList = service.getUserNameList();

    ```

### Bean Overview 

The bean definition 

| Property | IoC term | Example | 
|---|---| -- |
| Class | Instantiating Beans| Which Java class Object spring will create |
| Name  | Naming Beans | id or name field |
| Scope | Bean Scope | singleton or prototype | 
|Constructor Argument | Dependency Injection | Argument to the constructor | 
|Properties | Depedency Injection |  Injection to the setters | 
| Autorwiring mode | Autowiring Collaborators |  Automatic inject matching beans or manually |
| Initialization method | Initialization Callbacks | After bean creation if something needs to be initialize |
| Desctruction method | Destruction Callbacks | Clean up after baen is destoryed |


<details>
<summary> An odd path - Registering objects as bean (which are not part of container) </summary>

- Yes, `ApplicationContext` allows you to register an object which was created outside the container. But this is least used (not recommended in general)
- First get the Bean factory `getBeanFactory()` which returns `DefaultListableBeanFactory` and then use methods `registerSingleton(...)` or `registerBeanDefinition(..)` 

    ```java
    public class MyService {
        public void doSomething() {

        }
    }
    ```

    ```java

    import org.springframework.context.ApplicationContext; 
    import org.springframework.context.support.ClassPathXmlApplicationContext;
    import org.springframework.beans.factory.config.ConfigurableListBeanFactory;

    public class MainApp {
        public static void main(String[] args) {
            ApplicationContext context = new ClassPathXmlApplicationContext("beans.xml");
            MyService myService = new MyService();
            ConfigurableListBeanFactory beanFactory = ((ClassPathXmlApplicationContext) context).getBeanFactory();
            beanFactory.registerSingleton("myServiceBean", myService);

            MyService serviceFromContext = (MyService) context.getBean("myServiceBean");
            serviceFromContext.doSomething();
        }
    }
    ```

</details>

#### Naming Beans

> [!NOTE]
> Every bean has one or more identifiers
> Each must be unique. If multiple then other are aliases.

```xml
<bean id="myBean" name="beanAlias1, beanAlias2" class="com.example.MyBean"/>
```
- Both `id` and `name` are optional, if not provided then Spring container generate a unique name for that bean
  - But if you want to use `ref` then you have to assign a name
  - Not supplying a `name` is relevant in case of inner beans
    <details>
    <summary> Inner bean (Short live or Temporary Beans)</summary>

    ```xml
        <beans>
            <bean id="engine" class="com.example.Engine">
                <property name="type" value="V8"/>
            </bean>

            <bean id="car" class="com.example.Car">
                <property name="engine">
                    <bean class="com.example.Engine">
                        <property name="type" value="V8"/>
                    </bean>
                </property>
            </bean>
        </beans>
    ```
    </details>
  - Spring scans components (`@Component`, `@Service`, `@Repository`, and `@Controller`)
    - If not named, then name based on the rule
      - __Simple Class Name__ i.e., if class name `MyService` then `myService`
      - If `HTMLParser` then it keep it as same (both H and T are capital)

#### Instantiating Beans
- Bean Definition 
  - `class`: which class's object container need to create
  - Two ways to use `class` property either direct (constructor call) or static factory method 
    - Direct: 
        ```xml
        <bean id="myBean" class="com.example.MyClass"/>
        ```
    - Static Factory Method: 
      ```xml
      <bean id="myBean" class="com.example.MyFactoryClass" factory-method="createMyClass"/>
      ```
      ```java
        public class MyFactoryClass {
            private static MyFactoryClass myFactoryClass = new MyFactoryClass();
            private MyFactoryClass() {}

            public static MyFactoryClass createMyClass() {
                return myFactoryClass;
            }
        }
      ```
  - Nested Classes
    ```xml
      <bean id="myNestedBean" class="com.example.SomeThing.OtherThing"/>
      <bean id="myNestedBean" class="com.example.SomeThing$OtherThing"/>
    ```

- No special treatement is required before making a class as Bean in Spring. You can use this with any class

#### Instantiating by Using an Instance Factory Method 

- Factory beans itself can be managed through __DI__

>[!NOTE]
> In Spring "Factory bean" refer to a bean that is configured in Spring contianer and that itself can creates object through an `instance` or `static` factory method.


```java
public class DefaultServiceLocator {
    private static ClientService clientService = new ClientServiceImpl();
    private static AccountService accountService = new AccoutnServiceImpl();

    public ClientService createClientServiceInstance() {
        return clientService;
    }

    public AccountService createAccountServiceInstance() {
        return accountService;
    }
}
```

```xml

<bean id="serviceLocator" class="example.DefaultServiceLocator">
</bean>

<bean id="clientService" factory-bean="serviceLocator" factory-method="createClientServiceInstance"/>
<bean id="accountService" factory-bean="serviceLocator" factory-method="createAccountServiceInstacne"/>
```


### Dependency Injection 

- DI is a process whereby objects defines their depedencies 
  - Through constructor arguments
  - Arguments to a factory method 
  - Properties set on an object instance after it is constructed or returned from a factory method
- The container inject these dependency while creating the bean 
- The process is fundamentally inverse thus called IoC 
- Code is more clean with DI 
- Decoupling is more effective when objects are provided with their dependencies 
  - Use of Intefaces and DI makes you easy to test using `Mock`
    <details>
    <summary> An example </summary>

    ```java
    public interface MessageService {
        void send(String msg);
    }
    ```

    ```java
    public class EmailService implements MessageService {
        void send(String msg) {
            log.info("Email service msg");
        }
    }

    public class SmsService implements MessageService {
        void send(String msg) {
            log.info("SMS service");
        }
    }

    ```

    ```java
    public class NotificationService {
        private MessageService messageService;

        public NotificationService(MessageService messageService) {
            this.messageService = messageService;
        }

        public sendNotification(String message) {
            messageService.sendMessage(message);
        }
    }
    ```
    - Mock 
    ```java
    public class MockMessageService implements MessageService {
        void send(String msg) {
            log.info("mocked message service");
        }
    }
    ```
    ```java
    public class NotificationServiceTest {
        public static void main(String[] args) {
            MessageService mockService = new MockMessagingService();

            NotificationService notificationService 
                    = new NotificationService(mockService);

            notificationService.sendNotification("Test Message");
        }
    }

    ```
    </details>

#### Constructor argument resolution
- Order in which they are defined in the bean is the same order they are passed to the constructor
    <details>
    <summary> Example - constructor argument resolution </summary>


    ```xml
    <beans>
        <bean id="beanOne" class="x.y.ThingOne">
            <constructor-arg ref="beanTwo"/>
            <constructor-arg ref="beanThree"/>
        </bean>

        <bean id="beanTwo" class="x.y.ThingTwo"/>
        <bean id="beanThree" class="x.y.ThingThree"/>

    </beans>
    ```

    ```java
    package x.y;

    public class ThingOne {
        public ThingOne(ThingTwo thingTwo, ThingThree thingThree) { 
        }
    }
    ```

    </details>

- Constructor arg type matching
    ```xml
        <bean id="exampleBean" class="examples.ExampleBean">
            <constructor-arg type="int" value="7500000"/>
            <constructor-arg type="java.lang.String" value="42"/>
        </bean>
    ```
- Constructor argument index
    ```xml
        <bean id="exampleBean" class="examples.ExampleBean">
            <constructor-arg index="0" value="7500000"/>
            <constructor-arg index="1" value="42"/>
        </bean>
    ```

> [!NOTE]
> Index is 0-based


#### Setter-based DI 
- By calling `static` method on your beans after invoking a no-arg constructor or a no-arg `static` factory method to init your beans
    <details>
    <summary>DI using setters </summary>

    - Conventional Java class. It is POJO that has no dependencies on the container
    ```java
        public class Employee {
            private Address address;  // External dependency

            // No-argument constructor
            public Employee() {}

            // Setter method for dependency injection
            public void setAddress(Address address) {
                this.address = address;
            }

            public void showEmployeeDetails() {
                System.out.println("Employee Address: " + address);
            }
        }
    ```

    ```xml
        <beans>

        <bean id="addressBean" class="com.example.Address">
            <property name="city" value="Mumbai"/>
            <property name="state" value="Maharashtra"/>
        </bean>

        <bean id="employeeBean" class="com.example.Employee">
            <!-- Setter-based injection -->
            <property name="address" ref="addressBean"/> 
        </bean>
        </beans>

    ```
    </details>
- `ApplicationContext` support __constructor-based__ and __setter-based__ DI for the beans 
  - It also supports __setter-based__ DI when some of the dependencies have already bean injected through constructor approach
- When it is used ?
  - Optional dependencies

> [!TIP]
> Constructor-based DI is preferred for mandatory dependencies as it ensures that the object is fully initialized and its dependencies are not null, supporting immutability.
>
> Setter-based DI, on the other hand, is more suitable for optional dependencies or scenarios where flexibility is required to reconfigure the object later.
>
> Constructor injection is generally advocated by the Spring team
>


#### Circular Dependencies
- If Class A depends on class B and Class B depends on A
- Solution is to use __setter-based__ instead __constructor-based__ DI
- A circular dependency between bean A and bean B forces one of the beans to be injected into the other prior to being fully initialized itself
- Spring detect all these problems at early, during container load time 
  

> [!NOTE]
> constructor-arg : `<bean id="" class=""> <constructor-arg ref=""/> </bean>`
>
> factory-method: `<bean id="" class="" factory-method=""/>`
>
> setter-based: `<bean id="" class=""><property name="" value=""/>`


### Dependencies and Configuration in Detail

#### Straight values (Primitive, String, and so on)
- Properties and constructor arg can be define in two different ways i.e., __Inline values__ and __References__ 
    <details>
    <summary> Inline Values (String, Primitive, etc.) </summary>

    - Inline values
        ```xml
        <bean id="myDataSource" class="org.apache.commons.dbcp.BasicDataSource" destroy-method="close">
            <!-- String values as property settings -->
            <property name="driverClassName" value="com.mysql.jdbc.Driver"/>
            <property name="url" value="jdbc:mysql://localhost:3306/mydb"/>
            <property name="username" value="root"/>
            <property name="password" value="misterkaoli"/>
        </bean>
        ```

    - p-Namespace for simplified configuration 

        ```xml
        <bean id="..", class=".." destory-method="close"    
            p:url=".."
            p:username=".."
            p:password=".."/>
        ```

    - `idref` element
      - The idref element is simply an error-proof way to pass the id (a string value, not a reference) of another bean in the container to a `<constructor-arg>` or `<property/>`
        ```xml

        <bean id="id1" class=".."/>
        <bean>
            <property name="..">
                <idref bean="id1">
            </property>
        </bean>
        ```

    - The above is equivalent to below, but more safe, because `idref` tag let the container validate at deployment time, whether bean actually exists or not
        ```xml
        <bean id="id1" class="..." />
        <bean id="client" class="...">
            <property name=".." value="id1"/>
        </bean>
        ```

    </details>
