@echo off
echo ��ȷ���Ѿ�������JAVA_HOME��������
set JAVA_BIN=%JAVA_HOME%\bin
set JAVA_KEYTOOL=%JAVA_BIN%\keytool
echo ɾ���Ѿ����ڵ�֤��
rem keytool -delete -alias coolink -keystore %JAVA_HOME%/jre/lib/security/cacerts -storepass fulong
rem keytool -delete -alias coolink -storepass fulong -keystore coolink.keystore
echo ������������֤�飺(ע������֤��ʱ��CNҪ�ͷ�������������ͬ������ڱ��ز��ԣ���ʹ��localhost)   
%JAVA_KEYTOOL% -genkey -alias coolink -keyalg RSA -keysize 1024 -validity 70000 -dname "CN=egotour.coolink.cn, OU=coolink.cn, O=coolink.cn, L=Beijing, S=Beijing, C=SE" -keypass fulong -storepass fulong -keystore coolink.keystore
echo ����֤�飬�ɿͻ��˰�װ
%JAVA_KEYTOOL% -export -alias coolink -keystore coolink.keystore -file coolinkcerts.cer -storepass fulong   
echo �ͻ������ã�Ϊ�ͻ��˵�JVM������Կ(���������·���֤�鵼�뵽JVM��) 
%JAVA_KEYTOOL% -import -trustcacerts -alias coolink -keystore "%JAVA_HOME%/JRE/LIB/SECURITY/cacerts" -file coolinkcerts.cer -storepass fulong



