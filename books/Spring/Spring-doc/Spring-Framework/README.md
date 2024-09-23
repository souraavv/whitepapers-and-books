

## The IoC container
### Introduction to the Spring IoC Containers and Beans

- IoC is a broader principle of design pattern where the control flow of the program is inverted 
  - Instead programmer instantiation of dependencies, the resposibility is inverted to an external framework 
- Dependency Injection (DI) is a specialized form of IoC
  - DI is one of the technique to achieve IoC, where objects are injected into a class, rather than a class creating object
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
    - In the above example `NotifactionService` is tightly coupled with the `EmailService` 
    </details> 
  - In case of DI object defines their dependency only through **constructor arguments**, **arguments to a factory method**, or **properties that are set on the object instance after it is constructed**

- The `org.springframework.beans` and `org.springframework.context` packages are the basic of Spring Framework IoC's containers
- The `BeanFactory` interface provides an advanced configuration mechanism capable of managing any type of objects
  - `BeanFactory` provides the configuration framework and basic functionality 
- `ApplicationContext` is a sub-interface of `BeanFactory`
  - `ApplicationContext` adds more enterprise-specific functionality 
  - `ApplicationContext` is a superset of `BeanFactory` 

- In Spring, the objects which are backbone of your application and that are managed by Spring IoC contianers are called as beans
- A bean is an object that is instantiated, assembled, and managed by Spring IoC container 

