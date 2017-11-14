# This is how macros are defined. They are called with $(MACRO).
#CC=g++
#LIBBOX2D_LOCATION=.
#CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -IBox2D -L$(LIBBOX2D_LOCATION) -lBox2D -std=c++11

# This is a way to create c++ objects out of %.cpp's and %.h's (% is pattern recognition). This command is needed if for instance only a .h file is changed when updating an object (otherwise make doesn't recognize a difference in the .cpp and no update happens). 
# $@ is target and $< is suffix, or first item, (%.cpp and %.h components, which make automatically recognizes). This is extremely useful.
#%.o: %.cpp 
#	$(CC) -g -c -Wall -o $@ $< $(CFLAGS)

# Standard syntax target: component1.cpp component2.h. $^ is the right side of : .
#prog: sfml_test.o
#	$(CC) -g -Wall -o $@ $^ $(CFLAGS)

#prog: sfml_test.cpp
#	$(CC) -g -Wall -o prog sfml_test.cpp $(CFLAGS)

# With folders:
# This is how macros are defined. They are called with $(MACRO).
CC=g++
IDIR=../lib/Box2D
LIBBOX2D_LOCATION=../lib
CFLAGS=-lsfml-graphics -lsfml-window -lsfml-system -I$(IDIR) -L$(LIBBOX2D_LOCATION) -lBox2D -std=c++11
ODIR=obj

# This is a way to create c++ objects out of %.cpp's and %.h's (% is pattern recognition). This command is needed if for instance only a .h file is changed when updating an object (otherwise make doesn't recognize a difference in the .cpp and no update happens). 
# $@ is target and $< is suffix, or first item, (%.cpp and %.h components, which make automatically recognizes). This is extremely useful.
$(ODIR)/%.o: %.cpp 
	$(CC) -g -c -Wall -o $@ $< $(CFLAGS)

# Standard syntax target: component1.cpp component2.h. $^ is the right side of : .
prog: $(ODIR)/sfml_test.o
	$(CC) -g -Wall -o $@ $^ $(CFLAGS)


