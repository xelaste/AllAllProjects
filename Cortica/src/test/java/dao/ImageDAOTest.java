package dao;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

import domain.ImageData;

public class ImageDAOTest {

	ImageDAO dao = null;
	@Before
	public void setup()
	{
		dao = ImageDAOFactory.getInstance().createDAO(ImageDAOFactory.DBTYPE.HSQLDB);
	}
	@Test
	public void testInit() 
	{
		dao.init();
	}

	@Test
	public void testRetrieveImageByUrlNotExists() 
	{
		ImageData data = dao.retrieveImageByUrl(String.valueOf(System.currentTimeMillis()));
		Assert.assertNull(data);
	}

	@Test
	public void testPersistImage() 
	{
		ImageData data = new ImageData();
		data.setUrl("http://xxxx.png");
		data.setFilepath("c:\\xxx.png");
		data.setMd5("md5");
		dao.persistImage(data);
	}
	@Test
	public void testRetrieveImageByUrlExists() 
	{
		ImageData data = new ImageData();
		data.setUrl("http://yyyy.png");
		data.setFilepath("c:\\yy.png");
		data.setMd5("md5");
		dao.persistImage(data);
		ImageData found = dao.retrieveImageByUrl(data.getUrl());
		Assert.assertNotNull(found);
	}

}
