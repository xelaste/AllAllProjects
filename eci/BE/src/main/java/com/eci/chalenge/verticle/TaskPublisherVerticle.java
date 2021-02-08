package com.eci.chalenge.verticle;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Future;

import java.io.File;

public class TaskPublisherVerticle extends AbstractVerticle {
    private String name;
    private File[] files;
    private String outputDirectory;
    private int counter=0;
    public TaskPublisherVerticle(String name, File[] files, String outputDirectory) {
        this.name = name;
        this.files = files;
        this.outputDirectory = outputDirectory;
    }

    @Override
    public void start() throws Exception {
        System.out.println("Publisher Verticle started!");
        vertx.eventBus().consumer("completed", message -> {
            System.out.println(name + " received message.body() = " + message.body());
            counter++;
            System.out.println(name + " File " + counter + " from " + (files.length -1));
            if (counter == files.length -1 )
            {
                vertx.eventBus().send("CompleteSuggestion","Names");
            }
        });

        vertx.eventBus().consumer("CompleteSuggestionDone", message -> {
            System.out.println("All done " + message.body());
            vertx.close();
        });

        for (File file : files) {
            if (file.isDirectory()) {
                continue;
            }
            vertx.eventBus().send("listOfNames", file.toPath().toString() + "," + outputDirectory + "/" + file.getName());
        }
    }
}
