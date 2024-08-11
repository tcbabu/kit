#include <stdio.h>
#include <kulina.h>
extern char *flname;
  void *RunScrollTable ( void *, void * ) ;
  int main ( int argc , char **argv  ) {
      Dlink *S;
      char *pt;
      if(argc<2) return 0;
      flname=argv[1];
      S = RunScrollTable ( NULL , Dlinktoarray ( Dreadfile ( argv [ 1 ] ) ) ) ;
      if ( S != NULL ) {
          Dend ( S ) ;
          pt = ( char * ) Getrecord ( S ) ;
          if ( pt != NULL ) {
              if ( pt [ 0 ] == '\n' ) {Dend ( S ) ; Ddelete ( S ) ;}
          }
          Resetlink ( S ) ;
          Dwritefile ( S , argv [ 1 ] ) ;
          Dempty ( S ) ;
      }
      else fprintf ( stderr , "S is NULL\n" ) ;
      return 1;
  }
