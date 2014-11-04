/**
* Instituto Militar de Engenharia
* Information Security Course
* InterfaceJNI.cpp
* Created in 06 August 2014 by Hallison da Paz, Kizzy dos Reis and Rafael Batista
* This file act as an interface between a JAVA GUI and a C++ program based on the Alpha Algorithm. 
*/

#include <jni.h>
#include <iostream>
#include "Cifrador.h"
#include "Decifrador.h"
#include "main_Alpha.h"

using namespace std;


// Global variables
Cifrador cifrador;
Decifrador decifrador;


/**
 * Called by Java GUI to cipher a file in the path inFileName to a file in the path outFileName using senha as the key (128 bits)
 */
extern "C" JNIEXPORT void JNICALL
Java_main_Alpha_cifrar(JNIEnv *env, jobject obj, jstring senha, jstring confirmation, jstring inFileName, jstring outFileName){
	const char* c_senha = env->GetStringUTFChars(senha, 0);
	const char* c_confirmation = env->GetStringUTFChars(confirmation, 0);
	const char* c_inFileName = env->GetStringUTFChars(inFileName, 0);
	const char* c_outFileName = env->GetStringUTFChars(outFileName, 0);


	cifrador.cifrar(c_senha, c_confirmation, c_inFileName, c_outFileName);


	env->ReleaseStringUTFChars(senha,c_senha);
	env->ReleaseStringUTFChars(confirmation,c_confirmation);
	env->ReleaseStringUTFChars(inFileName,c_inFileName);
	env->ReleaseStringUTFChars(outFileName,c_outFileName);
}


/**
 * Called by Java GUI to decipher a file in the path inFileName to a file in the path outFileName using senha as the key (128 bits)
 */
extern "C" JNIEXPORT void JNICALL
Java_main_Alpha_decifrar(JNIEnv *env, jobject obj, jstring senha, jstring confirmation, jstring inFileName, jstring outFileName){
	const char* c_senha = env->GetStringUTFChars(senha, 0);
	const char* c_confirmation = env->GetStringUTFChars(confirmation, 0);
	const char* c_inFileName = env->GetStringUTFChars(inFileName, 0);
	const char* c_outFileName = env->GetStringUTFChars(outFileName, 0);


	decifrador.decifrar(c_senha, c_confirmation, c_inFileName, c_outFileName);


	env->ReleaseStringUTFChars(senha,c_senha);
	env->ReleaseStringUTFChars(confirmation,c_confirmation);
	env->ReleaseStringUTFChars(inFileName,c_inFileName);
	env->ReleaseStringUTFChars(outFileName,c_outFileName);
}

/**
 * Called by Java GUI to decipher a file in the path inFileName to a file in the path outFileName using senha as the key (128 bits)
 */
extern "C" JNIEXPORT void JNICALL
Java_main_Alpha_setIterationNumber(JNIEnv *env, jobject obj, jint numOfIterations){
	cifrador.setIterations(numOfIterations);
	decifrador.setIterations(numOfIterations);
}


/********** end file ***********/
