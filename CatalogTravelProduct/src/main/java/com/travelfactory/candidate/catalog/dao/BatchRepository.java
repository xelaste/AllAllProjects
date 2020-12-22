package com.travelfactory.candidate.catalog.dao;

import com.travelfactory.candidate.catalog.entities.Batch;
import org.springframework.data.mongodb.repository.MongoRepository;

public interface BatchRepository extends MongoRepository<Batch, String> 
{
	Batch findByVendorAndDate(String vendor, String date);
	
}

