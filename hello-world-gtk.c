#include <gtk/gtk.h>
// #include <assert.h>

// #define APPLICATION_ID "org.gtk.example"
#define APPLICATION_ID "com.github.Un1Gfn.gtk4"
#define TITLE "Example"

static void print_hello(const GtkWidget *const widget,const gconstpointer garbage){
  g_assert(widget&&!garbage);
  g_print("stdout\n");
  g_printerr("stderr\n");
}

static void fail(){
  g_assert_not_reached();
}

static void draw(GtkApplication *const app){

  GtkWidget *const window=gtk_application_window_new(app);
  gtk_window_set_title(GTK_WINDOW(window),TITLE);
  gtk_window_set_default_size(GTK_WINDOW(window),200,200);

  GtkWidget *const button=gtk_button_new_with_label("Hello World");
  g_signal_connect(button,"clicked",G_CALLBACK(print_hello),NULL);
  gtk_window_set_child(GTK_WINDOW(window),button);

  // gtk_application_set_menubar(app,NULL);
  // g_print("A\n");

  gtk_window_present(GTK_WINDOW(window));
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
  g_assert(g_application_id_is_valid(APPLICATION_ID));

  // No command line args
  GtkApplication *app=gtk_application_new(APPLICATION_ID,G_APPLICATION_FLAGS_NONE);
  g_signal_connect(app,"activate",G_CALLBACK(activate),NULL);
  g_signal_connect(app,"command-line",G_CALLBACK(fail),NULL);
  const int status=g_application_run(G_APPLICATION(app),0,NULL); // Invalid read of size ...

  // Command line args e.g. --gapplication-app-id
  // gio/stable/GApplication.html#g-application-run
  // GtkApplication *app=gtk_application_new(APPLICATION_ID,G_APPLICATION_CAN_OVERRIDE_APP_ID|G_APPLICATION_HANDLES_COMMAND_LINE);
  // g_signal_connect(app,"activate",G_CALLBACK(fail),NULL);
  // g_signal_connect(app,"command-line",G_CALLBACK(command_line),NULL);
  // const int status=g_application_run(G_APPLICATION(app),argc,argv); // Invalid read of size ...

  g_assert(status==0);

  g_print("%s\n",g_get_prgname());
  g_print("%s\n",g_get_application_name());

  // g_print("%s\n",g_application_get_application_id((GApplication*)app));
  g_print("%s\n",g_application_get_application_id(G_APPLICATION(app)));
  // https://stackoverflow.com/questions/27823299
  // g_print("%s\n",g_application_get_application_id(G_TYPE_CHECK_INSTANCE_CAST()));

  g_object_unref(app);
  app=NULL;

  return status;

  // return 0;

}
