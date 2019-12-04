g++ \
    -Iinclude \
    src/*.cpp \
    bin/res.o \
    `pkg-config gtkmm-3.0 --cflags --libs` \
    -o bin/ground_station.out \
    -s -std=c++17 -O3 \
    -lGL
