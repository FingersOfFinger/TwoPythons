package com.SFU;

import java.awt.*;
import java.io.IOException;
import java.net.Socket;
import java.util.TimerTask;
import java.util.Vector;

public class MyTimerTask extends TimerTask {

    private Vector<Socket> sockets;
    private Vector<Python> pythons;
    private final Vector<Point> fruits;


    MyTimerTask(Vector<Socket> inSocket, Vector<Point> inFruits, Vector<Python> inPythons) {
        sockets = inSocket;
        pythons = inPythons;
        fruits = inFruits;


    }

    @Override
    public void run() {

            try {
                for (int i = 0; i < sockets.size(); i++) {
                    SendCallBack.sendCallbackSetDisplay(pythons, sockets.get(i), fruits);
                }
            } catch (IOException e) {

                e.printStackTrace();
            }
            ServerClientGameThread.checkFruits(fruits, pythons);
            for (int i = 0; i < pythons.size(); i++) {
                pythons.get(i).move();
            }



    }


}
