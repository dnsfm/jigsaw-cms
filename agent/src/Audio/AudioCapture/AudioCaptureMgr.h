/*
 * �����ɼ��Ľӿ���
 */

#ifndef _AudioCaptureMGR_H_
#define _AudioCaptureMGR_H_

class AudioCaptureMgr
{

public:

    // �ɼ������������Ժ�Ļص�����ԭ�Ͷ���
    typedef void (*PIO_CALLBACK)(void* pObject, WAVEHDR* pWH); 

//
// AudioCaptureMgr ���� Singletonģʽ
//
public:

    // ��ʼ��ʵ��, ���û��ָ���豸����ʹ��Ĭ���豸
    static bool create(
        PIO_CALLBACK pCallback,              // Callback function
		void* pCallbackParameter,            // Callback parameter
        int nWaveInDeviceId = WAVE_MAPPER);  // WaveIn Device Id

	// ��ʼ��ʵ��,���ļ��ж�ȡ���ݣ����豸���������£��������ԣ�
    static bool createFromFile(
        PIO_CALLBACK pCallback,     // Callback function
		void* pCallbackParameter,   // Callback parameter
        char* filename);            // Audio data file

    // ����ʵ��
    static void destroy();

private:
	AudioCaptureMgr();
	virtual ~AudioCaptureMgr();	

public:

    //
    //��׽���õ��ü����ķ�ʽ����
    //���÷����뱣֤���� startCapture�ĵ��ú� stopCapture�ĵ����������ƥ��
    //

    // ��ʼ��׽
	static bool startCapture();

    // ֹͣ��׽
	static bool stopCapture();

};

#endif 
