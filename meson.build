# refer to gtk's meson.build as an example
# https://gitlab.gnome.org/GNOME/gtk/-/blob/main/meson.build

# https://mesonbuild.com/Reference-manual_functions.html#project
project('gtk3', 'c',
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
  meson_version: '==0.62.0',
  # subproject_dir: '',
  version: '0.1',
)


d = [ dependency('gtk+-3.0') ]

a = [
  # https://mesonbuild.com/Adding-arguments.html
  #
  '-Wextra',
  '-Winline',
  '-Wno-unused-parameter',
  '-Wdeprecated-declarations',
  #
  '-DG_ENABLE_DEBUG', # /usr/include/gtk-3.0/gtk/gtkdebug.h gtk_set_debug_flags()
  #
  '-DGTK_DISABLE_DEPRECATED',
  #
  '-DGDK_DISABLE_DEPRECATED',
  '-DGDK_PIXBUF_DISABLE_DEPRECATED',
  '-DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_3_24', '-DGDK_VERSION_MAX_ALLOWED=GDK_VERSION_3_24',
  #
  '-DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_72', '-DGLIB_VERSION_MAX_ALLOWED=GLIB_VERSION_2_72',
  #
]


executables = [
  'example-0',
  'example-1',
  'example-2',
]

# https://mesonbuild.com/Syntax.html#foreach-statements
foreach i : executables
  # https://mesonbuild.com/Reference-manual_functions.html#executable
  executable(i, i+'.c', dependencies: d, c_args: a)
endforeach

executable('backlight_gui', 'backlight_gui.c', 'backlight.c', dependencies: d, c_args: a)

executable('backlight_cli', 'backlight_cli.c', 'backlight.c')
