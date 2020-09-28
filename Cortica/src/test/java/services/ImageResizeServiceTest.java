package services;

import org.junit.Test;

import domain.ImageData;

public class ImageResizeServiceTest {

	@Test
	public void testExecute() 
	{
		ImageDownloadService downloadservice = new ImageDownloadService();
		ImageResizeService service = new ImageResizeService();
		ImageData data = new ImageData();
		data.setUrl("http://carbl.com/im/2013/07/Suzuki-Swift-5d-600x324.jpg");
		data.setFilepath("./temp/" + System.currentTimeMillis()+ ".jpg");
		downloadservice.setData(data);
		downloadservice.execute();
		service.setData(data);
		service.execute();
	}

}
