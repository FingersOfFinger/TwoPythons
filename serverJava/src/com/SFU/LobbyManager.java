package com.SFU;

import java.util.Vector;

public class LobbyManager {
    public static void addLobby(Lobby lobby) {
        Server.allLobby.add(lobby);
    }

    public static boolean deleteLobby(long id, String login) {
        for (int i = 0; i < Server.allLobby.size(); i++) {
            if (Server.allLobby.get(i).id == id && Server.allLobby.get(i).owner.equals(login)) {
                Server.allLobby.remove(i);
                return true;
            }
        }
        return false;
    }
    public static void deleteLobbyNoLogin(long id) {
        for (int i = 0; i < Server.allLobby.size(); i++) {
            if (Server.allLobby.get(i).id == id) {
                Server.allLobby.remove(i);
               return;
            }
        }
        return;
    }

    public static boolean enterLobby(long idLobby, int idUser) {
        for (int i = 0; i < Server.allLobby.size(); i++) {
            if (Server.allLobby.get(i).id == idLobby && Server.allLobby.get(i).idPreparation.contains(idUser)){
                return false;
            }
        }

        for (int i = 0; i < Server.allLobby.size(); i++) {
            if (Server.allLobby.get(i).id == idLobby && Server.allLobby.get(i).idPreparation.size() < 2) {
                Server.allLobby.get(i).idPreparation.add(idUser);
                System.out.println(Server.allLobby.get(i).idPreparation.size());
                return true;
            }
        }
        return false;
    }

    public static boolean exitLobby(long idLobby, int idUser) {
        for (int i = 0; i < Server.allLobby.size(); i++){
            //что в низу не протестировано!
            if (Server.allLobby.get(i).id == idLobby){
                if(Server.allLobby.get(i).idReady.contains(idUser)){
                    return false;
                }
            }
        }
        for (int i = 0; i < Server.allLobby.size(); i++) {
            if (Server.allLobby.get(i).id == idLobby) {
                for (int j = 0; j < Server.allLobby.get(i).idPreparation.size(); j++) {
                    if (Server.allLobby.get(i).idPreparation.get(j) == idUser) {
                        Server.allLobby.get(i).idPreparation.remove(j);
                        return true;
                    }
                }
                return false;
            }
        }
        return false;
    }
    public static boolean checkStartLobby(long idLobby) {
        for (int i = 0; i < Server.allLobby.size(); i++) {
            if (Server.allLobby.get(i).id == idLobby && Server.allLobby.get(i).idReady.size() == 2) {
                return true;
            }

        }
        return false;
    }
    public static void enterLobbyReady(long idLobby, int idUser){
        for (int i = 0; i < Server.allLobby.size(); i++){
            if (!Server.allLobby.get(i).idPreparation.contains(idUser)){
                return;
            }

        }

        for (int i = 0; i < Server.allLobby.size(); i++){
            //что в низу не протестировано!
            if (Server.allLobby.get(i).id == idLobby){
                if(!Server.allLobby.get(i).idReady.contains(idUser)){
                    Server.allLobby.get(i).idReady.add(idUser);
                }
            }
        }
    }
    public static Vector<Integer> getSockets(long idLobby){
        Vector<Integer>Sockets=new Vector<>();
        for (int i = 0; i < Server.allLobby.size(); i++){
            if (Server.allLobby.get(i).id == idLobby){
                Sockets.add(Server.allLobby.get(i).idReady.get(0));
                Sockets.add(Server.allLobby.get(i).idReady.get(1));
            }

        }
        return Sockets;
    }
}
