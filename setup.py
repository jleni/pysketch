# Distributed under the MIT software license, see the accompanying
# file LICENSE or http://www.opensource.org/licenses/mit-license.php.

from distutils.core import setup, Extension

module1 = Extension('pysketch.sketch_wrapper.cpp',
                    libraries = ['pysketch'],
                    include_dirs = ['src'],
                    library_dirs = ['pysketch'],
                    extra_compile_args=['-D__STDC_CONSTANT_MACROS'],
                    sources=['pysketch/sketch_wrapper.cpp'])

setup(name = 'pysketch',
      version='0.0.1',
      description = 'pySketch',
      url='https://github.com/jleni/pysketch',
      author='Juan Leni',
      license='MIT',
      ext_modules = [module1],
      packages=['pysketch'],
      package_dir={'pysketch': 'pysketch'},
      package_data={'pysketch': ['libpysketch.so']})
