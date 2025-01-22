package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class PizzaStore {
    
    public Pizza orderPizza(String type) {
        Pizza pizza;
        pizza = createPizza(type);
        pizza.prepare();
        pizza.bake();
        pizza.cut();
        pizza.box();
        return pizza;
    }
    protected abstract Pizza createPizza(String type);
}