// TestCommon.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "common/PathHelper/PathHelper.h"
#include "common/Log/Log.h"
#include "common/Base64Coder/Base64Coder.h"
#include "common/xml/xmlparser.h"

void testLog()
{
    Log::open();
    printf("%s\n", PathHelper::getApplicationRoot());
    FVS_DEBUG0("haha\n");

    printf("%s\n", PathHelper::getExeName());
    FVS_DEBUG1("haha, %d\n", 15);

    printf("%s\n", PathHelper::getIniFileFullName());
    FVS_DEBUG2("haha, %s, %d\n", "xxxx", 20);

    Log::close();
}

void testBase64Coder()
{
	FILE *file, *file2;
	string str, str2;

	//���ļ�
	file = fopen("D:\\DesktopR.exe", "rb");
	char buffer[1024];

	//��ȡ�ļ�
	size_t count = 0;
	size_t total_count = 0;
	while (!feof(file))
	{
		count = fread(buffer, sizeof(char), 1024, file);
		if(ferror(file))
		{
			break;
		}
		total_count += count;
		str.append(buffer, count);
	}

	//Base64����
	Base64Coder encoder;
	int len = str.length();
	encoder.Encode((const PBYTE)str.c_str(), len);
	str2 = encoder.EncodedMessage();

	//Base64����
	Base64Coder decoder;
	int len2 = str2.length();
	decoder.Decode((const PBYTE)str2.c_str(), len2);
	string str3;
	str3.append(decoder.DecodedMessage(), len);

	//�½��ļ�
	file2 = fopen("D:\\DesktopR_new.exe", "wb");
	//д���ļ�
	fwrite(str.c_str(), sizeof(char), str.length(), file2);
	//�ر��ļ�
	fclose(file);
	fclose(file2);
}

void testXMLParser()
{
	CXMLParser xml;
	//xml.Load("1.xml");
	//xml.SetDoc("<?xml-stylesheet type=\"text/xsl\" href=\"../leaveword.xsl\"?><wxl></wxl>");
	xml.SetDoc("<lyvc></lyvc>");
	xml.InsertElem("aaa");
	xml.Save("2.xml");
	xml.IntoElem();
	xml.AddElem("bbb", "��ά��");
	xml.Save("2.xml");
	xml.InsertElem("ccc", "");
	xml.Save("2.xml");
	xml.IntoElem();
	xml.InsertElem("ddd", "");
	xml.Save("2.xml");
	xml.InsertChildElem("eee", "���Ƿ�");
	xml.Save("2.xml");
	xml.InsertChildElem("eee", "���Ƿ�");
	xml.Save("2.xml");
	xml.InsertChildElem("fff", "�߸߹�");
	xml.Save("2.xml");
	xml.OutOfElem();
	xml.AddElem("hhh", "");
	xml.Save("2.xml");
	xml.AddChildElem("kkk", "������");
	xml.Save("2.xml");
	xml.Load( "D:\\multiserver\\src\\Client\\data\\180\\����������\\leaveword.xml" );
	string str = xml.GetMsgElemTextByIndex( "sender", 1 );
	printf( "%s", str.c_str() );
}


int _tmain(int argc, _TCHAR* argv[])
{
	testXMLParser();
	return 0;
}

