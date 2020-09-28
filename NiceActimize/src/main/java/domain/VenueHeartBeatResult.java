package domain;

public class VenueHeartBeatResult extends BasePOJO
{
	private boolean ok;
	private String venue;
	public boolean isOk() {
		return ok;
	}
	public void setOk(boolean ok) 
	{
		this.ok = ok;
	}
	public String getVenue() 
	{
		return venue;
	}
	public void setVenue(String venue) 
	{
		this.venue = venue;
	}
	
}
