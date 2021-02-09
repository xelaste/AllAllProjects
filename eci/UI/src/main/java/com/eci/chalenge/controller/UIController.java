package com.eci.chalenge.controller;

import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;
@RestController
public class UIController {
    @GetMapping("/names")
    public ResponseEntity<String> getNames(@RequestParam("prefix")String prefix, @RequestParam("threads")String threads, @RequestParam("time") String time) {
        return new ResponseEntity<String>("Request in process", HttpStatus.OK);
    }

    @GetMapping("/reset")
    public ResponseEntity<String> reset() {
        return new ResponseEntity<String>("Request in process", HttpStatus.OK);
    }

}
