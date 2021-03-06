COMPILER           = g++
GTK_CFG            = pkg-config gtkmm-3.0
IFLAGS             = \
	`$(GTK_CFG) --cflags` \
	-Iinclude
LFLAGS             = \
	`$(GTK_CFG) --libs`
FLAGS              = \
	-s -g -O0 -std=gnu++17 -Wall -Wno-unused-result
LIBS               = \
	-lGL \
	-lpthread
OUT                = ground_station
SRC                = \
	src/GroundStation.cpp \
	src/Logger.cpp \
	src/BackEnd.cpp \
	src/BackEnd/ServerSocket.cpp \
	src/BackEnd/ClientSocket.cpp \
	src/BackEnd/Server.cpp \
	src/BackEnd/Clients/Satellite.cpp \
	src/BackEnd/Clients/Phone.cpp \
	src/BackEnd/Clients/Compass.cpp \
	src/BackEnd/Clients/PowerSupplies.cpp \
	src/FrontEnd.cpp \
	src/FrontEnd/Window.cpp \
	src/FrontEnd/Pages/CLI.cpp \
	src/FrontEnd/Pages/Settings.cpp \
	src/FrontEnd/Pages/Satellite.cpp
OBJS               = $(SRC:.cpp=.o)

build: $(OBJS)
	@rm -f $(OUT)
	@$(COMPILER) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LIBS) $(LFLAGS)
	@rm -f $(OBJS)

clean:
	@rm -rf $(OUT) $(OBJS)

.cpp.o:
	@$(COMPILER) $(IFLAGS) $(FLAGS) -c $< -o $@