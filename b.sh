bin=bin
build=build
exe=${build}/tmlc.exe
gfx=gfx/chars.png

meson setup --reconfigure $build
meson compile -C $build

if [ -d $bin ]; then
    mv $exe $bin
    cp $gfx $bin
else
    mkdir $bin
    mv $exe $bin
    cp $gfx $bin
fi

binary_bin=${HOME}/Documents/tmlc_binaries/
spritesheet_bin=${HOME}/Documents/spritesheets/

if [ ! -d $binary_bin ]; then 
    mkdir -p $binary_bin
fi

if [ ! -d $spritesheet_bin ]; then
    mkdir -p $spritesheet_bin
fi