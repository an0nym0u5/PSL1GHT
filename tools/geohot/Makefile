CC			:=	$(PREFIX)gcc
CXX			:=	$(PREFIX)g++
AR			:=	$(PREFIX)ar
OBJCOPY		:=	$(PREFIX)objcopy

UNAME		:=	$(shell uname -s)

CFLAGS		:=	$(DEBUGFLAGS) -O2
CFLAGS		+=	$(INCLUDES)
CXXFLAGS	:=	$(CFLAGS) -fno-rtti -fno-exceptions
LDFLAGS		=	$(DEBUGFLAGS)

ifeq ($(strip $(PS3DEV)),)
  ifeq ($(strip $(DEVKITPS3)),)
    export PS3DEV := /usr/local/ps3dev
  else
    export PS3DEV := $(DEVKITPS3)
  endif
endif

ifneq (,$(findstring MINGW,$(UNAME)))
	PLATFORM	:= win32
	POSTFIX		:= .exe
	CFLAGS		+= -mno-cygwin
	LDFLAGS		+= -mno-cygwin -s
endif

ifneq (,$(findstring CYGWIN,$(UNAME)))
	LDFLAGS		+= -s
	POSTFIX		:= .exe
endif

ifneq (,$(findstring Darwin,$(UNAME)))
	CFLAGS		+=	-I/opt/local/include -I/usr/local/include
	LDFLAGS		+=	-L/opt/local/lib -L/usr/local/lib
endif

ifneq (,$(findstring BSD,$(UNAME)))
	CFLAGS		+=	-I/usr/local/include
	LDFLAGS		+=	-L/usr/local/lib
endif

LDFLAGS	+=	-lgmp -lcrypto -lz

TARGETS	:=	make_self$(POSTFIX) make_self_npdrm$(POSTFIX) package_finalize$(POSTFIX)

all: $(TARGETS)

make_self$(POSTFIX): make_self.c
	@echo building ... $(notdir $@)
	@$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

make_self_npdrm$(POSTFIX): make_self.c
	@echo building ... $(notdir $@)
	@$(CC) $< $(CFLAGS) $(LDFLAGS) -DNPDRM -o $@

package_finalize$(POSTFIX): package_finalize.c
	@echo building ... $(notdir $@)
	@$(CC) $< $(CFLAGS) $(LDFLAGS) -o $@

install: $(TARGETS)
	@echo Installing $(TARGETS)
	@[ -d $(PS3DEV)/bin ] || mkdir -p $(PS3DEV)/bin
	@install -m 755 $(TARGETS) $(PS3DEV)/bin

clean:
	@echo clean ...
	@rm -f $(TARGETS)

.PHONY: install clean
