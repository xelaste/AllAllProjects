package com.eci.chalenge.config;

import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Scope;

import java.util.LinkedList;
import java.util.List;

@Configuration
public class Config {
    @Bean
    @Scope("singleton")
    public List<String> files()
    {
        return new LinkedList<String>();
    }
}
