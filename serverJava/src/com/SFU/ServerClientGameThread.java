package com.SFU;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Vector;

public class ServerClientGameThread<checkFruits> extends Thread {
    public Vector<Point> fruits = new Vector<>();
    private static final HashMap<Integer, Timer> hashTimers = new HashMap<>();
    public Vector<Socket> sockets;
    private String login;
    public Vector<Python> pythons = new Vector<>();
    Timer timer;
    private TimerTask timerTask;

    ServerClientGameThread(Vector<Socket> inSockets) {

        for (int i = 0; i < inSockets.size(); i++) {

            pythons.add(new Python(i + 1));
        }


        sockets = inSockets;
        timer = new Timer();
        for (int i = 0; i < sockets.size(); i++) {
            hashTimers.put(Server.getPort(sockets.get(i).getRemoteSocketAddress()), timer);
        }
        //hashTimers.put(Server.getPort(socketTwo.getRemoteSocketAddress(),timer));
    }

    public static void stopTimer(int idSocket) {
        Timer timer = hashTimers.get(idSocket);
        if (timer!=null)
            timer.cancel();
        hashTimers.remove(idSocket);

    }

    public static void generateFruits(Vector<Point> fruits, Vector<Python> pythons) {
        int size = (int) (Math.random() * 3) + 1;
        Point point;
        boolean flag;


        for (int i = 0; i < size; i++) {
            while (true) {
                flag=true;
                point = new Point((int) (Math.random() * (19)), (int) (Math.random() * (19)));
                for (int j = 0; j < pythons.size(); j++)
                    if (pythons.get(j).dots.contains(point)) {
                        flag = false;
                        break;
                    }
                if (flag)
                    break;
            }


            fruits.add(point);
        }

    }

    public static void checkFruits(Vector<Point> fruits, Vector<Python> pythons) {
        for (int i = 0; i < fruits.size(); i++) {
            for (int j = 0; j < pythons.size(); j++) {
                if (pythons.get(j).dots.firstElement().equals(fruits.get(i))) {
                    fruits.remove(pythons.get(j).dots.firstElement());
                    pythons.get(j).height();
                    break;
                }
            }


        }

        if (fruits.size() == 0) {
            generateFruits(fruits, pythons);
        }


    }


    public void run() {
        generateFruits(fruits, pythons);
        try {
            for (int i = 0; i < pythons.size(); i++) {
                (new PlayerGamesThread(sockets.get(i), pythons.get(i))).start();
            }

            timerTask = new MyTimerTask(sockets, fruits, pythons);
            timer.scheduleAtFixedRate(timerTask, 0, 200);
        } catch (Exception e) {
            Server.usersOnline.remove(login);
            System.out.println(e);
        }
    }
}
