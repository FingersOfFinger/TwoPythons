package com.SFU;

import java.io.IOException;
import java.net.Socket;
import java.util.TimerTask;
import java.util.Vector;

public class ReadyTimerTask extends TimerTask {
    private int timer =0;
    private Vector <Socket>sockets=new Vector<>();
    ReadyTimerTask(Vector<Socket>inSockets){
        sockets=inSockets;

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
        if(timer==10)
            cancel();

    }
}
