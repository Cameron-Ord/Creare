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