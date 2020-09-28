package adapters;

import java.io.IOException;
import javax.ws.rs.client.ClientRequestContext;
import javax.ws.rs.client.ClientRequestFilter;

import util.Confugurations;
public class SecurityRequestFilter implements ClientRequestFilter 
{

	@Override
	public void filter(final ClientRequestContext rc) throws IOException 
	{
		rc.getHeaders().add("X-Starfighter-Authorization",Confugurations.getInstance().getProperty("X-Starfighter-Authorization"));
	}
}
