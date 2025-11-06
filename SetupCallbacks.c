#include <kulina.h>
  static DIT *FT;
  static DIN *BB , *SB , *WB , *CB , *NB , *BB , *LB;
  static DIW *W1 , *W2;
  static DIT *Tbl;
  static DIM *Fmsg;
  static DIALOG *Per;
  static Gclr *Gc ;
  char FontName [ 300 ] ;
  void ModifyScrollTableGc ( void *Tmp ) ;
  static int Fonto , Font , Fsizeo , Fsize , Fclro , Fclr , Nclro , \
       Nclr , Widtho , Width , Bclro , Bclr , Lclro , Lclr;
  int Setupbutton1callback ( int butno , int i , void *Tmp ) {
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
#if 0
      if ( kgFolderBrowser ( NULL , 200 , 100 , FontName , ( char * ) "*" ) ) {
          kgSetString ( FT , 0 , FontName ) ;
          kgUpdateWidget ( FT ) ;
          kgUpdateOn ( D ) ;
      }
#else
//  printf("Font = %d\n",Font);
      kgGetFreeTypeFont ( NULL , & Font ) ;
//  printf("Font = %d\n",Font);
      strcpy ( FontName , kgGetOthFont ( Font ) ) ;
      kgWrite ( Fmsg , FontName ) ;
      kgUpdateWidget ( Fmsg ) ;
      kgUpdateOn ( D ) ;
#endif
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void Setupbutton1init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  int Setuptextbox1callback ( int cellno , int i , void *Tmp ) {
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
  int Setupbrowser1callback ( int item , int i , void *Tmp ) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIW *B;
      int ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIW * ) kgGetWidget ( Tmp , i ) ;
      Fsize = ( item-1 ) +6;
      switch ( item ) {
          case 1:
          break;
      }
      return ret;
  }
  int Setupbutton2callback ( int butno , int i , void *Tmp ) {
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
      int r , g , b;
      kgGetDefaultRGB ( Fclr , & r , & g , & b ) ;
      kgGetColor ( NULL , 200 , 100 , & r , & g , & b ) ;
      Fclr = 91;
      kgDefineColor ( Fclr , r , g , b ) ;
      kgChangeButtonColor ( CB , 0 , r , g , b ) ;
      kgUpdateWidget ( CB ) ;
      kgUpdateOn ( D ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void Setupbutton2init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  int Setupbutton3callback ( int butno , int i , void *Tmp ) {
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
      int r , g , b;
      kgGetDefaultRGB ( Nclr , & r , & g , & b ) ;
      kgGetColor ( NULL , 200 , 100 , & r , & g , & b ) ;
      Nclr = 92;
      kgDefineColor ( Nclr , r , g , b ) ;
      kgChangeButtonColor ( NB , 0 , r , g , b ) ;
      kgUpdateWidget ( NB ) ;
      kgUpdateOn ( D ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void Setupbutton3init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  int Setupbrowser2callback ( int item , int i , void *Tmp ) {
  /*********************************** 
    item : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIW *B;
      int ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIW * ) kgGetWidget ( Tmp , i ) ;
      Width = ( item-1 ) *2+14;
      switch ( item ) {
          case 1:
          break;
      }
      return ret;
  }
  int Setupbutton4callback ( int butno , int i , void *Tmp ) {
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
      int r , g , b;
      kgGetDefaultRGB ( Bclr , & r , & g , & b ) ;
      kgGetColor ( NULL , 200 , 100 , & r , & g , & b ) ;
      Bclr = 93;
      kgDefineColor ( Bclr , r , g , b ) ;
      kgChangeButtonColor ( BB , 0 , r , g , b ) ;
      kgUpdateWidget ( BB ) ;
      kgUpdateOn ( D ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void Setupbutton4init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  int Setupbutton5callback ( int butno , int i , void *Tmp ) {
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
      int r , g , b;
      kgGetDefaultRGB ( Lclr , & r , & g , & b ) ;
      kgGetColor ( NULL , 200 , 100 , & r , & g , & b ) ;
      Lclr = 94;
      kgDefineColor ( Lclr , r , g , b ) ;
      kgChangeButtonColor ( LB , 0 , r , g , b ) ;
      kgUpdateWidget ( LB ) ;
      kgUpdateOn ( D ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      return ret;
  }
  void Setupbutton5init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  static int * SetupTbl ( void *Tmp ) {
      int i;
      char *Home;
      char Config [ 200 ] ;
      char *NewFont , afm [ 5 ] = "afm";
      FILE *fp;
      int *ipt = NULL;
      Tbl->FontSize = Fsize;;
      Tbl->width = Width;
      Tbl->Font = Font;
#if 0
      NewFont = ( char * ) kgGetString ( FT , 0 ) ;
      i = 0;
      if ( NewFont [ 0 ] >= ' ' ) {
          while ( NewFont [ i ] == ' ' ) i++;
          if ( NewFont [ i ] > ' ' ) {
              if ( strstr ( NewFont+i , ( char * ) "afm" ) == NULL ) {
                  if ( strstr ( NewFont+i , ( char * ) "." ) != NULL ) {
                      Font = kgAddFixedFont ( NewFont+i ) ;
                      Tbl->Font = Font;
                  }
              }
          }
      }
#endif
      ipt = ( int * ) malloc ( sizeof ( int ) *12 ) ;
//  Gc->tabl_char=Fclr;
      kgGetDefaultRGB ( Fclr , ipt , ipt+1 , ipt+2 ) ;
      kgGetDefaultRGB ( Nclr , ipt+3 , ipt+4 , ipt+5 ) ;
      kgGetDefaultRGB ( Bclr , ipt+6 , ipt+7 , ipt+8 ) ;
      kgGetDefaultRGB ( Lclr , ipt+9 , ipt+10 , ipt+11 ) ;
//  Gc->tabl_hchar=Nclr;
 // Gc->tabl_fill=Bclr;
//  Gc->tabl_line=Lclr;
      sprintf ( Config , "%-s/.kit" , getenv ( "HOME" ) ) ;
      fp = fopen ( Config , "w" ) ;
//  fprintf(fp,"%s\n",kgGetMonoFont(Tbl->Font));
      fprintf ( fp , "%s\n" , kgGetOthFont ( Tbl->Font ) ) ;
      fprintf ( fp , "%d %d\n" , Tbl->FontSize , Tbl->width ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 0 ] , ipt [ 1 ] , ipt [ 2 ] ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 3 ] , ipt [ 4 ] , ipt [ 5 ] ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 6 ] , ipt [ 7 ] , ipt [ 8 ] ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 9 ] , ipt [ 10 ] , ipt [ 11 ] ) ;
      fclose ( fp ) ;
      return ipt;;
  }
  static int * SetupTblDef ( void *Tmp ) {
      int i;
      char *Home;
      char Config [ 200 ] ;
      char *NewFont , afm [ 5 ] = "afm";
      FILE *fp;
      int *ipt = NULL;
      Tbl->FontSize = Fsize;;
      Tbl->width = Width;
      Tbl->Font = Font;
      ipt = ( int * ) malloc ( sizeof ( int ) *12 ) ;
      kgGetDefaultRGB ( Fclr , ipt , ipt+1 , ipt+2 ) ;
      kgGetDefaultRGB ( Nclr , ipt+3 , ipt+4 , ipt+5 ) ;
      kgGetDefaultRGB ( Bclr , ipt+6 , ipt+7 , ipt+8 ) ;
      kgGetDefaultRGB ( Lclr , ipt+9 , ipt+10 , ipt+11 ) ;
      sprintf ( Config , "%-s/.kit" , getenv ( "HOME" ) ) ;
      fp = fopen ( Config , "w" ) ;
//  fprintf(fp,"%s\n",kgGetMonoFont(Tbl->Font));
      fprintf ( fp , "%s\n" , kgGetOthFont ( Tbl->Font ) ) ;
      fprintf ( fp , "%d %d\n" , Tbl->FontSize , Tbl->width ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 0 ] , ipt [ 1 ] , ipt [ 2 ] ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 3 ] , ipt [ 4 ] , ipt [ 5 ] ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 6 ] , ipt [ 7 ] , ipt [ 8 ] ) ;
      fprintf ( fp , "%d %d %d\n" , ipt [ 9 ] , ipt [ 10 ] , ipt [ 11 ] ) ;
      fclose ( fp ) ;
      return ipt;;
  }
  int Setupsplbutton1callback ( int butno , int i , void *Tmp ) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIL *B;
      int n , ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIL * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx;
      switch ( butno ) {
          case 1:
          break;
          case 2:
          ModifyScrollTableGc ( Tbl->D ) ;
          Font = 10;
          Fsize = 10;
          Width = 20;
          Fclr = Fclro;
          Nclr = Nclro;
          Bclr = Bclro;
          Lclr = Lclro;
          pt [ 1 ] = SetupTblDef ( Tmp ) ;
          break;
          case 3:
          pt [ 1 ] = SetupTbl ( Tmp ) ;
          break;
      }
      return ret;
  }
  void Setupsplbutton1init ( DIL *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
  }
  int SetupWidgets ( void *Tmp ) {
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      int r , g , b;
      kgGetDefaultRGB ( Fclr , & r , & g , & b ) ;
      kgChangeButtonColor ( CB , 0 , r , g , b ) ;
      kgGetDefaultRGB ( Nclr , & r , & g , & b ) ;
      kgChangeButtonColor ( NB , 0 , r , g , b ) ;
      kgGetDefaultRGB ( Bclr , & r , & g , & b ) ;
      kgChangeButtonColor ( BB , 0 , r , g , b ) ;
      kgGetDefaultRGB ( Lclr , & r , & g , & b ) ;
      kgChangeButtonColor ( LB , 0 , r , g , b ) ;
      * ( W1->df ) = ( Fsize -6 ) +1;
      * ( W2->df ) = ( Width -14 ) /2+1;
      kgUpdateWidget ( CB ) ;
      kgUpdateWidget ( NB ) ;
      kgUpdateWidget ( BB ) ;
      kgUpdateWidget ( LB ) ;
      kgUpdateWidget ( W1 ) ;
      kgUpdateWidget ( W2 ) ;
      kgUpdateOn ( D ) ;
  }
  int Setupinit ( void *Tmp ) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
      int ret = 1;
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[0] is inputs, given by caller */
      SetupWidgets ( Tmp ) ;
//  kgSetString(FT,0,FontName);
//  kgUpdateWidget(FT);
      kgWrite ( Fmsg , FontName ) ;
      kgUpdateWidget ( Fmsg ) ;
      kgUpdateOn ( Tmp ) ;
      return ret;
  }
  int Setupcleanup ( void *Tmp ) {
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
  int ModifySetup ( void *Tmp , int GrpId ) {
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[0] is inputs given by caller */
      Tbl = ( DIT * ) pt [ 0 ] ;
      Per = ( DIALOG * ) Tbl->D;
      Gc = & ( Per->gc ) ;
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
      Fonto = Tbl->Font;
      Fsizeo = Tbl->FontSize;
      Widtho = Tbl->width;
      Fclro = Gc->tabl_char;
      Nclro = Gc->tabl_hchar;
      Bclro = Gc->tabl_fill;;
      Lclro = Gc->tabl_line;
      Font = Fonto;
      Fsize = Fsizeo;
      Width = Widtho;
      Fclr = Fclro;
      Nclr = Nclro;
      Bclr = Bclro;
      Lclr = Lclro;
      strcpy ( FontName , kgGetOthFont ( Tbl->Font ) ) ;
      FT = ( DIT * ) kgGetNamedWidget ( D , ( char * ) "Font" ) ;
      BB = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "Browse" ) ;
      SB = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "FontSize" ) ;
      WB = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "Width" ) ;
      CB = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "FontClr" ) ;
      NB = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "NumClr" ) ;
      BB = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "BkgrClr" ) ;
      LB = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "LineClr" ) ;
      W1 = ( DIW * ) kgGetNamedWidget ( D , ( char * ) "FontSize" ) ;
      W2 = ( DIW * ) kgGetNamedWidget ( D , ( char * ) "Width" ) ;
      Fmsg = ( DIM * ) kgGetNamedWidget ( D , ( char * ) "Fmsg" ) ;
      * ( W1->df ) = ( Fsize -6 ) /2+1;
      * ( W2->df ) = ( Width -14 ) /2+1;
      return GrpId;
  }
  int SetupCallBack ( void *Tmp , void *tmp ) {
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
  int SetupResizeCallBack ( void *Tmp ) {
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
  int SetupWaitCallBack ( void *Tmp ) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
    Called while waiting for event  
    return value 1 will close the the UI  
   ***********************************/ 
      int ret = 0;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      return ret;
  }
