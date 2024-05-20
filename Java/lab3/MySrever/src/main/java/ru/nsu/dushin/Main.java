package ru.nsu.dushin;

import java.io.IOException;

public class Main {
    public static void main(String[] args) {

        SocketServer server = new SocketServer(8080);
        try {
            server.start();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}