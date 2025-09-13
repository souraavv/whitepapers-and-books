package com.example.demo.service;

import org.springframework.stereotype.Service;

import java.util.List; 
import java.util.Optional;

import com.example.demo.model.Person;

import com.example.demo.repository.PersonRepository;

import lombok.AllArgsConstructor;

@AllArgsConstructor
@Service
public class PersonService {
    private PersonRepository repository; 

    public List<Person> findAll() {
        return repository.findAll();
    }

    public Optional<Person> findById(Long id) {
        return repository.findById(id);
    }

    public Optional<Person> findByEmail(String email) {
        return repository.findByEmail(email);
    }

    public Person create(Person p) {
        return repository.save(p);
    }


}
