package com.SFU;


import java.awt.*;

import java.net.Socket;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Vector;

public class ServerClientGameThread extends Thread {
    public Vector<Point> fruits = new Vector<>();
    private static final HashMap<Integer, Timer> hashTimers = new HashMap<>();
    private static final HashMap<Integer, Timer> hashTimersPrepare = new HashMap<>();
    public static HashMap<Socket,Socket>hashEnemy=new HashMap<>();
    public Vector<Socket> sockets;
    private String login;
    public Vector<Python> pythons = new Vector<>();
    Timer timer;
    Timer timerPreparation;

    ServerClientGameThread(Vector<Socket> inSockets) {

        for (int i = 0; i < inSockets.size(); i++) {

            pythons.add(new Python(pythons));
        }


        sockets = inSockets;
        timer = new Timer();
        timerPreparation=new Timer();
        for (Socket socket : sockets) {
            hashTimers.put(Server.getPort(socket.getRemoteSocketAddress()), timer);
            hashTimersPrepare.put(Server.getPort(socket.getRemoteSocketAddress()), timerPreparation);

        }
        hashEnemy.put(sockets.get(0),sockets.get(1));
        hashEnemy.put(sockets.get(1),sockets.get(0));
        //hashTimers.put(Server.getPort(socketTwo.getRemoteSocketAddress(),timer));
    }

    public static void stopTimer(int idSocket) {
        System.out.println("Результат");
        Timer timer = hashTimers.get(idSocket);
        hashTimers.remove(idSocket);
        Timer timerPrepare = hashTimersPrepare.get(idSocket);
        hashTimersPrepare.remove(idSocket);
        if (timer!=null) {

            timer.cancel();
            timerPrepare.cancel();
        }


    }

    public static void generateFruits(Vector<Point> fruits, Vector<Python> pythons) {
        int size = (int) (Math.random() * 3) + 1;
        Point point;
        boolean flag;


        for (int i = 0; i < size; i++) {
            do {
                flag = true;
                point = new Point((int) (Math.random() * (19)), (int) (Math.random() * (19)));
                for (Python python : pythons)
                    if (python.dots.contains(point)) {
                        flag = false;
                        break;
                    }
            } while (!flag);


            fruits.add(point);
        }

    }

    public static void checkFruits(Vector<Point> fruits, Vector<Python> pythons) {
        for (int i = 0; i < fruits.size(); i++) {
            for (Python python : pythons) {
                if (python.dots.firstElement().equals(fruits.get(i))) {
                    fruits.remove(python.dots.firstElement());
                    python.height();
                    python.points++;
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



            TimerTask timerTask = new MyTimerTask(sockets, fruits, pythons);
            TimerTask timerTaskPrepareGame=new ReadyTimerTask(sockets,timer,timerTask);
            sleep (500);
            timerPreparation.scheduleAtFixedRate(timerTaskPrepareGame,0,1000);


        } catch (Exception e) {
            Server.usersOnline.remove(login);
            System.out.println();
        }
    }
}
