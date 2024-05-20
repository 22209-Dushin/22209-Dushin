package ru.nsu.dushin;

import java.nio.ByteBuffer;
import java.nio.channels.SocketChannel;

public class Client {
    private SocketChannel channel;
    private ClientState state;
    private ByteBuffer buffer = ByteBuffer.allocate(1024 * 1024);
    private int fileNameLength;
    private int remainingBytes;
    private String fileName;
    public Client(SocketChannel channel) {
        this.channel = channel;
        this.state = ClientState.LENGTH_NAME;
        this.buffer = ByteBuffer.allocate(1024 * 1024);
    }

    public ClientState getState() { return this.state; }

    public SocketChannel getChannel() { return this.channel; }

    public void setFileNameLength(int fileNameLength) { this.fileNameLength = fileNameLength; }

    public void setState(ClientState clientState) { this.state = clientState; }

    public int getFileNameLength() { return this.fileNameLength; }

    public void setFileName(String fileName) { this.fileName = fileName; }

    public void setRemainingBytes(int remainingBytes) { this.remainingBytes = remainingBytes; }
    public int getRemainingBytes() { return this.remainingBytes; }


    public ByteBuffer getBuffer() { return this.buffer; }

    public void decreaseRemainingBytes(int bytesRead) { this.remainingBytes -= bytesRead; }

    public String getFileName() { return this.fileName; }
}
