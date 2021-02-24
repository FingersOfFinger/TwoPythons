package com.SFU;

import org.json.simple.JSONObject;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.HashMap;
import java.util.Vector;

public class Server {

    public static HashMap<Integer,Socket> mapSockets=new HashMap<>();
    public static Vector<Lobby>allLobby=new Vector<>();
    public static Vector<String> usersOnline= new Vector<>();
    public static HashMap<Integer,String>mapLoginsOnline=new HashMap<>();
    public static Vector<Socket>testSockets=new Vector<>(); // Тест игры, не забыть удалить
    public static int getPort(SocketAddress address){
        return ((InetSocketAddress) address).getPort();
    }
    public void start() {
        try {
            ServerSocket server = new ServerSocket(58);

            System.out.println("Server Started....");
            while (true) {
                Socket socket = server.accept();
                mapSockets.put(getPort(socket.getRemoteSocketAddress()),socket);
                System.out.println(" >> " + "Client No:" + getPort(socket.getRemoteSocketAddress())+ " started!");
                startAuthorizationThread(socket);
            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }
    public static void startAuthorizationThread(Socket socket){
        ServerClientAuthorizationThread sct = new ServerClientAuthorizationThread(socket);

        sct.start();
    }
    public static void startClientLobbyThread(Socket socket, JSONObject json){
        ServerClientLobbyThread sct=new ServerClientLobbyThread(socket,json);

        sct.start();
    }

}

