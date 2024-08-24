package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class ThinCrustDough implements Dough {
    String name;
    public ThinCrustDough() {
        name = "Thin crust dough";
        log.info(name);
    }
    public String getName() {
        return name;
    }
}