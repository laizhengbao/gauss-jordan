CC=gcc
CFLAGS=-Wall -march=native -std=gnu99 -Ofast -minline-all-stringops -fopenmp -lm
CFLAGS_DBG=$(CFLAGS) -g -D DBG
C_FILES=$(shell find src -name "*.c" )
OBJ=$(patsubst %.c, %.o, $(C_FILES) )
OBJ_DBG=$(patsubst %.c, %.o.dbg, $(C_FILES) )
OBJ_FILE=$(shell find . -name "*.o*" )
MAIN = main.c
LIB = libhomogj.so
prefix=/opt/homogj
OUTPUT=homogj

.PHONY: all lib debug clean install uninstall
all: $(OUTPUT)

lib: $(LIB)

install: all
	@echo Installing to $(prefix)
	@mkdir -p $(prefix)/bin
	@cp $(OUTPUT) $(prefix)/bin
	@cp README.md $(prefix)
	@echo done
uninstall:
	@echo Uninstalling form $(prefix)
	@-rm -r $(prefix)
	@echo done
debug: $(OUTPUT).dbg
clean:
	@echo Cleaning...
	@-rm -f $(OBJ_FILE)
	@-rm *$(OUTPUT)*
	@echo Done
%.o: %.c
	@echo Compiling and generating object $@
	@$(CC) $(CFLAGS) -fPIC -c -o $@ $<
%.o.dbg: %.c
	@echo Compiling and generating debugging object $@
	@$(CC) $(CFLAGS_DBG) -c -o $@ $<

$(OUTPUT): $(MAIN) $(OBJ)
	@echo Linking executable $@
	@$(CC) $(CFLAGS) -o $@ $^
$(OUTPUT).dbg: $(MAIN) $(OBJ_DBG)
	@echo Linking executable $@
	@$(CC) $(CFLAGS_DBG) -o $@ $^

$(LIB): $(OBJ)
	@echo Generating dynamic library $@
	@$(CC) -shared -o $@ $<
