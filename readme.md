<!--

https://autotools.io/libtool/version.html
https://developer.gnome.org/programming-guidelines/stable/versioning.html.en
https://developer.gnome.org/programming-guidelines/stable/api-stability.html.en
https://www.youtube.com/watch?v=qjF-VotgfeY
https://github.com/thesquash/stlwrt
https://forum.xfce.org/viewtopic.php?id=14023
https://www.youtube.com/watch?v=FEQgHueobG0
https://blogs.gnome.org/alexl/2019/03/29/broadway-adventures-in-gtk4/

https://gitlab.gnome.org/GNOME/glib/-/blob/master/gio/tests/gapplication-example-cmdline.c
https://gitlab.gnome.org/GNOME/glib/-/blob/master/gio/tests/gapplication-example-cmdline2.c
https://gitlab.gnome.org/GNOME/glib/-/blob/master/gio/tests/gapplication-example-cmdline3.c
https://gitlab.gnome.org/GNOME/glib/-/blob/master/gio/tests/gapplication-example-cmdline4.c

https://en.wikipedia.org/wiki/Common_Desktop_Environment
https://github.com/Immediate-Mode-UI/Nuklear
https://github.com/raizam/gamedev_libraries
https://en.wikipedia.org/wiki/Motif_(software)
https://aur.archlinux.org/packages/cdesktopenv/
https://sourceforge.net/projects/cdesktopenv/files/src/
https://developers.slashdot.org/story/01/05/23/0035232/the-superior-motif
https://sourceforge.net/p/motif/code/ci/master/tree/
http://users.cs.cf.ac.uk/Dave.Marshall/X_lecture/node5.html

-->



[HowDoI](https://wiki.gnome.org/HowDoI) &nbsp; [BestPractices](https://wiki.gnome.org/Projects/GTK/BestPractices) &nbsp; [CommonQuestions](/usr/share/gtk-doc/html/gtk4/gtk-question-index.html)

---

Offline docs
*   [GObject](/usr/share/gtk-doc/html/gobject/index.html)
*   [GLib](/usr/share/gtk-doc/html/glib/index.html)
*   [GTK4](/usr/share/gtk-doc/html/gtk4/index.html) ([online](https://developer.gnome.org/gtk4/4.0/))
*   [GIO](/usr/share/gtk-doc/html/gio/index.html)

https://wiki.gnome.org/Valgrind
*   https://www.valgrind.org/docs/manual/mc-manual.html#mc-manual.suppfiles
*   https://www.valgrind.org/docs/manual/manual-core.html
*   https://wiki.wxwidgets.org/Valgrind_Suppression_File_Howto
*   https://stackoverflow.com/questions/16659781/memory-leaks-in-gtk-hello-world-program
*   https://stackoverflow.com/questions/8453392/suppressing-valgrind-errors-from-gtk
*   https://stackoverflow.com/questions/16872178/memory-leaks-shown-by-valgrind-to-gtk-init-call

---

[ABI Laboratory - API/ABI changes review for Gtk+](https://abi-laboratory.pro/index.php?view=timeline&l=gtk%2B)

[pcmanfm-gtk3](https://archlinux.org/packages/community/x86_64/pcmanfm-gtk3/)
- no hamburger menu
- no [GtkHeaderBar](https://developer.gnome.org/gtk4/stable/GtkHeaderBar.html)
- [GtkPopoverMenuBar](https://developer.gnome.org/gtk4/stable/GtkPopoverMenuBar.html) ([GtkMenuBar](https://developer.gnome.org/gtk3/stable/GtkMenuBar.html))
- [gtk-window-set-decorated(window,FALSE)](https://developer.gnome.org/gtk4/stable/GtkWindow.html#gtk-window-set-decorated)
