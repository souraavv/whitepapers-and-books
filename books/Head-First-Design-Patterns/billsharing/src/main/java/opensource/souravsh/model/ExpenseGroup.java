package opensource.souravsh.model;

import lombok.Getter;
import lombok.Setter;

import java.util.*;


@Getter
public class ExpenseGroup {
    private String expenseGroupId;
    private Set<User> groupMember;
    @Setter
    // expenseId -> List<UserShare>
    // Expense has an amount, and amount is equally distributed to the

    private Map<String, Set<UserShare>> usersContributions;
    // Expense ID ->
    public ExpenseGroup() {
        this.expenseGroupId = UUID.randomUUID().toString();
        this.groupMember = new HashSet<>();
    }

//    public void addAnExpense(@org.jetbrains.annotations.NotNull Expense expense) {
//        userContributions.computeIfAbsent(expense.getExpenseId(), k -> new HashSet<>());
//        userContributions.get(expense.getExpenseId()).add()
//    }


}
