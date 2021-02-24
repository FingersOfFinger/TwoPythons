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
    public Socket socket;
    public Socket socketTwo;
    private String login;
    public Python python;
    Timer timer;
    private TimerTask timerTask;

    ServerClientGameThread(Socket inSocket) {
        python = new Python();
        socket = inSocket;
        python.setDirection("right");
        Point p1 = new Point(2, 0);
        Point p2 = new Point(1, 0);
        Point p3 = new Point(0, 0);
        python.setFirstDots(p1, p2, p3);
        timer = new Timer();
        hashTimers.put(Server.getPort(socket.getRemoteSocketAddress()),timer);
       //hashTimers.put(Server.getPort(socketTwo.getRemoteSocketAddress(),timer));
    }
    public static void stopTimer(int idSocket){
        hashTimers.get(idSocket).cancel();
        hashTimers.remove(idSocket);

    }

    public static void generateFruits(Vector<Point>fruits){
        int size=(int)(Math.random()*3)+1;

        for(int i=0;i<size;i++){
            fruits.add(new Point((int)(Math.random()*(15))+1,(int)(Math.random()*(15))+1));
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
            PlayerGamesThread player = new PlayerGamesThread(socket, python);
            player.start();
            timerTask = new MyTimerTask(socket,fruits,python);
            timer.scheduleAtFixedRate(timerTask, 0, 500);
        } catch (Exception e) {
            Server.usersOnline.remove(login);
            System.out.println(e);
        }
    }
}
