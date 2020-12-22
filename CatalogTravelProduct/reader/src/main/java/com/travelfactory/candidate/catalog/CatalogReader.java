package com.travelfactory.candidate.catalog;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.WebApplicationType;
import org.springframework.boot.autoconfigure.SpringBootApplication;
import org.springframework.boot.autoconfigure.domain.EntityScan;

@SpringBootApplication(scanBasePackages = "com.travelfactory.candidate")
@EntityScan( basePackages = {"com.travelfactory.candidate"} )
public class CatalogReader 
{
	
	public static void main(String[] args) 
	{
		 SpringApplication app = new SpringApplication(CatalogReader.class);
		 app.setWebApplicationType(WebApplicationType.NONE);
		 app.run(args);
	}
}
