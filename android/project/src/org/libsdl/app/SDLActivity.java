package org.libsdl.app;

import android.app.*;
import android.content.*;
import android.view.*;
import android.view.inputmethod.*;
import android.widget.*;
import android.os.*;
import android.util.Log;
import android.graphics.*;
import android.text.method.*;
import android.text.*;
import android.media.*;
import android.hardware.*;
import android.content.*;

import java.lang.*;
import java.util.*;
import com.zielm.p4a.*;

/**
    Not really SDL Activity - keeping activity name
    for backwards compatibility.
*/
public class SDLActivity extends Activity {
    @Override
    protected void onCreate(Bundle src) {
        super.onCreate(src);
        Log.i("com.zielm.p4a", "BEGIN");
        Wrapper.onCreate(this);
    }
}
