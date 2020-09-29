package il.co.xsites.challenge.base.ro;

import java.io.Serializable;
import java.util.Objects;

public abstract class BaseRO implements Serializable {

	// ------------------------ Constants -----------------------
	private static final long serialVersionUID = 1L;

	// ------------------------ Fields --------------------------
	private long id;

	private long creationTime;

	// ------------------------ Public methods ------------------
	// ------------------------ Constructors --------------------
	public BaseRO() {

	}

	public BaseRO(long id) {
		this.id = id;
	}

	// ------------------------ Field's handlers ----------------
	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public long getCreationTime() {
		return creationTime;
	}

	public void setCreationTime(long creationTime) {
		this.creationTime = creationTime;
	}

	@Override
	public boolean equals(Object o) {
		if(this == o) {
			return true;
		}
		if(o == null || getClass() != o.getClass()) {
			return false;
		}
		BaseRO baseRO = (BaseRO) o;
		return id == baseRO.id &&
				creationTime == baseRO.creationTime;
	}

	@Override
	public int hashCode() {
		return Objects.hash(id, creationTime);
	}

	// ------------------------ Private methods -----------------
}
