package domain;

public class Stocks extends BasePOJO
{
	private boolean ok;
	public boolean isOk() {
		return ok;
	}
	public void setOk(boolean ok) 
	{
		this.ok = ok;
	}
	StockSymbol symbols[];
	public StockSymbol[] getSymbols() {
		return symbols;
	}
	public void setSymbols(StockSymbol[] symbols) {
		this.symbols = symbols;
	}
	
	
}
