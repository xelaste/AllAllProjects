package il.co.xsites.challenge.pizza;

import il.co.xsites.challenge.base.ro.ResultRO;

public interface PizzaService {

	ResultRO getMenu(String name,String minPrice,String maxPrice);
	ResultRO orderPizza(Long id);
}
