package il.co.xsites.developertest.pizza;

import il.co.xsites.developertest.base.ro.ResultRO;
import il.co.xsites.developertest.pizza.annotation.QueryField;
import il.co.xsites.developertest.pizza.model.PizzaMenu;
import il.co.xsites.developertest.pizza.ro.PizzaMenuRO;
import il.co.xsites.developertest.utils.Utils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.ArrayList;
import java.util.List;

@Service("pizzaService")
public class PizzaServiceImpl implements PizzaService {

	protected Log log = LogFactory.getLog(getClass());

	@Autowired
	private PizzaHandler pizzaHandler;

	@Override
	public ResultRO getMenu(String name,String minPrice,String maxPrice) 
	{
		ResultRO resultRO = new ResultRO();

		try {
			List<PizzaMenu> menu = pizzaHandler.getPizzaMenu(name,minPrice,maxPrice);
			List<PizzaMenuRO> menuRO = new ArrayList<>();

			for(PizzaMenu pizzaMenu : menu) {
				menuRO.add(pizzaMenu.getRepresentation());
			}

			resultRO.setResult(menuRO);
		} catch(Exception e) {
			resultRO.setSuccess(false);
			resultRO.setError(e.getMessage());
		}

		return resultRO;
	}

	@Override
	public ResultRO orderPizza(Long id) {
		ResultRO resultRO = new ResultRO();

		PizzaMenu pizzaMenu = pizzaHandler.getPizza(id);
		String pizzaQueryString = Utils.extractQueryString(pizzaMenu, QueryField.class);

		resultRO.setResult(pizzaQueryString);

		return resultRO;
	}
}
