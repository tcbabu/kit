#include <stdio.h>
#include <kulina.h>
void *RunWmsg(void *,void *);
int kitWriteWarn(void *Tmp,Dlink *Data,char *Msg);
int main(void) {
// kgStartX(NULL) //can be used;
//  RunWmsg(NULL,NULL);
//  kgCloseX(); //canbe used
  int ret=kitWriteWarn(NULL,Dreadfile("Wmsg.c"),"Write following lines");
  printf("Return = %d\n",ret);
  return 1;
}
