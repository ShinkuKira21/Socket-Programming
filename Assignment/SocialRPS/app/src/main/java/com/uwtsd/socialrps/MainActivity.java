package com.uwtsd.socialrps;

import android.content.Intent;
import android.os.Bundle;
import android.view.View;

import androidx.appcompat.app.AppCompatActivity;
import com.uwtsd.socialrps.databinding.ActivityStartBinding;

public class MainActivity extends AppCompatActivity {
    // Used to load the 'socialrps' library on application startup.
    static {
        System.loadLibrary("socialrps");
    }

    private ActivityStartBinding binding;
    private AnimationThreads animTitle;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        /* Update: When I did the StaySafe application in Changemakers year 2,  ActivityMainBinding seems to manage the findViewById functionality. */ // https://medium.com/kayvan-kaseb/view-binding-say-bye-to-findviewbyid-67fc643f91f8
        binding = ActivityStartBinding.inflate(getLayoutInflater());
        setContentView(binding.getRoot());

        // loops til closes
        AnimateTitle();

        Intent intent = new Intent(this, GameActivity.class);
        binding.btnFindGame.setOnClickListener((View.OnClickListener) view -> {
            if(binding.txtbxPlayerName.getText().toString().contains(" "))
                binding.txtError.setText(R.string.socialrps_space_charcter);

            else if(!binding.txtbxPlayerName.getText().toString().isEmpty()) {
                binding.txtError.setVisibility(View.INVISIBLE);
                intent.putExtra("socialrps.playerName", binding.txtbxPlayerName.getText());
                startActivity(intent);
                finish();
            }
            else binding.txtError.setText(R.string.socialrps_name_empty);
        });
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
        try {
            animTitle.StopAnim();
            animTitle.join();
        } catch (InterruptedException e) {
            e.printStackTrace();
            animTitle.interrupt();
        }
    }

    private void AnimateTitle()
    {
        animTitle = new AnimationThreads(binding.txtTitle);
        animTitle.start();
    }
}