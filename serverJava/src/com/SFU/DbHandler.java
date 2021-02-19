package com.SFU;

import java.sql.*;

import org.sqlite.JDBC;



public class DbHandler {
    private static final String CON_STR = "jdbc:sqlite:resources/users.db";


    private static DbHandler instance = null;

    public static synchronized DbHandler getInstance()  {
        if (instance == null) {
            try {
                instance = new DbHandler();
            } catch (SQLException throwables) {
                throwables.printStackTrace();
            }
        }
        return instance;
    }

    // Объект, в котором будет храниться соединение с БД
    private Connection connection;

    private DbHandler() throws SQLException {
        // Регистрируем драйвер, с которым будем работать
        // в нашем случае Sqlite
        DriverManager.registerDriver(new JDBC());
        // Выполняем подключение к базе данных
        this.connection = DriverManager.getConnection(CON_STR);
    }

    public boolean checkUser(String login, String password) {
        System.out.println("checkUser");
        try (Statement statement = this.connection.createStatement()) {

            ResultSet resultSet = statement.executeQuery("SELECT id,login,password FROM users WHERE login=\""+login+"\" AND password=\""+password+"\"");

            if(resultSet.next()){
                return true;
            }
            return false;

        } catch (SQLException e) {
            e.printStackTrace();
            return false;
        }
    }
}
