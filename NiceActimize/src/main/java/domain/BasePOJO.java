package domain;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.ObjectWriter;

public class BasePOJO 
{

	@Override
	public String toString() 
	{
		String s = super.toString();
		ObjectWriter ow = new ObjectMapper().writerWithDefaultPrettyPrinter();
		
		try {
			return s + ow.writeValueAsString(this);
		} catch (JsonProcessingException e) 
		{
			e.printStackTrace();
			return s;
		}
	}
	
	
	
}
