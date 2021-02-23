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

public class ServerClientGameThread extends Thread {
    private static HashMap<Integer,Timer>hashTimers=new HashMap<>();
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




    public void run() {

        try {
            PlayerGamesThread player = new PlayerGamesThread(socket, python);
            player.start();
            timerTask = new MyTimerTask(socket,python);
            timer.scheduleAtFixedRate(timerTask, 0, 500);


        } catch (Exception e) {
            Server.usersOnline.remove(login);
            System.out.println(e);
        }
    }
}
