#include <gtk/gtk.h>

static void print_hello(GtkWidget *widget, gpointer data){
  g_print("Hello World\n");
}

static void activate(GtkApplication *app, gpointer user_data){

  GtkWidget *win=gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(win), "Window");
  gtk_container_set_border_width(GTK_CONTAINER(win), 10);

  GtkWidget *grid = gtk_grid_new();
  gtk_container_add(GTK_CONTAINER(win), grid);

  GtkWidget *b1 = gtk_button_new_with_label("Button 1");
  GtkWidget *b2 = gtk_button_new_with_label("Button 2");
  GtkWidget *bQ = gtk_button_new_with_label("Quit");
  gtk_grid_attach(GTK_GRID(grid), b1, 0, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), b2, 1, 0, 1, 1);
  gtk_grid_attach(GTK_GRID(grid), bQ, 0, 1, 2, 1);
  g_signal_connect(b1, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect(b2, "clicked", G_CALLBACK(print_hello), NULL);
  g_signal_connect_swapped(bQ, "clicked", G_CALLBACK(gtk_widget_destroy), win);

  gtk_widget_show_all(win);

}

int main(int argc, char **argv){

  g_set_prgname("floating");

  GtkApplication *app = gtk_application_new("org.gtk.example", G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  const int status = g_application_run(G_APPLICATION(app), argc, argv);
  
  g_object_unref(app);

  return status;

}
