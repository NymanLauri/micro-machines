CPPFLAGS += -g -Wall -std=c++11
INC = -I../../../src -I../../../src/Box2D
LIB = -L../../../src
SRCDIR = ../../../src
TESTFILE = EditorTest.cpp
EXTSRCFILES = PhysicsObject.cpp
SOURCES = $(EXTSRCFILES:%.cpp=$(SRCDIR)/%.cpp)
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lBox2D

test: $(TESTFILE) $(SOURCES)
	$(CXX) $(CPPFLAGS) -o test $(INC) $(LIB) $(TESTFILE) $(SOURCES) $(LIBS)
