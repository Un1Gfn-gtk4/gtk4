#include <assert.h>
#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#include "./backlight.h"

// static WINDOW *w=NULL;
// static void tui_init_ncurses(){
//   assert(NULL!=(w=initscr()));
//   assert(OK==cbreak());
//   assert(OK==noecho());
//   assert(OK==idlok(w,TRUE)); // use hardware insert/delete line feature
//   assert(OK==scrollok(w,TRUE)); // on newline action on the bottom line, scrolled window up one line
//   assert(OK==wrefresh(w));
// }
// static void tui_end_ncurses(){
//   assert(OK==delwin(w));w=NULL;
//   assert(OK==endwin());
//   assert(TRUE==isendwin());
// }

static struct termios t={0};

static void tui_init(){
  assert(0==tcgetattr(STDIN_FILENO,&t));
  assert(t.c_lflag&ECHO);
  assert(t.c_lflag&ICANON);
  t.c_lflag &= ~((tcflag_t)ECHO);
  t.c_lflag &= ~((tcflag_t)ICANON);
  assert(0==tcsetattr(STDIN_FILENO,TCSAFLUSH,&t));
}

static void tui_end(){
  assert(!(t.c_lflag&ECHO));
  assert(!(t.c_lflag&ICANON));
  t.c_lflag |= ECHO;
  t.c_lflag |= ICANON;
  assert(0==tcsetattr(STDIN_FILENO,TCSAFLUSH,&t));
  puts("bye");
}

static void loop(){
  for(;;){
    const int k=getchar();
    switch(k){
      case '-':
      case '_':
        backlight_dim();
        if(backlight_upd()) return;
        break;
      case '=':
      case '+':
        backlight_brighten();
        if(!backlight_upd()) return;
        break;
      case 'q':
        return;
    }
  }
}

int main(){

  backlight_init();
  backlight_upd();

  tui_init();
  atexit(tui_end);

  loop();

  return 0;

}

