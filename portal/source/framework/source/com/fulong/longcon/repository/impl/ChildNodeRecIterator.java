package com.fulong.longcon.repository.impl;

import java.sql.SQLException;
import java.util.Collection;
import java.util.Iterator;
import java.util.Vector;

import com.fulong.common.dao.DatabaseException;
import com.fulong.common.dao.JdbcDaoFactory;
import com.fulong.longcon.repository.Node;
import com.fulong.longcon.repository.NodeIterator;
import com.fulong.longcon.repository.core.InternalNode;
import com.fulong.longcon.repository.dao.NodeDao;
import com.fulong.longcon.repository.data.NodeData;
import com.fulong.longcon.repository.core.InternalRepository;

/**
 * <p>Title: 龙驭核心引擎</p>
 *
 * <p>Description: 龙驭核心引擎</p>
 *
 * <p>Copyright: 北京中科辅龙计算机技术股份有限公司 2007</p>
 *
 * <p>Company: 北京中科辅龙计算机技术股份有限公司</p>
 *
 * @author lishaobo
 * @version 1.0
 */
public class ChildNodeRecIterator implements NodeIterator<Node> {
    private InternalNode parent;
    private String name;
    private InternalRepository repository;
    private long pageSize;
    private long size;
    private Iterator<Node> nodes;
    private long position;
    public ChildNodeRecIterator(InternalNode parent,
                                InternalRepository repository) {
        this.parent = parent;
        this.repository = repository;
        this.pageSize = 20;
        this.size = -1;
        this.nodes = null;
        this.position = 0;
    }

    public ChildNodeRecIterator(InternalNode parent,
                                InternalRepository repository, String name) {
        this.parent = parent;
        this.name = name;
        this.repository = repository;
        this.pageSize = 20;
        this.size = -1;
        this.nodes = null;
        this.position = 0;
    }

    /**
     * getSize
     *
     * @return long
     * @todo Implement this com.fulong.common.util.PageIterator method
     */
    public long getSize() {
        if (this.size >= 0)
            return this.size;
        JdbcDaoFactory factory = this.repository.newJdbcDaoFactory();
        try {
            factory.open();
            NodeDao dao = (NodeDao) factory.getDao(NodeDao.class);
            if (this.name == null)
                this.size = dao.countRecByParent(this.parent.getID());
            else
                this.size = dao.countRecByParent(this.parent.getID(), this.name);
            return this.size;
        } catch (SQLException ex) {
            throw new DatabaseException(ex);
        } finally {
            factory.close();
        }

    }

    /**
     * Returns <tt>true</tt> if the iteration has more elements.
     *
     * @return <tt>true</tt> if the iterator has more elements.
     */
    public boolean hasNext() {
        return this.position < this.getSize();
    }

    /**
     * Returns the next element in the iteration.
     *
     * @return the next element in the iteration.
     */
    public Node next() {
        return this.nextNode();
    }

    /**
     * nextNode
     *
     * @return Node
     * @todo Implement this com.fulong.longcon.repository.NodeIterator method
     */
    public Node nextNode() {
        if ( (this.nodes == null) || (!this.nodes.hasNext()))
            this.populateNodes();
        this.position++;
        return (Node)this.nodes.next();

    }

    /**
     * Removes from the underlying collection the last element returned by the iterator (optional operation).
     *
     * @todo Implement this java.util.Iterator method
     */
    public void remove() {
        throw new UnsupportedOperationException();
    }

    private Iterator<Node> populateNodes() {
        Collection<Node> nodes = new Vector<Node>();
        JdbcDaoFactory factory = this.repository.newJdbcDaoFactory();
        try {
            factory.open();
            NodeDao dao = (NodeDao) factory.getDao(NodeDao.class);
            NodeData[] data;
            if (this.name == null)
                data = dao.findByParentRec(this.parent.getID(), position,
                                           pageSize);
            else
                data = dao.findByParentRec(this.parent.getID(), this.name,
                                           position,
                                           pageSize);
            for (int i = 0; i < data.length; i++) {
                nodes.add(this.repository.makeNode(data[i]));
            }

            this.nodes = nodes.iterator();
            return this.nodes;
        } catch (SQLException ex) {
            throw new DatabaseException(ex);
        } finally {
            factory.close();
        }

    }

    public void skip(long skipNum) {
        this.position += skipNum;
    }

    public long getPosition() {
        return this.position;
    }

    public void setFetchSize(long size) {
        this.pageSize = size;
    }
}
