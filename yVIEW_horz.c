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
   tYVIEW_PARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_cum = 0;
   /*---(find fixed widths)--------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_YVIEW   yLOG_value   ("LEVEL"     , x_lvl);
      x_max = 0;
      yview_by_cursor (YDLST_HEAD, &p, NULL);
      while (p != NULL) {
         DEBUG_YVIEW   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, horz %d, wide %3d", p, p->abbr, p->name, p->on, p->horz, p->wide);
         if (p->horz == x_lvl  ) {
            /*---(set width)----------------*/
            if      (p->on  != 'y'       )   p->wide = 0;
            else if (p->abbr != YVIEW_ALT)   p->wide = p->def_wide;
            /*---(find greatest)------------*/
            if (p->nox == '-'  && p->wide > x_max)   x_max = p->wide;
            /*---(read-out)-----------------*/
            DEBUG_YVIEW   yLOG_complex ("fixed"     , "%c %-12.12s wide %3d, max %3d, cum %3d", p->abbr, p->name, p->wide, x_max, s_cum);
            /*---(special)------------------*/
            if (p->abbr == YVIEW_YAXIS   )  s_yaxis = p->wide;
            /*---(done)---------------------*/
         }
         yview_by_cursor (YDLST_NEXT, &p, NULL);
      }
      s_cum += x_max;
      DEBUG_YVIEW   yLOG_complex ("s_cum"     , "%4d, %4d", x_max, s_cum);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_auto         (cint a_wide, cint a_alt)
{
   /*---(locals)-----------+-----+-----+-*/
   tYVIEW_PARTS     *p           = NULL;
   int         x_float     = 40;
   int         x_hist      = 60;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
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
   DEBUG_YVIEW   yLOG_complex ("bigs"      , "full %3d, main %3d, alt %3d, s_cum %3d", myVIEW.full_wide, myVIEW.main_wide, myVIEW.alt_wide, s_cum);
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
      case YVIEW_WINDOW   :
         p->wide = myVIEW.full_wide;
         break;
      case YVIEW_MAIN     :
      case YVIEW_NOTES    :
         p->wide = myVIEW.main_wide;
         break;
      case YVIEW_ALT      :
         p->wide = myVIEW.alt_wide;
         break;
      case YVIEW_PROGRESS :
         p->wide = myVIEW.main_wide + a_alt;
         break;
      case YVIEW_XAXIS    :
         p->wide = myVIEW.main_wide + a_alt + s_yaxis;
         break;
      default            : yview_by_cursor (YDLST_NEXT, &p, NULL);   continue;
      }
      /*---(display)------------------*/
      DEBUG_YVIEW   yLOG_complex ("automatic" , "%c %-12.12s %3d wide", p->abbr, p->name, p->wide);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_var          (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   int         x_max       =    0;          /* widest at level                */
   tYVIEW_PARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(set lefts)----------------------*/
   s_cum = 0;
   /*---(find var widths)----------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_YVIEW   yLOG_value   ("LEVEL"     , x_lvl);
      x_max = 0;
      yview_by_cursor (YDLST_HEAD, &p, NULL);
      while (p != NULL) {
         if (p->horz == x_lvl  ) {
            /*---(set left)-----------------*/
            if (p->x_tie  == '-')   p->left = s_cum;
            /*---(find greatest)------------*/
            if (p->nox == '-'  && p->wide > x_max)   x_max = p->wide;
            /*---(read-out)-----------------*/
            DEBUG_YVIEW   yLOG_complex ("variable"  , "%c %-12.12s wide %3d, max %3d, cum %3d", p->abbr, p->name, p->wide, x_max, s_cum);
            /*---(done)---------------------*/
         }
         yview_by_cursor (YDLST_NEXT, &p, NULL);
      }
      s_cum += x_max;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_link         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   tYVIEW_PARTS     *p           = NULL;
   tYVIEW_PARTS     *a           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(find var widths)----------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_YVIEW   yLOG_value   ("LEVEL"     , x_lvl);
      yview_by_cursor (YDLST_HEAD, &p, &a);
      while (p != NULL) {
         if (p->horz == x_lvl && a != NULL) {
            /*---(set left)-----------------*/
            if (p->x_tie  != '-')  {
               /*---(rightside is variable)----------*/
               /*   [--------------full]----------------]               */
               /*   xxxx[--a--][-----------p----------->?               */
               if (a->on != 'y' || a->wide > 0) {
                  DEBUG_YVIEW   yLOG_note    ("leftmost is fixed length or off");
                  p->left = a->left + a->wide;
                  if (p->on == 'y')  p->wide  = myVIEW.full_wide - p->left;
                  else               p->wide  = 0;
               }
               /*---(leftside is variable)-----------*/
               /*   [--------------full]----------------]               */
               /*   xxxx[-----------a----------->?[--p--]               */
               else {
                  DEBUG_YVIEW   yLOG_note    ("leftmost is variable length");
                  p->left  = myVIEW.full_wide - p->wide;
                  if (a->on == 'y')  a->wide  = p->left - a->left;
                  else               a->wide  = 0;
               }
               /*---(read-out)-----------------*/
               DEBUG_YVIEW   yLOG_complex ("linked"    , "%c %-12.12s wide %3d AND %c %-12.12s wide %3d", p->abbr, p->name, p->wide, a->abbr, a->name, a->wide);
            }
            /*---(done)---------------------*/
         }
         yview_by_cursor (YDLST_NEXT, &p, &a);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz__float       (tYVIEW_PARTS *w, tYVIEW_PARTS *p)
{
   /*---(locals)-----------+-----+-----+-*/
   float       x_big       =  0.0;
   float       x_sml       =  0.0;
   float       x_haf       =  0.0;
   float       x_qtr       =  0.0;
   float       x_edg       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   /*---(widths)-------------------------*/
   x_big   = w->wide * 0.90;
   x_sml   = w->wide * 0.50;
   if (x_big > 500)  x_big = 500;
   if (x_big < 500 && w->wide >= 500)  x_big = 500;
   if (x_sml > 250)  x_sml = 250;
   if (x_sml < 250 && w->wide >= 250)  x_sml = 250;
   DEBUG_YVIEW   yLOG_complex ("widths"    , "%4df, %4db, %4ds", w->wide, x_big, x_sml);
   /*---(positions)----------------------*/
   x_haf   = w->wide * 0.50;
   x_qtr   = x_haf  / 4.0;
   x_edg   = (w->wide - x_big) / 2.0;
   DEBUG_YVIEW   yLOG_complex ("positions" , "%4dl, %4dh, %4dq", w->left, x_haf, x_qtr);
   /*---(positions)----------------------*/
   switch (p->anchor) {
   case YVIEW_TOPLEF : case YVIEW_MIDLEF : case YVIEW_BOTLEF :
      p->wide = x_sml;
      p->left = w->left;
      break;
   case YVIEW_UPSBEG : case YVIEW_MIDBEG : case YVIEW_LOWBEG :
      p->wide = x_sml;
      p->left = w->left + (x_haf - x_sml) / 2.0;
      break;
   case YVIEW_TOPCEN : case YVIEW_MIDCEN : case YVIEW_BOTCEN : case YVIEW_UPSCEN : case YVIEW_LOWCEN :
      p->wide = x_sml;
      p->left = w->left + x_haf - (x_sml / 2.0);
      break;
   case YVIEW_TOPALL : case YVIEW_MIDALL : case YVIEW_BOTALL : case YVIEW_UPSALL : case YVIEW_LOWALL :
      p->wide = x_big;
      p->left = w->left + x_edg;
      break;
   case YVIEW_UPSEND : case YVIEW_MIDEND : case YVIEW_LOWEND :
      p->wide = x_sml;
      p->left = w->left + w->wide + (x_haf - x_sml) / 2.0 - p->wide;
      break;
   case YVIEW_TOPRIG : case YVIEW_MIDRIG : case YVIEW_BOTRIG :
      p->wide = x_sml;
      p->left = w->wide - x_sml;
      break;
   case YVIEW_HIDDEN :
      p->wide = x_sml;
      p->left = w->wide + x_haf * 2.0;
      break;
   }
   /*---(limits)-------------------------*/
   if (p->left < w->left)             p->left = w->left;
   if (p->left + p->wide > w->wide)   p->left = w->wide - p->wide;
   /*---(result)-------------------------*/
   DEBUG_YVIEW   yLOG_complex ("horz_float", "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_float, w->left, w->wide, p->wide, p->left);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz__menus       (tYVIEW_PARTS *w, tYVIEW_PARTS *p)
{
   /*> p->type = w->type;                                                             <*/
   float       x_side      =  0.0;
   float       x_half      =  0.0;
   float       x_qtr       =  0.0;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_value   ("a_left"    , w->left);
   DEBUG_YVIEW   yLOG_value   ("wide"      , p->wide);
   p->wide = p->def_wide;
   x_side  = p->wide * 0.50;
   x_half  = w->wide * 0.50;
   x_qtr   = (x_half - x_side) * 0.60;
   switch (p->anchor) {
   case YVIEW_TOPLEF : case YVIEW_MIDLEF : case YVIEW_BOTLEF :
      p->left = w->left;
      break;
   case YVIEW_UPSBEG : case YVIEW_MIDBEG : case YVIEW_LOWBEG :
      p->left = w->left + x_half - x_qtr  - x_side;
      break;
   case YVIEW_TOPCEN : case YVIEW_MIDCEN : case YVIEW_BOTCEN : case YVIEW_UPSCEN : case YVIEW_LOWCEN :
   case YVIEW_TOPALL : case YVIEW_MIDALL : case YVIEW_BOTALL : case YVIEW_UPSALL : case YVIEW_LOWALL :
      p->left = w->left + x_half - x_side;
      break;
   case YVIEW_UPSEND : case YVIEW_MIDEND : case YVIEW_LOWEND :
      p->left = w->left + x_half + x_qtr - x_side;
      break;
   case YVIEW_TOPRIG : case YVIEW_MIDRIG : case YVIEW_BOTRIG :
      p->left = w->left + w->wide - p->wide;
      break;
   case YVIEW_HIDDEN :
      p->left = w->left - x_half * 2.0;
      break;
   }
   DEBUG_YVIEW   yLOG_complex ("horz_menu" , "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_menu, w->left, w->wide, p->wide, p->left);
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz__hist        (tYVIEW_PARTS *w, tYVIEW_PARTS *p)
{
   /*> p->type = w->type;                                                             <*/
   switch (p->anchor) {
   case YVIEW_ALLLEF :
      p->wide = w->wide * 0.45;
      p->left = w->left + (w->wide * 0.05);
      break;
   case YVIEW_ALLCEN :
      p->wide = w->wide * 0.50;
      p->left = w->left + (w->wide * 0.25);
      break;
   case YVIEW_ALLRIG :
      p->wide = w->wide * 0.45;
      p->left = w->left + (w->wide * 0.50);
      break;
   case YVIEW_ALLFUL :
      p->wide = w->wide * 0.80;
      p->left = w->left + (w->wide * 0.10);
      break;
   }
   DEBUG_YVIEW   yLOG_complex ("horz_hist" , "%c, %3da, %3ds, %3dw, %3dl", myVIEW.loc_hist, w->left, w->wide, p->wide, p->left);
   return 0;
}

char
yview_horz_float        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tYVIEW_PARTS     *w           = NULL;
   tYVIEW_PARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(get main info)------------------*/
   yview_by_abbr   (YVIEW_WINDOW, &w, NULL);
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
         yview_horz__float  (w, p);
         break;
      case YVIEW_MENUS    :
         yview_horz__menus  (w, p);
         break;
      case YVIEW_HISTORY  :
         yview_horz__hist   (w, p);
         break;
      default               :
         yview_by_cursor (YDLST_NEXT, &p, NULL);
         continue;
      }
      /*---(display)------------------*/
      DEBUG_YVIEW   yLOG_complex ("overlay"   , "%c %-12.12s %3d wide", p->abbr, p->name, p->wide);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_final         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tYVIEW_PARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
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
      DEBUG_YVIEW   yLOG_complex ("other"     , "%c %-12.12s %3d wide", p->abbr, p->name, p->wide);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
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
   tYVIEW_PARTS     *p           = NULL;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(check for opengl)---------------*/
   DEBUG_YVIEW   yLOG_char    ("env"       , myVIEW.env);
   if (myVIEW.env != YVIEW_OPENGL) {
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(walk all)-----------------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      /*---(non-overlays)----------------*/
      if (p->own  != YVIEW_OWN_OVERLAY && p->own  != YVIEW_OWN_FLOAT && p->own  != YVIEW_OWN_WINDOW) {
         /*---(display)------------------*/
         DEBUG_YVIEW   yLOG_complex ("handling"  , "%c %-12.12s", p->abbr, p->name);
         /*---(easy first)---------------*/
         x_len = p->xlen = p->wide;
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
         /*---(and last)-----------------*/
         x_max = p->xmin + x_len;
      }
      /*---(display)---------------------*/
      DEBUG_YVIEW   yLOG_complex ("coords"    , "%c %-12.12s, %4dx, %4dw", p->abbr, p->name, p->xmin, p->xlen);
      /*---(done)------------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_overlay      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tYVIEW_PARTS     *w           = NULL;
   tYVIEW_PARTS     *m           = NULL;
   tYVIEW_PARTS     *p           = NULL;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(check for opengl)---------------*/
   DEBUG_YVIEW   yLOG_char    ("env"       , myVIEW.env);
   /*> if (myVIEW.env != YVIEW_OPENGL) {                                              <* 
    *>    DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);                                   <* 
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
      /*> if (p->mgmt != YVIEW_AUTO)  continue;                                       <*/
      /*---(main overlays)---------------*/
      if (p->own  == YVIEW_OWN_OVERLAY) {
         DEBUG_YVIEW   yLOG_complex ("main over" , "%c %-12.12s", p->abbr, p->name);
         p->left = m->left;
         p->wide = m->wide;
         if (myVIEW.env == YVIEW_OPENGL) {
            p->xmin = m->xmin;
            p->xlen = m->xlen;
         }
      }
      /*---(window overlays)-------------*/
      else if (p->own  == YVIEW_OWN_WINDOW) {
         DEBUG_YVIEW   yLOG_complex ("wind over" , "%c %-12.12s", p->abbr, p->name);
         p->left = w->left;
         p->wide = w->wide;
         if (myVIEW.env == YVIEW_OPENGL) {
            p->xmin = w->xmin;
            p->xlen = w->xlen;
         }
      }
      /*---(ignore floaters)-------------*/
      else if (p->own  == YVIEW_OWN_FLOAT) {
         DEBUG_YVIEW   yLOG_complex ("not float" , "%c %-12.12s", p->abbr, p->name);
      }
      /*---(display)---------------------*/
      DEBUG_YVIEW   yLOG_complex ("overlay"   , "%c %-12.12s, %4dx, %4dw", p->abbr, p->name, p->xmin, p->xlen);
      /*---(done)------------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_horz_status       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tYVIEW_PARTS     *p           = NULL;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   yview_by_abbr   (YVIEW_STATUS, &p, NULL);
   /*---(set size)--------------------*/
   myVIEW.s_wide = p->wide;
   if      (p->wide <  20)  myVIEW.s_size  = 'u';
   else if (p->wide <  40)  myVIEW.s_size  = 't';
   else if (p->wide <  70)  myVIEW.s_size  = 's';
   else if (p->wide < 110)  myVIEW.s_size  = 'm';
   else if (p->wide < 160)  myVIEW.s_size  = 'l';
   else if (p->wide < 220)  myVIEW.s_size  = 'h';
   else                     myVIEW.s_size  = 'g';
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_horz_source       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tYVIEW_PARTS     *f           = NULL;
   tYVIEW_PARTS     *p           = NULL;
   short       x_formula   =    0;
   short       x_command   =    0;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(set float)-------------------*/
   yview_by_abbr   (YVIEW_FLOAT  , &f, NULL);
   /*---(set formula)-----------------*/
   yview_by_abbr   (YVIEW_FORMULA, &p, NULL);
   if (p->on == 'y')    x_formula = p->wide;
   else                 x_formula = f->wide;
   /*---(set command)-----------------*/
   yview_by_abbr   (YVIEW_COMMAND, &p, NULL);
   if (p->on == 'y')    x_command = p->wide;
   else                 x_command = f->wide;
   /*---(update ySCR)--------------------*/
   yVIHUB_ySRC_size (x_formula, x_command);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_horz_xaxis        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tYVIEW_PARTS     *b           = NULL;
   tYVIEW_PARTS     *m           = NULL;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(set)-------------------------*/
   /*> yview_by_abbr   (YVIEW_BUFFER , &b, NULL);                                     <* 
    *> if (b->on == 'y')  yMAP_axis_avail ('u', b->wide);                             <* 
    *> yview_by_abbr   (YVIEW_MAIN   , &m, NULL);                                     <* 
    *> yMAP_axis_avail ('x', m->wide);                                                <* 
    *> if (b->on != 'y')  yMAP_axis_avail ('u', m->wide);                             <*/
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_complex ("args"      , "wide %3d, alt %3d", a_wide, a_alt);
   /*---(widths)-------------------------*/
   yview_horz_fixed   ();
   yview_horz_auto    (a_wide, a_alt);
   yview_horz_var     ();
   yview_horz_link    ();
   yview_horz_float   ();
   yview_horz_final   ();
   yview_horz_coords  ();
   yview_horz_overlay ();
   yview_horz_status  ();
   yview_horz_source  ();
   yview_horz_xaxis   ();
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}


