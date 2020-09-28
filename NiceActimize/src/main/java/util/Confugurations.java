package util;

import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import org.apache.log4j.Logger;

public class Confugurations 
{
	private Logger logger = Logger.getLogger(getClass());
	private static Confugurations instance= new Confugurations();
	public static Confugurations getInstance()
	{
		return instance;
	}
	private Properties properties = new Properties();
	public Confugurations() 
	{
		super();
		try (final InputStream stream =	this.getClass().getResourceAsStream("/config.properties")) 
		{
			properties.load(stream);
		} 
		catch (IOException e) 
		{
			logger.error(e,e);
			throw new RuntimeException(e);
		}
	}
	public String getProperty(String key) 
	{
		return properties.getProperty(key);
	}
	public String getProperty(String key, String defaultValue) {
		return properties.getProperty(key, defaultValue);
	}
	
	
	
}
