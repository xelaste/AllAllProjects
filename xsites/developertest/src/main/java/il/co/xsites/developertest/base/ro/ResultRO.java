package il.co.xsites.developertest.base.ro;

import java.io.Serializable;

/**
 * Object that contain result of service action.
 */
public class ResultRO implements Serializable {

	//------------------------ Constants -----------------------
	private static final long serialVersionUID = 1L;

	//------------------------ Fields --------------------------
	// true if operation was successful
	private boolean success;

	// error description
	private String error;

	// result of operation
	private Object result;

	//------------------------ Public methods ------------------
	//------------------------ Constructors --------------------
	public ResultRO() {
		this.success = true;
	}

	//------------------------ Field's handlers ----------------
	public boolean isSuccess() {
		return success;
	}

	public void setSuccess(boolean success) {
		this.success = success;
	}

	public String getError() {
		return error;
	}

	public void setError(String error) {
		this.error = error;
	}

	public Object getResult() {
		return result;
	}

	public void setResult(Object result) {
		this.result = result;
	}

	//------------------------ Other public methods ------------
	//------------------------ Private methods -----------------
}
