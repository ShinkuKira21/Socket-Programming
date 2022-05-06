package com.uwtsd.socialrps;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;

import com.uwtsd.socialrps.databinding.ActivityGameBinding;

interface INET4ADDRESS {
    String ip = "3.11.23.103";
    int port = 50018;
}

public class GameActivity extends AppCompatActivity {
    private ActivityGameBinding binding;
    private AnimationThreads animFindingGame;
    GameManager gameManager;
    private String playerName;

    private long cInstance;

    static {
        System.loadLibrary("socialrps");
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);

        binding = ActivityGameBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        playerName = getIntent().getExtras().get("socialrps.playerName").toString();

        //FindGame();
        // Binding setup for actions
        gameManager = new GameManager(binding, playerName);
    }

    @Override
    public void onBackPressed()
    {
        super.onBackPressed();

        Intent intent = new Intent(this, MainActivity.class);
        intent.putExtra("socialrps.playerName", playerName);
        startActivity(intent);
        finish();
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();

        try {
            if(animFindingGame != null && animFindingGame.isAlive())
            {
                animFindingGame.StopAnim();
                animFindingGame.join();
            }

        } catch (InterruptedException e) {
            e.printStackTrace();
            animFindingGame.interrupt();
        }

        DeconstructConnectionInstance(cInstance);
    }

    private void FindGame()
    {
        // animate finding game.
        binding.linlayLoad.setVisibility(View.VISIBLE);
        animFindingGame = new AnimationThreads(binding.txtStatus);
        animFindingGame.start();

        cInstance = InitiateConnectionInstance(INET4ADDRESS.ip, INET4ADDRESS.port, playerName);

    }

    private native long InitiateConnectionInstance(String ip, int port, String username);
    private native void DeconstructConnectionInstance(long cInstance);
}

class GameManager
{
    private String playerName;
    private int selection;

    public GameManager(ActivityGameBinding binding, String playerName)
    {
        this.playerName = playerName;
        ImageButton[] imgBtnArray = {binding.ibtnRock, binding.ibtnPaper, binding.ibtnScissors};

        for(int i = 0; i < imgBtnArray.length; i++)
            BindAction(imgBtnArray, i);
    }

    public int GetSelection()
    { return selection; }

    private void BindAction(ImageButton[] imgBtnArray, int i)
    {
        imgBtnArray[i].setOnClickListener((View.OnClickListener) view -> {
            for (int j = 0; j < imgBtnArray.length; j++)
            {
                if(j == i) continue;
                imgBtnArray[j].setVisibility(View.INVISIBLE);
            }

            imgBtnArray[i].setOnClickListener(null);
            selection = i;
        });
    }
}
