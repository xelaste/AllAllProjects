package modules;
import org.junit.Assert;
import org.junit.Test;

public class ProcessInputFileModuleTest {

	@Test
	public void testExecute() 
	{
		ProcessInputFileModule module = new ProcessInputFileModule();
		module.execute();
		Assert.assertFalse(module.getErrorExists());
	}

}
