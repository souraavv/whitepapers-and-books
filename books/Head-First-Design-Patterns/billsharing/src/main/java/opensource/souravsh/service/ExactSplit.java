package opensource.souravsh.service;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class ExactSplit implements SplitStrategy {
    
    @Override
    public Map<String, Double> splitAmount(Double amount, 
            List<String> userIds, List<Double> exactSplits) {
        
        Map<String, Double> splits = new HashMap<>();
        for (int i = 0; i < userIds.size(); ++i) {
            splits.put(userIds.get(i), exactSplits.get(i));
        }
        return splits;

    }
}
