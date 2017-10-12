/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

/**
 * ConferenceModeRightDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-17
 */
public interface ModeRightDAO extends DAO {

	/**
	 * Ȩ������
	 * 
	 */
	public void insert(long roleId, int rightID) throws SQLException;

	/**
	 * ��ɫȨ�޲鿴
	 * 
	 * @return ConferenceMemberRight[]
	 */
	public int[] findByRole(long roleId) throws SQLException;

	/**
	 * Ȩ��ɾ��
	 * 
	 * @return long
	 */
	public void delete(long roleId, int rightID) throws SQLException;

	/**
	 * ɾ������Ȩ��
	 * 
	 * @return void
	 */
	public void deleteByRole(long roleId) throws SQLException;

}
