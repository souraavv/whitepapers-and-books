package opensource.souravsh.service;

import java.util.HashMap;
import java.util.List;
import java.util.Map; 

public class EqualSplit implements SplitStrategy {
    @Override
    public Map<String, Double> splitAmount(Double amount, 
            List<String> userIds) {
        Map<String, Double> userAmountMap = new HashMap<>();
        Double amountPerUser = amount / userIds.size();
        userIds.forEach(userId -> userAmountMap.put(userId, amountPerUser));
        return userAmountMap;
    }
}
