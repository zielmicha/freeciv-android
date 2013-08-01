package com.zielm.p4a;

public class Event {
    // port of Python's Event

    private boolean _set = false;

    public synchronized void set() {
        _set = true;
        notifyAll();
    }

    public synchronized void waitFor() {
        if(_set)
            return;
        try {
            wait();
        } catch(InterruptedException ex) {
            throw new Error(ex);
        }
    }
}
