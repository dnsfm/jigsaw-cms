/**
 * 
 */
package com.fulong.lyvc;


/**
 * ConferenceLibraryMessageHandler
 *
 * ��Ԧ��Ƶ����ϵͳ v3.0
 *
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 *
 * @author ���۷�
 *
 * ����޸�ʱ�䣺2009-3-13
 */
public abstract class MessageHandler extends Handler{
	/**
	 * 
	 * @param messageBody
	 */
	 public abstract void execute(String messageBody) throws Exception;
	 
	
}
