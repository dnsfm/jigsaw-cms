DSO�Ľӿ��ĵ�

/*
1.�½�
*/
//�½�Word
document.all.FramerControl1.CreateNew("Word.Document");
//�½�Excel
document.all.FramerControl1.CreateNew("Excel.Sheet");
/*
2.���ļ�
*/
//���ƶ��ı����ļ�
document.all.FramerControl1.Open("C:\\TestBook.xls");
//�ƶ���Word����c:\plain.txt�ļ�
document.all.FramerControl1.Open("C:\\Plain.txt",false, "Word.Document");
//�򿪷��������ļ� 
document.all.FramerControl1.Open "https://secureserver/test/mytest.asp?id=123",true, "Excel.Sheet", "MyUserAccount", "MyPassword");
//�򿪷��������ļ� 
document.all.FramerControl1.Open("http://localhost/1.doc", true);
/*
3.�����ļ�
*/
//������
document.all.FramerControl1.Save("c:\\1.doc",true);
//������   
/*����HttpЭ��Post�ϴ��ӿ�,����Postһ����̬ҳ��(jsp,asp,php...),�ɶ�̬ҳ�渺���������
bool HttpInit();
bool HttpAddPostString(BSTR strName, BSTR strValue);
bool HttpAddPostCurrFile(BSTR strFileID, BSTR strFileName);
BSTR HttpPost(BSTR bstr);        
*/
//��ʼ��Http����
document.all.FramerControl1.HttpInit();
//����Post����
document.all.FramerControl1.HttpAddPostString("RecordID","20060102200");
document.all.FramerControl1.HttpAddPostString("UserID","��ֳ�");
//�ϴ��򿪵��ļ�
document.all.FramerControl1.HttpAddPostCurrFile("FileData", "�ĵ���.doc");
//ִ���ϴ�����
document.all.FramerControl1.HttpPost("http://xxxx.com/uploadfile.asp"); 
/*
4.�޶�����
*/
//��������״̬
document.all.FramerControl1.SetTrackRevisions(1);
//���������״̬
document.all.FramerControl1.SetTrackRevisions(0);
//���ܵ�ǰ�޶�
document.all.FramerControl1.SetTrackRevisions(4);
/*
5.���õ�ǰ�û�
*/
document.all.FramerControl1.SetCurrUserName("����");        
/*
6.���õ�ǰʱ��(�ʼ����ۻ���ʾ("Like 2006:02:07 11:11:11")
*/
document.all.FramerControl1.SetCurrTime("2006:02:07 11:11:11");
/*
7.���úʹ�����ǩ���˹��ܱȽ�ǿ��������ǩ���ݡ������ǩ����Ӻ�ͷ�ļ��Ϳ�����
SetFieldValue(BSTR strFieldName, BSTR strValue, BSTR strCmdOrSheetName)
strFieldName:��ǩ��
strValue��Ҫ���õ�ֵ
strCmdOrSheetName��
���� 
::ADDMARK::    ���BookMark
::DELMARK::          ɾ�����BookMark
::GETMARK::    ��λ�����BookMark
::FILE::                         ��������ļ�
::JPG::        �������ͼƬ
һ����˵��WORD����ǩ�����õģ�����ͨ���˽ӿڰ�����������ý���ǩ��ȥ��
*/
//�ڵ�ǰWORDλ�ò����ǩ,��ǩ��Ϊ"book1",��ֵΪ"test"
document.all.FramerControl1.SetFieldValue("book1","test","::ADDMARK::");
//������ǩ"Time",��ֵΪ"2006-03-16 22:22:22"
document.all.FramerControl1.SetFieldValue("Time","2006-03-16 22:22:22","");
//����ǩλ��"hongtou",�����ͷ�ļ�"http://222.222.222.222/hongtou1.doc" ��������ͷ���Զ����ȥ��
document.all.FramerControl1.SetFieldValue("hongtou","http://222.222.222.222/hongtou1.doc","::FILE::");
/*
8.���ò˵���ʾ���
BOOL SetMenuDisplay(long lMenuFlag)
lMenuFlagΪ������ֵ�����
#define MNU_NEW                         0x01
#define MNU_OPEN                        0x02
#define MNU_CLOSE                       0x04
#define MNU_SAVE                        0x08
#define MNU_SAVEAS                      0x16
#define MNU_PGSETUP                     0x64
#define MNU_PRINT                       0x256
#define MNU_PROPS                       0x32
#define MNU_PRINTPV                     0x126
*/
//ֻ�С��½����˵����� 
document.all.FramerControl1..SetMenuDisplay(1);
//ֻ�С��򿪡��˵����� 
document.all.FramerControl1.SetMenuDisplay(2);
//ֻ�С��򿪡��͡��½����˵����� 
document.all.FramerControl1.SetMenuDisplay(3);
/*
9.�����ĵ��ͽⱣ���ĵ�
lProOrUn:1:�����ĵ���0:�������
lProType:  
    wdNoProtection = -1,
    wdAllowOnlyRevisions = 0,
    wdAllowOnlyComments = 1,
    wdAllowOnlyFormFields = 2
strProPWD:����
*/
//��ȫ�����ĵ�������Ϊ"pwd"    
document.all.FramerControl1.ProtectDoc(1,1,"pwd");
//����ĵ�����                 
document.all.FramerControl1.ProtectDoc(0,1,"pwd");
/*
10.��ʾ�������޶�����
ShowRevisions(long nNewValue)
nNewValue = 0 �������޶�
          = 1 ����ʾ�޶�
*/
//��ʾ�޶�����
document.all.FramerControl1.ShowRevisions(1);
//�����޶�����
document.all.FramerControl1.ShowRevisions(0);
/*
11.����ϲ��ļ���
strFieldPath �ļ�·��,������http,ftp��·��
pPos = 0 //��ǰ���λ��
1;�ļ���ͷ
2;�ļ�ĩβ
pPos�ĵ�4λΪ1��ʱ�򣬴���������ͼƬ
InSertFile(BSTR strFieldPath, long lPos)
*/
//�ļ�ͷ�������ļ�
document.all.FramerControl1.InSertFile("http://XX.com/XX.doc",1);
//�ļ�β�������ļ� 
document.all.FramerControl1.InSertFile("http://XX.com/XX.doc",2);
//��ǰ���λ�ò����ļ�
document.all.FramerControl1.InSertFile("http://XX.com/XX.doc",0);
//�ļ�ͷ������ͼƬ
document.all.FramerControl1.InSertFile("http://XX.com/XX.jpg",9);
//�ļ�β������ͼƬ
document.all.FramerControl1.InSertFile("http://XX.com/XX.jpg",10);
//��ǰ���λ�ò���ͼƬ
document.all.FramerControl1.InSertFile("http://XX.com/XX.jpg",8);
/*
0x31. �ĵ����Ϊ
                HRESULT SaveAs([in] VARIANT strFileName, [in] VARIANT dwFileFormat, [out,retval] long* pbool);        
������
        strFileName���ļ�����·������c:\\11.doc
        dwFileFormat: �ļ���ʽ
dwFileFormat����ֵΪ��
Excel: Type
enum XlFileFormat
{
    xlAddIn = 18,
    xlCSV = 6,
    xlCSVMac = 22,
    xlCSVMSDOS = 24,
    xlCSVWindows = 23,
    xlDBF2 = 7,
    xlDBF3 = 8,
    xlDBF4 = 11,
    xlDIF = 9,
    xlExcel2 = 16,
    xlExcel2FarEast = 27,
    xlExcel3 = 29,
    xlExcel4 = 33,
    xlExcel5 = 39,
    xlExcel7 = 39,
    xlExcel9795 = 43,
    xlExcel4Workbook = 35,
    xlIntlAddIn = 26,
    xlIntlMacro = 25,
    xlWorkbookNormal = -4143,
    xlSYLK = 2,
    xlTemplate = 17,
    xlCurrentPlatformText = -4158,
    xlTextMac = 19,
    xlTextMSDOS = 21,
    xlTextPrinter = 36,
    xlTextWindows = 20,
    xlWJ2WD1 = 14,
    xlWK1 = 5,
    xlWK1ALL = 31,
    xlWK1FMT = 30,
    xlWK3 = 15,
    xlWK4 = 38,
    xlWK3FM3 = 32,
    xlWKS = 4,
    xlWorks2FarEast = 28,
    xlWQ1 = 34,
    xlWJ3 = 40,
    xlWJ3FJ3 = 41,
    xlUnicodeText = 42,
    xlHtml = 44
};
Word: Type
enum WdSaveFormat
{
    wdFormatDocument = 0,
    wdFormatTemplate = 1,
    wdFormatText = 2,
    wdFormatTextLineBreaks = 3,
    wdFormatDOSText = 4,
    wdFormatDOSTextLineBreaks = 5,
    wdFormatRTF = 6,
    wdFormatUnicodeText = 7,
    wdFormatEncodedText = 7,
    wdFormatHTML = 8
};
PPT:
enum PpSaveAsFileType
{
    ppSaveAsPresentation = 1,
    ppSaveAsPowerPoint7 = 2,
    ppSaveAsPowerPoint4 = 3,
    ppSaveAsPowerPoint3 = 4,
    ppSaveAsTemplate = 5,
    ppSaveAsRTF = 6,
    ppSaveAsShow = 7,
    ppSaveAsAddIn = 8,
    ppSaveAsPowerPoint4FarEast = 10,
    ppSaveAsDefault = 11,
    ppSaveAsHTML = 12,
    ppSaveAsHTMLv3 = 13,
    ppSaveAsHTMLDual = 14,
    ppSaveAsMetaFile = 15,
    ppSaveAsGIF = 16,
    ppSaveAsJPG = 17,
    ppSaveAsPNG = 18,
    ppSaveAsBMP = 19
};
*/
/*
0x32. ɾ�������ļ�
                        HRESULT DeleteLocalFile([in] BSTR strFilePath);        
������
        strFileName���ļ�����·������c:\\11.doc                        
*/                
/*
0x33.������ʱ�ļ�
                HRESULT GetTempFilePath([out,retval] BSTR* strValue);        
���أ�
    ��ʱ�ļ���·����ַ��ʹ�������DeleteLocalFile ɾ��
*/
/*
0x34.�����ĵ���ʾģʽ
                HRESULT ShowView([in] long dwViewType, [out,retval] long * pbool);        
dwViewType�Ŀ�ȡֵΪ��
enum WdViewType
{
    wdNormalView = 1,
    wdOutlineView = 2,
    wdPrintView = 3,
    wdPrintPreview = 4,
    wdMasterView = 5, //����Ǵ��
    wdWebView = 6
};
*/ 
//���ģʽ
document.all.FramerControl1.ShowView(5);
/*
0x39:����Զ���ļ�
                HRESULT DownloadFile( [in] BSTR strRemoteFile, [in] BSTR strLocalFile, [out,retval]  BSTR* strValue);        
������
         strRemoteFile��Զ��·����ַ,http or Ftp
         strLocalFile: ���ر����ַ��if strLocalFile == NULL then Create Temp File and return TempFile's Path
*/
/*
0x40������Http�ϴ�ʱ��ģ����������ļ�
                HRESULT HttpAddPostFile([in] BSTR strFileID, [in]  BSTR strFileName, [out,retval] long* pbool);
������
         strFileID���ļ���ID������������ҳ�����
         strFileName: �����ļ���ַ 
*/
/*
0x41,0x42.��ȡ��ϸ���޶���Ϣ��
   GetRevCount( [out,retval] long * pbool);
   GetRevInfo([in] long lIndex, [in]  long lType, [out,retval] BSTR* pbool);
   ��������
*/
var vCount;
vCount = document.all.FramerControl1.GetRevCount();
alert(vCount);
var vOpt = 0;
var vDate;
for(var i=1; i<= vCount; i++){
        vOpt = document.all.FramerControl1.GetRevInfo(i,2);
        if("1" == vOpt){
                vOpt = "����";
        }else if("2" == vOpt){
                vOpt = "ɾ��";
        }else{
                vOpt = "δ֪����";
        }
        vDate = new String(document.all.FramerControl1.GetRevInfo(i,1));
        vDate = parseFloat(vDate);
        alert(vDate);
        dateObj = new Date(vDate);
  alert(dateObj.getYear()   + "��" + dateObj.getMonth() + 1 + "��" + dateObj.getDate() +"��" +  dateObj.getHours() +"ʱ" +  dateObj.getMinutes() +"��" +  dateObj.getSeconds() +"��" );
        alert("�û�:"+document.all.FramerControl1.GetRevInfo(i,0) + "\r\n����:" + vOpt + "\r\n����:" + document.all.FramerControl1.GetRevInfo(i,3));
}
/*
0x43.���û�����Ϣ��
                HRESULT SetValue([in] BSTR strValue, [in]  BSTR strName, [out,retval] long* pbool);
1.�����ļ�ֻ������
        SetValue("password","::DOCPROP:PassWord");
2.�����ļ��޸�����
        SetValue("password","::DOCPROP:WritePW");
����ֵ��
0 ��ȷ
-1����֧�ִ������ȷ�����ĵڶ�������û�д���
-127:�쳣
*/
//�����ļ�ֻ������
document.all.FramerControl1.SetValue("password","::DOCPROP:PassWord");
//�����ļ��޸�����
document.all.FramerControl1.SetValue("password","::DOCPROP:WritePW");
/*
0x44.�����ĵ�����������������õ�
                HRESULT SetDocVariable([in] BSTR strVarName, [in]  BSTR strValue,[in] long lOpt, [out,retval] long* pbool);
strVarName: ������
strVlaue:����ֵ
lOpt: �������ͣ�
��λ
��һλΪ1:  ��ʾupdate�������
�ڶ�λΪ1:  ��ʾ���û��������������
����λΪ1:  δ��֧��
return:
0:OK
-127:�쳣
*/
/*
0x45: ��ҳ����
HRESULT SetPageAs([in] BSTR strLocalFile, [in]  long lPageNum, [in]  long lType,[out,retval] long* pbool);
strLocalFile������·��
lPageNum��ҳ��
*/

