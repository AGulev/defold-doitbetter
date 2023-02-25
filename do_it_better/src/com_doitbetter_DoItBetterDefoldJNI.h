#if defined(DM_PLATFORM_ANDROID)

#include <jni.h>
/* Header for class com_doitbetter_DoItBetterDefoldJNI */

#ifndef COM_DOITBETTER_DOITBETTERJNI_H
#define COM_DOITBETTER_DOITBETTERJNI_H
#ifdef __cplusplus
extern "C" {
#endif
	/*
	* Class:     com_doitbetter_DoItBetterDefoldJNI
	* Method:    doItBetterAddToQueue_first_arg
	* Signature: (ILjava/lang/String;I)V
	*/
	JNIEXPORT void JNICALL Java_com_doitbetter_DoItBetterDefoldJNI_doItBetterAddToQueue
	(JNIEnv *, jclass, jint, jstring);

#ifdef __cplusplus
}
#endif
#endif

#endif
