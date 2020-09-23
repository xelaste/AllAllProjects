package domain;

import java.util.Date;

public class Order extends BasePOJO 
{
	
	private String account;
	
	private Direction direction;
	
	private OrderType orderType;
	
	private String venue;
	
	private String stock;
	
	private int qty;
	private int price;

	private boolean ok;
	public boolean isOk() {
		return ok;
	}
	public void setOk(boolean ok) 
	{
		this.ok = ok;
	}
	
	public String getAccount() {
		return account;
	}

	public void setAccount(String account) {
		this.account = account;
	}

	public String getDirection() 
	{
		if (direction != null )
			return direction.name();
		else
			return null;
	}

	public void setDirection(String direction) 
	{
		this.direction =Direction.valueOf(direction);
	}

	public String getOrderType() {
		
		if (orderType != null )
		{	
			String s = orderType.name().replace("_", "-");
			return s;
		}
		else
		{
			return null;
		}
	}

	public void setOrderType(String orderType) 
	{
		String s = orderType.replace("-", "_");
		this.orderType = OrderType.valueOf(s);
	}

	public String getVenue() {
		return venue;
	}

	public void setVenue(String venue) {
		this.venue = venue;
	}

	public String getStock() {
		return stock;
	}

	public void setStock(String stock) {
		this.stock = stock;
	}

	public int getQty() {
		return qty;
	}

	public void setQty(int qty) {
		this.qty = qty;
	}

	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}

	public static enum Direction
	{
		buy,sell
	}

	public static enum OrderType
	{
		limit,market,fill_or_kill,immediate_or_cancel;
	}

}
