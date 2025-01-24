package opensource.souravsh.model;


import lombok.*;

import java.time.LocalDateTime;


@Setter
@Getter
@NoArgsConstructor
@AllArgsConstructor
@Builder
public class Expense {
    private String expenseId;
    private String expenseCreatorId;

    private String title;
    private String description;

    private double expenseAmount;
    private LocalDateTime expenseCreationDate;
    private ExpenseStatus expenseStatus;
    private ExpenseGroup expenseGroup;
}
