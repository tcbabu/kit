#include <stdio.h>
#include <string.h>
#include <kulina.h>
void *RunMsg(void *,void *);
int main(int argc,char *argv[]) {
// kgStartX(NULL) //can be used;
  char **hmsg;
  if(argc == 1) return 0;
  Dlink *L= Dreadfile(argv[1]);
  int count = Dcount(L)+1;
  hmsg = (char **)malloc(sizeof(char *)*count);
  char buf[200];
  char *pt;
  int i=0;
  Resetlink(L);
  FILE *fp=fopen("msgcode","w");
  fprintf(fp,"  char *hmsg[]=  {\n");
  while ( (pt=(char *)Getrecord(L))!= NULL){
      hmsg[i++]=pt;
      strcpy(buf,pt);
      buf[strlen(buf)-1]='\0';
      fprintf(fp, "    \"%-s\",\n",buf);
  }
  fprintf(fp,"   NULL};\n");
  hmsg[i]=NULL;
  RunMsg(NULL,hmsg);
  Dempty(L);
  free(hmsg);
//  kgCloseX(); //canbe used
  return 1;
}
