package services;

import java.io.File;
import  org.junit.Assert;
import org.junit.Test;

import domain.ImageData;

public class ImageDownloadServiceTest {

	@Test
	public void testExecute() 
	{
		ImageData data = new ImageData();
		data.setUrl("http://carbl.com/im/2013/07/Suzuki-Swift-5d-600x324.jpg");
		data.setFilepath("./temp/" + System.currentTimeMillis()+ ".jpg");
		ImageDownloadService service = new ImageDownloadService();
		service.setData(data);
		service.execute();
		File file = new File(data.getFilepath());
		Assert.assertTrue(file.exists());
		Assert.assertTrue(file.length() > 0); 
	}

}
