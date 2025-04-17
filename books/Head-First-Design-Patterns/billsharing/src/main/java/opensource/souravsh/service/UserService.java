package opensource.souravsh.service;

import java.util.Objects;
import java.util.Optional;

import lombok.extern.slf4j.Slf4j;
import opensource.souravsh.model.Contribution;
import opensource.souravsh.model.Expense;
import opensource.souravsh.model.ExpenseGroup;
import opensource.souravsh.model.User;
import opensource.souravsh.model.UserShare;
import opensource.souravsh.repository.ExpenseRepo;
import opensource.souravsh.repository.UserRepo;

@Slf4j
public class UserService implements ExpenseSubscriber {

    @Override
    public void update(Object o) {
        if (o instanceof String) {
            log.info("User added to group: {}", o);
        } else if (o instanceof Expense) {
            log.info("Expense created: {}", ((Expense) o).getTitle());
        } else {
            throw new IllegalArgumentException("Invalid object type");
        }
    }

    public User createUser(String name, String emailId, String phoneNumber) {
        User user = new User(name, emailId, phoneNumber);
        UserRepo.users.put(emailId, user);
        return user;
    }

    public void contributeToExpense(String expenseId, String emailId,
            Contribution contribution) {
        Expense expense = ExpenseRepo.expenses.get(expenseId);
        User user = UserRepo.users.get(emailId);
        if (expense != null) {
            ExpenseGroup expenseGroup = expense.getExpenseGroup();

            Optional<UserShare> userShare = expenseGroup.getUsersContributions().get(expenseId).stream()
                    .filter(share -> Objects.equals(share.getUserId(),
                            user.getUserId()))
                    .findFirst();
                    
            if (userShare.isPresent()) {

            } else {

            }

        } else {
            throw new IllegalArgumentException("Expense with id " + expenseId + " not found");

        }

    }

}
