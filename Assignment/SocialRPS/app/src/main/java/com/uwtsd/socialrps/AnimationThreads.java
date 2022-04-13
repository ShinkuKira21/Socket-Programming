package com.uwtsd.socialrps;

import android.widget.TextView;

public class AnimationThreads extends Thread {
    private Boolean bRunning;
    private final TextView textView;
    private final int min, max;

    AnimationThreads(TextView textView)
    {
        bRunning = true;
        this.textView = textView;
        min = 0; max = 75;
    }

    @Override
    public void run()
    {
        int pos = 0;
        int currentX = 1;
        int swap = 0;

        while(bRunning) {
            try {
                join(25);
            } catch (InterruptedException e) {
                e.printStackTrace();
                interrupt();
            } finally {
                currentX = Limit(pos, currentX);
                pos += currentX;

                if(pos == 0 && swap == 2)
                    swap = 0;

                else if(pos == 0)
                    swap += 1;

                if(swap != 2) textView.setRotationX(pos);
                else textView.setTranslationY(pos);
            }
        }

        // resets view
        textView.setRotationX(0);
        textView.setTranslationY(0);
    }

    public void StopAnim()
    {
        bRunning = false;
    }

    private int Limit(int pos, int current)
    {
        if(pos == max)
            return -1;

        else if(pos == min)
            return 1;

        return current;
    }
}
