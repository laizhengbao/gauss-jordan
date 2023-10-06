CC=gcc
CFLAGS=-Wall -march=native -std=gnu99 -Ofast
CFLAGS_DBG=$(CFLAGS) -g -D DBG
C_FILES=$(shell find src -name "*.c" )
OBJ=$(patsubst %.c, %.o, $(C_FILES) )
OBJ_DBG=$(patsubst %.c, %.o.dbg, $(C_FILES) )
OBJ_FILE=$(shell find . -name "*.o*" )
MAIN = main.c
prefix=/opt/homogj
OUTPUT=homogj

.PHONY: all debug clean install uninstall
all: $(OUTPUT)
install: all
	@echo Installing to $(prefix)
	@mkdir -p $(prefix)/bin
	@cp $(OUTPUT) $(prefix)/bin
	@cp README.md $(prefix)
	@chmod 755 src/*.sh
	@chmod 755 src/*.csh
	@cp src/homobf.sh /etc/profile.d
	@cp src/homobf.csh /etc/profile.d
	@echo done
uninstall:
	@echo Uninstalling form $(prefix)
	@-rm -r $(prefix)
	@-rm /etc/profile.d/homobf.csh
	@-rm /etc/profile.d/homobf.sh
	@echo done
debug: $(OUTPUT).dbg
clean:
	@echo Cleaning...
	@-rm -f $(OBJ_FILE)
	@-rm $(OUTPUT)*
	@echo Done
%.o: %.c
	@echo Compiling and generating object $@
	@$(CC) $(CFLAGS) -c -o $@ $<
%.o.dbg: %.c
	@echo Compiling and generating debugging object $@
	@$(CC) $(CFLAGS_DBG) -c -o $@ $<
$(OUTPUT): $(MAIN) $(OBJ)
	@echo Linking executable $@
	@$(CC) $(CFLAGS) -o $@ $^
$(OUTPUT).dbg: $(MAIN) $(OBJ_DBG)
	@echo Linking executable $@
	@$(CC) $(CFLAGS_DBG) -o $@ $^
