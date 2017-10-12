package com.fulong.lyvc.dao;

import java.sql.SQLException;

import com.fulong.lyvc.data.ConferenceData;

/**
 * 
 * ConferenceSession
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-11
 */
public interface ConferenceDAO extends DAO {

	//
	// Conference interface
	//

	// ����鿴�����鲻����ʱ����null
	public ConferenceData findById(long conferenceID) throws SQLException;

	// ���鴴��
	public long insert(ConferenceData conference) throws SQLException;

	// �����޸�
	public void update(ConferenceData conference) throws SQLException;

	// ����ɾ��
	public void delete(long conferenceID) throws SQLException;

	// ��û����б�
	public ConferenceData[] findAll() throws SQLException;

	/**
	 * ��ȡ�û������Ļ����б�
	 * 
	 * @param creatorId
	 * @return
	 * @throws SQLException
	 */
	public ConferenceData[] findByCreator(long creatorId)
			throws SQLException;

	//
	// Right interface
	//

	// ɾ��һ��Ȩ��
//	public void deleteConferenceRight(long rightID)	throws SQLException;

	// ȡ��һ��Ȩ��
//	public ConferenceRightData getConferenceRight(long rightID)	throws SQLException;

	// ������п���Ȩ��
	// public abstract ArrayList getAllConferenceRight() throws SQLException;

	// �ӻ�����ɾ��һ���û�
	// public abstract void deleteConferenceUser(long confId, long userId)
	// throws SQLException;

	// ��ȡ�û���ϵͳ�еĽ�ɫid
	// public abstract long getUserRole(long userId) throws SQLException;

//	public abstract void createBulletin(String title, String content)	throws SQLException, IOException;

//	public abstract void createConferenceNotice(long conferenceId,	String title, String content) throws SQLException, IOException;

	/*
	 * // �û�����ͨ��web�޸��û���������ϵ�˺�֪ͨ�����������Ӧ����usersession��ʵ�֡� //
	 * Ŀǰ���������Ϊ������conferencesession�ֳɵ�listener public abstract void
	 * notifyListenerRemoveUser(long userId) throws SQLException;
	 * 
	 * public abstract void notifyListenerAddUser(long id, String name, String
	 * passwd, String fname, String lname, String email) throws SQLException,
	 * IOException;
	 * 
	 * public abstract void notifyListenerSetUserPassword(long userId, String
	 * password) throws SQLException, IOException;
	 * 
	 * public abstract void notifyListenerAddGroup(long parentGroupId, long
	 * groupId, String groupName) throws SQLException, IOException;
	 * 
	 * public abstract void notifyListenerModifyGroup(long groupId, String
	 * groupName, String groupDesc) throws SQLException, IOException;
	 * 
	 * public abstract void notifyListenerRemoveGroup(long groupId) throws
	 * SQLException, IOException;
	 * 
	 * public abstract void notifyListenerAddGroupMember(long groupId, long
	 * userId) throws SQLException, IOException;
	 * 
	 * public abstract void notifyListenerDelGroupMember(long groupId, long
	 * memberId) throws SQLException, IOException;
	 * 
	 * public abstract void notifyListenerMoveGroupMember(long fromGroupId, long
	 * toGroupId, long memberId) throws SQLException, IOException;
	 */
	public void deleteByModel(int model) throws SQLException;

	public void deleteByCreatorId(long creatorId) throws SQLException;
}
