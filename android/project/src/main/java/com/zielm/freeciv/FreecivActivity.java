package com.zielm.freeciv;

import org.libsdl.app.SDLActivity;

import android.app.*;
import android.content.*;
import android.os.*;
import android.content.pm.PackageManager;
import android.Manifest;
import android.support.v4.content.ContextCompat;
import android.support.v4.app.ActivityCompat;


public class FreecivActivity extends SDLActivity implements ActivityCompat.OnRequestPermissionsResultCallback {
	private Object requestPermissionsMonitor = new Object();

	public static SDLActivity getSingleton() {
		return mSingleton;
	}

	@Override
	protected String[] getLibraries() {
		return new String[] { "SDL2", "SDL2_image", "SDL2_mixer", "SDL2_ttf", "python2.7", "freeciv-client", "main" };
	}

	// Called by onCreate()
	@Override
	public void loadLibraries() {
		super.loadLibraries();
		requestStoragePermissions();
	}

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState); // Calls loadLibraries()
		if (haveStoragePermissions()) {
			setWindowStyle(true); // fullscreen
		} else {
			// Avoid to start the app because it'll crash.
			// Replace the startup thread with an empty thread.
			mSDLThread = new Thread(new Runnable() {
					@Override public void run() {}
				},
				"SDLThread");
			mSDLThread.start();

			AlertDialog.Builder dlgAlert  = new AlertDialog.Builder(this);
	        dlgAlert.setMessage("Freeciv cannot start without access to storage.");
	        dlgAlert.setTitle("Storage access required");
	        dlgAlert.setPositiveButton("Exit",
	            new DialogInterface.OnClickListener() {
	                @Override
	                public void onClick(DialogInterface dialog,int id) {
	                    // if this button is clicked, close current activity
	                    SDLActivity.mSingleton.finish();
	                }
	            });
	       dlgAlert.setCancelable(false);
	       dlgAlert.create().show();
		}
	}

	private void requestStoragePermissions() {
		if (!haveStoragePermissions()) {
			String[] requiredPermissions = {Manifest.permission.WRITE_EXTERNAL_STORAGE, Manifest.permission.READ_EXTERNAL_STORAGE};
			ActivityCompat.requestPermissions(this, requiredPermissions, 1);
			synchronized(requestPermissionsMonitor) {
				try {
					// Dirty fix because I don't know why requestPermissionsMonitor.wait(0) never wakes up
					// => lets'do some polling during a maximum of 1 minute
					for (int i=0; i<240 && !haveStoragePermissions();i++) {
						requestPermissionsMonitor.wait(250);
					}
				} catch (InterruptedException ex) {
					ex.printStackTrace();
				}
			}
		}
	}

	@Override
	public void onRequestPermissionsResult(int requestCode, String permissions[], int[] grantResults) {
		synchronized(requestPermissionsMonitor) {
			requestPermissionsMonitor.notify();
		}
	}

	private boolean haveStoragePermissions() {
		return ContextCompat.checkSelfPermission(this, Manifest.permission.WRITE_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED
			&& ContextCompat.checkSelfPermission(this, Manifest.permission.READ_EXTERNAL_STORAGE) == PackageManager.PERMISSION_GRANTED;
	}
}

