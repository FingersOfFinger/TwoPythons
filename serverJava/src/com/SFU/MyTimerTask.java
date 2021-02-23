package com.SFU;

import java.io.IOException;
import java.net.Socket;
import java.util.TimerTask;

public class MyTimerTask extends TimerTask {
    private Socket socket;
    Python python;

    MyTimerTask(Socket inSocket, Python inPython) {
        socket = inSocket;
        python = inPython;


    }

    @Override
    public void run() {
        try {
            SendCallBack.sendCallbackSetDisplay(python, socket);
        } catch (IOException e) {
            e.printStackTrace();
        }
        //проверка в будущем
        python.move();
    }
}
