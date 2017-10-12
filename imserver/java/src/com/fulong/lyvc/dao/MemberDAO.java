/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

/**
 * MemberDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-18
 */
public interface MemberDAO extends DAO{
	
	public long getParentId(long Id) throws SQLException ;
	/**
	 * make the user as the child of the group identified by parentGroupId
	 */
	public void insert(long parentGroupId, long userId)
			throws SQLException;

	/**
	 * make the user as the child of the group identified by parentGroupId
	 */
	public boolean isMember(long parentGroupId, long userId)
			throws SQLException;

	/**
	 * remove the member from the group
	 */
	public void delete(long groupId, long memberId) throws SQLException;

	/**
	 * remove the member from the group
	 */
	public void deleteByGroup(long groupId) throws SQLException;

}
