#include <gtk/gtk.h>

// https://specifications.freedesktop.org/desktop-entry-spec/desktop-entry-spec-latest.html
// ... replacing it with an underscore ... cannot cause ambiguity ... underscores are not allowed in DNS domain names
#define APPID "com.github.Un1Gfn_obj.gtk4"

/*static void clicked(const GtkWidget *const widget,const gconstpointer garbage){
  g_assert(widget&&!garbage);
  g_print("clicked\n");
}*/

/*static void fail(){
  g_assert_not_reached();
}*/

static void draw(GtkApplication *const app){

  GtkWidget *const window=gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window),"Title");
  gtk_window_set_default_size(GTK_WINDOW(window),200,200);

  // GtkWidget *const button=gtk_button_new_with_label("button_label");
  // g_signal_connect(button,"clicked",G_CALLBACK(clicked),NULL);
  // gtk_window_set_child(GTK_WINDOW(window),button);

  // gtk_application_set_menubar(app,NULL);
  // g_print("A\n");

  // gtk_window_present(GTK_WINDOW(window));
  gtk_widget_show(window);
}

static void shutdown(GtkApplication *const app,const gconstpointer garbage){
  g_assert(app&&!garbage);
  g_print("shutdown\n");
  GList *l=gtk_application_get_windows(app);
  g_assert(!l);
  // g_assert( !(l->prev) && !(l->next) && (l->data) );
  // GtkWindow *win=GTK_WINDOW(l->data);
  // gtk_application_remove_window(app,win);
  // gtk_window_destroy(win);
}

static void activate(GtkApplication *const app,const gconstpointer garbage){
  g_assert(app&&!garbage);
  draw(app);
}

/*static int command_line(GtkApplication *const app, GApplicationCommandLine *const cmdline, const gconstpointer *garbage){
  g_assert(app&&!garbage);
  draw(app);
  return 0;
}*/

int main(const int argc,char **const argv){

  if(!gtk_init_check()){
    printf("fall back to textual interface\n");
    return 0;
  }

  // https://en.wikipedia.org/wiki/Reverse_domain_name_notation
  g_assert(g_application_id_is_valid(APPID));

  // No command line args
  GtkApplication *app=gtk_application_new(APPID,G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app,"shutdown",G_CALLBACK(shutdown),NULL);
  g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
  g_set_prgname("floating"); // ~/.i3/conf/00-forwindow // https://unix.stackexchange.com/questions/521019/specifying-the-wm-class-of-a-program
  g_assert(0==g_application_run(G_APPLICATION(app),0,NULL)); // Invalid read of size ...

  // Command line args e.g. --gapplication-app-id
  // gio/stable/GApplication.html#g-application-run
  // GtkApplication *app=gtk_application_new(APPID,G_APPLICATION_CAN_OVERRIDE_APP_ID|G_APPLICATION_HANDLES_COMMAND_LINE);
  // g_signal_connect(app,"command-line",G_CALLBACK(command_line),NULL);
  // g_assert(0==g_application_run(G_APPLICATION(app),argc,argv)); // Invalid read of size ...

  // g_print("%s\n",g_get_prgname());
  // g_print("%s\n",g_get_application_name());
  // // https://stackoverflow.com/questions/27823299
  // // g_print("%s\n",g_application_get_application_id(G_TYPE_CHECK_INSTANCE_CAST()));
  // g_print("%s\n",g_application_get_application_id(G_APPLICATION(app)));

  g_object_unref(app);
  app=NULL;
  return EXIT_SUCCESS;

}
