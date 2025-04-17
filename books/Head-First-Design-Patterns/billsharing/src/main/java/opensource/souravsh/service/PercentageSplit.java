package opensource.souravsh.service;

import java.util.List;
import java.util.HashMap;
import java.util.Map; 

public class PercentageSplit implements SplitStrategy {
    @Override
    public Map<String, Double> splitAmount(Double amount, List<String> userIds, 
            List<Double> percentages) {
        Map<String, Double> userAmountMap = new HashMap<>();

        for (int i = 0; i < userIds.size(); i++) {
            userAmountMap.put(userIds.get(i), amount * percentages.get(i) / 100);
        }
        return userAmountMap;
    }
    
}
