#ifndef PATH_HELPER_H
#define PATH_HELPER_H

//
// ����Ӧ�ó����·����������
//
//    ���ģ��ٶ�Ӧ�ó���װ֮����ļ��в������£�
//
//    ��Ӧ�ó����Ŀ¼��
//         |
//         |---- (bin)  ��ִ�г���Ŀ¼
//         |
//         |-----(conf) ���������ļ�Ŀ¼
//		   |		|
//		   |        |---history.ini ��¼��¼
//         |
//         |-----(help) �����ļ�Ŀ¼
//         |
//         |-----(data) �����ļ�Ŀ¼
//                  |
//                  |---(received files) Ĭ�ϵ��յ��ļ�����Ŀ¼
//                  |
//					|---(��¼�û���@��������ַ) ÿ���������ϵ�ÿ���û�һ��Ŀ¼
//							|
//							|---Config.ini ÿ���û��Լ��������ļ�(Ĭ�Ϸ���������)
//							|
//							|---Server.ini ÿ���û��Լ��ķ������б�(Ĭ�Ϸ���������)
//							|
//							|---leaveword.xml �յ�������
//							|
//							|---systemmsg.xml ϵͳ����
//							|
//							|---confnotice.xml ����֪ͨ
//							|
//							|---(conference) �����еĹ�����Ϣ����Ŀ¼
//							|
//							|---(chat) ����ϵ�˵�������Ϣ����Ŀ¼
//							|
//							|---(userface) �������вλ���Ա����ʾͼƬĿ¼
//							|

class PathHelper
{
public:

    // ȡ��Ӧ�ó����Ŀ¼·��(����������\����)
    static const char* getApplicationRoot();

    // ȡ��Ӧ�ó��������
    static const char* getExeName();

    // ȡ�������ļ�������
    static const char* getIniFileFullName();

    // ȡ�ð����ļ�������
    static const char* getHelpFileFullName();

	// ȡ�����ݴ�Ÿ�Ŀ¼(��������\����)
	static const char* getDataPath();

	// ȡ�ô洢���Ե��ļ���
	static const char* getLeavewordFileFullName(const char* userName, const char* server, bool bCreateIfNotExist = false);

	// ȡ�ô洢����֪ͨ���ļ���
	static const char* getConfNoticeFileFullName(const char* userName, const char* server, bool bCreateIfNotExist = false);

	// ȡ�ô洢ϵͳ��Ϣ���ļ���
	static const char* getSystemMessageFileFullName(const char* userName, const char* server, bool bCreateIfNotExist = false);

	// ȡ��Ĭ�ϵĽ����ļ���ŵ�Ŀ¼
    static const char* getDefaultReceivedFilePath();

	// ȡ��������Ϣ��ŵ�Ŀ¼
	static const char* getChatMsgPath( const char* userName, const char* server );

	// ȡ�û������ּ�¼��ŵ�Ŀ¼
	static const char* getConferenceMsgPath( const char* userName, const char* server );

	// ȡ���û����������ͷ���Ŀ¼
	static const char* getUserFacePath( const char* userName, const char* server );

	// ȡ�ø��������ļ�
	static const char* getUserPrivateConfigFile( const char* userName, const char* server );

	// ȡ�ø��˵����ݴ��Ŀ¼
	static const char* getUserDataPath( const char* userName, const char* server, bool bCreateIfNotExist = true );

	// ȡ�÷������б��ļ�
	static const char* getUserServerListFile( const char* userName, const char* server, bool bCreateIfNotExist = true );

	// �ж��ļ��Ƿ����
	static BOOL isFileExist(const char* fileFullName);

	// �õ���¼��¼���ļ�,û�о��ȴ���
	static const char* getLoginHistoryFile();

	// �ж�Ŀ¼�Ƿ����
	static BOOL isDirectoryExist(const char* dir);
private:
	// ����Ŀ¼
	static BOOL createDirectory(const char* dir);
	// �����ļ�
	static BOOL createFile(const char* fileFullName);

};

#endif
