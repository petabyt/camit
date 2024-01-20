#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include <camlib.h>

#include <ui.h>

uiControl *camit_int_layout();

struct PtpRuntime *luaptp_get_runtime(lua_State *L) {
	
}

int onClosing(uiWindow *w, void *data)
{
	uiQuit();
	return 1;
}

static void clickevent(uiButton *button, void *arg) {
	puts("Hello");
}

int main(void)
{
	uiInitOptions o = {0};
	const char *err;
	uiWindow *w;
	uiLabel *l;

	err = uiInit(&o);
	if (err != NULL) {
		fprintf(stderr, "Error initializing libui: %s\n", err);
		uiFreeInitError(err);
		return 1;
	}

	// Create a new window
	w = uiNewWindow("Camit", 500, 700, 0);
	uiWindowOnClosing(w, onClosing, NULL);

	uiBox *frame = uiNewVerticalBox();
	uiBoxSetPadded(frame, 1);

	uiBoxAppend(frame, camit_int_layout(), 0);

	uiWindowSetChild(w, uiControl(frame));
	uiControlShow(uiControl(w));
	uiMain();
	uiUninit();
	return 0;
}

