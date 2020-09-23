package il.co.xsites.developertest.pizza;

import il.co.xsites.developertest.base.BaseDaoImpl;
import il.co.xsites.developertest.pizza.model.PizzaMenu;
import org.hibernate.Criteria;
import org.hibernate.criterion.Restrictions;
import org.springframework.stereotype.Repository;

import java.util.List;

@SuppressWarnings("ALL")
@Repository
public class PizzaDaoImpl extends BaseDaoImpl implements PizzaDao {

	@Override
	public List<PizzaMenu> getPizzaMenus(String name,String minPrice,String maxPrice) 
	{
		Criteria criteria = getCurrentSession().createCriteria(PizzaMenu.class);
		if (name!=null&&!name.isEmpty())
		{
			criteria.add(Restrictions.eq("name", name));
		}
		if (minPrice!=null&&!minPrice.isEmpty())
		{
			criteria.add(Restrictions.ge("price",Double.parseDouble(minPrice)));
		}
		if (maxPrice!=null&&!maxPrice.isEmpty())
		{
			criteria.add(Restrictions.le("price", Double.parseDouble(maxPrice)));
		}		
		return criteria.list();
	}

	@Override
	public PizzaMenu getPizza(Long id) {
		return findObject(PizzaMenu.class, id);
	}
}
