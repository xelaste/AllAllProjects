package com.fronttravelfactory.exam.compaigns.model;

import javax.persistence.Entity;
import javax.persistence.FetchType;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;

import com.fasterxml.jackson.annotation.JsonIgnore;
@Entity
public class Contact 
{
	@Id 
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
	@ManyToOne(fetch = FetchType.LAZY)
	@JoinColumn(name = "campaign_id")
	private Campaign campaign;
	
	private String phone;
	private String email;
	private String name;
	
	public Contact() {super();};
	
	public Contact(Campaign campaign, String phone, String email, String name) {
		super();
		this.campaign = campaign;
		this.phone = phone;
		this.email = email;
		this.name = name;
	}
	
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	@JsonIgnore
	public Campaign getCampaign() {
		return campaign;
	}
	@JsonIgnore
	public void setCampaign(Campaign campaign) {
		this.campaign = campaign;
	}
	public String getPhone() {
		return phone;
	}
	public void setPhone(String phone) {
		this.phone = phone;
	}
	public String getEmail() {
		return email;
	}
	public void setEmail(String email) {
		this.email = email;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	
}
