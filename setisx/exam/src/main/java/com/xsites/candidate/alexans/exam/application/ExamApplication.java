package com.xsites.candidate.alexans.exam.application;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;

@SpringBootApplication(scanBasePackages = "com.xsites.candidate.alexans.exam")
@EntityScan( basePackages = {"com.xsites.candidate.alexans.exam"} )
public class ExamApplication 
{
	public static void main(String[] args) {
		SpringApplication.run(ExamApplication.class, args);
	}

}
