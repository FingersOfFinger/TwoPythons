package com.SFU;

import java.io.*;
import java.net.Socket;

public class ServerClientAuthorizationThread extends Thread {
    Socket socket;
    BufferedReader in;
    BufferedWriter out;

    ServerClientAuthorizationThread(Socket inSocket) {
        socket = inSocket;
    }

    public void run() {
        String word = "";
        try {

            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            while (!word.equals("close")) {
                word = in.readLine();
                System.out.println(word);
            }
            in.close();
            out.close();
            socket.close();

        } catch (Exception exc) {
            System.out.println(exc);

        } finally {

            System.out.println("Client exit");

        }
    }
}








