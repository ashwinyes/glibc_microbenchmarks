#Compile with new glibc
GLIBC_INSTALL_PATH=/path_to_new_glibc_build

gcc -fno-builtin -I$GLIBC_INSTALL_PATH/include \
	-Wl,--rpath=$GLIBC_INSTALL_PATH/lib \
	-Wl,--dynamic-linker=$GLIBC_INSTALL_PATH/lib/ld-linux-aarch64.so.1 \
	"$@" -lm -o bin/new.out

#Compile with old glibc
GLIBC_INSTALL_PATH=/path_to_old_glibc_build

gcc -fno-builtin -I$GLIBC_INSTALL_PATH/include \
	-Wl,--rpath=$GLIBC_INSTALL_PATH/lib \
	-Wl,--dynamic-linker=$GLIBC_INSTALL_PATH/lib/ld-linux-aarch64.so.1 \
	"$@" -lm -o bin/old.out
