KULINA=/usr
#CC	=g++ -pthread
CC	=cc -fPIC -pthread
kit	: kgedit.o kgeditCallbacks.o kgeditmain.o \
	 Sbox.o GetFontString.o GetFontStringCallbacks.o \
	 Msg.o MsgCallbacks.o Setup.o SetupCallbacks.o
	 $(CC) -o kit kgedit.o kgeditCallbacks.o kgeditmain.o \
	 Sbox.o GetFontString.o GetFontStringCallbacks.o \
	 Msg.o MsgCallbacks.o Setup.o SetupCallbacks.o \
	  -I$(KULINA)/include $(KULINA)/lib/libkulina.a $(KULINA)/lib/libgm.a -L/usr/X11R6/lib -lX11 -lXext -lm -lpthread -lz -lbz2 -lGL
	 ar -rD  libkgedit.a  kgedit.o kgeditCallbacks.o 
	 $(CC) -shared -o  libkgedit.so  kgedit.o kgeditCallbacks.o 
	 cp kit Kit/
	 tar czf Kitbin.tgz Kit
kgedit.o	: kgedit.c Gclrkgedit.c 
	 $(CC) -c kgedit.c
kgeditCallbacks.o	: kgeditCallbacks.c 
	 $(CC) -c kgeditCallbacks.c
kgeditmain.o	: kgeditmain.c 
	 $(CC) -c kgeditmain.c
clean	:  
	   rm -f *.o kgedit
install	: kit
	 cp kit /usr/bin/kit
