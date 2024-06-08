package ru.nsu.dushin;

import java.io.*;

class RecordManager {
    static private int record;
    public static int getRecord() { return record; }
    public static int loadRecord() {
        try {
            InputStream inputStream = RecordManager.class.getResourceAsStream("/record.txt");
            if (inputStream != null) {
                BufferedReader reader = new BufferedReader(new InputStreamReader(inputStream));
                String line = reader.readLine();
                reader.close();
                record = Integer.parseInt(line);
                return Integer.parseInt(line);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
        return 0;
    }

    public static void saveRecord(int newRecord) {
        record = newRecord;
        try {
            OutputStream outputStream = new FileOutputStream(RecordManager.class.getResource("/record.txt").getFile());
            BufferedWriter writer = new BufferedWriter(new OutputStreamWriter(outputStream));
            writer.write(String.valueOf(record));
            writer.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
