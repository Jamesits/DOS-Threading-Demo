SRCS=$(wildcard $(SRCDIR)/*.c)
OBJS=$(SRCS:.c=.OBJ)
ASMS=$(wildcard $(SRCDIR)/*.asm)
ASMOBJS=$(SRCS:.asm=.OBJ)
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
HEADERS=\\TC\\INCLUDE
LIBS=\\TC\\LIB\\
MDL = l
CC = tcc -m$(MDL) -w- -DTURBOC
CFLAGS = -I$(HEADERS) -I$(SRCDIR) -L$(LIBS)
ASM = tasm /MX /I$(HEADERS)
LINK = tlink
LIB = tlib
LIBFLAGS = /c

.c.OBJ: prep
	$(BATCH_MAKER) $(CC) -c $(CFLAGS) $*

.asm.OBJ: prep
	$(BATCH_MAKER) $(ASM) $*;

$(EXE): $(SRCS) $(ASMS)
	$(BATCH_MAKER) $(LINK) /v /l /m $(OBJS) $(ASMOBJS) $(EXE)

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

prep: copy-sources
	@echo "Resetting DOS build script..."
	rm -f $(DOS_BUILD_SCRIPT)
	@$(BATCH_MAKER) C:
	@$(BATCH_MAKER) cd src
	@$(BATCH_MAKER) set PATH=%PATH%\;C:\\TC\;C:\\TC\\BIN\;Z:\\\;
	@$(BATCH_MAKER) set CLASSPATH=%CLASSPATH%\;C:\\TC\\LIB\;
	@$(BATCH_MAKER) set LIB=%LIB%\;C:\\TC\\LIB\;
	@$(BATCH_MAKER) set INCLUDE=%INCLUDE%\;C:\\TC\\INCLUDE\;
	// $(BATCH_MAKER) $(CC) /v $(INCLUDES) $(LIBS) /e$@ $(notdir $(SRCS))

run:
	$(BATCH_MAKER) $(EXE)

copy-sources:
	@echo "Preparing program sources..."
	rm -rf $(BUILD_DOSROOT)
	cp -rf $(DOSROOT) $(BUILD_DOSROOT)

clean:
	@echo "Deleting temporary files..."
	rm -rf $(BUILD_TEMP)
