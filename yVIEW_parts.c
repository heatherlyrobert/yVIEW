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


#define      OWN_FULLY        'y'   /* only change color, text, and hiding    */
#define      OWN_PARTLY       'p'   /* change hiding, color, and drawing      */
#define      OWN_LITTLE       's'   /* change anything and everything         */
#define      OWN_MAIN         'm'   /* change anything and everything         */
#define      OWN_UNDERLAY     'u'   /* drawn before main                      */
#define      OWN_OVERLAY      'o'   /* drawn after everything else            */
#define      OWN_DATA         '-'   /* just a data holder                     */

#define      OWN_SETUP        "ypsm"
#define      OWN_HIDE         "ypso"
#define      OWN_REANCHOR     "yp"

#define      OWN_COMPLEX      "mso"
#define      OWN_MODERATE     "msp"
#define      OWN_SIMPLE       "po"

tPARTS  g_parts [MAX_PARTS] = {
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_TITLE     , "title"       , OWN_FULLY  , 'y',    1, '-', '-', 0, 0, 0,    1, '-', '-', '-', 0, 0, 0,  'r', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTRIG  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "left hand title bar"                                },
   { YVIEW_VERSION   , "version"     , OWN_FULLY  , 'y',    1, '/', '-', 0, 0, 0,    9, '-', 't', '-', 0, 0, 0,  'r', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTRIG  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "version display with debugging notice"              },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_BUFFER    , "buffer"      , OWN_FULLY  , '-',    2, '-', '-', 0, 0, 0,    7, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "buffer inventory at top"                            },
   { YVIEW_FORMULA   , "formula"     , OWN_FULLY  , '-',    2, '-', '-', 0, 0, 0,    6, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "formula and source editing line at top"             },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_NAV       , "nav"         , OWN_PARTLY , '-',    2, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "navigation panel to display tags and other links"   },
   { YVIEW_LAYERS    , "layers"      , OWN_PARTLY , '-',    2, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "displays all selected laysers over working"         },
   { YVIEW_YAXIS     , "yaxis"       , OWN_PARTLY , '-',    3, '-', '-', 0, 0, 0,    4, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , 0              , 0, 0, 0, 0, 0, 0,  "show the y-axis labels left of the main screen"     },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_XAXIS     , "xaxis"       , OWN_PARTLY , '-',    3, '/', '-', 0, 0, 0,    5, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , 0              , 0, 0, 0, 0, 0, 0,  "show the x-axis labels above the main screen"       },
   { YVIEW_ALT       , "alt"         , OWN_LITTLE , '-',    5, '-', '-', 0, 0, 0,    4, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "alternate working area or view"                     },
   { YVIEW_PROGRESS  , "progress"    , OWN_PARTLY , '-',    3, '/', '-', 0, 0, 0,    3, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "time and sequencing controls about status line"     },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_DETAILS   , "details"     , OWN_PARTLY , '-',    6, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "display area for critical details to right"         },
   { YVIEW_RIBBON    , "ribbon"      , OWN_FULLY  , '-',    7, '-', '-', 0, 0, 0,    3, '-', '-', 'y', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "menu and icon display for navigation of commands"   },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_MODES     , "modes"       , OWN_FULLY  , 'y',    2, '/', '-', 0, 0, 0,    2, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "informational to display current mode/submode"      },
   { YVIEW_STATUS    , "status"      , OWN_FULLY  , 'y',    9, '-', 'x', 0, 0, 0,    2, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "informational status bar above command line"        },
   { YVIEW_COMMAND   , "command"     , OWN_FULLY  , 'y',    2, '-', '-', 0, 0, 0,    1, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "command, search, and help message line at bottom"   },
   { YVIEW_KEYS      , "keys"        , OWN_FULLY  , 'y',    9, '/', 'c', 0, 0, 0,    1, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "latest keyboard characters typed"                   },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_GRID      , "grid"        , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , 0             , 0              , 0, 0, 0, 0, 0, 0,  "overlay main drawing with a grid"                   },
   { YVIEW_CURSOR    , "cursor"      , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , 0             , 0              , 0, 0, 0, 0, 0, 0,  "cursor display on screen"                           },
   { YVIEW_OVERLAY   , "overlay"     , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "shown over the working screen"                      },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_NOTES     , "notes"       , OWN_OVERLAY, 'y',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "overlay for interactive notation"                   },
   { YVIEW_FLOAT     , "float"       , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_BOTLEF  , YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "shown over the working screen"                      },
   { YVIEW_HISTORY   , "history"     , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "list of command/search history"                     },
   { YVIEW_MENUS     , "menus"       , OWN_OVERLAY, 'y',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_TOPLEF  , YCOLOR_CLEAR   , 0, 0, 0, 0, 0, 0,  "interactive menu overlay"                           },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { YVIEW_MAIN      , "main"        , OWN_MAIN   , 'y',    4, '-', '-', 0, 0, 0,    4, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , YVIEW_MIDCEN  , YCOLOR_GRY     , 0, 0, 0, 0, 0, 0,  "main working area in the middle"                    },
   { YVIEW_MASK      , "mask"        , OWN_OVERLAY, '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , 0             , 0              , 0, 0, 0, 0, 0, 0,  "desktop presentation mask for display"              },
   { YVIEW_WINDOW    , "window"      , OWN_DATA   , '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , 0             , 0              , 0, 0, 0, 0, 0, 0,  "full screen width and height"                       },
   /*---abbr---------   ---name-----   ---own-----  on   horz--nox--tie-dw-wi-le  vert--noy--tie--und-dt-ta-bo   ori  source, txt  drawer  type---------  ---mgmt-------  ---anchor-----  ---color------- xm xl ym yl zm zl    12345678901234567890123456789012345678901234567890  */
   { 0               , ""            , 0          , '-',    0, '-', '-', 0, 0, 0,    0, '-', '-', '-', 0, 0, 0,  '-', NULL  , "",  NULL  , YVIEW_FLAT   , YVIEW_AUTO    , 0             , 0              , 0, 0, 0, 0, 0, 0,  ""                                                   },
};

/*  lef/rig1----- 2----- 3----- 4----- 5----- 6----- 7-----
 * top/bot
 *     7   vers-- buffer---------------------------------->
 *     6   ´----´ formula--------------------------------->
 *     5   ¨    ¨ ´----´ xaxis--------------> ´----´ ´----´
 *     4   ¨    ¨ ¨    ¨ yaxis´ MAIN-- alt--- ¨    ¨ ¨    ¨
 *     3   ¨    ¨ nav--´ progress------------ detail ribbon
 *     2   ¨    ¨ modes- status--------------------------->
 *     1   title´ command--------------------------> keys->
 *
 *     0 in either means do not consider/show
 *     9 means tied to another element, handle width/height special
 *
 */

char
yview_parts_init        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(screen parts)-------------------*/
   myVIEW.npart = 0;
   for (i = 0; i < MAX_PARTS; ++i) {
      if (g_parts [i].abbr == 0)  break;
      DEBUG_PROG   yLOG_info    ("name"      , g_parts [i].name);
      ++(myVIEW.npart);
   }
   DEBUG_PROG   yLOG_value   ("npart"     , myVIEW.npart);
   /*---(ribbon)-------------------------*/
   /*> for (i = 0; i < LEN_LABEL; ++i)  s_win.r_icons [i] = -1;                       <* 
    *> s_win.r_nicon = 0;                                                             <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

static  char        s_abbr   =  '-';
static  char        s_pindex =  -10;
static  tPARTS     *s_part   = NULL;
static  char        s_aindex =  -10;
static  tPARTS     *s_link   = NULL;

char
yview__find_link        (char n, tPARTS **a_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   char        a           =   -1;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF   yLOG_sint    (n);
   DEBUG_GRAF   yLOG_spoint  (a_link);
   /*---(check for link)-----------------*/
   if (a_link == NULL) {
      DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   *a_link = NULL;
   DEBUG_GRAF   yLOG_schar   (g_parts [n].x_tie);
   DEBUG_GRAF   yLOG_schar   (g_parts [n].y_tie);
   if (g_parts [n].x_tie == '-' && g_parts [n].y_tie == '-') {
      DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(find link)----------------------*/
   for (i = 0; i < myVIEW.npart; ++i) {
      if (g_parts [i].abbr == g_parts [n].x_tie)  {
         a = i;
         *a_link = &(g_parts [i]);
         break;
      }
      if (g_parts [i].abbr == g_parts [n].y_tie)  {
         a = i;
         *a_link = &(g_parts [i]);
         break;
      }
   }
   DEBUG_GRAF   yLOG_spoint  (*a_link);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return a;
}

char
yview__parts_saved      (tPARTS **a_part, tPARTS **a_link)
{
   if (a_part != NULL)  *a_part = s_part;
   if (a_link != NULL)  *a_link = s_link;
   return s_pindex;
}

char
yview__parts_saving     (cchar a_abbr, cchar n, tPARTS *a_part, cchar a, tPARTS *a_link)
{
   s_abbr     = a_abbr;
   s_pindex   = n;
   s_part     = a_part;
   s_aindex   = a;
   s_link     = a_link;
   return 0;
}

char         /*-> locate screen parts by abbrev ------[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_by_abbr           (cchar  a_abbr, tPARTS **a_part, tPARTS **a_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   char        a           =   -1;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF   yLOG_sint    (a_abbr);
   /*---(defaults)-----------------------*/
   if (a_part != NULL)  *a_part = NULL;
   if (a_link != NULL)  *a_link = NULL;
   /*---(short-cut)----------------------*/
   if (a_abbr == s_abbr) {
      DEBUG_GRAF   yLOG_snote   ("short-cut using saved");
      DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
      return yview__parts_saved (a_part, a_link);
   }
   /*---(defense)------------------------*/
   --rce;  if (a_abbr <= G_KEY_SPACE || a_abbr >= G_KEY_TILDA) {
      DEBUG_GRAF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_schar   (a_abbr);
   DEBUG_GRAF   yLOG_sint    (myVIEW.npart);
   /*---(find the screen part)-----------*/
   for (i = 0; i < myVIEW.npart; ++i) {
      DEBUG_GRAF   yLOG_sint    (i);
      if (g_parts [i].abbr != a_abbr)         continue;
      n = i;
      break;
   }
   DEBUG_GRAF   yLOG_sint    (n);
   --rce;  if (n < 0) {
      DEBUG_GRAF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_snote   (g_parts [n].name);
   /*---(save back)----------------------*/
   yview__parts_saving (a_abbr, n, g_parts + n, -1, NULL);
   if (a_part != NULL)   *a_part = &(g_parts [n]);
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   /*---(run link)-----------------------*/
   a = yview__find_link (n, a_link);
   yview__parts_saving (a_abbr, n, g_parts + n, a, *a_link);
   /*---(complete)-----------------------*/
   return n;
}

char
yview_by_cursor         (char a_move, tPARTS **a_part, tPARTS **a_link)
{
   /*---(locals)-----------+-----+-----+-*/
   char         rce        =  -10;
   char         n          =   -1;
   char         a          =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   DEBUG_GRAF   yLOG_schar   (a_move);
   /*---(prepare)------------------------*/
   if (a_part != NULL)  *a_part = NULL;
   if (a_link != NULL)  *a_link = NULL;
   /*---(prepare)------------------------*/
   DEBUG_GRAF   yLOG_sint    (myVIEW.npart);
   n = s_pindex;
   DEBUG_GRAF   yLOG_sint    (n);
   /*---(update position)----------------*/
   --rce;  switch (a_move) {
   case YDLST_HEAD : n =  0;                break;
   case YDLST_PREV : --n;                   break;
   case YDLST_CURR :                        break;
   case YDLST_NEXT : ++n;                   break;
   case YDLST_TAIL : n = myVIEW.npart - 1;  break;
   default  :
              DEBUG_GRAF   yLOG_snote   ("illegal move");
              DEBUG_GRAF   yLOG_sexitr  (__FUNCTION__, rce);
              return rce;
   }
   DEBUG_GRAF   yLOG_sint    (n);
   /*---(check for trouble)--------------*/
   --rce;  if (n >= myVIEW.npart)  {
      DEBUG_GRAF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (n <  0)        {
      DEBUG_GRAF   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save back)----------------------*/
   yview__parts_saving (g_parts [n].abbr, n, g_parts + n, -1, NULL);
   if (a_part != NULL)   *a_part = &(g_parts [n]);
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   /*---(run link)-----------------------*/
   a = yview__find_link (n, a_link);
   yview__parts_saving (g_parts [n].abbr, n, g_parts + n, a, *a_link);
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return n;
}

char*
yview_parts_name        (cchar n)
{
   if (n < 0 || n >= myVIEW.npart)  return  "n/a";
   return g_parts [n].name;
}


