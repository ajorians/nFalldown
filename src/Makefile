GCC = nspire-g++
LD = nspire-ld
GENZEHN = genzehn

GCCFLAGS = -Os -Wall -W -marm -Wno-unused-parameter -I include
LDFLAGS = -L lib -lndls -lFalldown -lHighScore
OBJCOPY := "$(shell which arm-elf-objcopy 2>/dev/null)"
ifeq (${OBJCOPY},"")
	OBJCOPY := arm-none-eabi-objcopy
endif
EXE = nFalldown-sdl
DISTDIR = ..

OBJS = $(patsubst %.cpp,%.o,$(wildcard *.cpp))
vpath %.tns $(DISTDIR)
vpath %.elf $(DISTDIR)

all: prepare $(EXE).prg.tns

prepare:
	cd HighScoreLib; make; cd ..
	cd FalldownLib; make; cd ..
	mkdir include
	mkdir include/HighScoreLib
	mkdir include/FalldownLib
	mkdir lib
	cp -v HighScoreLib/include/HighScoreLib.h include/HighScoreLib
	cp -v HighScoreLib/libHighScore.a lib
	cp -v FalldownLib/include/FalldownLib.h include/FalldownLib
	cp -v FalldownLib/libFalldown.a lib

%.o: %.cpp
	$(GCC) $(GCCFLAGS) -c $<

$(EXE).elf: $(OBJS)
	mkdir -p $(DISTDIR)
	$(LD) $^ -o $(DISTDIR)/$@ $(LDFLAGS)

$(EXE).tns: $(EXE).elf
	$(GENZEHN) --input $(DISTDIR)/$^ --output $(DISTDIR)/$@ $(ZEHNFLAGS)

$(EXE).prg.tns: $(EXE).tns
	make-prg $(DISTDIR)/$^ $(DISTDIR)/$@

clean:
	cd HighScoreLib; make clean
	cd FalldownLib; make clean
	rm -rf include
	rm -rf lib
	rm -f *.o *.elf
	rm -f $(DISTDIR)/$(EXE).elf
	rm -f $(DISTDIR)/$(EXE).tns
	rm -f $(DISTDIR)/$(EXE).prg.tns

