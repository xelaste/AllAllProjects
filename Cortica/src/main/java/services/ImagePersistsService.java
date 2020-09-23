package services;

import dao.ImageDAO;
import dao.ImageDAOFactory;

public class ImagePersistsService extends ServiceBase 
{
	@Override
	public void execute() 
	{
		_logger.info("Persists image ...");
		ImageDAO dao = ImageDAOFactory.getInstance().createDAO(ImageDAOFactory.DBTYPE.HSQLDB);
		dao.persistImage(getData());
	}
}
