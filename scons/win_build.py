
cross_prefix = "/usr/local/cross-tools/x86_64-w64-mingw32"
sdl_libs = ['mingw32', 'SDL2main', 'SDL2_image', 'SDL2_ttf', 'SDL2']
other_libs = ['m', 'dinput8', 'dxguid', 'dxerr8', 'user32',
              'gdi32', 'winmm', 'imm32', 'ole32', 'oleaut32',
              'shell32', 'version', 'uuid', 'lua5.2']

targetSuffix = '.exe'
base ='#/src'
libs = sdl_libs + other_libs
libpaths = ['#/lib/']
cppflags = ['-Dmain=SDL_main']
sourcepaths = [base, cross_prefix + '/include']
linkflags = ['--static',
             '-Wl,--no-undefined',
             '-static-libgcc',
             '-static-libstdc++']
