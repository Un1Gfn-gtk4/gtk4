# refer to gtk's meson.build as an example
# https://gitlab.gnome.org/GNOME/gtk/-/blob/main/meson.build

# https://mesonbuild.com/Reference-manual_functions.html#project
project('demo', 'c',
  default_options: [
  # https://mesonbuild.com/Builtin-options.html#directories
    'prefix=/usr/local',
  # https://mesonbuild.com/Builtin-options.html#core-options
    'backend=ninja',
    'buildtype=debug',
    'debug=true',
    'strip=false',
    'warning_level=3',
    'werror=true',
  # https://mesonbuild.com/Builtin-options.html#base-options
    'b_lto=true',
    'b_ndebug=false',
    # 'b_pie=true',
  # https://mesonbuild.com/Builtin-options.html#compiler-options
    'c_std=gnu18',
  ],
  license: 'AGPL-3.0',
  meson_version: '==0.61.3',
  # subproject_dir: '',
  version: '0.1',
)

# https://mesonbuild.com/Reference-manual_functions.html#executable
executable('demo', 'main.c',
  dependencies: [ dependency('gtk4') ],
  c_args: [
  # https://mesonbuild.com/Adding-arguments.html
    '-Wextra',
    '-Winline',
    '-Wno-unused-parameter',
    '-Wdeprecated-declarations',
    # '-fmax-errors=1',
    #
    '-DG_ENABLE_DEBUG', # /usr/include/gtk-4.0/gtk/gtkdebug.h gtk_set_debug_flags()
    #
    '-DGTK_DISABLE_DEPRECATED',
    #
    '-DGDK_DISABLE_DEPRECATED',
    '-DGDK_PIXBUF_DISABLE_DEPRECATED',
    '-DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_4_6', '-DGDK_VERSION_MAX_ALLOWED=GDK_VERSION_4_6',
    #
    '-DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_70', '-DGLIB_VERSION_MAX_ALLOWED=GLIB_VERSION_2_70',
  ],
  # link_args: [],
  install: true,
  pie: true,
)
