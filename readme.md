[ABI Laboratory: API/ABI changes review for Gtk+](https://abi-laboratory.pro/index.php?view=timeline&l=gtk%2B)

[pcmanfm-gtk3](https://archlinux.org/packages/community/x86_64/pcmanfm-gtk3/)
- no hamburger menu
- no [GtkHeaderBar](https://developer.gnome.org/gtk4/stable/GtkHeaderBar.html)
- [GtkPopoverMenuBar](https://developer.gnome.org/gtk4/stable/GtkPopoverMenuBar.html) ([GtkMenuBar](https://developer.gnome.org/gtk3/stable/GtkMenuBar.html))
- [gtk-window-set-decorated(window,FALSE)](https://developer.gnome.org/gtk4/stable/GtkWindow.html#gtk-window-set-decorated)

[GTK 4.0 Reference Manual](https://developer.gnome.org/gtk4/4.0/)

https://wiki.gnome.org/Valgrind
*   https://www.valgrind.org/docs/manual/manual-core.html
*   https://wiki.wxwidgets.org/Valgrind_Suppression_File_Howto
*   https://stackoverflow.com/questions/8453392/suppressing-valgrind-errors-from-gtk
*   /usr/share/glib-2.0/valgrind/glib.supp
*   /usr/share/gtk-4.0/valgrind/gtk.supp
