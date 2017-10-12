/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

import com.fulong.lyvc.data.ContactGroupData;

/**
 * ContactDefaultGroupDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-18
 */
public interface ContactDefaultGroupDAO extends DAO{

	/**
	 * getDefaultGroupId
	 * 
	 * @param userId
	 *            long
	 * @return long
	 * @throws SQLException
	 */
	public void insert(ContactGroupData data) throws SQLException;

	/**
	 * getDefaultGroupId
	 * 
	 * @param userId
	 *            long
	 * @return long
	 */
	public ContactGroupData findByUser(long userId) throws SQLException;
	/**
	 * getDefaultGroupId
	 * 
	 * @param userId
	 *            long
	 * @return long
	 */
	public ContactGroupData findById(long id) throws SQLException;

}
