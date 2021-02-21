package com.SFU;

import java.sql.*;
import java.util.Vector;

import org.sqlite.JDBC;


public class DbHandler {
    private static final String CON_STR = "jdbc:sqlite:resources/users.db";


    private static DbHandler instance = null;

    public static synchronized DbHandler getInstance() {
        if (instance == null) {
            try {
                instance = new DbHandler();
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        return instance;
    }


    private Connection connection;

    private DbHandler() throws SQLException {

        DriverManager.registerDriver(new JDBC());

        this.connection = DriverManager.getConnection(CON_STR);
    }

    public boolean checkUser(String login, String password) {
        try (Statement statement = this.connection.createStatement()) {

            ResultSet resultSet = statement.executeQuery("SELECT id,login,password FROM users WHERE login=\"" + login + "\" AND password=\"" + password + "\"");

            if (resultSet.next()) {
                return true;
            }
            return false;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }

    public Vector<Statistic> getStatGame(String login) {
        Vector<Statistic>statistics=new Vector<>();
        try (Statement statement = this.connection.createStatement()) {

            ResultSet resultSet = statement.executeQuery("SELECT loser,winner,scoreWinner,scoreLoser FROM statistics WHERE winner=\"" + login + "\"");

            while (resultSet.next()) {
                statistics.add(new Statistic(resultSet.getString("loser"),resultSet.getString("winner"),resultSet.getInt("scoreWinner")));

            }
            ResultSet resultSet2 = statement.executeQuery("SELECT loser,winner,scoreWinner,scoreLoser FROM statistics WHERE loser=\"" + login + "\"");
            while (resultSet2.next()) {
                statistics.add(new Statistic(resultSet.getString("loser"),resultSet.getString("winner"),resultSet.getInt("scoreLoser")));

            }



        } catch (SQLException e) {
            e.printStackTrace();

        }
        return statistics;
    }




    private boolean checkLogin(String login) {
        try (Statement statement = this.connection.createStatement()) {

            ResultSet resultSet = statement.executeQuery("SELECT id,login,password FROM users WHERE login=\"" + login + "\"");

            if (resultSet.next()) {
                return true;
            }
            return false;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }

    }

    public boolean addUser(String login, String password) {
        if (!checkLogin(login)) {
            try (PreparedStatement statement = this.connection.prepareStatement(
                    "INSERT INTO users(`login`, `password`) " +
                            "VALUES(?, ?)")) {
                statement.setObject(1, login);
                statement.setObject(2, password);
                statement.execute();
            } catch (SQLException e) {
                e.printStackTrace();
                return false;
            }
        } else {
            return false;
        }
        return true;
    }
}
