#include <stdio.h>
void *Runkgedit(void *,void *);
int main(int argc,char *argv[]) {
// kgStartX(NULL) //can be used;
  char File[300];
  char *pt=argv[1];
  if(pt== NULL) pt=File;
  File[0]='\0';
  Runkgedit(NULL,pt);
//  kgCloseX(); //canbe used
  return 1;
}
