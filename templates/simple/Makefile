##--------------------------------------------------------------------------------
##
## Configuration
##
##--------------------------------------------------------------------------------
ifeq ($(strip $(PSL1GHT)),)
$(error "Please set PSL1GHT in your environment. export PSL1GHT=<path>")
endif

include $(PSL1GHT)/ppu_rules


#---------------------------------------------------------------------------------
# TITLE project title
# APPEGO 6 character app identifier
# APPVERSION 3 character version
# APPID 6 character application id (9 characters TOTAL)
# APPRAND 16 character random string
# CONTENTID 
# ICON0 320x176 pixel PNG image for XMB icon
# PIC1 1920x1080 pxel PNG image for XMB background
# SND0 ATRAC3 encoded audio file for XMB audio
# SFOXML xml file used to create PARAM.SFO
#---------------------------------------------------------------------------------
TITLE		:= Template - PSL1GHT
APPEGO		:= TMP003
APPVERSION	:= 003
APPID		:= TEMPLT$(APPVERSION)
APPRAND		:= $(shell openssl rand -hex 8 | tr [:lower:] [:upper:])
CONTENTID	:= $(APPEGO)-$(APPID)_00-$(APPRAND)
ICON0		:= $(CURDIR)/pkg/ICON0.PNG
SFOXML		:= $(CURDIR)/pkg/sfo.xml
PKGFILES	:= $(CURDIR)/pkg/extras


#---------------------------------------------------------------------------------
# TARGET name of the output
# BUILD directory where object files & intermediate files will be placed
# SOURCES list of directories containing source code
# INCLUDES list of directories containing extra header files
# DATA directory of binary files to be converted to object files
# SHADERS directory of vertex / fragment shaders to be compiled
# LIBS list of extra libraries to be link with the project
# LIBDIRS list of directories containing libraries, this must be the top level
#         containing include and lib
#---------------------------------------------------------------------------------
TARGET		:= $(notdir $(CURDIR))
BUILD		:= build
SOURCES		:= source
INCLUDES	:= include
DATA		:= data
SHADERS		:= shaders
LIBS		:= -laudio -lrt -llv2 -lm
LIBDIRS		:= $(PS3DEV)/portlibs/ppu $(PSL1GHT)/ppu


#---------------------------------------------------------------------------------
# FLAGS
# ASFLAGS
# CFLAGS
# LDFLAGS
#---------------------------------------------------------------------------------
FLAGS		:= -std=gnu99 -pedantic -mcpu=cell
CFLAGS		:= -g -O3 -Wall $(FLAGS) $(MACHDEP) $(LIBPATHS) $(INCLUDEPATHS)
CXXFLAGS	:= $(CFLAGS)
LDFLAGS		:= $(MACHDEP) -Wl,-Map,$(notdir $@).map
ASFLAGS		:=


#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))


##--------------------------------------------------------------------------------
##
## Files
##
##--------------------------------------------------------------------------------
export OUTPUT	:= $(CURDIR)/$(TARGET)
export VPATH	:= $(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
		   $(foreach dir,$(DATA),$(CURDIR)/$(dir)) \
		   $(foreach dir,$(SHADERS),$(CURDIR)/$(dir))
export BUILDDIR	:= $(CURDIR)/$(BUILD)
export DEPSDIR	:= $(BUILDDIR)
#---------------------------------------------------------------------------------
CFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
sFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
SFILES		:= $(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.S)))
BINFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.bin)))
TTFFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.ttf)))
PNGFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.png)))
JPGFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.jpg)))
GIFFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.gif)))
RAWFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.raw)))
MP3FILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.mp3)))
WAVFILES	:= $(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.wav)))
VCGFILES	:= $(foreach dir,$(SHADERS),$(notdir $(wildcard $(dir)/*.vcg)))
FCGFILES	:= $(foreach dir,$(SHADERS),$(notdir $(wildcard $(dir)/*.fcg)))
VPOFILES	:= $(VCGFILES:.vcg=.vpo)
FPOFILES	:= $(FCGFILES:.fcg=.fpo)
#---------------------------------------------------------------------------------
export OFILES	:= $(addsuffix .o,$(BINFILES)) \
		   $(addsuffix .o,$(TTFFILES)) \
		   $(addsuffix .o,$(PNGFILES)) \
		   $(addsuffix .o,$(JPGFILES)) \
		   $(addsuffix .o,$(GIFFILES)) \
		   $(addsuffix .o,$(RAWFILES)) \
		   $(addsuffix .o,$(MP3FILES)) \
		   $(addsuffix .o,$(WAVFILES)) \
		   $(addsuffix .o,$(VPOFILES)) \
		   $(addsuffix .o,$(FPOFILES)) \
		   $(CFILES:.c=.o) \
		   $(CPPFILES:.cpp=.o) \
		   $(sFILES:.s=.o) $(SFILES:.S=.o)
export INCLUDEPATHS	:= $(foreach dir,$(INCLUDES), -I$(CURDIR)/$(dir)) \
		   $(foreach dir,$(LIBDIRS),-I$(dir)/include) \
		   $(LIBPSL1GHT_INC) \
		   -I$(CURDIR)/$(BUILD)
export LIBPATHS	:= $(foreach dir,$(LIBDIRS),-L$(dir)/lib) \
		   $(LIBPSL1GHT_LIB) -L $(PSL1GHT)/ppu/lib
export OUTPUT	:= $(CURDIR)/$(TARGET)


##--------------------------------------------------------------------------------
##
## Tools
##
##--------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
LD		:= $(CC)
else
LD		:= $(CXX)
endif


##--------------------------------------------------------------------------------
##
## Rules
##
##--------------------------------------------------------------------------------

#---------------------------------------------------------------------------------
.PHONY:	$(BUILD) bin clean dex pkg run
#---------------------------------------------------------------------------------
$(BUILD): bin
	@[ -d $@ ] || mkdir -p $@
	@echo compiling ...
	@$(MAKE) --no-print-directory -C $(BUILDDIR) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------
clean:
	@echo cleaning ...
	@rm -rf $(BUILD) $(OUTPUT).a $(OUTPUT)*.elf $(OUTPUT)*.self $(OUTPUT)*.pkg

#---------------------------------------------------------------------------------
dex:	$(BUILD) $(OUTPUT).dex.self

#---------------------------------------------------------------------------------
pkg:	$(BUILD) $(OUTPUT).pkg

#---------------------------------------------------------------------------------
run:	$(BUILD) $(OUTPUT).self
	@ps3load $(OUTPUT).self

#---------------------------------------------------------------------------------
else

DEPENDS		:= $(OFILES:.o=.d)


##--------------------------------------------------------------------------------
##
## Targets
##
##--------------------------------------------------------------------------------
$(OUTPUT).dex.self:	$(OUTPUT).elf
$(OUTPUT).self:		$(OUTPUT).elf
$(OUTPUT).elf:		$(OFILES)

#---------------------------------------------------------------------------------
-include $(DEPENDS)

#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------
