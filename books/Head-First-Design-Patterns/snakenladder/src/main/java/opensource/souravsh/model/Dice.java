package opensource.souravsh.model;


import lombok.AllArgsConstructor;
import lombok.Getter;
import java.util.Random;

@Getter
@AllArgsConstructor
public class Dice {
    private int minValue;
    private int maxValue;

    public int roll() {
        Random random = new Random();
        return minValue + random.nextInt(maxValue - minValue + 1);
    }
}
