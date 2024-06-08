package ru.nsu.dushin;

import java.io.*;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.FileChannel;
import java.nio.channels.SocketChannel;

public class Main {
    public static void main(String[] args) {
        if (args.length < 3) {
            System.err.println("Usage: java Client <server_ip> <port> <file_name>");
            System.exit(1);
        }

        String ip = args[0];
        int port = Integer.parseInt(args[1]);
        String fileName = args[2];

        Client client = new Client(ip, port, fileName);
        client.sendFile();
    }
}





