package levels;

import java.util.Random;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.atomic.AtomicInteger;

import org.apache.log4j.Logger;
import adapters.StockfighterRestAdapter;
import domain.HeartBeatResult;
import domain.Order;
import domain.OrderBook;
import domain.OrderFullFillmentItem;
import domain.OrderResult;
import domain.Order.Direction;
import domain.Order.OrderType;
import domain.Quote;
import domain.VenueHeartBeatResult;
import util.Confugurations;

public class Solution 
{
	private Logger logger = Logger.getLogger(getClass());
	private StockfighterRestAdapter adapter = new StockfighterRestAdapter();
	private String venue=Confugurations.getInstance().getProperty("level1.venue");
	private String account=Confugurations.getInstance().getProperty("level1.account");
	private String stock=Confugurations.getInstance().getProperty("level1.symbol");
	private AtomicInteger numberOfAssets=new AtomicInteger(0);
	private AtomicInteger spentMoney=new AtomicInteger(0);
	private AtomicInteger balance=new AtomicInteger(0);
	
	public void firstStepsLevel1()
	{
		logger.debug("Enter firstStepsLevel1");
		VenueHeartBeatResult heartBeat = adapter.venueHeartbeat(venue);
		if (heartBeat.isOk())
		{	
			Quote qoute = adapter.quoteForAStock(venue,stock);
			logger.debug("Exists "  + qoute);
			int goal=100;
			Order order = new Order();
			order.setAccount(account);
			order.setVenue(venue);
			order.setStock(stock);
			order.setDirection(Order.Direction.buy.name());
			order.setOrderType(OrderType.market.name());
			order.setQty(goal);
			OrderResult orderResult = adapter.placeNewOrder(order);
			logger.debug("Placed order "  + orderResult);
		}	
		logger.debug("Exit firstStepsLevel1");
	}

	public void chokABlockLevel2()
	{
		logger.debug("Enter chokABlockLevel2");
		HeartBeatResult heartBeatResult = adapter.heartbeat();
		logger.debug(heartBeatResult);
		final int goal = 100000;
		int targetPrice=0;
		OrderBook book = adapter.orderbookForAStock(venue, stock);
		logger.debug( book );
		ExecutorService executorPlaceOrder = Executors.newFixedThreadPool(20);
		while (targetPrice == 0 )
		{	
			Quote qoute = adapter.quoteForAStock(venue,stock);
			if (qoute.getBid() > 0 )
			{	
				targetPrice = qoute.getBid();
				break;
			}	
		}	
		int orderCount=0;
		while (numberOfAssets.get() < goal)
		{
			
			orderCount++;
			// teke some rest
			if (orderCount % 100 ==0)
			{
				try 
				{
					Thread.sleep(new Random().nextInt(5000));
				} 
				catch (InterruptedException e) 
				{
					logger.debug(e);
				}
			}
			if (orderCount % 600 ==0)
			{
				try 
				{
					Thread.sleep(new Random().nextInt(6000));
				} 
				catch (InterruptedException e) 
				{
					logger.debug(e);
				}
			}
			Quote qoute = adapter.quoteForAStock(venue,stock);
			int quoteQty = 0;
			if ( qoute.getBid() > 0 && qoute.getBid()<targetPrice )
			{	
				targetPrice = qoute.getBid();
			}
			quoteQty = qoute.getBidSize();
			Order order = new Order();
			order.setAccount(account);
			order.setVenue(venue);
			order.setStock(stock);
			// sell every 100 orders
			if (orderCount % 200==0 )
			{	
				order.setDirection(Order.Direction.sell.name());
			}
			else
			{
				order.setDirection(Order.Direction.buy.name());
			}
			int qty = 20000 * ((new Random().nextInt(101)%100==0)?1:0) + Math.abs(new Random().nextInt((Math.min(500, quoteQty)) + 1) ) + 1;
			if ( qty <= 200 )
			{
				order.setOrderType(OrderType.market.name());
			}
			else
			{
				order.setOrderType(OrderType.immediate_or_cancel.name());
			}
			order.setQty(qty);

			order.setPrice(targetPrice + (new Random().nextInt(500))) ;

			executorPlaceOrder.submit(new OrderCreateService(order,numberOfAssets,spentMoney,balance));
			logger.debug("************ Total = " + numberOfAssets.get() + "************************");
		}
		executorPlaceOrder.shutdown();
		logger.debug("Exit chokABlockLevel2");
	}
	
	public void sellSideLevel3()
	{
	
		logger.debug("Enter chokABlockLevel3");
		HeartBeatResult heartBeatResult = adapter.heartbeat();
		logger.debug(heartBeatResult);
		final int goalProfit = 10000;
		final int maxOrderSize = 1000;
		int targetAskPrice=0;
		int targetBidPrice=0;
		ExecutorService executorPlaceOrder = Executors.newFixedThreadPool(20);
		while (targetBidPrice == 0 && targetAskPrice==0)
		{	
			Quote qoute = adapter.quoteForAStock(venue,stock);
			if (qoute.getBid() > 0 )
			{	
				targetBidPrice = qoute.getBid();
				break;
			}	
			if (qoute.getAsk() > 0 )
			{	
				targetAskPrice = qoute.getAsk();
				break;
			}	
		}	
		while ( balance.get() - spentMoney.get() < goalProfit )
		{
			Quote qoute = adapter.quoteForAStock(venue,stock);
			int quoteQty = 0;
			int askQty = 0;
			if ( qoute.getBid() > 0 && qoute.getBid()<targetBidPrice )
			{	
				targetBidPrice = qoute.getBid();
				
			}
			if ( qoute.getAsk() > 0 && qoute.getAsk()<targetAskPrice )
			{	
				targetBidPrice = qoute.getAsk();
			}
			quoteQty=qoute.getBidSize();
			askQty = qoute.getAskSize();
			if (numberOfAssets.get() > 1000 )
			{	
				Order order = new Order();
				int buffer = numberOfAssets.get();
				order.setAccount(account);
				order.setVenue(venue);
				order.setStock(stock);
				order.setQty(Math.min(maxOrderSize, buffer/2));
				order.setDirection(Order.Direction.sell.name());
				order.setOrderType(OrderType.market.name());
				order.setPrice(targetAskPrice - (new Random().nextInt(200))) ;
				executorPlaceOrder.submit(new OrderCreateService(order,numberOfAssets,spentMoney,balance));
			}
			else
			{
				quoteQty = qoute.getBidSize();
				Order order = new Order();
				order.setAccount(account);
				order.setVenue(venue);
				order.setStock(stock);
				order.setDirection(Order.Direction.buy.name());
				int qty = Math.abs(new Random().nextInt((Math.min(500, quoteQty)) + 1) ) + 1;
				order.setOrderType(OrderType.immediate_or_cancel.name());
				order.setQty(qty);
				order.setPrice(targetBidPrice + (new Random().nextInt(500))) ;
				executorPlaceOrder.submit(new OrderCreateService(order,numberOfAssets,spentMoney,balance));
			}
		}	
		executorPlaceOrder.shutdown();
		logger.debug("Exit sellSideLevel3");
	}
	public static class OrderCreateService implements Callable<OrderResult>
	{
		private Logger logger = Logger.getLogger(getClass());
		private Order order = null;
		private AtomicInteger numberOfAssets=null;
		private AtomicInteger spentMoney=null;
		private AtomicInteger balance=null;

		private StockfighterRestAdapter adapter = new StockfighterRestAdapter();
		public OrderCreateService(Order order,AtomicInteger numberOfAssets,AtomicInteger spentMoney,AtomicInteger balance) 
		{
			super();
			this.order = order;
			this.numberOfAssets=numberOfAssets;
			this.balance=balance;
			this.spentMoney=spentMoney;
		}
		@Override
		public OrderResult call() throws Exception 
		{
			OrderResult result=null;
			int days=0;
			do
			{	
				result = adapter.placeNewOrder(order);
				if (new Random().nextInt(6)%5 == 1 )
				{
					adapter.cancelExistingOrder(result.getVenue() , result.getStock(), result.getId());
				}
				Thread.sleep(200);
				if (days > 5 )
				{	
					logger.debug("Days " + days);
				}	
				days++;
				order.setPrice(Math.abs(order.getPrice() + new Random().nextInt(200)));
				result = adapter.retrieveExistingOrder(order.getVenue(), order.getStock(), result.getId());
			}	
			while (result.getFills().length==0 && !result.getOrderType().equals(Order.OrderType.market.name()) && days < 20 );	
			if (result.isOpen())
			{
				adapter.cancelExistingOrder(result.getVenue() , result.getStock(), result.getId());
				Thread.sleep(200);
			}
			result = adapter.retrieveExistingOrder(order.getVenue(), order.getStock(), result.getId());
			int totalfilled = result.getTotalFilled();
			boolean sell=false;
			if (order.getDirection().equals(Direction.sell.name()))
			{
				totalfilled = (-1) * totalfilled;
				sell=true;
			}
			numberOfAssets.addAndGet(totalfilled);
			OrderFullFillmentItem[] items = result.getFills();
			for (int i = 0; i < items.length; i++) 
			{
				int sum = items[i].getPrice() * items[i].getQty();
				if (sell)
				{
					balance.addAndGet(sum);
				}
				else
				{
					spentMoney.addAndGet(sum);
				}
			}
			logger.debug("****** Expenses is " + ( spentMoney.get() ) );
			logger.debug("****** balance is " + ( balance.get() ) );
			logger.debug("****** profit is " + ( balance.get() - spentMoney.get() ) );
			return result;
		}
	}
}
