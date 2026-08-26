#include <kulina.h>
#include "GetFontStringCallbacks.h"

static void *Args=NULL,*Rets=NULL;

static DIAINTR *It = NULL;


static MODINTERFACE ModFuns[] = { 
    (MODINTERFACE) NULL 
};
static Dlink *ModuleList=NULL;

 /* Callback for  GFselect   */ 
static char ** fonts;
static int WriteMessage(void *Tmp) {
   int item;
   DIX *X = (DIX *)kgGetNamedWidget(Tmp,(char *)"GFselect");
   DII *I = (DII *)kgGetNamedWidget(Tmp,(char *)"GFibox");
   item  = kgGetSelection(X);  
   char buff[200];
   char *Msg [ ] = {"\"Our lives begin to end the day we become " , \
           " silent about things that matter\"" , NULL};
  sprintf(buff,"!f09%d %-s",item-1,fonts[item-1]);
  kgWrite(I,buff);
  sprintf(buff,"!f%2.2d%-s",item-1,Msg[0]);
  kgWrite(I,buff);
  sprintf(buff,"!f%2.2d%-s",item-1,Msg[1]);
  kgWrite(I,buff);
  return 1;
}
int GetFontStringGFselectcallback(int item,int i,void *Tmp) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIX *X; 
  int ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  X = (DIX *)kgGetWidget(Tmp,i);
#if 0
  char buff[200];
   char *Msg [ ] = {"\"Our lives begin to end the day we become " , \
           " silent about things that matter\"" , NULL};
  printf("%s\n",fonts[item-1]);
  DII *I=(DII *)kgGetNamedWidget(Tmp,(char *)"GFibox");
  sprintf(buff,"%d %-s",item-1,fonts[item-1]);
  kgWrite(I,buff);
  sprintf(buff,"!f%2.2d%-s",item-1,Msg[0]);
  kgWrite(I,buff);
  sprintf(buff,"!f%2.2d%-s",item-1,Msg[1]);
  kgWrite(I,buff);
#endif
  WriteMessage(Tmp);
  switch(item) {
    case 1: 
      break;
  }
  return ret;
}
static int UpdateBrowser(void *Tmp) {
  int i=0;
  char **Fnames,Fontfull[300],Font[200],dummy1[10],dummy2[10];
  Dlink *L=Dopen();
  char *cpt,**items;
  ThumbNail **th;
  char *fpt;
  DIX *X = (DIX *)kgGetNamedWidget(Tmp,(char *)"GFselect");
  th = (ThumbNail **)kgGetList(X);
  kgFreeThumbNails(th);
  char **List = (char **)kgGetFontList();
  while(List[i]!= NULL) {
     sscanf(List[i],"%s %s %s",dummy1,dummy2,Fontfull);
     kgExtractBaseName(Fontfull,Font);
     fpt = strstr(Fontfull,Font);
//     printf("%s\n",Font);
     cpt = (char *)malloc(strlen(fpt)+1);
     strcpy(cpt,fpt);
     Dadd(L,cpt);
     i++;
  }
  kgFreeDouble((void **)List);
  fonts = (char **)Dlinktoarray(L);
  Dfree(L);
  th = (ThumbNail **)kgStringToThumbNails(fonts);
  kgSetList(X,(void **)th);
  kgUpdateWidget(X);
  kgUpdateOn(Tmp);   
  return i;
}
void  GetFontStringGFselectinit (DIX *X,void *ptmp) {
 // One may setup browser list here by setting X->list
 // if it need to be freed set it as X->pt also
 void **pt=(void **)ptmp; //pt[0] is arg 
  char **List = (char **)kgGetFontList();
  int i=0;
  char **Fnames,Fontfull[300],Font[200],dummy1[10],dummy2[10];
  Dlink *L=Dopen();
  char *cpt,**items;
  ThumbNail **th;
  char *fpt;

  while(List[i]!= NULL) {
     sscanf(List[i],"%s %s %s",dummy1,dummy2,Fontfull);
     kgExtractBaseName(Fontfull,Font);
     fpt = strstr(Fontfull,Font);
//     printf("%s\n",Font);
     cpt = (char *)malloc(strlen(fpt)+1);
     strcpy(cpt,fpt);
     Dadd(L,cpt);
     i++;
  }
  kgFreeDouble((void **)List);
  fonts = (char **)Dlinktoarray(L);
#if 0
  i =0;
  items = (char **)malloc(sizeof(char *)*(Dcount(L)+1));
  while(fonts[i]!= NULL) {
    sprintf(Fontfull,"%d %s  !f%2.2d%-s",i,fonts[i],i,fonts[i]);
    items[i]= (char *)malloc(strlen(Fontfull)+1);
    strcpy(items[i],Fontfull);
    printf("%s\n",items[i]);
    i++;
  }
  items[i]=NULL;
  Dfree(L);
  th = (ThumbNail **)kgStringToThumbNails(items);
  kgSetList(X,(void **)th);
  kgFreeDouble((void **)items);
#else
  Dfree(L);
  th = (ThumbNail **)kgStringToThumbNails(fonts);
  kgSetList(X,(void **)th);
#endif
}

 /* Callback for  GFadd   */ 

int GetFontStringGFaddcallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  char flname[300];
  strcpy(flname,"/usr/share/fonts/");
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  DIX *X = (DIX *)kgGetNamedWidget(Tmp,(char *)"GFselect");
  if ( kgFolderBrowser (Tmp , 100 , 100 , flname , ( char * ) "*.ttf *.otf" ) ) {
//  if (kgGetFreeTypeFont(Tmp,flname) != NULL) {
          kgAddFont(flname);
          ret =UpdateBrowser ( Tmp ) ;
          kgSetSelection(X,ret);
          kgUpdateWidget(X);
          kgUpdateOn(Tmp);
          WriteMessage(Tmp);
  }
  switch(butno) {
    case 1: //  Add Font 
      break;
  }
  return ret;
}
void  GetFontStringGFaddinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}

 /* Callback for  GFdone   */ 

int GetFontStringGFdonecallback( int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIL *B; 
  int n,ret=1; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  char fname[200];
  char *ot;
  DIX *X = (DIX *)kgGetNamedWidget(Tmp,(char *)"GFselect");
  strcpy(fname,kgGetSelectedString(X));
  if(pt[0]== NULL) ot = (char *)malloc(strlen(fname)+1);
  else ot = (char *)pt[0];
  strcpy(ot,fname);
  pt[1]= (void *)ot;
  D = (DIALOG *)Tmp;
  B = (DIL *) kgGetWidget(Tmp,i);
  n = B->nx;
  switch(butno) {
    case 1: //  !c38Done 
      break;
  }
  return ret;
}
void  GetFontStringGFdoneinit (DIL *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int GetFontStringSetup(void *Tmp,void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  /* you add any initialisation here */
  /* useful for setting is used as MakeGroup */
  return 1;
}
 
void * GetFontStringCleanDia(void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  
/* you add any cleaning  here */

  return NULL;
}
 
 
void *  GetFontStringAction(void *Tmp,void *Args) {
  return NULL;
} 
 
 
int   GetFontStringOn(void *itmp) {
  DIAINTR * Dt = (DIAINTR *) itmp;
  if(Dt == NULL ) Dt = (DIAINTR *)It;
  if(Dt != NULL) {
    if(Dt->Dtmp != NULL)kgSetGrpVisibility(Dt->Dtmp,Dt->GrpId,1);
    else return 0;
    return 1;
  } 
  return 0;
} 
 
int   GetFontStringOff(void *itmp) {
  DIAINTR * Dt = (DIAINTR *) itmp;
  if(Dt == NULL ) Dt = (DIAINTR *)It;
  if(Dt != NULL) {
    if(Dt->Dtmp != NULL)kgSetGrpVisibility(Dt->Dtmp,Dt->GrpId,0);
    else return 0;
    return 1;
  } 
  return 0;
} 
 
static char *GetPointer(char *str) { 
  char *pt; 
  pt = (char *)malloc(strlen(str)+1); 
  strcpy(pt,str); 
  return pt; 
} 
 
 
void * GetFontStringInterface(void *args,void *rets) {
  /*********************************** 
   ***********************************/ 
  DIAINTR *it= (DIAINTR *)malloc(sizeof(DIAINTR));
  it->GrpId=0;
  // filled by MakeGroup  it->xsh=0;
  it->ysh=0;
  it->RunDia = RunGetFontString;
  it->MakeGroup = MakeGetFontStringGroup;
  it->Title = GetPointer((char *)"GetFontString");
  it->Help = GetPointer( (char *)"No help yet, request");
  it->Action = GetFontStringAction;
  it->Settings = GetFontStringSetup;
  it->Cleanup  = GetFontStringCleanDia;
  if(args != NULL) Args=args;
  if(rets != NULL) Rets=rets;
  it->args = Args;
  it->rets = Rets;
  it->SwitchOn = GetFontStringOn;
  it->SwitchOff = GetFontStringOff;
  it->Dtmp = NULL; // fiiled by MakeGroup 
  It = it;
  return it;
}
 
 
int GetFontStringGFotfcallback(int butno,int i,void *Tmp) {
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
  char flname[300];
  strcpy(flname,"/usr/share/fonts/");
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  if ( kgFolderBrowser (NULL , 100 , 100 , flname , ( char * ) "*.otf" ) ) {
//  if (kgGetFreeTypeFont(Tmp,flname) != NULL) {
          kgAddFont(flname);
          UpdateBrowser ( Tmp ) ;
  }
  switch(butno) {
    case 1: //  Add otf font 
      break;
  }
  return ret;
}
void  GetFontStringGFotfinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int GetFontStringinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs, given by caller */
  WriteMessage((void*)(Tmp));
  return ret;
}
int GetFontStringcleanup(void *Tmp) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 1;
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[1] is outputs, if any  to be given to caller */
 /* pt[0] is inputs, given by caller */
  return ret;
}
int ModifyGetFontString(void *Tmp,int GrpId) {
  DIALOG *D;
  D = (DIALOG *)Tmp;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
 /* pt[0] is inputs given by caller */
  DIA *d;
  int i,n;
  kgCheckParentPosition(Tmp);
  d = D->d;

  if( ModuleList == NULL) ModuleList = kgGetModuleList((void **)ModFuns);
  i=0;
  void *args=NULL;
  DIAINTR *Dt;
  Resetlink(ModuleList);
  while ( (Dt=(DIAINTR *)Getrecord(ModuleList)) != NULL) {
    Dt->GrpId = Dt->MakeGroup(Tmp,NULL);
    kgShiftGrp(Tmp,Dt->GrpId,Dt->xsh,Dt->ysh);
    Dt->Settings(Tmp,args);
    i++;
  };

  i=0;while(d[i].t!= NULL) {;
     i++;
  };
  n=1;
//  strcpy(D->name,"Kulina Designer ver 3.0");    /*  Dialog name you may change */
#if 0
  if(D->fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D->xo=D->yo=0; D->xl = xres-10; D->yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D->xo=D->yo=0; D->xl = xres; D->yl=yres;
//     D->StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
#endif
  return GrpId;
}

int GetFontStringCallBack(void *Tmp,void *tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    tmp :  Pointer to KBEVENT  
   ***********************************/ 
  int ret = 0;
  DIALOG *D;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  KBEVENT *kbe;
  D = (DIALOG *)Tmp;
  kbe = (KBEVENT *)tmp;
  if(kbe->event ==1) {
    if(kbe->button ==1) {
    }
  }
  return ret;
}
int GetFontStringResizeCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  int ret = 0;
  int xres,yres,dx,dy;
  DIALOG *D;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  kgGetWindowSize(D,&xres,&yres);
  dx = xres - D->xl;
  dy = yres - D->yl;
  /* extra code */
  D->xl= xres;
  D->yl= yres;
  kgRedrawDialog(D);
  return ret;
}
int GetFontStringWaitCallBack(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
  int ret = 0;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  return ret;
}
void *RunGetFontString(void *,void *);
void *kgGetFontString(void *Tmp,void *name) {

/* if name is not NULL, fontname is copied to fname.
   Also returns fontname; if name is NULL new point is created.
   Otherwise fname is used.
*/
  return RunGetFontString(Tmp,name);
}
