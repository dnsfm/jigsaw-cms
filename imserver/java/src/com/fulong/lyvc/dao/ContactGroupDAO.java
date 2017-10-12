/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

import com.fulong.lyvc.data.ContactGroupData;

/**
 * ContactGroupDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-18
 */
public interface ContactGroupDAO extends DAO {
	public long insert(ContactGroupData data) throws SQLException ;

	/**
	 * renameGroup
	 *
	 * @param groupId long
	 * @param newName String
	 * @throws SQLException 
	 */
	public void rename(long groupId, String newName) throws SQLException;

	public ContactGroupData[] findGroupsByUser(long userId) throws SQLException;

	public ContactGroupData findGroupsById(long id) throws SQLException;
}
