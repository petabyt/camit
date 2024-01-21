#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "myjni.h"

#include <ui.h>
#include <uifw.h>

static void clickevent(uiButton *button, void *arg) {
	static int x = 0;
	char buffer[64];
	sprintf(buffer, "Clicked %X", x);
	uiButtonSetText(button, buffer);
	x++;
}

static void new_window(uiButton *button, void *arg) {
	uiBox *box = uiNewVerticalBox();
	uiBoxSetPadded(box, 1);
	uiButton *btn = uiNewButton("testing 123");
	uiBoxAppend(box, uiControl(btn), 0);

	uiWindow *win = uiNewWindow("Hello, World", 100, 100, 0);
	uiWindowSetChild(win, uiControl(box));
}

static uiControl *page_capture() {
	uiButton *btn;
	uiLabel *lbl;

	uiBox *box = uiNewVerticalBox();
	uiBoxSetPadded(box, 1);

	uiGroup *group = uiNewGroup("Parameters");
	uiForm *form = uiNewForm();
	uiFormSetPadded(form, 1);

	uiEntry *entry = uiNewEntry();
	uiEntrySetText(entry, "10");
	uiFormAppend(form, "How many shots to take", uiControl(entry), 0);

	entry = uiNewEntry();
	uiEntrySetText(entry, "10");
	uiFormAppend(form, "Seconds inbetween each shot", uiControl(entry), 0);
	uiGroupSetChild(group, uiControl(form));
	uiBoxAppend(box, uiControl(group), 0);

	uiBoxAppend(box, uiControl(uiNewVerticalSeparator()), 0);

	btn = uiNewButton("Start sequence");
	uiButtonOnClicked(btn, new_window, 0);
	uiBoxAppend(box, uiControl(btn), 0);

	btn = uiNewButton("Take single picture");
	uiBoxAppend(box, uiControl(btn), 0);

	uiBoxAppend(box, uiControl(uiNewVerticalSeparator()), 0);
	uiBoxAppend(box, uiControl(uiNewVerticalSeparator()), 0);

	return uiControl(box);
}

uiControl *camit_int_layout() {
	uiBox *frame = uiNewVerticalBox();
	uiBoxSetPadded(frame, 1);

	uiTab *tab = uiNewTab();
	uiTabAppend(tab, "Capture", page_capture());
	uiTabAppend(tab, "Bulb", page_capture());
	uiTabAppend(tab, "Scripts", page_capture());

	uiBoxAppend(frame, uiControl(tab), 0);

	//uiProgressBar *pg = uiNewProgressBar();
	//uiProgressBarSetValue(pg, 60);
	uiLabel *status = uiNewLabel("Currently doing something...");
	uiBoxAppend(frame, uiControl(status), 0);

	// uiButton *btn = uiNewButton("out of bounds");
	// uiButtonOnClicked(btn, new_window, 0);
	// uiBoxAppend(frame, uiControl(btn), 0);

	return (uiControl *)frame;
}

uiBox *get_connect_page() {
	uiBox *frame = uiNewVerticalBox();

    uiBox *box = uiNewVerticalBox();
    uiBoxSetPadded(box, 1);
	uiControlCenter(uiControl(box));

    uiButton *try_connect = uiNewButton("Connect");
	uiControlSetAttr(uiControl(try_connect), "drawable", "go_button");
    uiBoxAppend(box, uiControl(try_connect), 0);

	uiButton *about = uiNewButton("About");
	uiBoxAppend(box, uiControl(about), 0);

	uiLabel *error = uiNewLabel("");
	uiLabelAlignment(error, uiDrawTextAlignCenter);
	uiBoxAppend(box, uiControl(error), 0);

	uiBoxAppend(frame, uiControl(box), 0);
	uiLabel *status = uiNewLabel("Ready");
	uiBoxAppend(frame, uiControl(status), 0);

    return frame;
}

JNI_FUNC(void, StartUI)(JNIEnv *env, jobject thiz, jobject ctx) {
	uiAndroidInit(env, ctx);
    uiAndroidSetContent(get_connect_page());
	//uiAndroidSetContent(camit_int_layout());
}
