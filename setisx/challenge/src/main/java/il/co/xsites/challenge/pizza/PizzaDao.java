package il.co.xsites.challenge.pizza;

import java.util.List;

import il.co.xsites.challenge.pizza.model.PizzaMenu;

public interface PizzaDao {

	List<PizzaMenu> getPizzaMenus(String name,String minPrice,String maxPrice);

	PizzaMenu getPizza(Long id);
}
