package services;

import java.security.MessageDigest;

import domain.ImageData;

public class ImageMD5CalulatorService extends ServiceBase 
{
	@Override
	public void execute() 
	{
		_logger.info("Calculate MD5 ...");
		String strUrl = getData().getUrl();
		try 
		{
			MessageDigest md = MessageDigest.getInstance("MD5");
			byte digest[] = md.digest(strUrl.getBytes());
			ImageData data = getData();
			data.setMd5( new String(digest) );
		} 
		catch (Exception e) 
		{
			_logger.fatal(e,e);
			throw new RuntimeException(e);
		}
	}
}
