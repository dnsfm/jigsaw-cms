/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.Connection;

/**
 * BaseDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-17
 */
public class BaseDAO implements DAO{
	protected Connection connection;
	
	public void setConnection(Connection connection) {
		this.connection=connection;
	}

}
