O:=builddir

default: run

# clean:
# 	ninja -v -C $(O) -t clean

setup:
	echo "/Makefile <-- /meson.build <-- /builddir/build.ninja"
	rm -rf $(O)
	meson setup $(O) .

build:
# 	meson compile -v -C $(O)
	ninja -v -C $(O) -j4

run: build
# 	env GTK_DEBUG=interactive $(O)/example-2
# 	$(O)/backlight_cli
	$(O)/backlight_gui
