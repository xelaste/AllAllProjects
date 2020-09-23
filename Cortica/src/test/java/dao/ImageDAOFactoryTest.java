package dao;

import org.junit.Assert;

import org.junit.Test;

public class ImageDAOFactoryTest {

	@Test
	public void testGetInstance() 
	{
		ImageDAOFactory factory = ImageDAOFactory.getInstance();
		Assert.assertNotNull(factory);
	}

	@Test
	public void testCreateDAO() 
	{
		ImageDAOFactory factory = ImageDAOFactory.getInstance();
		ImageDAO dao = factory.createDAO(ImageDAOFactory.DBTYPE.HSQLDB);
		Assert.assertNotNull(dao);
	}

}
