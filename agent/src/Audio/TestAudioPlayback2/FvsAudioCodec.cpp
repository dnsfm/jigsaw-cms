// FvsAudioCodec.cpp: implementation of the FvsAudioCodec class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "FvsAudioCodec.h"
#include "../AudioCodec/g729a.h"
#include "../AudioCommon/AudioCommon.h"


#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FvsAudioCodec::FvsAudioCodec()
{
	va_g729a_init_encoder();
	va_g729a_init_decoder();
}

FvsAudioCodec::~FvsAudioCodec()
{
}

BOOL FvsAudioCodec::EncodeAudioData(char *pin, int len, char *pout, int *lenr)
{
	BOOL bRet=FALSE;
	if (!pin || len != AudioCommon::SIZE_AUDIO_FRAME || !pout)
		goto RET;
	
	va_g729a_encoder((short*)pin,(BYTE*)pout);
	va_g729a_encoder((short*)(pin+160),(BYTE*)pout+10);
	va_g729a_encoder((short*)(pin+320),(BYTE*)pout+20);
	va_g729a_encoder((short*)(pin+480),(BYTE*)pout+30);
	va_g729a_encoder((short*)(pin+640),(BYTE*)pout+40);
	va_g729a_encoder((short*)(pin+800),(BYTE*)pout+50);

	if (lenr)
		*lenr=60;

	bRet=TRUE;
RET:
	return bRet;

}
BOOL FvsAudioCodec::DecodeAudioData(char *pin, int len, char *pout, int *lenr)
{
	
	BOOL bRet=FALSE;
	if (!pin||len!=60||!pout)
		goto RET;

	va_g729a_decoder((BYTE*)pin,(short*)(pout),0);
	va_g729a_decoder((BYTE*)pin+10,(short*)(pout+160),0);
	va_g729a_decoder((BYTE*)pin+20,(short*)(pout+320),0);
	va_g729a_decoder((BYTE*)pin+30,(short*)(pout+480),0);
	va_g729a_decoder((BYTE*)pin+40,(short*)(pout+640),0);
	va_g729a_decoder((BYTE*)pin+50,(short*)(pout+800),0);

	if (lenr)
		*lenr=AudioCommon::SIZE_AUDIO_FRAME;
	
	bRet=TRUE;
RET:
	return bRet;	
}