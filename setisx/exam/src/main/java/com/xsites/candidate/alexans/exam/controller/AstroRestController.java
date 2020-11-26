package com.xsites.candidate.alexans.exam.controller;

import java.util.List;

import javax.inject.Inject;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RestController;

import com.xsites.candidate.alexans.exam.dao.OfficerDAO;
import com.xsites.candidate.alexans.exam.entities.Officer;
import com.xsites.candidate.alexans.exam.services.AstroService;

@RestController
public class AstroRestController {

    private final AstroService service;
    
    @Inject
    private final OfficerDAO dao=null;

    @Autowired
    public AstroRestController(AstroService service) {
        this.service = service;
    }

    @GetMapping("/astronauts")
    public String getAstro() {
        return "There are " + service.getAstronauts().getNumber()
                + " people in space";
    }
    
    @GetMapping("/officers")
    public List<Officer> getOfficers() 
    {
        return dao.findAll();
    }
}

