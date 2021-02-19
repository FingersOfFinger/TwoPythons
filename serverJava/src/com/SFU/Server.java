package com.SFU;

import java.net.InetSocketAddress;
import java.net.ServerSocket;
import java.net.Socket;
import java.net.SocketAddress;
import java.util.HashMap;

public class Server {
    public HashMap<Integer,Socket> mapSockets=new HashMap<>();
    private int getPort(SocketAddress address){
        return ((InetSocketAddress) address).getPort();
    }
    public void start() {
        try {
            ServerSocket server = new ServerSocket(81);

            System.out.println("Server Started....");
            while (true) {
                Socket socket = server.accept();
                mapSockets.put(getPort(socket.getRemoteSocketAddress()),socket);
                System.out.println(" >> " + "Client No:" + getPort(socket.getRemoteSocketAddress())+ " started!");
                ServerClientAuthorizationThread sct = new ServerClientAuthorizationThread(socket);
                sct.start();

            }
        } catch (Exception e) {
            System.out.println(e);
        }
    }

}

