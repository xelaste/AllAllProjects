package domain;

import java.util.Date;

public class ImageData 
{
	private Date downloadDate;
	private String filepath;
	private String url;
	private String md5;
	public Date getDownloadDate() {
		return downloadDate;
	}
	public void setDownloadDate(Date downloadDate) {
		this.downloadDate = downloadDate;
	}
	public String getFilepath() {
		return filepath;
	}
	public void setFilepath(String filepath) {
		this.filepath = filepath;
	}
	public String getUrl() {
		return url;
	}
	public void setUrl(String url) {
		this.url = url;
	}
	public String getMd5() {
		return md5;
	}
	public void setMd5(String md5) {
		this.md5 = md5;
	}
	@Override
	public String toString() 
	{
		StringBuilder sb = new StringBuilder();
		sb.append("\nDate=").append(downloadDate)		
		.append("\nfilepath=").append(filepath)
		.append("\nurl=").append(url)
		.append("\nmd5=").append(md5);
		return super.toString() + sb.toString();
	}
	
}
