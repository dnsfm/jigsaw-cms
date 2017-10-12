/**
 * 
 */
package com.fulong.lyvc.data;

/**
 * ConferenceDocumentData
 * 
 * ��Ԧ��Ƶ����ϵͳ v3.0
 * 
 * ��Ȩ���У������пƸ�������������ɷ����޹�˾ 2009
 * 
 * @author ���۷�
 * 
 *         ����޸�ʱ�䣺2009-3-17
 */
public class DocumentData {
	private long docId;
	private String docName;
	private String docURL;
	private String fileName;
	private long conferenceId;

	public long getConferenceId() {
		return conferenceId;
	}

	public void setConferenceId(long conferenceId) {
		this.conferenceId = conferenceId;
	}

	public long getDocId() {
		return docId;
	}

	public String getDocName() {
		return docName;
	}

	public String getDocURL() {
		return docURL;
	}

	public String getFileName() {
		return fileName;
	}

	public void setDocId(long docId) {
		this.docId = docId;
	}

	public void setDocName(String docName) {
		this.docName = docName;
	}

	public void setDocURL(String docURL) {
		this.docURL = docURL;
	}

	public void setFileName(String fileName) {
		this.fileName = fileName;
	}
}
