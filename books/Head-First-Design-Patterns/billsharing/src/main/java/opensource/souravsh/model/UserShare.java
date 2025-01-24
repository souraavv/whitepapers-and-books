package opensource.souravsh.model;

import java.util.ArrayList;
import java.util.List;

import lombok.Getter;
import lombok.Setter;

@Getter
@Setter
public class UserShare {
    private String userId;
    private double shareAmount;
    List<Contribution> contributions;

    public UserShare(String userId, double shareAmount) {
        this.userId = userId;
        this.shareAmount = shareAmount;
        this.contributions = new ArrayList<>();
    }
}
