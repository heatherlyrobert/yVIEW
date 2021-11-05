/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"




static int    s_main_tall  = 0;
static int    s_full_tall  = 0;

static int    s_xaxis      =  0;
static int    s_prog       =  0;
static int    s_cum        =  0;



/*====================------------------------------------====================*/
/*===----                       detailed functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___DETAILS_________o () { return; }

char         /*-> resize heights based on layout -----[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_vert_fixed (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   int         x_max       =    0;          /* widest at level                */
   tPARTS     *p           = NULL;
   char        x_skip      =  '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_cum = 0;
   /*---(find fixed heights)-------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_GRAF   yLOG_value   ("LEVEL"     , x_lvl);
      x_max = 0;
      yview_by_cursor (YDLST_HEAD, &p, NULL);
      while (p != NULL) {
         DEBUG_GRAF   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, vert %d, %c %c %c", p, p->abbr, p->name, p->on, p->vert, p->y_tie, p->under, p->noy);
         if (p->vert == x_lvl  ) {
            x_skip = '-';
            /*---(set height)---------------*/
            if    (p->on  != 'y')   p->tall = 0;
            else                    p->tall = p->def_tall;
            /*---(find greatest)------------*/
            if (p->y_tie != '-')    x_skip = 'y';
            if (p->under != '-')    x_skip = 'y';
            if (p->noy   != '-')    x_skip = 'y';
            if (x_skip == '-' && p->tall > x_max)   x_max = p->tall;
            /*---(read-out)-----------------*/
            DEBUG_GRAF   yLOG_complex ("fixed"     , "%c %-12.12s tall %3d, bott %3d, max %3d, cum %3d, %c", p->abbr, p->name, p->tall, p->bott, x_max, s_cum, x_skip);
            /*---(special)------------------*/
            if (p->abbr == YVIEW_PROGRESS)  s_prog   = p->tall;
            if (p->abbr == YVIEW_XAXIS   )  s_xaxis  = p->tall;
            /*---(done)---------------------*/
         }
         yview_by_cursor (YDLST_NEXT, &p, NULL);
      }
      s_cum += x_max;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_vert_auto  (cint a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   int         x_other     =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(major sizes)--------------------*/
   if (myVIEW.env == YVIEW_OPENGL) {
      s_full_tall = s_cum + a_tall;
      s_main_tall = a_tall;
      x_other     = a_tall + s_prog + s_xaxis;
   } else {
      s_full_tall = a_tall;
      s_main_tall = a_tall - s_cum;
      x_other     = a_tall - s_cum + s_prog;
   }
   DEBUG_GRAF   yLOG_complex ("bigs"      , "full %3d, main %3d, other %3d, s_cum %3d", s_full_tall, s_main_tall, x_other, s_cum);
   /*---(walk auto parts)----------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      /*---(filter)-------------------*/
      if (p->abbr != YVIEW_WINDOW && (p->on != 'y' || p->mgmt != YVIEW_AUTO)) {
         yview_by_cursor (YDLST_NEXT, &p, NULL);
         continue;
      }
      /*---(set)----------------------*/
      switch (p->abbr) {
      case YVIEW_WINDOW   : p->tall = s_full_tall;               break;
      case YVIEW_MAIN     :
      case YVIEW_NOTES    :
      case YVIEW_ALT      :
      case YVIEW_YAXIS    : p->tall = s_main_tall;               break;
      case YVIEW_NAV      :
      case YVIEW_DETAILS  :
      case YVIEW_RIBBON   : p->tall = x_other;                   break;
      default               : yview_by_cursor (YDLST_NEXT, &p, NULL); continue;
      }
      /*---(display)------------------*/
      DEBUG_GRAF   yLOG_complex ("automatic" , "%c %-12.12s tall %3d, bott %3d", p->abbr, p->name, p->tall, p->bott);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_vert_var   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   int         x_max       =    0;          /* widest at level                */
   tPARTS     *p           = NULL;
   char        x_skip      =  '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(set lefts)----------------------*/
   s_cum = 0;
   /*---(find var widths)----------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_GRAF   yLOG_value   ("LEVEL"     , x_lvl);
      x_max = 0;
      yview_by_cursor (YDLST_HEAD, &p, NULL);
      while (p != NULL) {
         DEBUG_GRAF   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, vert %d, %c %c %c", p, p->abbr, p->name, p->on, p->vert, p->y_tie, p->under, p->noy);
         if (p->vert == x_lvl  ) {
            x_skip = '-';
            /*---(set bottom)---------------*/
            if (p->y_tie == '-')    p->bott = s_cum;
            /*---(find greatest)------------*/
            if (p->y_tie != '-')    x_skip = 'y';
            if (p->under != '-')    x_skip = 'y';
            if (p->noy   != '-')    x_skip = 'y';
            if (x_skip == '-' && p->tall > x_max)   x_max = p->tall;
            /*---(read-out)-----------------*/
            DEBUG_GRAF   yLOG_complex ("variable"  , "%c %-12.12s tall %3d, bott %3d, max %3d, cum %3d, %c", p->abbr, p->name, p->tall, p->bott, x_max, s_cum, x_skip);
            /*---(done)---------------------*/
         }
         yview_by_cursor (YDLST_NEXT, &p, NULL);
      }
      s_cum += x_max;
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_vert_link  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   tPARTS     *p           = NULL;
   tPARTS     *a           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(find var widths)----------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_GRAF   yLOG_value   ("LEVEL"     , x_lvl);
      yview_by_cursor (YDLST_HEAD, &p, &a);
      while (p != NULL) {
         DEBUG_GRAF   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, vert %d, %c %c %c", p, p->abbr, p->name, p->on, p->vert, p->y_tie, p->under, p->noy);
         if (p->vert == x_lvl && a != NULL) {
            /*---(set left)-----------------*/
            if (p->y_tie  != '-')  {
               a->tall  = s_full_tall - a->bott - p->tall;
               p->bott  = s_full_tall - p->tall;
               /*---(read-out)-----------------*/
               DEBUG_GRAF   yLOG_complex ("linked"    , "%c %-12.12s tall %3d, bott %3d AND %c %-12.12s tall %3d, bott %3d", p->abbr, p->name, p->tall, p->bott, a->abbr, a->name, a->tall, a->bott);
            }
         }
         yview_by_cursor (YDLST_NEXT, &p, &a);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_vert__float (tPARTS *p, int a_bott)
{
   p->tall = p->def_tall;
   switch (p->anchor) {
   case YVIEW_TOPALL : p->bott = a_bott + s_main_tall - (p->tall * 2.0); break;
   case YVIEW_UPSALL : p->bott = a_bott + s_main_tall * (0.75) - (p->tall * 0.5);  break;
   case YVIEW_MIDALL : p->bott = a_bott + s_main_tall * (0.50) - (p->tall * 0.5);  break;
   case YVIEW_LOWALL : p->bott = a_bott + s_main_tall * (0.25) - (p->tall * 0.5);  break;
   case YVIEW_BOTALL : p->bott = a_bott + p->tall;  break;
   default    :
                         DEBUG_GRAF   yLOG_note    ("no appropriate float location found");
                         break;
   }
   DEBUG_GRAF   yLOG_complex ("vert_float", "%c, %3da, %3ds, %3dt, %3db", myVIEW.loc_float, a_bott, s_main_tall, p->tall, p->bott);
   return 0;
}

char
yview_vert__menu  (tPARTS *p, int a_bott)
{
   p->tall = p->def_tall;
   switch (p->anchor) {
   case YVIEW_TOPLEF : case YVIEW_TOPCEN : case YVIEW_TOPRIG :
      p->bott = a_bott + s_main_tall - p->tall;
      break;
   case YVIEW_UPSBEG : case YVIEW_UPSCEN : case YVIEW_UPSEND :
      p->bott = a_bott + (s_main_tall * 0.90) - p->tall;
      break;
   case YVIEW_MIDLEF : case YVIEW_MIDCEN : case YVIEW_MIDRIG : case YVIEW_MIDBEG : case YVIEW_MIDEND :
      p->bott = a_bott + (s_main_tall * 0.50) - (p->tall * 0.50);
      break;
   case YVIEW_LOWBEG : case YVIEW_LOWCEN : case YVIEW_LOWEND :
      p->bott = a_bott + (s_main_tall * 0.10);
      break;
   case YVIEW_BOTLEF : case YVIEW_BOTCEN : case YVIEW_BOTRIG :
      p->bott = a_bott;
      break;
   default    :
      DEBUG_GRAF   yLOG_note    ("no appropriate menu location found");
      break;
   }
   DEBUG_GRAF   yLOG_complex ("vert_menu" , "%c, %3da, %3ds, %3dt, %3db", myVIEW.loc_menu, a_bott, s_main_tall, p->tall, p->bott);
   return 0;
}

char
yview_vert__hist  (tPARTS *p, int a_bott)
{
   p->tall = s_main_tall * 0.90;
   p->bott = a_bott + (s_main_tall * 0.05);
   DEBUG_GRAF   yLOG_complex ("vert_hist" , "%c, %3da, %3ds, %3dt, %3db", myVIEW.loc_hist, a_bott, s_main_tall, p->tall, p->bott);
   return 0;
}

char
yview_vert_float        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_bott      =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get main info)------------------*/
   if (myVIEW.env == YVIEW_OPENGL )  {
      /*> yVIKEYS_view_bounds (YVIEW_MAIN, NULL, NULL, NULL, &x_bott, NULL, NULL);    <*/
      yview_by_abbr (YVIEW_MAIN, &p, NULL);
      x_bott = p->bott;
   } else {
      /*> yVIKEYS_view_size   (YVIEW_MAIN, NULL, NULL, &x_bott, NULL, NULL);          <*/
      yview_by_abbr (YVIEW_MAIN, &p, NULL);
      x_bott = p->bott;
   }
   DEBUG_GRAF   yLOG_complex ("working"   , "bott %3d tall %3d", x_bott, s_main_tall);
   /*---(walk floats)--------------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      /*---(filter)-------------------*/
      if (p->mgmt != YVIEW_AUTO) {
         yview_by_cursor (YDLST_NEXT, &p, NULL);
         continue;
      }
      /*---(set)----------------------*/
      switch (p->abbr) {
      case YVIEW_FLOAT    :
         yview_vert__float (p, x_bott);
         break;
      case YVIEW_MENUS    :
         yview_vert__menu  (p, x_bott);
         break;
      case YVIEW_HISTORY  :
         yview_vert__hist  (p, x_bott);
         break;
      default               :
         yview_by_cursor (YDLST_NEXT, &p, NULL);
         continue;
      }
      /*---(display)------------------*/
      DEBUG_GRAF   yLOG_complex ("overlay"   , "%c %-12.12s tall %3d, bott %3d", p->abbr, p->name, p->tall, p->bott);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> flip bottoms for ncurses -----------[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_vert_final        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(fill in widths)-----------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      if (p->on   == 'y' && p->tall ==  0 ) {
         p->tall = s_full_tall - p->bott;
         DEBUG_GRAF   yLOG_complex ("fill"      , "%c %-12.12s tall %3d, bott %3d", p->abbr, p->name, p->tall, p->bott);
      }
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> flip bottoms for ncurses -----------[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_vert_flip         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   if (myVIEW.env == YVIEW_OPENGL) {
      DEBUG_GRAF   yLOG_note    ("not required for opengl");
      DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(display)------------------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      DEBUG_GRAF   yLOG_complex (p->name, "bott %4d, left %4d, wide %4d, tall %4d, on %c", p->bott, p->left, p->wide, p->tall, p->on);
      p->bott = s_full_tall - p->bott - 1;
      DEBUG_GRAF   yLOG_complex (p->name, "bott %4d, left %4d, wide %4d, tall %4d, on %c", p->bott, p->left, p->wide, p->tall, p->on);
      if (p->bott < 0)  p->bott = 0;
      DEBUG_GRAF   yLOG_complex (p->name, "bott %4d, left %4d, wide %4d, tall %4d, on %c", p->bott, p->left, p->wide, p->tall, p->on);
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          main driver                         ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVER__________o () { return; }

char         /*-> resize widths based on layout ------[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_vert              (cint a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   int         n           =    0;          /* current part                   */
   int         x_under     =    0;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_value   ("a_tall"    , a_tall);
   /*---(heights)------------------------*/
   yview_vert_fixed ();
   yview_vert_auto  (a_tall);
   yview_vert_var   ();
   yview_vert_link  ();
   /*> yvikeys_sizes_anchor     (YVIEW_MAIN);                                         <*/
   yview_vert_float ();
   yview_vert_final ();
   yview_vert_flip  ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}
