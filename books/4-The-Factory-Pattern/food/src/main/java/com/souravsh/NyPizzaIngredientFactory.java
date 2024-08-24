package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class NyPizzaIngredientFactory implements PizzaIngredientFactory {
    public Dough createDough() {
        log.info("New york style dough");
        return new ThinCrustDough();
    }
    public Sauce createSauce() {
        log.info("New Yor style sauce");
        return new TomatoSauce();
    }
    public Cheese createCheese() {
        log.info("New Yor style cheese");
        return new SuperCheese();
    }
}