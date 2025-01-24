package opensource.souravsh.service;

import opensource.souravsh.model.*;

import opensource.souravsh.repository.ExpenseRepo;
import opensource.souravsh.repository.UserRepo;

import java.util.Objects;
import java.util.Optional;


public class UserService {

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

            Optional<UserShare> userShare =
                    expenseGroup.getUsersContributions().get(expenseId).stream().filter(share ->
                            Objects.equals(share.getUserId(),
                                    user.getUserId())).findFirst();
            if (userShare.isPresent()) {

            } else {
                
            }

        } else {
            throw new IllegalArgumentException("Expense with id " + expenseId + " not found");

        }

    }





}
