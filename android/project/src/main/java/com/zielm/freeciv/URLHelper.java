package com.zielm.freeciv;

import java.net.*;
import java.io.*;

public class URLHelper implements Runnable {
    String error;
    String result;
    String urlString;
    String uaString;

    public String getError() {
        return error;
    }

    public String getResult() {
        return result;
    }

    public boolean isFinished() {
        return error != null || result != null;
    }

    public URLHelper(String url, String ua) {
        urlString = url;
        uaString = ua;
        new Thread(this).start();
    }

    public void run() {
        try {
            URL url = new URL(urlString);
            HttpURLConnection urlConnection = (HttpURLConnection) url.openConnection();
            urlConnection.setRequestProperty("User-agent", uaString);
            result = readFileToString(urlConnection.getInputStream());
        } catch(Exception ex) {
            error = ex.toString();
        }
    }

    private String readFileToString (InputStream file) throws IOException {
        BufferedReader reader = new BufferedReader(new InputStreamReader(file));
        String line = null;
        StringBuilder stringBuilder = new StringBuilder();

        while((line = reader.readLine()) != null) {
            stringBuilder.append(line);
            stringBuilder.append("\n");
        }

        return stringBuilder.toString();
    }
}
