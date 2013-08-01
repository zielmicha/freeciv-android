package com.zielm.p4a;

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
import java.io.*;

public class Wrapper {
    static {
        System.loadLibrary("python2.7");
        System.loadLibrary("freeciv");
        System.loadLibrary("main");
    }

    private static final String TAG = "PythonWrapper";

    public static void onCreate(Activity activity) {
        Wrapper.context = activity;
        activity.setContentView(view = new WrapperView(activity));

        (new Thread() {
                public void run() {
                    init();
                }
            }).start();
    }

    public static void init() {
        extractApp();
        String pythonPath = context.getFilesDir() + "/code";
        init0(pythonPath);
    }

    static void extractApp() {
        extractDir("code");
    }

    static void extractDir(String name) {
        Log.i(TAG, "extracting " + name);
        try {
            InputStream in = context.getAssets().open(name + ".archive");
            ZipUtils.extract(in, new File(context.getFilesDir() + "/" + name));
        } catch(IOException err) {
            throw new RuntimeException(err);
        }
        Log.i(TAG, "done extracting " + name);
    }

    public static Context context;
    public static SurfaceHolder surfaceHolder;
    public static WrapperView view;
    public static native void init0(String pythonPath);
}
