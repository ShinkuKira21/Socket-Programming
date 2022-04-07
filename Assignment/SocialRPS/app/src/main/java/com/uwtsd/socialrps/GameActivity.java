package com.uwtsd.socialrps;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

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
