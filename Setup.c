#include <kulina.h>
#include "SetupCallbacks.h"
#include "GclrSetup.c"
  int SetupGroup ( DIALOG *D , void **v , void *pt ) {
      int GrpId = 0 , oitems = 0 , i , j;
      DIA *d = NULL , *dtmp;
      BUT_STR *butn0 = NULL;
      butn0 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn0 [ 0 ] .sw = 1;
      strcpy ( butn0 [ 0 ] .title , ( char * ) "!w23Browse" ) ;
      butn0 [ 0 ] .xpmn = NULL;
      butn0 [ 0 ] .xpmp = NULL;
      butn0 [ 0 ] .xpmh = NULL;
      butn0 [ 0 ] .bkgr = -1;
      butn0 [ 0 ] .butncode = 31;
      DIN b0 = {
          'n' , 313 , 45 , 392 , 80 , 2 , 2 , 72 , 22 , 1 , 1 , 5 , 0.500000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn0 , Setupbutton1callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b0.Wid , ( char * ) "Browse" ) ;
      b0.item = -1;
      T_ELMT *e1 ;
      e1 = ( T_ELMT * ) malloc ( sizeof ( T_ELMT ) *1 ) ;
      e1 [ 0 ] .fmt = ( char * ) malloc ( 9 ) ;
      strcpy ( e1 [ 0 ] .fmt , ( char * ) "Font%24s" ) ;
      e1 [ 0 ] .v = ( void * ) v [ 0 ] ;
      e1 [ 0 ] .sw = 1;
      e1 [ 0 ] .noecho = 0;
      e1 [ 0 ] .img = NULL;
      DIT t1 = {
          't' , 7 , 45 , 312 , 79 , 20 , 1 , 1 , e1 , 1 , 1 , NULL , Setuptextbox1callback , \
               0 , 1 , 18 , 9 /* args , Call back */
      };
      strcpy ( t1.Wid , ( char * ) "Font" ) ;
      t1.pt = NULL;
      t1.type = 1;
      t1.item = -1;
      char **menu2 ;
      menu2 = ( char ** ) malloc ( sizeof ( char * ) *10 ) ;
      menu2 [ 9 ] = NULL;
      menu2 [ 0 ] = ( char * ) malloc ( 2 ) ;
      strcpy ( menu2 [ 0 ] , ( char * ) "6" ) ;
      menu2 [ 1 ] = ( char * ) malloc ( 2 ) ;
      strcpy ( menu2 [ 1 ] , ( char * ) "7" ) ;
      menu2 [ 2 ] = ( char * ) malloc ( 2 ) ;
      strcpy ( menu2 [ 2 ] , ( char * ) "8" ) ;
      menu2 [ 3 ] = ( char * ) malloc ( 2 ) ;
      strcpy ( menu2 [ 3 ] , ( char * ) "9" ) ;
      menu2 [ 4 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu2 [ 4 ] , ( char * ) "10" ) ;
      menu2 [ 5 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu2 [ 5 ] , ( char * ) "11" ) ;
      menu2 [ 6 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu2 [ 6 ] , ( char * ) "12" ) ;
      menu2 [ 7 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu2 [ 7 ] , ( char * ) "13" ) ;
      menu2 [ 8 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu2 [ 8 ] , ( char * ) "14" ) ;
      char *prompt2 ;
      prompt2 = ( char * ) malloc ( 10 ) ;
      strcpy ( prompt2 , ( char * ) "FontSize " ) ;
      DIW w2 = {
          'w' , 51 , 92 , 185 , 121 , 4 , ( int * ) v [ 1 ] , prompt2 , menu2 , \
               NULL , Setupbrowser1callback , /* *args , callback */
      0 };
      strcpy ( w2.Wid , ( char * ) "FontSize" ) ;
      w2.item = -1;
      BUT_STR *butn3 = NULL;
      butn3 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn3 [ 0 ] .sw = 1;
      strcpy ( butn3 [ 0 ] .title , ( char * ) "" ) ;
      butn3 [ 0 ] .xpmn = NULL;
      butn3 [ 0 ] .xpmp = NULL;
      butn3 [ 0 ] .xpmh = NULL;
      butn3 [ 0 ] .bkgr = -235255250;
      butn3 [ 0 ] .butncode = 31;
      DIN b3 = {
          'n' , 86 , 136 , 136 , 186 , 2 , 2 , 42 , 42 , 1 , 1 , 1 , 0.150000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn3 , Setupbutton2callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b3.Wid , ( char * ) "FontClr" ) ;
      b3.item = -1;
      DIM m4 = {
      'm' , 49 , 187 , 160 , 211 , 1 , 0 };
      strncpy ( m4.msg , ( char * ) "Font Color" , 499 ) ;
      strcpy ( m4.Wid , ( char * ) "SetupWidget5" ) ;
      m4.item = -1;
      DIM m5 = {
      'm' , 235 , 187 , 335 , 211 , 1 , 0 };
      strncpy ( m5.msg , ( char * ) "Number Color" , 499 ) ;
      strcpy ( m5.Wid , ( char * ) "SetupWidget6" ) ;
      m5.item = -1;
      BUT_STR *butn6 = NULL;
      butn6 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn6 [ 0 ] .sw = 1;
      strcpy ( butn6 [ 0 ] .title , ( char * ) "" ) ;
      butn6 [ 0 ] .xpmn = NULL;
      butn6 [ 0 ] .xpmp = NULL;
      butn6 [ 0 ] .xpmh = NULL;
      butn6 [ 0 ] .bkgr = -255255;
      butn6 [ 0 ] .butncode = 31;
      DIN b6 = {
          'n' , 262 , 136 , 312 , 185 , 2 , 2 , 42 , 42 , 1 , 1 , 1 , 0.150000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn6 , Setupbutton3callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b6.Wid , ( char * ) "NumClr" ) ;
      b6.item = -1;
      char **menu7 ;
      menu7 = ( char ** ) malloc ( sizeof ( char * ) *11 ) ;
      menu7 [ 10 ] = NULL;
      menu7 [ 0 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 0 ] , ( char * ) "14" ) ;
      menu7 [ 1 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 1 ] , ( char * ) "16" ) ;
      menu7 [ 2 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 2 ] , ( char * ) "18" ) ;
      menu7 [ 3 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 3 ] , ( char * ) "20" ) ;
      menu7 [ 4 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 4 ] , ( char * ) "22" ) ;
      menu7 [ 5 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 5 ] , ( char * ) "24" ) ;
      menu7 [ 6 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 6 ] , ( char * ) "26" ) ;
      menu7 [ 7 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 7 ] , ( char * ) "28" ) ;
      menu7 [ 8 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 8 ] , ( char * ) "30" ) ;
      menu7 [ 9 ] = ( char * ) malloc ( 3 ) ;
      strcpy ( menu7 [ 9 ] , ( char * ) "32" ) ;
      char *prompt7 ;
      prompt7 = ( char * ) malloc ( 11 ) ;
      strcpy ( prompt7 , ( char * ) "LineWidth " ) ;
      DIW w7 = {
          'w' , 187 , 92 , 345 , 121 , 4 , ( int * ) v [ 2 ] , prompt7 , menu7 , \
               NULL , Setupbrowser2callback , /* *args , callback */
      0 };
      strcpy ( w7.Wid , ( char * ) "Width" ) ;
      w7.item = -1;
      DIM m8 = {
      'm' , 46 , 278 , 179 , 302 , 1 , 0 };
      strncpy ( m8.msg , ( char * ) "Background color" , 499 ) ;
      strcpy ( m8.Wid , ( char * ) "SetupWidget9" ) ;
      m8.item = -1;
      BUT_STR *butn9 = NULL;
      butn9 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn9 [ 0 ] .sw = 1;
      strcpy ( butn9 [ 0 ] .title , ( char * ) "" ) ;
      butn9 [ 0 ] .xpmn = NULL;
      butn9 [ 0 ] .xpmp = NULL;
      butn9 [ 0 ] .xpmh = NULL;
      butn9 [ 0 ] .bkgr = -49054049;
      butn9 [ 0 ] .butncode = 31;
      DIN b9 = {
          'n' , 84 , 226 , 136 , 278 , 2 , 2 , 42 , 42 , 1 , 1 , 1 , 0.150000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn9 , Setupbutton4callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b9.Wid , ( char * ) "BkgrClr" ) ;
      b9.item = -1;
      DIM m10 = {
      'm' , 234 , 278 , 334 , 302 , 1 , 0 };
      strncpy ( m10.msg , ( char * ) "Line Color" , 499 ) ;
      strcpy ( m10.Wid , ( char * ) "SetupWidget11" ) ;
      m10.item = -1;
      BUT_STR *butn11 = NULL;
      butn11 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn11 [ 0 ] .sw = 1;
      strcpy ( butn11 [ 0 ] .title , ( char * ) "" ) ;
      butn11 [ 0 ] .xpmn = NULL;
      butn11 [ 0 ] .xpmp = NULL;
      butn11 [ 0 ] .xpmh = NULL;
      butn11 [ 0 ] .bkgr = -142142142;
      butn11 [ 0 ] .butncode = 31;
      DIN b11 = {
          'n' , 262 , 226 , 314 , 278 , 2 , 2 , 42 , 42 , 1 , 1 , 1 , 0.150000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn11 , Setupbutton5callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b11.Wid , ( char * ) "LineClr" ) ;
      b11.item = -1;
      BUT_STR *butn12 = NULL;
      butn12 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *3 ) ;
      butn12 [ 0 ] .sw = 1;
      strcpy ( butn12 [ 0 ] .title , ( char * ) "!c12Cancel" ) ;
      butn12 [ 0 ] .xpmn = NULL;
      butn12 [ 0 ] .xpmp = NULL;
      butn12 [ 0 ] .xpmh = NULL;
      butn12 [ 0 ] .bkgr = -235255250;
      butn12 [ 0 ] .butncode = 126;
      butn12 [ 1 ] .sw = 1;
      strcpy ( butn12 [ 1 ] .title , ( char * ) "!c01Default" ) ;
      butn12 [ 1 ] .xpmn = NULL;
      butn12 [ 1 ] .xpmp = NULL;
      butn12 [ 1 ] .xpmh = NULL;
      butn12 [ 1 ] .bkgr = -235255250;
      butn12 [ 1 ] .butncode = -1456151426;
      butn12 [ 2 ] .sw = 1;
      strcpy ( butn12 [ 2 ] .title , ( char * ) "!c38Okay" ) ;
      butn12 [ 2 ] .xpmn = NULL;
      butn12 [ 2 ] .xpmp = NULL;
      butn12 [ 2 ] .xpmh = NULL;
      butn12 [ 2 ] .bkgr = -235255250;
      butn12 [ 2 ] .butncode = 126;
      DIL h12 = {
          'h' , 87 , 344 , 313 , 374 , 2 , 0 , 72 , 25 , 3 , 1 , 2 , 0.500000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn12 , Setupsplbutton1callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( h12.Wid , ( char * ) "SetupWidget13" ) ;
      h12.item = -1;
      DIM m13 = {
      'B' , 51 , 6 , 351 , 36 , 0 , 0 };
      strncpy ( m13.msg , ( char * ) "Select Only Mono Font" , 499 ) ;
      strcpy ( m13.Wid , ( char * ) "SetupWidget14" ) ;
      m13.item = -1;
      DIM m14 = {
      'm' , 10 , 49 , 310 , 73 , -1 , 0 };
      strncpy ( m14.msg , ( char * ) "" , 499 ) ;
      strcpy ( m14.Wid , ( char * ) "Fmsg" ) ;
      m14.item = -1;
      dtmp = D->d;
      i = 0;
      if ( dtmp != NULL ) while ( dtmp [ i ] .t != NULL ) i++;
      dtmp = ( DIA * ) realloc ( dtmp , sizeof ( DIA ) * ( i+16 ) ) ;
      d = dtmp+i;
      d [ 15 ] .t = NULL;
      d [ 0 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 0 ] .N = b0;
      d [ 0 ] .N->item = -1;
      Setupbutton1init ( d [ 0 ] .N , pt ) ;
      d [ 1 ] .t = ( DIT * ) malloc ( sizeof ( DIT ) ) ;
      *d [ 1 ] .t = t1;
      d [ 1 ] .t->item = -1;
      d [ 2 ] .t = ( DIT * ) malloc ( sizeof ( DIW ) ) ;
      *d [ 2 ] .w = w2;
      d [ 2 ] .w->item = -1;
      d [ 3 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 3 ] .N = b3;
      d [ 3 ] .N->item = -1;
      Setupbutton2init ( d [ 3 ] .N , pt ) ;
      d [ 4 ] .t = ( DIT * ) malloc ( sizeof ( DIM ) ) ;
      *d [ 4 ] .m = m4;
      d [ 4 ] .m->item = -1;
      d [ 5 ] .t = ( DIT * ) malloc ( sizeof ( DIM ) ) ;
      *d [ 5 ] .m = m5;
      d [ 5 ] .m->item = -1;
      d [ 6 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 6 ] .N = b6;
      d [ 6 ] .N->item = -1;
      Setupbutton3init ( d [ 6 ] .N , pt ) ;
      d [ 7 ] .t = ( DIT * ) malloc ( sizeof ( DIW ) ) ;
      *d [ 7 ] .w = w7;
      d [ 7 ] .w->item = -1;
      d [ 8 ] .t = ( DIT * ) malloc ( sizeof ( DIM ) ) ;
      *d [ 8 ] .m = m8;
      d [ 8 ] .m->item = -1;
      d [ 9 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 9 ] .N = b9;
      d [ 9 ] .N->item = -1;
      Setupbutton4init ( d [ 9 ] .N , pt ) ;
      d [ 10 ] .t = ( DIT * ) malloc ( sizeof ( DIM ) ) ;
      *d [ 10 ] .m = m10;
      d [ 10 ] .m->item = -1;
      d [ 11 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 11 ] .N = b11;
      d [ 11 ] .N->item = -1;
      Setupbutton5init ( d [ 11 ] .N , pt ) ;
      d [ 12 ] .t = ( DIT * ) malloc ( sizeof ( DIL ) ) ;
      *d [ 12 ] .h = h12;
      d [ 12 ] .h->item = -1;
      Setupsplbutton1init ( d [ 12 ] .h , pt ) ;
      d [ 13 ] .t = ( DIT * ) malloc ( sizeof ( DIM ) ) ;
      *d [ 13 ] .m = m13;
      d [ 13 ] .m->item = -1;
      d [ 14 ] .t = ( DIT * ) malloc ( sizeof ( DIM ) ) ;
      *d [ 14 ] .m = m14;
      d [ 14 ] .m->item = -1;
      d [ 15 ] .t = NULL;
      GrpId = kgOpenGrp ( D ) ;
      D->d = dtmp;
      j = 0;
      while ( d [ j ] .t != NULL ) { kgAddtoGrp ( D , \
           GrpId , ( void * ) ( d [ j ] .t ) ) ;j++;}
      return GrpId;
  }
/* One can also use the following code to add Widgets to an existing Dialog */
  int MakeSetupGroup ( DIALOG *D , void *arg ) {
      int GrpId;
      WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  1 data values
    Browser1  1 data value
    Browser2  1 data value

*************************************************/
      char *v0 ;
      v0 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v0 [ 0 ] = '\0';
      int *v1 ;
      v1 = ( int * ) malloc ( sizeof ( int ) ) ;
      *v1 = 1;
      int *v2 ;
      v2 = ( int * ) malloc ( sizeof ( int ) ) ;
      *v2 = 1;
      void** v = ( void ** ) malloc ( sizeof ( void* ) *4 ) ;
      v [ 3 ] = NULL;
      v [ 0 ] = ( void * ) ( v0 ) ;
      v [ 1 ] = ( void * ) ( v1 ) ;
      v [ 2 ] = ( void * ) ( v2 ) ;
      void *pt = NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      GrpId = SetupGroup ( D , v , pt ) ;
      Gpt = kgGetWidgetGrp ( D , GrpId ) ;
      Gpt->arg = v; // kulina will double free this; you may modify
      return GrpId;
  }
  int Setup ( void *parent , void **v , void *pt ) {
      int ret = 1 , GrpId , k;
      DIALOG D;
      DIA *d = NULL;
      D.VerId = 2107030000;
      kgInitUi ( & D ) ;
      D.d = NULL;
#if 1
      GrpId = SetupGroup ( & D , v , pt ) ;
#else 
      GrpId = MakeSetupGroup ( & D , pt ) ; // can try this also
#endif 
      d = D.d;
      D.d = d;
      D.bkup = 1; /* set to 1 for backup */
      D.bor_type = 4;
      D.df = 12;
      D.tw = 4;
      D.bw = 4;
      D.lw = 4;
      D.rw = 4;
      D.xo = 675; /* Position of Dialog */
      D.yo = 193;
      D.xl = 400; /* Length of Dialog */
      D.yl = 400; /* Width of Dialog */
      D.Initfun = Setupinit; /* init fuction for Dialog */
      D.Cleanupfun = Setupcleanup; /* init fuction for Dialog */
      D.kbattn = 0; /* 1 for drawing keyborad attention */
      D.butattn = 0; /* 1 for drawing button attention */
      D.fullscreen = 0; /* 1 for for fullscreen mode */
      D.NoTabProcess = 0; /* 1 for disabling Tab use */
      D.Deco = 1; /* 1 for Window Decorration */
      D.transparency = 0.000000; /* float 1.0 for full transparency */
      D.Newwin = 1; /* 1 for new window not yet implemented */
      D.DrawBkgr = 1; /* 1 for drawing background */
      D.Bkpixmap = NULL; /* background image */
      D.Sticky = 0; /* 1 for stickyness */
      D.Resize = 0; /* 1 for Resize option */
      D.MinWidth = 100; /* for Resize option */
      D.MinHeight = 100; /* for Resize option */
#if 1 
      D.Callback = SetupCallBack; /* default callback */
#else 
      D.Callback = NULL;
#endif
      D.ResizeCallback = SetupResizeCallBack; /* Resize callback */
#if 0 
      D.WaitCallback = NULL; /* Wait callback */
#else 
      D.WaitCallback = SetupWaitCallBack; /* Wait callback */
#endif
      D.Fixpos = 1; /* 1 for Fixing Position */
      D.NoTaskBar = 0; /* 1 for not showing in task bar*/
      D.NoWinMngr = 0; /* 1 for no Window Manager*/
      D.StackPos = 0; /* -1 , 0 , 1 for for Stack Position -1:below 0:normal 1:above*/
      D.Shapexpm = NULL; /* PNG/jpeg file for window shape;
          Black color will not be drawn */
      D.parent = parent; /* 1 for not showing in task bar*/
      D.pt = pt; /* any data to be passed by user*/
//  strcpy(D.name,"Kulina Designer ver 2.0");    /*  Dialog name you may change */
      if ( D.fullscreen != 1 ) { /* if not fullscreen mode */
          int xres , yres;
          kgDisplaySize ( & xres , & yres ) ;
      // D.xo=D.yo=0; D.xl = xres-10; D.yl=yres-80;
      }
      else { // for fullscreen
          int xres , yres;
          kgDisplaySize ( & xres , & yres ) ;
          D.xo = D.yo = 0; D.xl = xres; D.yl = yres;
//     D.StackPos = 1; // you may need it
      } /* end of fullscreen mode */
      ModifySetupGc ( & D ) ; /* set colors for gui if do not like default*/
      ModifySetup ( & D , GrpId ) ; /* add extras to gui*/
      ret = kgUi ( & D ) ;
      kgCleanUi ( & D ) ;
      return ret;
  }
  void *RunSetup ( void *parent , void *args ) {
/*************************************************

    Text_Box1  1 data values
    Browser1  1 data value
    Browser2  1 data value

*************************************************/
      char v0 [ 500 ] = "" ;
      int v1 = 1;
      int v2 = 1;
      void* v [ 3 ] ;
      v [ 0 ] = ( void * ) ( v0 ) ;
      v [ 1 ] = ( void * ) ( & v1 ) ;
      v [ 2 ] = ( void * ) ( & v2 ) ;
      void *pt [ 2 ] = {NULL , NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      pt [ 0 ] = args;
      Setup ( parent , v , ( void * ) pt ) ;
      return pt [ 1 ] ;
  }
