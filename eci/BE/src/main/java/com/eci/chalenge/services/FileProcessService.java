package com.eci.chalenge.services;

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
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Locale;
import java.util.Scanner;
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

    public void execute() {
        Task.init(numberOfTasks);
        File files[] = new File[0];
        try {
            files = Files.walk(new File(inputDirectory).toPath()).map(Path::toFile).toArray(File[]::new);
        } catch (IOException e) {
            e.printStackTrace();
        }
        createOutputDirectory();
        for (File file : files) {
            if (file.isDirectory()) {
                continue;
            }
            Task t = Task.getTaskFromPool();
            System.out.println("****************************");
            System.out.println(file.toPath().toString());
            System.out.println("****************************");
            try {
                t.execute(file.toPath().toString(), outputDirectory + "/" + file.getName());
            } catch (Exception e) {
                e.printStackTrace();
            }
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
        service.execute();
    }

    private static class Task {
        private int id;
        private static LinkedBlockingQueue<Task> tasks = new LinkedBlockingQueue<>();

        public static Task getTaskFromPool() {
            try {
                return tasks.take();
            } catch (InterruptedException e) {
                throw new RuntimeException(e);
            }
        }

        public static void init(int size) {
            tasks.clear();
            for (int i = 0; i < size; i++) {
                Task t = new Task();
                t.id = i + 1;
                tasks.offer(t);
            }
        }

        public void execute(String inputFileName, String outputFileName) throws Exception {
            Vertx vertx = Vertx.vertx();
            BufferedWriter fw = new BufferedWriter(new FileWriter(new File(outputFileName)));
            RecordParser recordParser = RecordParser.newDelimited("\n", bufferedLine -> {
                try {
                    fw.write(bufferedLine.toString() + "\n");
                } catch (IOException e) {
                    e.printStackTrace();
                }
            });

            OpenOptions opts = new OpenOptions().setRead(true);
            vertx.fileSystem().open(inputFileName, opts, ar -> {
                if (ar.succeeded()) {
                    AsyncFile file = ar.result();
                    file.handler(recordParser)
                            .exceptionHandler(Throwable::printStackTrace)
                            .endHandler(done -> {
                                tasks.offer(this);
                                try {
                                    fw.close();
                                } catch (IOException e) {
                                    e.printStackTrace();
                                }
                                vertx.close();
                            });
                } else {
                    ar.cause().printStackTrace();
                }
            });
        }
    }
}
