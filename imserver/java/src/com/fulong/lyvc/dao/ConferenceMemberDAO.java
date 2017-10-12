/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

/**
 * ConferenceMemberDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-17
 */
public interface ConferenceMemberDAO extends DAO{
	public  void insert(long conferenceID, long modelRoleID, long userID) throws SQLException;

	public long[] findByConference(long conferenceId) throws SQLException;


	public void delete(long confId, long userId) throws SQLException;

	public void deleteByConference(long confId) throws SQLException;

	public void deleteByUser(long userId) throws SQLException;

	public void deleteByMode(int type) throws SQLException;

	public boolean exists(long conferenceId, long userId) throws SQLException;
}
