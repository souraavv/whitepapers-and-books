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
  - [Fine-tuning Annotation-based Autowiring with @Primary or @Fallback](#fine-tuning-annotation-based-autowiring-with-primary-or-fallback)
  - [Fine-tuning Annotation-based Autowiring with Qualifiers](#fine-tuning-annotation-based-autowiring-with-qualifiers)
  - [Using Generics as Autowiring Qualifiers](#using-generics-as-autowiring-qualifiers)
  - [Injection with `@Resource`](#injection-with-resource)
  - [Using @Value](#using-value)
  - [Using @PostConstruct and @PreDestory](#using-postconstruct-and-predestory)
  - [Classpath Scanning and Managed Components](#classpath-scanning-and-managed-components)
  - [Java Based Container Configuration](#java-based-container-configuration)
  - [Instantiating the Spring Container by Using `AnnotationConfigApplicationContext`](#instantiating-the-spring-container-by-using-annotationconfigapplicationcontext)
    - [What is AnnnotationConfigApplicationContext ?](#what-is-annnotationconfigapplicationcontext-)
    - [Using `@Configuration` classes](#using-configuration-classes)
    - [Using `@Component` and JSR-330 classes](#using-component-and-jsr-330-classes)
    - [Building context programmatically](#building-context-programmatically)
  - [Using the @Bean Annotation](#using-the-bean-annotation)
    - [What is a Bean ?](#what-is-a-bean-)
    - [Where Bean is used ?](#where-bean-is-used-)
    - [Return type of a bean method](#return-type-of-a-bean-method)
    - [Dependencies in Bean method](#dependencies-in-bean-method)
    - [LifeCycle Support](#lifecycle-support)
    - [Bean Scope](#bean-scope)
    - [Customizing bean names](#customizing-bean-names)
  - [Using the `@Configuration` annotation](#using-the-configuration-annotation)
    - [What is `@Configuration`](#what-is-configuration)
    - [Injecting Inter-bean depedencies](#injecting-inter-bean-depedencies)
    - [Lookup method injection](#lookup-method-injection)
    - [Behind the scenes](#behind-the-scenes)
  - [Composing Java based Configurations](#composing-java-based-configurations)
    - [Injecting Dependencies across Config Classes](#injecting-dependencies-across-config-classes)
    - [Config Classes Are Beans Too](#config-classes-are-beans-too)
    - [Avoid Circular References](#avoid-circular-references)
    - [Fully-Qualifying Imported Beans](#fully-qualifying-imported-beans)
    - [Looser Coupling with Interfaces](#looser-coupling-with-interfaces)
    - [Influencing Startup Order](#influencing-startup-order)
    - [Background Initialization (Spring 6.2+)](#background-initialization-spring-62)
    - [Conditional Beans (`@Profile`, `@Conditional`)](#conditional-beans-profile-conditional)
  - [Environment Abstraction](#environment-abstraction)
    - [What is this abstraction ?](#what-is-this-abstraction-)
    - [Profiles - what are they and why needed ?](#profiles---what-are-they-and-why-needed-)
    - [Using `@Profile` on methods vs classes](#using-profile-on-methods-vs-classes)
    - [Profile expressions (boolean logic)](#profile-expressions-boolean-logic)
    - [Custom composed profile annotations](#custom-composed-profile-annotations)
    - [PropertySource abstraction — properties everywhere](#propertysource-abstraction--properties-everywhere)
      - [Precedence and search order — who wins when the same key is in multiple places](#precedence-and-search-order--who-wins-when-the-same-key-is-in-multiple-places)
      - [Adding custom PropertySource](#adding-custom-propertysource)
      - [`@PropertySource` — easy way to add a properties file](#propertysource--easy-way-to-add-a-properties-file)
      - [Placeholder resolution in `@PropertySource` locations](#placeholder-resolution-in-propertysource-locations)
    - [Practical guidelines](#practical-guidelines)
  - [Registering a LoadTimeWeaver(बुनकर)](#registering-a-loadtimeweaverबुनकर)
  - [Additional Capabilities of `ApplicationContext`](#additional-capabilities-of-applicationcontext)
    - [Internationalization - MessageSource (i18n)](#internationalization---messagesource-i18n)
    - [Resources and ResourceLoader](#resources-and-resourceloader)
    - [Events - ApplicationEvent, ApplicationListener, `@EventListener`](#events---applicationevent-applicationlistener-eventlistener)
    - [Built-in Lifecycle events](#built-in-lifecycle-events)
    - [Creating custom event](#creating-custom-event)
    - [Publishing Event](#publishing-event)
    - [Listening Styles](#listening-styles)
    - [Conditional listeners (SpEL)](#conditional-listeners-spel)
    - [Returning events from listener methods](#returning-events-from-listener-methods)
    - [Asynchronous listeners](#asynchronous-listeners)
      - [Why async listeners cannot return events that will be auto-published](#why-async-listeners-cannot-return-events-that-will-be-auto-published)
    - [Ordering listeners](#ordering-listeners)
    - [Multicaster customization - asynchronous dispatch and error handling](#multicaster-customization---asynchronous-dispatch-and-error-handling)
    - [Transactional concerns](#transactional-concerns)
    - [Generics and ResolvableType edge cases](#generics-and-resolvabletype-edge-cases)
    - [MDC / ThreadLocal and observability](#mdc--threadlocal-and-observability)
    - [Error handling and retries](#error-handling-and-retries)
    - [Example](#example)
  - [The BeanFactory API](#the-beanfactory-api)
    - [What is the BeanFactory API ?](#what-is-the-beanfactory-api-)
- [Resources](#resources)
  - [Introduction](#introduction)
  - [The Resource Interface](#the-resource-interface)
  - [Built-in Resource Implementation](#built-in-resource-implementation)
    - [UrlResource](#urlresource)
    - [ClassPathResource](#classpathresource)
    - [FileSystemResource](#filesystemresource)
    - [PathResource](#pathresource)
    - [ServletContextResource](#servletcontextresource)
    - [InputStreamResource](#inputstreamresource)
    - [ByteArrayResource](#bytearrayresource)
  - [The `ResourceLoader` interface](#the-resourceloader-interface)
  - [The `ResourcePatternResolver` Interface](#the-resourcepatternresolver-interface)
  - [The `ResourceLoaderAware` Interface](#the-resourceloaderaware-interface)
    - [Examples](#examples)


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
    <summary>Not Desirable Code - Tighly couple with framework</summary>

    ```java

    import org.springframework.context.ApplicationContext;
    import org.springframework.context.ApplicationContextAware;

    public class CommandManager implements ApplicationContextAware {
        private ApplicationContext applicationContext;

        public Object process(Map commandState) {
            Command command = createCommand();
            command.setState(commandState);
            return command.execute();
        }

        protected Command createCommand() {
            // notice the Spring API dependency!
            return this.applicationContext.getBean("command", Command.class);
        }

        public void setApplicationContext(
            ApplicationContext applicationContext) throws BeansException {
            this.applicationContext = applicationContext;
        }
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

### Fine-tuning Annotation-based Autowiring with @Primary or @Fallback
- Because autowiring by type may lead to multiple candidates, it is often necessary to have more control over the selection process.
    <details>
    <summary> Example of multiple candidates </summary>

    ```java

    public interface PaymentService {
        void processPayment();
    }

    @Component
    public class CreditCardPaymentService implements PaymentService {
        @Override
        public void processPayment() {
            System.out.println("Processing payment using Credit Card.");
        }
    }

    @Component
    public class PayPalPaymentService implements PaymentService {
        @Override
        public void processPayment() {
            System.out.println("Processing payment using PayPal.");
        }
    }

    // When you run the application, 
    // Spring will throw an exception because there are two candidates 
    // (CreditCardPaymentService and PayPalPaymentService), and it can’t decide which one to inject.

    @Service
    public class OrderService {

        @Autowired
        private PaymentService paymentService;

        public void placeOrder() {
            paymentService.processPayment();
        }
    }
    ```
    </details>
- One way is to use `@Primary` annotation
- If exactly one primary bean exists among the candidates, it becomes the autowired value.
    ```java
    @Configuration
    public class MovieConfiguration {

        @Bean
        @Primary
        public MovieCatalog firstMovieCatalog() { ... }

        @Bean
        public MovieCatalog secondMovieCatalog() { ... }

        // ...
    }
    ```

- In Spring 6.2, the introduction of the `@Fallback` annotation provides a mechanism to mark beans that should act as fallback options during dependency injection. 
- This feature helps manage the scenario where you have multiple beans of the same type, and you want to specify one (or more) as a fallback in case the primary beans are unavailable or don't meet certain conditions.
    <detials>
    <summary> Fallback in Spring - Example </summary>

    ```java
    
    public interface MessagingService {
        void sendMessage(String message);
    }

    @Component
    public class SmsMessagingService implements MessagingService {
        @Override
        public void sendMessage(String message) {
            System.out.println("Sending SMS: " + message);
        }
    }

    @Component
    public class EmailMessagingService implements MessagingService {
        @Override
        public void sendMessage(String message) {
            System.out.println("Sending Email: " + message);
        }
    }

    @Component
    @Fallback
    public class DefaultMessagingService implements MessagingService {
        @Override
        public void sendMessage(String message) {
            System.out.println("Fallback: Sending Default Message: " + message);
        }
    }


    @Service
    public class NotificationService {

        @Autowired
        private MessagingService messagingService;

        public void notifyUser(String message) {
            messagingService.sendMessage(message);
        }
    }

    ```

  - What Happens When Spring Starts?
    1. If Both `SmsMessagingService` and `EmailMessagingService` Exist:

    Spring will inject one of them based on the available beans.
    `DefaultMessagingService` will not be injected because it is marked with `@Fallback` and is used only when no other bean is available.
    2. If Only `SmsMessagingService` Exists:

    It will be injected as the primary bean (since it's the only regular bean available).
    The `@Fallback` bean (`DefaultMessagingService`) will not be injected, as there’s no need for a fallback.
    If No Regular Bean Exists (e.g., only `DefaultMessagingService`):

    3. The `@Fallback` bean (`DefaultMessagingService`) will be injected because there are no regular beans available.
    </details>


### Fine-tuning Annotation-based Autowiring with Qualifiers
- `@Primary` and `@Fallback` are effective ways to use autowiring by type with several instances
- When you need more control over the selection process, you can use Spring’s `@Qualifier` annotation

    ```java
    public class MovieRecommender {

        @Autowired
        @Qualifier("main")
        private MovieCatalog movieCatalog;
        // ...
    }

    public class MovieRecommender {
        private final MovieCatalog movieCatalog;
        private final CustomerPreferenceDao customerPreferenceDao;
        @Autowired
        public void prepare(@Qualifier("main") MovieCatalog movieCatalog,
                CustomerPreferenceDao customerPreferenceDao) {
            this.movieCatalog = movieCatalog;
            this.customerPreferenceDao = customerPreferenceDao;
        }
        // ...
    }
    ```
- [Q] Is there a way to do this conditionally ? like if I want to inject beans based on the feature toggle ? 
    - Yes, it possible via `@ConditionalOnProperty`
        ```java
        @Configuration
        public class MyFeatureConfiguration {

            @Bean
            @ConditionalOnPropoerty(
                name = "my.feature.enabled",
                havingValue = "true",
                matchIfMissing = false
            )
            public MyFeatureService myFeatureService() {
                return new MyFeatureService();
            }
        }
        ```
- There is also `@Profile` like `@Profile("dev")` or `@Profile("prod")`
- Fallback Style
    ```java
    @Bean
    @ConditionalOnMissingBean(MovieCatalog.class)
    public MovieCatalog fallbackMovieCatalog() {
        return new DefaultMovieCatalog();
    }
    ```

### Using Generics as Autowiring Qualifiers
- In addition to `@Qualifier` annotation, you can use Java generic types as an implicit form of qualification. For example, suppose you have following 
    ```java
    @Configuration
    public class MyConfiguration {
        @Bean
        public StringStore stringStore() {
            return new StringStore();
        }

        @Bean
        public IntegerStore integerStore() {
            return new IntegerStore();
        }
    }

    public interface Store<T> {
        void save(T value);
    }

    public class StringStore implements Store<String> {
        public void save(String value) {}
    }

    public class IntegerStore implements Store<Integer> {
        public void save(Integer value) {}
    }
    ```
- Now we can `@Autowire` the `Store` interface and the generic is used as a qualifier, as the following 
    ```java
    @Autowired
    private Store<String> s1; // <String> qualifier injects stringStore bean

    @Autowired
    private Store<Integer> s2;  // <Integer> qualifier inject integerStore bean

    // Inject all store beans as long as they have an <Integer> generic
    // Store<String> beans will not appear in this list.
    @Autowired
    private List<Store<Integer>> s;

    ```

### Injection with `@Resource`

- Spring also supports injection using the JSR-250 `@Resource` annotation (`jakarta.annotation.Resource`) on fields or bean property setter methods
- This is common pattern in Jakarta EE
- `@Resource` takes a name attribute. By default, Spring interprets the value as the bean name to be injected. 

    ```java
    public class SimpleMovieLister {

        private MovieFinder movieFinder;

        @Resource(name = "myMovieFinder")
        public void setMovieFinder(MovieFinder movieFinder) {
            this.movieFinder = movieFinder;
        }
    }
    ```
- If no name is specified, the deault name is derived from the field name or setter method. In case of a field, it takes the field name.
- In case of setter method it takes the bean property name. 

<details>
<summary> @Resource vs @Autowired </summary>

- ref: https://stackoverflow.com/questions/4093504/resource-vs-autowired
- `@Resource` means get me a known resource by name
- `@Inject` or `@Autowrired` try to wire in a suitable other component by type.
- Spring twist with `@Resource`
  - It first tries by name (strict jsr 250 style)
  - If no bean with that name exists, Spring falls backs to type-based injection like (`@Autowired`)
  - 
</details>

### Using @Value
- `@Value` is typically used to inject externalized properties:
    ```java
    @Component 
    public class MovieRecommender {
        private final String catalog;

        public MovieRecommender(@Value("${catalog.name}" String catalog)) {
            this.catalog = catalog;
        }
    }
    ```
- With the following configuration  
    ```java

    @Configuration
    @PropertySource("classpath:application.properties")
    public class AppConfig { }
    ```

- Default value
    ```java
    @Component 
    public class MovieRecommender {
        private final String catalog;

        public MovieRecommender(@Value("${catalog.name:defaultCataglog}") 
                String catalog) {
            this.catalog = catalog;
        }
    }
    ```
- and `application.properties` file:
    ```yml
    catalog.name=MovieCatalog
    ```

- Two placeholder style `${..}` and `#{..}`
  - `${..}` is the property placeholder syntax. It asks Spring to resolve a property from the Environment or property source (application.properties, system properties, env vars etc)
  - `#{...}` is SpEL (Spring Expression Language) expression. It is evaulated as an expression at runtime and can reference system properties, beans, do arithmetic, create maps/list, call methods, etc. 
    ```java
    @Component
    public class MovieRecommender {

        private final String catalog;

        public MovieRecommender(@Value("#{systemProperties['user.catalog'] + 
                'Catalog'}") String catalog) {
            this.catalog = catalog;
        }
    }
    ```
- The lenient default resolver and what "linient" means ?
  - Spring provides a lenient placeholder revolver by defualt. If Spring cannot find a property for `${catalog.name}`, it will not throw an exception by default. Instead it will inject the unresolved placeholder text itself as the value
- Making placeholder resolution strict:
  - `PropertySourcesPlaceholderConfigure`
  - If you want Spring startup to fail when a `${..}` placeholder is unresolved, declare a `PropertySourcesPlaceholderConfigure` bean
    ```java

    @Configuration
    public class AppConfig {

        @Bean
        public static PropertySourcesPlaceholderConfigure propertyPlaceHolderConfigure() {
            PropertySourcesPlaceholderConfigure cfg =
                    new PropertySourcePlaceHolderConfigure();

            return cfg;
        }
    }
    ```

### Using @PostConstruct and @PreDestory
- Lifecycle annotation `jakarta.annotation.PostConstruct` and `jakarta.annotation.PreDestroy`
- `@PreDestory`
  - Automatically be called just before the bean is destoryed
    ```java
    public class CachingMovieLister {

        @PostConstruct 
        public void populateMovieCache() {

        }

        @PreDestroy
        public void clearMovieCache() {

        }
    }
    ```

### Classpath Scanning and Managed Components

Ronak bhai aap add kr dena 



### Java Based Container Configuration 
- `@Bean` annotation is used to indicate that a method instantiates, configures, and initializes a new object to be managed by Spring IoC container 
- Annotating a class with `@Configuration` indicates that its primary purpose is a source of bean definitions. 
    ```java
    @Configuration
    public class AppConfig {

        @Bean
        public MyServiceImpl myService() {
            return new MyServiceImpl();
        }
    }
    ```

### Instantiating the Spring Container by Using `AnnotationConfigApplicationContext`
- When `@Configuration` classes are provided as input, the `@Configuration` class itself is registered as a bean definition and all declared `@Bean` methods within the class are also registered as bean definitions.

#### What is AnnnotationConfigApplicationContext ?
- It's a Spring container implementation that:
  - Can take `@Configuration` classes with `@Bean` methods
  - Can take `@Component` classes with `@Autowired` and `@Inject` for dependencies
  - Build the entire application context based on annotation 

#### Using `@Configuration` classes 
- If you pass a class annotated with `@Configuration`, Spring will:
  - Register that class as a bean
  - Look inside for all `@Bean` method and register those beans too

    ```java
    public static void main(String[] args) {
        ApplicationContext ctx = new AnnotationConfigApplicationContext(AppConfig.class);
        MyService myService = ctx.getBean(MyService.class);
        myService.doStuff();
    }
    ```
- Here 
  - `AppConfig` is a `@Configuration` class
  - Beans defined inside `AppConfig` are available in the container

#### Using `@Component` and JSR-330 classes
- Instead of `@Configuration`, you can directly give Spring your classes that are annotated with `@Component` (or `@Service`, `@Repository`, etc).
- Spring will handle dependencies with `@Autowired`/`@Inject`

    ```java
    ApplicationContext ctx = new AnnotationConfigApplicationContext(
        MyServiceImpl.class, Depedency1.class, Dependency2.class
    );

    MyService myService = ctx.getBean(MyService.class);
    myService.doStuff();
    ```

#### Building context programmatically
- You can start with empty container and register things step by steps
    ```java
    AnnotationConfigApplicationContext ctx = 
            new AnnotationConfigApplicationContext();
    ctx.register(AppConfig.class, OtherConfig.class);
    ctx.refresh(); // must step
    MyService myService = ctx.getBean(MyService.class);
    ```

### Using the @Bean Annotation

#### What is a Bean ? 
- `@Bean` is used on a method to tell Spring: The object returned by this method should be managed as a bean in the Spring Container 
- `@Bean` method name is the bean id

#### Where Bean is used ?
- Inside `@Component` class, inside a `@Configuration` class, Even in an interface with default methods

    ```java
    public interface BaseConfig {
        @Bean
        default TransferServiceImpl transferService() {
            return new TransferServiceImpl();
        }
    }

    @Configuration 
    public class AppConfig implements BaseConfig {

    }
    ```

#### Return type of a bean method 
- It can be concrete class
- It can be interface type

#### Dependencies in Bean method 
- This is constructor injection, but done through method parameter

    ```java
    @Bean
    public TransferService transferService(AccountRepository accountRepository) {
        return new TransferServiceImpl(accountRepository);
    }

    ```

#### LifeCycle Support
- Beans create via `@Bean`:
  - Can use `@PostConstruct` and `@PreDestroy`
  - Can implement Spring lifecycle interface (`InitializingBean`, `DisposableBean`, etc)
  - Can specify init and destory method directly:
    ```java
    @Bean(initMethod = "init", destoryMethod = "clenaup")
    public BeanOne beanOne() {
        return new BeanOne();
    }
    ```
- To disable auto-destroy. Else if bean has `close()` or `shutdown()` method, Spring will call them by default on shutdown
    ```java
    @Bean(destoryMethod = "")
    public DataSource dataSource() {...}
    ```

#### Bean Scope
- By default singleton (one instance)
- You can change scope with `@Scope`

    ```java
    @Bean
    @Scope("prototype")
    public Encryptor encryptor() {
        return new Encryptor();
    }
    ```
- Common scope - `singleton`, `prototype`, `request`, `session`
- The problem
  - Let’s say you have:
    - A singleton bean `UserService` - created only once.
    - A session-scoped bean `UserPreferences` - new for each logged-in user session.
    - Now, your singleton `UserService` needs to use `UserPreferences`
    - The Solution to this is Scoped Proxy
      - Spring solve this using proxies:
        - Instead of injecting the actual `UserPreference` object
        - It injects a proxy object (wrapper)
        - When the proxy is called, it automatically looks up the real session-scoped bean for the current user sessions
        - So spring handles the lifecycle
        - When `userService` calls `userPreferences.getTheme()`, the proxy looks up the correct `UserPreferences` object for the current session.
    ```java
    @Bean
    @SessionScope
    public UserPreferences userPreferences() {
        return new UserPreferences();
    }

    @Bean
    public UserService userService() {
        UserService service = new SimpleUserService();
        // proxy - this will inject a proxy, not a real instance
        service.setUserPreferences(userPreferences());
        // proxy
        return service;
    }
    ```
#### Customizing bean names
```java
@Bean("mythign")
public Thing thing() {
    return new Thing();
}
    ```

#### Bean aliases
```java
@Bean({"dataSource", "othername", "anotehrname"})
public DataSource dataSource() {
    return new DataSource();
}
```

### Using the `@Configuration` annotation

#### What is `@Configuration`
- It is a class level annotation
- Tells spring - "this class contains beans defintions"
- inside it we write `@Bean` methods that create and configure beans

    ```java
    @Configuration 
    public class AppConfig {
        @Bean
        public BeanOne beanOne() {
            return new BeanOne();
        }
    }
    ```
#### Injecting Inter-bean depedencies
- If one bean needs another, you can just call another `@Bean` method 

    ```java
    @Configuration
    public class AppConfig {
        @Bean
        public BeanOne beanOne() {
            return new BeanOne(beanTwo());
        }

        @Bean
        public BeanTwo beanTwo() {
            return new BeanTwo();
        }
    }
    ```
- the above only works in `@Configuration` classes and `@Compnent` classes

#### Lookup method injection 
- Spring beans are singleton by default
- when spring injects dependencies into a singleton Bean, it injects them once (at startup)
- If that dependency is a prototype bean (suppose to be new every time you ask), the singelton will still hold on to just one instance - the one created at startup
- Soution - Lookup method injection
  - Using proxy 
#### Behind the scenes

```java
@Configuration
public class AppConfig {
    @Bean
    public ClientService clientService1() {
        return new ClientServiceImpl(clientDao());
    }

    @Bean
    public ClientService clientService2() {
        return new ClientServiceImpl(clientDao());
    }

    @Bean
    public ClientDao clientDao() {
        return new ClientDaoImpl();
    }
}
```

- Here:
  - `clientDao()` is called twice.
  - Normally, that would create two `ClientDaoImpl` objects.
  - But Spring guarantees singleton by default → only one instance will exist.
- How ?
  - Spring uses CGLIB (bytecode subclassing) to enhance the `@Configuration` class at runtime 
  - It replaces your clientDao() call with logic like:
    - Check if clientDao is already created in the container.
    - If yes, return the cached one.
    - If no, create it, cache it, and return it.

### Composing Java based Configurations
- Similar to xml `<import>` here also we have `@Import` to pull in other config
    ```java
    @Configuration
    public class ConfigA {
        @Bean
        public A a() {
            return new A();
        }
    }

    @Configuration 
    @Import(ConfigA.class) // include ConfigA into this config
    public class ConfigB {
        @Bean
        public B b() {
            return new B();
        }
    }
    ```
- Now if you start you app with `ConfigB`, then spring will automatically load `ConfigA`
    ```java
    public static void main(String[] args) {
        ApplicationContext ctx = new AnnotationConfigApplicationContext(
            ConfigB.class
        );

        A a = ctx.getBean(A.class);
        B b = ctx.getBean(B.class);
    }
    ```
- Before only `@configuration` class were allowed to import, but now `@Component` classes are also allowed

#### Injecting Dependencies across Config Classes
- Problem: Beans often depend on each other across configurations.
- Example:
    ```java
    @Configuration
    public class ServiceConfig {
        @Bean
        public TransferService transferService(AccountRepository 
                accountRepository) {
            return new TransferService(accountRespository);
        }
    }

    @Configuration
    public class RepositoryConfig {
        @Bean
        public AccountRepository accountRepository(DataSource dataSource) {
            return new JdbcAccountRespository(dataSource);
        }
    }

    @Configuration
    @Import({ServiceConfig.class, RepositoryConfig.class})
    public class SystemTestConfig {
        @Bean
        public DataSource dataSource() {
            return new DataSource();
        }
    }
    ```

    ```java
    ApplicationContext ctx = new AnnotationConfigApplicationContext(
            SystemTestConfig.class);
    TransferService ts = ctx.getBean(TransferService.class);
    ```

#### Config Classes Are Beans Too
- `@Configuration` classes themselves are beans.
- That means you can use `@Autowired` or `@Value` inside them.
    ```java
    @Configuration
    public class ServiceConfig {
        @Autowired
        private AccountRepository accountRepository;

        @Bean
        public TransferService transferService() {
            return new TransferServiceImpl(accountRepository);
        }
    }
    ```

#### Avoid Circular References
- Don’t call your own `@Bean` methods in `@PostConstruct`.
- Why? Because at that point, the config class itself isn’t fully ready → circular creation issues.

#### Fully-Qualifying Imported Beans
- Problem: In `ServiceConfig`, you see an `@Autowired AccountRepository`, but where is it defined?
- It could be in many configs. Slightly ambiguous.
- Solution
    ```java
    @Configuration
    public class ServiceConfig {
        @Autowired
        private RepositoryConfig respositoryConfig;

        @Bean
        public TransferService transferService() {
            return new TransferService(respositoryConfig.accountRespository());
        }
    }
    ```
- Now it’s crystal clear that `accountRepository()` comes from `RepositoryConfig`.
- Tradeoff ? Yes, Tighter coupling between config classes. Solution ? think before going to next section

#### Looser Coupling with Interfaces 
- To reduce tight coupling, define config as inteface
    ```java
    @Configuration
    public interface RepositoryConfig {
        @Bean
        AccountRepository accountRepository();
    }

    @Configuration
    public class DefaultRespositoryConfig implements RespositoryConfig {
        @Bean
        public AccountRespository accountRespository() {
            return new JdbcAccountRespository(...);
        }
    }
    ```
- Now `ServiceConfig` can depend on `RepositoryConfig` interface, not concrete class. Cleaner and flexible.

#### Influencing Startup Order
- Use `@Lazy`, bean created only when first needed.
- Use `@DependsOn`, bean X must be initialized before bean Y.

#### Background Initialization (Spring 6.2+)
- `@Bean(bootstrap=BACKGROUND)` -> bean created in background thread.
- Dependencies wait if they need it early.
- Needs a bean of type `Executor` (bootstrapExecutor) to run.
- Great for heavy beans at startup (speed up app startup)

#### Conditional Beans (`@Profile`, `@Conditional`)
- `@Profile("dev")`:  bean only created in dev environment.


### Environment Abstraction

#### What is this abstraction ?
- `Environment` is an abstraction inside spring container that models two things:
  - profiles: which set of beans should be active
  - properties: key-value settings coming from many places.
- `Environment` is like container's runtime context manager that answers questions like
  - which profile is active now ?
  - where do i read property `x` and what value should I get ?

#### Profiles - what are they and why needed ?
- A profile is a named logical group of bean definitions, used to register different bean in different runtime env
- Use case:
  - Development: use in-memory DB for fast local and dev test
  - QA/Production: Use externally provided data source
  - Feature toggle per customer: customer-A beans and customer-B beans
- Example:
    ```java
    @Bean
    public DataSource dataSource() {
        return new EmbeddedDataSourceBuilder()
                .setType("my-schema.sql")
                .addScript("my-test-data.sql")
                .build();
    }

    @Bean(destoryMethod = "")
    public DataSource dataSource() throws Exception {
        Context ctx = new InitialContext();
        return (DataSource) ctx.lookup("java:com/env/jdbc/datasource");
    }

    ```
- Now how to switch between two based on the env ? Answer: profile
    ```java
    @Configuration
    @Profile("development")
    public class StandAloneDataConfig {
        @Bean
        public DataSource dataSource() {
            return new EmbeddedDataSourceBuilder()
                    .setType("my-schema.sql")
                    .addScript("my-test-data.sql")
                    .build();
        }
    }

    @Configuration
    @Profile("production")
    public class JndiDataConfig {
        @Bean(destoryMethod = "")
        public DataSource dataSource() throws Exception {
            Context ctx = new InitialContext();
            return (DataSource) ctx.lookup("java:com/env/jdbc/datasource");
        }
    }
    ```

#### Using `@Profile` on methods vs classes
- `@Profile` on a class: everything in the class (`@Bean` methods and `@Imports`) is skipped unless the profile is active.
- `@Profile` on a method: only that bean is registered if the profile is active — useful for different variants of a single logical bean (like two dataSource beans).
- Example: same bean name, two method variants
    ```java
    @Configuration
    public class AppConfig {
        @Bean("dataSource")
        @Profile("development")
        public DataSource standaloneDataSource() { ... }

        @Bean("dataSource")
        @Profile("production")
        public DataSource jndiDataSource() throws Exception { ... }
    }
    ```

#### Profile expressions (boolean logic)
- `@Profile` supports small expressions with operators:
  - `!`, `&` and `|`
  - Examples
    - `@Profile("production & us-east")` = active when both 'production' and 'us-east' are active.
    - `@Profile("!test")`

#### Custom composed profile annotations
- You can create your own annotation as a meta-annotation that wraps `@Profile`
    ```java
    @Target(ElementType.TYPE)
    @Retention(RetentionPolicy.RUNTIME)
    @Profile("production")
    public @interface Production {}
    ```
- Then use `@Prodcution` instead of `@Profile("production")`

#### PropertySource abstraction — properties everywhere
- `Environment` also manages property sources, i.e., key-value collections from various places:
  - JVM system properties (`-D...`)
  - OS env variables
  - JNDI entries
  - properties via `@PropertySource`

##### Precedence and search order — who wins when the same key is in multiple places
- Property search is hierarchical; earlier sources override later ones. Values are replaced (not merged)

##### Adding custom PropertySource

```java
ConfigurableApplicationContext ctx = new GenericApplicationContext();
MutablePropertySources sources = ctx.getEnvironment().getPropertySources();
sources.addFirst(new PropertySource());
```

##### `@PropertySource` — easy way to add a properties file
- Put `@PropertySource("classpath:/com/myco/app.properties")` on a `@Configuration` class to add that file as a `PropertySource`
    ```java
    @Configuration
    @PropertySource("classpath:/com/myco/app.properties")
    public class AppConfig {
        @Autowired Environment env;

        @Bean
        public TestBean testBean() {
            TestBean t = new TestBean();
            t.setName(env.getProperty("testbean.name"))
            return t;
        }

    }
    ```

##### Placeholder resolution in `@PropertySource` locations
- You can write `@PropertySource("classpath:/com/${my.placeholder:default/path}/app.properties")`
- The `${...}` values are resolved against already-registered property sources (e.g., system properties, environment variables).
- If a placeholder is not found and has no default, an `IllegalArgumentException` is thrown.

#### Practical guidelines 
- Avoid heavy `@Autowired` in `@Configuration` fields — configuration classes are created early.
- Beware of circular initialization:
  - Don’t access local `@Bean` methods from a `@PostConstruct` on the same config (leads to circular reference).
- When defining alternative beans with `@Profile`, use distinct method names and bean name attribute if you want multiple variants of the same logical bean.
- Activate profiles explicitly in production environments (e.g., JVM arg, environment variable). Don’t rely on defaults unless intended.

### Registering a LoadTimeWeaver(बुनकर)

### Additional Capabilities of `ApplicationContext`
- `ApplicationContext` = `BeanFactory` + framework features that matters to real applications 
- Key additions
  - Internationalization (i18n) via `MessageSource`
  - Resource access via `ResourceLoader`
  - Eventing via `ApplicationEventPublisher`/`ApplicationListener`
  - Parent/child context for layering
  - Startup instrumentation via `ApplicationStartup`

#### Internationalization - MessageSource (i18n)
- `ApplicationContext` implements `MessageSource`, so you can call `getMessage(...)` on context directly
    ```java
    @Bean
    public MessageSource messageSource() {
        ResourceBundleMessageSource ms 
                = new ResourceBundleMessageSource();
        ms.setBasenames("message", "errors");
        ms.setDefaultEncoding("UTF-8");
        return ms;
    }
    ```
#### Resources and ResourceLoader
- `ApplicationContext` extends `ResourceLoader`; calls `getResource(String location)` to get a `Resource`
- Location prefix:
  - `classpath:`, `file:`, `http:`
  
    ```java
    Resource res = context.getResource("classpath:sql/schema.sql");
    try (InputStream in = res.getInputStream()) {
        // read script
    }
    ```

#### Events - ApplicationEvent, ApplicationListener, `@EventListener`
- Spring events are in-process pub/sub mechanism for decoupling components inside the same `ApplicationContext`
- User events when you want to notify zero-or-more observers of something that happened without tight coupling between publisher and the consumer 
- Typical use cases
  - Domain events (entity created/updated)
  - Cache invalidation 
  - Audit/logging
  - startup/shutdown hooks
  - translating internal events to external system (Kafka) asynchronously

#### Built-in Lifecycle events
- `ContextRefreshedEvent`
  - Published when the ApplicationContext is initialized or refreshed
  - Means: bean definitions loaded, singletons pre-instantiated, post-processors active. Useful for cache warm-up and post-initialization work.
- `ContextStartedEvent`
  - Published when `ConfigurableApplicationContext.start()` is invoked. Triggers `Lifecycle` beans to start.
- `ContextStoppedEvent`
  - Published when `ConfigurableApplicationContext.stop()` is invoked. Triggers `Lifecycle` beans to stop.
- `ContextClosedEvent`
  - Published when `close()` is invoked or on JVM shutdown hook. Means singletons are being destroyed.
- `RequestHandledEvent`
  - Indicate completed HTTP request handling
  - Useful for request-level logging/metrics.

#### Creating custom event

- Classical
    ```java
    public class BlockedListEvent implements ApplicationEvent {
        @Getter
        private final String address;
        @Getter
        private final String content; 

        public BlockedListEvent(Object source, String address,
                String content) {
            super(source);
            this.address = address;
            this.content = content;
        }
    }
    ```
- Or just a POJO: Spring will wrap plain objects into an event envelope internally when published.
    ```java
    @Getter
    @NoArgsConstructor
    @AllArgsConstructor
    public class UserCreated {
        private final Long id;
    }
    ```

#### Publishing Event 
- Two common ways - 
    ```java
    @Component
    public class EmailService {
        private final ApplicationEventPublisher publisher;

        public EmailService(ApplicationEventPublisher publisher) {
            this.publisher = publisher;
        }

        public void sendEmail(String address, String content) {
            if (blocked(address)) {
                publisher.pubishEvent(
                    new BlockListEvent(this, address, content)
                );
                return;
            }
        }
    }
    ```
- Note that:
  - Events are published inside a running transaction will be handled synchronously by default, and listeners invoked in publisher's thread - so they share thread-local and transaction context 
  - If you want to publish an event post commit in a transaction then use `@TransactionalEventListener`

#### Listening Styles
- Classical
    ```java
    public class BlockedListNotifier 
            implements ApplicationListener<BlockedListEvent> {
        @Override 
        public void onApplicationEvent(BlockedListEvent e) {
            // handles synchronously
        }
    }
    ```

- Modern 
    ```java
    @Component 
    public class BlockedListNotifier {

        @EventListener
        public void onBlock(BlockedListEvent e) { ... }

        @EventListener(condition = "#event.severity == 'HIGH'")
        public void onHighBlock(BlockedListEvent e)  { ... }

        @EventListener({ContextRefreshedEvent.class,
                ContextStartedEvent.class})
        public void onContextStart() { ... }
    }
    ```
    - Advantages:
      - Use SpEL
      - Multiple handler in one bean 

#### Conditional listeners (SpEL)
- `condition` is evaluated in a SpEL context with values you can reference:
  - `#root.event` or `event` - the event object
  - `#root.args` or `args` - method arguments array
  - argument names (if compiled with -parameters) or `#p0`, `#a0` indexes
    ```java
    @EventListener(condition = "#event.level == 'CRITICAL' and 
            #p0.source == 'internal'")
    public void handleCritical(BlockedListEvent event) { ... }
    ```

#### Returning events from listener methods
- Synchronous `@EventListener` methods may return an event (or Collection/array) and Spring will publish it automatically:
    ```java
    @EventListener
    public ListUpdateEvent onBlocked(BlockedListEvent e) {
        return new ListUpdateEvent(this, ....);
    }
    ```
- This enables simple event-chaining without explicit publisher wiring.
- Not supported for async listeners.

#### Asynchronous listeners
- Two ways:
  - Annotate listener with `@Async` and enable `@EnableAsync`.
    ```java
    @EventListener
    @Asycn 
    public void sendNotification(EmailEvent e) { ... }
    ```
- As guessed by you - Async listeners execute in executor threads - they do not share the publisher thread's transaction or `ThreadLocal` context.
- Exceptions thrown in async listeners do not propagate to the publisher
- Async listeners cannot return events that will be auto-published.
- When to use ?
  - Long-running or blockig tasks
  - Offloading non-critical workflow

##### Why async listeners cannot return events that will be auto-published
- Short answer: return-based event chaining is inherently synchronous
- Spring only auto-publishes a listener method’s return value when that method has actually completed on the calling thread
- When you mark a listener @Async, the method is executed in a separate thread and the caller doesn't wait for the result


#### Ordering listeners
- User `@Order` on listener methods or implements `Ordered`
    ```java
    @EventListener
    @Order(10)
    public void first(BlockedListEvent e) {...}

    ```
- Lower value = higher precedence 
- Use ordering sparingly; prefer designing independent listeners when possible. Ordering is helpful when one listener sets up context for another.

#### Multicaster customization - asynchronous dispatch and error handling
- Spring uses an `ApplicationEventMulticaster` to distribute events.
- By default it is a `SimpleApplicationEventMulticaster` with synchronous dispatch
- Replace or configure it for async behavior or custom error handling:

    ```java
    @Bean
    ApplicationEventMulticaster applicationEventMulticaster(
        TaskExecutor taskExecutor, ErrorHandler errorHandler) {
        SimpleApplicationEventMulticaster multicaster = 
                new SimpleApplicationEventMulticaster();
        // enables async dispatch
        multicaster.setTaskExecutor(taskExecutor);
        // central error handling
        multicaster.setErrorHandler(errorHandler);
        return multicaster;
    }
    ```
- `taskExecutor` not only affects `@Async` usage for listeners if the multicaster uses it for dispatch, but it also controls dispatch behavior when using the multicaster directly
- `ErrorHandler` lets you centralize how exceptions from listeners are handled in **async dispatch**.

#### Transactional concerns
- Synchronous listeners share transaction context with the publisher if published inside a transaction
- For listeners that must run after a commit, use `@TransactionalEventListener`
    ```java
    @TransactionalEventListener(phase = TransactionPhase.AFTER_COMMIT)
    public void afterCommitHanlder(DomainEvent e) { ... }
    ```
#### Generics and ResolvableType edge cases
- Generic event dispatch works when the framework can resolve the concrete generic type at runtime.
- Due to type erasure, this works only if the event that is fired resolves the generic parameters on which the event listener filters
- If you publish a generic `EntityCreatedEvent<T>` and want listeners to receive only for `T=Person`, ensure your concrete event class retains the generic resolution:
  - Option 1: create concrete subclass `PersonCreatedEvent extends EntityCreatedEvent<Person>`
  - Option 2: implement `ResolvableTypeProvider` on the event to expose the **runtime generic type**: to guide the framework beyond what the runtime environment provides
    ```java
    public class EntityCreatedEvent<T> extends ApplicationEvent
            implements ResolvableTypeProvider {
        
        private final T entity;
        public EntityCreatedEvent(T entity) {

        }

        @Override
        public ResolvableType getResolvableType() {
            return ResolvableType.forClassWithGenerics(
                getClass(),
                ResolvableType.forInstance(getSource())
            );
        }
    }
    ```
- The above works for any events not only `ApplicationEvent`

#### MDC / ThreadLocal and observability
- MDC in the context of Spring refers to Mapped Diagnostic Context. It is a powerful feature provided by logging frameworks like Logback and Log4j, which allows you to enrich log messages with contextual information specific to the current thread's execution.
- Async listeners are executed on separate threads - MDC and ThreadLocal values are not propagated automatically.
- Strategies for MDC propagation:
  - Capture MDC from publisher and restore in listener wrapper.
  - Use executors that propagate context (e.g. `DelegatingSecurityContextExecutor` or custom wrappers).
- Strategy 1
  - Spring Boot's `ThreadPoolTaskExecutor` supports a `TaskDecorator` that wraps each `Runnable` before submission.
    ```java
    @Bean
    public TaskDecorator mdcTaskDecorator() {
        return runnable -> {
            Map<String, String> contextMap = MDC.getCopyOfContextMap();

            return () -> {
                Map<String, String> previous = MDC.getCopyOfContextMap();
                try {
                    if (contextMap != null) {
                        MDC.setContextMap(contextMap);
                    }
                    runnable.run();
                } finally {
                    if (previous != null) {
                        MDC.setContextMap(previous);
                    } else {
                        MDC.clear();
                    }
                }
            }
        }
    }
    ```
    ```java
    @Bean("asyncExecutor")
    public ThreadPoolTaskExecutor asyncExecutor(TaskDecorator taskDecorator) {
        ThreadPoolTaskExecutor exec = new ThreadPoolTaskExecutor();
        exec.setCorePoolSize(10);
        exec.setMaxPoolSize(50);
        // inject decorator
        exec.setTaskDecorator(taskDecorator);
        exec.initialize();
        return exec;
    }
    ```
- Strategy 2 - Pass MDC data as part of the event payload
    ```java
    public class BlockedListEvent {
        private final Map<String,String> mdc;
    }

    publisher.publishEvent(new BlockedListEvent(this, 
            addr, MDC.getCopyOfContextMap()));
    
    ```
- Strategy 3: Use tracing libraries that propagate context automatically
  - Spring Cloud Sleuth
  - **OpenTelemetry** - automatically propagates trace ids/span context into MDC
  - 
#### Error handling and retries
- Synchronous listeners: exceptions propagate to publisher - design accordingly.
- Async listeners: exceptions are handled by the executor. 
  - Use `ErrorHandler` on multicaster or catch/handle in listener.
- For retries: events are in-memory and non-durable - if you need retries, translate event handling to resilient messaging (e.g. publish to JMS/Kafka and rely on broker-level retries or consumer-side retry with dead-lettering).

#### Example
- A sample
    ```java
    @Service
    public class UserService {

        private final ApplicationEventPublisher publisher;
        public UserService(ApplicationEventPublishser publisher) {
            this.publisher = publisher;
        }

        @Transactional
        public void createUser(UserDto dto) {
            User u = userRepo.save(dto.toEntity());
            publisher.publishEvent(new UserCreatedEvent(
                this, u.getId()
            ));
        }
    }
    ```
- Listener that indexes
    ```java
    @Component
    public class UserIndexingListener {

        @TransactionalEventListener(phase = TransactionalPhase.AFTER_COMMIT);
        public void onUserCreated(UserCreatedEvent e) {
            indexService.index(e.getUserId());
        }
    }
    ```
- Async notifier listener
    ```java
    @Component
    public class NotificationListener {

        @EventListener
        @Async
        public void sendWelcomeEmail(UserCreatedEvent e) {
            emailService.sendWelcome(e.getUserId());
        }
    }
    ```

### The BeanFactory API 

#### What is the BeanFactory API ?
- Core DI Engine, while `ApplicationContext` is the feature-rich enterprice container build on top of it.
- It defines the fundamental contract for dependency injection
  - You ask a bean by name or type
  - The factory instantiates the bean, wire dependencies, and return it
- `DefaultListableBeanFactory` is the standard implementation of `BeanFactory`
- We will not be using this directly and most we will use `ApplicationContext`, else if you are just using `BeanFactory`, then you must have to register multiple things (`BeanPostProcessor`, `BeanFactoryPostProcessor` etc)

## Resources
- This chapter cover how Spring handles resources and how you acn work with resources in Spring 

### Introduction
- Java's standard `java.net.URL` class and standard handler for various URL prefixes

### The Resource Interface
- Spring's `Resource` interface located in the `org.springframework.core.io` package is meant to be more capable interface for abstracting access to low-level resources.
- The following listing provides an overview of the `Resource` interface.
    ```java
    public interface Resource extends InputStreamSource {
        boolean exists();
        boolean isReadable();
        boolean isOpen();
        boolean isFile();

        URL getURL() throws IOException;
        URI getURI() throws IOException;
        // Only works when file resides on the filesystem
        // doesn't work if resource is inside the JAR
        File getFile() throws IOException;

        ReadableByteChannel readableChannel() throws IOException;

        long contentLength() throws IOException;
        long lastModified() throws IOException;

        Resource createRelative(String relativePath) throws IOException;

        String getFilename();
        String getDescription();
    }
    ```

    ```java
    public interface InputStreamSource {
        InputStream getInputStream() throws IOException;
    }
    ```

- Some important method of `Resource` interface are:
  - `getInputStream()`: Locate and opens the resource, returning an `InputStream` for reading from the resource.
    - Every invocation return fresh `InputStream` and it's user responsibility to close the stream
  - `exists()`: Returns a `boolean` indicating whether this resource actually exists
  - `isOpen()`: Return a `boolean` indicating whether this resource represents a handle with open stream. If `true`, the `InputStream` cannot be read multiple times and must be read once only and then closed to avoid resource leaks. Return `false` for all usual resource implementation, with the exception of `InputStreamResource`
  - `getDescription()`: Returns a description for this resource, to be used for error output when working with the resource. This is often the fully qualified file name or the actual URL of the resource

    >[!NOTE]
    > The `Resource` abstraction doesn't replace functionality. It wraps it where possible. For example, a `UrlResource` wrpas a URL and uses the wrapped `URL` to do its work

### Built-in Resource Implementation
- Spring includes several bulit-in `Resource` implementations:
  - `UrlResource`
  - `ClassPathResource`
  - `FileSystemResource`
  - `PathResource`
  - `ServletContextResource`
  - `InputStreamResource`
  - `ByteArrayResource`

#### UrlResource
- `UrlResource` wraps a `java.net.URL` and can be used to access any object that is normally accessible with a URL, such as file, an HTTP targer, and FTP target and others
- All URLs have standarized `String` representation, such that appropriate standardized prefixes are used to indicate one URL type from another. This includes `file:`, `https:`, `ftp:` and others
- A `UrlResource` is created by Java code by explicity using the `UrlResource` constructor but is often created implicitly when you call an API method that takes a `String` argument meant to represent a path.
    ```java
    Resource res = new UrlResource("https://example.com/data.txt");
    ```
#### ClassPathResource
- This class represents a resource that should be obtained from the classpath. 
- It uses either the thread context class loader, a given class loader, or a given class for loading resources
- This `Resource` implementation supports resolution as a `java.io.File` if the class path resource resides in the file system but not for classpath resources that reside in a jar and have not been expanded to the filesystem. 
    ```java
    Resource res = new ClassPathResource("com/example/config.properties");
    ```

#### FileSystemResource
- This is a `Resource` implementation for `java.io.File` handles.
- Also supports `java.nio.file.Path` handles, applying Spring standard String-based path transformation but performing all operation via the `java.nio.file.Files` API.
- For pure `java.nio.path.Path` based support use a `PathResource` instead `FileSystemResource` 
    ```java
    Resource res = new FileSystemResource("/data/app/config.yml");
    ```
#### PathResource
- This is `Resource` implementation for `java.nio.file.Path` handles, performing all operations and transformatives via the `Path` API.
- It support resolution as `File` and as a `URL` and also implements the extended `WritableResource` interface
- `PathResource` is effectively a pure `java.nio.path.Path` based alternative to `FileSystemResource`
    ```java
    Path path = Paths.get("/data/app/config.yml");
    Resource res = new PathResource(path);
    ```

#### ServletContextResource
- Resources relative to a web application root.
- Interprets paths within the relevant web application's root directory

    ```java
    Resource res = new ServeletContextResource(
            servletContext, "/WEB-INF/views/home/jsp");
    ```

#### InputStreamResource
- An `InputStreamResource` is a `Resource` implementation for a given `InputStream`
- It should be used only if no specific `Resource` implementation is applicable
- Used when no specific `Resource` implementation is applicable. 
- In particular, prefere `ByteArrayResource` or any of the file-based `Resource` implementations where possible

    ```java
    InputStream is = new FileInputStream("data.txt");
    Resource res = new InputStreamResource(is);
    ```
- In contrast to other `Resource` implementations, this is a descriptor for an already-opened resource. Therefore, it returns `true` from `isOpen()`

#### ByteArrayResource

- Wraps a `byte[]` as a resource
- Create a fresh `ByteArrayInputStream` each time.
    ```java
    byte[] data = "hello World".getBytes(StandardCharsets.UTF_8);
    Resource res = new ByteArrayResource(data);
    ```

### The `ResourceLoader` interface
- The interface is meant to be implemented by objects that can return `Resource` instances
    ```java
    public interface ResourceLoader {
        Resource getResource(String location);
        ClassLoader getClassLoader();
    }
    ```
- All application contexts implements the `ResourceLoader` interace. Therefore, all application contexts may be used to obtain `Resource` instances
- When you call `getResource()` on a specific application context, and the location path specified doesn't have specific prefix, you get back a `Resource` type that is appropriate to that particular application context
- For example, assume the following snippet run agains `ClassPathXmlApplicationContext`
    ```java
    Resource template = ctx.getResource("some/resource/path/myTemplte.txt");
    ```
- The above return `ClassPathResource` 
- If the same method is run agains a `FileSystemXmlApplicatoinContext` instance, it would return a `FileSystemResource`
- For a `WebApplicationContext`, it would return a `ServletContextResource`
- On the other hand you can also force 
    ```java
    Resource template = ctx.getResource("classpath:some/resource/path/a.txt");
    Resource template = ctx.getResource("file:///some/resource/path/a.txt");
    Resource template = ctx.getResource("https://myhost.com/path/a.txt);
    ```

### The `ResourcePatternResolver` Interface
- Extension to the `ResourceLoader`
    ```java
    public interface ResourcePatternResolver extends ResourceLoader {
        String CLASSPATH_ALL_URL_PREFIX = "classpath*:";
        Resource[] getResources(String locationPattern) 
                throws IOException;
    }
    ```
- `*` matches zero or more character
- `**` matches zero or more directories in a path
- `?` matches exactly one character

    ```java
    ApplicationContext ctx = new ClassPathXmlApplicationContext("conf/app.xml");
    Resource[] resources = ctx.getResource("classpath*:com/example/**/*.html");

    for (Resource r: resources) {
        ...
    }
    ```

    ```java
    ResourcePatternResolver resolver = new PathMatchingResourcePatternResolver();
    Resource[] res = resolver.getResource("classpath*:META-INF/*-spring.xml");
    ```

    ```java
    ResourcePatternResolver resoler = new PathMatchingResourcePatternResolver();
    Resource[] res = resolver.getResource("file:./config/**/*.yml");
    ```

- Example: Injecting multiple resource with `@Value`
    ```yml
    templates.path=classpath*:com/myapp/**/templates/*.html
    ```

    ```java
    @Component
    public class MyBean {
        private final Resource[] templates;

        public MyBean(@Value("${templates.path}") Resource[] templates) {
            this.templates = templates
        }
    }
    ```

### The `ResourceLoaderAware` Interface
- A special callback interface which identifies components that expect to be provided a `ResourceLoader` reference
    ```java
    public interface ResourceLoaderAware {
        void setResourceLoader(ResourceLoader resourceLoader);
    }
    ```

- When a class implements `ResourceLoaderAware` and is deployed into an application context (a spring-managed bean), it is recognized as `ResourceLoaderAware` by the application context
- The application context then invoke `setResourceLoader(ResourceLoader)`, supplying itself as argument (remember all application context in Spring implements the `ResourceLoader` interface)
- Even better than above is to use constructor injection with `@Autowired` instead of callback interface

#### Examples
- Implementing `ResourceLoaderAware` (callback style)
    ```java
    @Component
    public class MyBean implements ResourceLoaderAware {
        private ResourceLoader resourceLoader;

        @Override
        public void setResourceLoader(ResourceLoader resourceLoader) {
            this.resourceLoader = resourceLoader;
        }

        public void load() throws IOException {
            Resource res = resourceLoader.getResource("callpath:config/my.yml");
        }
    }
    ```
- Constructor Injection 
    ```java
    @Component
    public class MyBean {
        private final ResourceLoader resourceLoader;

        public MyBean(ResourceLoader resourceLoader) {
            this.resourceLoader = resourceLoader;
        }

        public void load() throws IOException {
            Resource r = resourceLoader.getResource("file:/etc/app/conf.yml");
        }
    }
    ```
- Autowiring the `ResourcePatternResolver` (for wildcards)
    ```java
    @Component
    public class TemplateLoader {
        private final ResourcePatternResolver resolver;

        public TemplateLoader(ResourcePatternResolver resolver) {
            this.resolver = resolver;
        }

        public Resource[] findAllTemplates() throws IOException {
            return resolver.getResource("classpath*:com/example/**/templates/*.html");
        }
    }
    ```