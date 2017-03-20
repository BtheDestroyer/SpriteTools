#---------------------------------------------------------------------------------
.SUFFIXES:
#---------------------------------------------------------------------------------

ifeq ($(strip $(DEVKITARM)),)
$(error "Please set DEVKITARM in your environment. export DEVKITARM=<path to>devkitARM")
endif

include $(DEVKITARM)/3ds_rules

#---------------------------------------------------------------------------------
# TARGET is the name of the output
# BUILD is the directory where object files & intermediate files will be placed
# SOURCES is a list of directories containing source code
# DATA is a list of directories containing data files
# INCLUDES is a list of directories containing header files
#---------------------------------------------------------------------------------
TARGET		:=	spritetools
BUILD			:=	build
SOURCES		:=	source
DATA			:=	data
INCLUDES	:=	include

#---------------------------------------------------------------------------------
# options for code generation
#---------------------------------------------------------------------------------
ARCH	:=	-march=armv6k -mtune=mpcore -mfloat-abi=hard -mtp=soft

CFLAGS	:=	-g -Wall -Werror -O2 -mword-relocations \
			-ffunction-sections -fno-strict-aliasing \
			-fomit-frame-pointer \
			$(ARCH)

CFLAGS	+=	$(INCLUDE) -DARM11 -D_3DS

CXXFLAGS	:= $(CFLAGS) -fno-rtti -fno-exceptions -std=gnu++11

ASFLAGS	:=	-g $(ARCH)

LIBS 	:=	-lsf2d -lcitro3d -lctru -lm

#---------------------------------------------------------------------------------
# list of directories containing libraries, this must be the top level containing
# include and lib
#---------------------------------------------------------------------------------
LIBDIRS	:=	$(CTRULIB)
SF2DLIB :=  $(CTRULIB)/lib/libspritetools.a

#---------------------------------------------------------------------------------
# no real need to edit anything past this point unless you need to add additional
# rules for different file extensions
#---------------------------------------------------------------------------------
ifneq ($(BUILD),$(notdir $(CURDIR)))
#---------------------------------------------------------------------------------

export OUTPUT	:=	$(CURDIR)/lib/lib$(TARGET).a

export VPATH	:=	$(foreach dir,$(SOURCES),$(CURDIR)/$(dir)) \
			$(foreach dir,$(DATA),$(CURDIR)/$(dir))

export DEPSDIR	:=	$(CURDIR)/$(BUILD)

CFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.c)))
CPPFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.cpp)))
SFILES		:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.s)))
PICAFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.v.pica)))
SHLISTFILES	:=	$(foreach dir,$(SOURCES),$(notdir $(wildcard $(dir)/*.shlist)))
BINFILES	:=	$(foreach dir,$(DATA),$(notdir $(wildcard $(dir)/*.*)))

#---------------------------------------------------------------------------------
# use CXX for linking C++ projects, CC for standard C
#---------------------------------------------------------------------------------
ifeq ($(strip $(CPPFILES)),)
#---------------------------------------------------------------------------------
	export LD	:=	$(CC)
#---------------------------------------------------------------------------------
else
#---------------------------------------------------------------------------------
	export LD	:=	$(CXX)
#---------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------


ifneq ($(OS),Windows_NT)
	export DEPMKDIR := mkdir dependencies\
else
	export DEPMKDIR := mkdir -p dependencies/
endif


export OFILES	:=	$(addsuffix .o,$(BINFILES)) \
			$(PICAFILES:.v.pica=.shbin.o) $(SHLISTFILES:.shlist=.shbin.o) \
			$(CPPFILES:.cpp=.o) $(CFILES:.c=.o) $(SFILES:.s=.o)

export INCLUDE	:=	$(foreach dir,$(INCLUDES),-I$(CURDIR)/$(dir)) \
			$(foreach dir,$(LIBDIRS),-I$(dir)/include) \
			-I$(CURDIR)/$(BUILD)

.PHONY: $(BUILD) clean all

#---------------------------------------------------------------------------------
all: $(BUILD)

lib:
	@[ -d $@ ] || mkdir -p $@

$(BUILD): $(CTRULIB)/lib/libctru.a $(CTRULIB)/lib/libcitro3d.a $(CTRULIB)/lib/libsf2d.a $(CTRULIB)/lib/libsfil.a lib
	@[ -d $@ ] || mkdir -p $@
	@$(MAKE) --no-print-directory -C $(BUILD) -f $(CURDIR)/Makefile

#---------------------------------------------------------------------------------

libctru:
	@$(MAKE) $(CTRULIB)/lib/libctru.a

$(CTRULIB)/lib/libctru.a:
	@echo "Installing libctru dependency"
	@echo "    Cloning ctrulib from smealum's github..."
	-@git clone https://github.com/smealum/ctrulib dependencies/libctru/
	@echo "    Making and installing..."
	@$(MAKE) install -C dependencies/libctru/libctru/ -s
	@echo ""

libcitro3d:
	@$(MAKE) $(CTRULIB)/lib/libcitro3d.a

$(CTRULIB)/lib/libcitro3d.a: $(CTRULIB)/lib/libctru.a
	@echo "Installing libcitro3d dependency"
	@echo "    Cloning libcitro3d from fincs' github..."
	-@git clone https://github.com/fincs/citro3d dependencies/libcitro3d/
	@echo "    Making and installing..."
	@$(MAKE) install -C dependencies/libcitro3d/ -s
	@echo ""

libsf2d:
	@$(MAKE) $(CTRULIB)/lib/libsf2d.a

$(CTRULIB)/lib/libsf2d.a: $(CTRULIB)/lib/libctru.a $(CTRULIB)/lib/libcitro3d.a
	@echo "Installing libsf2d dependency"
	@echo "    Cloning sf2dlib from xerpi's github..."
	-@git clone https://github.com/xerpi/sf2dlib dependencies/libsf2d/
	@echo "    Making and installing..."
	@$(MAKE) install -C dependencies/libsf2d/libsf2d/ -s
	@echo ""

portlibs:
	@$(MAKE) $(DEVKITPRO)/portlibs/armv6k

$(DEVKITPRO)/portlibs/armv6k:
	@echo "Installing 3ds_portlibs dependency"
	@echo "    Cloning 3ds_portlibs from devkitPro's github..."
	-@git clone https://github.com/devkitpro/3ds_portlibs dependencies/3ds_portlibs/
	@echo "    Making and installing..."
	@echo "        Making zlib..."
	@$(MAKE) zlib -C dependencies/3ds_portlibs/ -s
	@echo "        Installing zlib..."
	@$(MAKE) install-zlib -C dependencies/3ds_portlibs/ -s
	@echo "        Making sqlite, libpng, libjpeg-turbo, libexif, and freetype..."
	@$(MAKE) sqlite libpng libjpeg-turbo libexif freetype -C dependencies/3ds_portlibs/ -s
	@echo "        Installing sqlite, libpng, libjpeg-turbo, libexif, and freetype..."
	@$(MAKE) install -C dependencies/3ds_portlibs/ -s
	@echo ""

sfillib:
	@$(MAKE) $(CTRULIB)/lib/libsfil.a

$(CTRULIB)/lib/libsfil.a: $(CTRULIB)/lib/libctru.a $(CTRULIB)/lib/libcitro3d.a $(CTRULIB)/lib/libsf2d.a $(DEVKITPRO)/portlibs/armv6k
	@echo "Installing libsfil dependency"
	@echo "    Cloning libsfil from xerpi's github..."
	-@git clone https://github.com/xerpi/sfillib dependencies/libsfil/
	@echo "    Making and installing..."
	@$(MAKE) install -C dependencies/libsfil/libsfil/ -s
	@echo ""

#---------------------------------------------------------------------------------
clean:
	@echo clean ...
	@rm -rf $(BUILD) dependencies lib latex html

#---------------------------------------------------------------------------------
install: $(BUILD)
	@echo "Copying .a library..."
	@cp $(OUTPUT) $(CTRULIB)/lib
	@echo "Done!"
	@echo "Copying .h files..."
	@cp -r include/* $(CTRULIB)/include
	@echo "Done!"
	@echo "Installed!"


#---------------------------------------------------------------------------------
docs:
	@doxygen Doxyfile

#---------------------------------------------------------------------------------
else

DEPENDS	:=	$(OFILES:.o=.d)

#---------------------------------------------------------------------------------
# main targets
#---------------------------------------------------------------------------------
$(OUTPUT)	:	$(OFILES)

#---------------------------------------------------------------------------------
%.bin.o	:	%.bin
#---------------------------------------------------------------------------------
	@echo $(notdir $<)
	@$(bin2o)

#---------------------------------------------------------------------------------
# rules for assembling GPU shaders
#---------------------------------------------------------------------------------
define shader-as
	$(eval CURBIN := $(patsubst %.shbin.o,%.shbin,$(notdir $@)))
	picasso -o $(CURBIN) $1
	bin2s $(CURBIN) | $(AS) -o $@
	echo "extern const u8" `(echo $(CURBIN) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"_end[];" > `(echo $(CURBIN) | tr . _)`.h
	echo "extern const u8" `(echo $(CURBIN) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`"[];" >> `(echo $(CURBIN) | tr . _)`.h
	echo "extern const u32" `(echo $(CURBIN) | sed -e 's/^\([0-9]\)/_\1/' | tr . _)`_size";" >> `(echo $(CURBIN) | tr . _)`.h
endef

%.shbin.o : %.v.pica %.g.pica
	@echo $(notdir $^)
	@$(call shader-as,$^)

%.shbin.o : %.v.pica
	@echo $(notdir $<)
	@$(call shader-as,$<)

%.shbin.o : %.shlist
	@echo $(notdir $<)
	@$(call shader-as,$(foreach file,$(shell cat $<),$(dir $<)/$(file)))

-include $(DEPENDS)

#---------------------------------------------------------------------------------------
endif
#---------------------------------------------------------------------------------------
