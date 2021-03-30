package com.SFU;

import org.json.simple.JSONObject;
import org.json.simple.parser.JSONParser;
import org.json.simple.parser.ParseException;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class PlayerGamesThread extends Thread{
    private Socket socket;
    private Python python;
    private BufferedReader in;
    PlayerGamesThread(Socket inSocket,Python inPython){
        socket=inSocket;
        python=inPython;

    }
    private void pars(String word) throws ParseException, IOException {
        Object obj = new JSONParser().parse(word);
        JSONObject json = (JSONObject) obj;
        if (((String) json.get("globalType")).equals("game")) {
            switch ((String) json.get("type")) {
                case("setDirectionPython"):
                    python.setDirection((String) json.get("directionPython"));
                    break;
                case ("closeGame"):
                    this.interrupt();
                    System.out.println("close");
                    ServerClientGameThread.stopTimer(Server.getPort(socket.getRemoteSocketAddress()));
                    ServerClientLobbyThread sct=new ServerClientLobbyThread(socket);
                    sct.start();
                    break;
            }
        }

    }
    public void run() {

        try {
            String word;
            in = new BufferedReader(new InputStreamReader(socket.getInputStream()));
            while (!this.isInterrupted()) {
                word = in.readLine();
               // System.out.println(word);
                try {
                    pars(word);

                } catch (ParseException | IOException e) {

                }

            }
        } catch (Exception e) {

            ServerClientGameThread.stopTimer(Server.getPort(socket.getRemoteSocketAddress()));
            System.out.println(e);
        }
    }
}
