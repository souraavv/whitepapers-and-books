package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class IndPizzaIngredientFactory implements PizzaIngredientFactory {
    public Dough createDough() {
        log.info("Indian style dough");
        return new SoftDough();
    }
    public Sauce createSauce() {
        log.info("Indian style sauce");
        return new IndTomatoSauce();
    }
    public Cheese createCheese() {
        log.info("Indian style cheese");
        return new SuperCheese();
    }
}
