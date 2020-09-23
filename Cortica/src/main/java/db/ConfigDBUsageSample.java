package db;

import java.sql.*;

public class ConfigDBUsageSample extends ConfigDB {

	public ConfigDBUsageSample(String DBAddress, String userName, String password, String driver) {
		super(DBAddress, userName, password, driver);
	}
	
	

	public void testTable() throws Exception {
		_logger.info("Starting query... ");
		String query = "SELECT * FROM images; ";
		Statement st = createStatement();
		ResultSet result = null;
		try {
			result = st.executeQuery(query);
			while (result.next()) { // process results one row at a time
				String url = result.getString("url");
				_logger.info("Found url " + url);
			}
			_logger.info("Finished query");

		}
		catch (Exception e) {
			_logger.error(e.getLocalizedMessage());
			throw e;
		}
		finally {
			closeStatement(st, result);
		}
	}
	
	public void createTable() throws SQLException {
		String query = "CREATE TABLE IF NOT EXISTS images "
				+ "(downloadDate DATE, filepath VARCHAR(2000),"
				+ "url VARCHAR(2000), md5 VARCHAR(32))";
		try (Statement s = createStatement()) {
			s.executeUpdate(query);
		}
	}
	
	public void insertIntoTable() throws SQLException {
		String query = "INSERT INTO images (downloadDate, filepath, url, md5) "
				+ " VALUES(now(), 'c://image.jpg', 'http://abcd.com/image.jpg', 'some_md5')";
		try (Statement s = createStatement()) {
			s.executeUpdate(query);
		}
	}
}