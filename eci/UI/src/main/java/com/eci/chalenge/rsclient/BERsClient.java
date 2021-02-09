package com.eci.chalenge.rsclient;

import com.fasterxml.jackson.annotation.JacksonInject;
import io.reactivex.Single;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.web.client.RestTemplateBuilder;
import org.springframework.http.ResponseEntity;
import org.springframework.stereotype.Component;
import org.springframework.web.client.RestTemplate;

import javax.inject.Inject;
import java.util.concurrent.TimeUnit;

@Component
public class BERsClient
{
    @Value("${be.url}")
    private String providerURL;
    @Inject
    private RestTemplateBuilder templateBuilder;

    public Single<ResponseEntity<String>> getNames (String prefix, String threads, String time)
    {
        RestTemplate template = templateBuilder.build();
        String url = providerURL +"/names/?threads={threads}&time={time}&prefix={prefix}";
        return Single.create( subsriber -> template.getForEntity(url,String.class,threads,time,prefix));
    }
    public ResponseEntity<String> reset ()
    {
        RestTemplate template = templateBuilder.build();
        String url = providerURL +"/reset";
        return template.getForEntity(url,String.class);
    }

}
