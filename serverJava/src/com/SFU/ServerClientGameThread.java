package com.SFU;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.awt.*;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;
import java.util.Timer;
import java.util.TimerTask;

public class ServerClientGameThread extends Thread {
    public Socket socket;
    private String login;
    public static Python python;
    static Timer timer;
    private TimerTask timerTask;

    ServerClientGameThread(Socket inSocket) {
        python=new Python();
        socket = inSocket;
        python.setDirection("right");
        Point p1=new Point(2,0);
        Point p2=new Point(1,0);
        Point p3=new Point(0,0);
        python.setFirstDots(p1,p2,p3);
        timer=new Timer();
    }
    public static void stopTimer(){
        timer.cancel();
    }



    public void run() {
        try {
            PlayerGamesThread player=new PlayerGamesThread(socket,python);
            player.start();

        }catch (Exception e){
            timer.cancel();

        }


        timerTask=new MyTimerTask(socket);
        timer.scheduleAtFixedRate(timerTask,0,500);
        try {

            while (!this.isInterrupted()) {

            }
        } catch (Exception e) {
            Server.usersOnline.remove(login);
            System.out.println(e);
        } finally {
            timer.cancel();
        }
    }
}
