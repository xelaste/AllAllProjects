package com.travelfactory.candidate.catalog.controllers;

import com.travelfactory.candidate.catalog.dao.BatchRepository;
import com.travelfactory.candidate.catalog.entities.Batch;
import com.travelfactory.candidate.catalog.entities.Room;

import java.util.Arrays;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.*;
import reactor.core.publisher.Mono;

@RestController
@RequestMapping("/catalog")
public class RoomController {
    private BatchRepository repository;
    public RoomController(BatchRepository repository) 
    {
        this.repository = repository;
    }

    @GetMapping(value = "/{vendor}/{date}/{id}")
    public Mono<ResponseEntity<Room>> getBatch(@PathVariable String vendor, @PathVariable String date ,@PathVariable String id) {
        try {
    	Batch b = repository.findByVendorAndDate(vendor, date);
    	if (b==null)
    	{
    		return Mono.just(new ResponseEntity<Room>(HttpStatus.NOT_FOUND));
    	}
    	else
    	{
    		return Arrays.stream(b.getRooms()).filter(r->id.equals(r.getId())).findFirst().map(r->Mono.just(new ResponseEntity<Room>(r, HttpStatus.OK))).get().defaultIfEmpty(new ResponseEntity<Room>(HttpStatus.NOT_FOUND));
    	}
    }
    catch (Exception e)
    {
    	e.printStackTrace();
    }
        return Mono.just(new ResponseEntity<Room>(HttpStatus.NOT_FOUND));
    }
}
