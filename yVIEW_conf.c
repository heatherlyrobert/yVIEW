/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



/*====================------------------------------------====================*/
/*===----                      default sizes                           ----===*/
/*====================------------------------------------====================*/
static void      o___DEFSIZE_________________o (void) {;}

char
yVIEW_defsize           (char a_part, short a_wide, short a_tall)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   tPARTS     *a           = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(identify part)------------------*/
   DEBUG_PROG   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, &a);
   DEBUG_PROG   yLOG_point   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_note    ("deal with a missing element");
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("name"      , p->name);
   DEBUG_PROG   yLOG_char    ("p->defs"   , p->defs);
   --rce;  if (p->defs == 0 || strchr ("wtB", p->defs) == NULL) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check default control)----------*/
   --rce;  if (p->defs == 'w' && a_tall != 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (p->defs == 't' && a_wide != 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(size)---------------------------*/
   DEBUG_PROG   yLOG_complex ("before"    , "%4dW, %4dT", p->def_wide, p->def_tall);
   if (a_wide > 0)  p->def_wide = a_wide;
   if (a_tall > 0)  p->def_tall = a_tall;
   DEBUG_PROG   yLOG_complex ("after"     , "%4dW, %4dT", p->def_wide, p->def_tall);
   /*---(check alt)----------------------*/
   DEBUG_PROG   yLOG_point   ("a"         , a);
   if (a != NULL) {
      DEBUG_PROG   yLOG_char    ("a->defs"   , a->defs);
      DEBUG_PROG   yLOG_info    ("name"      , a->name);
      DEBUG_PROG   yLOG_complex ("before"    , "%4dW, %4dT", a->def_wide, a->def_tall);
      if (a_wide > 0 && (strchr ("Bw", a->defs) != NULL))  a->def_wide = a_wide;
      if (a_tall > 0 && (strchr ("Bt", a->defs) != NULL))  a->def_tall = a_tall;
      DEBUG_PROG   yLOG_complex ("after"     , "%4dW, %4dT", a->def_wide, a->def_tall);
   }
   /*---(recalc)-------------------------*/
   yview_update ();
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      view configuration                      ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

char
yview__conf_type        (tPARTS *p, char a_type)
{
   DEBUG_PROG   yLOG_char    ("a_type"    , a_type);
   if      (a_type == YVIEW_LEAVE)     return 0;
   else if (a_type == YVIEW_DEPTH)     p->type = YVIEW_DEPTH;
   else                                p->type = YVIEW_FLAT;
   DEBUG_PROG   yLOG_char    ("type"      , p->type);
   return 0;
}

char
yview__conf_anchor      (tPARTS *p, char a_anchor)
{
   DEBUG_PROG   yLOG_value   ("a_anchor"  , a_anchor);
   if (p->anchor == 0) {
      DEBUG_PROG   yLOG_note    ("part has a dependent anchor");
      return 0;
   }
   if      (a_anchor == YVIEW_LEAVE)   return 0;
   else if (a_anchor <  '0' )         a_anchor = YVIEW_MIDCEN;
   else if (a_anchor >  '9' )         a_anchor = YVIEW_MIDCEN;
   DEBUG_PROG   yLOG_value   ("a_anchor"  , a_anchor);
   yview_set_anchor (p->abbr, a_anchor);
   return 0;
}

char
yview__conf_color       (tPARTS *p, char a_color)
{
   DEBUG_PROG   yLOG_value   ("a_color"   , a_color);
   if (p->color == YVIEW_LEAVE) {
      DEBUG_PROG   yLOG_note    ("part must be clear");
      return 0;
   }
   if      (a_color == YVIEW_LEAVE)    return 0;
   else if (a_color <=  0)             p->color  = 0;
   else if (a_color >  50)             p->color  = 0;
   else                                p->color  = a_color;
   DEBUG_PROG   yLOG_value   ("color"     , p->color);
   return 0;
}

char
yview__conf_magn        (tPARTS *p, float a_magn)
{
   DEBUG_PROG   yLOG_double  ("a_magn"    , a_magn);
   switch (p->abbr) {
   case YVIEW_WINDOW  :
   case YVIEW_MASK    :
      DEBUG_PROG   yLOG_note    ("part can not be magnified");
      return 0;
      break;
   }
   if      (a_magn  == YVIEW_LEAVE)    return 0;
   else if (a_magn >  0.01 && a_magn < 100.0)  p->magn = a_magn;
   DEBUG_PROG   yLOG_double  ("magn"      , p->magn);
   return 0;
}

char
yview__conf_drawer      (tPARTS *p, void *a_drawer)
{
   DEBUG_PROG   yLOG_point   ("a_drawer"  , a_drawer);
   switch (p->abbr) {
   case YVIEW_WINDOW  :
      DEBUG_PROG   yLOG_note    ("part can not have drawer");
      return 0;
      break;
   }
   if (a_drawer != NULL)    p->drawer = a_drawer;
   DEBUG_PROG   yLOG_point   ("drawer"    , p->drawer);
   return 0;
}

char
yview_conf_text         (char a_part, char *a_text)
{
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   if (rc < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_GRAF   yLOG_value   ("search"    , rc);
   if (a_text != NULL)  strlcpy (p->text, a_text, LEN_RECD);
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_simple            (char a_part, char a_color, void *a_drawer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(identify part)------------------*/
   DEBUG_PROG   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_PROG   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("name"      , p->name);
   DEBUG_PROG   yLOG_char    ("own"       , p->own);
   /*> --rce;  if (strchr (OWN_SIMPLE, p->own) == NULL) {                             <* 
    *>    DEBUG_PROG   yLOG_note    ("can not use function on this element");         <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(update)-------------------------*/
   yview__conf_color  (p, a_color);
   yview__conf_drawer (p, a_drawer);
   /*---(finish up)----------------------*/
   /*> p->mgmt   = YVIKEYS_AUTO;                                                      <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_full              (char a_part, char a_type, char a_anchor, float a_magn, char a_color, void *a_drawer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_PROG   yLOG_enter   (__FUNCTION__);
   /*---(identify part)------------------*/
   DEBUG_PROG   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_PROG   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_PROG   yLOG_info    ("name"      , p->name);
   DEBUG_PROG   yLOG_char    ("own"       , p->own);
   /*> --rce;  if (strchr (OWN_MODERATE, p->own) == NULL) {                           <* 
    *>    DEBUG_PROG   yLOG_note    ("can not use function on this element");         <* 
    *>    DEBUG_PROG   yLOG_exitr   (__FUNCTION__, rce);                              <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(update)-------------------------*/
   yview__conf_type   (p, a_type);
   yview__conf_anchor (p, a_anchor);
   yview__conf_magn   (p, a_magn);
   yview__conf_color  (p, a_color);
   yview__conf_drawer (p, a_drawer);
   /*---(finish up)----------------------*/
   yview_update ();
   /*> p->mgmt   = YVIKEYS_AUTO;                                             <*/
   /*---(complete)-----------------------*/
   DEBUG_PROG   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yVIEW_keys    (char *a_text) { return yview_conf_text (YVIEW_KEYS   , a_text); }
char yVIEW_modes   (char *a_text) { return yview_conf_text (YVIEW_MODES  , a_text); }
char yVIEW_title   (char *a_text) { return yview_conf_text (YVIEW_TITLE  , a_text); }



/*====================------------------------------------====================*/
/*===----                      data accessors                          ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESSOR________o () { return; }

char
yVIEW_size              (char a_part, char *a_on, short *a_left, short *a_wide, short *a_bott, short *a_tall)
{
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_GRAF   yLOG_value   ("search"    , rc);
   if (rc < 0) {
      DEBUG_GRAF   yLOG_note    ("deal with a missing element");
      if (a_on   != NULL)  *a_on    = '-';
      if (a_left != NULL)  *a_left  = 0;
      if (a_bott != NULL)  *a_bott  = 0;
      if (a_wide != NULL)  *a_wide  = 0;
      if (a_tall != NULL)  *a_tall  = 0;
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_GRAF   yLOG_note    ("save values for good entry");
   if (a_on   != NULL)  *a_on    = p->on;
   if (a_left != NULL)  *a_left  = p->left;
   if (a_bott != NULL)  *a_bott  = p->bott;
   if (a_wide != NULL)  *a_wide  = p->wide;
   if (a_tall != NULL)  *a_tall  = p->tall;
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_bounds            (char a_part, char *a_type, char *a_anchor, float *a_magn, short *a_xmin, short *a_xmax, short *a_xlen, short *a_ymin, short *a_ymax, short *a_ylen)
{
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_GRAF   yLOG_value   ("search"    , rc);
   if (rc < 0) {
      DEBUG_GRAF   yLOG_note    ("deal with a missing element");
      if (a_type   != NULL)  *a_type   = '-';
      if (a_anchor != NULL)  *a_anchor = '-';
      if (a_magn   != NULL)  *a_magn   = 0.00;
      if (a_xmin   != NULL)  *a_xmin   = 0;
      if (a_xmax   != NULL)  *a_xmax   = 0;
      if (a_xlen   != NULL)  *a_xlen   = 0;
      if (a_ymin   != NULL)  *a_ymin   = 0;
      if (a_ymax   != NULL)  *a_ymax   = 0;
      if (a_ylen   != NULL)  *a_ylen   = 0;
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_GRAF   yLOG_note    ("save values for good entry");
   if (a_type   != NULL)  *a_type   = p->type;
   if (a_anchor != NULL)  *a_anchor = p->anchor;
   if (a_magn   != NULL)  *a_magn   = p->magn;
   if (a_xmin   != NULL)  *a_xmin   = p->xmin;
   if (a_xmax   != NULL)  *a_xmax   = p->xmin + p->xlen;
   if (a_xlen   != NULL)  *a_xlen   = p->xlen;
   if (a_ymin   != NULL)  *a_ymin   = p->ymin;
   if (a_ymax   != NULL)  *a_ymax   = p->ymin + p->ylen;
   if (a_ylen   != NULL)  *a_ylen   = p->ylen;
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_showing           (char a_part)
{
   char        rc          =    0;
   char        x_on        =  '-';
   rc = yVIEW_size   (a_part, &x_on, NULL, NULL, NULL, NULL);
   if (rc < 0)       return -1;
   if (x_on == 'y')  return  1;
   return 0;
}

char
yVIEW_anchor            (char a_part)
{
   char        rc          =    0;
   char        x_anchor    =  '-';
   rc = yVIEW_bounds (a_part, NULL, &x_anchor, NULL, NULL, NULL, NULL, NULL, NULL, NULL);
   if (rc < 0)       return -1;
   return x_anchor;
}



/*====================------------------------------------====================*/
/*===----                       overall sizing                         ----===*/
/*====================------------------------------------====================*/
static void  o___SIZING__________o () { return; }

char
yview_update            (void)
{
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   yview_clear ();
   yview_horz  (myVIEW.orig_wide, myVIEW.alt_wide);
   yview_vert  (myVIEW.orig_tall);
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_resize            (short a_wide, short a_tall, short a_alt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   DEBUG_GRAF   yLOG_value   ("a_wide"    , a_wide);
   DEBUG_GRAF   yLOG_value   ("a_tall"    , a_tall);
   DEBUG_GRAF   yLOG_value   ("a_alt"     , a_alt);
   /*---(update globals)-----------------*/
   if (a_wide > 10)   myVIEW.orig_wide = a_wide;
   if (a_tall > 10)   myVIEW.orig_tall = a_tall;
   if (a_alt  > 10)   myVIEW.alt_wide  = a_alt;
   yview_update ();
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



