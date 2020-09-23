package services;

import org.junit.Assert;

import org.junit.Test;

import dao.ImageDAO;
import dao.ImageDAOFactory;
import domain.ImageData;

public class ImagePersistsServiceTest {

	@Test
	public void testExecute() 
	{
		ImageMD5CalulatorService service = new ImageMD5CalulatorService();
		ImageData data = new ImageData();
		data.setUrl("http://carbl.com/im/2013/07/Suzuki-Swift-5d-600x324.jpg");
		data.setFilepath("./temp/" + System.currentTimeMillis()+ ".jpg");
		service.setData(data);
		service.execute();
		ImagePersistsService persistsService = new ImagePersistsService();
		persistsService.setData(data);
		persistsService.execute();
		ImageDAO dao = ImageDAOFactory.getInstance().createDAO(ImageDAOFactory.DBTYPE.HSQLDB);
		ImageData found = dao.retrieveImageByUrl( data.getUrl() );
		Assert.assertTrue(found != null );
		Assert.assertTrue(data.getMd5().equals(found.getMd5()));
	}
}
