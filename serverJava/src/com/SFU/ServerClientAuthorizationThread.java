package com.SFU;

import java.io.*;
import java.net.Socket;


import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class ServerClientAuthorizationThread extends Thread {
    public Socket socket;
    public BufferedReader in;
    private DbHandler dbHandler = DbHandler.getInstance();
    private String login;

    ServerClientAuthorizationThread(Socket inSocket) {
        socket = inSocket;
    }

    private void pars(String word) throws ParseException, IOException {
        Object obj = new JSONParser().parse(word);
        JSONObject json = (JSONObject) obj;
        if (((String) json.get("globalType")).equals("connection")) {
            switch ((String) json.get("type")) {
                case ("authorization"):
                    chekAuthorization(json);
                    break;
                case ("registration"):
                    registration(json);
                    break;
            }
        } else {
            if (((String) json.get("globalType")).equals("lobby")) {
                Server.startClientLobbyThread(socket, json);
                this.interrupt();
            }

        }

    }

    private void chekAuthorization(JSONObject json) throws IOException {
        String mLogin = (String) json.get("login");
        String mPassword = (String) json.get("password");
        if (dbHandler.checkUser(mLogin, mPassword)) {
            login = mLogin;
            SendCallBack.sendCallbackAuthorization(true, socket);

        } else {
            SendCallBack.sendCallbackAuthorization(false, socket);
        }
    }


    private void registration(JSONObject json) throws IOException {
        String mLogin = (String) json.get("login");
        String mPassword = (String) json.get("password");
        if (dbHandler.addUser(mLogin, mPassword)) {
            SendCallBack.sendCallbackRegistration(true, socket);
        } else {
            SendCallBack.sendCallbackRegistration(false, socket);
        }
    }


    public void run() {

        try {
            String word = "";
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));

            while (!this.isInterrupted()) {
                word = in.readLine();
                System.out.println(word);
                try {
                    pars(word);

                } catch (ParseException|IOException e) {

                }
            }


        } catch (Exception e) {
            System.out.println(e);

        } finally {

        }
    }
}








