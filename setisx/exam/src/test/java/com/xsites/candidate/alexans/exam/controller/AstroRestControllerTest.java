package com.xsites.candidate.alexans.exam.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.mock.mockito.MockBean;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;

import com.xsites.candidate.alexans.exam.application.ExamApplication;
import com.xsites.candidate.alexans.exam.entities.AstroResponse;
import com.xsites.candidate.alexans.exam.entities.Officer;
import com.xsites.candidate.alexans.exam.services.AstroService;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.mockito.Mockito.when;

import java.util.ArrayList;
import java.util.List;

import org.junit.jupiter.api.Test;

@SpringBootTest(classes=ExamApplication.class, webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class AstroRestControllerTest {
    @Autowired
    private TestRestTemplate template;

    @MockBean
    private AstroService service;

    @Test
    public void numberOfAstronauts() {
        AstroResponse astroResponse = new AstroResponse();
        astroResponse.setNumber(6);
        when(service.getAstronauts()).thenReturn(astroResponse);

        String response = template.getForObject("/astronauts", String.class);
        assertEquals("There are 6 people in space", response);
    }
    
    
    @Test
    public void numberOfOficers() 
    {
    	ResponseEntity<List> entity = template.getForEntity("/officers",  List.class);
        assertEquals(HttpStatus.OK, entity.getStatusCode());
        assertEquals(MediaType.APPLICATION_JSON, entity.getHeaders().getContentType());
    }

}