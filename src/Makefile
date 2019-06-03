PROJECT				:= /home/shiny/repository/WebServer/
MAINSOURCE 			:= main.cpp

SOURCE  			:= $(wildcard *.cpp base/*.cpp)
override SOURCE 	:= $(filter-out $(MAINSOURCE),$(SOURCE))
OBJS    			:= $(patsubst %.cpp,%.o,$(SOURCE))

HTML				:= $(PROJECT)src/target/bin/
COMMON				:= $(PROJECT)src/common/
BIN 				:= $(PROJECT)src/target/bin/
INDEX 				:= $(PROJECT)index/
TARGET  			:= $(BIN)server

CC      			:= g++

LIBS    			:= -lpthread
INCLUDE				:= -I./usr/local/lib
CFLAGS  			:= -std=c++11 -g -Wall -O3 -D_PTHREADS

CXXFLAGS			:= $(CFLAGS)

all : $(TARGET)

objs : $(OBJS)

$(TARGET) : $(OBJS) main.o
	[ -e $(BIN) ] || mkdir -p $(BIN)
	$(CC) $(CXXFLAGS) -o $@ $^ $(LDFLAGS) $(LIBS)

.PHONY :

clean :
	find . -name '*.o' | xargs rm -f

cleanweb :
	find . -name '*.html' | xargs sudo rm -rf
	find . -name 'pics' | xargs sudo rm -rf

run :
	sh run.sh

stop :
	sudo killall server

ln :
	sudo ln -s $(INDEX)index.html	$(HTML)
	sudo ln -s $(INDEX)pics/		$(HTML)
