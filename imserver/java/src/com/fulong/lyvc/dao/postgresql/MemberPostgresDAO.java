/**
 * 
 */
package com.fulong.lyvc.dao.postgresql;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.fulong.lyvc.dao.MemberDAO;

/**
 * MemberPostgresDAO
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-18
 */
public class MemberPostgresDAO extends PostgresqlDAO implements MemberDAO{
/**
 * 
 * @param parentGroupId
 * @param userId
 * @throws SQLException
 */
	public void insert(long parentGroupId, long userId)
			throws SQLException {
			String sql = "insert into groupmember (groupid,memberid) values(?,?)";
			PreparedStatement ps = connection.prepareStatement(sql);
			ps.setLong(1, parentGroupId);
			ps.setLong(2, userId);
			ps.executeUpdate();
			ps.close();
	}
	public long getParentId(long Id) throws SQLException {
		long pId = -1;
			String sql = "select groupid, memberid from groupmember where memberid=?";
			PreparedStatement ps = connection.prepareStatement(sql);
			ps.setLong(1, Id);
			ResultSet rs = ps.executeQuery();
			if (rs.next())
				pId = rs.getLong("groupid");
			rs.close();
			ps.close();
			return pId;
	}

	
	/**
	 * ��ɾ����ϵ������Ӱ���û������������Member��ʧȥ������֯ Ӧ��������������ʹ�ã��Ա�֤����������
	 */
	public void delete(long groupId, long memberId) throws SQLException {
			String sql = "delete from groupmember where groupid=? and memberid=?";
			PreparedStatement ps = connection.prepareStatement(sql);
			ps.setLong(1, groupId);
			ps.setLong(2, memberId);
			ps.executeUpdate();
			ps.close();
	}
	public void deleteByGroup(long groupId) throws SQLException {
		String sql = "delete from groupmember where groupid=? ";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, groupId);
	
		ps.executeUpdate();
		ps.close();
		
	}
	public boolean isMember(long groupId, long memberId)	throws SQLException {
		boolean result = false;
		String sql = "select * from groupmember where groupid=? and memberid=?";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, groupId);
		ps.setLong(2, memberId);
		ResultSet rs = ps.executeQuery();
		result = rs.next();
		ps.close();
		return result;
	}	
	



	
}
