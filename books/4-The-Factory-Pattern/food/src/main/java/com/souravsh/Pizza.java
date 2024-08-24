package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public abstract class Pizza {
    String name;
    Dough dough; 
    Sauce sauce; 
    Cheese cheese;

    void bake() {
        log.info("Baking pizza");
    }
    void cut() {
        log.info("Cutting pizza");
    }
    void box() {
        log.info("Place the pizza in the box");
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    abstract void prepare();
}
