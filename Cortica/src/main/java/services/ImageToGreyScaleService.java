package services;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;

import javax.imageio.ImageIO;
public class ImageToGreyScaleService extends ServiceBase 
{
	@Override
	public void execute() 
	{
		_logger.info("Redraw image ...");
		String filepath=getData().getFilepath();
		_logger.info("path=" + filepath);
		try  
		{
			String extension = "jpg";
			int i = filepath.lastIndexOf('.');
			if (i > 0) 
			{
			    extension = filepath.substring(i+1);
			}
			BufferedImage originalImage = ImageIO.read(new File(filepath));
			int type = BufferedImage.TYPE_BYTE_GRAY;
			BufferedImage resizeImageJpg = resizeImage(originalImage, type);
			ImageIO.write(resizeImageJpg, extension, new File(filepath));
		}
		catch (Exception e)
		{
			_logger.fatal("Fail to redraw " + filepath);
			_logger.fatal(e,e);
			throw new RuntimeException(e);
		}
	}

	private static BufferedImage resizeImage(BufferedImage originalImage, int type)
	{
		BufferedImage resizedImage = new BufferedImage(originalImage.getWidth(), originalImage.getHeight(), type);
		Graphics2D g = resizedImage.createGraphics();
		g.drawImage(originalImage, 0, 0, null );
		g.dispose();
		return resizedImage;
	}	
}
