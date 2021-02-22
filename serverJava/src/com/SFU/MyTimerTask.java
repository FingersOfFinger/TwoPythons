package com.SFU;

import java.io.IOException;
import java.net.Socket;
import java.util.TimerTask;

public class MyTimerTask extends TimerTask {
    private Socket socket;
    MyTimerTask(Socket inSocket){
        socket=inSocket;


    }
    @Override
    public void run() {
        try {
            SendCallBack.sendCallbackSetDisplay(ServerClientGameThread.python,socket);
        } catch (IOException e) {
            e.printStackTrace();
        }
        //проверка в будущем
        ServerClientGameThread.python.move();
    }
}
