package com.eci.chalenge.services;

import io.vertx.core.Vertx;
import io.vertx.core.file.AsyncFile;
import io.vertx.core.file.OpenOptions;
import io.vertx.core.parsetools.RecordParser;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

import java.io.File;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Locale;
import java.util.Scanner;
import java.util.concurrent.LinkedBlockingQueue;

@Component
public class FileProcessService {
    @Value("${user.home}/eci/IN/")
    private String inputDirectory;
    @Value("${user.home}/eci/OUT/")
    private String outputDirectory;
    private int numberOfTasks=2;
    private int timeout=10;

    public int getNumberOfTasks() {
        return numberOfTasks;
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

    public void execute ()
    {
        Task.init(numberOfTasks);
        File files[] = new File[0];
        try {
            files = Files.walk(new File(inputDirectory).toPath()).map(Path::toFile).toArray(File[]::new);
        } catch (IOException e) {
            e.printStackTrace();
        }
        for(File file:files)
        {
            if (file.isDirectory())
            {
                continue;
            }
            Task t = Task.getTaskFromPool();
            t.execute(file.toPath().toString());
        }
    }

    public static void main(String[] args) {


    }
    private static class Task
    {
        private static LinkedBlockingQueue<Task> tasks = new LinkedBlockingQueue<>();
        public static Task getTaskFromPool()
        {
            try {
                return tasks.take();
            } catch (InterruptedException e)
            {
                throw new RuntimeException(e);
            }
        }
        public static void init (int size)
        {
            tasks.clear();
            for (int i=0;i<size;i++)
            {
                tasks.offer(new Task());
            }
        }
        public void execute(String fileName)
        {
            Vertx vertx = Vertx.vertx();
            RecordParser recordParser = RecordParser.newDelimited("\n", bufferedLine -> {
                System.out.println("bufferedLine = " + bufferedLine);
            });
            OpenOptions opts = new OpenOptions().setRead(true);
            vertx.fileSystem().open("C:\\Users\\alexans\\eci\\IN\\NAMES_1.txt", opts, ar -> {
                if (ar.succeeded()) {
                    AsyncFile file = ar.result();
                    file.handler(recordParser)
                            .exceptionHandler(Throwable::printStackTrace)
                            .endHandler(done -> {
                                tasks.offer(this);
                                vertx.close();
                            });
                } else {
                    ar.cause().printStackTrace();
                }
            });
        }
    }
}
