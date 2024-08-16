#include <kulina.h>
  static DIT *Tbl;
  static T_ELMT *E;
  static Dlink *Slist;
  static DIV *V;
  static DIL *DB;
  static DIN *B1;
  static int Mid;
  static DIN *Opt;
  static DIN *SB;
  static DIN *RB;
  static DIN *GB;
  static DIT *ST;
  static DIT *RT;
  static DIT *MT;
  static int StartLine = 0 , EndLine = 0 , Nlines , Count;
  static int AddMode = 0 , AddRow = -1;;
  static double Vsize , Vpos;
  static int MarkPos = 1;
  static int ExpandTab = 0;
  char *flname = NULL;
  static char Msg [ 200 ] ;
  static char Bkup [ 300 ] ;
  static char SaveFile [ 300 ] ;
  static char Buf [ 500 ] , Buf1 [ 500 ] ;
  void *RunGetFileName ( void *parent , void *args ) ;
  void *RunGetMarkPos ( void *parent , void *args ) ;
  static int GetLength ( char *s1 , char *s2 ) ;
  static int GetRealPos ( ) ;
  void * Runinitkit ( void *, void* ) ;
  static int SearchTbl();
  static int Splash ( char *Msg );
  static Dlink *BLS=NULL;
  static Dlink *Blist=NULL;
#define RETURN(n) {\
   Vpos = ( double ) ( StartLine-1 ) *100.0/Count;\
       ReadTbl ( ) ;\
       kgSetScrollPos ( V , Vpos ) ;\
       kgUpdateWidget ( V ) ;\
       kgUpdateOn ( Tmp ) ;\
       kgSetAttnWidget ( Tmp , Tbl ) ;\
       return ( n ) ;\
   }
static int comparerec(void *r1,void *r2) {
     if(strcmp((char *)r1,(char *)r2)==0 ) return 1;
     else return 0;
}
static int Compare(void) {
     int ret =0;
     Dlink *bk = (Dlink *)Dpop(BLS);
     if(bk==NULL) return 0;
     ret = Dcomplist(Slist,bk,comparerec);
     Dpush(BLS,bk);
     return ret;
}
static int Checkbkup(Dlink *bk) {
     int ret =0;
     if(bk==NULL) return 0;
     ret = Dcomplist(Slist,bk,comparerec);
     printf("Checkbkup : %d\n",ret);
     return ret;
}
static void *CopyRec(void *bf) {
   char *s=(char *)bf,*d;
   d = (char *) malloc(strlen(s)+1);
   strcpy(d,s);
   return d;
}
static void Push(){
   int count;
   Dlink *Bk=Dnewlist(Slist,CopyRec);
   Dpush(BLS,Bk);
   count = Dcount(BLS);
   printf("Pushed: count= %d\n",count);
   if(count> 10) {
      Dend(BLS);
      Bk = (Dlink *) Dpick(BLS);
      Dempty(Bk);
   }
}
static Dlink *Pop(){
  Dlink *bk = (Dlink *)Dpop(BLS);
  if(bk == NULL) return NULL;
  while (Checkbkup(bk)) {
    if(Dcount(BLS)== 0) {
        Dpush(BLS,bk);
        return NULL;
    }
    else Dempty(bk);
    bk = (Dlink *)Dpop(BLS);
    if(bk == NULL) return NULL;
  }
    if(Dcount(BLS)== 0) {
        Dpush(BLS,Dnewlist(bk,CopyRec));
        return bk;
    }
  return bk;
}
  static int Splash ( char *Msg ) {
      kgSplashMessage ( Tbl->D , 50 , 100 , 400 , 25 , Msg , 23 , 0 , 15 ) ;
      return 1;
  }
  static int SetupVbar ( ) {
      Count = Dcount ( Slist ) ;
      if ( Count > Nlines ) {
          kgSetWidgetVisibility ( V , 1 ) ;
          Vsize = ( double ) Nlines/Count*100;
          Vpos = ( double ) ( StartLine-1 ) /Count*100;
          kgSetScrollLength ( V , Vsize ) ;
          kgSetScrollPos ( V , Vpos ) ;
      }
      else kgSetWidgetVisibility ( V , 0 ) ;
      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int SetupTbl ( ) {
      int k;
      Count = Dcount ( Slist ) ;
      if ( Count <= Nlines ) {
//          Count = Dcount ( Slist ) ;
//          if ( Count < Nlines ) EndLine = Count;
//          else EndLine = Nlines;
          EndLine = Count;
          for ( k = 0;k < EndLine;k++ ) kgSetOnTableCell ( Tbl , k*2+1 ) ;
          for ( k = EndLine;k < Nlines;k++ ) kgSetOffTableCell ( Tbl , k*2+1 ) ;
      }
      else {
          EndLine = StartLine+Nlines-1;
          for ( k = 0;k < Nlines;k++ ) kgSetOnTableCell ( Tbl , k*2+1 ) ;
      }
//      kgUpdateWidget ( Tbl ) ;
      return 1;
  }
  static int WriteLineNo ( int row ) {
      char BUFF [ 10 ] ;
      sprintf ( BUFF , "%6d" , StartLine+row ) ;
      kgSetString ( Tbl , row*Tbl->nx , BUFF ) ;
      return 1;
  }
  static int ClearLineNo ( int row ) {
      char BUFF [ 10 ] ;
      strcpy ( BUFF , ( char * ) "" ) ;
      kgSetString ( Tbl , row*Tbl->nx , BUFF ) ;
      return 1;
  }
  static int WriteTbl ( void ) {
      int n = ( EndLine -StartLine +1 ) ;
      int i , j , k , l;
      char *cpt , *spt;
      char Buf [ 500 ] ;
      Resetlink ( Slist ) ;
      Dposition ( Slist , StartLine ) ;
      for ( i = 0;i < n;i++ ) {
          cpt = ( char * ) Getrecord ( Slist ) ;
          if ( cpt == NULL ) {
              fprintf ( stderr , "Cpt= NULL, Start: %d End:%d\n" , StartLine , EndLine ) ;
              fflush ( stderr ) ;
              break;
          }
          j = 0;k = 0;
          while ( ( cpt [ j ] >= ' ' ) || ( cpt [ j ] == '\t' ) ) {
              if ( cpt [ j ] != '\t' ) Buf [ k++ ] = cpt [ j ] ;
              else {
                  if ( ExpandTab ) {
                      l = ( j/8+1 ) *8;
                      while ( k < l ) Buf [ k++ ] = ' ';
                  }
                  else {
                      Buf [ k++ ] = cpt [ j ] ;
                      l = ( j/8+1 ) *8;
                      while ( k < l ) Buf [ k++ ] = 127;
                  }
              }
              j++;
          }
          Buf [ k ] = '\0';
          kgSetString ( Tbl , i*2+1 , Buf ) ;
          WriteLineNo ( i ) ;
      }
      kgUpdateWidget ( Tbl ) ;
      return 1;
  }
  static int ReadTbl ( void ) {
      int n = ( EndLine -StartLine +1 ) ;
      int i , j , k;
      char *cpt , *spt;
      if(!Compare())Push();
      for ( i = 0;i < n;i++ ) {
          cpt = ( char * ) kgGetString ( Tbl , i*2+1 ) ;
          spt = ( char * ) malloc ( strlen ( cpt ) +3 ) ;
          k = 0;j = 0;
          while ( cpt [ k ] != '\0' ) {
              if ( cpt [ k ] == 127 ) {k++;continue;}
              spt [ j ] = cpt [ k ] ;
              k++;j++;
          }
          spt [ j++ ] = '\n';
          spt [ j ] = '\0';
//          strcpy ( spt , cpt ) ;
//          strcat ( spt , "\n" ) ;
//       printf("%s",spt);
          Dreplace ( Slist , spt , StartLine+i-1 ) ;
      }
      return 1;
  }
  static int UpdateTbl ( void ) {
      int n = ( EndLine -StartLine +1 ) ;
      int i , j , k;
      char *cpt , *spt;
      for ( i = 0;i < n;i++ ) {
          cpt = ( char * ) kgGetString ( Tbl , i*2+1 ) ;
          spt = ( char * ) malloc ( strlen ( cpt ) +3 ) ;
          k = 0;j = 0;
          while ( cpt [ k ] != '\0' ) {
              if ( cpt [ k ] == 127 ) {
                 printf("Got 127\n");
                 k++;continue;
              }
              spt [ j ] = cpt [ k ] ;
              k++;j++;
          }
          spt [ j++ ] = '\n';
          spt [ j ] = '\0';
//          strcpy ( spt , cpt ) ;
//          strcat ( spt , "\n" ) ;
//       printf("%s",spt);
          Dreplace ( Slist , spt , StartLine+i-1 ) ;
      }
      return 1;
  }
  static int AddLine ( int row ) {
      char *buf;
      ReadTbl ( ) ;
      Dposition ( Slist , StartLine+row ) ;
      buf = ( char * ) malloc ( 2 ) ;
      strcpy ( buf , ( char * ) "\n" ) ;
      Dadd ( Slist , buf ) ;
      Count = Dcount ( Slist ) ;
      if ( Count <= ( Tbl->ny ) ) {
          EndLine+= 1;
          if ( EndLine <= Nlines ) {
              kgSetOnTableCell ( Tbl , ( EndLine-1 ) *2+1 ) ;
          }
      }
      if ( row == ( Nlines-1 ) ) {
          StartLine += 1;
          EndLine += 1;
      }
      WriteTbl ( ) ;
      SetupVbar ( ) ;
      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int AddStringLine ( int row ) {
      char *buf;
      ReadTbl ( ) ;
      Dposition ( Slist , StartLine+row ) ;
      buf = ( char * ) malloc ( strlen ( Buf1 ) +1 ) ;
      strcpy ( buf , ( char * ) Buf1 ) ;
      Dadd ( Slist , buf ) ;
      Count = Dcount ( Slist ) ;
      if ( Count <= ( Tbl->ny ) ) {
          EndLine+= 1;
          if ( EndLine <= Nlines ) {
              kgSetOnTableCell ( Tbl , ( EndLine-1 ) *2+1 ) ;
          }
      }
      if ( row == ( Nlines-1 ) ) {
          StartLine += 1;
          EndLine += 1;
      }
      WriteTbl ( ) ;
      SetupVbar ( ) ;
      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int InsertLine ( int row ) {
      char *buf;
      ReadTbl ( ) ;
      Dposition ( Slist , StartLine+row ) ;
      buf = ( char * ) malloc ( 2 ) ;
      strcpy ( buf , ( char * ) "\n" ) ;
      Dinsert ( Slist , buf ) ;
      Count = Dcount ( Slist ) ;
      if ( Count <= ( Tbl->ny ) ) {
          EndLine+= 1;
          if ( EndLine <= Nlines ) {
              kgSetOnTableCell ( Tbl , ( EndLine-1 ) *2+1 ) ;
          }
      }
      WriteTbl ( ) ;
      SetupVbar ( ) ;
      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int DeleteLine ( int row ) {
      char *buf;
      ReadTbl ( ) ;
//      printf("StartLine: %d:%d\n",StartLine,EndLine);
      Dposition ( Slist , StartLine+row ) ;
      Ddelete ( Slist ) ;
      Count = Dcount ( Slist ) ;
      if ( EndLine > Count ) {
          EndLine = Count;
      }
      if ( Count == 0 ) {
          StartLine = 1;
          EndLine = 1;
          buf = ( char * ) malloc ( 2 ) ;
          strcpy ( buf , "\n" ) ;
          Dadd ( Slist , buf ) ;
          Count = 1;
      }
      if ( Count <= Nlines ) {
          StartLine = EndLine-Count+1;
      }
      else {
          if ( ( EndLine-StartLine+1 ) < Nlines ) {
              StartLine = EndLine-Nlines+1;
          }
      }
      if ( ( Count ) < Nlines ) {
          kgSetString ( Tbl , ( Count ) *2+1 , ( char * ) "" ) ;
          kgSetOffTableCell ( Tbl , Count*2+1 ) ;
          ClearLineNo ( Count ) ;
      }
      WriteTbl ( ) ;
      SetupVbar ( ) ;
      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int RemoveLine ( int row ) {
      char *buf;
      Dposition ( Slist , StartLine+row ) ;
      Ddelete ( Slist ) ;
      Count = Dcount ( Slist ) ;
      if ( EndLine > Count ) {
          EndLine = Count;
      }
      if ( Count == 0 ) {
          StartLine = 1;
          EndLine = 1;
          buf = ( char * ) malloc ( 2 ) ;
          strcpy ( buf , "\n" ) ;
          Dadd ( Slist , buf ) ;
          Count = 1;
      }
      if ( Count <= Nlines ) {
          StartLine = EndLine-Count+1;
      }
      else {
          if ( ( EndLine-StartLine+1 ) < Nlines ) {
              StartLine = EndLine-Nlines+1;
          }
      }
      if ( ( Count ) < Nlines ) {
          kgSetString ( Tbl , ( Count ) *2+1 , ( char * ) "" ) ;
          kgSetOffTableCell ( Tbl , Count*2+1 ) ;
          ClearLineNo ( Count ) ;
      }
      return 1;
  }
  int ScrollTabletablebox1callback ( int cellno , int i , void *Tmp ) {
  /*************************************************
   cellno: current cell counted along column strting with 0
           ie 0 to (nx*ny-1)
           However cellno got 2 special values
             1. SCROLL_DOWN a scrolldown action
             2. SCROLL_UP a scrolldown action
             which may be ignored or peocessed
   i     : widget id starting from 0
   Tmp   : Pointer to DIALOG
   *************************************************/
      DIALOG *D;DIT *T;T_ELMT *e;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      int ret = 1;
      double pos;
      D = ( DIALOG * ) Tmp;
      T = ( DIT * ) kgGetWidget ( Tmp , i ) ;
      e = T->elmt;
      if ( cellno == SCROLL_DOWN ) {
          ReadTbl ( ) ;
          if ( EndLine < ( Count ) ) {
              StartLine++;
              EndLine++;
              WriteTbl ( ) ;
          }
          Vpos = ( double ) ( StartLine-1 ) *100.0/Count;
          kgSetScrollPos ( V , Vpos ) ;
          kgUpdateWidget ( V ) ;
          kgSetTableCursor ( Tbl , ( Nlines-1 ) *2+1 ) ;
          kgUpdateOn ( Tbl->D ) ;
          kgSkipEvents ( Tbl->D ) ;
      }
      else if ( cellno == SCROLL_UP ) {
          ReadTbl ( ) ;
          if ( StartLine > 1 ) {
              StartLine--;
              EndLine--;
              WriteTbl ( ) ;
          }
          Vpos = ( double ) ( StartLine-1 ) *100.0/Count;
          kgSetScrollPos ( V , Vpos ) ;
          kgUpdateWidget ( V ) ;
          kgSetTableCursor ( Tbl , 1 ) ;
          kgUpdateOn ( Tbl->D ) ;
          kgSkipEvents ( Tbl->D ) ;
      }
      else {
          if ( AddMode ) {
              int row = cellno/Tbl->nx;
              if ( row != AddRow ) {AddMode = 0;}
              else {
                  AddLine ( row ) ;
                  if ( row < ( Tbl->ny-1 ) ) row++;
                  AddRow = row;
              }
              kgSetTableCursor ( Tbl , ( row ) *Tbl->nx+1 ) ;
//        printf("Row: %d:%d  %d %d\n",row, cellno,Tbl->nx,Tbl->ny);
              kgUpdateOn ( Tbl->D ) ;
          }
          else {
              int curpos = kgGetTableCurpos ( Tbl ) ;
              int row = kgGetTableRow ( Tbl ) ;
              char *spt = kgGetString ( Tbl , cellno ) ;
              strcpy ( Buf , spt ) ;
              strcpy ( Buf1 , Buf+curpos ) ;
              strcat ( Buf1 , ( char * ) "\n" ) ;
              Buf [ curpos ] = '\0';
              strcat ( Buf , "\n" ) ;
              kgSetString ( Tbl , cellno , Buf ) ;
              kgUpdateWidget ( Tbl ) ;
              kgUpdateOn ( Tbl->D ) ;
              ReadTbl ( ) ;
              AddStringLine ( row ) ;
              if ( row < ( Tbl->ny-1 ) ) row++;
              kgSetTableCursor ( Tbl , ( row ) *Tbl->nx+1 ) ;
//      kgSetTableCursorPos ( Tbl , ( row) *Tbl->nx+1 , 0) ;
              kgUpdateOn ( Tbl->D ) ;
          }
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
  int ScrollTablevertscroll1callback ( double val , int i , void *Tmp ) {
  /***********************************
    val : current value
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIV *V;
      int ret = 1;
      int pos;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      V = ( DIV * ) kgGetWidget ( Tmp , i ) ;
      ReadTbl ( ) ;
      pos = Count*val/100.0;
      StartLine = pos+1;
      EndLine = StartLine +Nlines -1;
      if ( StartLine < 1 ) {
          StartLine = 1;
          EndLine = StartLine+Nlines-1;
      }
      if ( EndLine > Count ) {
          EndLine = Count;
          StartLine = EndLine -Nlines+1;
      }
//      printf("DIV: %d %d:%d\n",StartLine,EndLine,(Nlines/2)*Tbl->nx+1);
      WriteTbl ( ) ;
      kgSetTableCursor ( Tbl , ( Nlines/2 ) *Tbl->nx+1 ) ;
      kgSetAttnWidget ( Tmp , Tbl ) ;
      kgUpdateOn ( D ) ;
      return ret;
  }
  static int GotoMark ( ) {
      MarkPos = kgGetInt ( MT , 0 ) ;
      if ( MarkPos < 1 ) {
          MarkPos = 1;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
      }
      int pos = MarkPos -StartLine;
      ReadTbl ( ) ;
      Count = Dcount ( Slist ) ;
      if ( MarkPos > Count ) MarkPos = Count;
      pos = MarkPos -StartLine;
#if 1
      if ( ( pos > 0 ) && ( pos < Nlines ) ) {
          WriteTbl ( ) ;
          kgSetTableCursor ( Tbl , ( pos ) *Tbl->nx+1 ) ;
          kgSetAttnWidget ( Tbl->D , Tbl ) ;
          SetupVbar ( ) ;
          kgUpdateOn ( Tbl->D ) ;
          return 1;
      }
#endif
      EndLine = MarkPos;
      StartLine = EndLine -Nlines +1;
      if ( StartLine < 1 ) {
          StartLine = 1;
          EndLine = Nlines;
          if ( EndLine > Count ) EndLine = Count;
      }
      WriteTbl ( ) ;
      pos = MarkPos - StartLine;
//      printf("pos = %d\n",pos);
      kgSetTableCursor ( Tbl , ( pos ) *Tbl->nx+1 ) ;
      kgSetAttnWidget ( Tbl->D , Tbl ) ;
      SetupVbar ( ) ;
      kgUpdateOn ( Tbl->D ) ;
      return 1;
  }
  int ScrollTablehorizscroll1callback ( double val , int i , void *Tmp ) {
  /***********************************
    val : current value
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIZ *Z;
      int ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      Z = ( DIZ * ) kgGetWidget ( Tmp , i ) ;
      return ret;
  }
  int ScrollTablesplbutton1callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIL *B;
      int n , ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      char *cpt;
      D = ( DIALOG * ) Tmp;
      B = ( DIL * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx;
      switch ( butno ) {
          case 1:
          pt [ 1 ] = NULL;
          Dempty ( Slist ) ;
          Slist = Dreadfile ( SaveFile ) ;
          if ( Dcount ( Slist ) == 0 ) {
              Dempty ( Slist ) ;
              break;
          }
          if ( kgCheckMenu ( D , 10 , 100 , ( char * ) "Want to keep Saved File ?" , 1 ) ) \
          {
              char *fpt;
              strcpy ( Buf , flname ) ;
              if ( ( fpt = RunGetFileName ( NULL , Buf ) ) == NULL ) break;
              strcpy ( Buf , fpt ) ;
              free ( fpt ) ;
              Dempty ( Slist ) ;
              Slist = Dreadfile ( SaveFile ) ;
              Dwritefile ( Slist , Buf ) ;
              Dempty ( Slist ) ;
          }
          break;
          case 2:
          ReadTbl ( ) ;
          Dwritefile ( Slist , flname ) ;
          pt [ 1 ] = pt [ 0 ] ;
          Dempty ( Slist ) ;
          break;
      }
      remove ( Bkup ) ;
      remove ( SaveFile ) ;
      return ret;
  }
  void ScrollTablesplbutton1init ( DIL *B , void *pt ) {
      DB = B;
  }
  int ScrollTablebutton1callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIN *B;
      int n , ret = 0;
      int row;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      char *buf;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
      switch ( butno ) {
          case 1:
          row = kgGetTableRow ( Tbl ) ;
          DeleteLine ( row ) ;
          Count = Dcount ( Slist ) ;
          if ( Count <= 0 ) {
              buf = ( char * ) malloc ( 2 ) ;
              strcpy ( buf , "\n" ) ;
              Count = 1;
          }
          if ( row >= Count ) row = Count-1;
          kgSetTableCursor ( Tbl , ( row ) *Tbl->nx+1 ) ;
          kgUpdateOn ( Tmp ) ;
          break;
          case 2:
          AddMode = 1;
          row = kgGetTableRow ( Tbl ) ;
#if 0
          if ( row < Tbl->ny-1 ) {
              kgSetOnTableCell ( Tbl , ( row+1 ) *Tbl->nx+1 ) ;
//      kgUpdateWidget(Tbl);
//      kgUpdateOn(Tmp);
          }
#endif
          AddLine ( row ) ;
#if 1
          if ( row < ( Tbl->ny-1 ) ) row++;
          kgSetTableCursor ( Tbl , ( row ) *Tbl->nx+1 ) ;
#endif
          AddRow = row;
          kgUpdateOn ( Tmp ) ;
          break;
          case 3:
          AddMode = 1;
          row = kgGetTableRow ( Tbl ) ;
          InsertLine ( row ) ;
          kgSetTableCursor ( Tbl , ( row ) *Tbl->nx+1 ) ;
          AddRow = row;
          kgUpdateOn ( Tmp ) ;
          break;
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
  void ScrollTablebutton1init ( DIN *B , void *pt ) {
  }
  static char * ReplaceString ( char *lptr , char *ptmp ) {
      int k , l1 , l2 , loc;
      char *s = ( char * ) kgGetString ( ST , 0 ) ;
      char *r = ( char * ) kgGetString ( RT , 0 ) ;
      l1 = strlen ( lptr ) ;
      l2 = strlen ( ptmp ) ;
      loc = l1 -l2;
      strcpy ( Buf , lptr ) ;
      Buf [ loc ] = '\0';
      strcat ( Buf , r ) ;
      strcat ( Buf , ptmp+strlen ( s ) ) ;
//      printf ( "lptr : %s\n" , lptr ) ;
//      printf ( "Buf: %s" , Buf ) ;
      return Buf;
  }
  static int GetRealPos ( ) {
      char *s ;
      int curpos , realpos , i , k;
      int row , cell;
      curpos = kgGetTableCurpos ( Tbl ) ;
      cell = kgGetTableCell ( Tbl ) ;
      s = kgGetString ( Tbl , cell ) ;
      k = -1;
      for ( i = 0;i <= curpos;i++ ) {
          if ( s [ i ] != 127 ) k++;
      }
      return k;
  }
  int ScrollTablebutton5callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIN *B;
      int n , ret = 0;
      int k = 0 , loc , count;
      char *spt , *lptr , *ptmp , *npt;
      int row , curpos , stchar , rowbk , spos , rcurpos;
      int Slbak , Elbak , curbk;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
      spt = ( char * ) kgGetString ( ST , 0 ) ;
      k = 0;
      while ( spt [ k ] == ' ' ) k++;
      if ( spt [ k ] < ' ' ) return ret;
//      printf("%s\n",spt+k);
      ReadTbl ( ) ;
      Count = Dcount ( Slist ) ;
      row = kgGetTableRow ( Tbl ) ;
      rowbk = row;
      curpos = kgGetTableCurpos ( Tbl ) ;
      rcurpos = GetRealPos ( ) ;
      curbk = curpos;
      Slbak = StartLine;
      Elbak = EndLine;
      stchar = kgGetTableStartChar ( Tbl ) ;
      Dposition ( Slist , StartLine+row ) ;
      spos = StartLine+row -1;
//      printf ( "Row: %d %d %d\n" , rowbk , StartLine , curpos ) ;
      lptr = ( char * ) Getrecord ( Slist ) ;
      if ( lptr == NULL ) return 0;
 //     printf("%s\n",lptr+stchar);
      if ( ( ptmp = ( char * ) strstr ( lptr+rcurpos , spt ) ) != NULL ) {
//        loc = GetLength ( lptr+curpos , ptmp ) ;
          loc = GetLength ( lptr , ptmp ) -GetLength ( lptr , lptr+rcurpos ) ;
          npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
          strcpy ( npt , Buf ) ;
          spos = StartLine+row -1;
          Dreplace ( Slist , npt , spos ) ;
          WriteTbl ( ) ;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+curpos ) ;
          RETURN ( 0 ) ;
      }
      count = 1;
      if ( Count <= Nlines ) {
          while ( ( lptr = ( char * ) Getrecord ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  row += count;
                  npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
                  strcpy ( npt , Buf ) ;
                  spos = StartLine+row -1;
                  Dreplace ( Slist , npt , spos ) ;
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          row = rowbk;
          Resetlink ( Slist ) ;
          for ( k = 0;k <= rowbk;k++ ) {
              lptr = ( char * ) Getrecord ( Slist ) ;
              if ( lptr == NULL ) break;
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
                  strcpy ( npt , Buf ) ;
                  spos = StartLine+row -1;
                  Dreplace ( Slist , npt , spos ) ;
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( k ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
          }
      }
      else {
          while ( ( lptr = ( char * ) Getrecord ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  if ( EndLine+count <= Count ) {
                      StartLine += count;
                      EndLine += count;
                  }
                  else {
                      int offset = EndLine+count - Count;
                      EndLine = Count;
                      StartLine = EndLine -Nlines+1;
                      row+= offset;
                  }
                  npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
                  strcpy ( npt , Buf ) ;
                  spos = StartLine+row -1;
                  Dreplace ( Slist , npt , spos ) ;
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          Resetlink ( Slist ) ;
          count = 0;
          for ( k = 0;k < Slbak;k+= Nlines ) {
              for ( row = 0;row < Nlines;row++ ) {
                  lptr = ( char * ) Getrecord ( Slist ) ;
                  if ( lptr == NULL ) break;
                  if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                      loc = GetLength ( lptr , ptmp ) ;
                      StartLine = k+1;
                      EndLine = k+Nlines;
                      npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
                      strcpy ( npt , Buf ) ;
                      spos = StartLine+row -1;
                      Dreplace ( Slist , npt , spos ) ;
                      WriteTbl ( ) ;
                      kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                      RETURN ( 0 ) ;
                  }
              }
          }
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      Splash ( ( char * ) "Could not find" ) ;
      ReadTbl ( ) ;
      return ret;
  }
  void ScrollTablebutton5init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg
  }
  int ScrollTabletextbox2callback ( int cellno , int i , void *Tmp ) {
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
  static int MakeFileNames ( ) {
      char BaseName [ 200 ] ;
      kgExtractBaseName ( flname , BaseName ) ;
//      printf("BaseName: %s\n",BaseName);
      sprintf ( Bkup , ".%s.%d" , BaseName , getpid ( ) ) ;
      sprintf ( SaveFile , "%s.save.%d" , BaseName , getpid ( ) ) ;
//      printf("Bkup: %s\n",Bkup);
      remove ( Bkup ) ;
      remove ( SaveFile ) ;
      return 1;
  }
  int InitTable ( char *fl ) {
      char **Strs;
      char *cpt;
      DIALOG *D = ( DIALOG * ) Tbl->D;
      int nlines , k;
      kgSetGrpVisibility ( D , Mid , 1 ) ;
      kgSetWidgetVisibility ( V , 0 ) ;
      kgUpdateGrp ( D , Mid ) ;
      kgUpdateOn ( D ) ;
      flname = fl;
      Slist = Dreadfile ( flname ) ;
      MakeFileNames ( ) ;
      Strs = ( char ** ) Dlinktoarray ( Slist ) ;
      StartLine = EndLine = 1;
      E = Tbl->elmt;
      nlines = Tbl->ny;
      Nlines = Tbl->ny;
      if ( ( Strs == NULL ) || ( Strs [ 0 ] == NULL ) ) {
          cpt = ( char * ) malloc ( 2 ) ;
          strcpy ( cpt , "\n" ) ;
          Dadd ( Slist , cpt ) ;
          kgSetString ( Tbl , 1 , cpt ) ;
//          kgSetInt ( Tbl , 0 , 1 ) ;
          WriteLineNo ( 0 ) ;
          kgSetOnTableCell ( Tbl , 1 ) ;
          for ( k = 1;k < nlines; k++ ) {
              kgSetOffTableCell ( Tbl , k*2+1 ) ;
          }
          AddMode = 1;
          AddRow = 0;
      }
      else {
          k = 0;
          StartLine = 1;
          while ( Strs [ k ] != NULL ) {
              if ( k < nlines ) {
                  kgSetOnTableCell ( Tbl , k*2+1 ) ;
              }
              k++;
          }
          if ( k < nlines ) EndLine = k;
          else EndLine = nlines;
          while ( k < nlines ) {
              kgSetOffTableCell ( Tbl , k*2+1 ) ;
              k++;
          }
          WriteTbl ( ) ;
      }
      Count = Dcount ( Slist ) ;
      Resetlink ( Slist ) ;
      if ( Count <= Nlines ) kgSetWidgetVisibility ( V , 0 ) ;
      else {
          Vsize = ( double ) Nlines/Count*100;
          Vpos = 0;
          kgSetScrollLength ( V , Vsize ) ;
          kgSetScrollPos ( V , Vpos ) ;
      }
      kgUpdateWidget ( V ) ;
      kgUpdateWidget ( Tbl ) ;
      kgSetTableCursor ( Tbl , 1 ) ;
      kgSetDefaultAttnWidget ( D , Tbl ) ;
      kgUpdateOn ( D ) ;
      return 1;
  }
  static int SetupGrps ( ) {
      DIALOG *Tmp = ( DIALOG * ) Tbl->D;
      Mid = kgOpenGrp ( Tmp ) ;
      Opt = ( DIN * ) kgGetNamedWidget ( Tmp , ( char * ) "Optionals" ) ;
      kgAddtoGrp ( Tmp , Mid , kgGetNamedWidget ( Tmp , ( char * ) "Button1" ) ) ;
      kgAddtoGrp ( Tmp , Mid , kgGetNamedWidget ( Tmp , ( char * ) "Button2" ) ) ;
      SB = ( DIN * ) kgGetNamedWidget ( Tmp , ( char * ) "SearchButn" ) ;
      RB = ( DIN * ) kgGetNamedWidget ( Tmp , ( char * ) "Replace" ) ;
      kgAddtoGrp ( Tmp , Mid , SB ) ;
      kgAddtoGrp ( Tmp , Mid , RB ) ;
      kgAddtoGrp ( Tmp , Mid , Opt ) ;
      kgAddtoGrp ( Tmp , Mid , Tbl ) ;
      ST = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "SearchText" ) ;
      RT = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "Tbox2" ) ;
      kgAddtoGrp ( Tmp , Mid , ST ) ;
      kgAddtoGrp ( Tmp , Mid , RT ) ;
      kgAddtoGrp ( Tmp , Mid , V ) ;
      kgAddtoGrp ( Tmp , Mid , ST ) ;
      MT = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "MarkText" ) ;
      GB = ( DIN * ) kgGetNamedWidget ( Tmp , ( char * ) "Go" ) ;
      kgAddtoGrp ( Tmp , Mid , MT ) ;
      kgAddtoGrp ( Tmp , Mid , GB ) ;
      return 1;
  }
  int ScrollTabletextbox3callback ( int cellno , int i , void *Tmp ) {
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
      MarkPos = kgGetInt ( MT , 0 ) ;
      if ( MarkPos < 1 ) {
          MarkPos = 1;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
      }
      GotoMark ( ) ;
      kgUpdateOn ( Tmp ) ;
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
  int ScrollTablebutton6callback ( int butno , int i , void *Tmp ) {
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
      MarkPos = kgGetInt ( MT , 0 ) ;
      if ( MarkPos < 1 ) {
          MarkPos = 1;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
      }
      kgUpdateWidget ( MT ) ;
      GotoMark ( ) ;
      kgUpdateOn ( Tmp ) ;
      switch ( butno ) {
          case 1:
          break;
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
  void ScrollTablebutton6init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg
  }
  int ScrollTableinit ( void *Tmp ) {
  /***********************************
    Tmp :  Pointer to DIALOG
   ***********************************/
  /* you add any initialisation here */
      int ret = 1 , k;
      int nlines ;
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      char **Strs;
      char *cpt;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
//      flname = ( char * ) pt [ 0 ] ;
      Tbl = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "ScrollTable" ) ;
      V = ( DIV * ) kgGetNamedWidget ( D , ( char * ) "VertScroll" ) ;
      SetupGrps ( ) ;
      Slist = Dreadfile ( flname ) ;
      MakeFileNames ( ) ;
      BLS = Dopen();
      Strs = ( char ** ) Dlinktoarray ( Slist ) ;
      StartLine = EndLine = 1;
      E = Tbl->elmt;
      nlines = Tbl->ny;
      Nlines = Tbl->ny;
      if ( flname != NULL ) {
          if ( ( Strs == NULL ) || ( Strs [ 0 ] == NULL ) ) {
              cpt = ( char * ) malloc ( 2 ) ;
              strcpy ( cpt , "\n" ) ;
              Dadd ( Slist , cpt ) ;
              kgSetString ( Tbl , 1 , cpt ) ;
//          kgSetInt ( Tbl , 0 , 1 ) ;
              WriteLineNo ( 0 ) ;
              kgSetOnTableCell ( Tbl , 1 ) ;
              for ( k = 1;k < nlines; k++ ) {
                  kgSetOffTableCell ( Tbl , k*2+1 ) ;
              }
              AddMode = 1;
              AddRow = 0;
          }
          else {
              k = 0;
              StartLine = 1;
              while ( Strs [ k ] != NULL ) {
                  if ( k < nlines ) {
                      kgSetOnTableCell ( Tbl , k*2+1 ) ;
                  }
                  k++;
              }
              if ( k < nlines ) EndLine = k;
              else EndLine = nlines;
              while ( k < nlines ) {
                  kgSetOffTableCell ( Tbl , k*2+1 ) ;
                  k++;
              }
              WriteTbl ( ) ;
          }
          Count = Dcount ( Slist ) ;
          Resetlink ( Slist ) ;
          if ( Count <= Nlines ) kgSetWidgetVisibility ( V , 0 ) ;
          else {
              Vsize = ( double ) Nlines/Count*100;
              Vpos = 0;
              kgSetScrollLength ( V , Vsize ) ;
              kgSetScrollPos ( V , Vpos ) ;
              kgSetScrollMovement(V,(double)Nlines/Count*100.0);
          }
          kgUpdateWidget ( V ) ;
          kgUpdateWidget ( Tbl ) ;
          kgSetTableCursor ( Tbl , 1 ) ;
          kgSetDefaultAttnWidget ( Tmp , Tbl ) ;
      }
      Push();
      kgUpdateOn ( Tmp ) ;
      free ( Strs ) ;
      return ret;
  }
  int ScrollTablebutton2callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIN *B;
      int n , ret = 0 , row;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
      switch ( butno ) {
          case 1:
          ReadTbl ( ) ;
          Dwritefile ( Slist , SaveFile ) ;
          break;
          case 2:
//        printf("%s\n",flname);
          UpdateTbl();
          row = kgGetTableRow ( Tbl ) ;
          MarkPos=EndLine;
          kgSetInt(MT,0,MarkPos);
          kgUpdateWidget(MT);
#if 1
          if ( flname != NULL ) {
              int k;
              Dlink *bkup=NULL;
              bkup  = Pop();
              if(bkup == NULL) {
              sprintf ( Msg , "Sorry!! UNDO not possible; You may ABORT if needed" ) ;
              Splash ( Msg ) ;
              break;
              }
              Dempty(Slist);
              Slist = bkup;
              for ( k = 0;k < Nlines;k++ ) {
                  kgSetString ( Tbl , k*2 , ( char * ) "" ) ;
                  kgSetString ( Tbl , k*2+1 , ( char * ) "" ) ;
              }
              kgUpdateWidget ( Tbl ) ;
              kgUpdateOn ( Tbl->D ) ;
#if 0
              MarkPos = StartLine+kgGetTableRow ( Tbl ) ;
              kgSetInt ( MT , 0 , MarkPos ) ;
              kgUpdateWidget ( MT ) ;
#endif
              if ( (Slist==NULL)||( Count = Dcount ( Slist ) ) == 0 ) {
                  if(Slist != NULL) Dempty ( Slist ) ;
//                  Slist = Dreadfile ( flname ) ;
                    Slist = Dreadfile(SaveFile);
                    if(Dcount(Slist)==0) Slist = Dreadfile ( flname ) ;
              }
              Count = Dcount ( Slist ) ;
              if ( ( EndLine - StartLine +1 ) < Count ) {
                  EndLine = Count;
              }
              if ( EndLine >= Count ) {
                  EndLine = Count;
                  StartLine = EndLine-Nlines+1;
                  if ( StartLine < 1 ) StartLine = 1;
                  for ( k = 0;k < EndLine;k++ ) {
                      if ( k == Nlines ) break;
                      kgSetOnTableCell ( Tbl , k*2+1 ) ;
                  }
                  for ( k = EndLine;k < Nlines;k++ ) {
                      kgSetString ( Tbl , k*2 , ( char * ) "" ) ;
                      kgSetString ( Tbl , k*2+1 , ( char * ) "" ) ;
                      kgSetOffTableCell ( Tbl , k*2+1 ) ;
                  }
              }
              WriteTbl ( ) ;
              GotoMark ( ) ;
              if ( ( Count >= Nlines ) && ( StartLine > 1 ) ) row = Nlines-1;
              kgSetTableCursorPos ( Tbl , row*Tbl->nx+1 , 0 ) ;
              SetupVbar ( ) ;
              kgUpdateOn ( Tbl->D ) ;
          }
          else printf ( "flname== NULL\n" ) ;
#else
          SetupVbar ( ) ;
          WriteTbl ( ) ;
          kgUpdateOn ( Tbl->D ) ;
#endif
          break;
          case 3:
          kgSetGrpVisibility ( Tbl->D , Mid , 0 ) ;
          kgUpdateGrp ( Tbl->D , Mid ) ;
          kgSetWidgetVisibility ( Opt , 1 ) ;
          kgUpdateWidget ( Opt ) ;
          kgUpdateOn ( Tbl->D ) ;
          break;
          default:
          break;
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
  void ScrollTablebutton2init ( DIN *B , void *pt ) {
  }
  int ScrollTabletextbox1callback ( int cellno , int i , void *Tmp ) {
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
      SearchTbl();
      return ret;
  }
  int ScrollTabletextbox1callback_test ( int cellno , int i , void *Tmp ) {
  /*************************************************
   cellno: current cell counted along column strting with 0
           ie 0 to (nx*ny-1)
   i     : widget id starting from 0
   Tmp   : Pointer to DIALOG
   *************************************************/
      DIALOG *D;DIT *T;T_ELMT *e;
      int ret = 1;
      int curpos = kgGetTableCurpos ( Tbl ) ;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      char *spt = kgGetString ( Tbl , cellno ) ;
      D = ( DIALOG * ) Tmp;
      T = ( DIT * ) kgGetWidget ( Tmp , i ) ;
      e = T->elmt;
      strcpy ( Buf , spt ) ;
      free ( spt ) ;
      strcpy ( Buf1 , Buf+curpos ) ;
      Buf [ curpos ] = '\0';
      strcpy ( Buf , "\n" ) ;
      printf ( "%s%s" , Buf , Buf1 ) ;
      return ret;
  }
  static int GetLength ( char *s1 , char *s2 ) {
      int i = 0 , k = 0 , l;
      while ( s1+i != s2 ) {
#if 1
          if ( s1 [ i ] == '\t' ) {
              l = ( ( i ) /8+1 ) *8;
              k = l;
          }
          else k++;
#else
          k++;
#endif
          i++;
      }
      return k;
  }
 static int SearchTbl(){
      int k = 0 , loc , count;
      char *spt , *lptr , *ptmp;
      int row , curpos , stchar , rowbk , rcurpos;
      int Slbak , Elbak , curbk;
      DIALOG *D = ( DIALOG * ) Tbl->D;;
      void *Tmp =D;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      spt = ( char * ) kgGetString ( ST , 0 ) ;
      k = 0;
      while ( spt [ k ] == ' ' ) k++;
      if ( spt [ k ] < ' ' ) return 0;
//     printf("%s\n",spt+k);
      ReadTbl ( ) ;
      Count = Dcount ( Slist ) ;
      row = kgGetTableRow ( Tbl ) ;
      rowbk = row;
      curpos = kgGetTableCurpos ( Tbl ) ;
      rcurpos = GetRealPos ( ) ;
      curbk = curpos;
      Slbak = StartLine;
      Elbak = EndLine;
      stchar = kgGetTableStartChar ( Tbl ) ;
      Dposition ( Slist , StartLine+row ) ;
//      printf ( "Row: %d %d %d\n" , rowbk , StartLine , curpos ) ;
      lptr = ( char * ) Getrecord ( Slist ) ;
      if ( lptr == NULL ) return 0;
 //     printf("%s\n",lptr+stchar);
      if ( ( ptmp = ( char * ) strstr ( lptr+rcurpos+1 , spt ) ) != NULL ) {
          loc = GetLength ( lptr , ptmp ) -GetLength ( lptr , lptr+rcurpos ) ;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+curpos ) ;
          RETURN ( 0 ) ;
      }
      count = 1;
      if ( Count <= Nlines ) {
          while ( ( lptr = ( char * ) Getrecord ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  row += count;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          row = rowbk;
          Resetlink ( Slist ) ;
          for ( k = 0;k <= rowbk;k++ ) {
              lptr = ( char * ) Getrecord ( Slist ) ;
              if ( lptr == NULL ) break;
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  kgSetTableCursorPos ( Tbl , ( k ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
          }
      }
      else {
          while ( ( lptr = ( char * ) Getrecord ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  if ( EndLine+count <= Count ) {
                      StartLine += count;
                      EndLine += count;
                  }
                  else {
                      int offset = EndLine+count - Count;
                      EndLine = Count;
                      StartLine = EndLine -Nlines+1;
                      row+= offset;
                  }
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          Resetlink ( Slist ) ;
          count = 0;
          for ( k = 0;k < Slbak;k+= Nlines ) {
              for ( row = 0;row < Nlines;row++ ) {
                  lptr = ( char * ) Getrecord ( Slist ) ;
                  if ( lptr == NULL ) break;
                  if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                      loc = GetLength ( lptr , ptmp ) ;
                      StartLine = k+1;
                      EndLine = k+Nlines;
                      WriteTbl ( ) ;
                      kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                      RETURN ( 0 ) ;
                  }
              }
          }
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      Splash ( ( char * ) "Could not find" ) ;
      return 1;
  }
  int ScrollTablebutton3callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIN *B;
      int n , ret = 0;
      int k = 0 , loc , count;
      char *spt , *lptr , *ptmp;
      int row , curpos , stchar , rowbk , rcurpos;
      int Slbak , Elbak , curbk;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
      spt = ( char * ) kgGetString ( ST , 0 ) ;
      k = 0;
      while ( spt [ k ] == ' ' ) k++;
      if ( spt [ k ] < ' ' ) return ret;
//     printf("%s\n",spt+k);
      ReadTbl ( ) ;
      Count = Dcount ( Slist ) ;
      row = kgGetTableRow ( Tbl ) ;
      rowbk = row;
      curpos = kgGetTableCurpos ( Tbl ) ;
      rcurpos = GetRealPos ( ) ;
      curbk = curpos;
      Slbak = StartLine;
      Elbak = EndLine;
      stchar = kgGetTableStartChar ( Tbl ) ;
      Dposition ( Slist , StartLine+row ) ;
//      printf ( "Row: %d %d %d\n" , rowbk , StartLine , curpos ) ;
      lptr = ( char * ) Getrecord ( Slist ) ;
      if ( lptr == NULL ) return 0;
 //     printf("%s\n",lptr+stchar);
      if ( ( ptmp = ( char * ) strstr ( lptr+rcurpos+1 , spt ) ) != NULL ) {
          loc = GetLength ( lptr , ptmp ) -GetLength ( lptr , lptr+rcurpos ) ;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+curpos ) ;
          RETURN ( 0 ) ;
      }
      count = 1;
      if ( Count <= Nlines ) {
          while ( ( lptr = ( char * ) Getrecord ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  row += count;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          row = rowbk;
          Resetlink ( Slist ) ;
          for ( k = 0;k <= rowbk;k++ ) {
              lptr = ( char * ) Getrecord ( Slist ) ;
              if ( lptr == NULL ) break;
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  kgSetTableCursorPos ( Tbl , ( k ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
          }
      }
      else {
          while ( ( lptr = ( char * ) Getrecord ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  if ( EndLine+count <= Count ) {
                      StartLine += count;
                      EndLine += count;
                  }
                  else {
                      int offset = EndLine+count - Count;
                      EndLine = Count;
                      StartLine = EndLine -Nlines+1;
                      row+= offset;
                  }
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          Resetlink ( Slist ) ;
          count = 0;
          for ( k = 0;k < Slbak;k+= Nlines ) {
              for ( row = 0;row < Nlines;row++ ) {
                  lptr = ( char * ) Getrecord ( Slist ) ;
                  if ( lptr == NULL ) break;
                  if ( ( ptmp = ( char * ) strstr ( lptr , spt ) ) != NULL ) {
                      loc = GetLength ( lptr , ptmp ) ;
                      StartLine = k+1;
                      EndLine = k+Nlines;
                      WriteTbl ( ) ;
                      kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                      RETURN ( 0 ) ;
                  }
              }
          }
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      Splash ( ( char * ) "Could not find" ) ;
//      ReadTbl();
      return ret;
  }
  void ScrollTablebutton3init ( DIN *B , void *pt ) {
  }
  static int ReadInFile ( char *Infile ) {
      Dlink *Rlist = Dreadfile ( Infile ) ;
      void *ptmp;
      int count = Count , row;
      if ( Rlist != NULL ) {
          ReadTbl ( ) ;
          row = kgGetTableRow ( Tbl ) ;
          Dposition ( Slist , StartLine+row ) ;
          Resetlink ( Rlist ) ;
          while ( ( ptmp = Getrecord ( Rlist ) ) != NULL ) Dadd ( Slist , ptmp ) ;
          Dfree ( Rlist ) ;
          if ( count < Nlines ) SetupTbl ( ) ;
          SetupVbar ( ) ;
          WriteTbl ( ) ;
          kgSetTableCursorPos ( Tbl , row *Tbl->nx+1 , 0 ) ;
          kgUpdateOn ( Tbl->D ) ;
      }
      return 1;
  }
  static int WriteToFile ( char *fpt ) {
      if ( fpt != NULL ) {
          Dlink *Wlist = Dopen ( ) ;
          char *dpt , *spt;
          int endpos = StartLine+kgGetTableRow ( Tbl ) ;
          int k , s , e;
//          printf("File : %s\n",fpt);
          ReadTbl ( ) ;
          if ( endpos >= MarkPos ) {
              s = MarkPos;
              e = endpos;
          }
          else {
              s = endpos;
              e = MarkPos;
          }
          sprintf ( Buf1 , "Copy lines %d to %d ?" , s , e ) ;
          if ( ! kgQstMenu ( Tbl->D , 10 , 100 , Buf1 , 1 ) ) return 0;
          Dposition ( Slist , s ) ;
          for ( k = s;k <= e;k++ ) {
              spt = ( char * ) Getrecord ( Slist ) ;
              if ( spt == NULL ) break;
              dpt = ( char * ) malloc ( strlen ( spt ) +1 ) ;
              strcpy ( dpt , spt ) ;
              Dadd ( Wlist , dpt ) ;
          }
          Dwritefile ( Wlist , fpt ) ;
          Dempty ( Wlist ) ;
      }
      return 1;
  }
  static int CutToFile ( char *fpt ) {
      int k;
      if ( fpt != NULL ) {
          Dlink *Wlist = Dopen ( ) ;
          char *dpt , *spt;
          int endpos = StartLine+kgGetTableRow ( Tbl ) ;
          int k , s , e , lines;
//          printf("File : %s\n",fpt);
          ReadTbl ( ) ;
          if ( endpos >= MarkPos ) {
              s = MarkPos;
              e = endpos;
          }
          else {
              s = endpos;
              e = MarkPos;
          }
          sprintf ( Buf1 , "Cut(&copy) lines %d to %d ?" , s , e ) ;
          if ( ! kgQstMenu ( Tbl->D , 10 , 100 , Buf1 , 1 ) ) return 0;
          Dposition ( Slist , s ) ;
          for ( k = s;k <= e;k++ ) {
              spt = ( char * ) Dpick ( Slist ) ;
              if ( spt == NULL ) break;
              Dadd ( Wlist , spt ) ;
          }
          Dwritefile ( Wlist , fpt ) ;
          lines = Dcount ( Wlist ) ;
          Dempty ( Wlist ) ;
          Count = Dcount ( Slist ) ;
          if ( EndLine > Count ) {
              EndLine = Count;
              StartLine = EndLine -Nlines+1;
              if ( StartLine < 1 ) StartLine = 1;
          }
          for ( k = EndLine;k < Nlines;k++ ) {
              kgSetOffTableCell ( Tbl , k*2+1 ) ;
              kgSetString ( Tbl , k*2 , ( char * ) "" ) ;
              kgSetString ( Tbl , k*2+1 , ( char * ) "" ) ;
          }
      }
      WriteTbl ( ) ;
      return 1;
  }
  int ScrollTablebutton4callback ( int butno , int i , void *Tmp ) {
  /***********************************
    butno : selected item (1 to max_item)
i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIN *B;
      int n , ret = 0 , pos;
      char Infile [ 300 ] ;
      char *fpt;
      int row , k , count , spos , slold;
      char *cpt , *npt;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
      row = kgGetTableRow ( Tbl ) ;
      switch ( butno ) {
          case 1:
          Infile [ 0 ] = '\0';
          if ( kgFolderBrowser ( NULL , 100 , 100 , Infile , ( char * ) "*" ) ) {
              kgSkipEvents ( Tmp ) ;
              pos = kgGetTableRow ( Tbl ) +StartLine;
              ReadInFile ( Infile ) ;
              sprintf ( Msg , "Read in %s at %d" , Infile , pos ) ;
              Splash ( Msg ) ;
          }
          break;
          case 3:
          fpt = RunGetFileName ( NULL , NULL ) ;
          if ( WriteToFile ( fpt ) ) {
              if ( fpt != NULL ) {
                  sprintf ( Msg , "Wrote to  %s" , fpt ) ;
                  Splash ( Msg ) ;
                  free ( fpt ) ;
              }
          }
          break;
          case 2:
          MarkPos = kgGetTableRow ( Tbl ) +StartLine;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
          kgUpdateOn ( Tbl->D ) ;
#if 0
// sprintf ( Msg , "Marked Line: %d" , MarkPos ) ;
// Splash ( Msg ) ;
#endif
          break;
          case 4:
          if ( CutToFile ( Bkup ) ) {
              SetupVbar ( ) ;
              GotoMark ( ) ;
              kgUpdateOn ( Tmp ) ;
          }
          break;
          case 5:
          WriteToFile ( Bkup ) ;
          break;
          case 6:
          ReadInFile ( Bkup ) ;
          break;
          case 7:
          slold = StartLine;
          if ( StartLine+row >= Count ) break;
          Dposition ( Slist , StartLine+row ) ;
          cpt = ( char * ) Getrecord ( Slist ) ;
          strcpy ( Buf , cpt ) ;
          k = 0;while ( Buf [ k ] != '\n' ) k++;Buf [ k ] = '\0';
          Dposition ( Slist , StartLine+row+1 ) ;
          cpt = ( char * ) Getrecord ( Slist ) ;
          strcat ( Buf , cpt ) ;
          npt = ( char * ) malloc ( strlen ( Buf ) +1 ) ;
          strcpy ( npt , Buf ) ;
          spos = StartLine+row ;
          Dreplace ( Slist , npt , spos-1 ) ;
          WriteTbl ( ) ;
          DeleteLine ( row+1 ) ;
          if ( StartLine < slold ) row++;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , 0 ) ;
          kgUpdateOn ( Tmp ) ;
          break;
          case 8:
          kgSetWidgetVisibility ( Opt , 0 ) ;
          kgUpdateWidget ( Opt ) ;
          kgSetGrpVisibility ( Tmp , Mid , 1 ) ;
          kgUpdateGrp ( Tmp , Mid ) ;
          kgSetAttnWidget ( Tmp , Tbl ) ;
          kgUpdateOn ( Tmp ) ;
          break;
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
  void ScrollTablebutton4init ( DIN *B , void *pt ) {
  }
  int ScrollTablecleanup ( void *Tmp ) {
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
  int ModifyScrollTable ( void *Tmp , int GrpId ) {
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
 /* pt[0] is inputs given by caller */
      DIA *d;
      int i , n;
      int xo , yo , xl , yl;
      int xres , yres;
      d = D->d;
      D->NoTabProcess = 1;
      if ( pt [ 0 ] == NULL ) {
          flname = Runinitkit ( NULL , NULL ) ;
      }
      else flname = ( char * ) pt [ 0 ] ;
      i = 0;while ( d [ i ] .t != NULL ) {;
          i++;
      };
      n = 1;
      sprintf(Msg,"Kit Ver 1.0: File: %s",flname);
      strcpy ( D->name , Msg ) ; /* Dialog name you may change */
      DB = ( DIL * ) kgGetNamedWidget ( D , ( char * ) "SplButn" ) ;
      xl = DB->x2 -DB->x1;
      yl = DB->y2 -DB->y1;
      kgDisplaySize ( & xres , & yres ) ;
      xo = ( D->xl-xl ) /2;
      DB->x1 = xo;
      DB->x2 = xo+xl;
      B1 = ( DIN * ) kgGetNamedWidget ( D , ( char * ) "Button1" ) ;
      xl = B1->x2 -B1->x1;
      xo = D->xl-xl-25;
      B1->x1 = xo;
      B1->x2 = xo+xl;
      Buf [ 0 ] = '\0';
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
  int ScrollTableCallBack ( void *Tmp , void *tmp ) {
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
  int ScrollTableResizeCallBack ( void *Tmp ) {
  /***********************************
    Tmp :  Pointer to DIALOG
   ***********************************/
      int ret = 0 , k;
      int xres , yres , dx , dy;
      int xo , yo , xl , yl , Fz1 , Fz2i , nchr;
      static int Xl = -1 , Yl = -1 , Fz = -1 , By1;
      char Fmt [ 8 ] ;
      DIALOG *D;
      T_ELMT *elmt;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      kgGetWindowSize ( D , & xres , & yres ) ;
      dx = xres - D->xl;
      dy = yres - D->yl;
      if ( Xl == -1 ) {
          Xl = D->xl;
          Yl = D->yl;
          Fz = Tbl->FontSize;
          By1 = B1->y1;
      }
  /* extra code */
      D->xl = xres;
      D->yl = yres;
      xl = DB->x2 -DB->x1;
      yl = DB->y2 -DB->y1;
      xo = ( D->xl-xl ) /2;
      DB->x1 = xo;
      DB->x2 = xo+xl;
      DB->y1 = D->yl- yl -2;
      DB->y2 = DB->y1 + yl;
      xl = B1->x2 -B1->x1;
      yl = B1->y2 -B1->y1;
      if ( D->xl < Xl ) B1->y1 = 6;
      else B1->y1 = By1;
      B1->y2 = B1->y1+yl;
      xo = D->xl-xl-10;
      B1->x1 = xo;
      B1->x2 = xo+xl;
      Tbl->x2 = xres - 40;
      Tbl->y2 = yres - 40;
      Fz1 = ( Tbl->y2 - Tbl->y1-4 ) /48;
      if ( Fz1 > 12 ) Fz1 = 10;
      nchr = ( Tbl->x2 - Tbl->x1 ) /Fz1 -11;
      sprintf ( Fmt , "%%%ds" , nchr ) ;
      elmt = ( T_ELMT * ) Tbl->elmt;
      for ( k = 0;k < Tbl->ny;k++ ) {
          strcpy ( elmt [ k*Tbl->nx+1 ] .fmt , Fmt ) ;
      }
      Tbl->FontSize = Fz1;
      Tbl->width = 20;
      xl = V->x2 - V->x1;
      yl = V->y2 - V->y1;
      V->x1 = Tbl->x2+7;
      V->x2 = V->x1 + xl;
      V->y2 = Tbl->y2;
      yl = MT->y2 -MT->y1;
      MT->y1 = D->yl-35;
      MT->y2 = MT->y1+yl;
      yl = GB->y2 - GB->y1;
      GB->y1 = D->yl-36;
      GB->y2 = GB->y1+yl;
      kgRedrawDialog ( D ) ;
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
  int ScrollTableWaitCallBack ( void *Tmp ) {
  /***********************************
    Tmp :  Pointer to DIALOG
    Called while waiting for event
    return value 1 will close the the UI
   ***********************************/
      int ret = 0;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      return ret;
  }
