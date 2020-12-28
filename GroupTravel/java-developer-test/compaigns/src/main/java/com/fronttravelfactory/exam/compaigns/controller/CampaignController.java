package com.fronttravelfactory.exam.compaigns.controller;

import java.util.Arrays;
import java.util.List;
import java.util.Optional;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpStatus;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.ResponseStatus;
import org.springframework.web.bind.annotation.RestController;
import org.springframework.web.server.ResponseStatusException;

import com.fronttravelfactory.exam.compaigns.dao.CampaignRepository;
import com.fronttravelfactory.exam.compaigns.dao.ContactRepository;
import com.fronttravelfactory.exam.compaigns.model.Campaign;
import com.fronttravelfactory.exam.compaigns.model.Contact;
import com.fronttravelfactory.exam.compaigns.model.ContactFields;

@RestController
public class CampaignController 
{
	private static final String PHONE_REGEX="^[+]*[(]{0,1}[0-9]{1,4}[)]{0,1}[-\\s\\./0-9]*$";
	private static final String EMAIL_REGEX="^[\\w-.]+@([\\w-]+.)+[\\w-]{2,4}$";
	@Autowired
	private CampaignRepository campaignRepository;
	
	@Autowired
	private ContactRepository contactRepository;
	
	@ResponseBody
	@RequestMapping(value = "/marketing/ws/partner/campaign", method = RequestMethod.POST)
	public Campaign saveCampaign(@RequestBody Campaign campaign, HttpServletRequest request, HttpServletResponse response) 
	{
		return campaignRepository.save(campaign);
	}

	@ResponseBody
	@RequestMapping(value = "/marketing/ws/partner/campaign", method = RequestMethod.GET)
	public List<Campaign> searchAllCampaign(HttpServletRequest request, HttpServletResponse response) 
	{
		return campaignRepository.findAll();
	}
	@ResponseBody
	@RequestMapping(value = "/marketing/ws/partner/campaign/{campaignID}/register", method = RequestMethod.POST)
	@ResponseStatus(HttpStatus.OK) 
	public Contact saveContact(@RequestBody Contact contact, @PathVariable("campaignID") Integer campaignID, HttpServletRequest request, HttpServletResponse response) 
	{
		Optional<Campaign> campaign = campaignRepository.findById(campaignID);
		if (campaign.isPresent())
		{
			String mandatoryFields = campaign.get().getMandatoryFields();
			contact.setCampaign(campaign.get());
			ContactFields[] fields = (mandatoryFields != null) ? Arrays.stream(mandatoryFields.split(",")).map(s->ContactFields.valueOf(s)).toArray(ContactFields[]::new): new ContactFields[0];
			String phone = contact.getPhone();
			String email = contact.getEmail();
			for (int i = 0; i < fields.length; i++) 
			{
				switch (fields[i]) 
				{
					case Phone:
						
						if (phone==null || !phone.matches(PHONE_REGEX))
						{
							throw new ResponseStatusException(
									  HttpStatus.BAD_REQUEST, "wrong phone number " + phone
									);
						}
						break;
					case Email:
						
						if (email==null || !email.matches(EMAIL_REGEX))
						{
							throw new ResponseStatusException(
									  HttpStatus.BAD_REQUEST, "wrong email " + email
									);
						}
						break;

				default:
					break;
				}
			}
			if (email != null && contactRepository.findByEmail(email).size()>0)
			{
				throw new ResponseStatusException(
						HttpStatus.CONFLICT, "email exists already" + email
						);
			}
			if (phone != null && contactRepository.findByPhone(phone).size()>0)
			{
				throw new ResponseStatusException(
						  HttpStatus.CONFLICT, "phone exists already" + phone
						);
			}

			return contactRepository.save(contact);
		}
		else
		{
			throw new ResponseStatusException( HttpStatus.BAD_REQUEST, "wrong campaign " + campaignID);
		}
	}
	
}
