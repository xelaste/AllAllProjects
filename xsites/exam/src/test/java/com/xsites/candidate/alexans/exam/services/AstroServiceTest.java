package com.xsites.candidate.alexans.exam.services;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertTrue;

import org.junit.jupiter.api.Test;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;

import com.xsites.candidate.alexans.exam.application.ExamApplication;
import com.xsites.candidate.alexans.exam.entities.AstroResponse;


@SpringBootTest(classes = ExamApplication.class)
public class AstroServiceTest {
    private Logger logger = LoggerFactory.getLogger(AstroServiceTest.class);

    @Autowired
    private AstroService service;

    @Test
    public void getAstronauts() {
        AstroResponse response = service.getAstronauts();
        logger.info(response.toString());
        assertEquals("success", response.getMessage());
        assertTrue(response.getNumber() >= 0);
        assertEquals(response.getNumber(), response.getPeople().size());
    }
}