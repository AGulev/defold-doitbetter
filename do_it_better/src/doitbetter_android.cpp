#if defined(DM_PLATFORM_ANDROID)

#include <dmsdk/dlib/android.h>
#include "doitbetter_private.h"
#include "doitbetter_callback.h"
#include "com_doitbetter_DoItBetterDefoldJNI.h"

JNIEXPORT void JNICALL Java_com_doitbetter_DoItBetterDefoldJNI_doItBetterAddToQueue(JNIEnv * env, jclass cls, jint jmsg, jstring jjson)
{
    const char* json = env->GetStringUTFChars(jjson, 0);
    dmDoItBetter::AddToQueueCallback((dmDoItBetter::MessageId)jmsg, json);
    env->ReleaseStringUTFChars(jjson, json);
}

namespace dmDoItBetter {

struct DoItBetter
{
    jobject        m_objectJNI;
    
    jmethodID      m_Initialize;
    jmethodID      m_SetLoggingEnabled;
    jmethodID      m_MarkAsDevelopment;
    jmethodID      m_SendEvent;
};

static DoItBetter g_doItBetter;

static void CallVoidMethod(jobject instance, jmethodID method)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method);
}

static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr = env->NewStringUTF(cstr);
    env->CallVoidMethod(instance, method, jstr);
    env->DeleteLocalRef(jstr);
}

static void CallVoidMethodChar(jobject instance, jmethodID method, const char* cstr1, const char* cstr2, const char* cstr3)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    jstring jstr1 = env->NewStringUTF(cstr1);
    jstring jstr2 = env->NewStringUTF(cstr2);
    jstring jstr3 = env->NewStringUTF(cstr3);
    env->CallVoidMethod(instance, method, jstr1, jstr2, jstr3);
    env->DeleteLocalRef(jstr1);
    env->DeleteLocalRef(jstr2);
    env->DeleteLocalRef(jstr3);
}

static void CallVoidMethodBool(jobject instance, jmethodID method, bool cbool)
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();

    env->CallVoidMethod(instance, method, cbool);
}

void Initialize_Ext()
{
    dmAndroid::ThreadAttacher threadAttacher;
    JNIEnv* env = threadAttacher.GetEnv();
    jclass cls = dmAndroid::LoadClass(env, "com.doitbetter.DoItBetterDefoldJNI");

    jmethodID jni_constructor = env->GetMethodID(cls, "<init>", "(Landroid/app/Activity;)V");

    g_doItBetter.m_objectJNI = env->NewGlobalRef(env->NewObject(cls, jni_constructor, threadAttacher.GetActivity()->clazz));

    g_doItBetter.m_Initialize = env->GetMethodID(cls, "initialize", "(Ljava/lang/String;)V");
    g_doItBetter.m_SetLoggingEnabled = env->GetMethodID(cls, "enableLogging", "(Z)V");
    g_doItBetter.m_MarkAsDevelopment = env->GetMethodID(cls, "markAsDevelopment", "()V");
    g_doItBetter.m_SendEvent = env->GetMethodID(cls, "sendEvent", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)V");
}

void Initialize(const char* key) {
    CallVoidMethodChar(g_doItBetter.m_objectJNI, g_doItBetter.m_Initialize, key);
}

void SetLoggingEnabled(bool enabled){
    CallVoidMethodBool(g_doItBetter.m_objectJNI, g_doItBetter.m_SetLoggingEnabled, enabled);
}

void MarkAsDevelopment() {
    CallVoidMethod(g_doItBetter.m_objectJNI, g_doItBetter.m_MarkAsDevelopment);
}

void SendEvent(const char* eventName, const char* jsonString, const char* deduplicateID) {
    CallVoidMethodChar(g_doItBetter.m_objectJNI, g_doItBetter.m_SendEvent, eventName, jsonString, deduplicateID);
}

}//namespace dmDoItBetter

#endif // DM_PLATFORM_ANDROID
