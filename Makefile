KULINA=/usr
#CC    	=g++ -pthread
CC     	=cc -pthread
kit	: ScrollTable.o ScrollTableCallbacks.o \
          ScrollTablemain.o GetFileName.o \
          GetMarkPos.o initkit.o\
	 Setup.o SetupCallbacks.o 
	$(CC) -o kit ScrollTable.o ScrollTableCallbacks.o \
        ScrollTablemain.o \
        GetFileName.o GetMarkPos.o initkit.o \
	 Setup.o SetupCallbacks.o \
 -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a \
 -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread -lz -lbz2 -lGL
ScrollTable.o  	: ScrollTable.c GclrScrollTable.c
	 $(CC) -c ScrollTable.c
ScrollTableCallbacks.o 	: ScrollTableCallbacks.c
	 $(CC) -c ScrollTableCallbacks.c
ScrollTablemain.o      	: ScrollTablemain.c
	 $(CC) -c ScrollTablemain.c
Setup.o	: Setup.c GclrSetup.c 
	 $(CC) -c Setup.c
SetupCallbacks.o	: SetupCallbacks.c 
	 $(CC) -c SetupCallbacks.c
clean  	:
	rm -f *.o kit
install	: kit
	cp kit /usr/bin/
	 tar xzf fonts.tar -C /usr/share/fonts
