/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

import com.fulong.lyvc.data.ListenerData;

/**
 * ListenerDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-17
 */
public interface ListenerDAO extends DAO {

	public ListenerData getListener() throws SQLException;

	public void remove() throws SQLException;

	public void insert(ListenerData data) throws SQLException;

}
