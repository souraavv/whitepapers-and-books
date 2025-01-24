package opensource.souravsh.service;

import opensource.souravsh.model.Notification;
import opensource.souravsh.model.User;

public class EmailNotificationService implements NotificationService{
    @Override
    public void sendNotification(User user, Notification notification) {
        System.out.println("Hey " + user.getName() + "!");
        System.out.print("Email notification: " + notification.toString());
    }
}
