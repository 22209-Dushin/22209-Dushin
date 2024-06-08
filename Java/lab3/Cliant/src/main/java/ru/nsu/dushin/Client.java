package ru.nsu.dushin;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.SocketChannel;

public class Client {
    private String ip;
    private int port;
    private String fileName;

    public Client(String ip, int port, String fileName) {
        this.ip = ip;
        this.port = port;
        this.fileName = fileName;
    }

    public void sendFile() {
        try (SocketChannel socketChannel = SocketChannel.open(new InetSocketAddress(ip, port))) {
            File file = new File(fileName);
            int fileSize = (int) file.length();

            ByteBuffer fileNameLengthBuffer = ByteBuffer.allocate(4);
            fileNameLengthBuffer.putInt(file.getName().length());
            fileNameLengthBuffer.flip();
            socketChannel.write(fileNameLengthBuffer);
            fileNameLengthBuffer.clear();

            ByteBuffer fileNameBuffer = ByteBuffer.wrap(file.getName().getBytes());
            socketChannel.write(fileNameBuffer);


            ByteBuffer fileLengthBuffer = ByteBuffer.allocate(4);
            fileLengthBuffer.putInt(fileSize);
            fileLengthBuffer.flip();
            socketChannel.write(fileLengthBuffer);
            fileLengthBuffer.clear();

            int chunkSize = 1024 * 1024;
            byte[] buffer = new byte[chunkSize];
            int bytesRead;

            try (FileInputStream fileInputStream = new FileInputStream(fileName)) {
                FileChannel fileChannel = fileInputStream.getChannel();
                while ((bytesRead = fileChannel.read(ByteBuffer.wrap(buffer))) > 0) {
                    socketChannel.write(ByteBuffer.wrap(buffer, 0, bytesRead));
                }
            } catch (IOException e) {
                e.printStackTrace();
            }

            ByteBuffer confirmationLengthBuffer = ByteBuffer.allocate(4);
            socketChannel.read(confirmationLengthBuffer);
            confirmationLengthBuffer.flip();
            int confirmationLength = confirmationLengthBuffer.getInt();

            ByteBuffer confirmationBuffer = ByteBuffer.allocate(confirmationLength);
            socketChannel.read(confirmationBuffer);
            String confirmationMessage = new String(confirmationBuffer.array());

            System.out.println("Confirmation received from the server: " + confirmationMessage);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}




