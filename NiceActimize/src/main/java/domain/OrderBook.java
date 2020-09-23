package domain;

import java.util.Date;

public class OrderBook extends BasePOJO 
{
	private boolean ok;
	private Date ts;
	private String venue;
	private String symbol;
	private BookItem[] bids;
	private BookItem[] asks;
	
	public boolean isOk() {
		return ok;
	}
	public void setOk(boolean ok) 
	{
		this.ok = ok;
	}
	public Date getTs() 
	{
		return ts;
	}
	public void setTs(Date ts) 
	{
		this.ts = ts;
	}
	public BookItem[] getBids() {
		return bids;
	}
	public void setBids(BookItem[] bids) {
		this.bids = bids;
	}
	public BookItem[] getAsks() {
		return asks;
	}
	public void setAsks(BookItem[] asks) {
		this.asks = asks;
	}
	public String getVenue() {
		return venue;
	}
	public void setVenue(String venue) {
		this.venue = venue;
	}
	public String getSymbol() {
		return symbol;
	}
	public void setSymbol(String symbol) {
		this.symbol = symbol;
	}
	
}
