package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class SoftDough implements Dough {
    String name;
    public SoftDough() {
        name = "Soft dough";
        log.info(name);
    }
    public String getName() {
        return name;
    }
}