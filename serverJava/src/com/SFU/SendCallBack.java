package com.SFU;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;

public class SendCallBack {
    private static BufferedWriter out;

    public static void sendCallbackAuthorization(boolean access, Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        out.write("{\"globalType\":\"connection\",\"type\":\" authorization\",\"access\":\"" + Boolean.toString(access) + "\"}");
        out.flush();
    }

    public static void sendCallbackRegistration(boolean access, Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        out.write("{\"globalType\":\"connection\",\"type\":\"registration\",\"access\":\"" + Boolean.toString(access) + "\"}");
        out.flush();
    }

    public static void sendCallbackCreateLobby(boolean access, Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        out.write("{\"globalType\":\"lobby\",\"type\":\"receiveCreateLobby\",\"access\":\"" + Boolean.toString(access) + "\"}");
        out.flush();
    }

    public static void sendCallbackGetLobby(Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        String msg = "";
        for (int i = 0; i < Server.allLobby.size(); i++) {
            msg += "{\"id\":\"" + String.valueOf(Server.allLobby.get(i).id) + "\",\"name\":\"" + Server.allLobby.get(i).name + "\",\"owner\":\"" + Server.allLobby.get(i).owner + "\"},";
        }
        if (msg.length() > 0) {
            msg = msg.substring(0, msg.length() - 1);
        }
        out.write("{\"globalType\":\"lobby\",\"type\":\"receiveGetLobby\",\"lobby\":[" + msg + "]}");
        out.flush();
    }
    public static void sendCallbackDeleteLobby(boolean access,Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        out.write("{\"globalType\":\"lobby\",\"type\":\"receiveDeleteLobby\",\"access\":\"" + Boolean.toString(access) + "\"}");
        out.flush();

    }
    public static void sendCallbackEnterLobby(boolean access,Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        out.write("{\"globalType\":\"lobby\",\"type\":\"receiveEnterLobby\",\"access\":\"" + Boolean.toString(access) + "\"}");
        out.flush();

    }
    public static void sendCallbackExitLobby(boolean access,Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        out.write("{\"globalType\":\"lobby\",\"type\":\"\"receiveExitLobby\",\"access\":\"" + Boolean.toString(access) + "\"}");
        out.flush();

    }

}
