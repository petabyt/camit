CFLAGS=-Icamlib/src/ -fPIC
LDFLAGS=-Lcamlib/ -Wl,-rpath,camlib/ -lraylib -ljpeg -lcamlib -lusb-1.0 -lm

CL_FILES=$(addprefix camlib/src/,operations.o packet.o enums.o data.o enum_dump.o util.o canon.o liveview.o bind.o ip.o fuji.o ml.o log.o conv.o generic.o)
CL_FILES+=$(addprefix camlib/lua/,lua.o lua-cjson/lua_cjson.o lua-cjson/strbuf.o)

CAMLV_FILES=src/main.o src/lv.o

LUA_FILES=lua/lbaselib.o lua/lauxlib.o lua/lapi.o lua/lcode.o lua/lctype.o lua/ldebug.o lua/ldo.o lua/ldump.o lua/lfunc.o lua/lgc.o lua/llex.o lua/lmem.o lua/lobject.o lua/lopcodes.o lua/lparser.o lua/lstate.o lua/lstring.o lua/ltable.o lua/ltm.o lua/lundump.o lua/lvm.o lua/lzio.o lua/ltests.o lua/lstrlib.o
CFLAGS+=-Ilua/

ALL_FILES=$(CAMLV_FILES) $(LUA_FILES) $(CL_FILES)

camlv.out: $(ALL_FILES) so
	$(CC) $(ALL_FILES) $(LDFLAGS) -o camlv.out

so:
	cd camlib && make libcamlib.so

clean:
	$(RM) src/*.o *.out camlib/src/*.o camlib/lua/*.o camlib/lua/lua-cjson/*.o
	$(RM) lua/*.o
