package com.eci.chalenge.controllers;

import com.eci.chalenge.services.FileProcessService;
import com.eci.chalenge.starter.InputGenerator;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.inject.Inject;

@RestController
public class BEServerController
{
    @Inject
    FileProcessService service;

    @Inject
    InputGenerator generator;
    /*
        http://localhost:8080/names?threads=5&time=10&prefix=Ale"
     */
    @GetMapping("/names")
    public ResponseEntity<String>  getNames(@RequestParam("prefix")String prefix, @RequestParam("threads")String threads, @RequestParam("time") String time) {
        if ( prefix == null  || threads == null || time == null )
        {
            return new ResponseEntity<>("Invalid Input usage http://localhost:8080/names?threads=5&time=10&prefix=Ale", HttpStatus.BAD_REQUEST);
        }
        try {
            service.setTimeout(Integer.parseInt(time));
            service.setNumberOfTasks(Integer.parseInt(threads));
            service.execute();
        }
        catch (Exception e)
        {
            return new ResponseEntity<>("Server Error usage http://localhost:8080/names?threads=5&time=10&prefix=Ale", HttpStatus.BAD_REQUEST);
        }
        return new ResponseEntity<String>("Request in process", HttpStatus.OK);
    }
    @GetMapping("/reset")
    public  ResponseEntity<String> reset() {
        try {
            generator.run(null);
        } catch (Exception e) {
            e.printStackTrace();
            return new ResponseEntity<>("Server Error usage http://localhost:8080/names?threads=5&time=10&prefix=Ale", HttpStatus.BAD_REQUEST);
        }
        return new  ResponseEntity<String> ("reset completed",HttpStatus.OK);
    }

}
