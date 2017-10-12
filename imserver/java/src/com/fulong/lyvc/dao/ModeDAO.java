package com.fulong.lyvc.dao;

import java.sql.SQLException;

import com.fulong.lyvc.data.ModeData;

/**
 * 
 * ConferenceModelSession
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-11
 */
public interface ModeDAO extends DAO {

	// ����ģʽ�鿴�������ڷ���null
	public ModeData findByID(long conferenceModelID) throws SQLException;

	// �鿴���л���ģʽ�������ڷ���null
	public ModeData[] findAll() throws SQLException;

	/**
	 * 
	 * @return
	 * @throws SQLException
	 */
	public ModeData[] findUserDefinedModels() throws SQLException;

	// ����ģʽ����
	public long insert(ModeData conferenceModel) throws SQLException;

	// ����ģʽ�޸�
	public void update(ModeData conferenceModel) throws SQLException;

	// ����ģʽɾ��
	public void delete(long conferenceModelID) throws SQLException;

}
