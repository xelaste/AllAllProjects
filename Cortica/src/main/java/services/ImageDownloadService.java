package services;
import java.io.FileOutputStream;
import java.net.URL;
import java.net.URLConnection;
import java.nio.channels.Channels;
import java.nio.channels.ReadableByteChannel;
public class ImageDownloadService extends ServiceBase 
{
	@Override
	public void execute() 
	{
		_logger.info("Download image ...");
		String strUrl = getData().getUrl();
		String filepath=getData().getFilepath();
		_logger.info("From url=" + strUrl + " to " + filepath);
		URLConnection website = buildURLFromString(strUrl);
		try (ReadableByteChannel rbc = Channels.newChannel(website.getInputStream());
				FileOutputStream fos = new FileOutputStream(filepath);) 
		{
			fos.getChannel().transferFrom(rbc, 0, Long.MAX_VALUE);
			_logger.info( "# saved file " + filepath + " from url " + strUrl );
		}
		catch (Exception e)
		{
			_logger.fatal("Fail to save " + filepath);
			_logger.fatal(e,e);
			throw new RuntimeException(e);
		}
	}
	private URLConnection buildURLFromString(String strUrl)
	{
		URL website=null;
		URLConnection con=null;
		try 
		{
			website = new URL(strUrl);
			con = website.openConnection();
			con.setConnectTimeout(3000);
			con.setReadTimeout(3000);
		} 
		catch (Exception e) 
		{
			_logger.fatal(e,e);
			throw new RuntimeException(e);
		}
		return con;
	}
}
