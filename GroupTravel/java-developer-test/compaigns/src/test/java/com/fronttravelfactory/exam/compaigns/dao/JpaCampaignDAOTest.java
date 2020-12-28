package com.fronttravelfactory.exam.compaigns.dao;


import org.junit.jupiter.api.BeforeEach;
import org.junit.jupiter.api.Test;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.autoconfigure.jdbc.AutoConfigureTestDatabase;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.jdbc.core.JdbcTemplate;
import org.springframework.transaction.annotation.Transactional;

import com.fronttravelfactory.exam.compaigns.CompaignsApplication;
import com.fronttravelfactory.exam.compaigns.model.Campaign;
import com.fronttravelfactory.exam.compaigns.model.Contact;

import java.util.List;
import java.util.Optional;
import java.util.stream.Collectors;

import static org.hamcrest.MatcherAssert.assertThat;
import static org.hamcrest.Matchers.containsInAnyOrder;
import static org.junit.jupiter.api.Assertions.*;

@SpringBootTest(classes = CompaignsApplication.class)
@AutoConfigureTestDatabase
@Transactional
public class JpaCampaignDAOTest {

    @Autowired
    private CampaignRepository campaignDao;
    
    @Autowired
    private ContactRepository contactDao;

    @Autowired
    private JdbcTemplate template;

    @BeforeEach
    public void preTest()
    {
    	campaignDao.deleteAll();
    	Campaign campaign = new Campaign("xxx","Email,Phone"); 
    	campaignDao.save(campaign);
    	Contact contact = new Contact(campaign, "11111111", "aaa@aaa.com", "xxx_contact");
    	contactDao.save(contact);
    }
    @Test
    public void testSave() {
        
    	Campaign campaign = new Campaign("yyy","Email,Phone"); 
        campaign = campaignDao.save(campaign);
        assertNotNull(campaign.getId());
        
        Contact contact = new Contact(campaign, "11111111", "aaa@aaa.com", "yyy_contact"); 
        contact = contactDao.save(contact);
        assertNotNull(contact.getId());
    }

    @Test
    public void findOneThatExists() {
        template.query("select id from campaign", (rs, num) -> rs.getInt("id"))
                .forEach(id -> {
                    Optional<Campaign> campaign = campaignDao.findById(id);
                    assertTrue(campaign.isPresent());
                    assertEquals(id,campaign.get().getId());
                });
    }

    @Test
    public void findOneThatDoesNotExist() {
        Optional<Campaign> officer = campaignDao.findById(999);
        assertFalse(officer.isPresent());
    }

    @Test
    public void findAll() {
        List<String> dbNames = campaignDao.findAll().stream()
                                  .map(Campaign::getName)
                                  .collect(Collectors.toList());
        assertThat(dbNames, containsInAnyOrder("xxx"));
    }

    @Test
    public void count() {
        assertEquals(1, contactDao.count());
    }

    @Test
    public void delete() {
        template.query("select id from contact", (rs, num) -> rs.getInt("id"))
                .forEach(id -> {
                    Optional<Contact> contact = contactDao.findById(id);
                    assertTrue(contact.isPresent());
                    contactDao.delete(contact.get());
                });
        assertEquals(0, contactDao.count());
    }

}