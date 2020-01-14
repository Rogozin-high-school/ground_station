COMPILER           = g++
GTK_CFG            = pkg-config gtkmm-3.0
IFLAGS             = \
	`$(GTK_CFG) --cflags` \
	-Iinclude
LFLAGS             = \
	`$(GTK_CFG) --libs`
FLAGS              = \
	-s -O3 -std=gnu++17 -Wall
LIBS               = \
	-lGL \
	-lpthread
OUT                = ground_station
SRC                = \
	src/ground_station.cpp \
	src/graphics.cpp
OBJS               = $(SRC:.cpp=.o)

build: $(OBJS)
	@rm -f $(OUT)
	@$(COMPILER) $(IFLAGS) $(FLAGS) $(OBJS) -o $(OUT) $(LIBS) $(LFLAGS)
	@rm -f $(OBJS)

clean:
	@rm -rf $(OUT) $(OBJS)

.cpp.o:
	@$(COMPILER) $(IFLAGS) $(FLAGS) -c $< -o $@