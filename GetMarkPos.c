#include <kulina.h>
  static DIT *T = NULL;
  int GetMarkPostextbox1callback ( int cellno , int i , void *Tmp ) {
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
  int GetMarkPossplbutton1callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIL *B;
      int n , ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      int *MarkPos = ( int * ) pt [ 0 ] ;
      B = ( DIL * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx;
      switch ( butno ) {
          case 1:
          *MarkPos = kgGetInt ( T , 0 ) ;
          pt [ 1 ] = ( void * ) MarkPos;
          break;
      }
      return ret;
  }
  void GetMarkPossplbutton1init ( DIL *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg
  }
  int GetMarkPosinit ( void *Tmp ) {
  /***********************************
    Tmp :  Pointer to DIALOG
   ***********************************/
  /* you add any initialisation here */
      int ret = 1;
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[0] is inputs, given by caller */
      int *MarkPos = ( int * ) pt [ 0 ] ;
      T = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "Tbox" ) ;
      kgSetInt ( T , 0 , *MarkPos ) ;
      kgUpdateWidget ( T ) ;
      return ret;
  }
  int GetMarkPoscleanup ( void *Tmp ) {
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
  int ModifyGetMarkPos ( void *Tmp , int GrpId ) {
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[0] is inputs given by caller */
      DIA *d;
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
  int GetMarkPosCallBack ( void *Tmp , void *tmp ) {
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
  int GetMarkPosResizeCallBack ( void *Tmp ) {
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
  int GetMarkPosWaitCallBack ( void *Tmp ) {
  /***********************************
    Tmp :  Pointer to DIALOG 
    Called while waiting for event 
    return value 1 will close the the UI 
   ***********************************/
      int ret = 0;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      return ret;
  }
  void ModifyGetMarkPosGc ( void *Tmp ) {
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
   kgMkgclr((char *)"GetMarkPos",Tmp);
*/
  }
  int GetMarkPosGroup ( DIALOG *D , void **v , void *pt ) {
      int GrpId = 0 , oitems = 0 , i , j;
      DIA *d = NULL , *dtmp;
      T_ELMT *e0 ;
      e0 = ( T_ELMT * ) malloc ( sizeof ( T_ELMT ) *1 ) ;
      e0 [ 0 ] .fmt = ( char * ) malloc ( 17 ) ;
      strcpy ( e0 [ 0 ] .fmt , ( char * ) "Mark Position%6d" ) ;
      e0 [ 0 ] .v = ( void * ) v [ 0 ] ;
      e0 [ 0 ] .sw = 1;
      e0 [ 0 ] .noecho = 0;
      e0 [ 0 ] .img = NULL;
      DIT t0 = {
          't' , 10 , 9 , 234 , 43 , 20 , 1 , 1 , e0 , 1 , 1 , NULL , GetMarkPostextbox1callback , 0 , 0 , 18 , 9 /* args , Call back */
      };
      strcpy ( t0.Wid , ( char * ) "Tbox" ) ;
      t0.pt = NULL;
      t0.type = 1;
      t0.item = -1;
      BUT_STR *butn1 = NULL;
      butn1 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn1 [ 0 ] .sw = 1;
      strcpy ( butn1 [ 0 ] .title , ( char * ) "!c38Okay" ) ;
      butn1 [ 0 ] .xpmn = NULL;
      butn1 [ 0 ] .xpmp = NULL;
      butn1 [ 0 ] .xpmh = NULL;
      butn1 [ 0 ] .bkgr = -235255250;
      DIL h1 = {
          'h' , 89 , 58 , 169 , 87 , 2 , 0 , 72 , 22 , 1 , 1 , 2 , 0.500000 , 0 , 0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn1 , GetMarkPossplbutton1callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( h1.Wid , ( char * ) "GetMarkPosWidget3" ) ;
      h1.item = -1;
      dtmp = D->d;
      i = 0;
      if ( dtmp != NULL ) while ( dtmp [ i ] .t != NULL ) i++;
      dtmp = ( DIA * ) realloc ( dtmp , sizeof ( DIA ) * ( i+3 ) ) ;
      d = dtmp+i;
      d [ 2 ] .t = NULL;
      d [ 0 ] .t = ( DIT * ) malloc ( sizeof ( DIT ) ) ;
      *d [ 0 ] .t = t0;
      d [ 0 ] .t->item = -1;
      d [ 1 ] .t = ( DIT * ) malloc ( sizeof ( DIL ) ) ;
      *d [ 1 ] .h = h1;
      d [ 1 ] .h->item = -1;
      GetMarkPossplbutton1init ( d [ 1 ] .h , pt ) ;
      d [ 2 ] .t = NULL;
      GrpId = kgOpenGrp ( D ) ;
      D->d = dtmp;
      j = 0;
      while ( d [ j ] .t != NULL ) { kgAddtoGrp ( D , GrpId ,  \
          ( void * ) ( d [ j ] .t ) ) ;j++;}
      return GrpId;
  }
/* One can also use the following code to add Widgets to an existing Dialog */
  int MakeGetMarkPosGroup ( DIALOG *D , void *arg ) {
      int GrpId;
      WIDGETGRP *Gpt;
/*************************************************

    Text_Box1  1 data values

*************************************************/
      int *v0 ;
      v0 = ( int * ) malloc ( sizeof ( int ) ) ;
      *v0 = 1;
      void** v = ( void ** ) malloc ( sizeof ( void* ) *2 ) ;
      v [ 1 ] = NULL;
      v [ 0 ] = ( void * ) ( v0 ) ;
      void *pt = NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      GrpId = GetMarkPosGroup ( D , v , pt ) ;
      Gpt = kgGetWidgetGrp ( D , GrpId ) ;
      Gpt->arg = v; // kulina will double free this; you may modify
      return GrpId;
  }
  int GetMarkPos ( void *parent , void **v , void *pt ) {
      int ret = 1 , GrpId , k;
      DIALOG D;
      DIA *d = NULL;
      D.VerId = 2107030000;
      kgInitUi ( & D ) ;
      D.d = NULL;
#if 1
      GrpId = GetMarkPosGroup ( & D , v , pt ) ;
#else 
      GrpId = MakeGetMarkPosGroup ( & D , pt ) ; // can try this also
#endif 
      d = D.d;
      D.d = d;
      D.bkup = 1; /* set to 1 for backup */
      D.bor_type = 4;
      D.df = 1;
      D.tw = 4;
      D.bw = 4;
      D.lw = 4;
      D.rw = 4;
      D.xo = 203; /* Position of Dialog */
      D.yo = 81;
      D.xl = 257; /* Length of Dialog */
      D.yl = 92; /* Width of Dialog */
      D.Initfun = GetMarkPosinit; /* init fuction for Dialog */
      D.Cleanupfun = GetMarkPoscleanup; /* init fuction for Dialog */
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
      D.Callback = GetMarkPosCallBack; /* default callback */
#else 
      D.Callback = NULL;
#endif
      D.ResizeCallback = GetMarkPosResizeCallBack; /* Resize callback */
#if 0 
      D.WaitCallback = NULL; /* Wait callback */
#else 
      D.WaitCallback = GetMarkPosWaitCallBack; /* Wait callback */
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
      ModifyGetMarkPos ( & D , GrpId ) ; /* add extras to gui*/
      ModifyGetMarkPosGc ( & D ) ; /* set colors for gui if donot like default*/
      ret = kgUi ( & D ) ;
      kgCleanUi ( & D ) ;
      return ret;
  }
  void *RunGetMarkPos ( void *parent , void *args ) {
/*************************************************

    Text_Box1  1 data values

*************************************************/
      int v0 = 1;
      void* v [ 1 ] ;
      v [ 0 ] = ( void * ) ( & v0 ) ;
      void *pt [ 2 ] = {NULL , NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      pt [ 0 ] = args;
      GetMarkPos ( parent , v , ( void * ) pt ) ;
      return pt [ 1 ] ;
  }
