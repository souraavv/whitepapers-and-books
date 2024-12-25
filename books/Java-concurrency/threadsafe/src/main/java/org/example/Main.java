package org.example;

import static org.junit.jupiter.api.Assertions.assertEquals;

import org.junit.jupiter.api.Test;


public class Main {
    @Test
    public static void testChapter4() throws InterruptedException {
        final Chapter4 chapter4 = new Chapter4();
        int numThreads = 8;
        int incrementPerThread = 10;

        Thread[] threads = new Thread[numThreads];
        for (int i = 0; i < numThreads; i++) {
            System.out.println("running thread " + i);
            threads[i] = new Thread(() -> {
               for (int j = 0; j < incrementPerThread; j++) {
                   chapter4.increment();
               }
            });
            threads[i].start();
        }
        for (Thread thread : threads) {
            thread.join();
        }
        long expectedValue = numThreads * incrementPerThread;
        long actualValue = chapter4.getValue();
        assertEquals(expectedValue, actualValue);
        System.out.println("Expected value " + expectedValue);
        System.out.println("Actual value " + actualValue);
    }

    public static void main(String[] args) {
        try {
            testChapter4();
        } catch (Exception e) {
            
        }
    }
}