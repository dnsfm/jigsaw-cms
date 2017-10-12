package com.fulong.longcon.repository.dao.mysql;

import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;
import java.util.List;

import com.fulong.longcon.repository.dao.ReferenceValueDao;
import com.fulong.longcon.repository.data.NodePropertyData;

/**
 * 
 * 
 * Coolink协同工作框架模型
 * 
 * Copyright: 2009-2011 北京中科辅龙计算机技术股份有限公司
 * 
 * Company: 北京中科辅龙计算机技术股份有限公司
 * 
 * @author LJY
 * @modified songbo 2010-8-20
 * @version 2.0
 * 
 */
public class MysqlReferenceValueDao extends ReferenceValueDao {

    private static final String SQL_REFERENCE_TABLES = "SELECT table_name FROM INFORMATION_SCHEMA.TABLES where table_name LIKE 'r|_%' ESCAPE '|'";
    protected List<String> getReferenceTableName() throws SQLException{
    	PreparedStatement command = null;
    	ResultSet rs = null;
    	List<String> tabs = new ArrayList<String>();
    	try {
            command = connection.prepareStatement(
            		SQL_REFERENCE_TABLES);
            rs = command.executeQuery();
            while(rs.next()){
            	tabs.add(rs.getString(1));
            }
    	}finally {
                this.close(command,rs);
         }
		return tabs;
    }
	public NodePropertyData[] findReferenceByNode(String nodeID,String property, int fromIndex,
			int pageSize) throws SQLException {
		PreparedStatement command = null;
		try {
			command = connection
					.prepareStatement(toRangeQueryForMysql(this.makeSelQuery(nodeID)));
			command.setInt(1, fromIndex);
			command.setInt(2, pageSize);
			NodePropertyData[] result = this.retrieve(command);
			return result;
		} finally {
			this.close(command);
		}
	}
}
