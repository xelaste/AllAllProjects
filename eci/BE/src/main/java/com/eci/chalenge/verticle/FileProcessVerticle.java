package com.eci.chalenge.verticle;

import io.vertx.core.AbstractVerticle;
import io.vertx.core.Future;

import java.io.*;
import java.nio.charset.Charset;
import java.util.Scanner;

public class FileProcessVerticle extends AbstractVerticle {
    private String name;
    public FileProcessVerticle (String name)
    {
        this.name = name;
    }
    @Override
    public void start() throws Exception
    {
        System.out.println(name + " started");
        vertx.eventBus().consumer("listOfNames", message -> {
            System.out.println(name + " received message.body() = " + message.body());
            String strFileNames = message.body().toString();
            String[] fileNames = strFileNames.split(",");
            vertx.executeBlocking((future)->processMessage(fileNames[0],fileNames[1]));
        });
    }
    private void processMessage (String inputFileName,String outputFileName)
    {
        try {
            Scanner read = new Scanner(new File(inputFileName), Charset.defaultCharset().name());
            read.useDelimiter("\n");
            BufferedWriter writer = new BufferedWriter( new FileWriter(outputFileName));
            while (read.hasNext())
            {
                writer.write(read.next());
                writer.write("\n");
            }
            read.close();
            new File(inputFileName).delete();
            writer.flush();
            writer.close();
            vertx.eventBus().publish("completed",inputFileName);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }


}
