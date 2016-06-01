import subprocess

sdl_prefix = subprocess.check_output(["sdl2-config", "--prefix"]).strip()
lua_prefix = '/usr/local/Cellar/lua/5.2.4_3/lib'
sdl_libs = ['SDL2','SDL2_image', 'SDL2_ttf', 'pthread']
other_libs = ['m', 'dl', 'lua']

targetSuffix = ''
base ='#/src'

libs = sdl_libs + other_libs
libpaths = ['/usr/lib', sdl_prefix + '/lib']
cppflags = ['-D_REENTRANT']
sourcepaths = [base, sdl_prefix + '/include']
linkflags = []
