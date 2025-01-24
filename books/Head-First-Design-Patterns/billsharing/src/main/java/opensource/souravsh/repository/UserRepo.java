package opensource.souravsh.repository;

import opensource.souravsh.model.User;

import java.util.HashMap;
import java.util.Map;

public class UserRepo {
    // emailId -> User
    public static Map<String, User> users = new HashMap<>();
}
