package com.company;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Stack;

public class Main {

    public static void main(String[] args) {
        Stack<Integer> stack = new Stack<Integer>();
        Queue<Integer> queue = new LinkedList<>();
        for (int i=0;i<10;i++)
        {
            stack.push(i);
        }
        int size = stack.size();
        for (int i=0;i<size;i++)
        {
            queue.add(stack.pop());
        }
        for (int i=0;i<size/2;i++ )
        {
            int currentSize = size/2 - i - 1;
            for (int j=0;j<currentSize;j++)
            {
                queue.add(queue.remove());
                System.out.println(queue.element());
            }
            System.out.println("*" + queue.element());
            stack.push(queue.remove());
            if (currentSize == 0)
            {
                break;
            }
            for (int j=0;j<size/2;j++)
            {
                queue.add(queue.remove());
                System.out.println("+" + queue.element());
            }
        }

        while (queue.size() > 0 )
        {
            stack.push(queue.remove());
        }
        for (int i=0;i<size/2;i++)
        {
            queue.add(stack.pop());
        }
        while (queue.size() > 0 )
        {
            stack.push(queue.remove());
        }


        System.out.println(stack);
    }
}
