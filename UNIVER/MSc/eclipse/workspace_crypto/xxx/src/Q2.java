import java.awt.Button;
import java.awt.Frame;
import java.awt.GridLayout;


public class Q2 
{
	
	public static void main(String[] args){
		Frame f = new Frame("Question 3");
		f.setLayout(new GridLayout(2,3));
		for(int i=0;i<(int)Math.round(6.51);i++){
			f.add(new Button(""+(i+1)));
		}
		f.pack();
		f.validate();
		f.setVisible(true);
	}

	
}
