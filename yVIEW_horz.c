/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



static int    s_main_wide  = 0;
static int    s_alt_wide   = 0;
static int    s_full_wide  = 0;

static int    s_yaxis      =  0;
static int    s_cum        =  0;



/*====================------------------------------------====================*/
/*===----                       detailed functions                     ----===*/
/*====================------------------------------------====================*/
static void  o___DETAILS_________o () { return; }

char
yview_horz_fixed        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   int         x_max       =    0;          /* widest at level                */
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_cum = 0;
   /*---(find fixed widths)--------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_GRAF   yLOG_value   ("LEVEL"     , x_lvl);
      x_max = 0;
      yview_by_cursor (YDLST_HEAD, &p, NULL);
      while (p != NULL) {
         DEBUG_GRAF   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, horz %d, wide %3d", p, p->abbr, p->name, p->on, p->horz, p->wide);
         if (p->horz == x_lvl  ) {
            /*---(set width)----------------*/
            if    (p->on  != 'y')   p->wide = 0;
            else                    p->wide = p->def_wide;
            /*---(find greatest)------------*/
            if (p->nox == '-'  && p->wide > x_max)   x_max = p->wide;
            /*---(read-out)-----------------*/
            DEBUG_GRAF   yLOG_complex ("fixed"     , "%c %-12.12s wide %3d, max %3d, cum %3d", p->abbr, p->name, p->wide, x_max, s_cum);
            /*---(special)------------------*/
            if (p->abbr == YVIEW_YAXIS   )  s_yaxis = p->wide;
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
yview_horz_auto         (cint a_wide, cint a_alt)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   int         x_float     = 40;
   int         x_hist      = 60;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(major sizes)--------------------*/
   if (myVIEW.env == YVIEW_OPENGL) {
      s_full_wide = s_cum + a_wide + a_alt;
      s_main_wide = a_wide;
   } else {
      s_full_wide = a_wide;
      s_main_wide = a_wide - s_cum - a_alt;
      x_float /= 10;
      x_hist  /= 10;
   }
   s_alt_wide  = a_alt;
   DEBUG_GRAF   yLOG_complex ("bigs"      , "full %3d, main %3d, alt %3d, s_cum %3d", s_full_wide, s_main_wide, s_alt_wide, s_cum);
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
      case YVIEW_WINDOW   : p->wide = s_full_wide;                    break;
      case YVIEW_MAIN     :
      case YVIEW_NOTES    : p->wide = s_main_wide;                    break;
      case YVIEW_ALT      : p->wide = s_alt_wide;                     break;
      case YVIEW_PROGRESS : p->wide = s_main_wide + a_alt;            break;
      case YVIEW_XAXIS    : p->wide = s_main_wide + a_alt + s_yaxis;  break;
      default            : yview_by_cursor (YDLST_NEXT, &p, NULL);   continue;
      }
      /*---(display)------------------*/
      DEBUG_GRAF   yLOG_complex ("automatic" , "%c %-12.12s %3d wide", p->abbr, p->name, p->wide);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_var          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   int         x_max       =    0;          /* widest at level                */
   tPARTS     *p           = NULL;
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
         if (p->horz == x_lvl  ) {
            /*---(set left)-----------------*/
            if (p->x_tie  == '-')   p->left = s_cum;
            /*---(find greatest)------------*/
            if (p->nox == '-'  && p->wide > x_max)   x_max = p->wide;
            /*---(read-out)-----------------*/
            DEBUG_GRAF   yLOG_complex ("variable"  , "%c %-12.12s wide %3d, max %3d, cum %3d", p->abbr, p->name, p->wide, x_max, s_cum);
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
yview_horz_link         (void)
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
         if (p->horz == x_lvl && a != NULL) {
            /*---(set left)-----------------*/
            if (p->x_tie  != '-')  {
               /*---(rightside is variable)----------*/
               /*   [--------------full]----------------]               */
               /*   xxxx[--a--][-----------p----------->?               */
               if (a->on != 'y' || a->wide > 0) {
                  DEBUG_GRAF   yLOG_note    ("leftmost is fixed length or off");
                  p->left = a->left + a->wide;
                  if (p->on == 'y')  p->wide  = s_full_wide - p->left;
                  else               p->wide  = 0;
               }
               /*---(leftside is variable)-----------*/
               /*   [--------------full]----------------]               */
               /*   xxxx[-----------a----------->?[--p--]               */
               else {
                  DEBUG_GRAF   yLOG_note    ("leftmost is variable length");
                  p->left  = s_full_wide - p->wide;
                  if (a->on == 'y')  a->wide  = p->left - a->left;
                  else               a->wide  = 0;
               }
               /*---(read-out)-----------------*/
               DEBUG_GRAF   yLOG_complex ("linked"    , "%c %-12.12s wide %3d AND %c %-12.12s wide %3d", p->abbr, p->name, p->wide, a->abbr, a->name, a->wide);
            }
            /*---(done)---------------------*/
         }
         yview_by_cursor (YDLST_NEXT, &p, &a);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz__float       (tPARTS *p, int a_left)
{
   p->wide = s_main_wide * 0.90;
   p->left = a_left + (s_main_wide * 0.05);
   DEBUG_GRAF   yLOG_complex ("horz_float", "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_float, a_left, s_main_wide, p->wide, p->left);
   return 0;
}

char
yview_horz__menus       (tPARTS *p, int a_left)
{
   DEBUG_GRAF   yLOG_value   ("a_left"    , a_left);
   DEBUG_GRAF   yLOG_value   ("wide"      , p->wide);
   p->wide = p->def_wide;
   switch (p->anchor) {
   case YVIEW_TOPLEF : case YVIEW_MIDLEF : case YVIEW_BOTLEF :
      p->left = a_left;
      break;
   case YVIEW_UPSBEG : case YVIEW_MIDBEG : case YVIEW_LOWBEG :
      p->left = a_left + (s_main_wide * 0.10);
      break;
   case YVIEW_TOPCEN : case YVIEW_MIDCEN : case YVIEW_BOTCEN : case YVIEW_UPSCEN : case YVIEW_LOWCEN :
      p->left = a_left + (s_main_wide * 0.50) - (p->wide * 0.50);
      break;
   case YVIEW_UPSEND : case YVIEW_MIDEND : case YVIEW_LOWEND :
      p->left = a_left + (s_main_wide * 0.90) - p->wide;
      break;
   case YVIEW_TOPRIG : case YVIEW_MIDRIG : case YVIEW_BOTRIG :
      p->left = a_left + s_main_wide - p->wide;
      break;
   }
   DEBUG_GRAF   yLOG_complex ("horz_menu" , "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_menu, a_left, s_main_wide, p->wide, p->left);
   return 0;
}

char
yview_horz__hist        (tPARTS *p, int a_left)
{
   switch (p->anchor) {
   case YVIEW_ALLLEF :
      p->wide = s_main_wide * 0.45;
      p->left = a_left + (s_main_wide * 0.05);
      break;
   case YVIEW_ALLCEN :
      p->wide = s_main_wide * 0.50;
      p->left = a_left + (s_main_wide * 0.25);
      break;
   case YVIEW_ALLRIG :
      p->wide = s_main_wide * 0.45;
      p->left = a_left + (s_main_wide * 0.50);
      break;
   case YVIEW_ALLFUL :
      p->wide = s_main_wide * 0.80;
      p->left = a_left + (s_main_wide * 0.10);
      break;
   }
   DEBUG_GRAF   yLOG_complex ("horz_hist" , "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_hist, a_left, s_main_wide, p->wide, p->left);
   return 0;
}

char
yview_horz_float        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_left      =    0;
   int         x_curses    =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get main info)------------------*/
   if (myVIEW.env == YVIEW_OPENGL )  {
      /*> yVIKEYS_view_bounds (YVIEW_MAIN, &x_left, NULL, NULL, NULL, NULL, NULL);    <*/
      yview_by_abbr (YVIEW_MAIN, &p, NULL);
      x_left = p->left;
   } else {
      /*> yVIKEYS_view_size   (YVIEW_MAIN, &x_left, NULL, NULL, NULL, NULL);          <*/
      yview_by_abbr (YVIEW_MAIN, &p, NULL);
      x_left = p->left;
   }
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
         yview_horz__float  (p, x_left);
         break;
      case YVIEW_MENUS    :
         yview_horz__menus  (p, x_left);
         break;
      case YVIEW_HISTORY  :
         yview_horz__hist   (p, x_left);
         break;
      default               :
         yview_by_cursor (YDLST_NEXT, &p, NULL);
         continue;
      }
      /*---(display)------------------*/
      DEBUG_GRAF   yLOG_complex ("overlay"   , "%c %-12.12s %3d wide", p->abbr, p->name, p->wide);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_final         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(walk floats)--------------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      /*---(filter)-------------------*/
      if (p->on != 'y' || p->wide != 0) {
         yview_by_cursor (YDLST_NEXT, &p, NULL);
         continue;
      }
      /*---(set)----------------------*/
      p->wide = s_full_wide - p->left;
      /*---(display)------------------*/
      DEBUG_GRAF   yLOG_complex ("other"     , "%c %-12.12s %3d wide", p->abbr, p->name, p->wide);
      /*---(done)---------------------*/
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
yview_horz               (cint a_wide, cint a_alt)
{
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_complex ("args"      , "wide %3d, alt %3d", a_wide, a_alt);
   /*---(widths)-------------------------*/
   yview_horz_fixed        ();
   yview_horz_auto         (a_wide, a_alt);
   yview_horz_var          ();
   yview_horz_link         ();
   yview_horz_float        ();
   yview_horz_final        ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}