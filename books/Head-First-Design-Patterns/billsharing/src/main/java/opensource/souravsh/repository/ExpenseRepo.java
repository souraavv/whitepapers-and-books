package opensource.souravsh.repository;

import lombok.Getter;
import lombok.Setter;
import opensource.souravsh.model.Expense;
import opensource.souravsh.model.ExpenseGroup;

import java.util.HashMap;
import java.util.Map;

@Getter
@Setter
public class ExpenseRepo {
    public static Map<String, Expense> expenses = new HashMap<>();
    public static Map<String, ExpenseGroup> expenseGroups = new HashMap<>();
}
