package opensource.souravsh.service;

import java.util.List;
import java.util.Map;

public interface SplitStrategy {
    default Map<String, Double> splitAmount(Double amount, 
            List<String> userIds) {
        throw new UnsupportedOperationException("Not implemented");
    }

    default Map<String, Double> splitAmount(Double amount, List<String> userIds, 
            List<Double> splitInfo) {
        throw new UnsupportedOperationException("Not implemented");
    }
}
