package com.fulong.process.form;

import org.apache.struts.validator.ValidatorForm;

public class NormalActivityForm extends ValidatorForm {

	private static final long serialVersionUID = -7180063317185189562L;
	private String processID;
	private String ID;
	private String name;
	
	public String getProcessID() {
		return processID;
	}
	public void setProcessID(String processID) {
		this.processID = processID;
	}
	public String getID() {
		return ID;
	}
	public void setID(String id) {
		ID = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
}
