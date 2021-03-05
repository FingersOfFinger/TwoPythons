package com.SFU;

import java.io.IOException;
import java.net.Socket;
import java.util.Timer;
import java.util.TimerTask;
import java.util.Vector;

import static java.lang.Thread.sleep;

public class ReadyTimerTask extends TimerTask {
    private int timer =0;
    private Timer nextTimer;
    private TimerTask timerTask;
    private Vector <Socket>sockets=new Vector<>();
    ReadyTimerTask(Vector<Socket>inSockets, Timer inTimer,TimerTask inTimerTask){
        timerTask=inTimerTask;
        sockets=inSockets;
        nextTimer=inTimer;

    }
    @Override
    public void run() {
        timer++;
        for(int i=0;i<sockets.size();i++){
            try {
                SendCallBack.SendCallbackPreparationGame(sockets.get(i),10-timer);
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
        if(timer==10) {
            try {
                sleep(200);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
            cancel();
            nextTimer.scheduleAtFixedRate(timerTask, 0, 300);
        }

    }
}
