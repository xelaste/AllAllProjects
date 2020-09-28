package domain;

import java.util.Date;

public class OrderFullFillmentItem extends BasePOJO 
{
	int price;
	int qty;
	Date ts;
	
	public int getPrice() 
	{
		return price;
	}
	public void setPrice(int price) 
	{
		this.price = price;
	}
	public int getQty() {
		return qty;
	}
	public void setQty(int qty) 
	{
		this.qty = qty;
	}
	public Date getTs() 
	{
		return ts;
	}
	public void setTs(Date ts) 
	{
		this.ts = ts;
	}
}
