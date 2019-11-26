cd res

glib-compile-resources \
    --target=../bin/res.c \
    --generate-source res.xml

cd ../bin

g++ \
    res.c \
    `pkg-config gtkmm-3.0 --cflags` \
    -c
rm res.c

cd ..