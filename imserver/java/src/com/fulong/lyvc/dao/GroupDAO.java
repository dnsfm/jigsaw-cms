/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

import com.fulong.lyvc.data.GroupData;

/**
 * GroupDAO
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-18
 */
public interface GroupDAO extends DAO {
	/**
	 * 
	 * @param data
	 * @return
	 * @throws SQLException
	 */
	public long insert(GroupData data) throws SQLException;

	/**
	 * modify a group
	 */
	public void update(GroupData data) throws SQLException;

	/**
	 * get group by id
	 */
	public GroupData findById(long groupId) throws SQLException;

	/**
	 * get all subgroups under the group
	 */
	public GroupData[] findByParent(long groupId) throws SQLException;

	/**
	 * delete the group
	 */
	public void delete(long groupId) throws SQLException;

	/**
	 * set a new password of user
	 */
	public void updateManager(long groupId, long userId)
			throws SQLException;

	public boolean isGroupManager(long userId) throws SQLException;

}
