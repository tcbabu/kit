#include <stdio.h>
#include <kulina.h>
  extern char *flname;
  void *RunScrollTable ( void *, void * ) ;
  int main ( int argc , char **argv ) {
      Dlink *S;
      char *pt;
      if ( argc < 2 ) {
//	      fprintf(stderr,"Usage: %s [file]\n",argv[0]);
//	      return 0;
          RunScrollTable ( NULL , NULL ) ;
          return 1;
      }
      flname = argv [ 1 ] ;
      RunScrollTable ( NULL , argv [ 1 ] ) ;
#if 0
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
#endif
      return 1;
  }
