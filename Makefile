# https://developer.gnome.org/gtk4/4.0/gtk-compiling.html

###############################################################################

MAKEFLAGS+=--no-builtin-rules
MAKEFLAGS+=--no-builtin-variables

CC:=gcc
CFLAGS+=-std=gnu11 -g -O0 -Wall -Wextra -Wno-unused-parameter -Winline -Wdeprecated-declarations # -fmax-errors=1

# https://developer.gnome.org/glib/stable/glib-Version-Information.html
# https://developer.gnome.org/glib/stable/glib-compiling.html
demo.out: CFLAGS+=\
  $(shell pkg-config --cflags gtk4) \
  -DGTK_DISABLE_DEPRECATED \
  -DGDK_DISABLE_DEPRECATED \
  -DGDK_VERSION_MIN_REQUIRED=GDK_VERSION_4_0 \
  -DGDK_VERSION_MAX_ALLOWED=GDK_VERSION_4_0 \
  -DGDK_PIXBUF_DISABLE_DEPRECATED \
  -DGLIB_VERSION_MIN_REQUIRED=GLIB_VERSION_2_66 \
  -DGLIB_VERSION_MAX_ALLOWED=GLIB_VERSION_2_66

demo.out: LDLIBS+=$(shell pkg-config --libs gtk4)

###############################################################################

# /usr/share/gtk-doc/html/glib/glib-running.html (G_DEBUG)
default: demo.out
	env G_DEBUG=fatal-warnings ./$<

clean:
	@rm -fv *.o *.out *.log *.h.gch

demo.out:
%.out: %.c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $< $(LDLIBS)

# https://wiki.gnome.org/Valgrind
# /usr/share/gtk-doc/html/glib/glib-running.html (G_DEBUG)
# --leak-resolution=high
# --num-callers=20
demo.log:
%.log: %.out %.supp
	env \
	  G_DEBUG="fatal-warnings fatal_criticals" \
	  G_SLICE=always-malloc \
	valgrind \
	  --tool=memcheck \
	  --log-file=$@ \
	  --num-callers=500 \
	  -s \
	  --suppressions=/usr/lib/valgrind/default.supp \
	  --suppressions=/usr/share/glib-2.0/valgrind/glib.supp \
	  --suppressions=/usr/share/gtk-4.0/valgrind/gtk.supp \
	  --suppressions=./$(word 2,$^) \
	  --gen-suppressions=all \
	  --leak-check=full \
	  --show-leak-kinds=definite \
	./$<
	subl $@
