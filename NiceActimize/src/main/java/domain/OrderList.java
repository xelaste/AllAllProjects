package domain;

public class OrderList extends BasePOJO 
{
	private boolean ok;
	private String venue;
	private OrderResult[] orders;
	public boolean isOk() {
		return ok;
	}
	public void setOk(boolean ok) {
		this.ok = ok;
	}
	public String getVenue() {
		return venue;
	}
	public void setVenue(String venue) {
		this.venue = venue;
	}
	public OrderResult[] getOrders() {
		return orders;
	}
	public void setOrders(OrderResult[] orders) {
		this.orders = orders;
	}
	
}
