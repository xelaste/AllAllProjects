package services;
import java.awt.Graphics2D;
import java.awt.image.BufferedImage;
import java.io.File;
import javax.imageio.ImageIO;
public class ImageResizeService extends ServiceBase 
{
	public static final int IMG_WIDTH=200;
	public static final int IMG_HEIGHT=200;
	@Override
	public void execute() 
	{
		_logger.info("Resize image ...");
		String filepath=getData().getFilepath();
		_logger.info("path=" + filepath);
		try  
		{
			String extension = "jpg";
			int i = filepath.lastIndexOf('.');
			if (i > 0) {
			    extension = filepath.substring(i+1);
			}

			BufferedImage originalImage = ImageIO.read(new File(filepath));
			int type = originalImage.getType() == 0? BufferedImage.TYPE_INT_ARGB : originalImage.getType();
			BufferedImage resizeImageJpg = resizeImage(originalImage, type);
			ImageIO.write(resizeImageJpg, extension, new File(filepath));	
		}
		catch (Exception e)
		{
			_logger.fatal("Fail to resize " + filepath);
			_logger.fatal(e,e);
			throw new RuntimeException(e);
		}
	}

	private static BufferedImage resizeImage(BufferedImage originalImage, int type)
	{
		BufferedImage resizedImage = new BufferedImage(IMG_WIDTH, IMG_HEIGHT, type);
		Graphics2D g = resizedImage.createGraphics();
		g.drawImage(originalImage, 0, 0, IMG_WIDTH, IMG_HEIGHT, null);
		g.dispose();
		return resizedImage;
	}	
}
