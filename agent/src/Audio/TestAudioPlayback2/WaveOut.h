/*------------------------------------------------------------------------------*\
 =============================
   ģ������: waveout.h
 =============================

 [Ŀ��]
 
     ����waveOutXXX�������ʹ�ã�ʹ�����     
     	  
 [����]
		
	��ģ�����CWaveOut�࣬���Ǹ���װ��¼���������ࡣ   
 
 [�÷�]
   
    �����ǻ����࣬���鲻Ҫֱ��ʹ�ø���		
	 
 [������]
	
	 Winmm.lib 

 [�޸ļ�¼]
 
  �汾:    1.01.01
  ����:    01-11-1         
  ����:    Brant Q
  ��ע:
  

                                              
\*------------------------------------------------------------------------------*/
#ifndef _WAVEOUT_H_
#define _WAVEOUT_H_

void waveOutErrorMsg(MMRESULT mmr,char* szTitle);

class CWaveOut
{
public:		
	CWaveOut();
	virtual  ~CWaveOut();
	
	void SetLastMMError(MMRESULT mmr);
	MMRESULT GetLastMMError();
	
	BOOL CloseDev();
	BOOL OpenDev(WAVEFORMATEX* pfmt,DWORD dwCallback,DWORD dwCallbackInstance,DWORD fdwOpen);
	operator HWAVEOUT() const;

	static CString GetWaveOutName(UINT nIndex);
	static UINT GetWaveOutCount();
protected:

	MMRESULT m_mmr;
	HWAVEOUT m_hOut;
};


#endif