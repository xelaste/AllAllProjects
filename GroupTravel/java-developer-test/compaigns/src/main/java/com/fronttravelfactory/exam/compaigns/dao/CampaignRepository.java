package com.fronttravelfactory.exam.compaigns.dao;

import org.springframework.data.jpa.repository.JpaRepository;
import org.springframework.stereotype.Repository;

import com.fronttravelfactory.exam.compaigns.model.Campaign;

@Repository
public interface CampaignRepository extends JpaRepository<Campaign, Integer>  
{

}
