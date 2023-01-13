

UNAME := $(shell uname)

ifeq ($(shell uname -o 2>/dev/null),Msys)
	OS := MINGW
endif

ifneq ("$(OS)","")
	EZ_PATH=../../
endif

gravitationunivLIB_PATH=$(EZ_PATH)/libeasea/

CXXFLAGS =  -std=c++14 -fopenmp -O2 -g -Wall -fmessage-length=0 -I$(gravitationunivLIB_PATH)include

OBJS = gravitationuniv.o gravitationunivIndividual.o 

LIBS = -lpthread -fopenmp 
ifneq ("$(OS)","")
	LIBS += -lws2_32 -lwinmm -L"C:\MinGW\lib"
endif

#USER MAKEFILE OPTIONS :


#END OF USER MAKEFILE OPTIONS

TARGET =	gravitationuniv

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LDFLAGS) -g $(gravitationunivLIB_PATH)/libeasea.a $(LIBS)

	
#%.o:%.cpp
#	$(CXX) -c $(CXXFLAGS) $^

all:	$(TARGET)
clean:
ifneq ("$(OS)","")
	-del $(OBJS) $(TARGET).exe
else
	rm -f $(OBJS) $(TARGET)
endif
easeaclean:
ifneq ("$(OS)","")
	-del $(TARGET).exe *.o *.cpp *.hpp gravitationuniv.png gravitationuniv.dat gravitationuniv.prm gravitationuniv.mak Makefile gravitationuniv.vcproj gravitationuniv.csv gravitationuniv.r gravitationuniv.plot gravitationuniv.pop
else
	rm -f $(TARGET) *.o *.cpp *.hpp gravitationuniv.png gravitationuniv.dat gravitationuniv.prm gravitationuniv.mak Makefile gravitationuniv.vcproj gravitationuniv.csv gravitationuniv.r gravitationuniv.plot gravitationuniv.pop
endif

