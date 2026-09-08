#include <kulina.h>
#include "WmsgCallbacks.h"
#include "GclrWmsg.c"
int WmsgGroup( DIALOG *D,void **v,void *pt) {
  int GrpId=0,oitems=0,i,j;
  DIA *d=NULL,*dtmp;
  DIS s0 = { 
    's',
    5,36,  
    605,282,   
    11,  
    NULL,
    NULL,
    NULL ,
    NULL,NULL, /* *args, Callback*/
    20,6,22,1,1,1,0
//     line width,offset (not used),scroll width,highlight item(not used)
//     border on/off,bkgr on/off,hide on/off
//     uses Gclr items: msg_fill,msg_char,msg_bodr,scroll_fill,scroll_dim,scroll_vbright)
  };
  strcpy(s0.Wid,(char *)"Msgscroll1");
  s0.item = -1;
  DIM m1 = { 
    'm',
    10,8,  
    600,32,  
    0,0  
  };
  strncpy(m1.msg,(char *)"",499);
  strcpy(m1.Wid,(char *)"Message1");
  m1.item = -1;
  BUT_STR  *butn2=NULL; 
  butn2= (BUT_STR *)malloc(sizeof(BUT_STR)*3);
  butn2[0].sw=1;
  strcpy(butn2[0].title,(char *)"!c03!z54Cancel");
  butn2[0].xpmn=NULL;
  butn2[0].xpmp=NULL;
  butn2[0].xpmh=NULL;
  butn2[0].bkgr=-216226216;
  butn2[0].butncode=31;
  butn2[1].sw=1;
  strcpy(butn2[1].title,(char *)"!c38!z54Write");
  butn2[1].xpmn=NULL;
  butn2[1].xpmp=NULL;
  butn2[1].xpmh=NULL;
  butn2[1].bkgr=-216226216;
  butn2[1].butncode=-2302945;
  butn2[2].sw=1;
  strcpy(butn2[2].title,(char *)"!c01!z54Append");
  butn2[2].xpmn=NULL;
  butn2[2].xpmp=NULL;
  butn2[2].xpmh=NULL;
  butn2[2].bkgr=-216226216;
  butn2[2].butncode=-2302851;
  DIL h2 = { 
    'h',
    149,288,  
    470,323,
    10,0,  
    96, 
    26, 
    3,1, 
    7,0.500000,0,1,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn2, 
    WmsgSplbutn1callback ,  /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(h2.Wid,(char *)"Splbutn1");
  h2.item = -1;
  BUT_STR  *butn3=NULL; 
  butn3= (BUT_STR *)malloc(sizeof(BUT_STR)*2);
  butn3[0].sw=1;
  strcpy(butn3[0].title,(char *)"!c03!z54Cancel");
  butn3[0].xpmn=NULL;
  butn3[0].xpmp=NULL;
  butn3[0].xpmh=NULL;
  butn3[0].bkgr=-216226216;
  butn3[0].butncode=31;
  butn3[1].sw=1;
  strcpy(butn3[1].title,(char *)"!c38!z54Okay");
  butn3[1].xpmn=NULL;
  butn3[1].xpmp=NULL;
  butn3[1].xpmh=NULL;
  butn3[1].bkgr=-216226216;
  butn3[1].butncode=31;
  DIL h3 = { 
    'h',
    197,288,  
    417,322,
    10,0,  
    96, 
    26, 
    2,1, 
    7,0.500000,0,1,0,1,/* button type and roundinfg factor(0-0.5),bordr,hide ,nodrawbkgr*/ 
    butn3, 
    WmsgSplbutn2callback ,  /* *args, Callback */
    NULL  /* any args */
  };
  strcpy(h3.Wid,(char *)"Splbutn2");
  h3.item = -1;
  dtmp = D->d;
  i=0;
  if(dtmp!= NULL) while(dtmp[i].t!=NULL)i++;
  dtmp = (DIA *)realloc(dtmp,sizeof(DIA )*(i+5));
  d =dtmp+i; 
  d[4].t=NULL;
  d[0].t = (DIT *)malloc(sizeof(DIS));
  *d[0].s = s0;
  d[0].s->item = -1;
  WmsgMsgscroll1init(d[0].s,pt) ;
  d[1].t = (DIT *)malloc(sizeof(DIM));
  *d[1].m = m1;
  d[1].m->item = -1;
  d[2].t = (DIT *)malloc(sizeof(DIL));
  *d[2].h = h2;
  d[2].h->item = -1;
  WmsgSplbutn1init(d[2].h,pt) ;
  d[3].t = (DIT *)malloc(sizeof(DIL));
  *d[3].h = h3;
  d[3].h->item = -1;
  WmsgSplbutn2init(d[3].h,pt) ;
  d[4].t = NULL;
  GrpId=kgOpenGrp(D);
  D->d = dtmp;
  j=0;
  while(d[j].t!=NULL){ kgAddtoGrp(D,GrpId,(void *)(d[j].t));j++;}
  return GrpId;
} 

/* One can also use the following code to add Widgets to an existing Dialog */

int MakeWmsgGroup(DIALOG *D,void *arg) {
   int GrpId;
   WIDGETGRP *Gpt;
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt=NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   GrpId = WmsgGroup(D,v,pt);
   Gpt = kgGetWidgetGrp(D,GrpId);
   Gpt->arg= v; // kulina will double free this; you may modify
   WmsgSetup(D,Gpt->arg);
   return GrpId;
}

int Wmsg( void *parent,void **v,void *pt) {
  int ret=1,GrpId,k;
  DIALOG D;
  DIA *d=NULL;
  D.VerId=-1685927296;
  kgInitUi(&D);
  D.d=NULL;
#if 1
  GrpId = WmsgGroup(&D,v,pt);
#else 
  GrpId = MakeWmsgGroup(&D,pt); // can try this also
#endif 
  d = D.d;
  D.d = d;
  D.bkup = 1; /* set to 1 for backup */
  D.bor_type = 4;
  D.df = 0;
  D.tw = 4;
  D.bw = 4;
  D.lw = 4;
  D.rw = 4;
  D.xo = 697;   /* Position of Dialog */ 
  D.yo = 175;
  D.xl = 612;    /*  Length of Dialog */
  D.yl = 329;    /*  Width  of Dialog */
  D.Initfun = Wmsginit;    /*   init fuction for Dialog */
  D.Cleanupfun = Wmsgcleanup;    /*   cleanup fuction for Dialog */
  D.kbattn = 0;    /*  1 for drawing keyborad attention */
  D.butattn = 0;    /*  1 for drawing button attention */
  D.fullscreen = 0;    /*  1 for for fullscreen mode */
  D.NoTabProcess = 0;    /*  1 for disabling Tab use */
  D.Deco = 1;    /*  1 for Window Decorration */
  D.transparency = 0.000000;    /*  float 1.0 for full transparency */
  D.Newwin = 1;    /*  1 for new window not yet implemented */
  D.DrawBkgr = 1;    /*  1 for drawing background */
  D.Bkpixmap = NULL;    /*  background image */
  D.Sticky = 0;    /*  1 for stickyness */
  D.Resize = 0;    /*  1 for Resize option */
  D.MinWidth = 100;    /*   for Resize option */
  D.MinHeight = 100;    /*   for Resize option */
#if 1 
  D.Callback = WmsgCallBack;    /*  default Callback  */
#else 
  D.Callback = NULL;    
#endif
  D.ResizeCallback = WmsgResizeCallBack;  /*  Resize callback */
#if 0 
  D.WaitCallback = NULL;  /*  Wait callback */
#else 
  D.WaitCallback = WmsgWaitCallBack;  /*  Wait callback */
#endif
  D.Fixpos = 1;    /*  1 for Fixing Position */
  D.NoTaskBar = 0;    /*  1 for not showing in task bar*/
  D.NoWinMngr = 0;    /*  1 for no Window Manager*/
  D.StackPos = 0;    /* -1,0,1 for for Stack Position -1:below 0:normal 1:above*/
  D.Shapexpm = NULL;    /*  PNG/jpeg file for window shape;Black color will not be drawn */
  D.parent = parent;    /*  1 for not showing in task bar*/
  D.pt = pt;    /*  any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 3.0");    /*  Dialog name you may change */
  if(D.fullscreen!=1) {    /*  if not fullscreen mode */
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
  }
  else {    // for fullscreen
     int xres,yres; 
     kgDisplaySize(&xres,&yres); 
     D.xo=D.yo=0; D.xl = xres; D.yl=yres;
//     D.StackPos = 1; // you may need it
  }    /*  end of fullscreen mode */
  ModifyWmsgGc(&D);    /*  set colors for gui if do not like default*/
  ModifyWmsg(&D,GrpId);    /*  add extras to  gui*/
  ret= kgUi(&D);
  kgCleanUi(&D);
  return ret;
}
void *RunWmsg(void *parent ,void *args) {
/*************************************************


*************************************************/
   void **v=NULL;
   void *pt[2]={NULL,NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
   pt[0]=args;
   Wmsg(parent,v,(void *)pt );
   return pt[1];
}
