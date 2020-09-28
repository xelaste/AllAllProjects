package services;

import org.apache.log4j.Logger;

import domain.ImageData;

public abstract class ServiceBase 
{
	protected final Logger _logger = Logger.getLogger(getClass());
	private ImageData data;

	abstract public void execute();
	
	public ImageData getData() 
	{
		return data;
	}

	public void setData(ImageData data)
	{
		this.data = data;
	}
	
}
