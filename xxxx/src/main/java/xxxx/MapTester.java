package xxxx;

import java.util.HashMap;

public class MapTester 
{

	public static class Data
	{
		public String s;
		

		public Data(String s) {
			super();
			this.s = s;
		}


		@Override
		public boolean equals(Object obj) 
		{
			return true;
		}
		
	}

	public static void main(String[] args) 
	{
		HashMap<Data, String> map = new HashMap<>();
		map.put(new Data("xx"), "xx");
		map.put(new Data("yy"), "yy");
		map.put(new Data("xx"), "zz");
		System.out.println(map.size());
		System.out.println(map.get(new Data("xx")));
	}
}
