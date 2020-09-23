package dao;

import java.util.HashMap;
import java.util.Map;


public class ImageDAOFactory 
{
	private static ImageDAOFactory instance = new ImageDAOFactory();
	private Map<DBTYPE,ImageDAO> daos = new HashMap<>();
	public static ImageDAOFactory getInstance ()
	{
		return instance;
	}

	public synchronized ImageDAO createDAO (DBTYPE type)
	{
		ImageDAO dao = daos.get(type);
		switch (type) 
		{
		case HSQLDB:
			if (dao == null )
			{	
				dao = new HSQLDBImageDAO();
				dao.init();
				daos.put(type, dao);
			}
			return dao;
		default:
			return null;
		}
	}

	public static enum DBTYPE
	{
		HSQLDB,MYSQL,DB2,ORACLE
	}
	
}
