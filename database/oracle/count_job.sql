--ÿ��������ͳ�ƹ��̵�job

declare job number;
begin
  sys.dbms_job.submit( job,
                      'pro_count_new();',
                       Sysdate,
                       'TRUNC(sysdate) + 1');
  commit;
end;
/
--ÿ��һ����÷�������̵�job
declare job number;
begin
  sys.dbms_job.submit( job,
                      'analyzealltable();',
                       Sysdate,
                       'TRUNC(sysdate) + 1 +1/ (24)');
  commit;
end;
/