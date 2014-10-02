EXEC = boost_serial
OBJS = boost_serial.cpp
CXX  = g++
CXXFLAGS = -Wall -g
LIBS = -lopencv_core -lopencv_imgproc -lopencv_highgui -lserial -lboost_iostreams-mt -lboost_signals-mt -lboost_serialization-mt -lboost_system-mt
LDFLAGS = -I/opt/local/include/opencv -I/opt/local/include -I/usr/local/include -I/opt/local/include/boost
LDLIBS  = -L/opt/local/lib -L/usr/local/lib

$(EXEC): $(OBJS)
	$(CXX) $(CXXFLAGS) $(LDFLAGS) $(LDLIBS) $(OBJS) -o $@ $(LIBS)

#detecting2.o : detecting2.cpp
#	$(CXX) $(CXXFLAGS) $(LDFLAGS) -c detecting2.cpp $(LIBS)

.PHONY: clean

clean:
	rm -f $(EXEC) *~ 

