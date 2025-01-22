package opensource.souravsh.model;

import lombok.Getter;
import lombok.Setter;

import java.util.UUID;

@Getter
public class Player {
    private final String id;
    private final String name;
    @Setter
    private int position;
    @Setter
    private boolean won;

    public Player(String name) {
        this.id = UUID.randomUUID().toString();
        this.name = name;
        this.won = false;
        this.position = 1;
    }

}
