package modules;

import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.LinkedList;
import java.util.List;
import java.util.concurrent.BlockingQueue;
import java.util.concurrent.Callable;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.Future;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;
import java.util.concurrent.atomic.AtomicBoolean;

public class ProcessInputFileModule extends ProcessImageListModule
{
	
	private final static int BUFFER_SIZE=1000;
	private String filepath="./resources/input.images.txt";
	private BlockingQueue<String> queue = new LinkedBlockingQueue<>(BUFFER_SIZE);
	private ExecutorService executorConsumer = Executors.newFixedThreadPool(10);
	private ExecutorService executorProducer = Executors.newSingleThreadExecutor();
	private AtomicBoolean stop = new AtomicBoolean(false);
	private List<Future<Void>> listConsumersResults = new LinkedList<>();


	public String getFilepath() 
	{
		return filepath;
	}

	public void setFilepath(String filepath) 
	{
		this.filepath = filepath;
	}
	
	@Override
	public void execute ()
	{
		Future<Void> producerResult =executorProducer.submit( new Callable<Void>()  {

			@Override
			public Void call() throws Exception 
			{
				Path file = Paths.get(filepath);
				try (InputStream in = Files.newInputStream(file);
						BufferedReader reader =
								new BufferedReader(new InputStreamReader(in))) 
				{
					String line = null;
					while ((line = reader.readLine()) != null) 
					{
						_logger.info( "Put " + line );
						queue.offer(line);
					}
				} 
				catch (Exception e) 
				{
					_logger.fatal(e,e);
					throw new RuntimeException(e);
				}
				return null;
			}

			
		});
		for (int i=0;i<10;i++)
		{
			Future<Void> consumerResult = executorConsumer.submit(new Callable<Void>() 
			{
				@Override
				public Void call() 
				{
					while (!stop.get())
					{	
						try 
						{
							String imageUrl = queue.poll(100, TimeUnit.MILLISECONDS);
							if (imageUrl==null || imageUrl.isEmpty() )
							{
								continue;
							}
							_logger.info( "Take " + imageUrl );
							boolean error = getImageProcessModule().processImage(imageUrl);
							if ( error && !getErrorExists() )
							{
								setErrorExists(error);
							}
						}
						catch (Exception e)
						{
							_logger.fatal(e,e);
							throw new RuntimeException(e);
						}
					}
					return null;
				}
			});
			listConsumersResults.add(consumerResult);
		}
		try 
		{
			producerResult.get();
			while (queue.size()>0)
			{
				Thread.sleep(100);
			}
			stop.set(true);
			for(Future<Void> f:listConsumersResults)
			{
				f.get();
			}
		} 
		catch (Exception e) 
		{
			_logger.fatal(e,e);
			System.exit(100);
		}
	}
}
