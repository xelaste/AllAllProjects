package adapters;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import domain.Order;
import domain.OrderResult;

public class StockfighterRestAdapterTest {

	private StockfighterRestAdapter stockfighterRestAdapter;
	@Before
	public void setUp() throws Exception 
	{
		stockfighterRestAdapter = new StockfighterRestAdapter();
	}

	@After
	public void tearDown() throws Exception 
	{
	
	}

	@Test
	public void testHeartbeat() 
	{
		stockfighterRestAdapter.heartbeat();
	}
	@Test
	public void testVenueHeartbeat() 
	{
		stockfighterRestAdapter.venueHeartbeat("TESTEX");
	}
	@Test
	public void testVenueStocks() 
	{
		stockfighterRestAdapter.venueStocks("TESTEX");
	}
	@Test
	public void testOrderBookStocks() 
	{
		stockfighterRestAdapter.orderbookForAStock("TESTEX","FOOBAR");
	}
	@Test
	public void placeNewOrder ()
	{
		/*
		 *"account": "MST92145671",
  "venue": "LOBHEX",
  "stock": "LPEI",
  "qty": 100,
  "direction": "buy",
  "orderType": "market"  
		 */
		Order order = new Order();
		order.setStock("FOOBAR");
		order.setAccount("EXB123456");		
		order.setVenue("TESTEX");
		
		//order.setStock("LPEI");
		//order.setAccount("MST92145671");
		//order.setVenue("LOBHEX");
		
		order.setDirection("buy");
		order.setQty(10);
		order.setOrderType("limit");
		order.setPrice(10);
		stockfighterRestAdapter.placeNewOrder (order);
	}

	@Test
	public void testQuoteForStock() 
	{
		stockfighterRestAdapter.quoteForAStock("TESTEX","FOOBAR");
	}

	@Test
	public void testOrderStatus() 
	{
		Order order = new Order();
		order.setStock("FOOBAR");
		order.setAccount("EXB123456");		
		order.setVenue("TESTEX");
		
		//order.setStock("LPEI");
		//order.setAccount("MST92145671");
		//order.setVenue("LOBHEX");
		
		order.setDirection("buy");
		order.setQty(10);
		order.setOrderType("limit");
		order.setPrice(10);
		OrderResult orderResult = stockfighterRestAdapter.placeNewOrder (order);
		stockfighterRestAdapter.retrieveExistingOrder(order.getVenue(), order.getStock(), orderResult.getId());
	}
	
	@Test
	public void testCancelOrder() 
	{
		Order order = new Order();
		order.setStock("FOOBAR");
		order.setAccount("EXB123456");		
		order.setVenue("TESTEX");
		
		//order.setStock("LPEI");
		//order.setAccount("MST92145671");
		//order.setVenue("LOBHEX");
		
		order.setDirection("buy");
		order.setQty(10);
		order.setOrderType("limit");
		order.setPrice(10);
		OrderResult orderResult = stockfighterRestAdapter.placeNewOrder (order);
		orderResult = stockfighterRestAdapter.cancelExistingOrder(order.getVenue(), order.getStock(), orderResult.getId());
		Assert.assertFalse(orderResult.isOpen());
	}
	@Test
	public void testStatusForAllOrders()
	{
		stockfighterRestAdapter.statusForAllOrders("TESTEX", "EXB123456");
	}
	@Test
	public void testStatusForAllOrdersInAstock()
	{
		stockfighterRestAdapter.statusForAllOrdersInAStock("TESTEX", "EXB123456","FOOBAR");
	}

}
