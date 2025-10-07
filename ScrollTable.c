#include <kulina.h>
#include "ScrollTableCallbacks.h"
#include "GclrScrollTable.c"
  int ScrollTableGroup ( DIALOG *D , void **v , void *pt ) {
      int GrpId = 0 , oitems = 0 , i , j;
      DIA *d = NULL , *dtmp;
      T_ELMT *e0 ;
      e0 = ( T_ELMT * ) malloc ( sizeof ( T_ELMT ) *48 ) ;
      e0 [ 0 ] .fmt = ( char * ) malloc ( 4 ) ;
      strcpy ( e0 [ 0 ] .fmt , ( char * ) "%4s" ) ;
      e0 [ 0 ] .v = ( void * ) v [ 0 ] ;
      e0 [ 0 ] .sw = 0;
      e0 [ 0 ] .noecho = 0;
      e0 [ 0 ] .img = NULL;
      e0 [ 1 ] .fmt = ( char * ) malloc ( 5 ) ;
      strcpy ( e0 [ 1 ] .fmt , ( char * ) "%80s" ) ;
      e0 [ 1 ] .v = ( void * ) v [ 1 ] ;
      e0 [ 1 ] .sw = 1;
      e0 [ 1 ] .noecho = 0;
      e0 [ 1 ] .img = NULL;
      int Count0 = 2;
      for ( int j = 1;j < 24;j++ ) {
          for ( int i = 0;i < 2;i++ ) {
              e0 [ j*2+i ] .fmt = ( char * ) malloc ( strlen ( e0 [ i ] .fmt ) +1 ) ;
              strcpy ( e0 [ ( j ) *2+i ] .fmt , e0 [ i ] .fmt ) ;
              e0 [ ( j ) *2+i ] .v = ( void * ) v [ Count0+ ( j-1 ) *2+i ] ;
              e0 [ ( j ) *2+i ] .sw = e0 [ i ] .sw;
              e0 [ ( j ) *2+i ] .noecho = e0 [ i ] .noecho;
              e0 [ ( j ) *2+i ] .img = NULL;
          }
      }
      DIT T0 = {
          'T' , 8 , 66 , 925 , 557 , 20 , 2 , 24 , e0 , 0 , 1 , NULL , ScrollTabletablebox1callback , \
               0 , 0 , 16 , 10 /* args , Call back */
      };
      strcpy ( T0.Wid , ( char * ) "ScrollTable" ) ;
      T0.pt = NULL;
      T0.type = 0;
      T0.item = -1;
      DIV v1 = {
          'v' , 925 , 66 , 945 , 558 , 0 , 100.000000 , 0.000000 , 5.000000 , \
               NULL , ScrollTablevertscroll1callback /* *args , callback */
      };
      strcpy ( v1.Wid , ( char * ) "VertScroll" ) ;
      v1.item = -1;
      BUT_STR *butn2 = NULL;
      butn2 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *2 ) ;
      butn2 [ 0 ] .sw = 1;
      strcpy ( butn2 [ 0 ] .title , ( char * ) "!c31Abort" ) ;
      butn2 [ 0 ] .xpmn = NULL;
      butn2 [ 0 ] .xpmp = NULL;
      butn2 [ 0 ] .xpmh = NULL;
      butn2 [ 0 ] .bkgr = -235255250;
      butn2 [ 0 ] .butncode = 31;
      butn2 [ 1 ] .sw = 1;
      strcpy ( butn2 [ 1 ] .title , ( char * ) "!c38Done" ) ;
      butn2 [ 1 ] .xpmn = NULL;
      butn2 [ 1 ] .xpmp = NULL;
      butn2 [ 1 ] .xpmh = NULL;
      butn2 [ 1 ] .bkgr = -235255250;
      butn2 [ 1 ] .butncode = 31;
      DIL h2 = {
          'h' , 336 , 561 , 515 , 592 , 2 , 0 , 84 , 25 , 2 , 1 , 8 , 0.500000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn2 , ScrollTablesplbutton1callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( h2.Wid , ( char * ) "SplButn" ) ;
      h2.item = -1;
      BUT_STR *butn3 = NULL;
      butn3 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *3 ) ;
      butn3 [ 0 ] .sw = 1;
      strcpy ( butn3 [ 0 ] .title , ( char * ) "Del Line" ) ;
      butn3 [ 0 ] .xpmn = NULL;
      butn3 [ 0 ] .xpmp = NULL;
      butn3 [ 0 ] .xpmh = NULL;
      butn3 [ 0 ] .bkgr = -240245255;
      butn3 [ 0 ] .butncode = 125;
      butn3 [ 1 ] .sw = 1;
      strcpy ( butn3 [ 1 ] .title , ( char * ) "Add Line" ) ;
      butn3 [ 1 ] .xpmn = NULL;
      butn3 [ 1 ] .xpmp = NULL;
      butn3 [ 1 ] .xpmh = NULL;
      butn3 [ 1 ] .bkgr = -240245255;
      butn3 [ 1 ] .butncode = 125;
      butn3 [ 2 ] .sw = 1;
      strcpy ( butn3 [ 2 ] .title , ( char * ) "Insert Line" ) ;
      butn3 [ 2 ] .xpmn = NULL;
      butn3 [ 2 ] .xpmp = NULL;
      butn3 [ 2 ] .xpmh = NULL;
      butn3 [ 2 ] .bkgr = -240245255;
      butn3 [ 2 ] .butncode = 125;
      DIN b3 = {
          'n' , 712 , 36 , 914 , 66 , 2 , 2 , 64 , 24 , 3 , 1 , 7 , 0.300000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn3 , ScrollTablebutton1callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b3.Wid , ( char * ) "Button1" ) ;
      b3.item = -1;
      BUT_STR *butn4 = NULL;
      butn4 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *2 ) ;
      butn4 [ 0 ] .sw = 1;
      strcpy ( butn4 [ 0 ] .title , ( char * ) "Save" ) ;
      butn4 [ 0 ] .xpmn = NULL;
      butn4 [ 0 ] .xpmp = NULL;
      butn4 [ 0 ] .xpmh = NULL;
      butn4 [ 0 ] .bkgr = -221221221;
      butn4 [ 0 ] .butncode = 126;
      butn4 [ 1 ] .sw = 1;
      strcpy ( butn4 [ 1 ] .title , ( char * ) "Undo" ) ;
      butn4 [ 1 ] .xpmn = NULL;
      butn4 [ 1 ] .xpmp = NULL;
      butn4 [ 1 ] .xpmh = NULL;
      butn4 [ 1 ] .bkgr = -221221221;
      butn4 [ 1 ] .butncode = 126;
      DIN b4 = {
          'n' , 13 , 36 , 148 , 66 , 2 , 2 , 64 , 24 , 2 , 1 , 1 , 0.500000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn4 , ScrollTablebutton2callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b4.Wid , ( char * ) "Button2" ) ;
      b4.item = -1;
      T_ELMT *e5 ;
      e5 = ( T_ELMT * ) malloc ( sizeof ( T_ELMT ) *1 ) ;
      e5 [ 0 ] .fmt = ( char * ) malloc ( 5 ) ;
      strcpy ( e5 [ 0 ] .fmt , ( char * ) "%15s" ) ;
      e5 [ 0 ] .v = ( void * ) v [ 48 ] ;
      e5 [ 0 ] .sw = 1;
      e5 [ 0 ] .noecho = 0;
      e5 [ 0 ] .img = NULL;
      DIT t5 = {
          't' , 124 , 6 , 299 , 34 , 20 , 1 , 1 , e5 , 1 , 1 , NULL , ScrollTabletextbox1callback , \
               0 , 0 , 18 , 9 /* args , Call back */
      };
      strcpy ( t5.Wid , ( char * ) "SearchText" ) ;
      t5.pt = NULL;
      t5.type = 1;
      t5.item = -1;
      BUT_STR *butn6 = NULL;
      butn6 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn6 [ 0 ] .sw = 1;
      strcpy ( butn6 [ 0 ] .title , ( char * ) "Search" ) ;
      butn6 [ 0 ] .xpmn = NULL;
      butn6 [ 0 ] .xpmp = NULL;
      butn6 [ 0 ] .xpmh = NULL;
      butn6 [ 0 ] .bkgr = -240245255;
      butn6 [ 0 ] .butncode = -603980001;
      DIN b6 = {
          'n' , 47 , 6 , 124 , 36 , 2 , 2 , 72 , 24 , 1 , 1 , 7 , 0.300000 , 0 , 0 , \
               0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn6 , ScrollTablebutton3callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b6.Wid , ( char * ) "SearchButn" ) ;
      b6.item = -1;
      BUT_STR *butn7 = NULL;
      butn7 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *7 ) ;
      butn7 [ 0 ] .sw = 1;
      strcpy ( butn7 [ 0 ] .title , ( char * ) "Read in" ) ;
      butn7 [ 0 ] .xpmn = NULL;
      butn7 [ 0 ] .xpmp = NULL;
      butn7 [ 0 ] .xpmh = NULL;
      butn7 [ 0 ] .bkgr = -221221221;
      butn7 [ 0 ] .butncode = -2302850;
      butn7 [ 1 ] .sw = 1;
      strcpy ( butn7 [ 1 ] .title , ( char * ) "Mark" ) ;
      butn7 [ 1 ] .xpmn = NULL;
      butn7 [ 1 ] .xpmp = NULL;
      butn7 [ 1 ] .xpmh = NULL;
      butn7 [ 1 ] .bkgr = -221221221;
      butn7 [ 1 ] .butncode = -2302850;
      butn7 [ 2 ] .sw = 1;
      strcpy ( butn7 [ 2 ] .title , ( char * ) "Write To" ) ;
      butn7 [ 2 ] .xpmn = NULL;
      butn7 [ 2 ] .xpmp = NULL;
      butn7 [ 2 ] .xpmh = NULL;
      butn7 [ 2 ] .bkgr = -221221221;
      butn7 [ 2 ] .butncode = -2302850;
      butn7 [ 3 ] .sw = 1;
      strcpy ( butn7 [ 3 ] .title , ( char * ) "Cut" ) ;
      butn7 [ 3 ] .xpmn = NULL;
      butn7 [ 3 ] .xpmp = NULL;
      butn7 [ 3 ] .xpmh = NULL;
      butn7 [ 3 ] .bkgr = -221221221;
      butn7 [ 3 ] .butncode = -2302850;
      butn7 [ 4 ] .sw = 1;
      strcpy ( butn7 [ 4 ] .title , ( char * ) "Copy" ) ;
      butn7 [ 4 ] .xpmn = NULL;
      butn7 [ 4 ] .xpmp = NULL;
      butn7 [ 4 ] .xpmh = NULL;
      butn7 [ 4 ] .bkgr = -221221221;
      butn7 [ 4 ] .butncode = -2302850;
      butn7 [ 5 ] .sw = 1;
      strcpy ( butn7 [ 5 ] .title , ( char * ) "Paste" ) ;
      butn7 [ 5 ] .xpmn = NULL;
      butn7 [ 5 ] .xpmp = NULL;
      butn7 [ 5 ] .xpmh = NULL;
      butn7 [ 5 ] .bkgr = -221221221;
      butn7 [ 5 ] .butncode = -2302850;
      butn7 [ 6 ] .sw = 1;
      strcpy ( butn7 [ 6 ] .title , ( char * ) "Join" ) ;
      butn7 [ 6 ] .xpmn = NULL;
      butn7 [ 6 ] .xpmp = NULL;
      butn7 [ 6 ] .xpmh = NULL;
      butn7 [ 6 ] .bkgr = -221221221;
      butn7 [ 6 ] .butncode = -2302850;
      DIN b7 = {
          'n' , 148 , 36 , 616 , 66 , 2 , 2 , 64 , 24 , 7 , 1 , 1 , 0.500000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn7 , ScrollTablebutton4callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b7.Wid , ( char * ) "Optionals" ) ;
      b7.item = -1;
      BUT_STR *butn8 = NULL;
      butn8 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn8 [ 0 ] .sw = 1;
      strcpy ( butn8 [ 0 ] .title , ( char * ) "Replace" ) ;
      butn8 [ 0 ] .xpmn = NULL;
      butn8 [ 0 ] .xpmp = NULL;
      butn8 [ 0 ] .xpmh = NULL;
      butn8 [ 0 ] .bkgr = -240245255;
      butn8 [ 0 ] .butncode = 123;
      DIN b8 = {
          'n' , 299 , 6 , 369 , 36 , 2 , 2 , 64 , 24 , 1 , 1 , 7 , 0.300000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn8 , ScrollTablebutton5callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b8.Wid , ( char * ) "Replace" ) ;
      b8.item = -1;
      T_ELMT *e9 ;
      e9 = ( T_ELMT * ) malloc ( sizeof ( T_ELMT ) *1 ) ;
      e9 [ 0 ] .fmt = ( char * ) malloc ( 5 ) ;
      strcpy ( e9 [ 0 ] .fmt , ( char * ) "%15s" ) ;
      e9 [ 0 ] .v = ( void * ) v [ 49 ] ;
      e9 [ 0 ] .sw = 1;
      e9 [ 0 ] .noecho = 0;
      e9 [ 0 ] .img = NULL;
      DIT t9 = {
          't' , 370 , 6 , 545 , 36 , 20 , 1 , 1 , e9 , 1 , 1 , NULL , ScrollTabletextbox2callback , \
               0 , 0 , 18 , 9 /* args , Call back */
      };
      strcpy ( t9.Wid , ( char * ) "Tbox2" ) ;
      t9.pt = NULL;
      t9.type = 1;
      t9.item = -1;
      T_ELMT *e10 ;
      e10 = ( T_ELMT * ) malloc ( sizeof ( T_ELMT ) *1 ) ;
      e10 [ 0 ] .fmt = ( char * ) malloc ( 15 ) ;
      strcpy ( e10 [ 0 ] .fmt , ( char * ) "!h34MarkPos%4d" ) ;
      e10 [ 0 ] .v = ( void * ) v [ 50 ] ;
      e10 [ 0 ] .sw = 1;
      e10 [ 0 ] .noecho = 0;
      e10 [ 0 ] .img = NULL;
      DIT t10 = {
          't' , 10 , 558 , 162 , 586 , 20 , 1 , 1 , e10 , 1 , 1 , NULL , ScrollTabletextbox3callback , \
               0 , 0 , 18 , 9 /* args , Call back */
      };
      strcpy ( t10.Wid , ( char * ) "MarkText" ) ;
      t10.pt = NULL;
      t10.type = 0;
      t10.item = -1;
      BUT_STR *butn11 = NULL;
      butn11 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn11 [ 0 ] .sw = 1;
      strcpy ( butn11 [ 0 ] .title , ( char * ) "Go" ) ;
      butn11 [ 0 ] .xpmn = NULL;
      butn11 [ 0 ] .xpmp = NULL;
      butn11 [ 0 ] .xpmh = NULL;
      butn11 [ 0 ] .bkgr = -235255250;
      butn11 [ 0 ] .butncode = 126;
      DIN b11 = {
          'n' , 161 , 557 , 192 , 587 , 2 , 2 , 25 , 25 , 1 , 1 , 5 , 0.500000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn11 , ScrollTablebutton6callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b11.Wid , ( char * ) "Go" ) ;
      b11.item = -1;
      BUT_STR *butn12 = NULL;
      butn12 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn12 [ 0 ] .sw = 1;
      strcpy ( butn12 [ 0 ] .title , ( char * ) "" ) ;
      butn12 [ 0 ] .xpmn = NULL;
      butn12 [ 0 ] .xpmp = NULL;
      butn12 [ 0 ] .xpmh = NULL;
#if 1
      butn12 [ 0 ] .xpmn = ( char * ) malloc ( 100 ) ;
      strcpy ( butn12 [ 0 ] .xpmn , ( char * ) "##/usr/share/icons/Kulina/cog-icon-2-48x48.png" ) ;
          
#else
      butn12 [ 0 ] .xpmn = kgGetProcessedImage ( "##/usr/share/icons/Kulina/cog-icon-2-48x48.png" , \
           20 , 0.8 , 0 , 0 , 0 ) ;
#endif
      butn12 [ 0 ] .bkgr = -1;
      butn12 [ 0 ] .butncode = 126;
      DIN b12 = {
          'n' , 196 , 560 , 223 , 587 , 2 , 2 , 20 , 20 , 1 , 1 , 9 , 0.500000 , 0 , \
               0 , 0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn12 , ScrollTablebutton7callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b12.Wid , ( char * ) "Setup" ) ;
      b12.item = -1;
      BUT_STR *butn13 = NULL;
      butn13 = ( BUT_STR * ) malloc ( sizeof ( BUT_STR ) *1 ) ;
      butn13 [ 0 ] .sw = 1;
      strcpy ( butn13 [ 0 ] .title , ( char * ) "" ) ;
      butn13 [ 0 ] .xpmn = NULL;
      butn13 [ 0 ] .xpmp = NULL;
      butn13 [ 0 ] .xpmh = NULL;
      butn13 [ 0 ] .bkgr = -1;
      butn13 [ 0 ] .butncode = 126;
      DIN b13 = {
          'n' , 15 , 5 , 44 , 35 , 2 , 2 , 24 , 24 , 1 , 1 , 10 , 0.150000 , 0 , 0 , \
               0 , 1 , /* button type and roundinfg factor  \
              ( 0-0.5 ) , bordr , hide , nodrawbkgr*/
          butn13 , ScrollTablebutton8callback , /* Callbak */
          NULL /* any args */
      };
      strcpy ( b13.Wid , ( char * ) "Direction" ) ;
      b13.item = -1;
      char *xpm14 = NULL; /* pixmap info */
      DIP p14 = {
          'p' , 18 , 8 , 44 , 34 , ( void * ) xpm14 , -1 , /* bkgr colour */
          0 , 0 , 0.000000 /* border hide transparency*/
      };
      strcpy ( p14.Wid , ( char * ) "Arrow" ) ;
      p14.item = -1;
      dtmp = D->d;
      i = 0;
      if ( dtmp != NULL ) while ( dtmp [ i ] .t != NULL ) i++;
      dtmp = ( DIA * ) realloc ( dtmp , sizeof ( DIA ) * ( i+16 ) ) ;
      d = dtmp+i;
      d [ 15 ] .t = NULL;
      d [ 0 ] .t = ( DIT * ) malloc ( sizeof ( DIT ) ) ;
      *d [ 0 ] .t = T0;
      d [ 0 ] .t->item = -1;
      d [ 1 ] .t = ( DIT * ) malloc ( sizeof ( DIV ) ) ;
      *d [ 1 ] .v = v1;
      d [ 1 ] .v->item = -1;
      d [ 2 ] .t = ( DIT * ) malloc ( sizeof ( DIL ) ) ;
      *d [ 2 ] .h = h2;
      d [ 2 ] .h->item = -1;
      ScrollTablesplbutton1init ( d [ 2 ] .h , pt ) ;
      d [ 3 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 3 ] .N = b3;
      d [ 3 ] .N->item = -1;
      ScrollTablebutton1init ( d [ 3 ] .N , pt ) ;
      d [ 4 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 4 ] .N = b4;
      d [ 4 ] .N->item = -1;
      ScrollTablebutton2init ( d [ 4 ] .N , pt ) ;
      d [ 5 ] .t = ( DIT * ) malloc ( sizeof ( DIT ) ) ;
      *d [ 5 ] .t = t5;
      d [ 5 ] .t->item = -1;
      d [ 6 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 6 ] .N = b6;
      d [ 6 ] .N->item = -1;
      ScrollTablebutton3init ( d [ 6 ] .N , pt ) ;
      d [ 7 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 7 ] .N = b7;
      d [ 7 ] .N->item = -1;
      ScrollTablebutton4init ( d [ 7 ] .N , pt ) ;
      d [ 8 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 8 ] .N = b8;
      d [ 8 ] .N->item = -1;
      ScrollTablebutton5init ( d [ 8 ] .N , pt ) ;
      d [ 9 ] .t = ( DIT * ) malloc ( sizeof ( DIT ) ) ;
      *d [ 9 ] .t = t9;
      d [ 9 ] .t->item = -1;
      d [ 10 ] .t = ( DIT * ) malloc ( sizeof ( DIT ) ) ;
      *d [ 10 ] .t = t10;
      d [ 10 ] .t->item = -1;
      d [ 11 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 11 ] .N = b11;
      d [ 11 ] .N->item = -1;
      ScrollTablebutton6init ( d [ 11 ] .N , pt ) ;
      d [ 12 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 12 ] .N = b12;
      d [ 12 ] .N->item = -1;
      ScrollTablebutton7init ( d [ 12 ] .N , pt ) ;
      d [ 13 ] .t = ( DIT * ) malloc ( sizeof ( DIN ) ) ;
      *d [ 13 ] .N = b13;
      d [ 13 ] .N->item = -1;
      ScrollTablebutton8init ( d [ 13 ] .N , pt ) ;
      d [ 14 ] .t = ( DIT * ) malloc ( sizeof ( DIP ) ) ;
      *d [ 14 ] .p = p14;
      d [ 14 ] .p->item = -1;
      d [ 15 ] .t = NULL;
      GrpId = kgOpenGrp ( D ) ;
      D->d = dtmp;
      j = 0;
      while ( d [ j ] .t != NULL ) { kgAddtoGrp ( D , \
           GrpId , ( void * ) ( d [ j ] .t ) ) ;j++;}
      return GrpId;
  }
/* One can also use the following code to add Widgets to an existing Dialog */
  int MakeScrollTableGroup ( DIALOG *D , void *arg ) {
      int GrpId;
      WIDGETGRP *Gpt;
/*************************************************

    TableBox1  48 data values
    Text_Box1  1 data values
    Text_Box2  1 data values
    Text_Box3  1 data values

*************************************************/
      char *v0 ;
      v0 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v0 [ 0 ] = '\0';
      char *v1 ;
      v1 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v1 [ 0 ] = '\0';
      char *v2 ;
      v2 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v2 [ 0 ] = '\0';
      char *v3 ;
      v3 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v3 [ 0 ] = '\0';
      char *v4 ;
      v4 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v4 [ 0 ] = '\0';
      char *v5 ;
      v5 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v5 [ 0 ] = '\0';
      char *v6 ;
      v6 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v6 [ 0 ] = '\0';
      char *v7 ;
      v7 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v7 [ 0 ] = '\0';
      char *v8 ;
      v8 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v8 [ 0 ] = '\0';
      char *v9 ;
      v9 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v9 [ 0 ] = '\0';
      char *v10 ;
      v10 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v10 [ 0 ] = '\0';
      char *v11 ;
      v11 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v11 [ 0 ] = '\0';
      char *v12 ;
      v12 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v12 [ 0 ] = '\0';
      char *v13 ;
      v13 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v13 [ 0 ] = '\0';
      char *v14 ;
      v14 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v14 [ 0 ] = '\0';
      char *v15 ;
      v15 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v15 [ 0 ] = '\0';
      char *v16 ;
      v16 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v16 [ 0 ] = '\0';
      char *v17 ;
      v17 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v17 [ 0 ] = '\0';
      char *v18 ;
      v18 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v18 [ 0 ] = '\0';
      char *v19 ;
      v19 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v19 [ 0 ] = '\0';
      char *v20 ;
      v20 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v20 [ 0 ] = '\0';
      char *v21 ;
      v21 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v21 [ 0 ] = '\0';
      char *v22 ;
      v22 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v22 [ 0 ] = '\0';
      char *v23 ;
      v23 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v23 [ 0 ] = '\0';
      char *v24 ;
      v24 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v24 [ 0 ] = '\0';
      char *v25 ;
      v25 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v25 [ 0 ] = '\0';
      char *v26 ;
      v26 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v26 [ 0 ] = '\0';
      char *v27 ;
      v27 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v27 [ 0 ] = '\0';
      char *v28 ;
      v28 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v28 [ 0 ] = '\0';
      char *v29 ;
      v29 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v29 [ 0 ] = '\0';
      char *v30 ;
      v30 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v30 [ 0 ] = '\0';
      char *v31 ;
      v31 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v31 [ 0 ] = '\0';
      char *v32 ;
      v32 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v32 [ 0 ] = '\0';
      char *v33 ;
      v33 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v33 [ 0 ] = '\0';
      char *v34 ;
      v34 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v34 [ 0 ] = '\0';
      char *v35 ;
      v35 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v35 [ 0 ] = '\0';
      char *v36 ;
      v36 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v36 [ 0 ] = '\0';
      char *v37 ;
      v37 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v37 [ 0 ] = '\0';
      char *v38 ;
      v38 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v38 [ 0 ] = '\0';
      char *v39 ;
      v39 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v39 [ 0 ] = '\0';
      char *v40 ;
      v40 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v40 [ 0 ] = '\0';
      char *v41 ;
      v41 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v41 [ 0 ] = '\0';
      char *v42 ;
      v42 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v42 [ 0 ] = '\0';
      char *v43 ;
      v43 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v43 [ 0 ] = '\0';
      char *v44 ;
      v44 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v44 [ 0 ] = '\0';
      char *v45 ;
      v45 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v45 [ 0 ] = '\0';
      char *v46 ;
      v46 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v46 [ 0 ] = '\0';
      char *v47 ;
      v47 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v47 [ 0 ] = '\0';
      char *v48 ;
      v48 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v48 [ 0 ] = '\0';
      char *v49 ;
      v49 = ( char * ) malloc ( sizeof ( char ) *500 ) ;
      v49 [ 0 ] = '\0';
      int *v50 ;
      v50 = ( int * ) malloc ( sizeof ( int ) ) ;
      *v50 = 1;
      void** v = ( void ** ) malloc ( sizeof ( void* ) *52 ) ;
      v [ 51 ] = NULL;
      v [ 0 ] = ( void * ) ( v0 ) ;
      v [ 1 ] = ( void * ) ( v1 ) ;
      v [ 2 ] = ( void * ) ( v2 ) ;
      v [ 3 ] = ( void * ) ( v3 ) ;
      v [ 4 ] = ( void * ) ( v4 ) ;
      v [ 5 ] = ( void * ) ( v5 ) ;
      v [ 6 ] = ( void * ) ( v6 ) ;
      v [ 7 ] = ( void * ) ( v7 ) ;
      v [ 8 ] = ( void * ) ( v8 ) ;
      v [ 9 ] = ( void * ) ( v9 ) ;
      v [ 10 ] = ( void * ) ( v10 ) ;
      v [ 11 ] = ( void * ) ( v11 ) ;
      v [ 12 ] = ( void * ) ( v12 ) ;
      v [ 13 ] = ( void * ) ( v13 ) ;
      v [ 14 ] = ( void * ) ( v14 ) ;
      v [ 15 ] = ( void * ) ( v15 ) ;
      v [ 16 ] = ( void * ) ( v16 ) ;
      v [ 17 ] = ( void * ) ( v17 ) ;
      v [ 18 ] = ( void * ) ( v18 ) ;
      v [ 19 ] = ( void * ) ( v19 ) ;
      v [ 20 ] = ( void * ) ( v20 ) ;
      v [ 21 ] = ( void * ) ( v21 ) ;
      v [ 22 ] = ( void * ) ( v22 ) ;
      v [ 23 ] = ( void * ) ( v23 ) ;
      v [ 24 ] = ( void * ) ( v24 ) ;
      v [ 25 ] = ( void * ) ( v25 ) ;
      v [ 26 ] = ( void * ) ( v26 ) ;
      v [ 27 ] = ( void * ) ( v27 ) ;
      v [ 28 ] = ( void * ) ( v28 ) ;
      v [ 29 ] = ( void * ) ( v29 ) ;
      v [ 30 ] = ( void * ) ( v30 ) ;
      v [ 31 ] = ( void * ) ( v31 ) ;
      v [ 32 ] = ( void * ) ( v32 ) ;
      v [ 33 ] = ( void * ) ( v33 ) ;
      v [ 34 ] = ( void * ) ( v34 ) ;
      v [ 35 ] = ( void * ) ( v35 ) ;
      v [ 36 ] = ( void * ) ( v36 ) ;
      v [ 37 ] = ( void * ) ( v37 ) ;
      v [ 38 ] = ( void * ) ( v38 ) ;
      v [ 39 ] = ( void * ) ( v39 ) ;
      v [ 40 ] = ( void * ) ( v40 ) ;
      v [ 41 ] = ( void * ) ( v41 ) ;
      v [ 42 ] = ( void * ) ( v42 ) ;
      v [ 43 ] = ( void * ) ( v43 ) ;
      v [ 44 ] = ( void * ) ( v44 ) ;
      v [ 45 ] = ( void * ) ( v45 ) ;
      v [ 46 ] = ( void * ) ( v46 ) ;
      v [ 47 ] = ( void * ) ( v47 ) ;
      v [ 48 ] = ( void * ) ( v48 ) ;
      v [ 49 ] = ( void * ) ( v49 ) ;
      v [ 50 ] = ( void * ) ( v50 ) ;
      void *pt = NULL; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      GrpId = ScrollTableGroup ( D , v , pt ) ;
      Gpt = kgGetWidgetGrp ( D , GrpId ) ;
      Gpt->arg = v; // kulina will double free this; you may modify
      return GrpId;
  }
  int ScrollTable ( void *parent , void **v , void *pt ) {
      int ret = 1 , GrpId , k;
      DIALOG D;
      DIA *d = NULL;
      D.VerId = 2107030000;
      kgInitUi ( & D ) ;
      D.d = NULL;
#if 1
      GrpId = ScrollTableGroup ( & D , v , pt ) ;
#else 
      GrpId = MakeScrollTableGroup ( & D , pt ) ; // can try this also
#endif 
      d = D.d;
      D.d = d;
      D.bkup = 1; /* set to 1 for backup */
      D.bor_type = 4;
      D.df = 13;
      D.tw = 4;
      D.bw = 4;
      D.lw = 4;
      D.rw = 4;
      D.xo = 768; /* Position of Dialog */
      D.yo = 141;
      D.xl = 957; /* Length of Dialog */
      D.yl = 601; /* Width of Dialog */
      D.Initfun = ScrollTableinit; /* init fuction for Dialog */
      D.Cleanupfun = ScrollTablecleanup; /* init fuction for Dialog */
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
      D.Resize = 1; /* 1 for Resize option */
      D.MinWidth = 760; /* for Resize option */
      D.MinHeight = 400; /* for Resize option */
#if 1 
      D.Callback = ScrollTableCallBack; /* default callback */
#else 
      D.Callback = NULL;
#endif
      D.ResizeCallback = ScrollTableResizeCallBack; /* Resize callback */
#if 0 
      D.WaitCallback = NULL; /* Wait callback */
#else 
      D.WaitCallback = ScrollTableWaitCallBack; /* Wait callback */
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
      ModifyScrollTable ( & D , GrpId ) ; /* add extras to gui*/
      ModifyScrollTableGc ( & D ) ; /* set colors for gui if do not like default*/
      ret = kgUi ( & D ) ;
      kgCleanUi ( & D ) ;
      return ret;
  }
  void *RunScrollTable ( void *parent , void *args ) {
/*************************************************

    TableBox1  48 data values
    Text_Box1  1 data values
    Text_Box2  1 data values
    Text_Box3  1 data values

*************************************************/
      char v0 [ 500 ] = "" ;
      char v1 [ 500 ] = "" ;
      char v2 [ 500 ] = "" ;
      char v3 [ 500 ] = "" ;
      char v4 [ 500 ] = "" ;
      char v5 [ 500 ] = "" ;
      char v6 [ 500 ] = "" ;
      char v7 [ 500 ] = "" ;
      char v8 [ 500 ] = "" ;
      char v9 [ 500 ] = "" ;
      char v10 [ 500 ] = "" ;
      char v11 [ 500 ] = "" ;
      char v12 [ 500 ] = "" ;
      char v13 [ 500 ] = "" ;
      char v14 [ 500 ] = "" ;
      char v15 [ 500 ] = "" ;
      char v16 [ 500 ] = "" ;
      char v17 [ 500 ] = "" ;
      char v18 [ 500 ] = "" ;
      char v19 [ 500 ] = "" ;
      char v20 [ 500 ] = "" ;
      char v21 [ 500 ] = "" ;
      char v22 [ 500 ] = "" ;
      char v23 [ 500 ] = "" ;
      char v24 [ 500 ] = "" ;
      char v25 [ 500 ] = "" ;
      char v26 [ 500 ] = "" ;
      char v27 [ 500 ] = "" ;
      char v28 [ 500 ] = "" ;
      char v29 [ 500 ] = "" ;
      char v30 [ 500 ] = "" ;
      char v31 [ 500 ] = "" ;
      char v32 [ 500 ] = "" ;
      char v33 [ 500 ] = "" ;
      char v34 [ 500 ] = "" ;
      char v35 [ 500 ] = "" ;
      char v36 [ 500 ] = "" ;
      char v37 [ 500 ] = "" ;
      char v38 [ 500 ] = "" ;
      char v39 [ 500 ] = "" ;
      char v40 [ 500 ] = "" ;
      char v41 [ 500 ] = "" ;
      char v42 [ 500 ] = "" ;
      char v43 [ 500 ] = "" ;
      char v44 [ 500 ] = "" ;
      char v45 [ 500 ] = "" ;
      char v46 [ 500 ] = "" ;
      char v47 [ 500 ] = "" ;
      char v48 [ 500 ] = "" ;
      char v49 [ 500 ] = "" ;
      int v50 = 1;
      void* v [ 51 ] ;
      v [ 0 ] = ( void * ) ( v0 ) ;
      v [ 1 ] = ( void * ) ( v1 ) ;
      v [ 2 ] = ( void * ) ( v2 ) ;
      v [ 3 ] = ( void * ) ( v3 ) ;
      v [ 4 ] = ( void * ) ( v4 ) ;
      v [ 5 ] = ( void * ) ( v5 ) ;
      v [ 6 ] = ( void * ) ( v6 ) ;
      v [ 7 ] = ( void * ) ( v7 ) ;
      v [ 8 ] = ( void * ) ( v8 ) ;
      v [ 9 ] = ( void * ) ( v9 ) ;
      v [ 10 ] = ( void * ) ( v10 ) ;
      v [ 11 ] = ( void * ) ( v11 ) ;
      v [ 12 ] = ( void * ) ( v12 ) ;
      v [ 13 ] = ( void * ) ( v13 ) ;
      v [ 14 ] = ( void * ) ( v14 ) ;
      v [ 15 ] = ( void * ) ( v15 ) ;
      v [ 16 ] = ( void * ) ( v16 ) ;
      v [ 17 ] = ( void * ) ( v17 ) ;
      v [ 18 ] = ( void * ) ( v18 ) ;
      v [ 19 ] = ( void * ) ( v19 ) ;
      v [ 20 ] = ( void * ) ( v20 ) ;
      v [ 21 ] = ( void * ) ( v21 ) ;
      v [ 22 ] = ( void * ) ( v22 ) ;
      v [ 23 ] = ( void * ) ( v23 ) ;
      v [ 24 ] = ( void * ) ( v24 ) ;
      v [ 25 ] = ( void * ) ( v25 ) ;
      v [ 26 ] = ( void * ) ( v26 ) ;
      v [ 27 ] = ( void * ) ( v27 ) ;
      v [ 28 ] = ( void * ) ( v28 ) ;
      v [ 29 ] = ( void * ) ( v29 ) ;
      v [ 30 ] = ( void * ) ( v30 ) ;
      v [ 31 ] = ( void * ) ( v31 ) ;
      v [ 32 ] = ( void * ) ( v32 ) ;
      v [ 33 ] = ( void * ) ( v33 ) ;
      v [ 34 ] = ( void * ) ( v34 ) ;
      v [ 35 ] = ( void * ) ( v35 ) ;
      v [ 36 ] = ( void * ) ( v36 ) ;
      v [ 37 ] = ( void * ) ( v37 ) ;
      v [ 38 ] = ( void * ) ( v38 ) ;
      v [ 39 ] = ( void * ) ( v39 ) ;
      v [ 40 ] = ( void * ) ( v40 ) ;
      v [ 41 ] = ( void * ) ( v41 ) ;
      v [ 42 ] = ( void * ) ( v42 ) ;
      v [ 43 ] = ( void * ) ( v43 ) ;
      v [ 44 ] = ( void * ) ( v44 ) ;
      v [ 45 ] = ( void * ) ( v45 ) ;
      v [ 46 ] = ( void * ) ( v46 ) ;
      v [ 47 ] = ( void * ) ( v47 ) ;
      v [ 48 ] = ( void * ) ( v48 ) ;
      v [ 49 ] = ( void * ) ( v49 ) ;
      v [ 50 ] = ( void * ) ( & v50 ) ;
      void *pt [ 2 ] = {NULL , NULL}; /* pointer to send any extra information */
                  /* it will be aviilable in Callbacks */
      pt [ 0 ] = args;
      ScrollTable ( parent , v , ( void * ) pt ) ;
      return pt [ 1 ] ;
  }
