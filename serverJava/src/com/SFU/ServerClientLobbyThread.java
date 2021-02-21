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
                case("getLobby"):
                    getLobby();
                    break;
                case("deleteLobby"):
                    deleteLobby(Long.parseLong((String) json.get("id")),(String)json.get("login"));
                    break;
                case("enterLobby"):
                    enterLobby(Long.parseLong((String) json.get("id")));
                case("exitLobby"):
                    exitLobby(Long.parseLong((String) json.get("id")));
            }
        }

    }
    public long getHash(String s) {
        long l = 0;
        for (int i = 0; i < s.length(); i++)
            l = l * 127 + s.charAt(i);
        return l & Long.MAX_VALUE;
    }
    private void createLobby(JSONObject json) throws IOException {
        Lobby lobby=new Lobby();
        String name=(String)json.get("name");
        lobby.setName(name);
        String socketPort=String.valueOf(Server.getPort(socket.getRemoteSocketAddress()));
        lobby.setId(getHash(String.valueOf(Server.allLobby.size()+1)+name+socketPort+(String)json.get("owner")));
        System.out.println(getHash(String.valueOf(Server.allLobby.size()+1)+name+socketPort+(String)json.get("owner")));
        lobby.setOwner((String)json.get("owner"));
        lobby.setIdPreparation(Server.getPort(socket.getRemoteSocketAddress()));
        LobbyManager.addLobby(lobby);
        SendCallBack.sendCallbackCreateLobby(true,socket);

    }
    private void getLobby() throws IOException {
        SendCallBack.sendCallbackGetLobby(socket);

    }
    private void deleteLobby(Long id,String login) throws IOException {
        if(LobbyManager.deleteLobby(id,login)){
            SendCallBack.sendCallbackDeleteLobby(true,socket);
        }else{
            SendCallBack.sendCallbackDeleteLobby(false,socket);
        }

    }
    private void enterLobby(Long id) throws IOException {
        if(LobbyManager.enterLobby(id,Server.getPort(socket.getRemoteSocketAddress()))){
            SendCallBack.sendCallbackEnterLobby(true,socket);
        }else{
            SendCallBack.sendCallbackEnterLobby(false,socket);
        }
    }
    private void exitLobby(Long id) throws IOException {
        if(LobbyManager.exitLobby(id,Server.getPort(socket.getRemoteSocketAddress()))){
            SendCallBack.sendCallbackExitLobby(true,socket);
        }else{
            SendCallBack.sendCallbackExitLobby(false,socket);
        }

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
            Server.usersOnline.remove(login);
            System.out.println(e);

        } finally {


        }
    }
}
