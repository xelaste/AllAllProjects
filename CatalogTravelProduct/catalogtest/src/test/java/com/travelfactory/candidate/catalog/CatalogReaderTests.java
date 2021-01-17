package com.travelfactory.candidate.catalog;


import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Paths;

import org.junit.After;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import com.travelfactory.candidate.catalog.dao.BatchRepository;
import com.travelfactory.candidate.catalog.watcher.BatchReader;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = CatalogReader.class,webEnvironment = SpringBootTest.WebEnvironment.NONE)
public class CatalogReaderTests {
	@Autowired
	private BatchRepository repository; 
	@Autowired
	private BatchReader reader;
	@Before
	public void beforeReader() 
	{
		String folder=System.getProperty("user.home") + "/catalog";
		try 
		{
			if (!Files.exists(Paths.get(folder)))
			{
				Files.createDirectory(Paths.get(folder));
			}
			if (Files.exists(Paths.get(folder + "/booking-22-12-2020.csv")))
			{
				Files.delete(Paths.get(folder + "/booking-22-12-2020.csv"));
			}
		} 
		catch (IOException e) 
		{
			e.printStackTrace();
		}
		repository.deleteAll();
	}

	@After
	public void stopReader()
	{
		reader.setStopFlag(true);
	}
	@Test
	public void loaderTest() throws Exception 
	{
		String folder=System.getProperty("user.home") + "/catalog";
		String content = "Id,Name,RoomNumber\n"
				+ "2,Palace Hotel,1932\n"
				+ "3,Béatrice Impérial Hotel,164\n"
				+ "4,Dan Boutique,88";
		Files.write(Paths.get(folder + "/booking-22-12-2020.csv"), content.getBytes(StandardCharsets.UTF_8));
		Thread.sleep(1500);
		Assert.assertTrue(repository.count()==1 );
	}

}
