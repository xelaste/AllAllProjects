package domain;

import java.util.Date;

public class Quote extends BasePOJO 
{
/**
 * {
    "ok": true,
    "symbol": "FAC",
    "venue": "OGEX",
    "bid": 5100, // best price currently bid for the stock
    "ask": 5125, // best price currently offered for the stock
    "bidSize": 392, // aggregate size of all orders at the best bid
    "askSize": 711, // aggregate size of all orders at the best ask
    "bidDepth": 2748, // aggregate size of *all bids*
    "askDepth": 2237, // aggregate size of *all asks*
    "last": 5125, // price of last trade
    "lastSize": 52, // quantity of last trade
    "lastTrade": "2015-07-13T05:38:17.33640392Z", // timestamp of last trade
    "quoteTime": "2015-07-13T05:38:17.33640392Z" // ts we last updated quote at (server-side)
}
 * 
 */

	private boolean ok;
	private String venue;
	private String symbol;
	private  int bid;
	private  int ask;
	private int bidSize;
	private int askSize;
	private int bidDepth;
	private int askDepth;
	private int last;
	private int lastSize;
	private Date lastTrade;
	private Date quoteTime;
	public boolean isOk() {
		return ok;
	}
	public void setOk(boolean ok) {
		this.ok = ok;
	}
	public String getSymbol() {
		return symbol;
	}
	public void setSymbol(String symbol) {
		this.symbol = symbol;
	}
	public int getBid() {
		return bid;
	}
	public void setBid(int bid) {
		this.bid = bid;
	}
	public int getAsk() {
		return ask;
	}
	public void setAsk(int ask) {
		this.ask = ask;
	}
	public int getBidSize() {
		return bidSize;
	}
	public void setBidSize(int bidSize) {
		this.bidSize = bidSize;
	}
	public int getAskSize() {
		return askSize;
	}
	public void setAskSize(int askSize) {
		this.askSize = askSize;
	}
	public int getBidDepth() {
		return bidDepth;
	}
	public void setBidDepth(int bidDepth) {
		this.bidDepth = bidDepth;
	}
	public int getAskDepth() {
		return askDepth;
	}
	public void setAskDepth(int askDepth) {
		this.askDepth = askDepth;
	}
	public int getLast() {
		return last;
	}
	public void setLast(int last) {
		this.last = last;
	}
	public int getLastSize() {
		return lastSize;
	}
	public void setLastSize(int lastSize) {
		this.lastSize = lastSize;
	}
	public Date getLastTrade() {
		return lastTrade;
	}
	public void setLastTrade(Date lastTrade) {
		this.lastTrade = lastTrade;
	}
	public Date getQuoteTime() {
		return quoteTime;
	}
	public void setQuoteTime(Date quoteTime) {
		this.quoteTime = quoteTime;
	}
	public String getVenue() {
		return venue;
	}
	public void setVenue(String venue) {
		this.venue = venue;
	}

	
}
