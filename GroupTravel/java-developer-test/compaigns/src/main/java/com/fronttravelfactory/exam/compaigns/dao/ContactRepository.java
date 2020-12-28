package com.fronttravelfactory.exam.compaigns.dao;

import java.util.List;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.fronttravelfactory.exam.compaigns.model.Campaign;
import com.fronttravelfactory.exam.compaigns.model.Contact;

@Repository
public interface ContactRepository extends JpaRepository<Contact, Integer>  
{
	List <Contact> findByPhone(String phone);
	List <Contact> findByEmail(String email);
}
