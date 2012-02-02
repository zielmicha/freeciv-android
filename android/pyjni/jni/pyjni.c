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
    
    (*env)->PopLocalFrame(env, NULL);
    
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
    
    (*env)->PopLocalFrame(env, NULL);
    
    return Py_BuildValue("s", safe_retval);
}

PyObject* encode_or_decode_xz(PyObject* self, PyObject* args) {
    int length;
    char* data;
    int mode;
    if(!PyArg_ParseTuple(args, "is#", &mode, &data, &length))
        return NULL;
    
    JNIEnv* env = SDL_ANDROID_GetJNIEnv();
    aassert(env);
    
    (*env)->PushLocalFrame(env, 16);
    
    jclass cls = (*env)->FindClass(env, "org/renpy/android/MyHardware");
    aassert(cls);
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "encode_or_decode_xz", "([BZ)[B");
    aassert(mid);
    
    //alog("newbytearray");
    
    jobject inarr = (*env)->NewByteArray(env, length);
    //alog("setbytearrayregion");
    (*env)->SetByteArrayRegion(env, inarr, 0, length, data);
    
    //alog("callstaticobjectmethod");
    jobject obj = (*env)->CallStaticObjectMethod(env, cls, mid, inarr, mode==0?0:1);
    
    //alog("getarraylength");
    int reslength = (*env)->GetArrayLength(env, obj);;
    
    char* res = malloc(reslength);
    //char* safe_res = malloc(reslength);
    
    //alog("getbytearrayregion");
    (*env)->GetByteArrayRegion(env, obj, 0, reslength, res);
    //memcpy(safe_res, res, reslength)
    
    (*env)->PopLocalFrame(env, NULL);
    
    
    return Py_BuildValue("s#", res, reslength);
}


PyObject* open_intent(PyObject* self, PyObject* args) {
    char* url;
    char* intent_type;
    
    if(!PyArg_ParseTuple(args, "ss", &intent_type, &url))
        return NULL;
    
    JNIEnv* env = SDL_ANDROID_GetJNIEnv();
    aassert(env);
    
    jclass cls = (*env)->FindClass(env, "org/renpy/android/MyHardware");
    aassert(cls);
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "open_intent", "(Ljava/lang/String;Ljava/lang/String;)Ljava/lang/Object;");
    aassert(mid);
    jstring uri_string = (*env)->NewStringUTF(env, url);
    jstring type_string = (*env)->NewStringUTF(env, intent_type);
    (*env)->CallStaticObjectMethod(env, cls, mid, type_string, uri_string);
    
    return Py_BuildValue("i", 0);
}

PyObject* get_android_version(PyObject* self, PyObject* args) {
    JNIEnv* env = SDL_ANDROID_GetJNIEnv();
    aassert(env);
    
    jclass cls = (*env)->FindClass(env, "org/renpy/android/MyHardware");
    aassert(cls);
    jmethodID mid = (*env)->GetStaticMethodID(env, cls, "get_android_version", "()I");
    aassert(mid);
    int ver = (*env)->CallStaticIntMethod(env, cls, mid);
    
    return Py_BuildValue("i", ver);
}

static PyMethodDef PyjniMethods[] = {
    {"make_input_dialog", make_input_dialog, METH_VARARGS, ""},
    {"get_dialog_retval", get_dialog_retval, METH_VARARGS, ""},
    {"encode_or_decode_xz", encode_or_decode_xz, METH_VARARGS, ""},
    {"open_intent", open_intent, METH_VARARGS, ""},
    {"get_android_version", get_android_version, METH_VARARGS, ""},
    {NULL, NULL, 0, NULL}        /* Sentinel */
};

PyMODINIT_FUNC initpyjni(void)
{
    (void) Py_InitModule("pyjni", PyjniMethods);
}