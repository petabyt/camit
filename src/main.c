#include <stdio.h>
#include <stdlib.h>
#include <camlib.h>

#include <lua.h>
#include <lualib.h>
#include <lauxlib.h>

#include "cam.h"

struct CamState cam = {0};

LUALIB_API int luaopen_ptp(lua_State *L);
int luaopen_cjson(lua_State *l);

struct PtpRuntime *global_r = NULL;
struct PtpRuntime *luaptp_get_runtime(lua_State *L) {
	return global_r;
}

static int lua_script_print(lua_State *L) {
	const char *str = luaL_checkstring(L, 1);
	printf("%s\n", str);
	return 1;
}

static int lua_script_msleep(lua_State *L) {
	int ms = lua_tointeger(L, 1);
	usleep(ms * 1000);
	return 1;
}

static int lua_script_set_status(lua_State *L) {
	const char *str = luaL_checkstring(L, 1);
	printf("Status: %s\n", (char *)str);
	return 1;
}

lua_State *cam_lua_state() {
	lua_State *L = luaL_newstate();
	luaopen_base(L);
	luaopen_cjson(L);
	lua_register(L, "setStatusText", lua_script_set_status);
	lua_register(L, "print", lua_script_print);
	lua_register(L, "msleep", lua_script_msleep);

	luaL_requiref(L, "ptp", luaopen_ptp, 1);
	luaL_requiref(L, "json", luaopen_cjson, 1);
	luaL_requiref(L, "string", luaopen_string, 1);
	return L;
}

static int init_ptp_liveview() {
	// rc = ptp_liveview_init(r);
	// if (rc) {
		// return rc;
	// }
}

static int take_picture(struct PtpRuntime *r) {

	int rc = ptp_init_open_capture(r, 0, 0);
	return rc;

	return 0;
}

static int init_ptp(struct PtpRuntime *r) {
	if (ptp_device_init(r)) {
		puts("Device connection error");
		return -1;
	}

	int rc = ptp_open_session(r);
	if (rc) return rc;

	r->di = malloc(sizeof(struct PtpDeviceInfo));
	rc = ptp_get_device_info(r, r->di);
	if (rc) return rc;
	ptp_dump(r);

	cam.device_type = ptp_device_type(r);

	if (cam.device_type == PTP_DEV_EOS) {
		ptp_eos_set_remote_mode(r, 1);
		ptp_eos_set_event_mode(r, 1);
	}

	return 0;
}

static int deinit_ptp(struct PtpRuntime *r) {
	int rc = ptp_close_session(r);
	if (rc) return rc;

	return 0;
}

static int run_lua_script(struct PtpRuntime *r) {
	lua_State *L = cam_lua_state();

	int rc = luaL_loadfile(L, "test.lua");
	if (rc == LUA_ERRFILE) {
		puts("File not found");
		return 1;
	}

	if (lua_pcall(L, 0, 0, 0) != LUA_OK) {
		printf("Failed to run Lua: %s\n", lua_tostring(L, -1));
		lua_close(L);
		return -1;
	}

	lua_close(L);

	return 0;
}

int main() {
	struct PtpRuntime r;
	ptp_generic_init(&r);

	global_r = &r;

	int rc = init_ptp(&r);
	if (rc) {
		printf("Error connecting: %d\n", rc);
		return 1;
	}

	//camit_open_window(&r);

	run_lua_script(&r);

	deinit_ptp(&r);

	return 0;
}
