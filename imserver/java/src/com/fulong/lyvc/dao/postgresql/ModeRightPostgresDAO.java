/**
 * 
 */
package com.fulong.lyvc.dao.postgresql;

import java.sql.PreparedStatement;
import java.sql.SQLException;

import com.fulong.lyvc.dao.ModeRightDAO;

/**
 * ConferenceModeRightPostgresDAO
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-17
 */
public class ModeRightPostgresDAO extends PostgresqlDAO implements
		ModeRightDAO {

	/**
	 * Ȩ������
	 * 
	 * @param rightID
	 *            int
	 */
	public void insert(long roleId, int rightID) throws SQLException {
		String sql = "insert into conferenceroleright (roleid,rightid) values(?,?)";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, roleId);
		ps.setInt(2, rightID);
		ps.execute();
		ps.close();
	}

	/**
	 * ��ɫȨ�޲鿴
	 * 
	 * @return ConferenceMemberRight[]
	 */
	public int[] findByRole(long roleId) throws SQLException {
		String sql = "select rightid from conferenceroleright where roleid=?";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, roleId);
		return this.queryIntArray(ps);
	}

	/**
	 * Ȩ��ɾ��
	 * 
	 * @param rightID
	 *            int
	 * @return long
	 */
	public void delete(long roleId, int rightID) throws SQLException {
		String sql = "delete from conferenceroleright where roleid=? and rightid=?";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, roleId);
		ps.setInt(2, rightID);
		ps.execute();
		ps.close();
	}

	/**
	 * ɾ������Ȩ��
	 * 
	 * @return void
	 */
	public void deleteByRole(long roleId) throws SQLException {
		String sql = "delete from conferenceroleright where roleid=?";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.setLong(1, roleId);
		ps.execute();
		ps.close();
	}
}
