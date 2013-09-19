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
    public static boolean downloaded = false;
    public static boolean downloadedSuccess = false;
    static Queue<String> messages = new LinkedList<String>();

    public synchronized static String getMessage() {
        return messages.poll();
    }

    synchronized static void addMessage(String s) {
        messages.offer(s);
    }

    public synchronized static void init() {
        SDLActivity.mSingleton.runOnUiThread(new Runnable() {
                public void run(){
                    if(mDBApi == null) {
                        AppKeyPair appKeys = new AppKeyPair(APP_KEY, APP_SECRET);
                        AndroidAuthSession session;
                        if(tokenKey != null) {
                            AccessTokenPair tokens = new AccessTokenPair(tokenKey, tokenSecret);
                            Log.v(TAG, "using old tokens " + tokens);
                            session = new AndroidAuthSession(appKeys, ACCESS_TYPE, tokens);
                        } else {
                            Log.v(TAG, "need new tokens");
                            session = new AndroidAuthSession(appKeys, ACCESS_TYPE);
                        }
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

    public static void setTokens(String key, String secret) {
        tokenKey = key;
        tokenSecret = secret;
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
                Log.v(TAG, "tokens set to " + tokenKey + " " + tokenSecret);
            } catch (IllegalStateException e) {
                Log.i("DbAuthLog", "Error authenticating", e);
            }
            authFinished = true;
        }
    }

    public static void uploadFile(final String path, final String name) {
        (new Thread() {
                public void run() {
                    uploadFileBlocking(path, name);
                }
            }).start();
    }

    static void uploadFileBlocking(String path, String name) {
        try {
            File file = new File(path);
            FileInputStream inputStream = new FileInputStream(file);
            DropboxAPI.Entry response = mDBApi.putFile("/" + name, inputStream,
                                                       file.length(), null, null);
            Log.i(TAG, "uploaded file as " + response.rev);
            addMessage("save uploaded to Dropbox/Applications/Freeciv");
        } catch(IOException ex) {
            ex.printStackTrace();
            addMessage("Upload failed. Try again. (" + ex + ")");
        } catch(DropboxUnlinkedException ex) {
            ex.printStackTrace();
            tellNeedAuth();
        } catch(DropboxException ex) {
            addMessage("Upload failed. Try again. (" + ex + ")");
            ex.printStackTrace();
        }
    }

    public static void listDirectory() {
        (new Thread() {
                public void run() {
                    listDirectoryBlocking();
                }
            }).start();
    }

    public static List<DropboxAPI.Entry> result;

    public static String getPath(DropboxAPI.Entry e) {
        return e.path;
    }


    public static void printList(List<DropboxAPI.Entry> l) {
        System.err.println("printing list " + l.getClass());
        for(int i=0; i<l.size(); i++)
            System.err.println("list item " + i + "=" + l.get(i) + " " + l.get(i).path);
    }

    static void listDirectoryBlocking() {
        result = null;
        try {
            DropboxAPI.Entry ls = mDBApi.metadata("/", 1000, null, true, null);
            System.out.println("Files in the root path: " + ls.contents);
            result = ls.contents;
        } catch(DropboxUnlinkedException ex) {
            ex.printStackTrace();
            tellNeedAuth();
            result = new ArrayList<DropboxAPI.Entry>();
        } catch(DropboxException ex) {
            addMessage("Listing failed. Try again. (" + ex + ")");
            ex.printStackTrace();
            result = new ArrayList<DropboxAPI.Entry>();
        }
    }

    static void tellNeedAuth() {
        needAuth = true;
        //addMessage("You need to login.");
    }

    public static void downloadFile(final String path, final String outputPath) {
        downloaded = false;
        (new Thread() {
                public void run() {
                    downloadFileBlocking(path, outputPath);
                }
            }).start();
    }

    public static void downloadFileBlocking(String path, String outputPath) {
        downloadedSuccess = false;
        try{
            OutputStream output = new FileOutputStream(new File(outputPath));
            mDBApi.getFile(path, null, output, null);
            Log.i(TAG, "downloaded file  " + path + " as " + outputPath);
            downloadedSuccess = true;
        } catch(IOException ex) {
            ex.printStackTrace();
            addMessage("Download failed. Try again. (" + ex + ")");
        } catch(DropboxUnlinkedException ex) {
            ex.printStackTrace();
            tellNeedAuth();
        } catch(DropboxException ex) {
            addMessage("Download failed. Try again. (" + ex + ")");
            ex.printStackTrace();
        }
        downloaded = true;
    }
}
