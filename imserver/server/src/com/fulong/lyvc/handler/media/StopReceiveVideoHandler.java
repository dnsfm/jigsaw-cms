/**
 * 
 */
package com.fulong.lyvc.handler.media;

import com.fulong.lyvc.TCPMessage;
import com.fulong.lyvc.TCPChannel;
import com.fulong.lyvc.message.NotifyMediaServerRemoveVideo;
import com.fulong.lyvc.message.StopReceiveVideo;

/**
 * StopReceiveVideoHandler
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ���������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-13
 */
public class StopReceiveVideoHandler extends MediaBaseHandler {

	/*
	 * (non-Javadoc)
	 * 
	 * @see com.fulong.lyvc.net.Handler#execute(com.fulong.lyvc.net.TCPChannel,
	 * com.fulong.lyvc.message.BaseMessage)
	 */
	@Override
	public void execute(TCPChannel channel, TCPMessage message)throws Exception {
		this.setConferenceManager(channel.getDomain());

		StopReceiveVideo mess = (StopReceiveVideo) message;

		// ֪ͨý�������
		NotifyMediaServerRemoveVideo msgToSend = new NotifyMediaServerRemoveVideo();
		msgToSend.fromUserId = mess.receiverId;
		msgToSend.toUserId = mess.senderId;
		sendMessage(this.getMediaServer().getChannel(), msgToSend);

		// ֪ͨ�Է�
		sendMessage(mess.receiverId, message);
	}

}
