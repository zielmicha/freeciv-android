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

public class WrapperView extends SurfaceView implements SurfaceHolder.Callback {

    public WrapperView(Context c) {
        super(c);
        getHolder().addCallback(this);
    }

    void myRedraw() {
        android.graphics.Canvas canvas = getHolder().lockCanvas();
        if(canvas != null) {
            onDraw(canvas);
            getHolder().unlockCanvasAndPost(canvas);
        }
    }

    public void surfaceChanged(SurfaceHolder holder, int format, int width, int height) {}

    public void surfaceCreated(SurfaceHolder holder) {
        Wrapper.surfaceHolder = holder;
    }

    public void surfaceDestroyed(SurfaceHolder holder) {
        Wrapper.surfaceHolder = null;
    }

    @Override
    protected void onSizeChanged(int w, int h, int oldw, int oldh) {

    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event) {
        return true;
    }

    @Override
    public boolean onKeyUp(int keyCode, KeyEvent event) {
        return true;
    }

    @Override
    public boolean onTouchEvent(MotionEvent event) {
        return true;
    }
}
