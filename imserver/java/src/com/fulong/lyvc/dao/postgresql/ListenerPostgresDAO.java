/**
 * 
 */
package com.fulong.lyvc.dao.postgresql;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;

import com.fulong.lyvc.dao.ListenerDAO;
import com.fulong.lyvc.data.ListenerData;

/**
 * ListenerPostgresDAO
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-17
 */
public class ListenerPostgresDAO extends PostgresqlDAO implements ListenerDAO {
	public ListenerData getListener() throws SQLException {
		String sql = "select * from notifyregister";
		PreparedStatement ps = connection.prepareStatement(sql);
		ResultSet rs = ps.executeQuery();
		ListenerData listener = null;
		if (rs.next()) {
			listener = new ListenerData();
			listener.setId(rs.getLong("id"));
			listener.setIp(rs.getString("ip"));
			listener.setPort(rs.getInt("port"));
		}
		rs.close();
		ps.close();
		return listener;
	}
	
	public void insert(ListenerData data) throws SQLException{
		// Insert this listener
		String sql = "insert into notifyregister (id,ip,port) values(?,?,?)";
		PreparedStatement ps = connection.prepareStatement(sql);
		long id = this.getPrimaryKey();
		data.setId(id);
		ps.setLong(1, data.getId());
		ps.setString(2, data.getIp());
		ps.setInt(3, data.getPort());
		ps.execute();
		ps.close();
	}

	public void remove() throws SQLException {
		String sql = "delete from notifyregister";
		PreparedStatement ps = connection.prepareStatement(sql);
		ps.execute();
		ps.close();
	}
}
