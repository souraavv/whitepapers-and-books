
package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class VeggiePizza extends Pizza {
    PizzaIngredientFactory iFactory; 
    VeggiePizza(PizzaIngredientFactory iFactory) {
        this.iFactory = iFactory;
    }
    void prepare() {
        log.info("preparing " + name);
        dough = iFactory.createDough();
        sauce = iFactory.createSauce();
        cheese = iFactory.createCheese();
    }
}