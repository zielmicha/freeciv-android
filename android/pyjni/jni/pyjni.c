#include <jni.h>
#include <stdio.h>
#include <android/log.h>
#include <Python.h>
#include <string.h>
#include <stdlib.h>
JNIEnv *SDL_ANDROID_GetJNIEnv(void);
#define aassert(x) { if (!x) { __android_log_print(ANDROID_LOG_ERROR, "android_jni", "Assertion failed. %s:%d", __FILE__, __LINE__); abort(); }}
#define alog(x) __android_log_print(ANDROID_LOG_ERROR, "android_jni", x)


PyObject* make_input_dialog(PyObject* self, PyObject* args) {
    char* title;
    char* msg;
    char* default_;
    
    if(!PyArg_ParseTuple(args, "sss", &title, &msg, &default_))
        return NULL;
    
    JNIEnv* env = SDL_ANDROID_GetJNIEnv();
    aassert(env);
    
    (*env)->PushLocalFrame(env, 16);
    
    jclass cls = (*env)->FindClass(env, "org/renpy/android/Dialogs");
    aassert(cls);
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "showInputDialog", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
    aassert(mid);
    jstring title_string = (*env)->NewStringUTF(env, title);
    jstring msg_string = (*env)->NewStringUTF(env, msg);
    jstring default_string = (*env)->NewStringUTF(env, default_);
    (*env)->CallStaticObjectMethod(env, cls, mid, title_string, msg_string, default_string);
    
    env->PopLocalFrame(env, NULL);
    
    return Py_BuildValue("");
}

PyObject* get_dialog_retval(PyObject* self, PyObject* args) {
    if(!PyArg_ParseTuple(args, ""))
        return NULL;
    
    JNIEnv* env = SDL_ANDROID_GetJNIEnv();
    aassert(env);
    
    (*env)->PushLocalFrame(env, 16);
    
    jclass cls = (*env)->FindClass(env, "org/renpy/android/Dialogs");
    aassert(cls);
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "getRetVal", "()Ljava/lang/String;");
    aassert(mid);
    jobject obj = (*env)->CallStaticObjectMethod(env, cls, mid);
    
    const char* retval = (*env)->GetStringUTFChars(env, obj, NULL); // memory leak?
    char* safe_retval = malloc(strlen(retval));
    strcpy(safe_retval, retval);
    
    env->PopLocalFrame(env, NULL);
    
    return Py_BuildValue("s", safe_retval);
}



static PyMethodDef PyjniMethods[] = {
    {"make_input_dialog", make_input_dialog, METH_VARARGS, ""},
    {"get_dialog_retval", get_dialog_retval, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initpyjni(void)
{
    (void) Py_InitModule("pyjni", PyjniMethods);
}