/**
 * 
 */
package org.phoenix.dbimport;

import java.util.List;

import javax.sql.DataSource;

import org.springframework.jdbc.core.JdbcTemplate;

/**
 * @author lixf
 *
 */
public abstract class AbstractDBImport {
	/**
	 * Դ����Դ
	 */
	private DataSource source;
	/**
	 * Ŀ������Դ,����ϵͳ�����ݿ⣻
	 */
	private DataSource dest;
	
	private List<DBMapping> mappings;
	
	private long idcounter = 0;
	
	private int pageSize = 1000;
	public AbstractDBImport(){
		this.idcounter = System.currentTimeMillis();
	}
	
	
	public void setSource(DataSource source){
		this.source = source;
	}
	public void setDest(DataSource dest){
		this.dest = dest;
	}
	
	public void setMappings(List<DBMapping> mappings){
		this.mappings = mappings;
	}
	
	public void setPageSize(int size){
		this.pageSize = size;
	}
	
		
	public void execute(){
		
		for(DBMapping mapping:mappings){			
			String sqlRead = "select * from "+mapping.getTableName()+" order by "+ mapping.getIdColumn();
			long size = this.getRowCount(mapping);
			for(int i=0;i<=size/this.pageSize;i++){
			sqlRead = this.getPagination(sqlRead, 0, pageSize);
			}
			//�����ڵ�
			
			//����ֵ
		}
	}
	
	protected long getRowCount(DBMapping mapping){
		String sql = "select count(*) from "+mapping.getTableName();
		JdbcTemplate template = new JdbcTemplate(this.source);
		return template.queryForLong(sql);
		
	}
	
	protected abstract String getPagination(String query, int from , int number);
}
