package org.renpy.android;

import android.app.*;
import android.widget.*;
import android.view.*;
import android.content.*;

public class Dialogs {
    public static String retval = "";
    
    public static Object showInputDialog(final String title, final String message, final String default_) {
        Dialogs.retval = "";
        ((Activity)Hardware.context).runOnUiThread(new Runnable(){
            public void run() {
                AlertDialog.Builder alert = new AlertDialog.Builder(Hardware.context);
                
                alert.setTitle(title);
                alert.setMessage(message);
                
                // Set an EditText view to get user input 
                final EditText input = new EditText(Hardware.context);
                alert.setView(input);
                
                alert.setPositiveButton("Ok", new DialogInterface.OnClickListener() {
                public void onClick(DialogInterface dialog, int whichButton) {
                        String value = input.getText().toString();
                        Dialogs.retval = "ok:" + value;
                    }
                });
                
                alert.setNegativeButton("Cancel", new DialogInterface.OnClickListener() {
                    public void onClick(DialogInterface dialog, int whichButton) {
                        Dialogs.retval = "cancal:";
                    }
                });
                
                alert.show();
            }
        });
        return null;
    }
    
    public static String getRetVal() {
        return retval;
    }
}