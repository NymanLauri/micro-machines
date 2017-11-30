CPPFLAGS += -g -Wall -std=c++11
INC = -I../../src -I../../src/Box2D
LIB = -L../../src/Box2D
SRCDIR = ../../src
TESTFILE = CarTest.cpp
EXTSRCFILES = PhysicsObject.cpp Tire.cpp Car.cpp
SOURCES = $(EXTSRCFILES:%.cpp=$(SRCDIR)/%.cpp)
LIBS += -lsfml-graphics -lsfml-window -lsfml-system -lBox2D

test: $(TESTFILE) $(SOURCES)
	$(CXX) $(CPPFLAGS) -o test $(INC) $(LIB) $(TESTFILE) $(SOURCES) $(LIBS)
