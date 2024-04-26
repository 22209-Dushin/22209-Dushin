package ru.nsu.dushin;

class Pipe{
    public static final int WIDTH = 64;
    public static final int HEIGHT = 512;
    private int x = 360;
    private int y = 0;
    private boolean passed = false;

    public int getX() { return x; }

    public int getY() { return y; }
    public void addX(int dx) { this.x += dx; }
    public void setY(int y) { this.y = y; }
    public boolean isPassed() { return passed; }
    public void setPassed() { passed = !passed; }
}