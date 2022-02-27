/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



/*===[[ LAYOUT ]]=============================================================*/
/*---(window formatting)-------------------*/
typedef struct  cWIN  tWIN;
struct cWIN {
   /*---(header)------------*/
   char        a_format;                    /* format identifier              */
   char        a_adapt;                     /* adapt to add elements          */
   int         a_wide;                      /* asking width                   */
   int         a_tall;                      /* asking heigth                  */
   /*---(main sizes)--------*/
   int         grid_on;                     /* show grid over main y/n        */
   int         cursor_on;                   /* show grid over main y/n        */
   int         m_xmin;
   int         m_xmax;
   int         m_ymin;
   int         m_ymax;
   /*---(ribbon)------------*/
   int         r_icons     [LEN_LABEL];     /* actual icons for ribbon        */
   int         r_nicon;                     /* number of icons                */
   /*---(display)-----------*/
   /*> char        face;                                                              <*/
   /*> int         font;                                                              <*/
   int         icons;
   /*---(done)--------------*/
};
static tWIN   s_win;


tPARTS  g_parts [MAX_PARTS] = {
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_TITLE     , "title"       , OWN_FULLY  , 'y',    1, '-', '-', 0, 0, 0,    1, '-', '-', '-', 0, 0, 0,  'w', NULL  , "",  NULL  , 'r', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTRIG  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "left hand title bar"                                },
   { YVIEW_VERSION   , "version"     , OWN_FULLY  , 'y',    1, '/', '-', 0, 0, 0,    9, '-', 't', '-', 0, 0, 0,  'B', NULL  , "",  NULL  , 'r', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTRIG  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "version display with debugging notice"              },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_BUFFER    , "buffer"      , OWN_FULLY  , '-',    2, '-', '-', 0, 0, 0,    7, '-', '-', '-', 0, 0, 0,  't', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "buffer inventory at top"                            },
   { YVIEW_FORMULA   , "formula"     , OWN_FULLY  , '-',    2, '-', '-', 0, 0, 0,    6, '-', '-', '-', 0, 0, 0,  't', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "formula and source editing line at top"             },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_NAV       , "nav"         , OWN_PARTLY , '-',    2, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  'w', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "navigation panel to display tags and other links"   },
   { YVIEW_LAYERS    , "layers"      , OWN_PARTLY , '-',    2, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  'w', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "displays all selected laysers over working"         },
   { YVIEW_YAXIS     , "yaxis"       , OWN_PARTLY , '-',    3, '-', '-', 0, 0, 0,    4, '-', '-', '-', 0, 0, 0,  'w', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "show the y-axis labels left of the main screen"     },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_XAXIS     , "xaxis"       , OWN_PARTLY , '-',    3, '/', '-', 0, 0, 0,    5, '-', '-', '-', 0, 0, 0,  't', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "show the x-axis labels above the main screen"       },
   { YVIEW_ALT       , "alt"         , OWN_LITTLE , '-',    5, '-', '-', 0, 0, 0,    4, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "alternate working area or view"                     },
   { YVIEW_PROGRESS  , "progress"    , OWN_PARTLY , '-',    3, '/', '-', 0, 0, 0,    3, '-', '-', '-', 0, 0, 0,  't', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "time and sequencing controls about status line"     },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_DETAILS   , "details"     , OWN_PARTLY , '-',    6, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  'w', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "display area for critical details to right"         },
   { YVIEW_RIBBON    , "ribbon"      , OWN_FULLY  , '-',    7, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  'w', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "menu and icon display for navigation of commands"   },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_MODES     , "modes"       , OWN_FULLY  , 'y',    2, '/', '-', 0, 0, 0,    2, '-', '-', '-', 0, 0, 0,  'B', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "informational to display current mode/submode"      },
   { YVIEW_STATUS    , "status"      , OWN_FULLY  , 'y',    9, '-', 'x', 0, 0, 0,    2, '-', '-', '-', 0, 0, 0,  't', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "informational status bar above command line"        },
   { YVIEW_COMMAND   , "command"     , OWN_FULLY  , 'y',    2, '-', '-', 0, 0, 0,    1, '-', '-', '-', 0, 0, 0,  't', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "command, search, and help message line at bottom"   },
   { YVIEW_KEYS      , "keys"        , OWN_FULLY  , 'y',    9, '/', 'c', 0, 0, 0,    1, '-', '-', '-', 0, 0, 0,  'B', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "latest keyboard characters typed"                   },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_GRID      , "grid"        , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , 1.00, 0              , 0, 0, 0, 0, 0, 0,  "overlay main drawing with a grid"                   },
   { YVIEW_CURSOR    , "cursor"      , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , 1.00, 0              , 0, 0, 0, 0, 0, 0,  "cursor display on screen"                           },
   { YVIEW_OVERLAY   , "overlay"     , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , 1.00, YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "shown over the working screen"                      },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_NOTES     , "notes"       , OWN_OVERLAY, 'y',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , 1.00, 0              , 0, 0, 0, 0, 0, 0,  "overlay for interactive notation"                   },
   { YVIEW_FLOAT     , "float"       , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPALL  , 1.00, YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "shown over the working screen"                      },
   { YVIEW_HISTORY   , "history"     , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_ALLFUL  , 1.00, YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "list of command/search history"                     },
   { YVIEW_MENUS     , "menus"       , OWN_OVERLAY, 'y',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPCEN  , 1.00, YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "interactive menu overlay"                           },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_MAIN      , "main"        , OWN_MAIN   , 'y',    4, '-', '-', 0, 0, 0,    4, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , 1.00, YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "main working area in the middle"                    },
   { YVIEW_MASK      , "mask"        , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , 0             , 1.00, 0              , 0, 0, 0, 0, 0, 0,  "desktop presentation mask for display"              },
   { YVIEW_WINDOW    , "window"      , OWN_DATA   , '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , 0             , 1.00, 0              , 0, 0, 0, 0, 0, 0,  "full screen width and height"                       },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   defs source, txt  drawer  ori  type---------  ---mgmt-------  ---anchor-----  magn  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { 0               , ""            , 0          , '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , '-', YVIEW_FLAT   , YVIEW_AUTO    , 0             , 0.00, 0              , 0, 0, 0, 0, 0, 0,  ""                                                   },
};

/*  lef/rig1----- 2----- 3----- 4----- 5----- 6----- 7-----
 * top/bot
 *     7   vers-- buffer---------------------------------->
 *     6   �----� formula--------------------------------->
 *     5   �    � �----� xaxis--------------> �----� �----�
 *     4   �    � �    � yaxis� MAIN-- alt--- �    � �    �
 *     3   �    � nav--� progress------------ detail ribbon
 *     2   �    � modes- status--------------------------->
 *     1   title� command--------------------------> keys->
 *
 *     0 in either means do not consider/show
 *     9 means tied to another element, handle width/height special
 *
 */



static  char        s_abbr   =  '-';
static  char        s_pindex =  -10;
static  tPARTS     *s_part   = NULL;
static  char        s_atype  =    0;
static  char        s_aindex =  -10;
static  tPARTS     *s_link   = NULL;



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yview_parts_init        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(screen parts)-------------------*/
   myVIEW.npart = 0;
   for (i = 0; i < MAX_PARTS; ++i) {
      if (g_parts [i].abbr == 0)  break;
      DEBUG_YVIEW   yLOG_info    ("name"      , g_parts [i].name);
      ++(myVIEW.npart);
   }
   DEBUG_YVIEW   yLOG_value   ("npart"     , myVIEW.npart);
   /*---(defaults)-----------------------*/
   yview_factory    (myVIEW.env);
   /*---(ribbon)-------------------------*/
   /*> for (i = 0; i < LEN_LABEL; ++i)  s_win.r_icons [i] = -1;                       <* 
    *> s_win.r_nicon = 0;                                                             <*/
   /*---(floating)-----------------------*/
   yview_set_anchor (YVIEW_FLOAT  , YVIEW_TOPALL);
   yview_set_anchor (YVIEW_MENUS  , YVIEW_TOPCEN);
   yview_set_anchor (YVIEW_HISTORY, YVIEW_ALLFUL);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        finding parts                         ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char
yview__find_link        (char n, char *r_a, tPARTS **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        a           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_sint    (n);
   /*---(check for link)-----------------*/
   DEBUG_YVIEW   yLOG_spoint  (r_link);
   if (r_link == NULL) {
      DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   DEBUG_YVIEW   yLOG_spoint  (r_a);
   if (r_a    == NULL) {
      DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   *r_link = NULL;
   DEBUG_YVIEW   yLOG_schar   (g_parts [n].x_tie);
   DEBUG_YVIEW   yLOG_schar   (g_parts [n].y_tie);
   /*> if (g_parts [n].x_tie == '-' && g_parts [n].y_tie == '-') {                    <* 
    *>    DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(find link)----------------------*/
   for (i = 0; i < myVIEW.npart; ++i) {
      if (g_parts [i].abbr  == g_parts [n].x_tie)  { rc = 1; break; }
      if (g_parts [i].abbr  == g_parts [n].y_tie)  { rc = 1; break; }
      if (g_parts [i].x_tie == g_parts [n].abbr )  { rc = 2; break; }
      if (g_parts [i].y_tie == g_parts [n].abbr )  { rc = 2; break; }
      if (g_parts [n].abbr  == YVIEW_NAV    && g_parts [i].abbr == YVIEW_LAYERS)   { rc = 3; break; }
      if (g_parts [n].abbr  == YVIEW_LAYERS && g_parts [i].abbr == YVIEW_NAV)      { rc = 3; break; }
   }
   DEBUG_YVIEW   yLOG_sint    (rc);
   if (rc > 0) {
      *r_a    = i;
      DEBUG_YVIEW   yLOG_sint    (*r_a);
      *r_link = &(g_parts [i]);
      DEBUG_YVIEW   yLOG_spoint  (*r_link);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return rc;
}

char
yview__parts_saved      (tPARTS **r_part, tPARTS **r_link)
{
   if (r_part != NULL)  *r_part = s_part;
   if (r_link != NULL)  *r_link = s_link;
   return s_pindex;
}

char
yview__parts_saving     (cchar a_abbr, cchar n, tPARTS *a_part, cchar a_type, cchar a, tPARTS *a_link)
{
   s_abbr     = a_abbr;
   s_pindex   = n;
   s_part     = a_part;
   s_atype    = a_type;
   s_aindex   = a;
   s_link     = a_link;
   return 0;
}

char         /*-> locate screen parts by abbrev ------[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_by_abbr           (cchar  a_abbr, tPARTS **r_part, tPARTS **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        n           =   -1;
   char        a           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_sint    (a_abbr);
   /*---(defaults)-----------------------*/
   if (r_part != NULL)  *r_part = NULL;
   if (r_link != NULL)  *r_link = NULL;
   /*---(short-cut)----------------------*/
   if (a_abbr == s_abbr) {
      DEBUG_YVIEW   yLOG_snote   ("short-cut using saved");
      DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
      return yview__parts_saved (r_part, r_link);
   }
   /*---(defense)------------------------*/
   --rce;  if (a_abbr <= G_KEY_SPACE || a_abbr >= G_KEY_TILDA) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_schar   (a_abbr);
   DEBUG_YVIEW   yLOG_sint    (myVIEW.npart);
   /*---(find the screen part)-----------*/
   for (i = 0; i < myVIEW.npart; ++i) {
      DEBUG_YVIEW   yLOG_sint    (i);
      if (g_parts [i].abbr != a_abbr)         continue;
      n = i;
      break;
   }
   DEBUG_YVIEW   yLOG_sint    (n);
   --rce;  if (n < 0) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_snote   (g_parts [n].name);
   /*---(save back)----------------------*/
   yview__parts_saving (a_abbr, n, g_parts + n, 0, -1, NULL);
   if (r_part != NULL)   *r_part = &(g_parts [n]);
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   /*---(run link)-----------------------*/
   rc = yview__find_link (n, &a, r_link);
   yview__parts_saving (a_abbr, n, g_parts + n, rc, a, g_parts + a);
   /*---(complete)-----------------------*/
   return rc;
}

char
yview_by_index          (int n, tPARTS **r_part, tPARTS **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        x_abbr      =    0;
   char        a           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_sint    (n);
   /*---(defaults)-----------------------*/
   if (r_part != NULL)  *r_part = NULL;
   if (r_link != NULL)  *r_link = NULL;
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_sint    (n);
   DEBUG_YVIEW   yLOG_sint    (myVIEW.npart);
   --rce;  if (n < 0 || n >= myVIEW.npart) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find the screen part)-----------*/
   for (i = 0; i < myVIEW.npart; ++i) {
      DEBUG_YVIEW   yLOG_sint    (i);
      if (i != n)  continue;
      x_abbr = g_parts [i].abbr;
      break;
   }
   DEBUG_YVIEW   yLOG_sint    (x_abbr);
   --rce;  if (x_abbr < 0) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_schar   (g_parts [n].abbr);
   /*---(save back)----------------------*/
   yview__parts_saving (x_abbr, n, g_parts + n, 0, -1, NULL);
   if (r_part != NULL)   *r_part = &(g_parts [n]);
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   /*---(run link)-----------------------*/
   rc = yview__find_link (n, &a, r_link);
   yview__parts_saving (x_abbr, n, g_parts + n, rc, a, g_parts + a);
   /*---(complete)-----------------------*/
   return rc;
}

char
yview_by_name           (cchar *a_name, tPARTS **r_part, tPARTS **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   char        n           =   -1;
   char        x_abbr      =    0;
   char        a           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_spoint  (a_name);
   /*---(defaults)-----------------------*/
   if (r_part != NULL)  *r_part = NULL;
   if (r_link != NULL)  *r_link = NULL;
   /*---(defense)------------------------*/
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_snote   (a_name);
   DEBUG_YVIEW   yLOG_sint    (myVIEW.npart);
   /*---(find the screen part)-----------*/
   for (i = 0; i < myVIEW.npart; ++i) {
      DEBUG_YVIEW   yLOG_sint    (i);
      if (strcmp (g_parts [i].name, a_name) != 0)   continue;
      n = i;
      x_abbr = g_parts [i].abbr;
      break;
   }
   DEBUG_YVIEW   yLOG_sint    (n);
   --rce;  if (n < 0) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_schar   (g_parts [n].abbr);
   /*---(save back)----------------------*/
   yview__parts_saving (x_abbr, n, g_parts + n, 0, -1, NULL);
   if (r_part != NULL)   *r_part = &(g_parts [n]);
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   /*---(run link)-----------------------*/
   rc = yview__find_link (n, &a, r_link);
   yview__parts_saving (x_abbr, n, g_parts + n, rc, a, g_parts + a);
   /*---(complete)-----------------------*/
   return rc;
}

char
yview_by_cursor         (char a_move, tPARTS **r_part, tPARTS **r_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =   -1;
   char        a           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_schar   (a_move);
   /*---(prepare)------------------------*/
   if (r_part != NULL)  *r_part = NULL;
   if (r_link != NULL)  *r_link = NULL;
   /*---(prepare)------------------------*/
   DEBUG_YVIEW   yLOG_sint    (myVIEW.npart);
   n = s_pindex;
   DEBUG_YVIEW   yLOG_sint    (n);
   /*---(update position)----------------*/
   --rce;  switch (a_move) {
   case YDLST_HEAD : n =  0;                break;
   case YDLST_PREV : --n;                   break;
   case YDLST_CURR :                        break;
   case YDLST_NEXT : ++n;                   break;
   case YDLST_TAIL : n = myVIEW.npart - 1;  break;
   default  :
                     DEBUG_YVIEW   yLOG_snote   ("illegal move");
                     DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
                     return rce;
   }
   DEBUG_YVIEW   yLOG_sint    (n);
   /*---(check for trouble)--------------*/
   --rce;  if (n >= myVIEW.npart)  {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (n <  0)        {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   yview__parts_saving (g_parts [n].abbr, n, g_parts + n, 0, -1, NULL);
   if (r_part != NULL)   *r_part = &(g_parts [n]);
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   /*---(run link)-----------------------*/
   rc = yview__find_link (n, &a, r_link);
   yview__parts_saving (g_parts [n].abbr, n, g_parts + n, rc, a, g_parts + a);
   /*---(complete)-----------------------*/
   return rc;
}

char*
yview_parts_name        (cchar n)
{
   if (n < 0 || n >= myVIEW.npart)  return  "n/a";
   return g_parts [n].name;
}



/*====================------------------------------------====================*/
/*===----                     resetting to defaults                    ----===*/
/*====================------------------------------------====================*/
static void  o___DEFAULT_________o () { return; }

char
yview__wipe             (char a_full, char a_part, char a_on, short a_nwide, short a_ntall, short a_owide, short a_otall, void *a_draw, char a_anchor, char a_color)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   /*---(prepare)------------------------*/
   rc = yview_by_abbr (a_part, &p, NULL);
   --rce;  if (rc < 0)  return rce;
   /*---(set defaults)-------------------*/
   if (a_full == 'y') {
      p->on         = a_on;
      if (myVIEW.env == YVIEW_CURSES) {
         p->def_wide   = a_nwide;
         p->def_tall   = a_ntall;
      } else if (myVIEW.env == YVIEW_OPENGL) {
         p->def_wide   = a_owide;
         p->def_tall   = a_otall;
      } else {
         p->def_wide   = 0;
         p->def_tall   = 0;
      }
      if (a_draw != NULL)  p->drawer = a_draw;
   }
   /*---(initialize)---------------------*/
   p->wide       = 0;
   p->left       = 0;
   p->tall       = 0;
   p->bott       = 0;
   /*---(detail)-------------------------*/
   if (a_full == 'y') {
      p->type       = YVIEW_FLAT;
      p->mgmt       = YVIEW_AUTO;
      p->anchor     = a_anchor;
      p->magn       = 1.0;
      p->color      = a_color;
   }
   /*---(pointers)-----------------------*/
   if (a_full == 'y') {
      p->source     = NULL;
      strlcpy (p->text, "", LEN_RECD);
      p->drawer     = NULL;
   }
   /*---(coordinates)--------------------*/
   p->xmin       = p->xlen       = 0;
   p->ymin       = p->ylen       = 0;
   p->zmin       = p->zlen       = 0;
   if (myVIEW.env == YVIEW_OPENGL && p->type == YVIEW_DEPTH) {
      p->zmin = -500;
      p->zlen = 1000;
   }
   /*---(output)-------------------------*/
   DEBUG_YVIEW   yLOG_complex ("part"      , "%-12.12s, on %c, wide %3d, tall %3d, draw %-10.10p", p->name, p->on, p->def_wide, p->def_tall, p->drawer);
   /*---(complete)-----------------------*/
   return 0;
}

char
yview__clear_all        (char a_full, char a_env)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_full"    , a_full);
   DEBUG_YVIEW   yLOG_char    ("a_env"     , a_env);
   /*---(global)-------------------------*/
   --rce;  if (a_env == 0 || strchr ("gc", a_env) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   myVIEW.env = a_env;
   /*---(default values)-----------------*/
   /*                                       -curses-- -opengl--                       */
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_TITLE   , 'y',   1,   0,  15,   0,  NULL, YVIEW_BOTRIG  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_VERSION , 'y',   1,   5,  15,  40,  NULL, YVIEW_BOTRIG  , YCOLOR_GRY     );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_BUFFER  , '-',   0,   1,   0,  15,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_FORMULA , '-',   0,   1,   0,  15,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_NAV     , '-',  20,   0, 150,   0,  NULL, YVIEW_TOPLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_LAYERS  , '-',  20,   0, 150,   0,  NULL, YVIEW_TOPLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_YAXIS   , '-',   5,   0,  40,   0,  NULL, YVIEW_TOPLEF  , YCOLOR_GRY     );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_XAXIS   , '-',   0,   1,   0,  15,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_ALT     , '-',   0,   0,   0,   0,  NULL, YVIEW_MIDCEN  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_PROGRESS, '-',   0,  10,   0, 100,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_DETAILS , '-',  20,   0, 250,   0,  NULL, YVIEW_TOPLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_RIBBON  , '-',   5,   0,  40,   0,  NULL, YVIEW_TOPLEF  , YCOLOR_GRY     );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_MODES   , 'y',   5,   1,  40,  15,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_STATUS  , 'y',   0,   1,   0,  15,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_COMMAND , 'y',   0,   1,   0,  15,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_KEYS    , 'y',   5,   1,  40,  15,  NULL, YVIEW_BOTLEF  , YCOLOR_GRY     );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_GRID    , '-',   0,   0,   0,   0,  NULL, 0             , YCOLOR_CLEAR   );
   yview__wipe (a_full, YVIEW_CURSOR  , '-',   0,   0,   0,   0,  NULL, 0             , YCOLOR_CLEAR   );
   yview__wipe (a_full, YVIEW_OVERLAY , '-',   0,   0,   0,   0,  NULL, 0             , YCOLOR_CLEAR   );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_FLOAT   , 'y',   0,   1,   0,  15,  NULL, YVIEW_TOPALL  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_HISTORY , 'y',   0,   0,   0,   0,  NULL, YVIEW_ALLFUL  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_MENUS   , 'y',  40,  14, 280, 200,  NULL, YVIEW_TOPCEN  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_NOTES   , 'y',   0,   0,   0,   0,  NULL, 0             , YCOLOR_CLEAR   );
   /*----------------- ---part--------- -on- wide tall wide tall ---drawer------------ */
   yview__wipe (a_full, YVIEW_MAIN    , 'y',   0,   0,   0,   0,  NULL, YVIEW_MIDCEN  , YCOLOR_GRY     );
   yview__wipe (a_full, YVIEW_MASK    , '-',   0,   0,   0,   0,  NULL, 0             , YCOLOR_CLEAR   );
   yview__wipe (a_full, YVIEW_WINDOW  , '-',   0,   0,   0,   0,  NULL, 0             , YCOLOR_CLEAR   );
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yview_factory      (char a_env) { return yview__clear_all ('y', a_env); }
char yview_clear        (void)       { return yview__clear_all ('-', myVIEW.env); }



/*====================------------------------------------====================*/
/*===----                         part anchors                         ----===*/
/*====================------------------------------------====================*/
static void  o___ANCHOR__________o () { return; }

/*> char                                                                                                     <* 
 *> yview__anchor_calc      (tPARTS *p)                                                                      <* 
 *> {                                                                                                        <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                              <* 
 *>    int         x_len       =    0;                                                                       <* 
 *>    int         y_len       =    0;                                                                       <* 
 *>    /+---(header)----------------------+/                                                                 <* 
 *>    DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);                                                             <* 
 *>    /+---(check for opengl)---------------+/                                                              <* 
 *>    DEBUG_YVIEW   yLOG_schar   (myVIEW.env);                                                               <* 
 *>    if (myVIEW.env != YVIEW_OPENGL) {                                                                     <* 
 *>       DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);                                                          <* 
 *>       return 0;                                                                                          <* 
 *>    }                                                                                                     <* 
 *>    /+---(handle auto first)--------------+/                                                              <* 
 *>    if (p->mgmt != YVIEW_AUTO) {                                                                          <* 
 *>       DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);                                                          <* 
 *>       return 0;                                                                                          <* 
 *>    }                                                                                                     <* 
 *>    /+---(easy first)---------------------+/                                                              <* 
 *>    x_len = p->xlen = p->wide;                                                                            <* 
 *>    y_len = p->ylen = p->tall;                                                                            <* 
 *>    /+---(horzontal)----------------------+/                                                              <* 
 *>    switch (p->anchor) {                                                                                  <* 
 *>    case YVIEW_TOPLEF : case YVIEW_MIDLEF : case YVIEW_BOTLEF :                                           <* 
 *>       p->xmin = 0;                                                                                       <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_UPSBEG : case YVIEW_MIDBEG : case YVIEW_LOWBEG :                                           <* 
 *>       p->xmin = 0 - (x_len * 0.75);                                                                      <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_TOPCEN : case YVIEW_UPSCEN : case YVIEW_MIDCEN : case YVIEW_LOWCEN : case YVIEW_BOTCEN :   <* 
 *>       p->xmin = 0 - (x_len * 0.50);                                                                      <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_UPSEND : case YVIEW_MIDEND : case YVIEW_LOWEND :                                           <* 
 *>       p->xmin = 0 - (x_len * 0.25);                                                                      <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_TOPRIG : case YVIEW_MIDRIG : case YVIEW_BOTRIG :                                           <* 
 *>       p->xmin = 0 - x_len;                                                                               <* 
 *>       break;                                                                                             <* 
 *>    }                                                                                                     <* 
 *>    /+---(vertical)-----------------------+/                                                              <* 
 *>    switch (p->anchor) {                                                                                  <* 
 *>    case YVIEW_TOPLEF : case YVIEW_TOPCEN : case YVIEW_TOPRIG :                                           <* 
 *>       p->ymin = 0 - y_len;                                                                               <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_UPSBEG : case YVIEW_UPSCEN : case YVIEW_UPSEND :                                           <* 
 *>       p->ymin = 0 - (y_len * 0.75);                                                                      <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_MIDLEF : case YVIEW_MIDBEG : case YVIEW_MIDCEN : case YVIEW_MIDEND : case YVIEW_MIDRIG :   <* 
 *>       p->ymin = 0 - (y_len * 0.50);                                                                      <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_LOWBEG : case YVIEW_LOWCEN : case YVIEW_LOWEND :                                           <* 
 *>       p->ymin = 0 - (y_len * 0.75);                                                                      <* 
 *>       break;                                                                                             <* 
 *>    case YVIEW_BOTLEF : case YVIEW_BOTCEN : case YVIEW_BOTRIG :                                           <* 
 *>       p->ymin = 0;                                                                                       <* 
 *>       break;                                                                                             <* 
 *>    }                                                                                                     <* 
 *>    /+---(default depths)-----------------+/                                                              <* 
 *>    p->zmin = -500;                                                                                       <* 
 *>    p->zlen = 1000;                                                                                       <* 
 *>    /+---(complete)-----------------------+/                                                              <* 
 *>    DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);                                                             <* 
 *>    return 0;                                                                                             <* 
 *> }                                                                                                        <*/

/*> char                                                                              <* 
 *> yview_anchor_calc       (char a_abbr)                                             <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    tPARTS     *p           = NULL;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);                                      <* 
 *>    yview_by_abbr (a_abbr, &p, NULL);                                              <* 
 *>    if (p == NULL) {                                                               <* 
 *>       DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, -10);                              <* 
 *>       return -10;                                                                 <* 
 *>    }                                                                              <* 
 *>    yview__anchor_calc (p);                                                        <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                      <* 
 *>    return 0;                                                                      <* 
 *> }                                                                                 <*/

/*> char                                                                                                                                                             <* 
 *> yview_anchor_calc_all   (void)                                                                                                                                   <* 
 *> {                                                                                                                                                                <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                                                                      <* 
 *>    tPARTS     *p           = NULL;                                                                                                                               <* 
 *>    /+---(header)-------------------------+/                                                                                                                      <* 
 *>    DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);                                                                                                                     <* 
 *>    /+---(find fixed heights)-------------+/                                                                                                                      <* 
 *>    yview_by_cursor (YDLST_HEAD, &p, NULL);                                                                                                                       <* 
 *>    while (p != NULL) {                                                                                                                                           <* 
 *>       yview__anchor_calc (p);                                                                                                                                    <* 
 *>       DEBUG_YVIEW   yLOG_complex (p->name, "bott %4d, left %4d, wide %4d, tall %4d, on %c", p->bott, p->left, p->wide, p->tall, p->on);                           <* 
 *>       DEBUG_YVIEW   yLOG_complex (p->name, "xmin %4d, xlen %4d, ymin %4d, ylen %4d, zmin %4d, zlen %4d", p->xmin, p->xlen, p->ymin, p->ylen, p->zmin, p->zlen);   <* 
 *>       yview_by_cursor (YDLST_NEXT, &p, NULL);                                                                                                                    <* 
 *>    }                                                                                                                                                             <* 
 *>    /+---(complete)-----------------------+/                                                                                                                      <* 
 *>    DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                                                                                                     <* 
 *>    return 0;                                                                                                                                                     <* 
 *> }                                                                                                                                                                <*/


char
yview_get_anchor        (char a_abbr)
{
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   rc = yview_by_abbr (a_abbr, &p, NULL);
   --rce;  if (rc < 0) {
      return rce;
   }
   return p->anchor;
}


