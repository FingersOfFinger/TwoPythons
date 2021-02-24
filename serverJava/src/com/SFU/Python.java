package com.SFU;

import java.awt.*;
import java.util.Vector;

public class Python {
    public Vector<Point> dots = new Vector<>();
    Direction direction = Direction.right;

    public void setFirstDots(Point p1, Point p2, Point p3) {
        dots.add(p1);
        dots.add(p2);
        dots.add(p3);
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
