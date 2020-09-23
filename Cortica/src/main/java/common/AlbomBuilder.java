package common;

import modules.ProcessImageListModule;
import modules.ProcessInputFileModule;

public class AlbomBuilder {

	public static void main(String[] args) 
	{
		ProcessImageListModule module = new ProcessInputFileModule();
		module.execute();
	}
}
