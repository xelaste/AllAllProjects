package il.co.xsites.challenge.base;

import javax.persistence.*;

import il.co.xsites.challenge.base.ro.BaseRO;
import il.co.xsites.challenge.base.ro.BaseUpdatableRO;

import java.util.Date;

/**
 * Base class for Updateble Hibernate entities.
 */
@MappedSuperclass
public abstract class BaseUpdatebleEntity extends BaseEntity {

	private static final long serialVersionUID = 1L;

	//------------------------ Constants -----------------------
	//------------------------ Fields --------------------------
	// the last time the entity was edited.
	private Date lastUpdateTime;

	//------------------------ Public methods ------------------
	//------------------------ Constructors --------------------
	//------------------------ Field's handlers ----------------
	@Version
	@Temporal(TemporalType.TIMESTAMP)
	@Column(name = "last_update_time", nullable = false)
	public Date getLastUpdateTime() {
		return lastUpdateTime;
	}

	public void setLastUpdateTime(Date lastUpdateTime) {
		this.lastUpdateTime = lastUpdateTime;
	}

	//------------------------ Other public methods ------------
	@SuppressWarnings("unchecked")
	@Transient
	@Override
	public <T extends BaseRO> T getRepresentation() {
		BaseUpdatableRO ro = super.getRepresentation();
		ro.setLastUpdateTime(getCreationTime().getTime());
		return (T) ro;
	}

	//------------------------ Private methods -----------------
}
