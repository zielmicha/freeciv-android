package com.zielm.freeciv;

import com.dropbox.client2.*;
import com.dropbox.client2.session.*;
import com.dropbox.client2.android.*;
import com.dropbox.client2.exception.*;
import org.libsdl.app.*;

public class DropboxHelper {
    final static private String APP_KEY = "31sn2p1jkkwev8c";
    final static private String APP_SECRET = "mf7kp87rgzy332k";
    final static private Session.AccessType ACCESS_TYPE =
        Session.AccessType.APP_FOLDER;
    private static DropboxAPI<AndroidAuthSession> mDBApi;

    public static void init() {
        SDLActivity.mSingleton.runOnUiThread(new Runnable() {
                public void run(){
                    AppKeyPair appKeys = new AppKeyPair(APP_KEY, APP_SECRET);
                    AndroidAuthSession session = new AndroidAuthSession(appKeys, ACCESS_TYPE);
                    mDBApi = new DropboxAPI<AndroidAuthSession>(session);
                }
            });
    }

    public static void doAuth() {
        SDLActivity.mSingleton.runOnUiThread(new Runnable() {
                public void run(){
                    mDBApi.getSession().startAuthentication(SDLActivity.mSingleton);
                }
            });
    }
}
