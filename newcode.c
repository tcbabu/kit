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
          if ( ReadTbl ( ) == 0 ) {
              kgScrollDownTable ( Tbl , Tbl->ny-1 ) ;
              WriteTblLine ( 0 ) ;
          }
          else {
              if ( EndLine < ( Count ) ) {
                  StartLine++;
                  EndLine++;
                  WriteTbl ( ) ;
              }
          }
          Vpos = ( double ) ( StartLine-1 ) *100.0/Count;
          kgSetScrollPos ( V , Vpos ) ;
          kgUpdateWidget ( V ) ;
          kgSetTableCursor ( Tbl , ( Nlines-1 ) *2+1 ) ;
          kgUpdateOn ( Tbl->D ) ;
          kgSkipEvents ( Tbl->D ) ;
      }
      else if ( cellno == SCROLL_UP ) {
          if ( ReadTbl ( ) == 0 ) {
              kgScrollUpTable ( Tbl , Tbl->ny-1 ) ;
              WriteTblLine ( Tbl->ny-1 ) ;
          }
