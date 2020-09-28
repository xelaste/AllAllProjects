package dao;

import java.sql.ResultSet;
import java.sql.Statement;
import java.util.Date;

import org.apache.commons.codec.binary.Base64;
import org.apache.log4j.Logger;

import db.ConfigDB;
import domain.ImageData;

public abstract class ImageDAO 
{
	protected static final Logger _logger = Logger.getRootLogger();
	protected ConfigDB configDB;
	public void init ()
	{
		String query = "CREATE TABLE IF NOT EXISTS images "
				+ "(downloadDate  TIMESTAMP, filepath VARCHAR(2000),"
				+ "url VARCHAR(2000), md5 VARCHAR(32))";
		try (Statement s = configDB.createStatement()) {
			s.executeUpdate(query);
		}
		catch (Exception e) {
			_logger.error(e.getLocalizedMessage());
			throw new RuntimeException(e);
		}

	}
	public ImageData retrieveImageByUrl (String URL)
	{
		_logger.info("Starting query... ");
		ImageData data = null;
		String query = "SELECT * FROM images where url='" + URL + "'";
		Statement st = configDB.createStatement();
		ResultSet result = null;
		try {
			result = st.executeQuery(query);
			if (result.next()) 
			{ 
				data = new ImageData();
				data.setUrl(result.getString("url"));
				data.setDownloadDate (result.getTimestamp("downloadDate"));
				data.setFilepath(result.getString ("filepath"));
				String md5 = result.getString ("md5");
				byte[] md5Decoded = Base64.decodeBase64(md5.getBytes());
				data.setMd5( new String (md5Decoded));
			}
			_logger.info("Finished query");
			return data;
		}
		catch (Exception e) {
			_logger.error(e.getLocalizedMessage());
			throw new RuntimeException(e);
		}
		finally {
			configDB.closeStatement(st, result);
		}
	}
	public void persistImage (ImageData data)
	{
		ImageData existingImage = retrieveImageByUrl(data.getUrl());
		String query = null;
		byte[] md5Encoded = Base64.encodeBase64(data.getMd5().getBytes());
		String md5 = new String (md5Encoded);
		if (existingImage != null )
		{
			query = "update images set downloadDate=now(), filepath='" + data.getFilepath() + "',md5='" + md5 +"' where url='" + data.getUrl() + "'"; 
		}
		else
		{
			query = "INSERT INTO images (downloadDate, filepath, url, md5) "
					+ " VALUES(now(),'" + data.getFilepath()+"','" + data.getUrl() + "','" + md5 +"')";
		}
		try (Statement s = configDB.createStatement()) 
		{
			s.executeUpdate(query);
		}
		catch (Exception e) {
			_logger.error(e.getLocalizedMessage());
			throw new RuntimeException(e);
		}

	}
	
}
