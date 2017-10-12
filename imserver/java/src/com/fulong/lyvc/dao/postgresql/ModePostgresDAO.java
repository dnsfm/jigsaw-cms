package com.fulong.lyvc.dao.postgresql;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import com.fulong.lyvc.dao.ModeDAO;
import com.fulong.lyvc.data.ModeData;

/**
 * 
 * ConferenceModelSessionImpl
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-11
 */
public class ModePostgresDAO extends PostgresqlDAO implements ModeDAO {

	public long insert(ModeData data)
			throws SQLException {
			String sql = "insert into conferencemodel (id,name,description,ispredefined) values(?,?,?,?)";
			PreparedStatement ps = connection.prepareStatement(sql);
			data.setId(getPrimaryKey());
			ps.setLong(1, data.getId());
			ps.setString(2, data.getName());
			ps.setString(3, data.getDesc());
			ps.setBoolean(4, data.isPredefined());
			ps.execute();
			ps.close();
			return data.getId();
	}

	/**
	 * deleteConferenceModel
	 * 
	 * @param conferenceModelID
	 *            long
	 * @return boolean

	 */
	public void delete(long conferenceModelID)
			throws SQLException {
			String sql = "delete from conferencemodel where id=?";
			PreparedStatement ps = connection.prepareStatement(sql);
			ps.setLong(1, conferenceModelID);
			ps.execute();
			ps.close();
	}


	public ModeData findByID(long conferenceModelID) throws SQLException {
		ModeData data=null;
			String sql = "select * from conferencemodel where id=?";
			PreparedStatement ps = connection.prepareStatement(sql);
			ps.setLong(1, conferenceModelID);
			ResultSet rs = ps.executeQuery();
			if (rs.next()) {
				data = new ModeData();
				data.setId(conferenceModelID);
				data.setName(rs.getString("name"));
				data.setDesc(rs.getString("description"));
			}
			rs.close();
			ps.close();
			return data;
	}

	/**
	 * getAkkConferenceModels
	 * 
	 * @param
	 * @return ArrayList

	 */
	public ModeData[] findAll() throws SQLException {
			ArrayList<ModeData> models = new ArrayList<ModeData>();
			String sql = "select * from conferencemodel";
			PreparedStatement ps = connection.prepareStatement(sql);
			ResultSet rs = ps.executeQuery();
			while (rs.next()) {
				ModeData conferenceModel = new ModeData();
				conferenceModel.setId(rs.getLong("id"));
				conferenceModel.setName(rs.getString("name"));
				conferenceModel.setDesc(rs.getString("description"));
				models.add(conferenceModel);
			}

			rs.close();
			ps.close();
			return models.toArray(new ModeData[models.size()]);
	}

	public ModeData[] findUserDefinedModels()	throws SQLException {
		ArrayList<ModeData> models = new ArrayList<ModeData>();
			String sql = "select * from conferencemodel where ispredefined=false";
			PreparedStatement ps = connection.prepareStatement(sql);
			ResultSet rs = ps.executeQuery();
			while (rs.next()) {
				ModeData conferenceModel = new ModeData();
				conferenceModel.setId(rs.getLong("id"));
				conferenceModel.setName(rs.getString("name"));
				conferenceModel.setDesc(rs.getString("description"));
				models.add(conferenceModel);
			}

			rs.close();
			ps.close();
			return models.toArray(new ModeData[models.size()]);
	
	}

	/**
	 * modifyConferenceModel
	 * 
	 * @param conferenceModel
	 *            ConferenceModel
	 */
	public void update(ModeData conferenceModel)
			throws SQLException {
			String sql = "update conferencemodel set name=?,description=? where id=?";
			PreparedStatement ps = connection.prepareStatement(sql);
			ps.setString(1, conferenceModel.getName());
			ps.setString(2, conferenceModel.getDesc());
			ps.setLong(3, conferenceModel.getId());
			ps.execute();
			ps.close();
	}

	
}
