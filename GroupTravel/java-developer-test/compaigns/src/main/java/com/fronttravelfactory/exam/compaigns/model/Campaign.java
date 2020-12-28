package com.fronttravelfactory.exam.compaigns.model;

import java.util.ArrayList;
import java.util.List;

import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.OneToMany;

import com.fasterxml.jackson.annotation.JsonIgnore;

@Entity
public class Campaign 
{
    @Id 
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private String name;
	@OneToMany(fetch=FetchType.EAGER, cascade = CascadeType.ALL, orphanRemoval = true,mappedBy="campaign")
	private List<Contact> Contacts = new ArrayList<>();

	@Column(name = "mandatory_fields")
    private String mandatoryFields;    
	public Campaign() {super();}
	public Campaign(String name, String mandatoryFields) 
	{
		super();
		this.name = name;
		this.mandatoryFields = mandatoryFields;
	}
	
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	public String getMandatoryFields() 
	{
		return mandatoryFields;
	}
	public void setMandatoryFields(String mandatoryFields) {
		this.mandatoryFields = mandatoryFields;
	}
	
	public List<Contact> getContacts() 
	{
		return Contacts;
	}
	public void setContacts(List<Contact> contacts) {
		Contacts = contacts;
	}


	
}
