project('cma_read', 'cpp', version : '0.1', default_options : ['warning_level=3', 'cpp_std=gnu++20'])

# Directories
src_dir = 'src'
public_include_dir = 'public'
lib_include_dir = 'includes'

# Dependencies
pybind11_dep = dependency('pybind11')

# Source files
sources = files(f'@src_dir@/flow_iterator.cpp', f'@src_dir@/flowmap.cpp', f'@src_dir@/rawdata.cpp',f'@src_dir@/fcase.cpp')
ex_sources = files(f'@src_dir@/main.cpp')

# Build shared library
shared_lib = library('cma_read_shared',
                     sources,
                     include_directories: [public_include_dir, lib_include_dir],
                     pic: true)

# Build static library
static_library('cma_read_static',
               sources,
               include_directories: [public_include_dir, lib_include_dir],
               pic: true)

# Build Python extension module
python_extension_suffix = run_command('python3-config', '--extension-suffix').stdout().strip()
python_extension_suffix = python_extension_suffix.substring(1)
python_module_name = 'cma_read'
modfile = files(f'@src_dir@/pymodule.cpp') + sources

py = shared_library(python_module_name,
                    modfile,
                    name_suffix: python_extension_suffix,
                    name_prefix: '',
                    include_directories: [public_include_dir, lib_include_dir, '/usr/include/python3.10/'],
                    dependencies: [pybind11_dep],
                    link_args: ['-lpython3.10'])

# Build executable
executable('test_cma_read',
           ex_sources,
           include_directories: [public_include_dir, lib_include_dir],
           link_with: shared_lib)
