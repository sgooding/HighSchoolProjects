include ../../makefile.top

CXXDIR = -I/usr/include/ -I/usr/include/w32api/ $(CMU_INC)

LIBDIR  = -L/usr/X11R6/lib -L/usr/lib/w32api/ $(CMU_LIB_DIR)

CXXFLAGS = $(COMPILERFLAGS) 

LIBS = -lcmugraphics -lgdi32 -lgdiplus -lwinmm 

TARGET=Projectile

ADD_TARGET+=$(TARGET)

$(TARGET): $(TARGET).o
	$(CXX) $(OPT) $^ -o $@ $(LIBDIR) $(LIBS) 

.cpp.o:
	$(CXX) $(CXXFLAGS) $(CXXDIR) -c $< -o $@

clean: 
	rm *.o $(TARGET) 


include ../../makefile.post
