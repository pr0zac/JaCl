#include <jni.h>
#include <stdio.h>
#include "JaCl.h"

#include "crypto_box.h"
#include "crypto_secretbox.h"

#include "NaClInterface.h"

JNIEXPORT jlong JNICALL
Java_JaCl_initCppSide(JNIEnv *env, jobject obj) {
    NaClInterface* nacl_interface = new NaClInterface();
    return reinterpret_cast<jlong>(nacl_interface);
}

JNIEXPORT jstring JNICALL
Java_JaCl_nonce(JNIEnv *env, jobject obj, jlong ptr) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string n = nacl_interface->nonce();
    return env->NewString((const jchar*)n.c_str(), (jsize)n.length());
}

JNIEXPORT void JNICALL
Java_JaCl_setRemoteNonce(JNIEnv *env, jobject obj, jlong ptr, jstring j_rn) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string rn((const char*)env->GetStringChars(j_rn, 0), (size_t)env->GetStringLength(j_rn));
    nacl_interface->set_remote_nonce(rn);
}

JNIEXPORT void JNICALL
Java_JaCl_genNewNonce(JNIEnv *env, jobject obj, jlong ptr) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    nacl_interface->gen_new_nonce();
}

JNIEXPORT jstring JNICALL
Java_JaCl_publicKey(JNIEnv *env, jobject obj, jlong ptr) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string pk = nacl_interface->public_key();
    return env->NewString((const jchar*)pk.c_str(), (jsize)pk.length());
}

JNIEXPORT jstring JNICALL
Java_JaCl_secretKey(JNIEnv *env, jobject obj, jlong ptr) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string sk = nacl_interface->secret_key();
    return env->NewString((const jchar*)sk.c_str(), (jsize)sk.length());
}

JNIEXPORT void JNICALL
Java_JaCl_setRemoteKey(JNIEnv *env, jobject obj, jlong ptr, jstring j_rk) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string rk((const char*)env->GetStringChars(j_rk, 0), (size_t)env->GetStringLength(j_rk));
    nacl_interface->set_remote_key(rk);
}

JNIEXPORT void JNICALL
Java_JaCl_genNewKeys(JNIEnv *env, jobject obj, jlong ptr) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    nacl_interface->gen_new_keys();
}

JNIEXPORT jstring JNICALL
Java_JaCl_secret(JNIEnv *env, jobject obj, jlong ptr) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string s = nacl_interface->secret();
    return env->NewString((const jchar*)s.c_str(), (jsize)s.length());
}

JNIEXPORT void JNICALL
Java_JaCl_setSecret(JNIEnv *env, jobject obj, jlong ptr, jstring j_ns) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string ns((const char*)env->GetStringChars(j_ns, 0), (size_t)env->GetStringLength(j_ns));
    nacl_interface->set_secret(ns);
}

JNIEXPORT void JNICALL
Java_JaCl_genNewSecret(JNIEnv *env, jobject obj, jlong ptr) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    nacl_interface->gen_new_secret();
}

JNIEXPORT jstring JNICALL
Java_JaCl_publicDecrypt(JNIEnv *env, jobject obj, jlong ptr, jstring j_enc_msg) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string enc_msg((const char*)env->GetStringChars(j_enc_msg, 0), (size_t)env->GetStringLength(j_enc_msg) * 2);
    std::string msg = nacl_interface->public_decrypt(enc_msg);
    return env->NewString((const jchar*)msg.c_str(), (jsize)msg.length()/2);
}

JNIEXPORT jstring JNICALL
Java_JaCl_publicEncrypt(JNIEnv *env, jobject obj, jlong ptr, jstring j_msg) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string msg((const char*)env->GetStringChars(j_msg, 0), (size_t)env->GetStringLength(j_msg) * 2);
    std::string enc_msg = nacl_interface->public_encrypt(msg);
    return env->NewString((const jchar*)enc_msg.c_str(), (jsize)enc_msg.length()/2);
}

JNIEXPORT jstring JNICALL
Java_JaCl_secretDecrypt(JNIEnv *env, jobject obj, jlong ptr, jstring j_enc_msg) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string enc_msg((const char*)env->GetStringChars(j_enc_msg, 0), (size_t)env->GetStringLength(j_enc_msg));
    std::string msg = nacl_interface->secret_decrypt(enc_msg);
    return env->NewString((const jchar*)msg.c_str(), (jsize)msg.length());
}

JNIEXPORT jstring JNICALL
Java_JaCl_secretEncrypt(JNIEnv *env, jobject obj, jlong ptr, jstring j_msg) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::string msg((const char*)env->GetStringChars(j_msg, 0), (size_t)env->GetStringLength(j_msg));
    std::string enc_msg = nacl_interface->secret_encrypt(msg);
    return env->NewString((const jchar*)enc_msg.c_str(), (jsize)enc_msg.length());
}


JNIEXPORT void JNICALL 
Java_JaCl_printTest(JNIEnv *env, jobject obj, jlong ptr, jstring j_pk) {
    NaClInterface* nacl_interface = reinterpret_cast<NaClInterface*>(ptr);
    std::cout << "C++ side public_key: " << nacl_interface->public_key() << " length: " << nacl_interface->public_key().length() << "\n";

    std::string pk((const char*)env->GetStringChars(j_pk, 0), (size_t)env->GetStringLength(j_pk));
    std::cout << "C++ side passed public_key: " << pk << " length: " << pk.length() << "\n";
}

