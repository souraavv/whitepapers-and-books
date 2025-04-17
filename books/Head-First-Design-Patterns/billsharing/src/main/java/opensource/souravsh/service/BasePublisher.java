package opensource.souravsh.service;

import java.util.HashSet;
import java.util.Set;

import opensource.souravsh.model.Expense;

public class BasePublisher {
    private Set<ExpenseSubscriber> subscribers = new HashSet<>();

    public void addSubscriber(ExpenseSubscriber subscriber) {
        subscribers.add(subscriber);
    }

    public void removeSubscriber(ExpenseSubscriber subscriber) {
        subscribers.remove(subscriber);
    }

    public void notifySubscribers(Object o) {
        for (ExpenseSubscriber subscriber : subscribers) {
            subscriber.update(o);
        }
    }

    public void notifySubscriber(Object o, ExpenseSubscriber s) {
        if (subscribers.contains(s)) {
            s.update(o);
        } else {
            System.out.println("Subscriber not found");
        }
    }
}