package com.uwtsd.socialrps;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;
import android.widget.ImageButton;

import androidx.appcompat.app.AppCompatActivity;

import com.uwtsd.socialrps.databinding.ActivityGameBinding;

public class GameActivity extends AppCompatActivity {
    // loads network manager
    static {
        System.loadLibrary("socialrps");
    }

    private ActivityGameBinding binding;
    private AnimationThreads animFindingGame;
    private String playerName;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        binding = ActivityGameBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());
        playerName = getIntent().getExtras().get("socialrps.playerName").toString();

        //FindGame();
        // Binding setup for actions
        ActionManager actionManager = new ActionManager(binding);
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
            animFindingGame.StopAnim();
            animFindingGame.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
        }
    }

    private void FindGame()
    {
        // animate finding game.
        binding.linlayLoad.setVisibility(View.VISIBLE);
        animFindingGame = new AnimationThreads(binding.txtStatus);
        animFindingGame.start();
    }
}

class ActionManager
{
    private int selection;

    public ActionManager(ActivityGameBinding binding)
    {
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
        });
    }
}
