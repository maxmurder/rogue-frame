import os

env = Environment(ENV = {   'PATH' : os.environ['PATH'],
                            'HOME' : os.environ['HOME'],
                            'TERM' : 'xterm'})
                            
AddOption(  '--win64', 
            action = 'store_true',
            help = 'cross-compiles for windows',
            default = False)
            
if GetOption('win64'):
    env['CXX'] = 'x86_64-w64-mingw32-g++'
    vardir = 'build/win'
else:
    env['CXX']='g++'
    vardir='build/linux'
    
VariantDir(vardir, 'src')
Export('env')
SConscript(vardir + '/SConscript')
