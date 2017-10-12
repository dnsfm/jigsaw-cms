-- Create table
create table SITE_DOMAIN_TEMPLATE
(
  SITEID     VARCHAR2(128) not null,
  TMEPLATEID VARCHAR2(32) not null,
  NAVIGATE   VARCHAR2(1) default 0 not null
)
tablespace CL
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
comment on column SITE_DOMAIN_TEMPLATE.SITEID
  is '��վid';
comment on column SITE_DOMAIN_TEMPLATE.TMEPLATEID
  is 'ģ��id';
comment on column SITE_DOMAIN_TEMPLATE.NAVIGATE
  is '����ģ��Ϊ''1'',Ĭ��Ϊ''0''';
-- Create/Recreate primary, unique and foreign key constraints 
alter table SITE_DOMAIN_TEMPLATE
  add constraint DOMAIN_TEMPLATE_PK primary key (SITEID, TMEPLATEID)
  using index 
  tablespace CL
  pctfree 10
  initrans 2
  maxtrans 255
  storage
  (
    initial 64K
    minextents 1
    maxextents unlimited
  );


alter table site drop column tmeplate_id