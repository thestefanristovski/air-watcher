src := $(shell ls *.cpp)
objs:= $(patsubst %.cpp,%.o,$(src)) 
 
AirWatcher : $(objs)
	g++ -o $@ $^
 
%.o : %.cpp
	g++ -c -o $@ $<
 
clean :
	rm -f AirWatcher *.o

