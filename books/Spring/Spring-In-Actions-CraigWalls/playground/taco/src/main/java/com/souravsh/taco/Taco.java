package com.souravsh.taco;

import java.util.List;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;

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
