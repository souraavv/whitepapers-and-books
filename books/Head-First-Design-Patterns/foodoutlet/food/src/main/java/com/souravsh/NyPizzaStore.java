package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class NyPizzaStore extends PizzaStore {

    protected Pizza createPizza(String type) {
        Pizza pizza = null;
        PizzaIngredientFactory iFactory = new NyPizzaIngredientFactory();
        if (type.equals("cheese")) {
            pizza = new CheesePizza(iFactory);
            pizza.setName("New York Style Cheese Pizza");
        }
        if (type.equals("veggie")) {
            pizza = new VeggiePizza(iFactory);
            pizza.setName("New York Style Veggie Pizza");
        }
        return pizza;
    }
}