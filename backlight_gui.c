#include <assert.h>
#include <gtk/gtk.h>

#include "./backlight.h"

static GtkWidget *win=NULL;
static GtkWidget *bB=NULL;
static GtkWidget *bD=NULL;

static void closewin(GtkWidget *w, gpointer p){
  gtk_widget_destroy(win);
  backlight_revert();
  puts("bye.closewin.revert");
}

static void click(GtkWidget *w, gpointer p){

  assert(!p);
  if(bB==w)
    backlight_brighten();
  else if(bD==w)
    backlight_dim();
  else
    assert(false);

  if(!backlight_upd()){

    GtkWidget *dialog=gtk_message_dialog_new(
      /*parent*/  GTK_WINDOW(win),
      /*flags*/   GTK_DIALOG_MODAL|GTK_DIALOG_DESTROY_WITH_PARENT,
      /*type*/    GTK_MESSAGE_QUESTION,
      /*buttons*/ GTK_BUTTONS_YES_NO,
      /*msgfmt*/  "%s", "Take effect?");
    const gint rid=gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog); dialog=NULL;
    if(GTK_RESPONSE_NO==rid){
      backlight_revert();
      puts("bye.narrow.revert");
    }else{
      assert(GTK_RESPONSE_YES==rid);
      puts("bye.narrow.save");
    }

    gtk_widget_destroy(win);

  }
}

static void button_label_align_fill2start(GtkButton *b){

  assert(GTK_TYPE_BUTTON==G_OBJECT_TYPE(b));

  GList *l=gtk_container_get_children(GTK_CONTAINER(b));
  assert(!l->next);

  GtkLabel *lb=l->data;
  assert(GTK_TYPE_LABEL==G_OBJECT_TYPE(lb));

  assert(GTK_ALIGN_FILL==gtk_widget_get_halign(GTK_WIDGET(lb)));
  gtk_widget_set_halign(GTK_WIDGET(lb),GTK_ALIGN_START);

}

static void key_press_event(GtkWidget* w, GdkEventKey *e, gpointer p){
  assert(!p);
  assert(win==w);
  switch(e->keyval){
    case GDK_KEY_equal:
    case GDK_KEY_plus:
      // g_signal_emit_by_name(bB,"button-press-event",NULL); // no animation
      g_signal_emit_by_name(GTK_BUTTON(bB),"activate",NULL); // animation
      break;
    case GDK_KEY_underscore:
    case GDK_KEY_minus:
      // g_signal_emit_by_name(bD,"button-press-event",NULL); // no animation
      g_signal_emit_by_name(GTK_BUTTON(bD),"activate",NULL); // animation
      break;
    default:
      printf("unknown key [0x%x] '%c'\n", e->keyval, e->keyval);
      break;
  }
}

static void activate(GtkApplication *a, gpointer p){
  
  assert(a);
  assert(!p);

  // bottom-up widgets

  bD=gtk_button_new_with_label("(-) dim [?]");
  bB=gtk_button_new_with_label("(+) brighten [?]");
  gtk_widget_set_has_tooltip(bB,TRUE);
  gtk_widget_set_has_tooltip(bD,TRUE);
  gtk_widget_set_tooltip_text(bB,"If the screen is too dark,\nincrease brightness to brighten it");
  gtk_widget_set_tooltip_text(bD,"if the screen emits too much glare,\nreduce brightness to dim it");
  g_signal_connect(bB,"clicked",G_CALLBACK(click),NULL);
  g_signal_connect(bD,"clicked",G_CALLBACK(click),NULL);

  // top-down layout

  win=gtk_application_window_new(a); assert(win);
  gtk_window_set_title(GTK_WINDOW(win),"floating");
  // gtk_container_set_border_width(GTK_CONTAINER(win),20);

  // https://stackoverflow.com/questions/34387757/how-do-i-intercept-a-gtk-window-close-button-click
  g_signal_connect(win,"delete-event",G_CALLBACK(closewin),NULL);
  g_signal_connect(win,"key-press-event",G_CALLBACK(key_press_event),NULL);

  GtkWidget *g=gtk_grid_new(); assert(g);
  gtk_container_add(GTK_CONTAINER(win),g);

  // +------+
  // |[-][+]|
  // +------+
  // gtk_grid_attach(GTK_GRID(g),bB,/*c*/1,/*r*/0,/*w*/1,h1);
  // gtk_grid_attach(GTK_GRID(g),bD,/*c*/0,/*r*/0,/*w*/1,/*h*/1);

  // +---+
  // |[+]|
  // |[-]|
  // +---+
  gtk_grid_attach(GTK_GRID(g),bB,/*c*/0,/*r*/0,/*w*/1,/*h*/1);
  gtk_grid_attach(GTK_GRID(g),bD,/*c*/0,/*r*/1,/*w*/1,/*h*/1);
  button_label_align_fill2start(GTK_BUTTON(bB));
  button_label_align_fill2start(GTK_BUTTON(bD));

  gtk_widget_show_all(win);

}

int main(){

  backlight_init();
  backlight_upd();

  g_set_prgname("floating");
  GtkApplication *a=gtk_application_new("com.appid",G_APPLICATION_FLAGS_NONE);
  g_signal_connect(a,"activate",G_CALLBACK(activate), NULL);

  const int r=g_application_run(G_APPLICATION(a),0,NULL);

  g_object_unref(a);
  return r;

}
