package com.SFU;

import java.awt.*;
import java.util.Vector;

public class Python {
    public Vector<Point> dots = new Vector<>();
    Direction direction;


    Python(int keyGeneration) {
        switch (keyGeneration){
            case 1:
                dots.add(new Point(2,0));
                dots.add(new Point(1, 0));
                dots.add(new Point(0, 0));
                direction = Direction.right;
                break;
            case 2:
                dots.add(new Point(2,19));
                dots.add(new Point(1, 19));
                dots.add(new Point(0, 19));
                direction = Direction.right;
                break;
            case 3:
                dots.add(new Point(17,0));
                dots.add(new Point(18, 0));
                dots.add(new Point(19, 0));
                direction = Direction.left;
                break;
            case 4:
                dots.add(new Point(17,19));
                dots.add(new Point(18, 19));
                dots.add(new Point(19, 19));
                direction = Direction.left;
                break;
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
