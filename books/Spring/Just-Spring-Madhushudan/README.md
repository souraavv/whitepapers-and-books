- [Chapter 1. Basic](#chapter-1-basic)
  - [Introduction](#introduction)
  - [Object Coupling Problem](#object-coupling-problem)
- [Chapter 2. Fundamentals](#chapter-2-fundamentals)
  - [Using XML](#using-xml)
  - [Using Annotation](#using-annotation)

# Chapter 1. Basic 
## Introduction 
- Spring has been built for - the *dependency injection* (DI)
## Object Coupling Problem 
- A tighly couple code is always bad for good scalable and testable components
- Example
  ```java
    public class VanillaDataReaderClient {
        private FileReader fileReader = null;
        private String fileName = "src/main/resources/basics/basics-trades-data.txt";

        public VanillaDataReaderClient() {
            try {
            fileReader = new FileReader(fileName);
            } catch (FileNotFoundException e) {
            System.out.println("Exception" + e.getMessage());
            }
        }

        private String fetchData() {
            return fileReader.read();
        }

        public static void main(String[] args) {
            VanillaDataReaderClient dataReader = new VanillaDataReaderClient();
            System.out.println("Got data using no-spring: " + dataReader.fetchData());
        }
    }
  ```


# Chapter 2. Fundamentals

- For Spring, all objects are beans.
- Beans are the objects that are created and manage by the Spring Framework
  - There is a context (consider this as a bucket of beans) - a container in Spring terms
  - You can query this container using `getBeans()` method
- To init beans, metadata can be provided using simple XML file, annotation and Java configuration

## Using XML
- Spring reads the config file and init and loads classes into a runtime contianer
- In below sample xml file note the use of `constructor-arg`, `property`, `ref`
  - `constructor-arg` is used for constructor arguments (later we will see how to define ordering in the constructor argument and type parsing from `String` to the specific define in constructor)
  - For setters you can use `property`, note that if it is a simple value then you can use `value` else if it is a reference to some other bean then you can use `ref`
    ```xml
    <?xml version="1.0" encoding="UTF-8" ?>
    <beans xmlns="http://www.springframework.org/schema/beans"
           xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
           xsi:schemaLocation="http://www.springframework.org/scheam/beans
           http://www.springframework.org/schema/beans/spring-beans.xsd">
            <bean name="person" class="com.souravsh.beans.Person">
                <constructor-arg value="Sourav" />
                <constructor-arg value="Sharma" />
                <property name="age" value="10" />
                <property name="address" ref="address"/>
            </bean>
            <bean name="address" class="com.souravsh.beans.Address">
                <property name="houseNumber" value="35" />
            </bean>
    </beans>
    ```

    ```java
    public class PersonClient {
        private static ApplicationContext context = null;
        public PersonClient() {
            context = new ClassPathXmlApplicationContext("path-to-xml-conf-file.xml");
        }
        public String getPersonDetails() {
            Person person = (Person) context.getBean("person");
            return person.getDetails();
        }
    }
    ```

## Using Annotation
- Another way to wire bens is using annotations
    ```java
    public class ReservationService {
        @Autowired
        private ReservationService reservationService = null;

        public void process(Reservation r) {
            reservationService.reserve(r);
        }
    }
    ```
- When a **variable**, **method** or **constructor** is annoated with `@Autowired`, framework will find the relevant dependency and inject that dependency automatically by lookin gat the `byType`
- To do so you need to specify framework that you are going to use annotations
  - Annotation `annotation-config` tag let the framework know we are following the annotation route
  - Note that name and class name are different and thus spring will use `byType` instead of `byName` when picking up the dependency
    ```xml
    <?xml version="1.0" encoding="UTF-8" ?>
    <beans xmlns="..."
           xmlns:xsi="..."
           xmlns:context="http://www.springframework.org/schema/context"
           xsi:schemaLocation="..."
           http://www.springframework.org/schema/context
           http://www.springframework.org/schema/context/spring-context.xsd"
    >
    <context:annotation-config/>
            <bean name="reservationService" class="com.souravsh.beans.Rs"/>
            <bean name="reservationManager" class="com.souravsh.beans.Rm"/>
    </beans>
    ```
