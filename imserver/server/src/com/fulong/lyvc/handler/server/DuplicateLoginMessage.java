package com.fulong.lyvc.handler.server;

import com.fulong.lyvc.TCPChannel;
import com.fulong.lyvc.message.Login;
/**
 * 
 * DuplicateLoginMessage
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-13
 */
public class DuplicateLoginMessage {
    public TCPChannel channel;
    public Login loginMessage;
}
