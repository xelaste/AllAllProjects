package com.eci.chalenge.verticle;

import com.eci.chalenge.repository.TST;
import io.vertx.core.AbstractVerticle;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Locale;
import java.util.Scanner;

public class CompleteSuggestionVerticle extends AbstractVerticle {
    private String name;
    private String prefix;
    private String outputDirectory;

    public CompleteSuggestionVerticle(String name, String prefix, String outputDirectory) {
        this.name = name;
        this.prefix = prefix;
        this.outputDirectory = outputDirectory;
    }

    @Override
    public void start() throws Exception {
        System.out.println(name + " started");
        vertx.eventBus().consumer("CompleteSuggestion", message -> {
            System.out.println(name + " proceed output");
            vertx.executeBlocking((future) -> completeSuggestion());
        });
    }

    private void completeSuggestion() {
        TST<Integer> st = new TST<Integer>();
        File dir = new File(outputDirectory);
        try {
            int value = 0;
            File files[] = Files.walk(dir.toPath()).map(Path::toFile).toArray(File[]::new);
            for (File file : files) {
                if (file.isDirectory()) {
                    continue;
                }
                Scanner read = new Scanner(file, Charset.defaultCharset().name());
                read.useDelimiter(",|\\s");
                while (read.hasNext()) {
                    String key = read.next();
                    if (key.trim().length() > 0) {
                        st.put(key.toLowerCase(Locale.ROOT), value++);
                    }
                }
            }
            Iterable<String> answer = st.keysWithPrefix(prefix);
            BufferedWriter writer = new BufferedWriter( new FileWriter(outputDirectory + "/" + "autoCompleteSuggestion.log"));
            writer.write(answer.toString());
            writer.flush();
            writer.close();
            vertx.eventBus().send("CompleteSuggestionDone",answer.toString());
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
