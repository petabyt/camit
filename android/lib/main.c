#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myjni.h"

#include <ui.h>
#include "ui_android.h"

uiControl *camit_int_layout();

JNI_FUNC(void, StartUI)(JNIEnv *env, jobject thiz, jobject ctx) {
	uiAndroidInit(env, ctx);
	uiAndroidSetContent(camit_int_layout());
}
