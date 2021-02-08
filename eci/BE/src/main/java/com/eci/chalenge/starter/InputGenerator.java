package com.eci.chalenge.starter;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.boot.ApplicationArguments;
import org.springframework.boot.ApplicationRunner;
import org.springframework.stereotype.Component;

import javax.annotation.Resource;
import java.io.*;
import java.nio.charset.Charset;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.Stream;

/*
    Create at least 20 CSV files in folder named: In,
    containing at least 250 lines of names. Each line will have at least 10 names.
*/
@Component
public class InputGenerator implements ApplicationRunner{
    public static final int NUMBER_OF_FILES = 20;
    public static final int FILE_SIZE = 250;
    public static final int LINE_SIZE = 10;
    public static final String FILE_NAME_PREFIX="NAMES_%d";
    @Resource (name="files")
    private List<String> lstFiles;
    @Value("${user.home}/eci/IN/")
    private String inputDirectory;
    @Value("${input.file.name}")
    private String inputFileName;
    @Override
    public void run(ApplicationArguments args) throws Exception {
        try {
            Scanner read = new Scanner(new File(inputFileName),Charset.defaultCharset().name());
            read.useDelimiter("\\s");
            Random random = new Random();
            int numberOfFiles= NUMBER_OF_FILES + random.nextInt(NUMBER_OF_FILES);
            File dir = new File ( inputDirectory );
            if (dir.exists())
            {
                Stream<Path> files = Files.walk(dir.toPath());
                files.map(Path::toFile).forEach(File::delete);
                dir.delete();
            }
            dir.mkdirs();
            while(lstFiles.size()<numberOfFiles && read.hasNext())
            {
                int currentFileSize = FILE_SIZE + random.nextInt(FILE_SIZE);
                String currentFileName = dir.getAbsolutePath() + "/" + String.format(FILE_NAME_PREFIX,lstFiles.size() + 1 ) + ".txt";
                lstFiles.add(currentFileName);
                Files.deleteIfExists(Paths.get(currentFileName));
                BufferedWriter writer = new BufferedWriter( new FileWriter(currentFileName));
                for (int i=0;i<currentFileSize;i++) {
                    int currentLineLength = LINE_SIZE + random.nextInt(LINE_SIZE);
                    List<String> lstLine = new ArrayList<>(currentLineLength);
                    for (int j=0;j<currentLineLength && read.hasNext();) {
                        String word = read.next();
                        if (word.matches("\\w+")) {
                            lstLine.add(word);
                            j++;
                        }
                    }
                    writer.write(String.join(",",lstLine) + "\n");
                }
                writer.flush();
                writer.close();
            }
            read.close();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }

    }
}
