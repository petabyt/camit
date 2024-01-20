CFLAGS=-Icamlib/src/
LDFLAGS=-Lcamlib/ -Wl,-rpath,camlib/ -lraylib -ljpeg -lcamlib -lm

ifdef VCAM
LDFLAGS+=-L../vcam/ -Wl,-rpath,../vcam/ -lusb
else
LDFLAGS+=-lusb-1.0
endif

CAMLIB_CORE=$(addprefix camlib/src/,operations.o packet.o enums.o data.o enum_dump.o lib.o canon.o liveview.o bind.o ip.o ml.o log.o conv.o generic.o)
CAMLIB_CORE+=$(addprefix camlib/lua/,lua.o lua-cjson/lua_cjson.o lua-cjson/strbuf.o)

CFLAGS+=$(shell pkg-config --cflags lua-5.3)
LDFLAGS+=$(shell pkg-config --libs lua-5.3)

CAMIT_CORE=src/main.o src/lv.o src/win.o
FILES=$(CAMIT_CORE) $(LUA_FILES) $(CAMLIB_CORE)
FILES_LIBUI=src/libui.o src/int.o $(LUA_FILES) $(CAMLIB_CORE)

camit.out: $(FILES) so
	$(CC) $(FILES) $(LDFLAGS) -o camit.out

camit-libui.out: $(FILES_LIBUI)
	$(CC) $(FILES_LIBUI) $(LDFLAGS) -lui -o camit-libui.out

so:
	cd camlib && make libcamlib.so
	cd ../vcam && make

clean:
	$(RM) src/*.o *.out camlib/src/*.o camlib/lua/*.o camlib/lua/lua-cjson/*.o
	$(RM) lua/*.o DUMP

.PHONY: so clean
