import java.io.IOException;

public class Question01 {
	public static void main(String[] args) {
		Question05Sub myref = new Question05Sub();
		try{
			myref.test();
		}catch(Exception ioe){}
	}
	void test() throws IOException{
		System.out.println("In Question05");
		throw new IOException();
	}
}
class Question05Sub extends Question01 {
	void test() {
		System.out.println("In Question05Sub");
	}

}


