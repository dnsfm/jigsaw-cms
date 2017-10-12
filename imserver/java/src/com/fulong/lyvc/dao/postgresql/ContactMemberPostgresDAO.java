/**
 * 
 */
package com.fulong.lyvc.dao.postgresql;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.fulong.lyvc.dao.ContactMemberDAO;

/**
 * ContactMemberPostgresDAO
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-18
 */
public class ContactMemberPostgresDAO extends PostgresqlDAO implements
		ContactMemberDAO {
	/**
	 * addGroupMember
	 * 
	 * @param userId
	 *            long
	 * @param groupId
	 *            long
	 * @throws SQLException
	 */
	public void insert(long userId, long groupId) throws SQLException {
		// insert record
		String sql = "insert into groupuser(userid, groupId) values(?, ?)";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, userId);
		ps.setLong(2, groupId);
		ps.executeUpdate();
	}

	/**
	 * removeGroupMember
	 * 
	 * @param userId
	 *            long
	 * @param groupId
	 *            long
	 * @throws SQLException
	 */
	public void delete(long userId, long groupId) throws SQLException {

		String sql = "delete from groupuser where userid=? and groupid=?";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, userId);
		ps.setLong(2, groupId);
		ps.executeUpdate();
		ps.close();

	}

	public boolean isMember(long userId, long groupId) throws SQLException {
		String sql = "select * from groupuser where userid=? and groupid=?";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, userId);
		ps.setLong(2, groupId);
		ResultSet rs = ps.executeQuery();
		boolean result = (rs.next());
		ps.close();
		return result;
	}
}
