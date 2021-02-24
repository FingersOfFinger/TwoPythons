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
    public Vector<Point>fruits=new Vector<>();
    private static final HashMap<Integer,Timer>hashTimers=new HashMap<>();
    public Vector<Socket> sockets;
    public Socket socketTwo;
    private String login;
    public Python python;
    Timer timer;
    private TimerTask timerTask;

    ServerClientGameThread(Vector<Socket> inSocket) {
        python = new Python(3);
        sockets = inSocket;
        timer = new Timer();
        for (int i=0;i<sockets.size();i++) {
            hashTimers.put(Server.getPort(sockets.get(i).getRemoteSocketAddress()), timer);
        }
       //hashTimers.put(Server.getPort(socketTwo.getRemoteSocketAddress(),timer));
    }
    public static void stopTimer(int idSocket){
        hashTimers.get(idSocket).cancel();
        hashTimers.remove(idSocket);

    }

    public static void generateFruits(Vector<Point>fruits){
        int size=(int)(Math.random()*3)+1;

        for(int i=0;i<size;i++){
            fruits.add(new Point((int)(Math.random()*(19))+1,(int)(Math.random()*(19))+1));
        }

    }
    public static void checkFruits(Vector<Point>fruits,Python python){
        for(int i=0;i<fruits.size();i++){
            if(python.dots.firstElement().equals(fruits.get(i))){
                fruits.remove(python.dots.firstElement());
                python.height();
                break;
            }
        }
        if(fruits.size()==0){
            generateFruits(fruits);
        }


    }




    public void run() {
        generateFruits(fruits);

        try {
            PlayerGamesThread player = new PlayerGamesThread(sockets.get(0), python);
            player.start();
            timerTask = new MyTimerTask(sockets.get(0),fruits,python);
            timer.scheduleAtFixedRate(timerTask, 0, 500);
        } catch (Exception e) {
            Server.usersOnline.remove(login);
            System.out.println(e);
        }
    }
}
