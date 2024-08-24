package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class CheesePizza extends Pizza {
    PizzaIngredientFactory iFactory;
    public CheesePizza(PizzaIngredientFactory iFactory) {
        this.iFactory = iFactory;
    }

    void prepare() {
        log.info("preparing " + name);
        dough = iFactory.createDough();
        sauce = iFactory.createSauce();
        cheese = iFactory.createCheese();
    }
}