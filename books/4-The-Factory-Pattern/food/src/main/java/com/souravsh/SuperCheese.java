package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SuperCheese implements Cheese {
    String name;
    public SuperCheese() {
        name = "Super Cheese";
        log.info(name);
    }
    public String getName() {
        return name;
    }
}