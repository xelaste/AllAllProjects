package domain;

import java.util.Date;

public class OrderResult extends Order 
{
	private Date ts;
	
	private String symbol;
	
	private String id;
	
	private int originalQty;

	private int totalFilled;
	private boolean open;
	private String error;
	
	private OrderFullFillmentItem fills[];
	public int getTotalFilled() {
		return totalFilled;
	}
	public void setTotalFilled(int totalFilled) {
		this.totalFilled = totalFilled;
	}
	public boolean isOpen() {
		return open;
	}
	public void setOpen(boolean open) {
		this.open = open;
	}
	public String getError() {
		return error;
	}
	public void setError(String error) {
		this.error = error;
	}
	public Date getTs() {
		return ts;
	}
	public void setTs(Date ts) {
		this.ts = ts;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) 
	{
		this.id = id;
	}
	public int getOriginalQty() 
	{
		return originalQty;
	}
	public void setOriginalQty(int originalQty) 
	{
		this.originalQty = originalQty;
	}
	public OrderFullFillmentItem[] getFills() 
	{
		return fills;
	}
	public void setFills(OrderFullFillmentItem[] fills) 
	{
		this.fills = fills;
	}

	public String getSymbol() 
	{
		return symbol;
	}
	public void setSymbol(String symbol) 
	{
		this.symbol = symbol;
	}

	
}
