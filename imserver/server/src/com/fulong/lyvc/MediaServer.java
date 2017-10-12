package com.fulong.lyvc;

import java.io.IOException;


/**
 * 
 * MediaServer
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-12
 */
public interface MediaServer {
	/**
	 * ������IP��ַ
	 * 
	 * @return
	 */
	public String getIP();

	/**
	 * ����IP��ַ
	 * 
	 * @param ip
	 */
	public void setIP(String ip);

	/**
	 * UDP�˿�
	 * 
	 * @return
	 */
	public int getUDPPort();

	/**
	 * ����UDP�˿�
	 * 
	 * @param port
	 */
	public void setUDPPort(int port);

	/**
	 * TCP�˿�
	 * 
	 * @return
	 */
	public int getTCPPort();

	/**
	 * ����TCP�˿�
	 * 
	 * @param port
	 */
	public void setTCPPort(int port);

	/**
	 * ��ȡͨ��
	 */
	public TCPChannel getChannel();

	/**
	 * ����ͨ��
	 * 
	 * @param channel
	 */
	public void setChannel(TCPChannel channel);

	/**
	 * ����
	 * 
	 * @throws IOException
	 */
	public void start() throws IOException;
}
