package il.co.xsites.challenge.utils;

import java.lang.reflect.Field;

public class Utils {

	private Utils() {
		throw new UnsupportedOperationException();
	}

	/**
	 * A generic method that extracts a query string (e.g. fieldName=fieldValue&fieldName2=fieldValue2)
	 * from every field on `source` which is annotated with the given `annotation`.
	 * Should work with any object & any annotation.
	 *
	 * @param source
	 * @param annotation
	 * @return
	 */
	public static String extractQueryString(Object source, Class annotation) 
	{
		Field[] fields = source.getClass().getDeclaredFields();
		StringBuilder builder = new StringBuilder();
		for (int i = 0; i < fields.length; i++) 
		{
			fields[i].setAccessible(true);
			if (fields[i].isAnnotationPresent(annotation))
			{
				
				try {
					Object value = fields[i].get(source);
					String name = fields[i].getName();
					builder.append(name).append("=").append(value.toString()).append("&");
					
				} catch (IllegalArgumentException e) {
					
					e.printStackTrace();
				} catch (IllegalAccessException e) {
					
					e.printStackTrace();
				}
			}
		}
		if (builder.length() >0 && builder.charAt(builder.length()-1)=='&')
		{
			builder.setLength(builder.length() - 1);
		}		
		return builder.toString();
	}
}
