#include <jni.h>
#include <stdio.h>
#include "JaCl.h"

JNIEXPORT void JNICALL 
Java_JaCl_print(JNIEnv *env, jobject obj)
{
   printf("Hello World!\n");
   return;
}
