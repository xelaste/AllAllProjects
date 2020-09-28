package dao;

import db.ConfigDB;

public class HSQLDBImageDAO extends ImageDAO 
{

	public HSQLDBImageDAO() 
	{
		super();
		configDB = new ConfigDB("jdbc:hsqldb:mem:ImagesDB", "sa", "", org.hsqldb.jdbcDriver.class.getName());
	}
	
}
