package com.uwtsd.socialrps;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;

import com.uwtsd.socialrps.databinding.ActivityGameBinding;

public class GameActivity extends AppCompatActivity {
    private ActivityGameBinding binding;
    private AnimationThreads animFindingGame;
    GameManager gameManager;
    private String playerName;

    private long gameActivity;

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

        FindGame();

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


        if(animFindingGame != null && animFindingGame.isAlive())
        {
            animFindingGame.StopAnim();
        }

        DeconstructGameActivity(gameActivity);
    }

    private void FindGame()
    {
        // animate finding game.
        binding.linlayLoad.setVisibility(View.VISIBLE);
        animFindingGame = new AnimationThreads(binding.txtStatus);
        animFindingGame.start();

        gameActivity = InitiateGameActivity(playerName);
        int status = JoinGame(gameActivity);
        if(status <= 0) {
            System.out.println("Error!");
            onBackPressed();
        }

        Thread startGame = new Thread(() -> {
            while(StartGame(gameActivity) == 0)
            {
                try {
                    Thread.sleep(100);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            }
        });
        startGame.start();
    }

    private native long InitiateGameActivity(String username);
    private native int JoinGame(long gameActivity);
    private native int StartGame(long gameActivity);
    private native void DeconstructGameActivity(long gameActivity);
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
