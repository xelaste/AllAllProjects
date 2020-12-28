package com.fronttravelfactory.exam.compaigns.controller;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.boot.test.web.client.TestRestTemplate;
import org.springframework.http.HttpStatus;
import org.springframework.http.MediaType;
import org.springframework.http.ResponseEntity;
import com.fronttravelfactory.exam.compaigns.CompaignsApplication;
import com.fronttravelfactory.exam.compaigns.dao.CampaignRepository;
import com.fronttravelfactory.exam.compaigns.dao.ContactRepository;
import com.fronttravelfactory.exam.compaigns.model.Campaign;
import com.fronttravelfactory.exam.compaigns.model.Contact;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotNull;
import static org.junit.jupiter.api.Assertions.assertTrue;

import java.util.List;

import org.junit.jupiter.api.AfterEach;
import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;

@SpringBootTest(classes = CompaignsApplication.class, webEnvironment = SpringBootTest.WebEnvironment.RANDOM_PORT)
@AutoConfigureTestDatabase
public class CampaignControllerTest {

	@Autowired
    private TestRestTemplate template;

    @Autowired
    private CampaignRepository campaignDao;
    
    @Autowired
    private ContactRepository contactDao;
    @BeforeEach
    public void preTest()
    {
    	contactDao.deleteAll();
    	campaignDao.deleteAll();
    }
    
    @AfterEach
    public void postTest()
    {
    	contactDao.deleteAll();
    	campaignDao.deleteAll();
    }

    @Test
    public void save() 
    {
    	Campaign campaign = new Campaign("xxx","Email,Phone"); 
    	ResponseEntity<Campaign> response = template.postForEntity("/marketing/ws/partner/campaign", campaign, Campaign.class);
        assertNotNull(response.getBody().getId());
        Integer id = response.getBody().getId();
        Contact contact = new Contact(campaign, "11111111", "aaa@aaa.com", "yyy_contact"); 
        ResponseEntity<Contact> contactResponseEntity = template.postForEntity(String.format("/marketing/ws/partner/campaign/%d/register", id), contact, Contact.class);
        assertNotNull(contactResponseEntity.getBody().getId());

    }
    
    @Test
    public void getCampaignList() 
    {
    	
    	save();
    	ResponseEntity<List> entity = template.getForEntity("/marketing/ws/partner/campaign",  List.class);
        assertEquals(HttpStatus.OK, entity.getStatusCode());
        assertEquals(MediaType.APPLICATION_JSON, entity.getHeaders().getContentType());
        assertTrue(entity.getBody().size()>0);
    }

}