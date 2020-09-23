package modules;

import java.io.File;
import java.util.concurrent.atomic.AtomicLong;

import org.apache.log4j.Logger;

import domain.ImageData;
import services.ServiceBase;

public abstract class ImageProcessModule 
{
	protected final Logger _logger = Logger.getLogger(getClass());
	private AtomicLong counter =new AtomicLong(System.currentTimeMillis());
	protected abstract ServiceBase[] generateProcessSteps();
	
	public boolean processImage(final String imageUrl)
	{
		_logger.info("Start process image " + imageUrl);
		ServiceBase[] steps = generateProcessSteps();
		ImageData data = new ImageData();
		data.setUrl(imageUrl);
		String extension = "jpg";
		int i = imageUrl.lastIndexOf('.');
		if (i > 0) {
		    extension = imageUrl.substring(i+1);
		}
		Long value = counter.getAndIncrement();
		String imageFolder = System.getProperty("user.dir") +"/images";
		File file = new File(imageFolder);
		file.mkdirs();
		String filepath = imageFolder+"/" + value + "." + extension;
		_logger.info("* filepath=" + filepath );
		data.setFilepath(filepath);
		for (int j = 0; j < steps.length; j++) 
		{
			try
			{
				_logger.info(data);
				steps[j].setData(data);
				steps[j].execute();
			}
			catch (Exception e)
			{
				_logger.fatal(e,e);
				_logger.info("Fail to process image " + imageUrl);
				return false;
			}
		}
		_logger.info("Completed process image " + imageUrl);
		return true;
	}
}
