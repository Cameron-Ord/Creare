project('test', 'c')


src = [
    'src/binary.c', 
    'src/font.c', 
    'src/gfx.c',
    'src/input.c', 
    'src/main.c', 
    'src/render.c', 
    'src/renderer.c', 
    'src/window.c'
]

host = host_machine.system()
if host == 'windows'
    libsdl_inc = include_directories('C:/SDL2/include')
    libsdl_dep = declare_dependency(
        include_directories: libsdl_inc,
        compile_args: ['-DSDL_MAIN_HANDLED'],
        link_args: [
            '-LC:/SDL2/lib', 
            '-lSDL2main', 
            '-lSDL2', 
            '-lSDL2_image', 
            '-lm',
        ]
    )

    executable('tmlc', sources: src,c_args: ['-Wall',  '-Wextra',  '-pedantic'], dependencies: libsdl_dep, win_subsystem: 'console')
endif
