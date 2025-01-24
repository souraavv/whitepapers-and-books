package opensource.souravsh.model;

import lombok.Getter;
import lombok.Setter;
import lombok.ToString;

import java.time.LocalDateTime;

@Getter
@Setter
@ToString
public class Notification {
    private String notificationMessage;
    private LocalDateTime notificationTime;

    public Notification(String notificationMessage) {
        this.notificationMessage = notificationMessage;
        this.notificationTime = LocalDateTime.now();
    }
}
