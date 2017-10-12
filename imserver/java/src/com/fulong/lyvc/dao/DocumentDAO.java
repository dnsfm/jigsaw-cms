/**
 * 
 */
package com.fulong.lyvc.dao;

import java.sql.SQLException;

import com.fulong.lyvc.data.DocumentData;

/**
 * ConferenceDocumentDAO
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-17
 */
public interface DocumentDAO extends DAO {

	public long insert(DocumentData data) throws SQLException;

	public DocumentData[] findByConference(long conferenceID)
			throws SQLException;

	public void update(DocumentData data) throws SQLException;
}
