package opensource.souravsh;
import opensource.souravsh.util.Pair;
import org.junit.Test;

import java.util.*;

public class Main {
    public static void main(String[] args) {
        long val = StringHashing.computeHash("abc");
        System.out.println("val = " + val);
    }
}