# USE `coolinkclean_new`;

#
# Source for table node_view
#

DROP TABLE IF EXISTS `node_view`;
CREATE TABLE `node_view` (
  `nodefid` varchar(128) NOT NULL DEFAULT '' COMMENT 'ָ����ĳ����ٵ�����',
  `prodefid` varchar(128) NOT NULL DEFAULT '' COMMENT 'ָ����ĳ����ٶ��������Զ��������',
  `width` decimal(22,0) DEFAULT NULL COMMENT '������ʾ��Ҫ�Ŀ��',
  `orderno` decimal(22,0) DEFAULT NULL COMMENT '������ʾ�����'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Source for table nodedef_processdef
#

DROP TABLE IF EXISTS `nodedef_processdef`;
CREATE TABLE `nodedef_processdef` (
  `node_definition` varchar(128) NOT NULL DEFAULT '' COMMENT '��ٵ�pkid',
  `process_definition` varchar(128) DEFAULT NULL COMMENT '��������pkid'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

#
# Source for table node_definition_authorization
#

DROP TABLE IF EXISTS `node_definition_authorization`;
CREATE TABLE `node_definition_authorization` (
  `principal_id` varchar(32) NOT NULL DEFAULT '' COMMENT '��Ȩ��ID��/�û�/������ID',
  `principal_type` decimal(22,0) DEFAULT NULL COMMENT '�����ͣ�1���û���2��������3������Ȩ������',
  `definition_id` varchar(128) NOT NULL DEFAULT '' COMMENT '���ID',
  `action` varchar(16) NOT NULL DEFAULT '' COMMENT '����manage������read����create������modify���޸�delete��ɾ��'
) ENGINE=InnoDB DEFAULT CHARSET=utf8;



#
# Source for procedure pro_copy_NodeDefinition
#

DROP PROCEDURE IF EXISTS `pro_copy_NodeDefinition`;
CREATE DEFINER=`root`@`%` PROCEDURE `pro_copy_NodeDefinition`(
  in sourceID Varchar(256),  
  in destID   Varchar(256)
)
BEGIN
	
Insert Into nodedef_processdef (node_definition,process_definition)
Select destID ,process_definition
From nodedef_processdef x
Where x.node_definition =sourceID;

Insert Into node_definition_authorization (principal_id,principal_type,definition_id,action)
Select principal_id,principal_type,destID,action
From node_definition_authorization x
Where x.definition_id =sourceID;


Insert Into node_view (nodefid, prodefid, width, orderno)
Select destID,prodefid,width,orderno
From node_view x
Where x.nodefid =sourceID;
END;