package com.eci.chalenge.verticle;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Future;

import java.io.File;

public class TaskPublisherVerticle extends AbstractVerticle {
    private String name;
    private File[] files;
    private String outputDirectory;

    public TaskPublisherVerticle(String name, File[] files,  String outputDirectory) {
        this.name = name;
        this.files = files;
        this.outputDirectory = outputDirectory;
    }
    @Override
    public void start() throws Exception {
        System.out.println("SendVerticle started!");
        for (File file : files) {
            if (file.isDirectory()) {
                continue;
            }
            vertx.eventBus().send("listOfNames", file.toPath().toString() + "," + outputDirectory + "/" + file.getName());
        }
    }
}
