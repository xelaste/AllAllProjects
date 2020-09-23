package services;

import  org.junit.Assert;

import org.junit.Test;

import domain.ImageData;

public class ImageMD5CalulatorServiceTest {

	@Test
	public void testExecute() 
	{
		ImageMD5CalulatorService service = new ImageMD5CalulatorService();
		ImageData data = new ImageData();
		data.setUrl("http://carbl.com/im/2013/07/Suzuki-Swift-5d-600x324.jpg");
		data.setFilepath("./temp/" + System.currentTimeMillis()+ ".jpg");
		service.setData(data);
		service.execute();
		System.out.println(data.getMd5());
		Assert.assertNotNull(data.getMd5());
	}

}
