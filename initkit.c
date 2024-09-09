#include <kulina.h>
  static DIT *TI = NULL;
  static char Fbuf [ 300 ] = "";
  int initkittextbox1callback ( int cellno , int i , void *Tmp ) {
  /*************************************************
   cellno: current cell counted along column strting with 0
           ie 0 to (nx*ny-1)
   i     : widget id starting from 0
   Tmp   : Pointer to DIALOG
   *************************************************/
      DIALOG *D;DIT *T;T_ELMT *e;
      int ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      T = ( DIT * ) kgGetWidget ( Tmp , i ) ;
      e = T->elmt;
      return ret;
  }
  int initkitbutton1callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIN *B;
      int n , ret = 0;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
      TI = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "initkittext" ) ;
      if ( kgFolderBrowser ( NULL , 200 , 200 , Fbuf , ( char * ) "*" ) ) {
          kgSetString ( TI , 0 , Fbuf ) ;
          kgUpdateWidget ( TI ) ;
          kgUpdateOn ( Tmp ) ;
      }
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void initkitbutton1init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  int initkitsplbutton1callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIL *B;
      int n , ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      char *fpt , *rpt;
      D = ( DIALOG * ) Tmp;
      B = ( DIL * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx;
      TI = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "initkittext" ) ;
      fpt = kgGetString ( TI , 0 ) ;
      rpt = ( char * ) malloc ( strlen ( fpt ) +1 ) ;
      strcpy ( rpt , fpt ) ;
      pt [ 1 ] = ( void * ) rpt;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void initkitsplbutton1init ( DIL *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  int initkitinit ( void *Tmp ) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
      int ret = 1;
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[0] is inputs, given by caller */
      return ret;
  }
  int initkitcleanup ( void *Tmp ) {
  /* you add any cleanup/mem free here */
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      int ret = 1;
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[1] is outputs, if any  to be given to caller */
 /* pt[0] is inputs, given by caller */
      return ret;
  }
  static void *MakeImage ( float xl , float yl ) {
      void *fid , *img;
      float x = 200. , y = 400 , dx = 50 , dy = 50 , lng;
      float sh = 1.0;
      fid = kgInitImage ( ( int ) xl , ( int ) yl , 8 ) ;
      kgUserFrame ( fid , 0.0 , 0.0 , xl , yl ) ;
      kgTextSize ( fid , 40.0 , 35.0 , 2.0 ) ;
      kgMove2f ( fid , x , y ) ;
      kgTextFont ( fid , 34 ) ;
      kgTextColor ( fid , 42 ) ;
      y = yl-dy;
      lng = kgStringLength ( fid , "!c37!w41Kit" ) ;
      x = ( xl-lng ) *0.5;
      y -= dy;
      kgMove2f ( fid , x , y ) ;
      kgWriteText ( fid , ( char * ) "!c37!w41Kit" ) ;
      kgTextSize ( fid , 30.0 , 30.0 , 2.0 ) ;
      kgTextFont ( fid , 23 ) ;
      lng = kgStringLength ( fid , "Kulina" ) ;
      x = ( xl-lng ) *0.5;
      y -= dy;
      kgMove2f ( fid , x , y ) ;
      kgWriteText ( fid , ( char * ) "Kulina" ) ;
      lng = kgStringLength ( fid , "Text Editor" ) ;
      x = ( xl-lng ) *0.5;
      y -= dy;
      kgMove2f ( fid , x , y ) ;
      kgWriteText ( fid , ( char * ) "Text Editor" ) ;
      kgTextColor ( fid , 45 ) ;
      kgTextFont ( fid , 34 ) ;
      kgTextSize ( fid , 40.0 , 35.0 , 2.0 ) ;
      y = yl-dy;
      lng = kgStringLength ( fid , "!c37!w41Kit" ) ;
      x = ( xl-lng ) *0.5;
      y -= dy;
      kgMove2f ( fid , x+sh , y-sh ) ;
      kgWriteText ( fid , ( char * ) "!c37!w41Kit" ) ;
      kgTextFont ( fid , 23 ) ;
      kgTextSize ( fid , 30.0 , 30.0 , 2.0 ) ;
      lng = kgStringLength ( fid , "Kulina" ) ;
      x = ( xl-lng ) *0.5;
      y -= dy;
      kgMove2f ( fid , x+sh , y-sh ) ;
      kgWriteText ( fid , ( char * ) "Kulina" ) ;
      lng = kgStringLength ( fid , "Text Editor" ) ;
      x = ( xl-lng ) *0.5;
      y -= dy;
      kgMove2f ( fid , x+sh , y-sh ) ;
      kgWriteText ( fid , ( char * ) "Text Editor" ) ;
      img = kgGetSharpImage ( fid ) ;
      kgCloseImage ( fid ) ;
      return img;
  }
  int Modifyinitkit ( void *Tmp , int GrpId ) {
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      DIP *P;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[0] is inputs given by caller */
      DIA *d;
      P = ( DIP * ) kgGetNamedWidget ( Tmp , ( char * ) "initkitimg" ) ;
      P->xpm = ( void * ) MakeImage ( ( float ) ( P->x2-P->x1 ) ,  \
          ( float ) ( P->y2-P->y1 ) ) ;
      int i , n;
      d = D->d;
      i = 0;while ( d [ i ] .t != NULL ) {;
          i++;
      };
      n = 1;
//  strcpy(D->name,"Kulina Designer ver 2.0");    /*  Dialog name you may change */
#if 0
      if ( D->fullscreen != 1 ) { /* if not fullscreen mode */
          int xres , yres;
          kgDisplaySize ( & xres , & yres ) ;
      // D->xo=D->yo=0; D->xl = xres-10; D->yl=yres-80;
      }
      else { // for fullscreen
          int xres , yres;
          kgDisplaySize ( & xres , & yres ) ;
          D->xo = D->yo = 0; D->xl = xres; D->yl = yres;
//     D->StackPos = 1; // you may need it
      } /* end of fullscreen mode */
#endif
      return GrpId;
  }
  int initkitCallBack ( void *Tmp , void *tmp ) {
  /***********************************
    Tmp :  Pointer to DIALOG
    tmp :  Pointer to KBEVENT
   ***********************************/
      int ret = 0;
      DIALOG *D;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      KBEVENT *kbe;
      D = ( DIALOG * ) Tmp;
      kbe = ( KBEVENT * ) tmp;
      if ( kbe->event == 1 ) {
          if ( kbe->button == 1 ) {
          }
      }
      return ret;
  }
  int initkitResizeCallBack ( void *Tmp ) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      int ret = 0;
      int xres , yres , dx , dy;
      DIALOG *D;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      kgGetWindowSize ( D , & xres , & yres ) ;
      dx = xres - D->xl;
      dy = yres - D->yl;
  /* extra code */
      D->xl = xres;
      D->yl = yres;
      kgRedrawDialog ( D ) ;
      return ret;
  }
  int initkitWaitCallBack ( void *Tmp ) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
      int ret = 0;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      return ret;
  }
  void ModifyinitkitGc ( void *Tmp ) {
      DIALOG *D;
      Gclr *gc;
      D = ( DIALOG * ) Tmp;
      gc = & ( D->gc ) ;
/*
//  You may change default settings here
//  probably you can allow the user to create a config in $HOME
//  and try to read that file (if exits); so dynamic configuration is possible
   kgColorTheme(D,220,220,200);
   kgColorTheme1(D,220,220,200);
   kgColorTheme2(D,220,220,200);
   kgDefaultGuiTheme(gc);
   kgGrayGuiTheme(gc);
   gc->FontSize =9;
   gc->FontGuiSize =9;
   gc->InputFontSize =8;
   gc->MenuFont = 21;
   gc->PromptFont = 21;
   gc->ButtonFont = 21;
   gc->MsgFont = 21;
   gc->Font=23;
   kgMkgclr((char *)"initkit",Tmp);
*/
  }
  int initkitGroup ( DIALOG *D , void **v , void *pt ) {
      int GrpId = 0 , oitems = 0 , i , j;
      DIA *d = NULL , *dtmp;
      char *xpm0 = NULL; /* pixmap info */
      DIP p0 = {
          'p' , 7 , 10 , 474 , 404 , ( void * ) xpm0 , -1 , /* bkgr colour */
          0 , 0 , 0.000000 /* border hide transparency*/
      };
      strcpy ( p0.Wid , ( char * ) "initkitimg" ) ;
      p0.item = -1;
      T_ELMT *e1 ;
      e1 = ( T_ELMT * ) malloc ( sizeof ( T_ELMT ) *1 ) ;
      e1 [ 0 ] .fmt = ( char * ) malloc ( 5 ) ;
      strcpy ( e1 [ 0 ] .fmt , ( char * ) "%30s" ) ;
      e1 [ 0 ] .v = ( void * ) v [ 0 ] ;
      e1 [ 0 ] .sw = 1;
      e1 [ 0 ] .noecho = 0;
      e1 [ 0 ] .img = NULL;
      DIT t1 = {
          't' , 35 , 287 , 350 , 321 , 20 , 1 , 1 , e1 , 1 , 1 , NULL , initkittextbox1callback , 0 , 0 , 18 , 9 /* args , Call back */
      };
      strcpy ( t1.Wid , ( char * ) "initkittext" ) ;
      t1.pt = NULL;
      t1.type = 1;
      t1.item = -1;
      BUT_STR *butn2 = NULL;
      butn2 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn2 [ 0 ] .sw = 1;
      strcpy ( butn2 [ 0 ] .title , ( char * ) "!w32!c36Browse" ) ;
      butn2 [ 0 ] .xpmn = NULL;
      butn2 [ 0 ] .xpmp = NULL;
      butn2 [ 0 ] .xpmh = NULL;
      butn2 [ 0 ] .bkgr = -240245255;
      butn2 [ 0 ] .butncode = 127;
      DIN b2 = {
          'n' , 351 , 285 , 445 , 319 , 2 , 2 , 84 , 24 , 1 , 1 , 8 , 0.500000 , 0 , 0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn2 , initkitbutton1callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b2.Wid , ( char * ) "initkitbrowse" ) ;
      b2.item = -1;
      DIM m3 = {
      'm' , 89 , 246 , 338 , 283 , 0 , 0 };
      strncpy ( m3.msg , ( char * ) "!w32!f23Select File" , 499 ) ;
      strcpy ( m3.Wid , ( char * ) "initkitWidget5" ) ;
      m3.item = -1;
      BUT_STR *butn4 = NULL;
      butn4 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn4 [ 0 ] .sw = 1;
      strcpy ( butn4 [ 0 ] .title , ( char * ) "!w32!c37Done" ) ;
      butn4 [ 0 ] .xpmn = NULL;
      butn4 [ 0 ] .xpmp = NULL;
      butn4 [ 0 ] .xpmh = NULL;
      butn4 [ 0 ] .bkgr = -1;
      butn4 [ 0 ] .butncode = 127;
      DIL h4 = {
          'h' , 193 , 343 , 287 , 376 , 2 , 0 , 84 , 25 , 1 , 1 , 8 , 0.500000 , 0 , 0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn4 , initkitsplbutton1callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( h4.Wid , ( char * ) "initkitWidget5" ) ;
      h4.item = -1;
      dtmp = D->d;
      i = 0;
      if ( dtmp != NULL ) while ( dtmp [ i ] .t != NULL ) i++;
      dtmp = ( DIA * ) realloc ( dtmp , sizeof ( DIA ) * ( i+6 ) ) ;
      d = dtmp+i;
      d [ 5 ] .t = NULL;
      d [ 0 ] .t = ( DIT * ) malloc ( sizeof ( DIP ) ) ;
      *d [ 0 ] .p = p0;
      d [ 0 ] .p->item = -1;
      d [ 1 ] .t = ( DIT * ) malloc ( sizeof ( DIT ) ) ;
      *d [ 1 ] .t = t1;
      d [ 1 ] .t->item = -1;
      d [ 2 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 2 ] .N = b2;
      d [ 2 ] .N->item = -1;
      initkitbutton1init ( d [ 2 ] .N , pt ) ;
      d [ 3 ] .t = ( DIT * ) malloc ( sizeof ( DIM ) ) ;
      *d [ 3 ] .m = m3;
      d [ 3 ] .m->item = -1;
      d [ 4 ] .t = ( DIT * ) malloc ( sizeof ( DIL ) ) ;
      *d [ 4 ] .h = h4;
      d [ 4 ] .h->item = -1;
      initkitsplbutton1init ( d [ 4 ] .h , pt ) ;
      d [ 5 ] .t = NULL;
      GrpId = kgOpenGrp ( D ) ;
      D->d = dtmp;
      j = 0;
      while ( d [ j ] .t != NULL ) { kgAddtoGrp ( D , GrpId ,  \
          ( void * ) ( d [ j ] .t ) ) ;j++;}
      return GrpId;
  }
/* One can also use the following code to add Widgets to an existing Dialog */
  int MakeinitkitGroup ( DIALOG *D , void *arg ) {
      int GrpId;
      WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  1 data values

*************************************************/
      char *v0 ;
      v0 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v0 [ 0 ] = '\0';
      void** v = ( void ** ) malloc ( sizeof ( void* ) *2 ) ;
      v [ 1 ] = NULL;
      v [ 0 ] = ( void * ) ( v0 ) ;
      void *pt = NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      GrpId = initkitGroup ( D , v , pt ) ;
      Gpt = kgGetWidgetGrp ( D , GrpId ) ;
      Gpt->arg = v; // kulina will double free this; you may modify
      return GrpId;
  }
  int initkit ( void *parent , void **v , void *pt ) {
      int ret = 1 , GrpId , k;
      DIALOG D;
      DIA *d = NULL;
      D.VerId = 2107030000;
      kgInitUi ( & D ) ;
      D.d = NULL;
#if 1
      GrpId = initkitGroup ( & D , v , pt ) ;
#else 
      GrpId = MakeinitkitGroup ( & D , pt ) ; // can try this also
#endif 
      d = D.d;
      D.d = d;
      D.bkup = 1; /* set to 1 for backup */
      D.bor_type = 4;
      D.df = 4;
      D.tw = 4;
      D.bw = 4;
      D.lw = 4;
      D.rw = 4;
      D.xo = 803; /* Position of Dialog */
      D.yo = 156;
      D.xl = 481; /* Length of Dialog */
      D.yl = 412; /* Width of Dialog */
      D.Initfun = initkitinit; /* init fuction for Dialog */
      D.Cleanupfun = initkitcleanup; /* init fuction for Dialog */
      D.kbattn = 0; /* 1 for drawing keyborad attention */
      D.butattn = 0; /* 1 for drawing button attention */
      D.fullscreen = 0; /* 1 for for fullscreen mode */
      D.NoTabProcess = 0; /* 1 for disabling Tab use */
      D.Deco = 0; /* 1 for Window Decorration */
      D.transparency = 0.000000; /* float 1.0 for full transparency */
      D.Newwin = 1; /* 1 for new window not yet implemented */
      D.DrawBkgr = 1; /* 1 for drawing background */
      D.Bkpixmap = NULL; /* background image */
      D.Sticky = 0; /* 1 for stickyness */
      D.Resize = 0; /* 1 for Resize option */
      D.MinWidth = 100; /* for Resize option */
      D.MinHeight = 100; /* for Resize option */
#if 1 
      D.Callback = initkitCallBack; /* default callback */
#else 
      D.Callback = NULL;
#endif
      D.ResizeCallback = initkitResizeCallBack; /* Resize callback */
#if 0 
      D.WaitCallback = NULL; /* Wait callback */
#else 
      D.WaitCallback = initkitWaitCallBack; /* Wait callback */
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
      Modifyinitkit ( & D , GrpId ) ; /* add extras to gui*/
      ModifyinitkitGc ( & D ) ; /* set colors for gui if do not like default*/
      ret = kgUi ( & D ) ;
      kgCleanUi ( & D ) ;
      return ret;
  }
  void *Runinitkit ( void *parent , void *args ) {
/*************************************************

    Text_Box1  1 data values

*************************************************/
      char v0 [ 500 ] = "" ;
      void* v [ 1 ] ;
      v [ 0 ] = ( void * ) ( v0 ) ;
      void *pt [ 2 ] = {NULL , NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      pt [ 0 ] = args;
      initkit ( parent , v , ( void * ) pt ) ;
      return pt [ 1 ] ;
  }
