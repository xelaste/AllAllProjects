package modules;

import services.ImageDownloadService;
import services.ImageMD5CalulatorService;
import services.ImagePersistsService;
import services.ImageResizeService;
import services.ImageToGreyScaleService;
import services.ServiceBase;

public class ImageProcessModuleImpl extends ImageProcessModule {


	@Override
	protected ServiceBase[] generateProcessSteps() 
	{
		ServiceBase[] steps = new ServiceBase[5];
		steps[0]=new ImageDownloadService();
		steps[1]=new ImageMD5CalulatorService();
		steps[2]=new ImageResizeService();
		steps[3]=new ImageToGreyScaleService();
		steps[4]=new ImagePersistsService();

		return steps;
	}

}
