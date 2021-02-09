package com.eci.chalenge.controller;

import com.eci.chalenge.rsclient.BERsClient;
import org.springframework.http.HttpStatus;
import org.springframework.http.ResponseEntity;
import org.springframework.web.bind.annotation.GetMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.RestController;

import javax.inject.Inject;

@RestController
public class UIController {
    @Inject
    private BERsClient client;

    @GetMapping("/names")
    public ResponseEntity<String> getNames(@RequestParam("prefix")String prefix, @RequestParam("threads")String threads, @RequestParam("time") String time) {
        client.getNames(prefix,threads,time).subscribe(result->{System.out.println(result.getBody().toString());});
        return new ResponseEntity<String>("Request in process subscribed", HttpStatus.OK);
    }

    @GetMapping("/reset")
    public ResponseEntity<String> reset() {
        return client.reset();
    }

}
