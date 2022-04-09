package com.uwtsd.socialrps;

enum EStates {
    pending,
    received
}

public class State extends Thread {
    EStates state;

    @Override
    public void run()
    {
        // loop State til pending isn't True
        while(state == EStates.pending);
        System.out.println("Here");
    }

    protected void SetState(EStates state)
    { this.state = state; }
}
