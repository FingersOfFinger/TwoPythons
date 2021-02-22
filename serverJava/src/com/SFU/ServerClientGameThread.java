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
    public BufferedReader in;
    private String login;
    private JSONObject json;
    public static Python python;
    private Timer timer;
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
    private void pars(String word) throws ParseException, IOException{
        Object obj = new JSONParser().parse(word);
        JSONObject json = (JSONObject) obj;
        if (((String) json.get("globalType")).equals("game")) {
            switch ((String) json.get("type")) {
                case("setDirectionPython"):
                    python.setDirection((String) json.get("directionPython"));
                    break;
            }
        }

    }

    public void run() {
        timerTask=new MyTimerTask(socket);
        timer.scheduleAtFixedRate(timerTask,0,500);
        try {
            String word = "";
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            while (!this.isInterrupted()) {
                word = in.readLine();
                System.out.println(word);
                try {
                    pars(word);

                } catch (ParseException | IOException e) {

                }

            }
        } catch (Exception e) {
            Server.usersOnline.remove(login);
            System.out.println(e);



        } finally {
            timer.cancel();


        }
    }
}
