package com.SFU;

import java.util.Vector;

public class Lobby {
    public int id;
    public String name;
    public String owner;
    public Vector<Integer>idPreparation=new Vector<Integer>();
    public Vector<Integer>idReady=new Vector<Integer>();


    public void setId(int inId){
        id=inId;
    }
    public void setName(String inName){
        name=inName;
    }
    public void setOwner(String inOwner){
        owner=inOwner;
    }
    public void setIdPreparation(int idSocket){
        idPreparation.add(idSocket);

    }
    public void setIdReady(int idSocket){
        idReady.add(idSocket);

    }
}
