package com.souravsh.taco;

import java.util.List;

import jakarta.validation.constraints.NotNull;
import jakarta.validation.constraints.Size;
import lombok.Data;

@Data
public class Taco {
    @NotNull
    @Size(min=5, message="Name must be atleast 5 character long")
    private String name;
    
    @NotNull
    @Size(min=1, message="Must choose on ingredient")
    private List<Ingredient> ingredient;
}
