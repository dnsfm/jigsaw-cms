grant execute on ctx_ddl to username; --��Ȩ

--�����ʷ�������
begin 
ctx_ddl.create_preference('my_lexer','chinese_lexer');
end;