package opensource.souravsh.model;

import lombok.Setter;
import lombok.Getter;
import lombok.NonNull;

import java.util.UUID;

@Getter
@Setter
public class User {
    private String name;
    private String emailId;
    private String phoneNumber;
    private String userId;

    public User(@NonNull String emailId, @NonNull String name,
                String phoneNumber) {
        userId = UUID.randomUUID().toString();
        this.emailId = emailId;
        this.name = name;
        this.phoneNumber = phoneNumber;
    }
}
