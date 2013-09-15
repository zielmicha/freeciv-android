package com.zielm.freeciv;

import com.dropbox.client2.*;
import com.dropbox.client2.session.*;
import com.dropbox.client2.android.*;
import com.dropbox.client2.exception.*;
import org.libsdl.app.*;
import java.io.*;
import java.util.*;
import android.util.Log;

public class DropboxHelper {
    final static private String APP_KEY = "31sn2p1jkkwev8c";
    final static private String APP_SECRET = "mf7kp87rgzy332k";
    final static private Session.AccessType ACCESS_TYPE =
        Session.AccessType.APP_FOLDER;
    private static DropboxAPI<AndroidAuthSession> mDBApi;
    final static private String TAG = "freeciv-dropbox";

    public static String tokenKey = null;
    public static String tokenSecret = null;
    public static boolean authFinished;
    public static boolean needAuth = false;
    static Queue<String> messages = new LinkedList<String>();

    public synchronized static String getMessage() {
        return messages.peek();
    }

    synchronized static void addMessage(String s) {
        messages.offer(s);
    }

    public synchronized static void init() {
        SDLActivity.mSingleton.runOnUiThread(new Runnable() {
                public void run(){
                    if(mDBApi == null) {
                        AppKeyPair appKeys = new AppKeyPair(APP_KEY, APP_SECRET);
                        AndroidAuthSession session = new AndroidAuthSession(appKeys, ACCESS_TYPE);
                        mDBApi = new DropboxAPI<AndroidAuthSession>(session);
                    }
                    synchronized(DropboxHelper.class) {
                            DropboxHelper.class.notify();
                    }
                }
            });
        try {
            DropboxHelper.class.wait();
        } catch(InterruptedException ex) {}
    }

    public static void useTokens() {
        SDLActivity.mSingleton.runOnUiThread(new Runnable() {
                public void run() {
                    mDBApi.getSession().setAccessTokenPair(new AccessTokenPair(tokenKey, tokenSecret));
                }
            });
    }

    public static void doAuth() {
        authFinished = false;
        SDLActivity.mSingleton.runOnUiThread(new Runnable() {
                public void run(){
                    mDBApi.getSession().startAuthentication(SDLActivity.mSingleton);
                }
            });
    }

    public static void onResume() {
        if (mDBApi != null && mDBApi.getSession().authenticationSuccessful()) {
            try {
                Log.v(TAG, "onResume()");
                mDBApi.getSession().finishAuthentication();

                AccessTokenPair tokens = mDBApi.getSession().getAccessTokenPair();
                Log.v(TAG, "tokens " + tokens);
                tokenKey = tokens.key;
                tokenSecret = tokens.secret;
            } catch (IllegalStateException e) {
                Log.i("DbAuthLog", "Error authenticating", e);
            }
            authFinished = true;
        }
    }

    public static void uploadFile(String path, String name) {
        try {
            File file = new File(path);
            FileInputStream inputStream = new FileInputStream(file);
            DropboxAPI.Entry response = mDBApi.putFile("/" + name, inputStream,
                                                       file.length(), null, null);
            Log.i(TAG, "uploaded file as " + response.rev);
            addMessage("save uploaded to Dropbox/Applications/Freeciv");
        } catch(IOException ex) {
            ex.printStackTrace();
            // do something
        } catch(DropboxUnlinkedException ex) {
            ex.printStackTrace();
            tellNeedAuth();
        } catch(DropboxException ex) {
            ex.printStackTrace();
        }
    }

    static void tellNeedAuth() {
        needAuth = true;
        //addMessage("You need to login.");
    }
}
