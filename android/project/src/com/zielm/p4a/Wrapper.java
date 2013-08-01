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

        ActivityManager mgm = (ActivityManager) context.getSystemService(Activity.ACTIVITY_SERVICE);
        Log.i("Wrapper", "memory: " + mgm.getLargeMemoryClass());

        (new Thread() {
                public void run() {
                    init();
                }
            }).start();
    }

    public static void init() {
        extractApp();
        uiReadyEvent.waitFor();
        String pythonPath = context.getFilesDir().getAbsolutePath();
        init0(pythonPath);
    }

    static void extractApp() {
        if(!checkSerial()) {
            extractDir("code", "");
            extractDir("res", "data");
            writeSerial();
        }
    }

    static boolean checkSerial() {
        try {
            String pkgSerial =
                new BufferedReader(new InputStreamReader(context.getAssets().open("serial"))).readLine();
            String oldSerial =
                new BufferedReader(new FileReader(context.getFilesDir() + "/serial")).readLine();
            return pkgSerial.equals(oldSerial);
        } catch(IOException err) {
            err.printStackTrace();
            return false;
        }
    }

    static void writeSerial() {
        try {
            String pkgSerial =
                new BufferedReader(new InputStreamReader(context.getAssets().open("serial"))).readLine();
            FileWriter writer = new FileWriter(context.getFilesDir() + "/serial");
            writer.write(pkgSerial + "\n");
            writer.close();
        } catch(IOException err) {
            throw new RuntimeException(err);
        }
    }

    static void extractDir(String name, String target) {
        Log.i(TAG, "extracting " + name);
        try {
            File targetFile = new File(context.getFilesDir() + "/" + target);
            targetFile.mkdirs();
            InputStream in = context.getAssets().open(name + ".archive");
            ZipUtils.extract(in, targetFile);
        } catch(IOException err) {
            throw new RuntimeException(err);
        }
        Log.i(TAG, "done extracting " + name);
    }

    public static Context context;
    public static SurfaceHolder surfaceHolder;
    public static WrapperView view;
    public static Event uiReadyEvent = new Event();
    public static native void init0(String pythonPath);
}
