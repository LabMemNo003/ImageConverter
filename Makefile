SRCS = main.cpp debug.cpp convert.cpp

BOOST_OPTIONS = -L/usr/local/lib/ -lboost_program_options -lboost_system -lboost_filesystem -lboost_regex
OPENCV_OPTIONS = `pkg-config --libs opencv`
OTHER_OPTIONS = -std=c++11

all:
	g++ $(SRCS) $(BOOST_OPTIONS) $(OPENCV_OPTIONS) $(OTHER_OPTIONS) -o imgcvt