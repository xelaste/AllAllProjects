package il.co.xsites.developertest.base;

/**
 * Base interface for DAO.
 */
public interface BaseDao {

	/**
	 * Persist entity to DB.
	 *
	 * @param object entity for saving.
	 * @return persisted entity
	 */
	<T extends BaseEntity> T saveOrUpdate(T object);

	/**
	 * Flush session.
	 */
	void flush();

	/**
	 * Clear session cache.
	 */
	void clear();
}
