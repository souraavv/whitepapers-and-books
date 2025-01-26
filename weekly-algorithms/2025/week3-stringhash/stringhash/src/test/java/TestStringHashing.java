import opensource.souravsh.StringHashing;
import opensource.souravsh.util.Pair;
import org.junit.Test;

import java.util.*;

public class TestStringHashing {

    @Test
    public void searchDuplicateStringsInArray() {
        List<String> array = Arrays.asList("apple", "banana", "cherry", "date", "apple", "date");
        int n = array.size();
        List<Pair<Long, Integer>> hashes = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            hashes.add(new Pair<>(StringHashing.computeHash(array.get(i)), i));
        }

        hashes.sort(Comparator.comparing(Pair::getFirst));

        List<List<Integer>> groups = new ArrayList<>();

        for (int i = 0; i < n; i++) {
            if (i == 0 || !Objects.equals(hashes.get(i).getFirst(), hashes.get(i - 1).getFirst())) {
                groups.add(new ArrayList<>());
            }
            groups.get(groups.size() - 1).add(hashes.get(i).getSecond());
        }

        for (Pair<Long, Integer> pair : hashes) {
            System.out.println("hash: " + pair.getFirst() + " , index: " + pair.getSecond());
        }

        for (List<Integer> group : groups) {
            System.out.println("group: " + group);
        }

    }
}
