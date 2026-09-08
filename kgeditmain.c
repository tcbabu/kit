#include <stdio.h>
#include <string.h>
void *Runkgedit(void *,void *);
int main(int argc,char *argv[]) {
// kgStartX(NULL) //can be used;
  char *pt;
  char File[300];
  strcpy(File, "");
  pt=  File;
  if(argc>1) {
     pt=argv[1];
  }
  Runkgedit(NULL,pt);
//  kgCloseX(); //canbe used
  return 1;
}
