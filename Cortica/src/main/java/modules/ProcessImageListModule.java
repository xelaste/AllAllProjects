package modules;

import java.util.concurrent.atomic.AtomicBoolean;

import org.apache.log4j.Logger;

public abstract class ProcessImageListModule
{
	protected final Logger _logger = Logger.getLogger(getClass());
	private AtomicBoolean errorExists=new AtomicBoolean(false);
	private ImageProcessModule imageProcessModule = new ImageProcessModuleImpl();
	
	
	public ImageProcessModule getImageProcessModule() 
	{
		return imageProcessModule;
	}
	public void setImageProcessModule(ImageProcessModule imageProcessModule) {
		this.imageProcessModule = imageProcessModule;
	}
	public boolean getErrorExists() 
	{
		return errorExists.get();
	}
	public void setErrorExists(boolean errorExists) 
	{
		this.errorExists.set(errorExists);
	}
	public abstract void execute ();

}
