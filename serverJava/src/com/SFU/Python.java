package com.SFU;

import java.awt.*;
import java.util.Vector;

public class Python {
    public Vector<Point> dots = new Vector<>();
    Direction direction;
    public int points = 0;
    public Color color = new Color((int) (Math.random() * 255), (int) (Math.random() * 230), (int) (Math.random() * 200));


    Python(Vector<Python> pythons) {
        boolean flag;
        while (true) {
            flag=true;
            dots.add(new Point((int) (Math.random() * 16) + 3, (int) (Math.random() * 16) + 3));
            int random = (int) (Math.random() * 3);
            dots.add(new Point(0,0));
            dots.add(new Point(0,0));
            switch (random) {
                case 0:
                    direction = Direction.left;
                    break;
                case 1:
                    direction = Direction.right;

                case 2:
                    direction = Direction.up;
                    break;
                case 3:
                    direction = Direction.down;
                    break;
            }
            this.move();
            this.move();




            for(int i=0;i<pythons.size();i++)
                if(pythons.get(i).dots.contains(this.dots)){
                    flag=false;
                }
            if(flag)
                break;
            dots.clear();
        }
    }

    public void setDirection(String inDirection) {
        switch (inDirection) {
            case ("up"):
                if (!direction.equals(Direction.down))
                    direction = Direction.up;
                break;
            case ("down"):
                if (!direction.equals(Direction.up))
                    direction = Direction.down;
                break;
            case ("left"):
                if (!direction.equals(Direction.right))
                    direction = Direction.left;
                break;
            case ("right"):
                if (!direction.equals(Direction.left))
                    direction = Direction.right;
                break;


        }

    }

    public void height() {
        dots.add(new Point(0, 0));
    }

    public void move() {
        for (int i = dots.size() - 1; i > 0; --i) {
            dots.get(i).x = dots.get(i - 1).x;
            dots.get(i).y = dots.get(i - 1).y;
        }

        switch (direction) {
            case left:
                dots.get(0).x -= 1;
                break;
            case right:
                dots.get(0).x += 1;
                break;
            case up:
                dots.get(0).y -= 1;
                break;
            case down:
                dots.get(0).y += 1;
                break;
        }

    }
}
