Mysql���������ݿⲿ��

1.����init1.0.3.sql����ṹ�����ã��������ʼ����(�������������ʹ��MySQL-Front 5.1),�洢�������޸�`root`@`%`

2.count_job.sqlΪ����ͳ��job��sql��optimize_job.sqlΪ���Ż�job��sql��ִ�д�sql����δ����event_scheduler��
  ��ִ��set GLOBAL event_scheduler=on

����1.�������NODE_DEFINITION_SUPER��, ��ִ��pro_insert(update)_nodedefinition.sql
      ���޸�pro_insert(update)_NodeDefinition�洢����

    2.����ʹ��pro_copy_NodeDefinition�洢���̣���ִ��pro_copy_nodedefinition.sql
      �����NODEDEF_PROCESSDEF��NODE_DEFINITION_AUTHORIZATION��NODE_VIEW��

    3.����ʹ��TR_NodeDefinition_INSERT����������ִ��tr_nodedefinition_insert.sql
      �����NODE_QUOTA��

Packet for query is too large����
�����������my.ini���[mysqld]�������²��� (����������������ÿɲο�my_?.ini)
[mysqld] 
max_allowed_packet=64M(��С�ɵ�)

��oracle����mysql���Ȱѱ��collation-server��Ϊutf8_general_ci���ٵ������ݣ���������.
mysql�ı���ֱ����mysql-front�еĵ���Ϊsql�ļ�����
