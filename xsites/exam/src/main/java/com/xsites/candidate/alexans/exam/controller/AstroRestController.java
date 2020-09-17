package com.xsites.candidate.alexans.exam.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.xsites.candidate.alexans.exam.services.AstroService;

@RestController
public class AstroRestController {

    private final AstroService service;

    @Autowired
    public AstroRestController(AstroService service) {
        this.service = service;
    }

    @GetMapping("/astronauts")
    public String getAstro() {
        return "There are " + service.getAstronauts().getNumber()
                + " people in space";
    }
}
