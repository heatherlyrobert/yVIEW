/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



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
      myVIEW.full_wide = s_cum + a_wide + a_alt;
      myVIEW.main_wide = a_wide;
   } else {
      myVIEW.full_wide = a_wide;
      myVIEW.main_wide = a_wide - s_cum - a_alt;
      x_float /= 10;
      x_hist  /= 10;
   }
   myVIEW.alt_wide  = a_alt;
   DEBUG_GRAF   yLOG_complex ("bigs"      , "full %3d, main %3d, alt %3d, s_cum %3d", myVIEW.full_wide, myVIEW.main_wide, myVIEW.alt_wide, s_cum);
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
      case YVIEW_WINDOW   : p->wide = myVIEW.full_wide;                    break;
      case YVIEW_MAIN     :
      case YVIEW_NOTES    : p->wide = myVIEW.main_wide;                    break;
      case YVIEW_ALT      : p->wide = myVIEW.alt_wide;                     break;
      case YVIEW_PROGRESS : p->wide = myVIEW.main_wide + a_alt;            break;
      case YVIEW_XAXIS    : p->wide = myVIEW.main_wide + a_alt + s_yaxis;  break;
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
                  if (p->on == 'y')  p->wide  = myVIEW.full_wide - p->left;
                  else               p->wide  = 0;
               }
               /*---(leftside is variable)-----------*/
               /*   [--------------full]----------------]               */
               /*   xxxx[-----------a----------->?[--p--]               */
               else {
                  DEBUG_GRAF   yLOG_note    ("leftmost is variable length");
                  p->left  = myVIEW.full_wide - p->wide;
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
yview_horz__float       (tPARTS *m, tPARTS *p)
{
   p->type = m->type;
   p->magn = m->magn;
   p->wide = m->wide * 0.90;
   p->left = m->left + (m->wide * 0.05);
   DEBUG_GRAF   yLOG_complex ("horz_float", "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_float, m->left, m->wide, p->wide, p->left);
   return 0;
}

char
yview_horz__menus       (tPARTS *m, tPARTS *p)
{
   p->type = m->type;
   p->magn = m->magn;
   DEBUG_GRAF   yLOG_value   ("a_left"    , m->left);
   DEBUG_GRAF   yLOG_value   ("wide"      , p->wide);
   p->wide = p->def_wide;
   switch (p->anchor) {
   case YVIEW_TOPLEF : case YVIEW_MIDLEF : case YVIEW_BOTLEF :
      p->left = m->left;
      break;
   case YVIEW_UPSBEG : case YVIEW_MIDBEG : case YVIEW_LOWBEG :
      p->left = m->left + (m->wide * 0.10);
      break;
   case YVIEW_TOPCEN : case YVIEW_MIDCEN : case YVIEW_BOTCEN : case YVIEW_UPSCEN : case YVIEW_LOWCEN :
      p->left = m->left + (m->wide * 0.50) - (p->wide * 0.50);
      break;
   case YVIEW_UPSEND : case YVIEW_MIDEND : case YVIEW_LOWEND :
      p->left = m->left + (m->wide * 0.90) - p->wide;
      break;
   case YVIEW_TOPRIG : case YVIEW_MIDRIG : case YVIEW_BOTRIG :
      p->left = m->left + m->wide - p->wide;
      break;
   }
   DEBUG_GRAF   yLOG_complex ("horz_menu" , "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_menu, m->left, m->wide, p->wide, p->left);
   return 0;
}

char
yview_horz__hist        (tPARTS *m, tPARTS *p)
{
   p->type = m->type;
   p->magn = m->magn;
   switch (p->anchor) {
   case YVIEW_ALLLEF :
      p->wide = m->wide * 0.45;
      p->left = m->left + (m->wide * 0.05);
      break;
   case YVIEW_ALLCEN :
      p->wide = m->wide * 0.50;
      p->left = m->left + (m->wide * 0.25);
      break;
   case YVIEW_ALLRIG :
      p->wide = m->wide * 0.45;
      p->left = m->left + (m->wide * 0.50);
      break;
   case YVIEW_ALLFUL :
      p->wide = m->wide * 0.80;
      p->left = m->left + (m->wide * 0.10);
      break;
   }
   DEBUG_GRAF   yLOG_complex ("horz_hist" , "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_hist, m->left, m->wide, p->wide, p->left);
   return 0;
}

char
yview_horz_float        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *m           = NULL;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(get main info)------------------*/
   yview_by_abbr   (YVIEW_MAIN, &m, NULL);
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
         yview_horz__float  (m, p);
         break;
      case YVIEW_MENUS    :
         yview_horz__menus  (m, p);
         break;
      case YVIEW_HISTORY  :
         yview_horz__hist   (m, p);
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
      p->wide = myVIEW.full_wide - p->left;
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
/*===----                       coordinate calcs                       ----===*/
/*====================------------------------------------====================*/
static void  o___COORDS__________o () { return; }

char
yview_horz_coords       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   short       x_len       =    0;
   short       x_max       =    0;
   tPARTS     *p           = NULL;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(check for opengl)---------------*/
   DEBUG_GRAF   yLOG_schar   (myVIEW.env);
   if (myVIEW.env != YVIEW_OPENGL) {
      DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(walk all)-----------------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      /*---(skip non-auto)---------------*/
      if (p->mgmt != YVIEW_AUTO)  continue;
      if (p->own  != OWN_OVERLAY) {
         /*---(easy first)---------------*/
         x_len = p->xlen = p->wide * p->magn;
         DEBUG_GRAF   yLOG_sint    (x_len);
         /*---(horzontal)----------------*/
         switch (p->anchor) {
         case YVIEW_TOPLEF : case YVIEW_MIDLEF : case YVIEW_BOTLEF :
            p->xmin = 0;
            break;
         case YVIEW_UPSBEG : case YVIEW_MIDBEG : case YVIEW_LOWBEG :
            p->xmin = 0 - (x_len * 0.75);
            break;
         case YVIEW_TOPCEN : case YVIEW_UPSCEN : case YVIEW_MIDCEN : case YVIEW_LOWCEN : case YVIEW_BOTCEN :
            p->xmin = 0 - (x_len * 0.50);
            break;
         case YVIEW_UPSEND : case YVIEW_MIDEND : case YVIEW_LOWEND :
            p->xmin = 0 - (x_len * 0.25);
            break;
         case YVIEW_TOPRIG : case YVIEW_MIDRIG : case YVIEW_BOTRIG :
            p->xmin = 0 - x_len;
            break;
         }
         DEBUG_GRAF   yLOG_sint    (p->xmin);
         /*---(and last)-----------------*/
         x_max = p->xmin + x_len;
         DEBUG_GRAF   yLOG_sint    (x_max);
      }
      /*---(done)------------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_horz_overlay      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *w           = NULL;
   tPARTS     *m           = NULL;
   tPARTS     *p           = NULL;
   /*---(header)----------------------*/
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(check for opengl)---------------*/
   DEBUG_GRAF   yLOG_schar   (myVIEW.env);
   /*> if (myVIEW.env != YVIEW_OPENGL) {                                              <* 
    *>    DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);                                   <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(get window info)----------------*/
   yview_by_abbr   (YVIEW_WINDOW, &w, NULL);
   /*---(get main info)------------------*/
   yview_by_abbr   (YVIEW_MAIN  , &m, NULL);
   /*---(walk all)-----------------------*/
   yview_by_cursor (YDLST_HEAD  , &p, NULL);
   while (p != NULL) {
      /*---(skip non-auto)---------------*/
      if (p->mgmt != YVIEW_AUTO)  continue;
      if (p->own  == OWN_OVERLAY) {
         /*---(full main space)----------*/
         if (strchr (OVER_FULL, p->abbr) != NULL) {
            p->left = m->left;
            p->wide = m->wide;
            if (myVIEW.env == YVIEW_OPENGL) {
               p->xmin = m->xmin;
               p->xlen = m->xlen;
            }
         }
         /*---(full window space)--------*/
         else if (strchr (OVER_WIND, p->abbr) != NULL) {
            p->left = w->left;
            p->wide = w->wide;
            if (myVIEW.env == YVIEW_OPENGL) {
               p->xmin = w->xmin;
               p->xlen = w->xlen;
            }
         } 
         /*---(sub-main space)-----------*/
         else {
            if (myVIEW.env == YVIEW_OPENGL) {
               p->xlen = p->wide * p->magn;
               p->xmin = m->xmin + ((p->left - m->left) * m->magn);
            }
         }
         DEBUG_GRAF   yLOG_sint    (p->xmin);
         DEBUG_GRAF   yLOG_sint    (p->xlen);
         DEBUG_GRAF   yLOG_sint    (p->xmin + p->xlen);

      }
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
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
   yview_horz_fixed   ();
   yview_horz_auto    (a_wide, a_alt);
   yview_horz_var     ();
   yview_horz_link    ();
   yview_horz_float   ();
   yview_horz_final   ();
   yview_horz_coords  ();
   yview_horz_overlay ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}


