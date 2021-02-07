package com.eci.chalenge.be;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

@SpringBootApplication(scanBasePackages = "com.eci.chalenge")
public class BeApplication {
	public static void main(String[] args) {
		SpringApplication.run(BeApplication.class, args);
	}

}
