package com.SFU;

import java.awt.*;
import java.io.IOException;
import java.net.Socket;
import java.util.TimerTask;
import java.util.Vector;

public class MyTimerTask extends TimerTask {
    private final Socket socket;
    private final Python python;
    private final Vector<Point> fruits;


    MyTimerTask(Socket inSocket, Vector<Point>inFruits, Python inPython) {
        socket = inSocket;
        python = inPython;
        fruits=inFruits;


    }

    @Override
    public void run() {
        try {
            SendCallBack.sendCallbackSetDisplay(python, socket,fruits);
        } catch (IOException e) {
            e.printStackTrace();
        }
        ServerClientGameThread.checkFruits(fruits,python);
        python.move();
    }
}
