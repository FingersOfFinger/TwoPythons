package com.SFU;

import java.io.*;
import java.net.Socket;


import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class ServerClientAuthorizationThread extends Thread {
    public Socket socket;
    public BufferedReader in;
    public BufferedWriter out;
    private DbHandler dbHandler = DbHandler.getInstance();
    private String login;

    ServerClientAuthorizationThread(Socket inSocket) {
        socket = inSocket;
    }

    private void pars(String word) throws ParseException, InterruptedException {
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
        }else{
            if (((String) json.get("globalType")).equals("lobby")){
                Server.startClientLobbyThread(socket,json);
                throw new InterruptedException();
            }

        }

    }

    private void chekAuthorization(JSONObject json) {
        String mLogin=(String) json.get("login");
        String mPassword=(String) json.get("password");
        if (dbHandler.checkUser(mLogin,mPassword)) {
            login=mLogin;
            sendCallbackAuthorization(true);

        } else {
            sendCallbackAuthorization(false);
        }
    }

    private void sendCallbackAuthorization(boolean access) {

        try {
            out.write("{\"globalType\":\"connection\",\"type\":\" authorization\",\"access\":\"" + Boolean.toString(access) + "\"}");
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }


    }

    private void registration(JSONObject json) {
        String mLogin=(String) json.get("login");
        String mPassword=(String) json.get("password");
        if (dbHandler.addUser(mLogin, mPassword)) {
            sendCallbackRegistration(true);
        } else {
            sendCallbackRegistration(false);
        }

    }

    private void sendCallbackRegistration(boolean access) {
        try {
            out.write("{\"globalType\":\"connection\",\"type\":\"registration\",\"access\":\"" + Boolean.toString(access) + "\"}");
            out.flush();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }

    public void run() {

        try {
            String word = "";
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
            while (!word.equals("close")) {
                word = in.readLine();
                System.out.println(word);
                try {
                    pars(word);


                } catch (ParseException e) {

                }
            }
            in.close();
            out.close();
            socket.close();
        } catch (Exception e) {
            System.out.println(e);

        } finally {
            System.out.println("Client exit");
        }
    }
}








