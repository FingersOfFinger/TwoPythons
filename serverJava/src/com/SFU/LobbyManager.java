package com.SFU;

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

    public static boolean enterLobby(long idLobby, int idUser) {
        for (int i = 0; i < Server.allLobby.size(); i++) {
            if (Server.allLobby.get(i).id == idLobby && Server.allLobby.get(i).idPreparation.size() < 2) {
                Server.allLobby.get(i).idPreparation.add(idUser);
                return true;
            }
        }
        return false;

    }

    public static boolean exitLobby(long idLobby, int idUser) {
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
}
