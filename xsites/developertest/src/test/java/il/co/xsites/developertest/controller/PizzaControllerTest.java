package il.co.xsites.developertest.controller;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import org.springframework.test.context.junit4.SpringRunner;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;

import il.co.xsites.developertest.base.ro.ResultRO;

@RunWith(SpringRunner.class)
@SpringBootTest(webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
public class PizzaControllerTest 
{

	@Autowired 
	TestRestTemplate template;
	@Test
	public void test() 
	{
		Gson gson = new GsonBuilder().setPrettyPrinting().create();
		ResponseEntity<ResultRO> entity = template.getForEntity("/pizza/menu?minPrice=2.99", ResultRO.class);
        assertEquals(HttpStatus.OK, entity.getStatusCode());
        assertEquals(MediaType.APPLICATION_JSON_UTF8, entity.getHeaders().getContentType());
        ResultRO response = entity.getBody();
        System.out.println(gson.toJson(response));
        assertTrue(response.isSuccess());

	}
	@Test
	public void testOrder() 
	{
		Gson gson = new GsonBuilder().setPrettyPrinting().create();
		ResponseEntity<ResultRO> entity = template.postForEntity("/pizza/order?id=1",null, ResultRO.class);
        assertEquals(HttpStatus.OK, entity.getStatusCode());
        assertEquals(MediaType.APPLICATION_JSON_UTF8, entity.getHeaders().getContentType());
        ResultRO response = entity.getBody();
        System.out.println(gson.toJson(response));
        assertTrue(response.isSuccess());

	}
	

}
