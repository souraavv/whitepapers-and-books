package com.example.demo.controller;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import lombok.extern.slf4j.Slf4j;


@Slf4j
@RestController
public class HelloController {

    @GetMapping("/hello")
    public String sayHello() {
        return "hello, spring boot is running!";
    }
    
}