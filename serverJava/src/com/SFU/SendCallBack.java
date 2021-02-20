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
    public static void sendCallbackCreateLobby(boolean access,Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        out.write("{\"globalType\":\"lobby\",\"type\":\"receiveCreateLobby\",\"access\":\"" + Boolean.toString(access) + "\"}");
        out.flush();
    }
}
