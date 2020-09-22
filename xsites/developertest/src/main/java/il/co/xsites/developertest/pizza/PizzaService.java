package il.co.xsites.developertest.pizza;

import il.co.xsites.developertest.base.ro.ResultRO;

public interface PizzaService {

	ResultRO getMenu(String name,String minPrice,String maxPrice);
	ResultRO orderPizza(Long id);
}
