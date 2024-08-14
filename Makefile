KULINA=/usr
#CC    	=g++ -pthread
CC     	=cc -pthread
kit	: ScrollTable.o ScrollTableCallbacks.o \
          ScrollTablemain.o GetFileName.o \
          GetMarkPos.o initkit.o
	$(CC) -o kit ScrollTable.o ScrollTableCallbacks.o \
        ScrollTablemain.o \
        GetFileName.o GetMarkPos.o initkit.o \
 -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a \
 -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread -lz -lbz2 -lGL
ScrollTable.o  	: ScrollTable.c GclrScrollTable.c
	 $(CC) -c ScrollTable.c
ScrollTableCallbacks.o 	: ScrollTableCallbacks.c
	 $(CC) -c ScrollTableCallbacks.c
ScrollTablemain.o      	: ScrollTablemain.c
	 $(CC) -c ScrollTablemain.c
clean  	:
	rm -f *.o kit
install	: kit
	cp kit /usr/bin/
