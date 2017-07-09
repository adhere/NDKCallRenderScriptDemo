#include <jni.h>
#include <string>
#include <jni.h>
#include <android/log.h>
#include <android/bitmap.h>

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "tfClass.h"

extern "C"
JNIEXPORT jstring JNICALL
Java_ndk_renderscript_learn_ndkcallrenderscriptdemo_MainActivity_stringFromJNI(
    JNIEnv *env,
    jobject /* this */) {
  std::string hello = "Hello from C++";
  return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_ndk_renderscript_learn_ndkcallrenderscriptdemo_MainActivity_nativeRsMono(JNIEnv *env, jclass,
                                                                              jstring pathObj,
                                                                              jint X, jint Y,
                                                                              jobject jbitmapIn,
                                                                              jobject jbitmapOut) {
// convert the jni to c++ type
  void *inputPtr = nullptr;
  void *outputPtr = nullptr;
  AndroidBitmap_lockPixels(env, jbitmapIn, &inputPtr);
  AndroidBitmap_lockPixels(env, jbitmapOut, &outputPtr);
  const char *path = env->GetStringUTFChars(pathObj, nullptr);

// rs compute
  compute(path, X, Y, inputPtr, outputPtr);

//release the resource
  AndroidBitmap_unlockPixels(env, jbitmapIn);
  AndroidBitmap_unlockPixels(env, jbitmapOut);
  env->ReleaseStringUTFChars(pathObj, path);
}

