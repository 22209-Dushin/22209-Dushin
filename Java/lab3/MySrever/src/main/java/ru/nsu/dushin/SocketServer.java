package ru.nsu.dushin;

import java.io.FileOutputStream;
import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.ByteBuffer;
import java.nio.channels.SelectionKey;
import java.nio.channels.Selector;
import java.nio.channels.ServerSocketChannel;
import java.nio.channels.SocketChannel;
import java.util.HashMap;
import java.util.Iterator;

import static java.lang.Math.min;

public class SocketServer {
    private Selector selector;
    private int port;
    private HashMap<SocketChannel, Client> clients;

    public SocketServer(int port) {
        this.port = port;
        this.clients = new HashMap<>();
    }
    public void start() throws IOException {
        this.selector = Selector.open();
        ServerSocketChannel serverSocketChannel = ServerSocketChannel.open();
        serverSocketChannel.bind(new InetSocketAddress(this.port));
        serverSocketChannel.configureBlocking(false);
        serverSocketChannel.register(this.selector, SelectionKey.OP_ACCEPT);

        System.out.println("Server started...");

        while (true) {
            this.selector.select();
            Iterator<SelectionKey> keys = this.selector.selectedKeys().iterator();
            while(keys.hasNext()) {
                SelectionKey key = keys.next();
                keys.remove();
                if (!key.isValid()) continue;
                if (key.isAcceptable()) accept(key);
                else if (key.isReadable()) read(key);
            }
        }
    }

    private void accept(SelectionKey key) throws IOException {
        ServerSocketChannel serverSocketChannel = (ServerSocketChannel) key.channel();
        SocketChannel channel = serverSocketChannel.accept();
        channel.configureBlocking(false);
        channel.register(this.selector, SelectionKey.OP_READ);
        this.clients.put(channel, new Client(channel));
    }

    private void read(SelectionKey key) throws IOException{
        Client client = this.clients.get(key.channel());
        SocketChannel channel = client.getChannel();
        if (client.getState() == ClientState.LENGTH_NAME && channel.socket().getInputStream().available() >= 4) {
            ByteBuffer lengthNameBuffer = ByteBuffer.allocate(4);
            channel.read(lengthNameBuffer);
            client.setFileNameLength(ByteBuffer.wrap(lengthNameBuffer.array()).getInt());
            client.setState(ClientState.NAME);
        }
        if (client.getState() == ClientState.NAME && channel.socket().getInputStream().available() >= client.getFileNameLength()) {
            ByteBuffer NameBuffer = ByteBuffer.allocate(client.getFileNameLength());
            channel.read(NameBuffer);
            client.setFileName(new String(NameBuffer.array()));
            client.setState(ClientState.LENGTH_FILE);
        }
        if (client.getState() == ClientState.LENGTH_FILE && channel.socket().getInputStream().available() >= 4) {
            ByteBuffer lengthFileBuffer = ByteBuffer.allocate(4);
            channel.read(lengthFileBuffer);
            client.setRemainingBytes(ByteBuffer.wrap(lengthFileBuffer.array()).getInt());
            client.setState(ClientState.FILE);
        }
        if (client.getState() == ClientState.FILE) {
            while(channel.socket().getInputStream().available() >= min(client.getRemainingBytes(), 1024 * 1024)) {
                int bytesRead = channel.read(client.getBuffer());
                client.decreaseRemainingBytes(bytesRead);
                try (FileOutputStream fileOutputStream = new FileOutputStream(client.getFileName(), true)) {
                    fileOutputStream.getChannel().position(fileOutputStream.getChannel().size());
                    fileOutputStream.write(client.getBuffer().array(), 0, bytesRead);
                }
                if (client.getRemainingBytes() == 0) {
                    client.setState(ClientState.DONE);
                    break;
                }
            }
        }
        if (client.getState() == ClientState.DONE) {
            sendAnswer(client);
        }
    }

    private void sendAnswer(Client client) throws IOException {
        String confirmationMessage = client.getFileName() + " Ack";
        ByteBuffer confirmationBuffer = ByteBuffer.allocate(4 + confirmationMessage.getBytes().length);
        confirmationBuffer.putInt(confirmationMessage.getBytes().length);
        confirmationBuffer.put(confirmationMessage.getBytes());
        confirmationBuffer.flip();
        client.getChannel().write(confirmationBuffer);
        client.getChannel().close();
        this.clients.remove(client.getChannel());
    }
}
