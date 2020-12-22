package com.travelfactory.candidate.catalog;

import javax.inject.Inject;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = CatalogReader.class)
public class CatalogReaderTests {
	@Inject
	private CatalogReader reader;
	@Test
	public void contextLoads() 
	{
		CatalogReader.main(new String[0]);
	}

}
