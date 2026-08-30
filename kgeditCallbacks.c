#include <kulina.h>
#include "kgeditCallbacks.h"
#include "simages.c"

static void *Args=NULL,*Rets=NULL;

static DIAINTR *It = NULL;


static MODINTERFACE ModFuns[] = { 
    (MODINTERFACE) NULL 
};
static Dlink *ModuleList=NULL;
int GetFont(void *,int xo,int yo);
void *RunSbox(void *,void *);
void *RunSetup(void *,void *);
void *kgGetFontString(void *,void *);
void *RunMsg(void *parent ,void *args);
  static DIT *Tbl;
  static T_ELMT *E;
  static Dlink *Slist;
  static DIV *V;
  static DIL *DB;
  static DIN *B1;
  static int Mid;
  static DIN *Opt;
  static DIN *GB;
  static DIN *PB;
  static DIT *MT;
  static int NBK = 10;  //Backup Limit
  static int Tblrow;
  static int DifPos = -1;
  static int SerDir = 1;
  static int StartLine = 0 , EndLine = 0 , Nlines , Count;
  static int TblRow;
  static int AddMode = 0 , AddRow = -1;
  static int B1x , B1y;
  static double Vsize , Vpos;
  static int MarkPos = 1 , LastPos = 1;
  static int ExpandTab = 0 , Tabp = 8;
  static char *vi = NULL , *vs = NULL;
  static int Xl = -1 , Yl = -1 , Fz = -1 , By1 , DefWidth;
  static int nydef = -1;
  char *flname = NULL;
  static char Msg [ 200 ] ;
  static char Bkup [ 300 ] ;
  static char SaveFile [ 300 ] ;
  static char Buf [ 2000 ] , Buf1 [ 2000 ] ;
  void *RunGetFileName ( void *parent , void *args ) ;
  void *RunGetMarkPos ( void *parent , void *args ) ;
  void ModifykgeditGc ( void *Tmp ) ;
  static int GetLength ( char *s1 , char *s2 ) ;
  static int GetRealPos ( ) ;
  void * Runinitkit ( void *, void* ) ;
  void *RunSetup ( void *parent , void *args ) ;
  static int SearchTbl ( ) ;
  static int SearchTblRev ( ) ;
  static int WriteTblRow ( int row ) ;
  static char *SearchStr ( char *str , char* ptn ) ;
  static int Splash ( char *Msg ) ;
  static Dlink *BLS = NULL;
  static Dlink *DLS = NULL;
  static Dlink *Blist = NULL;
  static Dlink *Llist = NULL;
  static char SrString[300],ReString[300];
  typedef struct _posvec {
      int Loc;
      int Start;
      int Nlines;
  } POSVEC;
  static POSVEC *lpt;
  int LocPush ( ) {
      POSVEC *pt;
      pt = ( POSVEC * ) malloc ( sizeof ( POSVEC ) ) ;
      if ( Llist == NULL ) Llist = Dopen ( ) ;
      pt->Loc = kgGetTableRow ( Tbl ) ;
      pt->Start = StartLine;
      pt->Nlines = Tbl->ny;
      Dpush ( Llist , pt ) ;
      return 1;
  }
  int LocPop ( ) {
      POSVEC *pt;
      int Nlinesorg;
      int size ;
      if ( Llist == NULL ) LocPush ( ) ;
      pt = Dpop ( Llist ) ;
      if ( pt == NULL ) {
          pt = ( POSVEC * ) malloc ( sizeof ( POSVEC ) ) ;
          pt->Loc = kgGetTableRow ( Tbl ) ;
          pt->Start = StartLine;
          pt->Nlines = Tbl->ny;
      }
      TblRow = pt->Loc ;
      StartLine = pt->Start;
      Nlinesorg = pt->Nlines;
      Nlines = Tbl->ny;
      if ( TblRow >= Nlines ) {
          size = EndLine -StartLine +1;
          StartLine = StartLine + TblRow;
          TblRow = 0;
      }
      EndLine = StartLine +Nlines -1;
      if ( EndLine > Count ) {
          EndLine = Count;
      }
      size = EndLine -StartLine +1;
      while ( ( Count >= Nlines ) && ( size < Nlines ) ) {
          StartLine--;
          TblRow++;
          EndLine = StartLine +Nlines -1;
          if ( EndLine > Count ) {
              EndLine = Count;
          }
          size = EndLine -StartLine +1;
      }
  //printf("Pop: %d %d %d\n",StartLine,EndLine,TblRow);
      free ( pt ) ;
      return 1;
  }
#define RETURN(n) {\
   Vpos = ( double ) ( StartLine-1 ) *100.0/Count;\
       ReadTbl ( ) ;\
       kgSetScrollPos ( V , Vpos ) ;\
       kgUpdateWidget ( V ) ;\
       kgUpdateOn ( Tmp ) ;\
       kgSetAttnWidget ( Tmp , Tbl ) ;\
       return ( n ) ;\
   }
  static int Strcmp ( char *s1 , char *s2 ) {
      int k;
      if ( ( s1 == NULL ) && ( s2 == NULL ) ) return 0;
      if ( ( s1 == NULL ) || ( s2 == NULL ) ) return 1;
      k = 0;
      while ( s1 [ k ] != '\0' ) {
          if ( s2 [ k ] == '\0' ) {
//        printf("%s %s\n",s1,s2);
              return 1;
          }
          if ( s1 [ k ] != s2 [ k ] ) {
//           printf("1: %d %di :%d\n",s1[k],s2[k],k);
//           printf("1: %s %s\n",s1,s2);
              return 1;
          }
          k++;
      }
      if ( s2 [ k ] != '\0' ) return 1;
      else return 0;
  }
  static int PositionAt ( int pos ) {
      Nlines = Tbl->ny;
      StartLine = pos -Nlines/2;
      if ( StartLine < 1 ) StartLine = 1;
      EndLine = StartLine +Nlines -1;
      if ( EndLine > Count ) {
          EndLine = Count;
          StartLine = EndLine -Nlines+1;
          if ( StartLine < 1 ) StartLine = 1;
      }
      Tblrow = pos -StartLine;
      return Tblrow;
  }
  static int comparerec ( void *r1 , void *r2 ) {
      if ( Strcmp ( ( char * ) r1 , ( char * ) r2 ) == 0 ) return 1;
      else {
          return 0;
      }
  }
  static int Compare ( void ) {
      int ret = 0 , k;
      char *r1 , *r2;
      Dlink *bk = ( Dlink * ) Dpop ( BLS ) ;
      if ( bk == NULL ) return 0;
      ret = Dcomplist ( Slist , bk , comparerec ) ;
      Dpush ( BLS , bk ) ;
      return ret;
  }
  static int CheckLists ( Dlink *bk ) {
      int ret = 0 , k;
      char *r1 , *r2;
      DifPos = -1;
      if ( bk == NULL ) return 0;
      Resetlink ( Slist ) ;
      Resetlink ( bk ) ;
      k = 0 ;
      while ( ( r1 = ( char * ) Getrecord ( Slist ) ) != NULL ) {
          if ( ( r2 = ( char * ) Getrecord ( bk ) ) == NULL ) {
              DifPos = k+1;
              return 0;
          }
          if ( Strcmp ( r1 , r2 ) != 0 ) {
              DifPos = k+1;
              return 0;
          }
          k++;
      }
      r2 = ( char * ) Getrecord ( bk ) ;
      if ( r2 != NULL ) {
          DifPos = k;
          return 0;
      }
      DifPos = -1;
      return 1;
  }
  static int Checkbkup ( Dlink *bk ) {
      int ret = 0;
      if ( bk == NULL ) return 0;
#if 0
      ret = Dcomplist ( Slist , bk , comparerec ) ;
#else
      ret = CheckLists ( bk ) ;
#endif
//     printf("Checkbkup : %d\n",DifPos);
      return ret;
  }
  static void *CopyRec ( void *bf ) {
      char *s = ( char * ) bf , *d;
      d = ( char * ) malloc ( strlen ( s ) +1 ) ;
      strcpy ( d , s ) ;
      return d;
  }
  static int Push ( ) {
      int count;
      int *dpt = NULL;
      if(NBK == 0 ) return 0;
      if ( Compare ( ) ) return 0;
      Dlink *Bk = Dnewlist ( Slist , CopyRec ) ;
      Dpush ( BLS , Bk ) ;
      dpt = ( int * ) malloc ( sizeof ( int * ) *5 ) ;
      dpt [ 0 ] = 1;
      dpt [ 1 ] = StartLine;
      dpt [ 2 ] = EndLine;
      dpt [ 3 ] = kgGetTableRow ( Tbl ) ;
      dpt [ 4 ] = MarkPos;
//   printf ("Push: %d %d %d %d\n",StartLine,EndLine,dpt[3],MarkPos);
      Dpush ( DLS , dpt ) ;
      count = Dcount ( BLS ) ;
//   printf("Pushed: count= %d\n",count);
      if ( count > NBK ) {
          Dend ( BLS ) ;
          Bk = ( Dlink * ) Dpick ( BLS ) ;
          Dempty ( Bk ) ;
          Dend ( DLS ) ;
          Ddelete ( DLS ) ;
      }
      return 1;
  }
  static Dlink *Pop ( ) {
      Dlink *bk = ( Dlink * ) Dpop ( BLS ) ;
      int *dpt;
      POSVEC *lpt;
      dpt = ( int * ) Dpop ( DLS ) ;
      if ( bk == NULL ) return NULL;
      while ( Checkbkup ( bk ) ) {
          if ( Dcount ( BLS ) == 0 ) {
              Dpush ( BLS , bk ) ;
              Dpush ( DLS , dpt ) ;
              return NULL;
          }
          else {Dempty ( bk ) ; free ( dpt ) ;}
          bk = ( Dlink * ) Dpop ( BLS ) ;
          dpt = ( int * ) Dpop ( DLS ) ;
          if ( bk == NULL ) return NULL;
      }
      if ( Dcount ( BLS ) == 0 ) {
          Dpush ( BLS , Dnewlist ( bk , CopyRec ) ) ;
#if 0
          MarkPos = dpt [ 4 ] ;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
#endif
          Count = Dcount ( bk ) ;
          if ( MarkPos > Count ) MarkPos = Count;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
          PositionAt ( DifPos ) ;
          Dpush ( DLS , dpt ) ;
          return bk;
      }
      Count = Dcount ( bk ) ;
      PositionAt ( DifPos ) ;
      free ( dpt ) ;
      return bk;
  }
  static int CleanupLinks ( ) {
      Dlink *bk = ( Dlink * ) Dpop ( BLS ) ;
      int *dpt;
      POSVEC *lpt;
      Dempty(DLS);
      DLS=Dopen();
      while ( bk != NULL ){
        Dempty(bk);
        bk=NULL;
        bk =( Dlink * ) Dpop ( BLS ) ; 
      }
      DifPos=1;
      PositionAt ( DifPos ) ;
      return 1;
  }
  static int Splash ( char *Msg ) {
//    kgSplashMessage ( Tbl->D , 50 , 100 , 400 , 25 , Msg , 23 , 0 , 15 ) ;
      kgMessageSplash(Tbl->D,Msg);
      return 1;
  }
  static int SetupVbar ( ) {
      Count = Dcount ( Slist ) ;
      if ( Count > Nlines ) {
          kgSetWidgetVisibility ( V , 1 ) ;
          Vsize = ( double ) Nlines/Count*100.0;
          Vpos = ( double ) ( StartLine-1 ) /Count*100.0;
          kgSetScrollLength ( V , Vsize ) ;
          kgSetScrollPos ( V , Vpos ) ;
      }
      else kgSetWidgetVisibility ( V , 0 ) ;
      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int SetupTbl ( ) {
      int k;
      Nlines = Tbl->ny;
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
          if ( EndLine == Count ) {
              StartLine = EndLine-Nlines+1;
          }
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
//      printf("%d : %s\n" , StartLine+row ,BUFF);
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
      char Buf [ 5000 ] ;
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
                      l = ( k/Tabp+1 ) *Tabp;
                      while ( k < l ) Buf [ k++ ] = ' ';
                  }
                  else {
                      l = ( k/Tabp+1 ) *Tabp;
                      Buf [ k++ ] = cpt [ j ] ;
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
  static int WriteTblRow ( int row ) {
      int n = ( EndLine -StartLine +1 ) ;
      int i , j , k , l;
      char *cpt , *spt;
      char Buf [ 5000 ] ;
      Resetlink ( Slist ) ;
      Dposition ( Slist , StartLine+row ) ;
      i = row;
      {
          cpt = ( char * ) Getrecord ( Slist ) ;
          if ( cpt == NULL ) {
              fprintf ( stderr , "Cpt= NULL, Start: %d End:%d\n" , StartLine , EndLine ) ;
              fflush ( stderr ) ;
              return 0;
          }
          j = 0;k = 0;
          while ( ( cpt [ j ] >= ' ' ) || ( cpt [ j ] == '\t' ) ) {
              if ( cpt [ j ] != '\t' ) Buf [ k++ ] = cpt [ j ] ;
              else {
                  if ( ExpandTab ) {
                      l = ( k/Tabp+1 ) *Tabp;
                      while ( k < l ) Buf [ k++ ] = ' ';
                  }
                  else {
                      l = ( k/Tabp+1 ) *Tabp;
                      Buf [ k++ ] = cpt [ j ] ;
                      while ( k < l ) Buf [ k++ ] = 127;
                  }
              }
              j++;
          }
          Buf [ k ] = '\0';
          kgSetString ( Tbl , i*2+1 , Buf ) ;
          WriteLineNo ( i ) ;
          kgPrintTableCell ( Tbl , i*2 ) ;
          kgPrintTableCell ( Tbl , i*2+1 ) ;
//          printf("%d : %s\n",i,Buf);
      }
      return 1;
  }
  static int ReadTbl ( void ) {
      int n = ( EndLine -StartLine +1 ) ;
      int i , j , k;
      char *cpt , *spt;
      Push ( ) ;
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
//                printf("Got 127\n");
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
//      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int AddStringAtRow ( char *Buf ) {
      char *buf;
      int row = kgGetTableRow ( Tbl ) ;
      ReadTbl ( ) ;
      Dposition ( Slist , StartLine+row ) ;
      buf = ( char * ) malloc ( strlen ( Buf ) +1 ) ;
      strcpy ( buf , ( char * ) Buf ) ;
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
//      kgUpdateWidget ( V ) ;
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
//      kgUpdateWidget ( V ) ;
      return 1;
  }
  static int DeleteLine ( int row ) {
      char *buf;
 //     ReadTbl ( ) ;
//      printf("StartLine: %d:%d\n",StartLine,EndLine);
      Dposition ( Slist , StartLine+row ) ;
      Ddelete ( Slist ) ;
      Count = Dcount ( Slist ) ;
      if ( EndLine > Count ) {
          EndLine = Count;
          if ( Count > Nlines ) row++;
          if ( row >= Nlines ) row = Nlines-1;
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
      if ( MarkPos > Count ) {
          MarkPos = Count;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
      }
//      kgUpdateWidget ( V ) ;
      return row;
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
  static int ReadInLink ( Dlink *Rlist ) {
      void *ptmp;
      int count = Count , row , rcount = 0 , shift = 0;
      if ( Rlist != NULL ) {
          row = kgGetTableRow ( Tbl ) ;
          Dposition ( Slist , StartLine+row ) ;
          Resetlink ( Rlist ) ;
          rcount = Dcount ( Rlist ) ;
          Resetlink ( Rlist ) ;
          while ( ( ptmp = Getrecord ( Rlist ) ) != NULL ) Dadd ( Slist , ptmp ) ;
          Dfree ( Rlist ) ;
          if ( count < Nlines ) shift = Nlines-count;
          Count = Dcount ( Slist ) ;
          count = Count;
          if ( count <= Nlines ) {
              SetupTbl ( ) ;
              WriteTbl ( ) ;
              kgSetTableCursorPos ( Tbl , ( rcount+row ) *Tbl->nx+1 , 0 ) ;
          }
          else {
              StartLine += rcount;
              EndLine += rcount;
              if ( shift > 0 ) {
                  StartLine -= shift;
              }
              SetupTbl ( ) ;
              WriteTbl ( ) ;
              kgSetTableCursorPos ( Tbl , ( shift+row ) *Tbl->nx+1 , 0 ) ;
          }
          kgUpdateOn ( Tbl->D ) ;
      }
      return 1;
  }
  static int ReadInLink_org ( Dlink *Rlist ) {
      void *ptmp;
      int count = Count , row , rcount = 0;
      if ( Rlist != NULL ) {
          row = kgGetTableRow ( Tbl ) ;
          Dposition ( Slist , StartLine+row ) ;
          Resetlink ( Rlist ) ;
          rcount = Dcount ( Rlist ) ;
          Resetlink ( Rlist ) ;
          while ( ( ptmp = Getrecord ( Rlist ) ) != NULL ) Dadd ( Slist , ptmp ) ;
          Dfree ( Rlist ) ;
          Count = Dcount ( Slist ) ;
          count = Count;
          if ( count < Nlines ) {
              SetupTbl ( ) ;
              WriteTbl ( ) ;
              kgSetTableCursorPos ( Tbl , ( rcount+row ) *Tbl->nx+1 , 0 ) ;
          }
          else {
              StartLine += rcount;
              EndLine += rcount;
              SetupTbl ( ) ;
              WriteTbl ( ) ;
              kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , 0 ) ;
          }
          kgUpdateOn ( Tbl->D ) ;
      }
      return 1;
  }
  int ProcessClip ( DIALOG *D , char *str ) {
      char *pt , lchar , ch , *buf;;
      int i , n , Okay = 0 , ln;
      Dlink *L;
      if ( str == NULL ) return 0;
#if 0 // Not needed
      {
          i = 0;
          while ( str [ i ] != '\0' ) {
              if ( str [ i ] == '\n' ) {Okay = 1;break;}
              i++;
          }
          if ( Okay == 0 ) {
              free ( str ) ;
              str = kgGetPrimary ( D ) ;
          }
      }
#endif
      ln = strlen ( str ) ;
      lchar = str [ ln ] ;
      i = 0;
      pt = str;
      L = Dopen ( ) ;
      while ( str [ i ] != '\0' ) {
          if ( str [ i ] == '\n' ) {
              ch = str [ i+1 ] ;
              str [ i+1 ] = '\0';
              buf = ( char * ) malloc ( strlen ( pt ) +1 ) ;
              strcpy ( buf , pt ) ;
              Dadd ( L , buf ) ;
              str [ i+1 ] = ch;
              pt = str+i+1;
          }
          i++;
      }
      if ( lchar != '\n' ) {
          buf = ( char * ) malloc ( strlen ( pt ) +2 ) ;
          strcpy ( buf , pt ) ;
          strcat ( buf , "\n" ) ;
          Dadd ( L , buf ) ;
      }
      ReadInLink ( L ) ;
      return 1;
  }
  static int ReadInFile ( char *Infile ) {
      Dlink *Rlist = Dreadfile ( Infile ) ;
      void *ptmp;
      int count = Count , row , rcount , shift = 0;
      if ( Rlist != NULL ) {
          ReadTbl ( ) ;
          row = kgGetTableRow ( Tbl ) ;
          Dposition ( Slist , StartLine+row ) ;
          Resetlink ( Rlist ) ;
          rcount = Dcount ( Rlist ) ;
          Resetlink ( Rlist ) ;
          while ( ( ptmp = Getrecord ( Rlist ) ) != NULL ) Dadd ( Slist , ptmp ) ;
          Dfree ( Rlist ) ;
          if ( count < Nlines ) shift = Nlines-count;
          Count = Dcount ( Slist ) ;
          count = Count;
          if ( count <= Nlines ) {
              SetupTbl ( ) ;
              WriteTbl ( ) ;
              kgSetTableCursorPos ( Tbl , ( rcount+row ) *Tbl->nx+1 , 0 ) ;
          }
          else {
              StartLine += rcount;
              EndLine += rcount;
              if ( shift > 0 ) {
                  StartLine -= shift;
              }
              SetupTbl ( ) ;
              WriteTbl ( ) ;
              kgSetTableCursorPos ( Tbl , ( shift+row ) *Tbl->nx+1 , 0 ) ;
          }
          SetupVbar ( ) ;
          kgUpdateOn ( Tbl->D ) ;
      }
      return 1;
  }
  int WriteClipBoard ( Dlink *Wlist ) {
      int len = 0;
      char *Buff , *pt;
      if ( Wlist == NULL ) return 0;
      Resetlink ( Wlist ) ;
      while ( ( pt = ( char * ) Getrecord ( Wlist ) ) != NULL ) {
          len += ( strlen ( pt ) +1 ) ;
      }
      Buff = ( char * ) malloc ( len+1 ) ;
      Buff [ 0 ] = '\0';
      Resetlink ( Wlist ) ;
      while ( ( pt = ( char * ) Getrecord ( Wlist ) ) != NULL ) {
          strcat ( Buff , pt ) ;
      }
      Resetlink ( Wlist ) ;
      kgSetClipBoard ( Tbl->D , Buff ) ;
//    kgSetPrimary(Tbl->D,Buff);
      free ( Buff ) ;
      return len;
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
          sprintf ( Buf1 , "Copy lines %d to %d to !c03%-s?" , s , e ,fpt) ;
          if ( s != e ) if ( ! kgQstMenu ( Tbl->D , 50 , 100 , Buf1 , 1 ) ) return 0;
          Dposition ( Slist , s ) ;
          for ( k = s;k <= e;k++ ) {
              spt = ( char * ) Getrecord ( Slist ) ;
              if ( spt == NULL ) break;
              dpt = ( char * ) malloc ( strlen ( spt ) +1 ) ;
              strcpy ( dpt , spt ) ;
              Dadd ( Wlist , dpt ) ;
          }
          WriteClipBoard ( Wlist ) ;
          Dwritefile ( Wlist , fpt ) ;
          Dempty ( Wlist ) ;
      }
      return 1;
  }
  static int CopyToBuf ( char *fpt ) {
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
          if ( s != e ) if ( ! kgQstMenu ( Tbl->D , 50 , 100 , Buf1 , 1 ) ) return 0;
          Dposition ( Slist , s ) ;
          for ( k = s;k <= e;k++ ) {
              spt = ( char * ) Getrecord ( Slist ) ;
              if ( spt == NULL ) break;
              dpt = ( char * ) malloc ( strlen ( spt ) +1 ) ;
              strcpy ( dpt , spt ) ;
              Dadd ( Wlist , dpt ) ;
          }
          WriteClipBoard ( Wlist ) ;
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
          if ( s != e ) if ( ! kgQstMenu ( Tbl->D , 50 , 100 , Buf1 , 1 ) ) return 0;
          Dposition ( Slist , s ) ;
          for ( k = s;k <= e;k++ ) {
              spt = ( char * ) Dpick ( Slist ) ;
              if ( spt == NULL ) break;
              Dadd ( Wlist , spt ) ;
          }
          WriteClipBoard ( Wlist ) ;
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
  static int CleanTableAndRedraw (char *newfile  ) {
      int k;
      char *spt;
      MarkPos=1;
      ReadTbl ( ) ;
      Resetlink(Slist);
      Dempty(Slist);
      Slist = Dreadfile(newfile);
      if(Slist == NULL) {
        Slist = Dopen();
        spt = (char *)malloc(3);
        strcpy(spt," \n");
        Dadd(Slist,spt);
      }
          Count = Dcount ( Slist ) ;
          EndLine=Count;
          StartLine =1;
          if ( EndLine > Nlines ) {
              EndLine = Nlines;
          }
          for ( k = 0;k < Nlines;k++ ) {
              kgSetOnTableCell ( Tbl , k*2+1 ) ;
              kgSetString ( Tbl , k*2 , ( char * ) "" ) ;
              kgSetString ( Tbl , k*2+1 , ( char * ) "" ) ;
          }
          for ( k = EndLine;k < Nlines;k++ ) {
              kgSetOffTableCell ( Tbl , k*2+1 ) ;
              kgSetString ( Tbl , k*2 , ( char * ) "" ) ;
              kgSetString ( Tbl , k*2+1 , ( char * ) "" ) ;
          }
#if 0
      if ( Count <= Nlines ) kgSetWidgetVisibility ( V , 0 ) ;
      else {
          Vsize = ( double ) ( Nlines ) /Count*100.0;
          Vpos = 0;
          kgSetScrollLength ( V , Vsize ) ;
          kgSetScrollPos ( V , Vpos ) ;
          kgSetScrollMovement ( V , ( double ) Nlines/Count*100.0 ) ;
      }
#endif
      SetupVbar();
      kgUpdateWidget ( V ) ;
      WriteTbl ( ) ;
      return 1;
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
  static int GotoLastPos ( ) {
      if ( MarkPos < 1 ) {
          MarkPos = 1;
          kgSetInt ( MT , 0 , MarkPos ) ;
          kgUpdateWidget ( MT ) ;
      }
      int pos = LastPos-StartLine;
      ReadTbl ( ) ;
      Count = Dcount ( Slist ) ;
      if ( MarkPos > Count ) MarkPos = Count;
      if ( LastPos > Count ) LastPos = Count;
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
      EndLine = LastPos;
      StartLine = EndLine -Nlines +1;
      if ( StartLine < 1 ) {
          StartLine = 1;
          EndLine = Nlines;
          if ( EndLine > Count ) EndLine = Count;
      }
      WriteTbl ( ) ;
      kgSetTableCursor ( Tbl , ( pos ) *Tbl->nx+1 ) ;
      kgSetAttnWidget ( Tbl->D , Tbl ) ;
      SetupVbar ( ) ;
      kgUpdateOn ( Tbl->D ) ;
      return 1;
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
  static char *SearchStr ( char *str , char* ptn ) {
      char *ret = NULL;
      char *ptmp;
      ptmp = strstr ( str , ptn ) ;
      if ( ptmp != NULL ) {
          ret = ptmp;
          while ( ( ptmp = strstr ( ptmp+1 , ptn ) ) != NULL ) {
              ret = ptmp;
          }
      }
      return ret;
  }
  static char * ReplaceString ( char *lptr , char *ptmp ) {
      int k , l1 , l2 , loc;
      char *s = ( char * ) SrString ;
      char *r = ( char * ) ReString ;
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
  static int ReplaceTblRev ( ) {
      void *Tmp = ( void * ) Tbl->D;
      int n , ret = 0;
      int k = 0 , loc , count , rln;
      char *spt , *lptr , *ptmp , *npt , *rpt , chtmp;
      int row , curpos , stchar , rowbk , spos , rcurpos;
      int Slbak , Elbak , curbk;
      spt = SrString ;
      rpt = ReString ;
      rln = strlen ( rpt ) ;
//      printf ( " ReplaceTblRev()\n" ) ;
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
      lptr = ( char * ) Getrecordrev ( Slist ) ;
      if ( lptr == NULL ) return 0;
      chtmp = lptr [ rcurpos ] ;
      lptr [ rcurpos ] = '\0';
      if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
          lptr [ rcurpos ] = chtmp;
          loc = GetLength ( lptr , ptmp ) ;
          npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
          strcpy ( npt , Buf ) ;
          spos = StartLine+row -1;
          Dreplace ( Slist , npt , spos ) ;
          WriteTbl ( ) ;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
          RETURN ( 0 ) ;
      }
      lptr [ rcurpos ] = chtmp;
      count = 1;
      if ( Count <= Nlines ) {
          while ( ( lptr = ( char * ) Getrecordrev ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  row -= count;
                  npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
                  strcpy ( npt , Buf ) ;
                  spos = StartLine+row-1;
//                  Resetlink(Slist);
                  Dreplace ( Slist , npt , spos ) ;
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          row = rowbk;
          Dend ( Slist ) ;
          for ( k = Count-1;k > rowbk;k-- ) {
              lptr = ( char * ) Getrecordrev ( Slist ) ;
              if ( lptr == NULL ) break;
              if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
                  strcpy ( npt , Buf ) ;
                  spos = StartLine+k -1;
                  Dreplace ( Slist , npt , spos ) ;
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( k ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
          }
      }
      else {
          while ( ( lptr = ( char * ) Getrecordrev ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  if ( StartLine-count >= 1 ) {
                      StartLine -= count;
                      EndLine -= count;
                  }
                  else {
                      row = StartLine+row -count-1;
                      StartLine = 1;
                      EndLine = Nlines;
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
          Dend ( Slist ) ;
          count = 0;
          for ( k = Count-1;k > Elbak;k-= Nlines ) {
              for ( row = Nlines-1;row >= 0;row-- ) {
                  lptr = ( char * ) Getrecordrev ( Slist ) ;
                  if ( lptr == NULL ) break;
                  if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                      loc = GetLength ( lptr , ptmp ) ;
                      EndLine = k+1;
                      StartLine = EndLine-Nlines+1;;
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
  static int SearchTbl ( ) {
      int k = 0 , loc , count;
      char *spt , *lptr , *ptmp;
      int row , curpos , stchar , rowbk , rcurpos;
      int Slbak , Elbak , curbk;
      DIALOG *D = ( DIALOG * ) Tbl->D;;
      void *Tmp = D;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      spt = SrString ;
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
  static int SearchTblRev ( ) {
      int k = 0 , loc , count;
      char *spt , *lptr , *ptmp , chtmp;
      int row , curpos , stchar , rowbk , rcurpos;
      int Slbak , Elbak , curbk;
      DIALOG *D = ( DIALOG * ) Tbl->D;;
      void *Tmp = D;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      spt = SrString ;
      k = 0;
      while ( spt [ k ] == ' ' ) k++;
      if ( spt [ k ] < ' ' ) return 0;
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
//      printf ( "Row: %d %d %d\n" , rowbk , StartLine , curpos ) ;
      lptr = ( char * ) Getrecordrev ( Slist ) ;
      if ( lptr == NULL ) return 0;
      chtmp = lptr [ rcurpos ] ;
      lptr [ rcurpos ] = '\0';
      if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
          lptr [ rcurpos ] = chtmp;
          loc = GetLength ( lptr , ptmp ) ;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
          RETURN ( 0 ) ;
      }
      lptr [ rcurpos ] = chtmp;
      count = 1;
      if ( Count <= Nlines ) {
          while ( ( lptr = ( char * ) Getrecordrev ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  row -= count;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          row = rowbk;
          Dend ( Slist ) ;
          for ( k = Count-1;k > rowbk;k-- ) {
              lptr = ( char * ) Getrecordrev ( Slist ) ;
              if ( lptr == NULL ) break;
              if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  kgSetTableCursorPos ( Tbl , ( k ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
          }
      }
      else {
          while ( ( lptr = ( char * ) Getrecordrev ( Slist ) ) != NULL ) {
              if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                  loc = GetLength ( lptr , ptmp ) ;
                  if ( StartLine-count >= 1 ) {
                      StartLine -= count;
                      EndLine -= count;
                  }
                  else {
                      row = StartLine+row -count-1;
                      StartLine = 1;
                      EndLine = Nlines;
                  }
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc ) ;
                  RETURN ( 0 ) ;
              }
              count++;
          }
          Dend ( Slist ) ;
          count = 0;
          for ( k = Count-1;k > Elbak;k-= Nlines ) {
              for ( row = Nlines-1;row >= 0;row-- ) {
                  lptr = ( char * ) Getrecordrev ( Slist ) ;
                  if ( lptr == NULL ) break;
                  if ( ( ptmp = ( char * ) SearchStr ( lptr , spt ) ) != NULL ) {
                      loc = GetLength ( lptr , ptmp ) ;
                      EndLine = k+1;
                      StartLine = EndLine-Nlines+1;;
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
 /* Callback for  KEDtable   */ 

int kgeditKEDtablecallback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
           However cellno got 2 special values
             1. SCROLL_DOWN a scrolldown action
             2. SCROLL_UP a scrolldown action
             3. LINE_CHANGE for line change  action
             4. TAB_PRESS for tab action
             5. BUTTON2_PRESS for button2 action
             6. BUTTON3_PRESS for button3 action
             which may be ignored or peocessed
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 

      DIALOG *D;DIT *T;T_ELMT *e;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      int ret = 1;
      double pos;
      char *str = NULL;
      D = ( DIALOG * ) Tmp;
      T = ( DIT * ) kgGetWidget ( Tmp , i ) ;
      e = T->elmt;
      if ( cellno == BUTTON2_PRESS ) {
          ReadTbl ( ) ;
          Push ( ) ;
          str = ( char * ) kgProcessClips ( D , 2 ) ;
          if ( str != NULL ) ProcessClip ( D , str ) ;
          return ret;
      }
      if ( cellno == BUTTON3_PRESS ) {
          ReadTbl ( ) ;
          Push ( ) ;
          str = ( char * ) kgProcessClips ( D , 3 ) ;
          if ( str != NULL ) ProcessClip ( D , str ) ;
          return ret;
      }
      if ( cellno == TAB_PRESS ) {
          ReadTbl ( ) ;
          if ( Push ( ) ) {LocPush ( ) ; WriteTbl ( ) ;}
          return ret;
      }
      if ( cellno == LINE_CHANGE ) {
          AddMode = 0;
          ReadTbl ( ) ;
          if ( Push ( ) ) {LocPush ( ) ;WriteTbl ( ) ;}
          return ret;
      }
      if ( cellno == SCROLL_DOWN ) {
//          kgUpdateOff(Tbl->D);
          ReadTbl ( ) ;
          if ( Push ( ) ) {LocPush ( ) ;}
          if ( EndLine < ( Count ) ) {
              StartLine++;
              EndLine++;
#if 1
//              printf("ScrollDown\n");
              kgScrollDownTable ( Tbl , Tbl->ny-1 ) ;
              WriteTblRow ( Tbl->ny-1 ) ;
#else
              WriteTbl ( ) ;
#endif
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
          if ( Push ( ) ) {LocPush ( ) ;}
          if ( StartLine > 1 ) {
              StartLine--;
              EndLine--;
#if 1
// Not useful
              kgScrollUpTable ( Tbl , Tbl->ny-1 ) ;
              WriteTblRow ( 0 ) ;
#else
              WriteTbl ( ) ;
#endif
          }
          Vpos = ( double ) ( StartLine-1 ) *100.0/Count;
          kgSetScrollPos ( V , Vpos ) ;
          kgUpdateWidget ( V ) ;
          kgSetTableCursor ( Tbl , 1 ) ;
          kgUpdateOn ( Tbl->D ) ;
          kgSkipEvents ( Tbl->D ) ;
      }
      else {
          LocPush ( ) ;
          if ( AddMode ) {
              int row = cellno/Tbl->nx;
              if ( row != AddRow ) {AddMode = 0;}
              else {
                  AddLine ( row ) ;
                  if ( row < ( Tbl->ny-1 ) ) row++;
                  AddRow = row;
              }
              ReadTbl ( ) ;
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
              AddStringLine ( row ) ;
              ReadTbl ( ) ;
              if ( row < ( Tbl->ny-1 ) ) row++;
              kgSetTableCursor ( Tbl , ( row ) *Tbl->nx+1 ) ;
//      kgSetTableCursorPos ( Tbl , ( row) *Tbl->nx+1 , 0) ;
              kgUpdateOn ( Tbl->D ) ;
          }
      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }

 /* Callback for  KEDfinish   */ 

int kgeditKEDfinishcallback( int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIL *B;
      int n , ret = 1;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      char *cpt;
      void *Busy = NULL;
      D = ( DIALOG * ) Tmp;
      B = ( DIL * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx;
      switch ( butno ) {
          case 1:
          if ( ! kgCheckMenu ( D , 50 , 200 , ( char * ) "Want to !c03ABORT ?" , \
              0 ) ) {\
              kgSetAttnWidget ( Tbl->D , Tbl ) ;
              return 0;
          }
          pt [ 1 ] = NULL;
          Dempty ( Slist ) ;
#if 0
          Slist = Dreadfile ( SaveFile ) ;
          if ( Dcount ( Slist ) == 0 ) {
              Dempty ( Slist ) ;
              break;
          }
          if ( kgCheckMenu ( D , 10 , 100 , ( char * ) "Want to keep Saved File ?" , \
          1 ) ) {
              char *fpt;
              strcpy ( Buf , flname ) ;
#if 0
              if ( ( fpt = RunGetFileName ( Tmp , Buf ) ) == NULL ) break;
              strcpy ( Buf , fpt ) ;
              free ( fpt ) ;
#else
              if( !kgFolderBrowser(Tmp,100,100,Buf,(char *)"*")) break;
#endif
              Dempty ( Slist ) ;
              Slist = Dreadfile ( SaveFile ) ;
              Dwritefile ( Slist , Buf ) ;
              Dempty ( Slist ) ;
          }
#endif
          kgDisableSelection ( D ) ;
          break;
          case 2:
          kgDisableSelection ( D ) ;
          Busy = kgOpenBusy ( D , B->x1-100 , B->y1 ) ;
          ReadTbl ( ) ;
          Dwritefile ( Slist , flname ) ;
          pt [ 1 ] = pt [ 0 ] ;
          Dempty ( Slist ) ;
          kgCloseBusy ( Busy ) ;
          break;
      }
      kgSetAttnWidget ( Tbl->D , Tbl ) ;
      remove ( Bkup ) ;
      remove ( SaveFile ) ;
      return ret;
}
void  kgeditKEDfinishinit (DIL *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}

 /* Callback for  KEDopt2   */ 

int kgeditKEDopt2callback(int butno,int i,void *Tmp) {
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
      LocPush ( ) ;
      switch ( butno ) {
          case 1:
          row = kgGetTableRow ( Tbl ) ;
          ReadTbl ( ) ;
          row = DeleteLine ( row ) ;
          Count = Dcount ( Slist ) ;
          if ( Count <= 0 ) {
              buf = ( char * ) malloc ( 2 ) ;
              strcpy ( buf , "\n" ) ;
              Count = 1;
          }
          if ( ( row >= Count ) ) row = Count-1;
          kgSetTableCursor ( Tbl , ( row ) *Tbl->nx+1 ) ;
          kgSkipEvents ( Tbl->D ) ;
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
          ReadTbl ( ) ;
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
void  kgeditKEDopt2init (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
      B1x = B->x1;
      B1y = B->y1;
}

  static int RedrawTable ( ) {
      int Fz1 , Fz2 , nchr , nymax , nyo , k , nxo;
      int xl , yl , i , j;
      char Fmt [ 20 ] ;
      DIALOG *D = ( DIALOG * ) Tbl->D;
      T_ELMT *elmt;
      elmt = ( T_ELMT * ) Tbl->elmt;
      nyo = Tbl->ny;
      nxo = Tbl->nx;
#if 1
      for ( j = 0;j < nyo;j++ ) {
          for ( i = 0;i < nxo;i++ ) {
              k = j*nxo+i;
              if ( elmt [ k ] .img != NULL ) {
                  kgFreeImage ( elmt [ k ] .img ) ;
              }
              elmt [ k ] .img = NULL;
          }
      }
#endif
      if ( nydef == -1 ) nydef = Tbl->ny;
      Fz1 = Tbl->FontSize;;
      if ( Tbl->width < 2*Fz1 ) Tbl->width = 2*Fz1;
      DefWidth = Tbl->width;
//      Tbl->ny = ( Tbl->y2 - Tbl->y1-4 ) /(2*Fz1);
      Tbl->ny = ( Tbl->y2 - Tbl->y1-4 ) / ( Tbl->width ) ;
      Fz2 = ( Tbl->y2 - Tbl->y1-4 ) / ( 2*Tbl->ny ) ;
      if ( Fz1 > Fz2 ) Fz1 = Fz2;
      nchr = ( Tbl->x2 - Tbl->x1 ) /Fz1 -11;
      Tbl->x2 = ( nchr+11 ) *Fz1+Tbl->x1;
      Tbl->ny = ( float ) ( Tbl->y2 - Tbl->y1-4 ) / ( Tbl->width ) +0.5;
      Tbl->y2 = Tbl->width* ( Tbl->ny ) +Tbl->y1+4;
      sprintf ( Fmt , "%%%ds" , nchr ) ;
      elmt = ( T_ELMT * ) Tbl->elmt;
      if ( Tbl->ny > nydef ) elmt = ( T_ELMT * ) realloc \
       ( elmt , Tbl->nx*Tbl->ny*sizeof ( T_ELMT ) ) ;
      Tbl->elmt = elmt;
      nymax = Tbl->ny;
      if ( nymax > nyo ) nymax = nyo;
      if ( nymax < nydef ) nymax = nydef;
      if ( nymax > Tbl->ny ) nymax = Tbl->ny;
      for ( k = 0;k < nymax;k++ ) {
          strcpy ( elmt [ k*Tbl->nx ] .fmt , ( char * ) "%4s" ) ;
          elmt [ k*Tbl->nx ] .sw = 0;
          elmt [ k*Tbl->nx ] .noecho = 0;
          elmt [ k*Tbl->nx ] .img = NULL;
          strcpy ( elmt [ k*Tbl->nx+1 ] .fmt , Fmt ) ;
          elmt [ k*Tbl->nx+1 ] .sw = 1;
          elmt [ k*Tbl->nx+1 ] .noecho = 0;
          elmt [ k*Tbl->nx+1 ] .img = NULL;
      }
//      if((Tbl->ny>nydef)&&(Tbl->ny > nyo)) {
//      printf( "Tbl->ny: %d nydef: %d\n",Tbl->ny,nydef);
      if ( ( Tbl->ny > nydef ) ) {
          int j = 0;
          char *cpt = NULL;
//         printf("vi vs realloc\n");
          vi = ( char * ) realloc ( vi , 20* ( Tbl->ny - nydef ) ) ;
          vs = ( char * ) realloc ( vs , 2000* ( Tbl->ny - nydef ) ) ;
          for ( k = nydef;k < Tbl->ny;k++ ) {
              elmt [ k*Tbl->nx ] .fmt = ( char * ) malloc ( 10 ) ;
              elmt [ k*Tbl->nx+1 ] .fmt = ( char * ) malloc ( 10 ) ;
              strcpy ( elmt [ k*Tbl->nx ] .fmt , ( char * ) "%4s" ) ;
              elmt [ k*Tbl->nx ] .sw = 0;
              elmt [ k*Tbl->nx ] .noecho = 0;
              elmt [ k*Tbl->nx ] .img = NULL;
              strcpy ( elmt [ k*Tbl->nx+1 ] .fmt , Fmt ) ;
              elmt [ k*Tbl->nx+1 ] .sw = 1;
              elmt [ k*Tbl->nx+1 ] .noecho = 0;
              elmt [ k*Tbl->nx+1 ] .img = NULL;
              elmt [ k*Tbl->nx ] .v = ( void * ) ( vi+j*20 ) ;
              elmt [ k*Tbl->nx +1 ] .v = ( void * ) ( vs+j*2000 ) ;
              cpt = ( char * ) elmt [ k*Tbl->nx ] .v;
              cpt [ 0 ] = '\0';
              cpt = ( char * ) elmt [ k*Tbl->nx +1 ] .v;
              cpt [ 0 ] = '\0';
              j++;
          }
      }
      Nlines = Tbl->ny;
      Tbl->FontSize = Fz1;
      xl = V->x2 - V->x1;
      yl = V->y2 - V->y1;
      V->x1 = Tbl->x2+10;
      V->x2 = V->x1 + xl;
      V->y2 = Tbl->y2;
      yl = MT->y2 -MT->y1;
      MT->y1 = D->yl-35;
      MT->y2 = MT->y1+yl;
      yl = GB->y2 - GB->y1;
      GB->y1 = D->yl-36;
      GB->y2 = GB->y1+yl;
      kgRedrawDialog ( D ) ;
 //     if(Tbl->ny !=  nyo) {
      SetupTbl ( ) ;
      WriteTbl ( ) ;
      SetupVbar ( ) ;
//      kgUpdateWidget ( V ) ;
//      kgUpdateWidget (Tbl ) ;
      kgUpdateOn ( D ) ;
//      }
      kgSetAttnWidget ( D , Tbl ) ;
      return 1;
  }
  static int MakeFileNames ( ) {
      char BaseName [ 200 ] ;
      kgExtractBaseName ( flname , BaseName ) ;
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
      printf ( "Nlines= %d\n" , Nlines ) ;
#if 0
      if ( ( Strs == NULL ) || ( Strs [ 0 ] == NULL ) ) {
          cpt = ( char * ) malloc ( 3 ) ;
          strcpy ( cpt , " \n" ) ;
          Dadd ( Slist , cpt ) ;
          if ( Strs == NULL ) Strs = ( char ** ) Dlinktoarray ( Slist ) ;
          else Strs [ 0 ] = cpt;
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
#else
      if ( ( Strs == NULL ) || ( Strs [ 0 ] == NULL ) ) {
          printf ( "File not existing...\n" ) ;
          cpt = ( char * ) malloc ( 2 ) ;
          strcpy ( cpt , "\n" ) ;
          Dinsert ( Slist , cpt ) ;
          if ( Strs != NULL ) free ( Strs ) ;
          Strs = ( char ** ) Dlinktoarray ( Slist ) ;
      }
      {
#endif
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
          Vsize = ( double ) Nlines/Count*100.0;
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
      Opt = ( DIN * ) kgGetNamedWidget ( Tmp , ( char * ) "KEDopt1" ) ;
      kgAddtoGrp ( Tmp , Mid , kgGetNamedWidget ( Tmp , ( char * ) "KEDopt2" ) ) ;
      kgAddtoGrp ( Tmp , Mid , Opt ) ;
      kgAddtoGrp ( Tmp , Mid , Tbl ) ;
      kgAddtoGrp ( Tmp , Mid , V ) ;
      MT = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "KEDmark" ) ;
      GB = ( DIN * ) kgGetNamedWidget ( Tmp , ( char * ) "KEDgo" ) ;
      kgAddtoGrp ( Tmp , Mid , MT ) ;
      kgAddtoGrp ( Tmp , Mid , GB ) ;
      return 1;
  }
 /* Callback for  KEDopt1   */ 

int kgeditKEDopt1callback(int butno,int i,void *Tmp) {
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
          if ( kgFolderBrowser ( Tmp , 100 , 100 , Infile , ( char * ) "*" ) ) {
              kgSkipEvents ( Tmp ) ;
              pos = kgGetTableRow ( Tbl ) +StartLine;
              LastPos = pos ;
              LocPush ( ) ;
              ReadInFile ( Infile ) ;
              sprintf ( Msg , "Read in %s at %d" , Infile , pos ) ;
              Splash ( Msg ) ;
          }
          break;
          case 3:
#if 0
          fpt = RunGetFileName ( Tmp , NULL ) ;
#else
          Buf[0]='\0';
          if( !kgFolderBrowser(Tmp,100,100,Buf,(char *)"*")) break;
          fpt = Buf;
#endif
          if ( WriteToFile ( fpt ) ) {
              if ( fpt != NULL ) {
                  sprintf ( Msg , "Wrote to  %s" , fpt ) ;
                  Splash ( Msg ) ;
//                  free ( fpt ) ;
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
          LastPos = MarkPos ;
          LocPush ( ) ;
          if ( CutToFile ( Bkup ) ) {
              SetupVbar ( ) ;
              GotoMark ( ) ;
              kgUpdateOn ( Tmp ) ;
          }
          break;
          case 5:
          CopyToBuf( Bkup ) ;
          break;
          case 6:
          LastPos = pos ;
          LocPush ( ) ;
          ReadInFile ( Bkup ) ;
          break;
          case 7:
          LocPush ( ) ;
          Push ( ) ;
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
void  kgeditKEDopt1init (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}

 /* Callback for  KEDmark   */ 

int kgeditKEDmarkcallback(int cellno,int i,void *Tmp) {
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

 /* Callback for  KEDgo   */ 

int kgeditKEDgocallback(int butno,int i,void *Tmp) {
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
void  kgeditKEDgoinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
  static int LoadConfig ( void *Tmp ) {
      char Config [ 300 ] ;
      char FontName [ 300 ] ;
      DIALOG *D = ( DIALOG * ) Tmp;
      Gclr *Gc = & ( D->gc ) ;
      int r , g , b;
      int Font;
      sprintf ( Config , "%-s/.kit" , getenv ( ( char * ) "HOME" ) ) ;
      FILE *fp = fopen ( Config , "r" ) ;
      if ( fp != NULL ) {
          fscanf ( fp , "%s" , FontName ) ;
//      Tbl->Font = kgAddFixedFont(FontName);
          Font = kgCheckFont ( FontName ) ;
          if ( Font >= 0 ) Tbl->Font = Font;
          else Tbl->Font = kgAddFont ( FontName ) ;
          fscanf ( fp , "%d%d" , & ( Tbl->FontSize ) , & ( Tbl->width ) ) ;
          fscanf ( fp , "%d%d%d" , & r , & g , & b ) ;
          kgDefineColor ( Gc->tabl_char , r , g , b ) ;
          fscanf ( fp , "%d%d%d" , & r , & g , & b ) ;
          kgDefineColor ( Gc->tabl_hchar , r , g , b ) ;
          fscanf ( fp , "%d%d%d" , & r , & g , & b ) ;
          kgDefineColor ( Gc->tabl_fill , r , g , b ) ;;
          fscanf ( fp , "%d%d%d" , & r , & g , & b ) ;
          kgDefineColor ( Gc->tabl_line , r , g , b ) ;
          fclose ( fp ) ;
          RedrawTable ( ) ;
      }
      return 1;
  }
int kgeditSetup(void *Tmp,void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  /* you add any initialisation here */
  /* useful for setting is used as MakeGroup */
  return 1;
}
 
void * kgeditCleanDia(void *args) {
  /*********************************** 
    args :  Pointer to args  
   ***********************************/ 
  
/* you add any cleaning  here */

  return NULL;
}
 
 
void *  kgeditAction(void *Tmp,void *Args) {
  return NULL;
} 
 
 
int   kgeditOn(void *itmp) {
  DIAINTR * Dt = (DIAINTR *) itmp;
  if(Dt == NULL ) Dt = (DIAINTR *)It;
  if(Dt != NULL) {
    if(Dt->Dtmp != NULL)kgSetGrpVisibility(Dt->Dtmp,Dt->GrpId,1);
    else return 0;
    return 1;
  } 
  return 0;
} 
 
int   kgeditOff(void *itmp) {
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
 
 
void * kgeditInterface(void *args,void *rets) {
  /*********************************** 
   ***********************************/ 
  DIAINTR *it= (DIAINTR *)malloc(sizeof(DIAINTR));
  it->GrpId=0;
  // filled by MakeGroup  it->xsh=0;
  it->ysh=0;
  it->RunDia = Runkgedit;
  it->MakeGroup = MakekgeditGroup;
  it->Title = GetPointer((char *)"kgedit");
  it->Help = GetPointer( (char *)"No help yet, request");
  it->Action = kgeditAction;
  it->Settings = kgeditSetup;
  it->Cleanup  = kgeditCleanDia;
  if(args != NULL) Args=args;
  if(rets != NULL) Rets=rets;
  it->args = Args;
  it->rets = Rets;
  it->SwitchOn = kgeditOn;
  it->SwitchOff = kgeditOff;
  it->Dtmp = NULL; // fiiled by MakeGroup 
  It = it;
  return it;
}
 
 
int kgeditKEDscrollcallback(double val,int i,void *Tmp) {
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
int kgeditKEDcfcallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  int font,r,g,b;
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  char fname[200],buf[300];
  switch(butno) {
    case 1: //  !c38Colors 
      kgGetColor(Tmp,30,30,&r,&g,&b);
      sprintf(buf,"$tc-%-d%-3.3d%-3.3d\n",r,g,b); 
      AddStringAtRow(buf);
      break;
    case 2: //  !f23!c01Fonts 
        kgGetFontString(Tmp,fname);
        sprintf(buf,"$f%-s\n",fname);
        AddStringAtRow(buf);
//      font = GetFont(Tmp,50,50);
      break;
  }
  return ret;
}
void  kgeditKEDcfinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
static int FileMenu(void *Parent) {
   int   v0 = 1;
   char *fmenu[]={(char *)"Open",(char *)"Save",(char *)"Save as",
                  (char *)"Save&Quit",(char *)"Quit",NULL};
   v0 = kgMenu1(Parent,15,63,0,fmenu,5,NULL,NULL);
   return v0;
}
int kgeditKEDsavecallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
      int  row , curpos , rcurpos;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  void *Busy=NULL;
  char Buf[300];
  switch(butno) {
    case 1: //  Save 
          int opt = FileMenu(Tmp);
          switch(opt) {
            case 1:
            char FileName[300];
            if( kgCheckMenu(Tmp,50,50,
               "Open New File (if needed save before opening) ?",0)) {
              strcpy(FileName,getenv("PWD"));
              strcat(FileName,"/");
              if(!kgFolderBrowser(Tmp,50,50,FileName,"*")) break;
              DII *I = (DII *)kgGetNamedWidget(Tmp,(char *)"KEDtitle");
              sprintf(Buf,"!z34!f12File : %-s",FileName);
              kgWrite(I,Buf);
              CleanTableAndRedraw(FileName);
              strcpy(flname,FileName);
              CleanupLinks();
            }
            break;
            case 2:
            kgDisableSelection ( D ) ;
            Busy = kgOpenBusy ( D , B->x1+10 , B->y1 ) ;
            ReadTbl ( ) ;
            Dwritefile ( Slist , flname ) ;
            kgCloseBusy ( Busy ) ;
            Splash("Saved File");
            break;
            case 3:
            char File[300];
            strcpy(File,getenv("PWD"));
            strcat(File,"/");
            if(kgFolderBrowser(Tmp,50,50,File,(char *)"*")){
              kgDisableSelection ( D ) ;
              Busy = kgOpenBusy ( D , B->x1+10 , B->y1 ) ;
              ReadTbl ( ) ;
              Dwritefile ( Slist , File ) ;
              kgCloseBusy ( Busy ) ;
              Splash("Saved File");
            }
            break;
            case 5:
            if (  kgCheckMenu ( D , 50 , 200 ,
                ( char * ) "Want to !c03ABORT ?" , 0 ) ) { 
              pt [ 1 ] = NULL;
              Dempty ( Slist ) ;
              kgDisableSelection ( D ) ;
              remove ( Bkup ) ;
              remove ( SaveFile ) ;
              kgSetExit(Tmp);
            }
            break;
            case 4:
            kgDisableSelection ( D ) ;
            Busy = kgOpenBusy ( D , B->x1+10 , B->y1 ) ;
            ReadTbl ( ) ;
            Dwritefile ( Slist , flname ) ;
            pt [ 1 ] = pt [ 0 ] ;
            Dempty ( Slist ) ;
            kgCloseBusy ( Busy ) ;
            remove ( Bkup ) ;
            remove ( SaveFile ) ;
            kgSetExit(Tmp);
            break;
            default:
            break;
          }
      break;
    case 2: //  Undo 
          row = kgGetTableRow ( Tbl ) ;
          curpos = kgGetTableCurpos ( Tbl ) ;
          rcurpos = GetRealPos ( ) ;
          UpdateTbl ( ) ;
#if 1  //TCB
          row = kgGetTableRow ( Tbl ) ;
//          MarkPos = EndLine;
//          kgSetInt ( MT , 0 , MarkPos ) ;
//          kgUpdateWidget ( MT ) ;
          if ( flname != NULL ) {
              int k;
              Dlink *bkup = NULL;
              bkup = Pop ( ) ;
              if ( bkup == NULL ) {
                  sprintf ( Msg , "Sorry!! UNDO not possible; You may ABORT if needed" ) ;
                  Splash ( Msg ) ;
                  break;
              }
              Dempty ( Slist ) ;
              Slist = bkup;
              LocPop ( ) ;
              row = TblRow;
              for ( k = 0;k < Nlines;k++ ) {
                  kgSetString ( Tbl , k*2 , ( char * ) "" ) ;
                  kgSetString ( Tbl , k*2+1 , ( char * ) "" ) ;
              }
              kgUpdateWidget ( Tbl ) ;
//              kgUpdateOn ( Tbl->D ) ;
#if 0
              MarkPos = StartLine+kgGetTableRow ( Tbl ) ;
#endif
              kgSetInt ( MT , 0 , MarkPos ) ;
              kgUpdateWidget ( MT ) ;
              if ( ( Slist == NULL ) || ( Count = Dcount ( Slist ) ) == 0 ) {
                  if ( Slist != NULL ) Dempty ( Slist ) ;
//                  Slist = Dreadfile ( flname ) ;
                  Slist = Dreadfile ( SaveFile ) ;
                  if ( Dcount ( Slist ) == 0 ) Slist = Dreadfile ( flname ) ;
              }
              Count = Dcount ( Slist ) ;
              if ( ( EndLine - StartLine ) > Count ) {
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
//              GotoLastPos ( ) ;
//              if ( ( Count >= Nlines ) && ( StartLine > 1 ) ) row = Nlines-1;
              kgSetTableCursorPos ( Tbl , row*Tbl->nx+1 , 0 ) ;
//TCB              SetupVbar ( ) ;
              kgUpdateOn ( Tbl->D ) ;
          }
          else printf ( "flname== NULL\n" ) ;
#else
          int k , chng = 0;
          Dlink *bkup = NULL;
          bkup = Pop ( ) ;
          if ( bkup == NULL ) {
              sprintf ( Msg , "Sorry!! UNDO not possible; You may ABORT if needed" ) ;
              Splash ( Msg ) ;
              break;
          }
          chng = Dcount ( Slist ) -Dcount ( bkup ) ;
          Dempty ( Slist ) ;
          Slist = bkup;
          for ( k = 0;k < Nlines;k++ ) {
              kgSetString ( Tbl , k*2 , ( char * ) "" ) ;
              kgSetString ( Tbl , k*2+1 , ( char * ) "" ) ;
          }
          kgUpdateWidget ( Tbl ) ;
          SetupVbar ( ) ;
          WriteTbl ( ) ;
          row = Tblrow;
          if ( chng ) row = Tblrow-1;
          kgSetTableCursorPos ( Tbl , row*Tbl->nx+1 , 0 ) ;
          kgUpdateOn ( Tbl->D ) ;
#endif
      break;
  }
  kgSetAttnWidget ( Tbl->D , Tbl ) ;
  return ret;
}
void  kgeditKEDsaveinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgeditKEDstringscallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  switch(butno) {
    case 1: //  Strings 
      char *Strs[2];
      Strs[0]=SrString;
      Strs[1]=ReString;
      RunSbox(Tmp,Strs);
      break;
  }
  kgSetAttnWidget ( Tbl->D , Tbl ) ;
  return ret;
}
void  kgeditKEDsearchinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgeditKEDreplacecallback(int butno,int i,void *Tmp) {
  /***********************************
    butno : selected item (1 to max_item)
    i :  Index of Widget  (0 to max_widgets-1)
    Tmp :  Pointer to DIALOG
   ***********************************/
      DIALOG *D;DIN *B;
      int n , ret = 0;
      int k = 0 , loc , count , rln;
      char *spt , *lptr , *ptmp , *npt , *rpt;
      int row , curpos , stchar , rowbk , spos , rcurpos;
      int Slbak , Elbak , curbk;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
      DIT *TS=(DIT *)kgGetNamedWidget(Tmp,(char *)"KEDstbox");
      DIT *TR=(DIT *)kgGetNamedWidget(Tmp,(char *)"KEDrtbox");
      strcpy(SrString,(char *)kgGetString(TS,0));
      strcpy(ReString,(char *)kgGetString(TR,0));
      spt = SrString ;
      rpt = ReString ;
      rln = strlen ( rpt ) ;
      k = 0;
      while ( spt [ k ] >= ' ' ) k++;
//      fprintf ( stderr , "Nlines + %d %d\n" , Nlines , Tbl->ny ) ;
      Nlines = Tbl->ny;
      ReadTbl ( ) ;
      LocPush ( ) ;
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
      if ( k == 0 ) {
//      code for insertion at curpos
          ptmp = lptr+rcurpos;
          loc = 0;
          npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
          strcpy ( npt , Buf ) ;
          spos = StartLine+row -1;
          Dreplace ( Slist , npt , spos ) ;
          WriteTbl ( ) ;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+curpos+rln ) ;
          RETURN ( 0 ) ;
      }
      if ( SerDir == 0 ) return ReplaceTblRev ( ) ;
      if ( ( ptmp = ( char * ) strstr ( lptr+rcurpos , spt ) ) != NULL ) {
          loc = GetLength ( lptr , ptmp ) -GetLength ( lptr , lptr+rcurpos ) ;
          npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
          strcpy ( npt , Buf ) ;
          spos = StartLine+row -1;
          Dreplace ( Slist , npt , spos ) ;
          WriteTbl ( ) ;
          kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+curpos+rln ) ;
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
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+rln ) ;
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
                  row = k;
                  loc = GetLength ( lptr , ptmp ) ;
                  npt = ( char * ) malloc ( strlen ( ReplaceString ( lptr , ptmp ) ) +1 ) ;
                  strcpy ( npt , Buf ) ;
                  spos = StartLine+k -1;
                  Dreplace ( Slist , npt , spos ) ;
                  WriteTbl ( ) ;
                  kgSetTableCursorPos ( Tbl , ( k ) *Tbl->nx+1 , loc+rln ) ;
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
                  kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+rln ) ;
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
                      kgSetTableCursorPos ( Tbl , ( row ) *Tbl->nx+1 , loc+rln ) ;
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
void  kgeditKEDstringsinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgeditKEDsearchcallback(int butno,int i,void *Tmp) {
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
      DIT *TS=(DIT *)kgGetNamedWidget(Tmp,(char *)"KEDstbox");
      strcpy(SrString,(char *)kgGetString(TS,0));
      spt = SrString ;
      k = 0;
      while ( spt [ k ] == ' ' ) k++;
      if ( spt [ k ] < ' ' ) return ret;
//     printf("%s\n",spt+k);
      ReadTbl ( ) ;
      if ( SerDir == 0 ) return SearchTblRev ( ) ;
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
void  kgeditKEDreplaceinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgeditKEDhelpcallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  char *hmsg[]=  {
    "Kit (!c16K!c00ulina ed!c16IT!c00or) is supposed to be a simple graphical",
    "editor for Linux. It is aimed as an editor which be can be",
    "used with a few trials. However few tips may be useful.",
    "",
    "!c381. Markpos",
    "This position is used by operations like ,!c38'write to'!c00, !c38'cut'!c00",
    "and !c38'copy'!c00. It is used as the start position for these commands.",
    "Also the !c38'Go'!c00 button (int the lower bar) can take the cursor",
    "to !c38Markpos!c00. The !c38Markpos!c00 can be set either by pressing the !c38'Mark'!c00",
    "button in the top bar or by typing explicitly at the",
    "!c38'MarkPos'!c00 text box in bottom bar.",
    "",
    "!c382. Search and Replace strings.",
    "These strings are set at the respective text boxes in top",
    "bar. Either of the strings can be empty. The search string",
    "is used for searching the pattern. A !c38'Replace'!c00 will",
    "replace the next search string with the replace string.",
    "If the search string is empty, a !c38'Replace'!c00 will insert the",
    "replace string at the current cursor position.",
    "If the replace string is empty , a !c38'Replace'!c00 will remove the",
    "next search string.",
    "",
    "!c38Note: Text input box  can be cleared by typing an !c33'Esc'!c38 character.",
   NULL};
  switch(butno) {
    case 1: //  Help 
      RunMsg(Tmp,hmsg);
      break;
  }
  kgSetAttnWidget ( Tbl->D , Tbl ) ;
  return ret;
}
void  kgeditKEDhelpinit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgeditKEDdowncallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  DIALOG *D;DIN *B; 
  int n,ret =0; 
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  B = (DIN *)kgGetWidget(Tmp,i);
  n = B->nx*B->ny;
  switch(butno) {
    case 1: //   
      break;
  }
  kgSetAttnWidget ( Tbl->D , Tbl ) ;
  return ret;
}
void  kgeditKEDdowninit (DIN *B,void *ptmp) {
 void **pt=(void **)ptmp; //pt[0] is arg 
// may use kgChangeButtonNormalImage etc...
 BUT_STR *buts;
 buts = (BUT_STR *) (B->buts);
}
int kgeditKEDdircallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      DIP *P;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      void *img;
      D = ( DIALOG * ) Tmp;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      BUT_STR *buts = ( BUT_STR * ) B->buts;
      P = ( DIP* ) kgGetNamedWidget ( D , ( char * ) "KEDarrow" ) ;
      n = B->nx*B->ny;
      img = buts [ 0 ] .xpmn;
      buts [ 0 ] .xpmn = buts [ 0 ] .xpmp;
      buts [ 0 ] .xpmp = img;
      P->xpm = buts [ 0 ] .xpmn ;
      kgUpdateWidget ( P ) ;
      kgUpdateOn ( D ) ;
      SerDir = ( SerDir+1 ) %2;
      switch ( butno ) {
          case 1:
          break;
      }
      kgSetAttnWidget ( Tbl->D , Tbl ) ;
      return ret;
}
void  kgeditKEDdirinit (DIN *B,void *ptmp) {
// may use kgChangeButtonNormalImage etc...
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
      BUT_STR *buts = ( BUT_STR * ) B->buts;
// if(buts[0].xpmn!= NULL) free(buts[0].xpmn);
      buts [ 0 ] .xpmp = ( void * ) kgUpdirImage ( 16 , 100 , 100 , 100 ) ;
      buts [ 0 ] .xpmn = ( void * ) kgDowndirImage ( 16 , 100 , 100 , 100 ) ;
}
  void ScrollTablebutton8init ( DIN *B , void *ptmp ) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
      BUT_STR *buts = ( BUT_STR * ) B->buts;
// if(buts[0].xpmn!= NULL) free(buts[0].xpmn);
      buts [ 0 ] .xpmp = ( void * ) kgUpdirImage ( 16 , 100 , 100 , 100 ) ;
      buts [ 0 ] .xpmn = ( void * ) kgDowndirImage ( 16 , 100 , 100 , 100 ) ;
  }

int kgeditKEDsetupcallback(int butno,int i,void *Tmp) {
  /*********************************** 
    butno : selected item (1 to max_item) 
    i :  Index of Widget  (0 to max_widgets-1) 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
      DIALOG *D;DIN *B;
      int n , ret = 0;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      int *ipt;
      Gclr *Gc;
      D = ( DIALOG * ) Tmp;
      Gc = & ( D->gc ) ;
      B = ( DIN * ) kgGetWidget ( Tmp , i ) ;
      n = B->nx*B->ny;
#if 1
      if ( ( ipt = ( int * ) RunSetup ( Tmp , Tbl ) ) != NULL ) {
          if ( Tbl->width < 2*Tbl->FontSize ) Tbl->width = 2*Tbl->FontSize;
          DefWidth = Tbl->width;
          Fz = Tbl->FontSize;
          kgDefineColor ( Gc->tabl_char , ipt [ 0 ] , ipt [ 1 ] , ipt [ 2 ] ) ;
          kgDefineColor ( Gc->tabl_hchar , ipt [ 3 ] , ipt [ 4 ] , ipt [ 5 ] ) ;
          kgDefineColor ( Gc->tabl_fill , ipt [ 6 ] , ipt [ 7 ] , ipt [ 8 ] ) ;
          kgDefineColor ( Gc->tabl_line , ipt [ 9 ] , ipt [ 10 ] , ipt [ 11 ] ) ;
          free ( ipt ) ;
          RedrawTable ( ) ;
      }
#endif
      switch ( butno ) {
          case 1:
          break;
      }
      kgSetAttnWidget ( Tbl->D , Tbl ) ;
      return ret;
  }
 void  kgeditKEDsetupinit (DIN *B,void *ptmp) {
      void **pt = ( void ** ) ptmp; //pt [ 0 ] is arg 
      BUT_STR *buts = ( BUT_STR * ) B->buts;
      free ( buts [ 0 ] .xpmn ) ;
      buts [ 0 ] .xpmn = ( void * ) & Setupimg_str;
  }
int kgeditKEDstboxcallback(int cellno,int i,void *Tmp) {
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
      strcpy(SrString,kgGetString(T,0));
      if ( SerDir ) SearchTbl ( ) ;
      else SearchTblRev ( ) ;
      kgSetAttnWidget ( Tbl->D , Tbl ) ;
      return ret;
}
int kgeditKEDrtboxcallback(int cellno,int i,void *Tmp) {
  /************************************************* 
   cellno: current cell counted along column strting with 0 
           ie 0 to (nx*ny-1) 
   i     : widget id starting from 0 
   Tmp   : Pointer to DIALOG 
   *************************************************/ 
  DIALOG *D;DIT *T;T_ELMT *e; 
  int ret=1;
  void **pt= (void **)kgGetArgPointer(Tmp); // Change as required
// pt[0] is args passed as inputs; pt[1] is output pointer
  D = (DIALOG *)Tmp;
  T = (DIT *)kgGetWidget(Tmp,i);
  e = T->elmt;
  kgSetAttnWidget ( Tbl->D , Tbl ) ;
  return ret;
}
int kgeditinit(void *Tmp) {
  /*********************************** 
    Tmp :  Pointer to DIALOG  
   ***********************************/ 
  /* you add any initialisation here */
      int ret = 1 , k;
      int nlines ;
      DIALOG *D;
      D = ( DIALOG * ) Tmp;
      char **Strs,Buf[300];
      char *cpt;
      BUT_STR *buts;
      DIN *AB;
      void **pt = ( void ** ) kgGetArgPointer ( Tmp ) ; // Change as required
      flname = ( char * ) pt [ 0 ] ;
      if(flname[0]=='\0') {
        strcpy(flname,getenv("PWD"));
        strcat(flname,"/");
        if(!kgFolderBrowser(Tmp,50,50,flname,"*")) exit(0);
      }
      Tbl = ( DIT * ) kgGetNamedWidget ( Tmp , ( char * ) "KEDtable" ) ;
      V = ( DIV * ) kgGetNamedWidget ( D , ( char * ) "KEDscroll" ) ;
      DII *I = (DII *)kgGetNamedWidget(Tmp,(char *)"KEDtitle");
      sprintf(Buf,"!z34!f12File : %-s",flname);
      kgWrite(I,Buf);
      DIP *P;
      P = ( DIP* ) kgGetNamedWidget ( D , ( char * ) "KEDarrow" ) ;
      AB = ( DIN* ) kgGetNamedWidget ( D , ( char * ) "KEDdir" ) ;
      buts = ( BUT_STR * ) AB->buts;
      P->xpm = buts [ 0 ] .xpmn ;
      kgUpdateWidget ( P ) ;
      SetupGrps ( ) ;
      Slist = Dreadfile ( flname ) ;
      MakeFileNames ( ) ;
      BLS = Dopen ( ) ;
      DLS = Dopen ( ) ;
      Strs = ( char ** ) Dlinktoarray ( Slist ) ;
      StartLine = EndLine = 1;
      LoadConfig ( Tmp ) ;
      E = Tbl->elmt;
      nlines = Tbl->ny;
      Nlines = Tbl->ny;
//      LoadConfig ( Tmp ) ;
      kgUpdateWidget ( Tbl ) ;
      if ( flname != NULL ) {
          if ( ( Strs == NULL ) || ( Strs [ 0 ] == NULL ) ) {
              cpt = ( char * ) malloc ( 2 ) ;
              strcpy ( cpt , "\n" ) ;
              Dadd ( Slist , cpt ) ;
              if ( Strs != NULL ) free ( Strs ) ;
              Strs = ( char ** ) Dlinktoarray ( Slist ) ;
          }
      }
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
      Count = Dcount ( Slist ) ;
      Resetlink ( Slist ) ;
      if ( Count <= Nlines ) kgSetWidgetVisibility ( V , 0 ) ;
      else {
          Vsize = ( double ) ( Nlines ) /Count*100.0;
          Vpos = 0;
          kgSetScrollLength ( V , Vsize ) ;
          kgSetScrollPos ( V , Vpos ) ;
          kgSetScrollMovement ( V , ( double ) Nlines/Count*100.0 ) ;
      }
      kgUpdateWidget ( V ) ;
      kgUpdateWidget ( Tbl ) ;
      kgSetTableCursor ( Tbl , 1 ) ;
      kgSetDefaultAttnWidget ( Tmp , Tbl ) ;
//      kgSetDefaultAttnWidget ( Tmp , ST ) ;
      SrString[0]='\0';
      ReString[0]='\0';
      Push ( ) ;
      kgEnableSelection ( Tmp ) ;
      kgUpdateOn ( Tmp ) ;
      free ( Strs ) ;
      return ret;
}
int kgeditcleanup(void *Tmp) {
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
int Modifykgedit(void *Tmp,int GrpId) {
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
  strcpy(D->name,"Kit (Kulina edITor) Ver. 4.0");    /*  Dialog name you may change */
//    sprintf(D->name,"%-s",(char *)pt[0]);
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
  B1 = (DIN *)kgGetNamedWidget(D,(char *)"KEDopt2");
  DB = (DIL *)kgGetNamedWidget(D,(char *)"KEDfinish");
  return GrpId;
}

int kgeditCallBack(void *Tmp,void *tmp) {
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
int kgeditResizeCallBack_o(void *Tmp) {
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
  int kgeditResizeCallBack ( void *Tmp ) {
  /***********************************
    Tmp :  Pointer to DIALOG
   ***********************************/
      int ret = 0 , k , nyo , nxo , i , j;
      int xres , yres , dx , dy , nymax , val;
      int xo , yo , xl , yl , Fz1 , Fz2 , nchr;
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
          DefWidth = Tbl->width;
      }
  /* extra code */
      if ( nydef == -1 ) nydef = Tbl->ny;
      elmt = ( T_ELMT * ) Tbl->elmt;
      nyo = Tbl->ny;
      nxo = Tbl->nx;
#if 1
      for ( j = 0;j < nyo;j++ ) {
          for ( i = 0;i < nxo;i++ ) {
              k = j*nxo+i;
              if ( elmt [ k ] .img != NULL ) {
                  kgFreeImage ( elmt [ k ] .img ) ;
              }
              elmt [ k ] .img = NULL;
          }
      }
#endif
      D->xl = xres;
      D->yl = yres;
      xl = DB->x2 -DB->x1;
      yl = DB->y2 -DB->y1;
      xo = ( D->xl-xl ) /2;
      DB->x1 = xo;
      DB->x2 = xo+xl;
      DB->y1 = D->yl- yl -2;
      DB->y2 = DB->y1 + yl;
#if 1
      xl = B1->x2 -B1->x1;
      yl = B1->y2 -B1->y1;
      xo = D->xl-xl-10;
      B1->x1 = xo;
      if ( B1->x1 > B1x ) B1->x1 = B1x;
      B1->x2 = B1->x1+xl;
#endif
      Tbl->x2 = xres - 40;
      Tbl->y2 = yres - 50;
      Fz1 = Fz;
      if ( Tbl->width < 2*Fz1 ) Tbl->width = 2*Fz1;
//      Tbl->ny = ( Tbl->y2 - Tbl->y1-4 ) /(2*Fz1);
      Tbl->ny = ( Tbl->y2 - Tbl->y1-4 ) / ( Tbl->width ) ;
      Fz2 = ( Tbl->y2 - Tbl->y1-4 ) / ( 2*Tbl->ny ) ;
      if ( Fz1 > Fz2 ) Fz1 = Fz2;
#if 0
      if ( Fz1 > 12 ) {
          Fz1 = 10;
          Tbl->ny = ( Tbl->y2 - Tbl->y1-4 ) / ( 2*Fz1 ) ;
      }
      else if ( Fz1 < 10 ) {
          Tbl->ny = 24;
          Fz1 = ( float ) ( Tbl->y2 - Tbl->y1-4 ) / ( 2*Tbl->ny ) +0.2;
      }
#endif
      nchr = ( Tbl->x2 - Tbl->x1 ) /Fz1 -11;
      Tbl->x2 = ( nchr+11 ) *Fz1+Tbl->x1;
      Tbl->ny = ( float ) ( Tbl->y2 - Tbl->y1-4 ) / ( Tbl->width ) +0.5;
      Tbl->y2 = Tbl->width* ( Tbl->ny ) +Tbl->y1+4;
      sprintf ( Fmt , "%%%ds" , nchr ) ;
      elmt = ( T_ELMT * ) Tbl->elmt;
      if ( Tbl->ny > nydef ) elmt = ( T_ELMT * ) realloc \
       ( elmt , Tbl->nx*Tbl->ny*sizeof ( T_ELMT ) ) ;
      Tbl->elmt = elmt;
      nymax = Tbl->ny;
      if ( nymax > nyo ) nymax = nyo;
      if ( nymax < nydef ) nymax = nydef;
      if ( nymax > Tbl->ny ) nymax = Tbl->ny;
      for ( k = 0;k < nymax;k++ ) {
          strcpy ( elmt [ k*Tbl->nx ] .fmt , ( char * ) "%4s" ) ;
          elmt [ k*Tbl->nx ] .sw = 0;
          elmt [ k*Tbl->nx ] .noecho = 0;
          elmt [ k*Tbl->nx ] .img = NULL;
          strcpy ( elmt [ k*Tbl->nx+1 ] .fmt , Fmt ) ;
          elmt [ k*Tbl->nx+1 ] .sw = 1;
          elmt [ k*Tbl->nx+1 ] .noecho = 0;
          elmt [ k*Tbl->nx+1 ] .img = NULL;
      }
//      if((Tbl->ny>nydef)&&(Tbl->ny > nyo)) {
      if ( ( Tbl->ny > nydef ) ) {
          int j = 0;
          char *cpt = NULL;
          vi = ( char * ) realloc ( vi , 20* ( Tbl->ny - nydef ) ) ;
          vs = ( char * ) realloc ( vs , 2000* ( Tbl->ny - nydef ) ) ;
          for ( k = nydef;k < Tbl->ny;k++ ) {
              elmt [ k*Tbl->nx ] .fmt = ( char * ) malloc ( 10 ) ;
              elmt [ k*Tbl->nx+1 ] .fmt = ( char * ) malloc ( 10 ) ;
              strcpy ( elmt [ k*Tbl->nx ] .fmt , ( char * ) "%4s" ) ;
              elmt [ k*Tbl->nx ] .sw = 0;
              elmt [ k*Tbl->nx ] .noecho = 0;
              elmt [ k*Tbl->nx ] .img = NULL;
              strcpy ( elmt [ k*Tbl->nx+1 ] .fmt , Fmt ) ;
              elmt [ k*Tbl->nx+1 ] .sw = 1;
              elmt [ k*Tbl->nx+1 ] .noecho = 0;
              elmt [ k*Tbl->nx+1 ] .img = NULL;
              elmt [ k*Tbl->nx ] .v = ( void * ) ( vi+j*20 ) ;
              elmt [ k*Tbl->nx +1 ] .v = ( void * ) ( vs+j*2000 ) ;
              cpt = ( char * ) elmt [ k*Tbl->nx ] .v;
              cpt [ 0 ] = '\0';
              cpt = ( char * ) elmt [ k*Tbl->nx +1 ] .v;
              cpt [ 0 ] = '\0';
              j++;
          }
      }
      Nlines = Tbl->ny;
      Tbl->FontSize = Fz1;
//      Tbl->width = DefWidth;;
      xl = V->x2 - V->x1;
      yl = V->y2 - V->y1;
      V->x1 = Tbl->x2+10;
      V->x2 = V->x1 + xl;
      V->y2 = Tbl->y2;
      yl = MT->y2 -MT->y1;
      MT->y1 = D->yl-35;
      MT->y2 = MT->y1+yl;
      yl = GB->y2 - GB->y1;
      GB->y1 = D->yl-36;
      GB->y2 = GB->y1+yl;
      DIN *H = (DIN *)kgGetNamedWidget((void *)D, (char *) "KEDhelp");
      H->y1 = D->yl-36;
      H->y2 = H->y1+yl;
      DIN *S = (DIN *)kgGetNamedWidget((void *)D, (char *) "KEDsetup");
      S->y1 = D->yl-36;
      S->y2 = S->y1+yl;
      kgRedrawDialog ( D ) ;
 //     if(Tbl->ny !=  nyo) {
      SetupTbl ( ) ;
      WriteTbl ( ) ;
      SetupVbar ( ) ;
 //     kgUpdateWidget ( V ) ;
//      kgUpdateWidget (Tbl ) ;
      kgUpdateOn ( D ) ;
//      }
      kgSetAttnWidget ( Tmp , Tbl ) ;
      return ret;
  }
int kgeditWaitCallBack(void *Tmp) {
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
