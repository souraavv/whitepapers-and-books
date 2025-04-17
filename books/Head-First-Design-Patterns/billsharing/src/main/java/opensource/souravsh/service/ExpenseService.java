package opensource.souravsh.service;


import opensource.souravsh.model.*;
import opensource.souravsh.repository.ExpenseRepo;
import opensource.souravsh.repository.UserRepo;

import java.time.LocalDateTime;
import java.util.Set;
import java.util.UUID;

public class ExpenseService {


    private SplitStrategy splitStrategy = new EqualSplit();
    private BasePublisher publisher = new BasePublisher();


    public Expense createExpense(String expenseCreatorId, String title,
                                 String description, Double expenseAmount,
                                 ExpenseGroup expenseGroup) {
        Expense expense = Expense.builder()
                .expenseId(UUID.randomUUID().toString())
                .expenseCreatorId(expenseCreatorId)
                .expenseAmount(expenseAmount)
                .description(description)
                .title(title)
                .expenseGroup(expenseGroup)
                .expenseCreationDate(LocalDateTime.now())
                .expenseStatus(ExpenseStatus.CREATED)
                .build();
        ExpenseRepo.expenses.put(expense.getExpenseId(), expense);
        return expense;
    }

    public ExpenseGroup createExpenseGroup() {
        ExpenseGroup expenseGroup =  new ExpenseGroup();
        ExpenseRepo.expenseGroups.put(expenseGroup.getExpenseGroupId(),
                expenseGroup);
        return expenseGroup;
    }

    public void addMemberToExpenseGroup(String userId, String expenseGroupId) {
        ExpenseGroup expenseGroup = ExpenseRepo.expenseGroups.get(expenseGroupId);
        if (expenseGroup != null) {
            User user = UserRepo.users.get(userId);
            if (user != null) {
                expenseGroup.getGroupMember().add(user);
                publisher.addSubscriber(user);
                publisher.notifySubscribers(String.format("User '%s' added to group", user.getName()));
            } else {
                throw new IllegalArgumentException("Invalid user id provided:" +
                        " " + userId);
            }
        } else {
            throw new IllegalArgumentException("Invalid expense Group ID " +
                    "provided: " + expenseGroupId);
        }
    }

    public void addExpenseToExpenseGroup(String expenseId,
                                         String expenseGroupId) {

        ExpenseGroup expenseGroup =
                ExpenseRepo.expenseGroups.get(expenseGroupId);
        if (expenseGroup != null) {
            Expense expense = ExpenseRepo.expenses.get(expenseId);
            if (expense != null) {
                expense.setExpenseGroup(expenseGroup);

            } else {
                throw new IllegalArgumentException("Invalid expense Id: " + expenseId);
            }

        } else {
            throw new IllegalArgumentException("Invalid expenseGroupId: " + expenseGroupId);

        }
    }

    public void setExpenseStatus(String expenseId, ExpenseStatus expenseStatus) {
        ExpenseRepo.expenses.get(expenseId).setExpenseStatus(expenseStatus);
    }

    public void evaluateExpenseStatus(String expenseId) {
        Expense expense = ExpenseRepo.expenses.get(expenseId);
        if (expense != null) {
            double totalExpenseAmount = expense.getExpenseAmount();
            ExpenseGroup expenseGroup = expense.getExpenseGroup();

            Set<UserShare> userShares =
                    expenseGroup.getUsersContributions().get(expenseId);

            double contributionTillNow =
                    userShares.stream().flatMap(userShare -> userShare.getContributions().stream()).
                    mapToDouble(Contribution::getContributionValue)
                            .sum();
            if (contributionTillNow == totalExpenseAmount) {
                setExpenseStatus(expenseId, ExpenseStatus.SETTLED);
            }
        } else {
            throw new IllegalArgumentException("Invalid expense Id: " + expenseId);
        }
    }

    public boolean isExpenseSettled(String expenseId) {
        evaluateExpenseStatus(expenseId);
        Expense expense = ExpenseRepo.expenses.get(expenseId);
        if (expense != null) {
            return expense.getExpenseStatus().equals(ExpenseStatus.SETTLED);
        } else {
            throw new IllegalArgumentException("Invalid expense Id: " + expenseId);
        }

    }

}
