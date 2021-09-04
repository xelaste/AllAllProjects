import java.io.IOException;
import java.io.RandomAccessFile;
import java.util.Vector;
class A{}

class B extends A implements E {}	//line 1
class C extends A{}
class D extends B{}
interface E{}

public class Question07 
{
	static void xx(){};	
	void xx( int aa ){}
static class AA extends Question07
{
	static void xx(){};
}

}