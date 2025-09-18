package com.souravsh.rest.controller;

import java.util.Arrays;
import java.util.Random;

import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.souravsh.rest.Quote;
import com.souravsh.rest.Value;


@RestController
public class QuotersController {

    private static final Value[] QUOTES = new Value[] {
            new Value(1L, "Working."),
            new Value(2L, "Spring."),
            new Value(3L, "Really."),
            new Value(4L, "Spring's.")
        };

    @GetMapping("/api/random")
    public Quote randomQuote() {
        Random random = new Random();
        Value value = QUOTES[random.nextInt(4)];
        return new Quote("success", value);
    }

    @GetMapping("/api")
    public Quote[] allQuotes() {
        return Arrays.stream(QUOTES)
                .map(v -> new Quote("success", v))
                .toArray(Quote[]::new);
    }
    
}
