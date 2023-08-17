# If you move this project you can change the directory 
# to match your GBDK root directory (ex: GBDK_HOME = "C:/GBDK/"
GBDK_HOME = /home/chris/tools/gbdk
JAVA = /home/chris/tools/amazon-corretto-17/bin/java
EMULICIOUS = /home/chris/tools/emulicious/Emulicious.jar

LCC = $(GBDK_HOME)/bin/lcc
PNG2ASSET = $(GBDK_HOME)/bin/png2asset

# You can set flags for LCC here
# For example, you can uncomment the line below to turn on debug output
LCCFLAGS = -I.

# You can set the name of the .gb ROM file here
PROJECTNAME    = skelecrew

SRCDIR      = src
OBJDIR      = build
SPRITEDIR	= sprite
MAPDIR		= tilemap
LEVELDIR	= levels
GENDIR		= gen
BINS	    = $(OBJDIR)/$(PROJECTNAME).gb

PNGSOURCES   = $(foreach dir,$(SPRITEDIR),$(notdir $(wildcard $(dir)/*.png)))
PNG_CSOURCES = $(PNGSOURCES:%.png=gen/%.c)
PNG_CHEADERS = $(PNGSOURCES:%.png=gen/%.h)

MAPSOURCES   = $(foreach dir,$(MAPDIR),$(notdir $(wildcard $(dir)/*.png)))
MAP_CSOURCES = $(MAPSOURCES:%.png=gen/%.c)
MAP_CHEADERS = $(MAPSOURCES:%.png=gen/%.h)

LEVELSOURCES   = $(foreach dir,$(LEVELDIR),$(notdir $(wildcard $(dir)/*.png)))
LEVEL_CSOURCES = $(LEVELSOURCES:%.png=gen/%.c)
LEVEL_CHEADERS = $(LEVELSOURCES:%.png=gen/%.h)

CSOURCES    = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.c)))
ASMSOURCES  = $(foreach dir,$(SRCDIR),$(notdir $(wildcard $(dir)/*.s)))
OBJS       = $(LEVEL_CSOURCES:gen/%.c=$(OBJDIR)/%.o) $(MAP_CSOURCES:gen/%.c=$(OBJDIR)/%.o) $(PNG_CSOURCES:gen/%.c=$(OBJDIR)/%.o) $(CSOURCES:%.c=$(OBJDIR)/%.o) $(ASMSOURCES:%.s=$(OBJDIR)/%.o)

# .d files that are generated by the compiler to show what .cpp files depend on what .h files
# so that when a header file is updated, we know which .cpp files need recompiling
DFILES = $(OBJS:.o=.d)

all:	$(OBJDIR)/ $(BINS)

.PRECIOUS: $(PNG_CSOURCES) $(MAP_CSOURCES) $(LEVEL_CSOURCES)

# Assign save.c to RAM bank 0 on the MBC
$(OBJDIR)/save.o:	$(SRCDIR)/save.c
	$(LCC) $(LCCFLAGS) -Wf-MMD -Wf-ba0 -c -o $@ $<

# Compile .c files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.c $(PNG_CSOURCES)
	$(LCC) $(LCCFLAGS) -Wf-MMD -c -o $@ $<

$(OBJDIR)/%.o:	$(GENDIR)/%.c | $(OBJDIR)/
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# Compile .s assembly files in "src/" to .o object files
$(OBJDIR)/%.o:	$(SRCDIR)/%.s | $(OBJDIR)/
	$(LCC) $(LCCFLAGS) -c -o $@ $<

# If needed, compile .c files in "src/" to .s assembly files
# (not required if .c is compiled directly to .o)
$(OBJDIR)/%.s:	$(SRCDIR)/%.c | $(OBJDIR)/
	$(LCC) $(LCCFLAGS) -S -o $@ $<

gen/gbcompo.c:	tilemap/gbcompo.png | gen/
	$(PNG2ASSET) $< -b 1 -map -noflip -c $@ 

gen/zymie.c: sprite/zymie.png | gen/
	$(PNG2ASSET) $< -spr8x8 -sw 16 -sh 16 -keep_palette_order -noflip -c $@ 

$(GENDIR)/%.c:	$(SPRITEDIR)/%.png | gen/
	$(PNG2ASSET) $< -spr8x8 -px 0 -py 0 -keep_palette_order -keep_duplicate_tiles -noflip -c $@ 

$(GENDIR)/%.c:	$(MAPDIR)/%.png | gen/
	$(PNG2ASSET) $< -b 1 -map -keep_palette_order -noflip -c $@ 

$(GENDIR)/%.c:	$(LEVELDIR)/%.png | gen/
	$(PNG2ASSET) $< -map -source_tileset tiled/metatiles.png -noflip -c $@ 

# Link the compiled object files into a .gb ROM file
$(BINS):	$(OBJS)
	$(LCC) $(LCCFLAGS) -Wm-yt0x1B -Wl-yo4 -Wl-ya4 -Wl-m -o $(BINS) $(OBJS) lib/hUGEDriver.o

$(OBJDIR)/:
	mkdir -p $(OBJDIR)

gen/:
	mkdir -p gen

clean:
	rm -rf $(OBJDIR) gen

run: build/$(PROJECTNAME).gb
	$(JAVA) -jar $(EMULICIOUS) build/$(PROJECTNAME).gb

usage: build/$(PROJECTNAME).gb
	~/tools/romusage build/$(PROJECTNAME).map -g

# '-include' will add in our .d files without erroring if one does not exist
-include $(DFILES)
