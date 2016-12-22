SRCS=main.c
OBJS=$(SRCS:.c=.OBJ)
EXE=THREAD

export BUILD_TEMP=build
export DOSROOT=dosroot
export BUILD_DOSROOT=$(BUILD_TEMP)/dosroot
export DOS_BUILD_SCRIPT=$(BUILD_DOSROOT)/BUILD.BAT
export BATCH_MAKER=buildsystem/dos.sh
export BUILD_SYSTEM_ROOT=buildsystem
export BUILD_SYSTEM_DOSBOX_ROOT=$(BUILD_SYSTEM_ROOT)/dosbox
export BUILD_SYSTEM_QEMU_ROOT=$(BUILD_SYSTEM_ROOT)/qemu
export BUILD_SYSTEM_QEMU_IMAGE_TEMPLATE=$(BUILD_SYSTEM_QEMU_ROOT)/template.img

SRCDIR=$(DOSROOT)/src
CC=TCC /ml
INCLUDES=/I\\TC\\INCLUDE
LINKER=TLINK
LIBS=/L\\TC\\LIB\\

: build
.PHONY: clean build

build: build-dosbox

build-dosbox: $(EXE)
	@echo "Starting DOSBox..."
	$(BUILD_SYSTEM_DOSBOX_ROOT)/dosbox.sh $(DOS_BUILD_SCRIPT)

build-qemu: $(EXE)
	@echo "Starting QEMU..."
	$(BUILD_SYSTEM_QEMU_ROOT)/qemu.sh $(DOS_BUILD_SCRIPT)

run-dosbox: | $(EXE) run build-dosbox

run-qemu: | $(EXE) run build-qemu

$(EXE): copy-sources
	@echo "Resetting DOS build script..."
	rm -f $(DOS_BUILD_SCRIPT)
	@$(BATCH_MAKER) C:
	@$(BATCH_MAKER) cd src
	@$(BATCH_MAKER) set PATH=%PATH%\;C:\\TC\;C:\\TC\\BIN\;Z:\\\;
	@$(BATCH_MAKER) set CLASSPATH=%CLASSPATH%\;C:\\TC\\LIB\;
	@$(BATCH_MAKER) set LIB=%LIB%\;C:\\TC\\LIB\;
	@$(BATCH_MAKER) set INCLUDE=%INCLUDE%\;C:\\TC\\INCLUDE\;
	$(BATCH_MAKER) $(CC) /v $(INCLUDES) $(LIBS) /e$@ $(notdir $(SRCS))

run:
	$(BATCH_MAKER) $(EXE)

copy-sources: $(BATCH_MAKER)
	@echo "Preparing program sources..."
	rm -rf $(BUILD_DOSROOT)
	cp -rf $(DOSROOT) $(BUILD_TEMP)

clean:
	@echo "Deleting temporary files..."
	rm -rf $(BUILD_TEMP)
