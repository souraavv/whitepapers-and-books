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
    - [Primitive or Straight values (String, int, and so on)](#primitive-or-straight-values-string-int-and-so-on)
    - [Collections](#collections)
    - [Compound property name](#compound-property-name)
  - [Depends-On](#depends-on)
  - [Lazy-initialized Beans](#lazy-initialized-beans)
  - [Autowiring](#autowiring)
  - [Method Injection](#method-injection)
  - [Bean Scopes](#bean-scopes)
    - [Singleton](#singleton)
    - [Prototype](#prototype)
    - [Singleton Beans with Prototype-bean Dependencies](#singleton-beans-with-prototype-bean-dependencies)
    - [Web Aware Application Context](#web-aware-application-context)
  - [Customizing the Nature of Beans](#customizing-the-nature-of-beans)
    - [Lifecycle Callbacks](#lifecycle-callbacks)
  - [Annotation-based container configuration](#annotation-based-container-configuration)


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

#### Primitive or Straight values (String, int, and so on)
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

    - c-Namespace
      - `ref` is used as suffix in case of references
        ```xml
            <bean id="beanOne" class="x.y.ThingOne" c:thingTwo-ref="beanTwo"
                    c:thingThree-ref="beanThree" c:email="something@somewhere.com"/>
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

#### Collections

<details>
<summary>List, Set, Map, Props</summary>

```xml
<bean id="moreComplexObject" class="example.ComplexObject">
    <!-- Properties defined using the props element -->
    <property name="adminEmails">
        <props>
            <prop key="administrator">administrator@example.org</prop>
            <prop key="support">support@example.org</prop>
            <prop key="development">development@example.org</prop>
        </props>
    </property>
    <!-- List property -->
    <property name="someList">
        <list>
            <value>a list element followed by a reference</value>
            <ref bean="myDataSource" />
        </list>
    </property>
    <!-- Map property -->
    <property name="someMap">
        <map>
            <entry key="an entry" value="just some string"/>
            <entry key="a ref" value-ref="myDataSource"/>
        </map>
    </property>
    <!-- Set property -->
    <property name="someSet">
        <set>
            <value>just some string</value>
            <ref bean="myDataSource" />
        </set>
    </property>
</bean>

```

</details>


#### Compound property name

- The `something` bean has a `fred` property, which has a `bob` property, which has a `sammy` property, and that final `sammy` property is being set to a value of `123`
    ```xml
    <bean id="something" class="things.ThingOne">
        <property name="fred.bob.sammy" value="123" />
    </bean>
    ```

- In order for this to work, the fred property of `something` and the `bob` property of `fred` must not be `null` after the bean is constructed. Otherwise, a `NullPointerException` is thrown.


### Depends-On 

- The `depends-on` attribute can explicitly force one or more beans to be initialized before the bean
- Sometimes dependencies between beans are less direct. 
  - An example is when a static initializer in a class needs to be triggered, such as for database driver registration. 
  - The `depends-on` attribute can explicitly force one or more beans to be initialized before the bean using this element is initialized. 

- Depends on Single Bean
    ```xml
    <bean id="beanOne" class="ExampleBean" depends-on="manager"/>
    <bean id="manager" class="ManagerBean" />
    ```
- Or multiple
    ```xml
        <bean id="beanOne" class="ExampleBean" depends-on="manager,accountDao">
            <property name="manager" ref="manager" />
        </bean>

        <bean id="manager" class="ManagerBean" />
        <bean id="accountDao" class="x.y.jdbc.JdbcAccountDao" />
    ```

- `depends-on` can also control shutdown order.
-  Dependent beans that define a `depends-on` relationship with a given bean are destroyed first, prior to the given bean itself being destroyed


### Lazy-initialized Beans

- By default, Spring's `ApplicationContext` eagerly initializes all singleton beans during startup to quickly identify configuration errors
- However, you can prevent this behavior by using __lazy initialization__, where a bean is created only when it is first requested.
- In XML, this is controlled by the lazy-init attribute in the `<bean/>` element.
- If a lazy-initialized bean is a dependency of a non-lazy singleton bean, it will be instantiated at startup to satisfy that dependency
    ```xml
    <bean id="lazy" class="com.something.ExpensiveToCreateBean" lazy-init="true"/>
    <bean name="not.lazy" class="com.something.AnotherBean"/>
    ```
- Make all beans __lazy__
    ```xml
    <beans default-lazy-init="true">
        <!-- Ab koi bhi bean pre-instantiated nahi hoga... -->
    </beans>
    ```

### Autowiring 
- The Spring container can autowire relationships between collaborating beans
- You can let Spring resolve collaborators (other beans) automatically for your bean by inspecting the contents of the `ApplicationContext`
- Autowiring can significantly reduce the need to specify properties or constructor arguments
- Autowiring can update a configuration as your objects evolve. 
  - For example, if you need to add a dependency to a class, that dependency can be satisfied automatically without you needing to modify the configuration.
- Thus autowiring can be especially useful during development, without negating the option of switching to explicit wiring when the code base becomes more stable.

| Autowire Mode |	Description |
|---|---|
| no |	Default mode. No autowiring will be performed. |
| byType |	Autowires by property type. Spring looks for a bean of the same type. |
| byName |	Autowires by property name. Spring looks for a bean with the same name as the property. |
| constructor |	Autowires using the constructor. Spring resolves dependencies via constructor arguments.|

-
    <details>
    <summary>Simple Example of Autowiring </summary>

    ```java
    public class DataSource {
        public void connect() {}
    }

    public class UserService {
        private DataSource dataSource;

        public void setDataSource(DataSource dataSource) {
            this.dataSource = dataSource;
        }

        public void performAction() {}
    }
    ```
  
    ```xml
    <beans>
        <bean id="dataSource" class="com.example.DataSource" />

        <!-- Autowire byType -->
        <bean id="userService" class="com.example.UserService" autowire="byType" />
        <!-- Autwirte byName -->
        <bean id="userService" class="com.example.UserService" autowire="byName" />
        <!-- constructor -->
        <bean id="userService" class="com.example.UserService" autowire="constructor"/>

    </beans>
    ```

    ```java
        public class UserService {
            private final DataSource dataSource;

            // Constructor injection
            public UserService(DataSource dataSource) {
                this.dataSource = dataSource;
            }

            public void performAction() {
                dataSource.connect();
                System.out.println("Action performed in UserService.");
            }
        }
    ```


    </details>


### Method Injection 

- __Singleton vs Prototype Problem__: In Spring, most beans are singletons, meaning they are created only once. But sometimes, a singleton bean (A) might need a fresh instance of a prototype bean (B) for every method call. How do you get a new instance every time?
- __The Challenge__: Once Spring creates a singleton bean, it only sets the dependencies once. If a singleton bean depends on a prototype, it can only access the same prototype instance every time—not what we want!
- __Common Fix__: Using `getBean()` from the Spring container provides new prototype instances but couples your code to Spring.
- __Method Injection__: Allows Spring to automatically inject a new prototype instance each time, without coupling your code to Spring.

<details>
<summary></summary>

```java

import org.springframework.context.ApplicationContext;
import org.springframework.context.ApplicationContextAware;

public class CommandManager implements ApplicationContextAware {
    private ApplicationContext applicationContext;

    public Object process(Map)
}


```
</details>


### Bean Scopes
- Spring supports six scopes 

| Scope | Description |
|---|---|
| Singleton | Single object instance for each Spring IoC Container |
| Prototype | Scopes a single bean definition to any number of instances | 
| Request | Scope is a single HTTP Request (web-aware Application Context) | 
| Session | lifecycle of an HTTP session (web-aware Application Context)| 
| Application | lifecycle of a Servlet Context (web-aware..) |
| WebSocket | valid in the context of web socket | 


#### Singleton 
- Spring IoC creates exactly one instance of the object defined by the bean definition 
    ```xml
    <bean id="accountService" class="com.something.DefaultAccountService"/>
    <!-- the following is equivalent, though redundant (singleton scope is the default) -->
    <bean id="accountService" class="com.something.DefaultAccountService" scope="singleton"/>
    ```


#### Prototype 
- Non-singleton (a new bean instance every time a request for that specific bean is made)
    ```xml
    <bean id="accountService" class="com.something.DefaultAccountService" scope="prototype"/>
    ```

#### Singleton Beans with Prototype-bean Dependencies
- If Singleton dependes on Prototype bean
  - When Spring creates the singleton bean, it injects one instance of the prototype bean (at the time of creation)
- The singleton continues using this same prototype instance, even though prototypes should be fresh each time.
- To get new prototype instances at runtime, regular dependency injection won’t work; use method injection instead.
    ```java
    @Component 
    public class SingletonBean {

        public void performTask() {
            PrototypeBean pb = getPrototypeBean();
            pb.doSomething();
        }

        // This method will return a new PrototypeBean instance every time it's called
        @Lookup
        public PrototypeBean getPrototypeBean() {
            // Spring overrides this method with logic to return a new prototype bean
            return null;
        }
    }
    ```


#### Web Aware Application Context

```xml
<bean id="loginAction" class="com.something.LoginAction" scope="request"/>
```

```java
@RequestScope
@Component
public class LoginAction {
	// ...
}
```


```xml
<bean id="userPreferences" class="com.something.UserPreferences" scope="session"/>
```

```java
@SessionScope
@Component
public class LoginAction {
	// ...
}
```


```xml
<bean id="appPreferences" class="com.something.AppPreferences" scope="application"/>
```

```java
@ApplicationScope
@Component
public class LoginAction {
	// ...
}
```


```xml
<bean id="loginAction" class="com.something.LoginAction" scope="session"/>
```

```java
@SessionScope
@Component
public class LoginAction {
	// ...
}
```

- Spring also allows to have custom scopes

### Customizing the Nature of Beans

#### Lifecycle Callbacks

- Keeping this section for future TODO, might not be required at this point
- For now just remember that 
  - The Spring Framework allows bean customization through various interfaces: Lifecycle Callbacks for managing bean initialization and destruction, `ApplicationContextAware` and `BeanNameAware` for accessing context and bean details, and Other Aware Interfaces for additional capabilities.


### Annotation-based container configuration

- Instead of xml use annotation to define and configure bean
    ```java
    import org.springframework.context.annotation.Bean;
    import org.springframework.context.annotation.Configuration;

    @Configuration
    public class AppConfig {
        @Bean
        public MyService myService() {
            return new MyServiceImpl();
        }
    }
    ```
- `@Component` and stereotype annotation;
  - Used to mark a class as a Spring-managed component. Spring scans for these components.
  - `@Component` - Generic Stereotype for any Spring-managed component
  - `@Service` - Specialization for service-layer component
  - `@Repository` - Specialization for DAO (Data Access Object) classes
  - `@Controller` - Specialization for MVC controllers

- Annotation based injection are preformed before external property injection. Thus, external configuration (for example Xml based) effectively overrides the annotations for properties when both approaches are used.

- When using `@Autowired` makes sure that type of bean (class or interface) must match the type expected at the injection point
    ```java
    @Bean 
    public MovieCatalog movieCatalog() {
        return new MovieCataologImpl(); // Return type matches injection point
    }

    // Injection point
    @Autowired
    private MovieCatalog movieCatalog; // match correctly
    ```

- Self Injection 
  - Self-injection in Spring allows a bean to refer it self. This is important when a bean is proxy. Proxy here means than Spring wraps orginal bean so that it can apply transactional logic before and after the method calls.
    ```java
        import org.springframework.beans.factory.annotation.Autowired;
        import org.springframework.stereotype.Service;
        import org.springframework.transaction.annotation.Transactional;

        @Service
        public class MyService {

            @Autowired
            private MyService self; // Self-injection

            // Proxy starts the transaction; calls the real method; commit/rollback based on result
            @Transactional
            public void doSomething() {
                System.out.println("Doing something with transaction support.");
            }

            public void triggerSomething() {
                // Calling via self ensures transactional proxy is used
                self.doSomething();
            }
        }
    ```
    - Instead this if you use `this.doSomething()` then proxy behavior will get skip. But please remember using self injection is not a preferred approach and only a backup option
  
- Non mandatory beans (Optional Dependencies) 
  - `@Autowired(required = false)`: This tells Spring to inject the MovieFinder bean if it exists in the Spring context.
    - If no matching `MovieFinder` bean is available, Spring does not throw an error and simply leaves the `movieFinder` field as `null`.
    ```java
    @Service
    public class MyService {

        private Logger logger;

        @Autowired(required = false)
        public void setLogger(Logger logger) {
            this.logger = logger; // Injected only if Logger is defined
        }

        public void doSomething() {
            if (logger != null) {
                logger.log("Operation performed!");
            } else {
                System.out.println("Logger not available. Proceeding without logging.");
            }
        }
    }
    ```
  - The above is not preffered way. Instead of using optional dependencies, you might use conditional bean creation (e.g., `@ConditionalOnMissingBean` in Spring Boot).
  - Or Use
    ```java
    public class SimpleMovieLister {
        @Autowired
        public void setMovieFinder(Optional<MovieFinder> movieFinder) {
            ...
        }
    }

    // OR 

    public class SimpleMovieLister {
        @Autowired
        public void setMovieFinder(@Nullable MovieFinder movieFinder) {
            ...
        }
    }
    ```

