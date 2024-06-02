package ru.nsu.dushin;

import javax.sound.sampled.*;
import java.net.URL;
import java.util.HashMap;
import java.util.Map;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class Sound {
    private Map<Integer, Clip> soundClips = new HashMap<>();
    private URL[] soundURL = new URL[3];
    private ExecutorService executor = Executors.newCachedThreadPool();

    public Sound() {
        soundURL[0] = getClass().getResource("/die.wav");
        soundURL[1] = getClass().getResource("/wing.wav");
        soundURL[2] = getClass().getResource("/music.wav");

        // Preload all sound clips
        for (int i = 0; i < soundURL.length; i++) {
            Clip clip = loadClip(soundURL[i]);
            soundClips.put(i, clip);
        }
    }

    private Clip loadClip(URL url) {
        try {
            AudioInputStream audioInputStream = AudioSystem.getAudioInputStream(url);
            Clip clip = AudioSystem.getClip();
            clip.open(audioInputStream);
            return clip;
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    public void play(int i) {
        Clip clip = soundClips.get(i);
        if (clip != null) {
            executor.execute(() -> {
                clip.setFramePosition(0);
                clip.start();
            });
        }
    }

    public void loop(int i) {
        Clip clip = soundClips.get(i);
        if (clip != null) {
            executor.execute(() -> {
                clip.setFramePosition(0);
                clip.loop(Clip.LOOP_CONTINUOUSLY);
            });
        }
    }
}