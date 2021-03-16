package com.SFU;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.*;
import java.net.Socket;
import java.util.Vector;

public class ServerClientLobbyThread extends Thread{
    public Socket socket;
    public BufferedReader in;
    private final String login;
    private final JSONObject json;
    private final DbHandler dbHandler = DbHandler.getInstance();
    ServerClientLobbyThread(Socket inSocket,JSONObject inJson,String inLogin){socket=inSocket;json=inJson;login=inLogin;}
    private void pars(String word) throws ParseException, IOException {

        Object obj = new JSONParser().parse(word);
        JSONObject json = (JSONObject) obj;
        if (json.get("globalType").equals("lobby")) {
            switch ((String) json.get("type")) {
                case ("createLobby") -> createLobby(json);
                case ("getLobby") -> getLobby();
                case ("deleteLobby") -> deleteLobby(Long.parseLong((String) json.get("id")), (String) json.get("login"));
                case ("enterLobby") -> enterLobby(Long.parseLong((String) json.get("id")));
                case ("exitLobby") -> exitLobby(Long.parseLong((String) json.get("id")));
                case ("startGame") -> startGame(Long.parseLong((String) json.get("id")));
                case ("getStatGame") -> getStatGame((String) json.get("login"));
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
        lobby.setId(getHash((Server.allLobby.size() + 1) +name+socketPort+ json.get("owner")));
        System.out.println(getHash((Server.allLobby.size() + 1) +name+socketPort+ json.get("owner")));
        lobby.setOwner((String)json.get("owner"));
        lobby.setIdPreparation(Server.getPort(socket.getRemoteSocketAddress()));
        LobbyManager.addLobby(lobby);
        SendCallBack.sendCallbackCreateLobby(true,socket);

    }
    private void getLobby() throws IOException {
        SendCallBack.sendCallbackGetLobby(socket);

    }
    private void deleteLobby(Long id,String login) throws IOException {
        SendCallBack.sendCallbackDeleteLobby(LobbyManager.deleteLobby(id, login),socket);

    }
    private void enterLobby(Long id) throws IOException {
        SendCallBack.sendCallbackEnterLobby(LobbyManager.enterLobby(id, Server.getPort(socket.getRemoteSocketAddress())),socket);
    }
    private void exitLobby(Long id) throws IOException {
        SendCallBack.sendCallbackExitLobby(LobbyManager.exitLobby(id, Server.getPort(socket.getRemoteSocketAddress())),socket);

    }
    private void startGame(Long id){
        LobbyManager.enterLobbyReady(id,Server.getPort(socket.getRemoteSocketAddress()));
        System.out.println(LobbyManager.checkStartLobby(id));
        if(LobbyManager.checkStartLobby(id)){
            Socket socket1;
            Socket socket2;
            Vector<Integer> Sockets=LobbyManager.getSockets(id);
            socket1=Server.mapSockets.get(Sockets.get(0));
            socket2=Server.mapSockets.get(Sockets.get(1));
            System.out.println(Sockets.get(0));
            System.out.println(Sockets.get(1));
            LobbyManager.deleteLobbyNoLogin(id);
            //старт игры

        }

    }
    private void getStatGame(String login) throws IOException {
        SendCallBack.sendCallbackStatGames(dbHandler.getStatGame(login),socket);
    }
    public void run() {
        try {
            String word;
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
            System.out.println();

        }
    }
}
