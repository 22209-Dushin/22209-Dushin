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
        ByteBuffer buffer = client.getBuffer();
        int bytesRead;
        switch (client.getState()) {
            case LENGTH_NAME :
                buffer.limit(4);
                bytesRead = channel.read(buffer);
                client.decreaseRemainingBytes(bytesRead);
                if (client.getRemainingBytes() == 0) {
                    client.setFileNameLength(ByteBuffer.wrap(buffer.slice().array()).getInt());
                    client.setRemainingBytes(client.getFileNameLength());
                    client.setState(ClientState.NAME);
                    buffer.clear();
                }
                break;
            case NAME :
                buffer.limit(client.getFileNameLength());
                bytesRead = channel.read(buffer);
                client.decreaseRemainingBytes(bytesRead);
                if (client.getRemainingBytes() == 0) {
                    client.setFileName(new String(buffer.array(), 0, client.getFileNameLength()));
                    client.setRemainingBytes(4);
                    client.setState(ClientState.LENGTH_FILE);
                    buffer.clear();
                }
                break;
            case LENGTH_FILE :
                buffer.limit(4);
                bytesRead = channel.read(buffer);
                client.decreaseRemainingBytes(bytesRead);
                if (client.getRemainingBytes() == 0) {
                    client.setRemainingBytes(ByteBuffer.wrap(buffer.slice().array()).getInt());
                    client.setState(ClientState.FILE);
                    buffer.clear();
                }
                break;
            case FILE :
                bytesRead = channel.read(client.getBuffer());
                client.decreaseRemainingBytes(bytesRead);
                try (FileOutputStream fileOutputStream = new FileOutputStream(client.getFileName(), true)) {
                    fileOutputStream.getChannel().position(fileOutputStream.getChannel().size());
                    fileOutputStream.write(client.getBuffer().array(), 0, bytesRead);
                    buffer.clear();
                }
                if (client.getRemainingBytes() == 0) {
                    client.setState(ClientState.DONE);
                }
            case DONE :
                sendAnswer(client);
                break;
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
