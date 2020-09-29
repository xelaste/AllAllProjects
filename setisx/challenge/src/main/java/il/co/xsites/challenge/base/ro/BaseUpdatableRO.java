package il.co.xsites.challenge.base.ro;

import java.util.Objects;

public abstract class BaseUpdatableRO extends BaseRO {

	// ------------------------ Constants -----------------------
	private static final long serialVersionUID = 1L;

	// ------------------------ Fields --------------------------
	private long lastUpdateTime;

	// ------------------------ Public methods ------------------
	// ------------------------ Constructors --------------------
	// ------------------------ Field's handlers ----------------
	public long getLastUpdateTime() {
		return lastUpdateTime;
	}

	public void setLastUpdateTime(long lastUpdateTime) {
		this.lastUpdateTime = lastUpdateTime;
	}

	@Override
	public boolean equals(Object o) {
		if(this == o) {
			return true;
		}
		if(o == null || getClass() != o.getClass()) {
			return false;
		}
		if(!super.equals(o)) {
			return false;
		}
		BaseUpdatableRO that = (BaseUpdatableRO) o;
		return lastUpdateTime == that.lastUpdateTime;
	}

	@Override
	public int hashCode() {
		return Objects.hash(super.hashCode(), lastUpdateTime);
	}

	// ------------------------ Private methods -----------------
}
