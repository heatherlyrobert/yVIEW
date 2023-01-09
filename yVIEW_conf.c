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
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(identify part)------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, &a);
   DEBUG_YVIEW   yLOG_point   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("deal with a missing element");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_info    ("name"      , p->name);
   DEBUG_YVIEW   yLOG_char    ("p->defs"   , p->defs);
   --rce;  if (p->defs == 0 || strchr ("wtB", p->defs) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check default control)----------*/
   --rce;  if (p->defs == 'w' && a_tall != 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (p->defs == 't' && a_wide != 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(size)---------------------------*/
   DEBUG_YVIEW   yLOG_complex ("before"    , "%4dW, %4dT", p->def_wide, p->def_tall);
   if (a_wide > 0)  p->def_wide = a_wide;
   if (a_tall > 0)  p->def_tall = a_tall;
   DEBUG_YVIEW   yLOG_complex ("after"     , "%4dW, %4dT", p->def_wide, p->def_tall);
   if (a_part == YVIEW_ALT)  myVIEW.alt_wide = p->def_wide;
   /*---(check alt)----------------------*/
   DEBUG_YVIEW   yLOG_point   ("a"         , a);
   if (a != NULL) {
      DEBUG_YVIEW   yLOG_char    ("a->defs"   , a->defs);
      DEBUG_YVIEW   yLOG_info    ("name"      , a->name);
      DEBUG_YVIEW   yLOG_complex ("before"    , "%4dW, %4dT", a->def_wide, a->def_tall);
      if (a_wide > 0 && (strchr ("Bw", a->defs) != NULL))  a->def_wide = a_wide;
      if (a_tall > 0 && (strchr ("Bt", a->defs) != NULL))  a->def_tall = a_tall;
      DEBUG_YVIEW   yLOG_complex ("after"     , "%4dW, %4dT", a->def_wide, a->def_tall);
   }
   /*---(recalc)-------------------------*/
   yview_update ();
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      view configuration                      ----===*/
/*====================------------------------------------====================*/
static void      o___CONFIG__________________o (void) {;}

char
yview__conf_type        (tPARTS *p, char a_type)
{
   DEBUG_YVIEW   yLOG_char    ("a_type"    , a_type);
   if      (a_type == YVIEW_LEAVE)     return 0;
   else if (a_type == YVIEW_DEPTH)     p->type = YVIEW_DEPTH;
   else if (a_type == YVIEW_FLATISH)   p->type = YVIEW_FLATISH;
   else                                p->type = YVIEW_FLAT;
   DEBUG_YVIEW   yLOG_char    ("type"      , p->type);
   return 0;
}

char
yview__conf_anchor      (tPARTS *p, char a_anchor)
{
   DEBUG_YVIEW   yLOG_value   ("a_anchor"  , a_anchor);
   if (p->anchor == 0) {
      DEBUG_YVIEW   yLOG_note    ("part has a dependent anchor");
      return 0;
   }
   if      (a_anchor == YVIEW_LEAVE)   return 0;
   else if (a_anchor <  '0' )         a_anchor = YVIEW_MIDCEN;
   else if (a_anchor >  '9' )         a_anchor = YVIEW_MIDCEN;
   DEBUG_YVIEW   yLOG_value   ("a_anchor"  , a_anchor);
   yview_set_anchor (p->abbr, a_anchor);
   return 0;
}

char
yview__conf_color       (tPARTS *p, char a_major, char a_minor)
{
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(args)---------------------------*/
   DEBUG_YVIEW   yLOG_spoint  (p);
   --rce;  if (p == NULL) {
      DEBUG_YVIEW   yLOG_snote   ("part is null");
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_snote   (p->name);
   DEBUG_YVIEW   yLOG_sint    (p->cmajor);
   --rce;  if (p->cmajor == YVIEW_LEAVE) {
      DEBUG_YVIEW   yLOG_snote   ("color must be clear");
      DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   /*---(major color)--------------------*/
   DEBUG_YVIEW   yLOG_sint    (a_major);
   if (a_major == YVIEW_LEAVE) {
      DEBUG_YVIEW   yLOG_snote   ("color change not requested");
      DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
      return 0;
   }
   if      (a_major <   0)             p->cmajor = 0;
   else if (a_major >  70)             p->cmajor = 0;
   else if (a_major % 10 != 0)         p->cmajor = 0;
   else                                p->cmajor = a_major;
   DEBUG_YVIEW   yLOG_sint    (p->cmajor);
   /*---(minor color)--------------------*/
   DEBUG_YVIEW   yLOG_sint    (a_minor);
   if      (a_minor <   0)             p->cminor = 0;
   else if (a_minor >   9)             p->cminor = 0;
   else                                p->cminor = a_minor;
   DEBUG_YVIEW   yLOG_sint    (p->cminor);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview__conf_drawer      (tPARTS *p, void *a_drawer)
{
   DEBUG_YVIEW   yLOG_point   ("a_drawer"  , a_drawer);
   switch (p->abbr) {
   case YVIEW_WINDOW  :
      DEBUG_YVIEW   yLOG_note    ("part can not have drawer");
      return 0;
      break;
   }
   if (a_drawer != NULL)    p->drawer = a_drawer;
   DEBUG_YVIEW   yLOG_point   ("drawer"    , p->drawer);
   return 0;
}

char
yview_conf_text         (char a_part, char *a_text)
{
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_point   ("a_text"    , a_text);
   if (a_text == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   strlcpy (p->text, a_text, LEN_RECD);
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview__system           (char a_part, void *a_drawer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(identify part)------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   --rce;  if (a_part == 0 || strchr ("FHM", a_part) == NULL) {
      DEBUG_YVIEW   yLOG_note    ("only floats can be configured this way");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_info    ("name"      , p->name);
   DEBUG_YVIEW   yLOG_char    ("own"       , p->own);
   /*---(update)-------------------------*/
   yview__conf_drawer (p, a_drawer);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yVIEW_menus    (void *a_drawer) { return yview__system (YVIEW_MENUS   , a_drawer); }

char
yVIEW_simple            (char a_part, char a_major, char a_minor, void *a_drawer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(identify part)------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   /*> --rce;  if (a_part == 0 || strchr ("FHM", a_part) != NULL) {                   <* 
    *>    DEBUG_YVIEW   yLOG_note    ("floats can not be configured this way");       <* 
    *>    DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_info    ("name"      , p->name);
   DEBUG_YVIEW   yLOG_char    ("own"       , p->own);
   /*---(update)-------------------------*/
   yview__conf_color  (p, a_major, a_minor);
   yview__conf_drawer (p, a_drawer);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_full              (char a_part, char a_type, char a_anchor, char a_major, char a_minor, void *a_drawer)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(identify part)------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   --rce;  if (a_part == 0 || strchr ("FHM", a_part) != NULL) {
      DEBUG_YVIEW   yLOG_note    ("floats can not be configured this way");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_info    ("name"      , p->name);
   DEBUG_YVIEW   yLOG_char    ("own"       , p->own);
   /*---(update)-------------------------*/
   yview__conf_type   (p, a_type);
   yview__conf_anchor (p, a_anchor);
   yview__conf_color  (p, a_major, a_minor);
   yview__conf_drawer (p, a_drawer);
   /*---(finish up)----------------------*/
   yview_update ();
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
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
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("deal with a missing element");
      if (a_on   != NULL)  *a_on    = '-';
      if (a_left != NULL)  *a_left  = 0;
      if (a_bott != NULL)  *a_bott  = 0;
      if (a_wide != NULL)  *a_wide  = 0;
      if (a_tall != NULL)  *a_tall  = 0;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YVIEW   yLOG_note    ("save values for good entry");
   if (a_on   != NULL)  *a_on    = p->on;
   if (a_left != NULL)  *a_left  = p->left;
   if (a_bott != NULL)  *a_bott  = p->bott;
   if (a_wide != NULL)  *a_wide  = p->wide;
   if (a_tall != NULL)  *a_tall  = p->tall;
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_curses            (char a_part, char *r_name, char *r_on, char *r_source, char *r_text, char *r_orient, short *r_left, short *r_wide, short *r_bott, short *r_tall)
{
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("deal with a missing element");
      if (r_name   != NULL)  strlcpy (r_name, "", LEN_LABEL);
      if (r_on     != NULL)  *r_on     = '-';
      if (r_source != NULL)  *r_source = NULL;
      if (r_text   != NULL)  strlcpy (r_text, "", LEN_RECD);
      if (r_orient != NULL)  *r_orient = '-';
      if (r_left   != NULL)  *r_left   = 0;
      if (r_bott   != NULL)  *r_bott   = 0;
      if (r_wide   != NULL)  *r_wide   = 0;
      if (r_tall   != NULL)  *r_tall   = 0;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YVIEW   yLOG_note    ("save values for good entry");
   if (r_name   != NULL)  strlcpy (r_name, p->name, LEN_LABEL);
   if (r_on     != NULL)  *r_on     = p->on;
   if (r_source != NULL)  *r_source = p->source;
   if (r_text   != NULL)  strlcpy (r_text, p->text, LEN_RECD);
   if (r_orient != NULL)  *r_orient = p->orient;
   if (r_left   != NULL)  *r_left   = p->left;
   if (r_bott   != NULL)  *r_bott   = p->bott;
   if (r_wide   != NULL)  *r_wide   = p->wide;
   if (r_tall   != NULL)  *r_tall   = p->tall;
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_bounds            (char a_part, char *a_type, char *a_anchor, short *a_xmin, short *a_xmax, short *a_xlen, short *a_ymin, short *a_ymax, short *a_ylen)
{
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("deal with a missing element");
      if (a_type   != NULL)  *a_type   = '-';
      if (a_anchor != NULL)  *a_anchor = '-';
      if (a_xmin   != NULL)  *a_xmin   = 0;
      if (a_xmax   != NULL)  *a_xmax   = 0;
      if (a_xlen   != NULL)  *a_xlen   = 0;
      if (a_ymin   != NULL)  *a_ymin   = 0;
      if (a_ymax   != NULL)  *a_ymax   = 0;
      if (a_ylen   != NULL)  *a_ylen   = 0;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YVIEW   yLOG_note    ("save values for good entry");
   if (a_type   != NULL)  *a_type   = p->type;
   if (a_anchor != NULL)  *a_anchor = p->anchor;
   if (a_xmin   != NULL)  *a_xmin   = p->xmin;
   if (a_xmax   != NULL)  *a_xmax   = p->xmin + p->xlen;
   if (a_xlen   != NULL)  *a_xlen   = p->xlen;
   if (a_ymin   != NULL)  *a_ymin   = p->ymin;
   if (a_ymax   != NULL)  *a_ymax   = p->ymin + p->ylen;
   if (a_ylen   != NULL)  *a_ylen   = p->ylen;
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_opengl            (char a_part, char *r_name, char *r_on, char *r_source, char *r_text, char *a_type, char *a_anchor, short *a_xmin, short *a_xmax, short *a_xlen, short *a_ymin, short *a_ymax, short *a_ylen)
{
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   rc = yview_by_abbr (a_part, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("deal with a missing element");
      if (r_name   != NULL)  strlcpy (r_name, "", LEN_LABEL);
      if (r_on     != NULL)  *r_on     = '-';
      if (r_source != NULL)  *r_source = NULL;
      if (r_text   != NULL)  strlcpy (r_text, "", LEN_RECD);
      if (a_type   != NULL)  *a_type   = '-';
      if (a_anchor != NULL)  *a_anchor = '-';
      if (a_xmin   != NULL)  *a_xmin   = 0;
      if (a_xmax   != NULL)  *a_xmax   = 0;
      if (a_xlen   != NULL)  *a_xlen   = 0;
      if (a_ymin   != NULL)  *a_ymin   = 0;
      if (a_ymax   != NULL)  *a_ymax   = 0;
      if (a_ylen   != NULL)  *a_ylen   = 0;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   DEBUG_YVIEW   yLOG_note    ("save values for good entry");
   DEBUG_GRAF   yLOG_complex (p->name, "%c on %c, xmin %4d, xlen %4d, ymin %4d, ylen %4d", a_part, p->on, p->xmin, p->xlen, p->ymin, p->ylen);
   if (r_name   != NULL)  strlcpy (r_name, p->name, LEN_LABEL);
   if (r_on     != NULL)  *r_on     = p->on;
   if (r_source != NULL)  *r_source = p->source;
   if (r_text   != NULL)  strlcpy (r_text, p->text, LEN_RECD);
   if (a_type   != NULL)  *a_type   = p->type;
   if (a_anchor != NULL)  *a_anchor = p->anchor;
   if (a_xmin   != NULL)  *a_xmin   = p->xmin;
   if (a_xmax   != NULL)  *a_xmax   = p->xmin + p->xlen;
   if (a_xlen   != NULL)  *a_xlen   = p->xlen;
   if (a_ymin   != NULL)  *a_ymin   = p->ymin;
   if (a_ymax   != NULL)  *a_ymax   = p->ymin + p->ylen;
   if (a_ylen   != NULL)  *a_ylen   = p->ylen;
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
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
   rc = yVIEW_bounds (a_part, NULL, &x_anchor, NULL, NULL, NULL, NULL, NULL, NULL);
   if (rc < 0)       return -1;
   return x_anchor;
}



/*====================------------------------------------====================*/
/*===----                     re-anchoring floats                      ----===*/
/*====================------------------------------------====================*/
static void  o___FLOATS__________o () { return; }


char
yview_set_anchor        (char a_abbr, char a_anchor)
{
   char        rce         =  -10;
   char        rc          =    0;
   tPARTS     *p           = NULL;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_abbr"    , a_abbr);
   DEBUG_YVIEW   yLOG_char    ("a_anchor"  , a_anchor);
   --rce;  if (a_anchor == 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  switch (a_abbr) {
   case YVIEW_FLOAT   :
      DEBUG_YVIEW   yLOG_info    ("float"     , YVIEW_LOC_FLOAT);
      if (strchr (YVIEW_LOC_FLOAT, a_anchor) == NULL) {
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      myVIEW.loc_float = a_anchor;
      break;
   case YVIEW_HISTORY :
      DEBUG_YVIEW   yLOG_info    ("history"   , YVIEW_LOC_HIST);
      if (strchr (YVIEW_LOC_HIST , a_anchor) == NULL) {
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      switch (a_anchor) {
      case 'f' : a_anchor = YVIEW_ALLFUL;   break;
      case 'l' : a_anchor = YVIEW_ALLLEF;   break;
      case 'c' : a_anchor = YVIEW_ALLCEN;   break;
      case 'r' : a_anchor = YVIEW_ALLRIG;   break;
      }
      break;
   case YVIEW_MENUS   :
      DEBUG_YVIEW   yLOG_info    ("menus"     , YVIEW_LOC_MENU);
      if (strchr (YVIEW_LOC_MENU , a_anchor) == NULL) {
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      myVIEW.loc_menu  = a_anchor;
      break;
   default    :
      DEBUG_YVIEW   yLOG_info    ("normal"    , YVIEW_LOC_NORM);
      if (strchr (YVIEW_LOC_NORM , a_anchor) == NULL) {
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      myVIEW.loc_hist  = a_anchor;
      break;
   }
   rc = yview_by_abbr (a_abbr, &p, NULL);
   DEBUG_YVIEW   yLOG_value   ("search"    , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   p->anchor = a_anchor;
   yview_update ();
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yVIEW_loc_float    (char a_loc) { return yview_set_anchor (YVIEW_FLOAT  , a_loc); }
char yVIEW_loc_history  (char a_loc) { return yview_set_anchor (YVIEW_HISTORY, a_loc); }
char yVIEW_loc_menu     (char a_loc) { return yview_set_anchor (YVIEW_MENUS  , a_loc); }



/*====================------------------------------------====================*/
/*===----                       overall sizing                         ----===*/
/*====================------------------------------------====================*/
static void  o___SIZING__________o () { return; }

char
yview_update            (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         x_alt       =    0;
   tPARTS     *a           = NULL;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   yVIEW_debug_list ();
   yview_clear ();
   yVIEW_debug_list ();
   yview_by_abbr (YVIEW_ALT, &a, NULL);
   if (a->on != 'y')  x_alt = 0;
   else               x_alt = a->def_wide;
   yview_horz  (myVIEW.orig_wide, x_alt);
   yview_vert  (myVIEW.orig_tall);
   yVIHUB_yMAP_refresh_disponly ();
   yVIEW_debug_list ();
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_resize            (short a_wide, short a_tall, short a_alt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_value   ("a_wide"    , a_wide);
   DEBUG_YVIEW   yLOG_value   ("a_tall"    , a_tall);
   DEBUG_YVIEW   yLOG_value   ("a_alt"     , a_alt);
   /*---(update globals)-----------------*/
   if (a_wide > 10)   myVIEW.orig_wide = a_wide;
   if (a_tall > 10)   myVIEW.orig_tall = a_tall;
   if (a_alt  > 10)   myVIEW.alt_wide  = a_alt;
   DEBUG_YVIEW   yLOG_complex ("new"       , "%4dw, %4dt, %4da", myVIEW.orig_wide, myVIEW.orig_tall, myVIEW.alt_wide);
   yview_update ();
   yview_note_update ();
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}



