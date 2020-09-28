package domain;

public class HeartBeatResult extends BasePOJO
{
	private boolean ok;
	public boolean isOk() {
		return ok;
	}
	public void setOk(boolean ok) 
	{
		this.ok = ok;
	}
	private String error;
	
	public String getError() 
	{
		return error;
	}
	public void setError(String error) 
	{
		this.error = error;
	}
	
	
}
