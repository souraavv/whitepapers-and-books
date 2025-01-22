package com.souravsh;

import lombok.extern.slf4j.Slf4j;

@Slf4j
public class IndTomatoSauce implements Sauce {
    String name;
    public IndTomatoSauce() {
        log.info("tomato sauce");
        name = "Tomato Sauce";
    }
    public String getName() {
        return name;
    }
}