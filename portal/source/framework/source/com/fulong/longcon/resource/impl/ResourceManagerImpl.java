package com.fulong.longcon.resource.impl;

import java.io.IOException;
import java.io.InputStream;
import java.security.Principal;
import java.sql.SQLException;
import java.util.Date;

import javax.sql.DataSource;

import com.fulong.common.cache.Cache;
import com.fulong.common.cache.CacheFactory;
import com.fulong.common.dao.DaoFactory;
import com.fulong.common.dao.DatabaseException;
import com.fulong.common.dao.JdbcDaoFactory;
import com.fulong.common.dao.JdbcDaoProvider;
import com.fulong.common.dao.PropertiesDaoProvider;
import com.fulong.longcon.ItemExistsException;
import com.fulong.longcon.repository.Node;
import com.fulong.longcon.repository.NodeDefinition;
import com.fulong.longcon.repository.Repository;
import com.fulong.longcon.resource.Resource;
import com.fulong.longcon.resource.ResourceCollection;
import com.fulong.longcon.resource.ResourceIterator;
import com.fulong.longcon.resource.dao.ResourceDao;
import com.fulong.longcon.resource.data.ResourceData;
import com.fulong.longcon.resource.ext.ResourceManagerExt;
import com.fulong.longcon.security.PassportProvider;

/**
 * <p>Title: 资源管理系统</p>
 *
 * <p>Description: 资源管理系统</p>
 *
 * <p>Copyright: 北京中科辅龙计算机技术有限公司</p>
 *
 * <p>Company: 北京中科辅龙计算机技术有限公司</p>
 *
 * @author lishaobo
 * @version 1.0
 */
public class ResourceManagerImpl implements ResourceManagerExt{
    private static final String ROOT_PATH = "/resources";
    private static final String FILE_NODE_NAME = "resource";
    private static final String DIRECTORY_NODE_NAME="child";
    private static final String RESOURCE_SCHEME = "resource-scheme";
    private Cache cache;
    private CacheFactory cacheFactory;
    private DataSource datasource;
    private JdbcDaoProvider provider;
    private String dao= "oracle";
    private PassportProvider passport;
    private NodeDefinition nodeDef;
    private Resource root;
    private Repository repository;

    /**
     * 根据路径或者资源ID获取资源对象。如果文件已经存在，则获取实体对象，如果不存在，则return null;
     * @param filePath String 资源的绝对路径
     * @return Resource
     */
    public Resource getResource(String filePath) {
        if (this.cache.containsKey(filePath))
            return (Resource)this.cache.get(filePath);
        Resource resource=(Resource)this.repository.getNode(filePath);
        if(resource!=null)
            return resource;
        ResourceData data=null;
        DaoFactory factory = this.newDaoFactory();
        try {
            factory.open();
            filePath = this.format(filePath);
            ResourceDao dao = (ResourceDao) factory.getDao(ResourceDao.class);
            data = dao.getByPath(filePath);
        } catch (SQLException se) {
            throw new DatabaseException(se);
        } finally {
            factory.close();
        }
        if(data==null)
            return null;
        return (Resource)this.repository.getNode(data.getPkid());
    }

    public synchronized Resource getRootResource() {
        return this.root;
    }
/*
    private Resource loadRootResource() {
        DaoFactory factory = this.newDaoFactory();
        try {
            factory.open();
            ResourceDao dao = (ResourceDao) factory.getDao(ResourceDao.class);
            ResourceData data = dao.getByPath(ROOT_PATH);
            if (data != null)
                return new ResourceImpl(this, data);
            else {
                return null;
            }
        } catch (SQLException se) {
            throw new DatabaseException(se);
        } finally {
            factory.close();
        }

    }
*/
    /**
     * 当前owner的根目录
     * @param owner Principal
     * @return Resource
     * @throws SQLException 
     */
    public Resource getRootResource(Principal owner) throws IOException, SQLException {
        Resource resource = this.getResource(ROOT_PATH + "/" + owner.getName());
        if (resource == null) {
            resource = this.makeDir(ROOT_PATH + "/" + owner.getName());
            resource.setOwner(owner);
        }
        return resource;
    }

    /**
     * 根据父目录和文件名获取资源对象
     * @param child  String 资源的路径，相对或者绝对
     * @param parent Resource 基准路径。
     * @return Resource
     */
    public Resource getResource(Resource parent, String child) {
        String parentPath = parent.getPath();
        parentPath = this.format(parentPath);
        child = this.format(child);
        if ( (!parentPath.endsWith("/")) && (!child.startsWith("/")))
            parentPath = parentPath + "/";
        if ( (parentPath.endsWith("/")) && (child.startsWith("/")))
            parentPath = parentPath.substring(0, parentPath.length() - 1);

        String path = parentPath + child;
        return this.getResource(path);
    }

    public void setDao(String dao) {
        this.dao=dao;
    }

    public DaoFactory newDaoFactory() {
        return new JdbcDaoFactory(this.datasource, this.provider);
    }

    public DataSource getDatasource() {
        return datasource;
    }

    public void setDatasource(DataSource datasource) {
        this.datasource = datasource;
    }

    public void setProvider(JdbcDaoProvider provider) {
        this.provider = provider;
    }

    /**
     *
     * @param repository Repository
     */
    public void init() {
        PropertiesDaoProvider provider = new PropertiesDaoProvider();
        provider.addMappingFile("com.fulong.longcon.resource." + dao);
        this.provider = provider;
        this.cache=this.cacheFactory.getCache(Resource.class);
    }
    /**
     * 启动，加载根节点
     */
    public void start(){
        this.root=this.getResource(ROOT_PATH);
        if(this.root==null)
            throw new DatabaseException("Unable to found resource root. please check database setting.");
        nodeDef = this.repository.getDefinitionManager().getDefinition(
            RESOURCE_SCHEME);
    }

    public void setCacheFactory(CacheFactory cacheFactory) {
        this.cacheFactory = cacheFactory;
    }

    public void setPassport(PassportProvider passport) {
        this.passport = passport;
    }

    /**
     * 支持文件到文件的copy,文件到文件夹的copy
     * @param source Resource
     * @param dest Resource
     * @throws IOException
     */
    public void copyFile(Resource source, Resource dest) throws IOException {
        if (dest == null)
			throw new IOException();

		/* 不能把流读出再写入 */
		InputStream is = null;
		try {
			is = source.read();
			dest.write(is);
		} finally {
			if (is != null)
				is.close();
		}
		dest.setMime(source.getMime());
    }

    /**
     * source（不包括本身）下的内容（文件和文件夹）拷贝到dest下
     * 复制目录。目录下的子目录，文件同时复制
     * @param source 源目录
     * @param dest 目的目录
     * @throws IOException
     * @throws SQLException 
     */
    public void copyDirectory(Resource source, Resource dest) throws
        IOException, SQLException {
        if (dest == null)
            return;
        if ( (source.isReadOnly() == false && dest.isReadOnly() == false)) {
            ResourceCollection rc = source.getChildren(true);
            ResourceIterator ri = rc.resources();
            String nextPath;
            while (ri.hasNext()) {
                Resource rs = ri.nextResource();
                nextPath = dest.getPath() + "/" + this.getDirectory(rs);
                Resource resource = this.getResource(nextPath);
                if (resource == null) {
                    if (rs.isFile()) {
                        resource = createNewFile(nextPath);
                        this.copyFile(rs, resource);
                    } else {
                        mkdirs(nextPath);
                        this.copyDirectory(rs, resource);
                    }
                }
            }
        }
    }

    public String getDirectory(Resource rs) {
        String path = rs.getPath();
        path = this.format(path);
        int last = path.lastIndexOf("/");
        String fileDirectory = null;
        if (last > 0)
            fileDirectory = path.substring(last + 1, path.length());
        return fileDirectory;
    }
/*
    public SecurityManager getPassport() {
        return passport;
    }
 */

    public Repository getRepository() {
        return this.repository;
    }

    public JdbcDaoProvider getProvider() {
        return provider;
    }

    public PassportProvider getPassport() {
        return passport;
    }

    /**
     * 创建目录
     * @return boolean
     * @throws SQLException 
     * @throws ItemExistsException 如果该路径上对应的目录或者文件已经存在。
     */
    public Resource makeDir(String path) throws IOException, SQLException {
        path = this.format(path);
        Resource rs = this.getResource(path);
        if (rs != null)
            return rs;

        Resource parent = this.getResource(this.getParentPath(path));
        //在父目录的节点下建立新节点
        Node node =parent.addNode(nodeDef, FILE_NODE_NAME);
        Principal owner = parent.getOwner();
        DaoFactory factory = this.newDaoFactory();
        try {
            factory.open();
            ResourceDao dao = (ResourceDao) factory.getDao(ResourceDao.class);
            ResourceData data = new ResourceData();
            data.setPath(path);
            data.setPkid(node.getID());
            data.setCreationTime(new Date());
            data.setCreatorID(owner.getName());
            data.setIsFolder(true);
            data.setParentPath(this.getParentPath(path));
            if (owner != null)
                data.setOwnerID(owner.getName());
            dao.insert(data);
            Resource resource = new ResourceImpl(this, data, node);
            this.cache(resource);
            return resource;

        } catch (SQLException se) {
            factory.rollback();
            throw new DatabaseException(se);
        } finally {
            factory.close();
        }
    }

    /**
     * 创建目录，如果其父目录不存在，则同时也创建父目录
     *  including any necessary but nonexistent parent directories.
     * @return boolean
     * @throws SQLException 
     */

    public Resource mkdirs(String path) throws IOException, SQLException {
        path = this.format(path);
        Resource rs = this.getResource(path);
        if (rs != null)
            return rs;
        //父目录是否存在
        String parentPath = this.getParentPath(path);
        if (parentPath != null) {
            Resource parent = this.getResource(parentPath);
            if (parent == null)
                this.mkdirs(parentPath);
        }
        return this.makeDir(path);
    }

    /**
     * 创建文件，如果文件对应的目录不存在，则同时也创建相关的目录。
     * @return boolean 如果文件不存在，创建成功则返回true。如果文件已经存在，则返回false.
     * @throws SQLException 
     * @throws ItemExistsException 如果该路径上对应的目录或者文件已经存在。
     */
    public Resource createNewFile(String path) throws IOException, SQLException {
        String resoucePath = this.format(path);
        Resource rs = this.getResource(resoucePath);
        if (rs != null)
            return rs;

        String parentPath = this.getParentPath(resoucePath);
        //判断文件目录是否存在
        Resource dir = this.getResource(parentPath);
        if (dir == null) {
            dir = this.mkdirs(parentPath);
        }
        //在其父目录的节点下创建一个节点
        Node node = dir.addNode(nodeDef, DIRECTORY_NODE_NAME);

        DaoFactory factory = this.newDaoFactory();
        try {
            factory.open();
            ResourceDao dao = (ResourceDao) factory.getDao(ResourceDao.class);
            ResourceData data = new ResourceData();
//          if (data != null)          return new ResourceImpl(this, data);
            data.setPath(resoucePath);
            data.setPkid(node.getID());
            data.setCreationTime(new Date());
            data.setCreatorID(dir.getOwner().getName());
            data.setOwnerID(dir.getOwner().getName());
            data.setIsFolder(false);
            data.setParentPath(parentPath);
            data.setName(this.getFileName(resoucePath));
            dao.insert(data);
            Resource resource = new ResourceImpl(this, data,node);
            this.cache(resource);
            return resource;

        } catch (SQLException se) {
            factory.rollback();
            throw new DatabaseException(se);
        } finally {
            factory.close();
        }
    }



    /**
     * 删除文件或者目录。如果是删除目录，则要求这个目录为空。
     * @return boolean 删除成功
     */
    public boolean delete(Resource resource) {
        Resource rs = this.getResource(resource.getPath());
        if (rs.isDirectory()) {
            ResourceCollection rc = rs.getChildren(true);
            if (rc.resources().getSize() > 0) {
                return false;
            }
        }
        DaoFactory factory = this.newDaoFactory();
        try {
            factory.open();
            ResourceDao dao = (ResourceDao) factory.getDao(ResourceDao.class);
            dao.delete(resource.getPath());
            this.uncache(resource);
            return true;
        } catch (SQLException se) {
            factory.rollback();
            throw new DatabaseException(se);
        } finally {
            factory.close();
        }

    }

    private String getParentPath(String path) {
        path = this.format(path);
        int last = path.lastIndexOf("/");
        String parentPath = null;
        if (last > 0)
            parentPath = path.substring(0, last);
        return parentPath;
    }

    private String getFileName(String path) {
        path = this.format(path);
        int last = path.lastIndexOf("/");
        String fName = null;
        if (last > 0)
            fName = path.substring(last + 1, path.length());
        return fName;
    }

    private String format(String path) {
        String result;
        result = path.replaceAll("\\\\", "/");
        result = path.replaceAll("//", "/");
        return result;
    }

    /**
     * 删除文件或者目录.
     * @param resource Resource
     * @return boolean
     */
    public boolean deleteTree(Resource resource) {
        DaoFactory factory = this.newDaoFactory();
        try {
            factory.open();
            ResourceDao dao = (ResourceDao) factory.getDao(ResourceDao.class);
            dao.deleteTree(resource.getPath());
            this.uncache(resource);
            return true;
        } catch (SQLException se) {
            factory.rollback();
            throw new DatabaseException(se);
        } finally {
            factory.close();
        }

    }
    /**
      *
      * @param node Node
      * @return Node
      */
     public Node nodeDeleting(Node node) {
         if(node.getDefinition().isNodeType(RESOURCE_SCHEME))
         this.delete((Resource)node);
         return node;
     }

     /**
      *
      * @param node Node
      * @return Node
      */
     public Node nodeLoading(Node node) {
         if(!node.isNodeType(RESOURCE_SCHEME))
             return node;
         DaoFactory factory = this.newDaoFactory();
         try {
             factory.open();
             ResourceDao dao = (ResourceDao) factory.getDao(ResourceDao.class);
             ResourceData data = dao.getByPath(node.getID());
             if (data != null) {
                 Resource resource = new ResourceImpl(this, data, node);
                 this.cache(resource);
                 return resource;
             } else {
                 this.cache.put(node.getID(), null);
                 return null;
             }
         } catch (SQLException se) {
             throw new DatabaseException(se);
         } finally {
             factory.close();
        }
    }
    private void cache(Resource resource) {
        this.cache.put(resource.getID(), resource);
        this.cache.put(resource.getPath(), resource);
    }

    private void uncache(Resource resource) {
        this.cache.remove(resource.getID());
        this.cache.remove(resource.getPath());
    }

	@Override
	public Resource createNewFile(Resource folder, String name)
			throws IOException, SQLException {
		// TODO Auto-generated method stub
		return null;
	}
}
