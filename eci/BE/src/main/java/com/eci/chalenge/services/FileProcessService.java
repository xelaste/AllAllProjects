package com.eci.chalenge.services;

import com.eci.chalenge.verticle.CompleteSuggestionVerticle;
import com.eci.chalenge.verticle.FileProcessVerticle;
import com.eci.chalenge.verticle.TaskPublisherVerticle;
import io.vertx.core.Vertx;
import io.vertx.core.file.AsyncFile;
import io.vertx.core.file.OpenOptions;
import io.vertx.core.parsetools.RecordParser;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.stream.Stream;

@Component
public class FileProcessService {
    @Value("${user.home}/eci/IN/")
    private String inputDirectory;
    @Value("${user.home}/eci/OUT/")
    private String outputDirectory;
    private int numberOfTasks = 2;
    private int timeout = 10;
    private String prefix;
    public int getNumberOfTasks() {
        return numberOfTasks;
    }

    public String getPrefix() {
        return prefix;
    }

    public void setPrefix(String prefix) {
        this.prefix = prefix;
    }

    public void setNumberOfTasks(int numberOfTasks) {
        this.numberOfTasks = numberOfTasks;
    }

    public String getInputDirectory() {
        return inputDirectory;
    }

    public void setInputDirectory(String inputDirectory) {
        this.inputDirectory = inputDirectory;
    }

    public String getOutputDirectory() {
        return outputDirectory;
    }

    public void setOutputDirectory(String outputDirectory) {
        this.outputDirectory = outputDirectory;
    }

    public int getTimeout() {
        return timeout;
    }

    public void setTimeout(int timeout) {
        this.timeout = timeout;
    }
    public void execute() {
        try {

            File[] files = Files.walk(new File(inputDirectory).toPath()).map(Path::toFile).toArray(File[]::new);
            createOutputDirectory();
            FileProcessVerticle verticles[] = new FileProcessVerticle[numberOfTasks];
            Vertx vertx = Vertx.vertx();
            for (int i=0;i<verticles.length;i++)
            {
                verticles[i] = new FileProcessVerticle("task_" + (i+1) );
                if (i==0) {
                    vertx.deployVerticle(verticles[i], ar -> {
                        if (ar.succeeded()) {
                            TaskPublisherVerticle publisher = new TaskPublisherVerticle("publisher",files,outputDirectory);
                            vertx.deployVerticle(publisher);
                        }
                        else
                            System.out.println(ar.cause());
                    });
                }
                else
                {
                    vertx.deployVerticle(verticles[i]);
                }
            }
            CompleteSuggestionVerticle completeSuggestionVerticle = new CompleteSuggestionVerticle("CompleteSuggestion",prefix,outputDirectory);
            vertx.deployVerticle(completeSuggestionVerticle);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    private void createOutputDirectory() {
        File dir = new File(outputDirectory);
        try {
            if (dir.exists()) {
                Stream<Path> files = Files.walk(dir.toPath());
                files.map(Path::toFile).forEach(File::delete);
                dir.delete();
            }
            dir.mkdirs();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
    public static void main(String[] args) {
        FileProcessService service = new FileProcessService();
        service.setInputDirectory("C:\\Users\\alexans\\eci\\IN");
        service.setOutputDirectory("C:\\Users\\alexans\\eci\\OUT");
        service.setTimeout(10);
        service.setNumberOfTasks(3);
        service.setPrefix("all");
        service.execute();
    }
}
