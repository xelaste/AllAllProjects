package com.travelfactory.candidate.catalog.watcher;
import java.nio.file.FileSystems;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardWatchEventKinds;
import java.nio.file.WatchEvent;
import java.nio.file.WatchKey;
import java.nio.file.WatchService;
import java.util.LinkedList;
import java.util.stream.Stream;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.CommandLineRunner;
import org.springframework.boot.autoconfigure.condition.ConditionalOnNotWebApplication;
import org.springframework.stereotype.Component;

import com.travelfactory.candidate.catalog.dao.BatchRepository;
import com.travelfactory.candidate.catalog.entities.Batch;
import com.travelfactory.candidate.catalog.entities.Room;

@Component
@ConditionalOnNotWebApplication
public class BatchReader implements CommandLineRunner 
{

	private boolean stopFlag=false;
	@Value("${travelfactory.catalog.folder}")
	private String folder=System.getProperty("user.home") + "/catalog";
	private BatchRepository repository;
	public BatchReader(BatchRepository repository) 
	{
		this.repository = repository;
	}
	@Override
	public void run(String ...args) 
	{
		try
		{
			WatchService watchService = FileSystems.getDefault().newWatchService();
			Path dir = Paths.get(folder);
			WatchKey key = dir.register(watchService, StandardWatchEventKinds.ENTRY_CREATE);

			for (;stopFlag;) {

				for (WatchEvent<?> event: key.pollEvents()) 
				{
					WatchEvent.Kind<?> kind = event.kind();
					if (kind == StandardWatchEventKinds.OVERFLOW) 
					{
						continue;
					}

					// The filename is the
					// context of the event.
					WatchEvent<Path> ev = (WatchEvent<Path>)event;
					Path filename = ev.context();

					// Verify that the new
					//  file is a text file.
					Stream <String> lines=null;
					try {
						String batchName = filename.toFile().getName().split("\\.")[0];
						String vendor=batchName.split("-")[0];
						String date = batchName.split("-")[1] + "-" + batchName.split("-")[2] + "-" + batchName.split("-")[3];
						Batch existingBatch = repository.findByVendorAndDate(vendor, date);
						Batch batch = new Batch();
						if (existingBatch!=null)
						{
							repository.delete(existingBatch);
						}
						batch.setDate(date);
						batch.setVendor(vendor);
						lines = Files.lines(dir.resolve(filename));
						LinkedList<Room> rooms = new LinkedList<>();
						lines.skip(1).forEach(s->{
							System.out.println(s);
							Room r = new Room();	
							rooms.add(r);
							r.setId(s.split(",")[0]);
							r.setName(s.split(",")[1]);
							r.setNumber(Integer.parseInt(s.split(",")[2]));
						});
						lines.close();
						batch.setRooms( rooms.toArray(new Room[rooms.size()]) );
						repository.save(batch);
						dir.resolve(filename).toFile().delete();
					
					} catch (Exception x) 
					{
						System.err.println(x);
						continue;
					}
					finally 
					{
						if (lines!=null)
						{
							lines.close();
						}
					}
				}

				// Reset the key -- this step is critical if you want to
				// receive further watch events.  If the key is no longer valid,
				// the directory is inaccessible so exit the loop.
				boolean valid = key.reset();
				if (!valid) {
					break;
				}
			}
		}
		catch (Exception e)
		{
			e.printStackTrace();
		}


	}
	public boolean isStopFlag() 
	{
		return stopFlag;
	}
	public void setStopFlag(boolean stopFlag) 
	{
		this.stopFlag = stopFlag;
	}
}
