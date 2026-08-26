#include <stdio.h>
void *RunGetFontString(void *,void *);
int main(void) {
// kgStartX(NULL) //can be used;
char *cpt,fname[330];
  cpt =(char *)RunGetFontString(NULL,fname);
  printf ("Fname: %s %s\n",fname,cpt);
//  kgCloseX(); //canbe used
  return 1;
}
