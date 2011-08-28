package org.renpy.android;
import android.content.*;
import android.net.*;
public class MyHardware {
	public static Object open_intent(String type, String url) {
		Intent myIntent = new Intent(type, Uri.parse(url));

		Hardware.context.startActivity(myIntent);
		return null;
	}
}