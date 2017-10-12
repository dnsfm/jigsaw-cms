-- Create table
create table NODE_DEFINITION_SUPER
(
  DEFINITION_ID VARCHAR2(128),
  SUPER_ID      VARCHAR2(128),
  TYPE          CHAR(1) default 0 not null
)
tablespace COOLINKCMS
  pctfree 10
  initrans 1
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );
-- Add comments to the columns 
comment on column NODE_DEFINITION_SUPER.DEFINITION_ID
  is '���ݷ���ID';
comment on column NODE_DEFINITION_SUPER.SUPER_ID
  is '������ID';
comment on column NODE_DEFINITION_SUPER.TYPE
  is '�Ƿ�����������.1:�������ࣻ0����������';
