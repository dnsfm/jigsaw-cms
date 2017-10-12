/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

/**
 * ContactMemberDAO
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-18
 */
public interface ContactMemberDAO extends DAO {

	/**
	 * addGroupMember
	 * 
	 * @param userId
	 *            long
	 * @param groupId
	 *            long
	 * @throws SQLException
	 */
	public void insert(long userId, long groupId) throws SQLException;

	/**
	 * removeGroupMember
	 * 
	 * @param userId
	 *            long
	 * @param groupId
	 *            long
	 * @throws SQLException
	 */
	public void delete(long userId, long groupId) throws SQLException;

	/**
	 * 
	 * @param userId
	 * @param groupId
	 * @return
	 * @throws SQLException
	 */
	public boolean isMember(long userId, long groupId) throws SQLException;

}
