package il.co.xsites.challenge.pizza;

import static org.junit.Assert.*;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;


import il.co.xsites.challenge.base.ro.ResultRO;

@RunWith(SpringRunner.class)
@SpringBootTest
public class PizzaServiceImplTest {

	@Autowired
	PizzaService service;
	
	@Test
	public void testSearchByName() 
	{
		ResultRO resultRO = service.getMenu("Margherita", null, null);
		assertNotNull(resultRO);
		System.out.println(resultRO.getResult());
	}

	@Test
	public void testSearchByPrice() 
	{
		ResultRO resultRO = service.getMenu(null, "0", "99999999");
		assertNotNull(resultRO);
		System.out.println(resultRO.getResult());
	}

	@Test
	public void testOrderPizza() 
	{
		ResultRO resultRO = service.orderPizza((long) 1);
		assertNotNull(resultRO);
		System.out.println(resultRO.getResult());
	}
}
