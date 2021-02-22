package com.SFU;

import java.io.BufferedWriter;
import java.io.IOException;
import java.io.OutputStreamWriter;
import java.net.Socket;
import java.util.Vector;

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
    public static void sendCallbackStatGames(Vector<Statistic>statistics,Socket socket) throws IOException {
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        String msg = "";
        for (int i = 0; i < statistics.size(); i++) {
            msg += "{\"winner\":\"" + statistics.get(i).winner+ "\",\"loser\":\"" +  statistics.get(i).loser + "\",\"score\":\"" + String.valueOf( statistics.get(i).score) + "\"},";
        }
        if (msg.length() > 0) {
            msg = msg.substring(0, msg.length() - 1);
        }
        out.write("{\"globalType\":\"lobby\",\"type\":\"receiveStatGame\",\"userScore\":[" + msg + "]}");
        out.flush();
    }
    public static void sendCallbackSetDisplay(Python python,Socket socket) throws IOException { //тут в будущем будет много чего
        out = new BufferedWriter(new OutputStreamWriter(socket.getOutputStream()));
        String msg="";
        for(int i=0;i<python.dots.size();i++){
            msg+="{\"x\":\""+String.valueOf(python.dots.get(i).x)+"\",\"y\":\""+String.valueOf(python.dots.get(i).y)+"\"},";
        }
        if (msg.length() > 0) {
            msg = msg.substring(0, msg.length() - 1);
        }
        out.write("{\"globalType\":\"game\",\"type\":\"setDisplay\",\"coordinatesPython1\":["+msg+"]}");
        out.flush();

    }

}
