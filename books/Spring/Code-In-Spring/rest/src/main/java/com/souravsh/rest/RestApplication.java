package com.souravsh.rest;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Profile;
import org.springframework.web.client.RestClientException;
import org.springframework.web.client.RestTemplate;

import lombok.extern.slf4j.Slf4j;

@Slf4j
@SpringBootApplication
public class RestApplication {

    public static void main(String[] args) {
		SpringApplication.run(RestApplication.class, args);
	}

    @Bean
    public RestTemplate restTemplate(RestTemplateBuilder builder) {
        return builder.build();
    }

    @Bean
    @Profile("local")
    public CommandLineRunner run(RestTemplate restTemplate, 
            @Value("${server.port:8080}") int serverPort) {
        return _ -> {
            String url = String.format("http://localhost:%d/api/random", 
                    serverPort);
            try {
                Quote quote = restTemplate.getForObject(url, Quote.class);
                if (quote != null && quote.value() != null) {
                    log.info("Recieved quote: id: {}, text: {}",
                            quote.value().id(), quote.value().quote());
                } else {
                    log.warn("nothing avail");
                }
            } catch (RestClientException ex) {
                log.error("Could not fetch quote from {}; continuing "
                        + "without failing startup. Reason: {}", 
                        url, ex.getMessage());
            }
        };
    }
}
