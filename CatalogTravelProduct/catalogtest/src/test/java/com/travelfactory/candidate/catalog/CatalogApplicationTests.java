package com.travelfactory.candidate.catalog;


import java.nio.file.Files;
import java.util.Date;
import java.util.LinkedList;

import org.junit.Before;
import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;
import com.travelfactory.candidate.catalog.dao.BatchRepository;
import com.travelfactory.candidate.catalog.entities.Batch;
import com.travelfactory.candidate.catalog.entities.Room;

@RunWith(SpringRunner.class)
@SpringBootTest(classes = CatalogApplication.class)
public class CatalogApplicationTests {

	@Autowired
	private BatchRepository repository; 
	
	@Before
	public void beforeReader() 
	{
		repository.deleteAll();
		Batch batch = new Batch();
		batch.setDate(new Date().toInstant().toString());
		batch.setVendor("vendor");
		LinkedList<Room> rooms = new LinkedList<>();
		Room r = new Room();	
		rooms.add(r);
		r.setId("1");
		r.setName("room1");
		r.setNumber(1);
		r = new Room();	
		rooms.add(r);
		r.setId("2");
		r.setName("room2");
		r.setNumber(2);		
		batch.setRooms( rooms.toArray(new Room[rooms.size()]) );
		repository.save(batch);
	}
	@Test
	public void contextLoads() 
	{
		
	}

}
