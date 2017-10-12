--ÿ��������ͳ�ƹ��̵�job
# set GLOBAL event_scheduler=on ;

CREATE EVENT `count_job` ON SCHEDULE 
EVERY 1 DAY 
STARTS concat(date_format(now(),'%Y-%m-%d'),' 00:00:00')
ON COMPLETION NOT PRESERVE ENABLE COMMENT 'ÿ��������ͳ�ƹ��̵�job'
DO 
  call pro_count_new();

--ÿ��һ���Ż����job

CREATE EVENT `optimize_job` ON SCHEDULE 
EVERY 1 MONTH 
STARTS concat(date_format(now(),'%Y-%m-%d'),' 00:00:00')
ON COMPLETION NOT PRESERVE ENABLE COMMENT '--ÿ��һ���Ż����job'
DO 
  call optimize_all_tables(