package adapters;

import javax.json.stream.JsonGenerator;
import javax.ws.rs.client.Client;
import javax.ws.rs.client.ClientBuilder;
import javax.ws.rs.client.Entity;
import javax.ws.rs.client.WebTarget;
import javax.ws.rs.core.MediaType;
import javax.ws.rs.core.Response;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.glassfish.jersey.client.ClientConfig;
import org.glassfish.jersey.jackson.JacksonFeature;
import org.glassfish.jersey.jsonp.JsonProcessingFeature;
import domain.HeartBeatResult;
import domain.Order;
import domain.OrderBook;
import domain.OrderList;
import domain.OrderResult;
import domain.Quote;
import domain.Stocks;
import domain.VenueHeartBeatResult;
import util.Confugurations;

public class StockfighterRestAdapter 
{
	private Logger logger = Logger.getLogger(getClass());
	private WebTarget target;
	public StockfighterRestAdapter() 
	{
		ClientConfig clientConfig = new ClientConfig();
		clientConfig.register(new JacksonFeature())
		.register(JsonProcessingFeature.class)
		.register(SecurityRequestFilter.class)
        .property(JsonGenerator.PRETTY_PRINTING, true);
		Client client = ClientBuilder.newClient(clientConfig);
		target = client.target(Confugurations.getInstance().getProperty("app.end.point"));
	}
	
	public HeartBeatResult heartbeat ()
	{
		return issueGetRequest ("/heartbeat",HeartBeatResult.class);
	}
	
	public VenueHeartBeatResult venueHeartbeat (String venue)
	{
		return issueGetRequest ("/venues/"+venue+"/heartbeat",VenueHeartBeatResult.class);
	}
	
	public Stocks venueStocks (String venue)
	{
		return issueGetRequest ("/venues/"+venue+"/stocks",Stocks.class);
	}
	
	public OrderBook orderbookForAStock (String venue,String stock)
	{
		return issueGetRequest ("/venues/"+venue+"/stocks/"+stock,OrderBook.class);
	}
	
	public OrderResult placeNewOrder (Order order)
	{
		Response response = target.path("/venues/"+order.getVenue()+"/stocks/"+order.getStock() + "/orders")
				.request(MediaType.APPLICATION_JSON_TYPE)
				.post(Entity.entity(order,MediaType.APPLICATION_JSON_TYPE));
		if (response.getStatus() == 200) 
		{	
			OrderResult result=response.readEntity(OrderResult.class);
			logger.log(Level.DEBUG, "Order Result is " + result);
			return result;
		}
		else
		{
			logger.log(Level.DEBUG, "Place new order Error code=" + response.getStatus());
			throw new RuntimeException("Place new order Error code=" + response.getStatus());
		}
	}
	public Quote quoteForAStock (String venue,String stock)
	{
		return issueGetRequest ("/venues/"+venue+"/stocks/"+stock+"/quote",Quote.class);
	}

	public OrderResult retrieveExistingOrder (String venue,String stock,String id)
	{
		return issueGetRequest ("/venues/"+venue+"/stocks/"+stock+"/orders/" + id,OrderResult.class);
	}

	public OrderResult cancelExistingOrder (String venue,String stock,String id)
	{
		OrderResult order=null;
		Response response = target.path("/venues/"+venue+"/stocks/"+stock+"/orders/" + id ).request(MediaType.APPLICATION_JSON_TYPE).delete();
		if (response.getStatus() == 200) 
		{	
			order=response.readEntity(OrderResult.class);
			logger.log(Level.DEBUG, "Status For Existing Order is " + order);
			return order;
		}
		else
		{
			logger.log(Level.DEBUG, "Status For Existing Order  error code=" + response.getStatus());
			throw new RuntimeException("Status For Existing Order Error code=" + response.getStatus());
		}
	}
	
	public OrderList statusForAllOrdersInAStock(String venue,String account,String stock)
	{
		String path = "/venues/"+venue+"/accounts/"+account + "/stocks/"+stock+ "/orders";
		return issueGetRequest (path,OrderList.class);
	}
	
	public OrderList statusForAllOrders(String venue,String account)
	{
		String path="/venues/"+venue+"/accounts/"+account + "/orders";
		return issueGetRequest (path,OrderList.class);
	}
	protected <T> T issueGetRequest (String path,Class<T> clazz)
	{
		logger.log(Level.DEBUG, "Enter to issueGetRequest with path" + path);
		T t=null;
		Response response = target.path(path).request(MediaType.APPLICATION_JSON_TYPE).get();
		if (response.getStatus() == 200) 
		{	
			t=response.readEntity(clazz);
			logger.log(Level.DEBUG, "Request result is " + t);
			logger.log(Level.DEBUG, "Exit from issueGetRequest");
			return t;
		}
		else
		{
			logger.log(Level.ERROR, "Request failed with error code=" + response.getStatus());
			throw new RuntimeException("Request failed with error code=" + response.getStatus());
		}
			
	}
}
