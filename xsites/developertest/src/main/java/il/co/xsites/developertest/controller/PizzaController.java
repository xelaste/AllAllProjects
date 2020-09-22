package il.co.xsites.developertest.controller;

import il.co.xsites.developertest.base.ro.ResultRO;
import il.co.xsites.developertest.pizza.PizzaService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.*;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * Controller for work with Pizza REST api service.
 */
@Controller
public class PizzaController {

	@Autowired
	private PizzaService pizzaService;

	/**
	 * TODO - 1:
	 *
	 * Currently this api call returns all pizza menus from the db.
	 * Enhance this api call with the ability to search for a pizza menu item by name and / or between minPrice / maxPrice.
	 * e.g. /pizza/menu?name=chees&maxPrice=10 should return pizza data for pizza 'Cheesy Crust'
	 * e.g. /pizza/menu?minPrice=0&maxPrice=1 should return pizza data for pizza 'Margherita'
	 *
	 * @param request
	 * @param response
	 * @return
	 */
	@ResponseBody
	@RequestMapping(value = "/pizza/menu", method = RequestMethod.GET)
	public ResultRO getMenu(HttpServletRequest request, HttpServletResponse response) {
		String name = request.getParameter("name");
		String minPrice=request.getParameter("minPrice");
		String maxPrice=request.getParameter("minPrice");
		return pizzaService.getMenu(name,minPrice,maxPrice);
	}

	/**
	 * TODO - 2:
	 *
	 * 1. Create a new custom java annotation.
	 * 2. Add the new custom annotation on PizzaMenu's name & price fields.
	 * 3. Implement stub Utils.extractQueryString which extracts a query string
	 * (e.g. fieldName=fieldValue&fieldName2=fieldValue2) from every PizzaMenu field which is
	 * annotated with the new custom java annotation.
	 * e.g When calling /pizza/order?id=3 the result should be 'name=Sicilian&price=2.99'
	 *
	 * @param id
	 * @param request
	 * @param response
	 * @return
	 */
	@ResponseBody
	@RequestMapping(value = "/pizza/order", method = RequestMethod.POST)
	public ResultRO orderPizza(@RequestParam Long id, HttpServletRequest request, HttpServletResponse response) {
		return pizzaService.orderPizza(id);
	}
}
