package domain;

import com.fasterxml.jackson.annotation.JsonProperty;

public class BookItem 
{
	int price;
	int qty;
	boolean isBuy;
	public int getPrice() {
		return price;
	}
	public void setPrice(int price) {
		this.price = price;
	}
	public int getQty() {
		return qty;
	}
	public void setQty(int qty) {
		this.qty = qty;
	}
	public boolean isBuy() {
		return isBuy;
	}
	@JsonProperty("isBuy")
	public void setBuy(boolean isBuy) {
		this.isBuy = isBuy;
	}
	
}
