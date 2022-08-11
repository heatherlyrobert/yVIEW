/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



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
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   s_cum = 0;
   /*---(find fixed heights)-------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_YVIEW   yLOG_value   ("LEVEL"     , x_lvl);
      x_max = 0;
      yview_by_cursor (YDLST_HEAD, &p, NULL);
      while (p != NULL) {
         DEBUG_YVIEW   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, vert %d, %c %c %c", p, p->abbr, p->name, p->on, p->vert, p->y_tie, p->under, p->noy);
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
            DEBUG_YVIEW   yLOG_complex ("fixed"     , "%c %-12.12s tall %3d, bott %3d, max %3d, cum %3d, %c", p->abbr, p->name, p->tall, p->bott, x_max, s_cum, x_skip);
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
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_vert_auto  (cint a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   int         x_other     =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(major sizes)--------------------*/
   if (myVIEW.env == YVIEW_OPENGL) {
      myVIEW.full_tall = s_cum + a_tall;
      myVIEW.main_tall = a_tall;
      x_other     = a_tall + s_prog + s_xaxis;
   } else {
      myVIEW.full_tall = a_tall;
      myVIEW.main_tall = a_tall - s_cum;
      x_other     = a_tall - s_cum + s_prog;
   }
   DEBUG_YVIEW   yLOG_complex ("bigs"      , "full %3d, main %3d, other %3d, s_cum %3d", myVIEW.full_tall, myVIEW.main_tall, x_other, s_cum);
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
      case YVIEW_WINDOW   : p->tall = myVIEW.full_tall;               break;
      case YVIEW_MAIN     :
      case YVIEW_NOTES    :
      case YVIEW_ALT      :
      case YVIEW_YAXIS    : p->tall = myVIEW.main_tall;               break;
      case YVIEW_NAV      :
      case YVIEW_DETAILS  :
      case YVIEW_RIBBON   : p->tall = x_other;                   break;
      default             : yview_by_cursor (YDLST_NEXT, &p, NULL); continue;
      }
      /*---(display)------------------*/
      DEBUG_YVIEW   yLOG_complex ("automatic" , "%c %-12.12s tall %3d, bott %3d", p->abbr, p->name, p->tall, p->bott);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(set lefts)----------------------*/
   s_cum = 0;
   /*---(find var widths)----------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_YVIEW   yLOG_value   ("LEVEL"     , x_lvl);
      x_max = 0;
      yview_by_cursor (YDLST_HEAD, &p, NULL);
      while (p != NULL) {
         DEBUG_YVIEW   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, vert %d, %c %c %c", p, p->abbr, p->name, p->on, p->vert, p->y_tie, p->under, p->noy);
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
            DEBUG_YVIEW   yLOG_complex ("variable"  , "%c %-12.12s tall %3d, bott %3d, max %3d, cum %3d, %c", p->abbr, p->name, p->tall, p->bott, x_max, s_cum, x_skip);
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
yview_vert_link  (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_lvl       =    0;          /* evaluation level               */
   tPARTS     *p           = NULL;
   tPARTS     *a           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(find var widths)----------------*/
   for (x_lvl = 1; x_lvl <= 9; ++x_lvl) {
      DEBUG_YVIEW   yLOG_value   ("LEVEL"     , x_lvl);
      yview_by_cursor (YDLST_HEAD, &p, &a);
      while (p != NULL) {
         DEBUG_YVIEW   yLOG_complex ("checking"  , "%-10.10p, %c %-10.10s, on %c, vert %d, %c %c %c", p, p->abbr, p->name, p->on, p->vert, p->y_tie, p->under, p->noy);
         if (p->vert == x_lvl && a != NULL) {
            /*---(set left)-----------------*/
            if (p->y_tie  != '-')  {
               a->tall  = myVIEW.full_tall - a->bott - p->tall;
               p->bott  = myVIEW.full_tall - p->tall;
               /*---(read-out)-----------------*/
               DEBUG_YVIEW   yLOG_complex ("linked"    , "%c %-12.12s tall %3d, bott %3d AND %c %-12.12s tall %3d, bott %3d", p->abbr, p->name, p->tall, p->bott, a->abbr, a->name, a->tall, a->bott);
            }
         }
         yview_by_cursor (YDLST_NEXT, &p, &a);
      }
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview__vert_float       (tPARTS *m, tPARTS *p)
{
   /*> p->type   = m->type;                                                           <*/
   p->tall   = p->def_tall;
   p->magn   = m->magn;
   switch (p->anchor) {
   case YVIEW_TOPALL : p->bott = m->bott + m->tall - (p->tall * 2.0); break;
   case YVIEW_UPSALL : p->bott = m->bott + m->tall * (0.75) - (p->tall * 0.5);  break;
   case YVIEW_MIDALL : p->bott = m->bott + m->tall * (0.50) - (p->tall * 0.5);  break;
   case YVIEW_LOWALL : p->bott = m->bott + m->tall * (0.25) - (p->tall * 0.5);  break;
   case YVIEW_BOTALL : p->bott = m->bott + p->tall;  break;
   default    :
                       DEBUG_YVIEW   yLOG_note    ("no appropriate float location found");
                       break;
   }
   DEBUG_YVIEW   yLOG_complex ("vert_float", "%c, %3da, %3ds, %3dt, %3db", myVIEW.loc_float, m->bott, m->tall, p->tall, p->bott);
   p->zmin   = m->zmin;
   p->zlen   = m->zlen;
   return 0;
}

char
yview__vert_menu        (tPARTS *m, tPARTS *p)
{
   short       x_bott      =    0;
   short       x_bottm     =    0;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_complex ("main"      , "bott %4d tall %4d anchor %c magn %5.2f ymin %4d ylen %4d", m->bott, m->tall, m->anchor, m->magn, m->ymin, m->ylen);
   /*> p->type   = m->type;                                                           <*/
   p->tall   = p->def_tall;
   p->magn   = m->magn;
   switch (p->anchor) {
   case YVIEW_TOPALL : case YVIEW_TOPLEF : case YVIEW_TOPCEN : case YVIEW_TOPRIG :
      p->bott = m->bott + m->tall - p->tall;
      break;
   case YVIEW_UPSALL : case YVIEW_UPSBEG : case YVIEW_UPSCEN : case YVIEW_UPSEND :
      p->bott = m->bott + (m->tall * 0.75) - (p->tall * 0.50);
      break;
   case YVIEW_MIDALL : case YVIEW_MIDLEF : case YVIEW_MIDCEN : case YVIEW_MIDRIG : case YVIEW_MIDBEG : case YVIEW_MIDEND :
      p->bott = m->bott + (m->tall * 0.50) - (p->tall * 0.50);
      break;
   case YVIEW_LOWALL : case YVIEW_LOWBEG : case YVIEW_LOWCEN : case YVIEW_LOWEND :
      p->bott = m->bott + (m->tall * 0.25) - (p->tall * 0.50);;
      break;
   case YVIEW_BOTALL : case YVIEW_BOTLEF : case YVIEW_BOTCEN : case YVIEW_BOTRIG :
      p->bott = m->bott;
      break;
   default    :
      DEBUG_YVIEW   yLOG_note    ("no appropriate menu location found");
      break;
   }
   /*> if (myVIEW.env == YVIEW_OPENGL) {                                                                                                                               <* 
    *>    /+> p->ymin = m->ymin + (p->bott - m->bott) * m->magn;                             <+/                                                                       <* 
    *>    x_bott  = p->bott - m->bott;                                                                                                                                 <* 
    *>    x_bottm = x_bott  * m->magn;                                                                                                                                 <* 
    *>    p->ymin = m->ymin + x_bottm;                                                                                                                                 <* 
    *>    DEBUG_YVIEW   yLOG_complex ("y_min"     , "%4db - %4db = %4dB * %5.2fm = %4d + %4dn = %4dN", p->bott, m->bott, x_bott, m->magn, x_bottm, m->ymin, p->ymin);   <* 
    *>    p->ylen = p->tall * m->magn;                                                                                                                                 <* 
    *>    DEBUG_YVIEW   yLOG_complex ("y_len"     , "%4dt, %4dT * %5.2fm = %4dL", p->def_tall, p->tall, m->magn, p->ylen);                                              <* 
    *> }                                                                                                                                                               <*/
   DEBUG_YVIEW   yLOG_complex ("vert_menu" , "%c, %4db, %4dt, %4dn, %4dx", myVIEW.loc_menu, p->bott, p->tall, p->ymin, p->ylen);
   p->zmin   = m->zmin;
   p->zlen   = m->zlen;
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview__vert_hist        (tPARTS *m, tPARTS *p)
{
   /*> p->type = m->type;                                                             <*/
   p->magn = m->magn;
   p->tall = m->tall * 0.90;
   p->bott = m->bott + (m->tall * 0.05);
   DEBUG_YVIEW   yLOG_complex ("vert_hist" , "%c, %3da, %3ds, %3dt, %3db", myVIEW.loc_hist, m->bott, m->tall, p->tall, p->bott);
   p->zmin   = m->zmin;
   p->zlen   = m->zlen;
   return 0;
}

char
yview_vert_float        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *m           = NULL;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(get main info)------------------*/
   yview_by_abbr (YVIEW_MAIN, &m, NULL);
   DEBUG_YVIEW   yLOG_complex ("working"   , "bott %4d tall %4d anchor %c magn %5.2f ymin %4d ylen %4d", m->bott, m->tall, m->anchor, m->magn, m->ymin, m->ylen);
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
         yview__vert_float (m, p);
         break;
      case YVIEW_MENUS    :
         yview__vert_menu  (m, p);
         break;
      case YVIEW_HISTORY  :
         yview__vert_hist  (m, p);
         break;
      case YVIEW_GRID     : case YVIEW_OVERLAY  :
      case YVIEW_NOTES    : case YVIEW_CURSOR   :
         /*> p->type = m->type;                                                       <*/
         p->magn = m->magn;
         p->zmin = m->zmin;
         p->zlen = m->zlen;
      default               :
         yview_by_cursor (YDLST_NEXT, &p, NULL);
         continue;
      }
      /*---(display)------------------*/
      DEBUG_YVIEW   yLOG_complex ("overlay"   , "%c %-12.12s, bott %4d tall %4d ymin %4d ylen %4d ymax %4d", p->abbr, p->name, p->bott, p->tall, p->ymin, p->ylen, p->ymin + p->ylen);
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> flip bottoms for ncurses -----------[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_vert_final        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(fill in widths)-----------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      if (p->on   == 'y' && p->tall ==  0 ) {
         p->tall = myVIEW.full_tall - p->bott;
         DEBUG_YVIEW   yLOG_complex ("fill"      , "%c %-12.12s tall %3d, bott %3d", p->abbr, p->name, p->tall, p->bott);
      }
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char         /*-> flip bottoms for ncurses -----------[ ------ [gz.742.001.01]*/ /*-[00.0000.112.!]-*/ /*-[--.---.---.--]-*/
yview_vert_flip         (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   if (myVIEW.env == YVIEW_OPENGL) {
      DEBUG_YVIEW   yLOG_note    ("not required for opengl");
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(display)------------------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      DEBUG_YVIEW   yLOG_complex (p->name, "bott %4d, left %4d, wide %4d, tall %4d, on %c", p->bott, p->left, p->wide, p->tall, p->on);
      p->bott = myVIEW.full_tall - p->bott - 1;
      DEBUG_YVIEW   yLOG_complex (p->name, "bott %4d, left %4d, wide %4d, tall %4d, on %c", p->bott, p->left, p->wide, p->tall, p->on);
      if (p->bott < 0)  p->bott = 0;
      DEBUG_YVIEW   yLOG_complex (p->name, "bott %4d, left %4d, wide %4d, tall %4d, on %c", p->bott, p->left, p->wide, p->tall, p->on);
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
yview_vert_coords       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   short       y_len       =    0;
   short       y_max       =    0;
   tPARTS     *p           = NULL;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(check for opengl)---------------*/
   DEBUG_YVIEW   yLOG_schar   (myVIEW.env);
   if (myVIEW.env != YVIEW_OPENGL) {
      DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(walk all)-----------------------*/
   yview_by_cursor (YDLST_HEAD, &p, NULL);
   while (p != NULL) {
      /*---(skip non-auto)---------------*/
      if (p->mgmt != YVIEW_AUTO)  continue;
      if (p->own  != OWN_OVERLAY) {
         /*---(easy first)---------------*/
         y_len = p->ylen = p->tall * p->magn;
         DEBUG_YVIEW   yLOG_sint    (y_len);
         /*---(vertical)-----------------*/
         switch (p->anchor) {
         case YVIEW_TOPLEF : case YVIEW_TOPCEN : case YVIEW_TOPRIG :
            p->ymin = 0 - y_len;
            break;
         case YVIEW_UPSBEG : case YVIEW_UPSCEN : case YVIEW_UPSEND :
            p->ymin = 0 - (y_len * 0.75);
            break;
         case YVIEW_MIDLEF : case YVIEW_MIDBEG : case YVIEW_MIDCEN : case YVIEW_MIDEND : case YVIEW_MIDRIG :
            p->ymin = 0 - (y_len * 0.50);
            break;
         case YVIEW_LOWBEG : case YVIEW_LOWCEN : case YVIEW_LOWEND :
            p->ymin = 0 - (y_len * 0.75);
            break;
         case YVIEW_BOTLEF : case YVIEW_BOTCEN : case YVIEW_BOTRIG :
            p->ymin = 0;
            break;
         }
         DEBUG_YVIEW   yLOG_sint    (p->ymin);
         /*---(and last)-----------------*/
         y_max = p->ymin + y_len;
         DEBUG_YVIEW   yLOG_sint    (y_max);
      }
      /*---(done)------------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_vert_overlay      (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *w           = NULL;
   tPARTS     *m           = NULL;
   tPARTS     *p           = NULL;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(check for opengl)---------------*/
   DEBUG_YVIEW   yLOG_schar   (myVIEW.env);
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
      if (p->mgmt != YVIEW_AUTO)  continue;
      if (p->own  == OWN_OVERLAY) {
         /*---(full main space)----------*/
         if (strchr (OVER_FULL, p->abbr) != NULL) {
            p->bott = m->bott;
            p->tall = m->tall;
            if (myVIEW.env == YVIEW_OPENGL) {
               p->ymin = m->ymin;
               p->ylen = m->ylen;
            }
         }
         /*---(full window space)--------*/
         else if (strchr (OVER_WIND, p->abbr) != NULL) {
            p->bott = w->bott;
            p->tall = w->tall;
            if (myVIEW.env == YVIEW_OPENGL) {
               p->ymin = w->ymin;
               p->ylen = w->ylen;
            }
         } 
         /*---(sub-main space)-----------*/
         else {
            if (myVIEW.env == YVIEW_OPENGL) {
               p->ylen = p->tall * p->magn;
               p->ymin = m->ymin + ((p->bott - m->bott) * m->magn);
            }
         }
         DEBUG_YVIEW   yLOG_sint    (p->ymin);
         DEBUG_YVIEW   yLOG_sint    (p->ylen);
         DEBUG_YVIEW   yLOG_sint    (p->ymin + p->ylen);
      }
      /*---(done)---------------------*/
      yview_by_cursor (YDLST_NEXT, &p, NULL);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_vert_yaxis        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *m           = NULL;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(set)-------------------------*/
   /*> yview_by_abbr   (YVIEW_MAIN   , &m, NULL);                                     <* 
    *> yMAP_axis_avail ('y', m->tall);                                                <* 
    *> yMAP_axis_avail ('z', 0);                                                      <*/
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_vert_progress     (void)
{
   /*---(locals)-----------+-----+-----+-*/
   tPARTS     *m           = NULL;
   tPARTS     *a           = NULL;
   tPARTS     *x           = NULL;
   tPARTS     *y           = NULL;
   tPARTS     *p           = NULL;
   int         x_max       =    0;
   int         x_theo      =    0;
   int         x_rem       =    0;
   float       x_ratio     =  0.0;
   int         x_orig      =    0;
   int         x_tall      =    0;
   /*---(header)----------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(check full status)-----------*/
   DEBUG_YVIEW   yLOG_schar   (myVIEW.prog_full);
   if (myVIEW.prog_full == '-') {
      DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(get specific windows)-----------*/
   yview_by_abbr   (YVIEW_MAIN    , &m, NULL);
   yview_by_abbr   (YVIEW_ALT     , &a, NULL);
   yview_by_abbr   (YVIEW_XAXIS   , &x, NULL);
   yview_by_abbr   (YVIEW_YAXIS   , &y, NULL);
   yview_by_abbr   (YVIEW_PROGRESS, &p, NULL);
   /*---(set)-------------------------*/
   x_orig  = p->tall;
   x_max   = x->tall + m->tall + p->tall;
   switch (myVIEW.prog_full) {
   case 'y' :
      p->tall = x_max;
      x_rem   = 0;
      break;
   default  :
      x_theo  = p->tall * (myVIEW.prog_full - '0');
      if (x_theo >= x_max)  { p->tall = x_max;  x_rem = x_max; }
      else                  { p->tall = x_theo; x_rem = x_max - x_theo; }
      break;
   }
   p->ylen = p->tall;
   if (x_rem <  x->tall) {
      x->tall = 0; x->wide = 0;  x->ylen = 0;
      y->tall = 0; y->wide = 0;  y->ylen = 0;
      m->tall = 0; m->wide = 0;  m->ylen = 0;
      a->tall = 0; a->wide = 0;  a->ylen = 0;
   } else {
      x_rem  -= x->tall;
      x_ratio = x_rem / (float) (x->tall + m->tall);
      x_tall  = p->tall - x_orig;
      y->bott += x_tall;
      y->tall = x_rem;  y->ylen *= x_ratio;
      m->bott += x_tall;
      m->tall = x_rem;  m->ylen *= x_ratio;
      a->bott += x_tall;
      a->tall = x_rem;  a->ylen *= x_ratio;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
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
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_value   ("a_tall"    , a_tall);
   /*---(heights)------------------------*/
   yview_vert_fixed    ();
   yview_vert_auto     (a_tall);
   yview_vert_var      ();
   yview_vert_link     ();
   yview_vert_float    ();
   yview_vert_final    ();
   yview_vert_flip     ();
   yview_vert_coords   ();
   yview_vert_overlay  ();
   yview_vert_yaxis    ();
   yview_vert_progress ();
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}


