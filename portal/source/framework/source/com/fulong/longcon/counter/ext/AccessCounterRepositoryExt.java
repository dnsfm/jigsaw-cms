package com.fulong.longcon.counter.ext;

import com.fulong.longcon.counter.AccessCounterRepository;
import com.fulong.common.dao.JdbcDaoFactory;

/**
 * <p>Title: 龙驭网站内容管理系统核心引擎</p>
 *
 * <p>Description: 龙驭网站内容管理系统核心引擎</p>
 *
 * <p>Copyright: 北京中科辅龙计算机技术有限公司 2006</p>
 *
 * <p>Company: 北京中科辅龙计算机技术有限公司</p>
 *
 * @author <a href='mailto:lixf@fulong.com.cn'>lixf</a>
 * @version 2.0
 */
public interface AccessCounterRepositoryExt
    extends AccessCounterRepository {
    /**
     * 获取数据库联接
     * @return JdbcDaoFactory
     */
    public JdbcDaoFactory newJdbcDaoFactory();

   

}
