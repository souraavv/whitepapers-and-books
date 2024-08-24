package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class TomatoSauce implements Sauce {
    String name;
    public TomatoSauce() {
        log.info("tomato sauce");
        name = "Tomato Sauce";
    }
    public String getName() {
        return name;
    }
}