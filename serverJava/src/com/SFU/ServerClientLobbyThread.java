package com.SFU;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.*;
import java.net.Socket;

public class ServerClientLobbyThread extends Thread{
    public Socket socket;
    public BufferedReader in;
    public BufferedWriter out;
    private String login;
    private JSONObject json;
    ServerClientLobbyThread(Socket inSocket,JSONObject inJson){socket=inSocket;json=inJson;}
    private void pars(String word) throws ParseException, IOException {

        Object obj = new JSONParser().parse(word);
        JSONObject json = (JSONObject) obj;
        if (((String) json.get("globalType")).equals("lobby")) {
            switch ((String) json.get("type")) {
                case ("createLobby"):
                    createLobby(json);
                    break;



            }
        }

    }
    private void createLobby(JSONObject json) throws IOException {
        Lobby lobby=new Lobby();
        lobby.setName((String)json.get("name"));
        lobby.setId(Server.allLobby.size()+1);
        lobby.setOwner((String)json.get("owner"));
        lobby.setIdPreparation(Server.getPort(socket.getRemoteSocketAddress()));
        Server.allLobby.add(lobby);
        SendCallBack.sendCallbackCreateLobby(true,socket);

    }
    public void run() {
        try {
            String word = "";
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            pars(json.toString());
            while (!this.isInterrupted()) {
                word = in.readLine();
                System.out.println(word);
                try {
                    pars(word);
                } catch (ParseException|IOException e) {
                    System.out.println(e);
                }
            }
        } catch (Exception e) {
            System.out.println(e);

        } finally {

        }
    }
}
