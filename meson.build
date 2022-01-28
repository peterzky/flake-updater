project('updater', 'c',
        version : '0.1',
        default_options : ['warning_level=3',
                           'c_std=c11'])

# libuv_dep = dependency('libuv')
json_dep = dependency('json-c')
thread_dep = dependency('threads')

exe = executable('flake-updater',
                 ['src/main.c',
                  'src/dir.h',
                  'src/dir.c',
                  'src/pkg.h',
                  'src/pkg.c'],
                 dependencies: [json_dep, thread_dep],
                 install : true)
