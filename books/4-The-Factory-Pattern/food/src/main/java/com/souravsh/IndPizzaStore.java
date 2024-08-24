package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class IndPizzaStore extends PizzaStore {

    protected Pizza createPizza(String type) {
        Pizza pizza = null;
        PizzaIngredientFactory iFactory = new IndPizzaIngredientFactory();
        if (type.equals("cheese")) {
            pizza = new CheesePizza(iFactory);
            pizza.setName("Indian Style Cheese Pizza");
        }
        if (type.equals("veggie")) {
            pizza = new VeggiePizza(iFactory);
            pizza.setName("Indian Style Veggie Pizza");
        }
        return pizza;
    }
}