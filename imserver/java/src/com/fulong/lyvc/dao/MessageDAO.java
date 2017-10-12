package com.fulong.lyvc.dao;


import java.sql.SQLException;

import com.fulong.lyvc.data.MessageData;
import com.fulong.lyvc.message.MessageFormatException;
/**
 * 
 * PendingMessageSession
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-12
 */
public interface MessageDAO extends DAO{

        // Save message
        public void saveMessage(MessageData data) throws SQLException;

        // Get messages for a user
        public MessageData[] getMessages(long userId) throws SQLException, MessageFormatException;

        // Remove pending message
        public void removeMessage(long messageId) throws SQLException;
}
