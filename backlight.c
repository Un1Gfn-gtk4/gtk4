#include <assert.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

#include "./backlight.h"

#define BACKLIGHT_MAX    "/sys/class/backlight/intel_backlight/max_brightness"
#define BACKLIGHT_ACTUAL "/sys/class/backlight/intel_backlight/actual_brightness"
#define BACKLIGHT_CUR    "/sys/class/backlight/intel_backlight/brightness"

static int orig=0;

static int prev=0;
static int cur=0;

static int min=0;
static int max=0;

static inline int file2int(const char *const path){
  FILE *fr=fopen(path, "r"); assert(fr);
  int r=0;
  fscanf(fr, "%d", &r);
  fclose(fr); fr=NULL;
  return r;
}

static inline void cur2file(const char *const path){
  FILE *fw=fopen(path, "w"); assert(fw);
  assert(2<=fprintf(fw, "%d\n", cur));
  fclose(fw); fw=NULL;
}

static inline void show(){
  printf("(%3d) %3d (%3d)\n",min,cur,max);
}

void backlight_init(){
  orig=cur=file2int(BACKLIGHT_ACTUAL);
  max=file2int(BACKLIGHT_MAX);
  show();
}

void backlight_revert(){
  cur=orig;
  cur2file(BACKLIGHT_CUR);
  printf("%*d\n", 1+3+1+1+3, cur);
}

// unused param for g_signal_connect_swapped()
// https://docs.gtk.org/gobject/func.signal_connect_swapped.html
void backlight_dim(__attribute__((unused)) void *p){
  // puts("dim()");
  max=cur;
}

// unused param for g_signal_connect_swapped()
// https://docs.gtk.org/gobject/func.signal_connect_swapped.html
void backlight_brighten(__attribute__((unused)) void *p){
  // puts("brighten()");
  min=cur;
}

// false if narrowed down
// true  if still converging
bool backlight_upd(){
  prev=cur;
  cur=(min+max)/2;
  show();
  if(1>=abs(prev-cur))
    return false;
  cur2file(BACKLIGHT_CUR);
  return true;
}
