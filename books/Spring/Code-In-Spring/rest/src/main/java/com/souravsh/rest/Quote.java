package com.souravsh.rest;

import com.fasterxml.jackson.annotation.JsonIgnoreProperties;

/**
 * Domain record that maps the top-level JSON for the quoters response.
 * Example JSON:
 * {
 *   "type": "success",
 *   "value": {
 *     "id": 10,
 *     "quote": "Really loving Spring Boot..."
 *   }
 * }
 */
@JsonIgnoreProperties(ignoreUnknown = true)
public record Quote(String type, Value value) {}
