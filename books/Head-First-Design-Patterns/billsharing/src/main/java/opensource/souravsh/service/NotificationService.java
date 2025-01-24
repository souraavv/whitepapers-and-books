package opensource.souravsh.service;

import opensource.souravsh.model.Notification;
import opensource.souravsh.model.User;

public interface NotificationService {
    public void sendNotification(User user, Notification notification);
}
