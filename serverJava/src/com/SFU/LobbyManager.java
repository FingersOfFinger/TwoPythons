package com.SFU;

public class LobbyManager {
    public static void addLobby(Lobby lobby){
        Server.allLobby.add(lobby);
    }
    public static boolean deleteLobby(long id,String login){
        for(int i=0;i<Server.allLobby.size();i++){
            if(Server.allLobby.get(i).id==id && Server.allLobby.get(i).owner.equals(login)){
                Server.allLobby.remove(i);
                return true;
            }
        }
        return false;
    }
}
