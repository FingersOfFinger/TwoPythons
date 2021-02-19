package com.SFU;

import java.io.*;
import java.net.Socket;
import java.sql.SQLException;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;


public class ServerClientAuthorizationThread extends Thread {
    public Socket socket;
    public BufferedReader in;
    public BufferedWriter out;
    private DbHandler dbHandler = DbHandler.getInstance();;
    ServerClientAuthorizationThread(Socket inSocket) {
        socket = inSocket;
    }
    private void pars(String word) throws ParseException {
        Object obj = new JSONParser().parse(word);
        JSONObject json = (JSONObject) obj;
        if (((String) json.get("globalType")).equals("connection")) {
            switch ((String) json.get("type")) {
                case ("authorization"):
                    chekAuthorization(json);

            }
        }

    }
    private void chekAuthorization(JSONObject json){
        if (dbHandler.checkUser((String) json.get("login"), (String) json.get("password"))) {
            sendCallbackAuthorization(true);

        } else {
            sendCallbackAuthorization(false);
        }
    }
    public void sendCallbackAuthorization(boolean access){
        if(access){
            try {
                out.write("{\"globalType\":\"connection\",\"type\":\" autorization\",\"access\":\"true\"}");
                out.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }else{
            try {
                out.write("{\"globalType\":\"connection\",\"type\":\" autorization\",\"access\":\"false\"}");
                out.flush();
            } catch (IOException e) {
                e.printStackTrace();
            }

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
                    System.out.println(e);
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








