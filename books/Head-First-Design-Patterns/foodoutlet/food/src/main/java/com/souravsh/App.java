package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class App 
{
    public static void main(String[] args) {
        PizzaStore nyPizzaStore = new NyPizzaStore();
        nyPizzaStore.orderPizza("cheese");
        nyPizzaStore.orderPizza("veggie");

        PizzaStore IndPizzaStore = new IndPizzaStore();
        IndPizzaStore.orderPizza("cheese");
        IndPizzaStore.orderPizza("veggie");
    }
}
