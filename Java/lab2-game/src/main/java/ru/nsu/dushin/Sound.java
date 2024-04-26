package ru.nsu.dushin;

import javax.sound.sampled.AudioInputStream;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.Clip;
import java.net.URL;

class Sound{
    private Clip clip;
    private URL soundURL[] = new URL[3];
    public Sound() {
        soundURL[0] = getClass().getResource("/die.wav");
        soundURL[1] = getClass().getResource("/wing.wav");
        soundURL[2] = getClass().getResource("/music.wav");
    }
    public void setFile(int i) {
        try {
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(soundURL[i]);
            clip = AudioSystem.getClip();
            clip.open(audioInputStream);
        }catch(Exception e){
            e.printStackTrace();
        }
    }
    public void play() {
        clip.start();
    }
    public void loop() {
        clip.loop(Clip.LOOP_CONTINUOUSLY);
    }
}