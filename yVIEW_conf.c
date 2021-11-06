/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"

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

char
yVIEW_simple            (cchar a_part, cchar a_color, void *a_drawer)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        n           =    0;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(identify part)------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_char    ("a_part"    , a_part);                              <* 
    *> n = yvikeys_view__abbr (a_part);                                               <* 
    *> DEBUG_PROG   yLOG_value   ("n"         , n);                                   <* 
    *> if (n < 0) {                                                                   <* 
    *>    DEBUG_PROG   yLOG_note    ("deal with a missing element");                  <* 
    *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <* 
    *> DEBUG_PROG   yLOG_info    ("name"      , s_parts [n].name);                    <* 
    *> DEBUG_PROG   yLOG_char    ("own"       , s_parts [n].own);                     <* 
    *> if (strchr (OWN_SIMPLE, s_parts [n].own) == NULL) {                            <* 
    *>    DEBUG_PROG   yLOG_note    ("can not use function on this element");         <* 
    *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <* 
    *> /+---(save color)---------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_color"   , a_color);                             <* 
    *> if (a_color >= 0 && a_color < 50)  s_parts [n].color  = a_color;               <* 
    *> else                               s_parts [n].color  = 0;                     <* 
    *> DEBUG_PROG   yLOG_value   ("color"     , s_parts [n].color);                   <* 
    *> /+---(save drawer)--------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_point   ("a_drawer"  , a_drawer);                            <* 
    *> if (a_drawer != NULL)     s_parts [n].drawer = a_drawer;                       <* 
    *> DEBUG_PROG   yLOG_point   ("drawer"    , s_parts [n].drawer);                  <* 
    *> /+---(finish up)----------------------+/                                       <* 
    *> s_parts [n].mgmt   = YVIKEYS_AUTO;                                             <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return 0;                                                                      <*/
}

char
yVIEW_basic             (cchar a_part, cchar a_type, cchar a_anchor, cchar a_color, void *a_drawer)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        n           =    0;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(identify part)------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_char    ("a_part"    , a_part);                              <* 
    *> n = yvikeys_view__abbr (a_part);                                               <* 
    *> DEBUG_PROG   yLOG_value   ("n"         , n);                                   <* 
    *> if (n < 0) {                                                                   <* 
    *>    DEBUG_PROG   yLOG_note    ("deal with a missing element");                  <* 
    *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <* 
    *> DEBUG_PROG   yLOG_info    ("name"      , s_parts [n].name);                    <* 
    *> DEBUG_PROG   yLOG_char    ("own"       , s_parts [n].own);                     <* 
    *> if (strchr (OWN_MODERATE, s_parts [n].own) == NULL) {                          <* 
    *>    DEBUG_PROG   yLOG_note    ("can not use function on this element");         <* 
    *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <* 
    *> /+---(perspective)--------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_char    ("a_type"    , a_type);                              <* 
    *> if      (a_type == '-')            ;                                           <* 
    *> else if (a_type == YVIKEYS_DEPTH)   s_parts [n].type = YVIKEYS_DEPTH;          <* 
    *> else                                s_parts [n].type = YVIKEYS_FLAT;           <* 
    *> DEBUG_PROG   yLOG_char    ("type"      , s_parts [n].type);                    <* 
    *> /+---(anchor)-------------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_anchor"  , a_anchor);                            <* 
    *> if      (a_anchor <  0  )  s_parts [n].anchor = YVIKEYS_MIDCEN;                <* 
    *> else if (a_anchor >= 10 )  s_parts [n].anchor = YVIKEYS_MIDCEN;                <* 
    *> else                       s_parts [n].anchor = a_anchor;                      <* 
    *> DEBUG_PROG   yLOG_value   ("anchor"    , s_parts [n].anchor);                  <* 
    *> yvikeys_sizes_anchor (n);                                                      <* 
    *> /+---(save color)---------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_color"   , a_color);                             <* 
    *> if (a_color >= 0 && a_color < 50)  s_parts [n].color  = a_color;               <* 
    *> else                               s_parts [n].color  = 0;                     <* 
    *> DEBUG_PROG   yLOG_value   ("color"     , s_parts [n].color);                   <* 
    *> /+---(save drawer)--------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_point   ("a_drawer"  , a_drawer);                            <* 
    *> if (a_drawer != NULL)     s_parts [n].drawer = a_drawer;                       <* 
    *> DEBUG_PROG   yLOG_point   ("drawer"    , s_parts [n].drawer);                  <* 
    *> /+---(finish up)----------------------+/                                       <* 
    *> s_parts [n].mgmt   = YVIKEYS_AUTO;                                             <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return 0;                                                                      <*/
}



char
yVIEW_setup             (cchar a_part, cchar a_type, cchar a_anchor, cint a_xmin, cint a_xlen, cint a_ymin, cint a_ylen, cint a_zmin, cint a_zlen, cchar a_color, void *a_drawer)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                       <* 
    *> char        n           =    0;                                                <* 
    *> /+---(header)-------------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_enter   (__FUNCTION__);                                      <* 
    *> /+---(identify part)------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_char    ("a_part"    , a_part);                              <* 
    *> n = yvikeys_view__abbr (a_part);                                               <* 
    *> DEBUG_PROG   yLOG_value   ("n"         , n);                                   <* 
    *> if (n < 0) {                                                                   <* 
    *>    DEBUG_PROG   yLOG_note    ("deal with a missing element");                  <* 
    *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <* 
    *> DEBUG_PROG   yLOG_info    ("name"      , s_parts [n].name);                    <* 
    *> DEBUG_PROG   yLOG_char    ("own"       , s_parts [n].own);                     <* 
    *> if (strchr (OWN_COMPLEX, s_parts [n].own) == NULL) {                           <* 
    *>    DEBUG_PROG   yLOG_note    ("can not use function on this element");         <* 
    *>    DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                   <* 
    *>    return n;                                                                   <* 
    *> }                                                                              <* 
    *> /+---(perspective)--------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_char    ("a_type"    , a_type);                              <* 
    *> if      (a_type == '-')            ;                                           <* 
    *> else if (a_type == YVIKEYS_DEPTH)   s_parts [n].type = YVIKEYS_DEPTH;          <* 
    *> else                                s_parts [n].type = YVIKEYS_FLAT;           <* 
    *> DEBUG_PROG   yLOG_char    ("type"      , s_parts [n].type);                    <* 
    *> /+---(anchor)-------------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_anchor"  , a_anchor);                            <* 
    *> if      (a_anchor <  0  )  s_parts [n].anchor = YVIKEYS_MIDCEN;                <* 
    *> else if (a_anchor >= 10 )  s_parts [n].anchor = YVIKEYS_MIDCEN;                <* 
    *> else                       s_parts [n].anchor = a_anchor;                      <* 
    *> DEBUG_PROG   yLOG_value   ("anchor"    , s_parts [n].anchor);                  <* 
    *> /+---(save x-coords)------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_xmin"    , a_xmin);                              <* 
    *> DEBUG_PROG   yLOG_value   ("a_xlen"    , a_xlen);                              <* 
    *> if (a_xlen != 0) {                                                             <* 
    *>    s_parts [n].xmin  = a_xmin;                                                 <* 
    *>    if      (a_xlen == -1)  s_parts [n].xlen  = a_xmin - s_parts [n].wide;      <* 
    *>    else if (a_xlen ==  1)  s_parts [n].xlen  = a_xmin + s_parts [n].wide;      <* 
    *>    else                    s_parts [n].xlen  = a_xlen;                         <* 
    *> }                                                                              <* 
    *> DEBUG_PROG   yLOG_value   ("xmin"      , s_parts [n].xmin);                    <* 
    *> DEBUG_PROG   yLOG_value   ("xlen"      , s_parts [n].xlen);                    <* 
    *> /+---(save y-coords)------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_ymin"    , a_ymin);                              <* 
    *> DEBUG_PROG   yLOG_value   ("a_ylen"    , a_ylen);                              <* 
    *> if (a_ylen != 0) {                                                             <* 
    *>    s_parts [n].ymin  = a_ymin;                                                 <* 
    *>    if      (a_ylen == -1)  s_parts [n].ylen  = a_ymin - s_parts [n].tall;      <* 
    *>    else if (a_ylen ==  1)  s_parts [n].ylen  = a_ymin + s_parts [n].tall;      <* 
    *>    else                    s_parts [n].ylen  = a_ylen;                         <* 
    *> }                                                                              <* 
    *> DEBUG_PROG   yLOG_value   ("ymin"      , s_parts [n].ymin);                    <* 
    *> DEBUG_PROG   yLOG_value   ("ylen"      , s_parts [n].ylen);                    <* 
    *> /+---(save z-coords)------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_zmin"    , a_zmin);                              <* 
    *> DEBUG_PROG   yLOG_value   ("a_zlen"    , a_zlen);                              <* 
    *> if (a_ylen != 0) {                                                             <* 
    *>    if (a_zmin == 0 && a_zlen == 0) {                                           <* 
    *>       s_parts [n].zmin  = -500;                                                <* 
    *>       s_parts [n].zlen  = 1000;                                                <* 
    *>    } else {                                                                    <* 
    *>       s_parts [n].zmin  = a_zmin;                                              <* 
    *>       s_parts [n].zlen  = a_zlen;                                              <* 
    *>    }                                                                           <* 
    *> }                                                                              <* 
    *> DEBUG_PROG   yLOG_value   ("zmin"      , s_parts [n].zmin);                    <* 
    *> DEBUG_PROG   yLOG_value   ("zlen"      , s_parts [n].zlen);                    <* 
    *> /+---(save color)---------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_value   ("a_color"   , a_color);                             <* 
    *> if (a_color >= 0 && a_color < 50)  s_parts [n].color  = a_color;               <* 
    *> else                               s_parts [n].color  = 0;                     <* 
    *> DEBUG_PROG   yLOG_value   ("color"     , s_parts [n].color);                   <* 
    *> /+---(save drawer)--------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_point   ("a_drawer"  , a_drawer);                            <* 
    *> if (a_drawer != NULL)              s_parts [n].drawer = a_drawer;              <* 
    *> DEBUG_PROG   yLOG_point   ("drawer"    , s_parts [n].drawer);                  <* 
    *> /+---(finish up)----------------------+/                                       <* 
    *> s_parts [n].mgmt   = YVIKEYS_CUSTOM;                                           <* 
    *> /+---(complete)-----------------------+/                                       <* 
    *> DEBUG_PROG   yLOG_exit    (__FUNCTION__);                                      <* 
    *> return 0;                                                                      <*/
}
