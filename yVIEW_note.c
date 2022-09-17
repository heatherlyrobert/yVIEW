/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"


/*
 * connector types
 *       œÄÄÄÄÄÄÇ            œ       
 *              Å            Å         
 *     œ       VÅ      œÄÄÄÇ ÑÄÄÇ       opengl only
 *     Å        Å          Å    Åv        D = direct
 *     Å  H   ÉÄàÄÇ       hÅ  ÉÄàÄÇ
 *     ÑÄÄÄÄÄÄÜ   Å        ÑÄÄÜ   Å
 *            ÑÄÄÄÖ           ÑÄÄÄÖ
 *  œ
 *  Å   œÄœ
 *  œ
 *
 *
 *  clear types
 *                                 œ          œ    
 *    ÉÄÄÄÄÄÄÄÄÇ  É≤≤≤≤≤≤≤≤Ç       Å          å        
 *    Å  text  Å  å  text  å   ëÄÄÄàÄÄÄê  ë≤≤≤à≤≤≤ê     œÄÄÜexplain
 *    Å        Å  å        å    explain    explain
 *    ÑÄÄÄÄÄÄÄÄÖ  Ñ≤≤≤≤≤≤≤≤Ö                            õ≤≤Üexplain
 *
 *                                 œÄÄÄÄÄÄÄÄÄÄÇ      
 *   Å                                        Å                      
 *   Å  ÉÄÄÄÄÄÄÄÄÇ      ÉÄÄÄÄÄÄÄÄÇ      ÉÄÄÄÄÄàÄÄÄÄÄÇ      ÉÄÄÄÄÄÄÄÄÇ
 *   ÑÄÄÜ  text  Å      Å  text  Å      Å text      Å      Å  text  Å
 *      Å        Å   ÉÄÄÜ        Å      Å           Å      Å        Å
 *      ÑÄÄÄÄÄÄÄÄÖ   Å  ÑÄÄÄÄÄÄÄÄÖ      ÑÄÄÄÄÄÄÄÄÄÄÄÖ      ÑÄÄÄÄÄÄÄÄÖ
 *                   Å
 *                                 œÄÄÄÄÄÄÄÄÄÄÇ      
 *   Å                                        Å                      
 *   Å  ÉÄÄÄÄÄÄÄÄÇ      ÉÄÄÄÄÄÄÄÄÇ           ÄàÄ           ÉÄÄÄÄÄÄÄÄÇ
 *   ÑÄÄÜ  text  Å      Å  text  Å  ÄÄÜ¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨     Å  text  Å
 *      Å        Å   ÉÄÄÜ        Å    Å¨¨¨¨¨¨¨¨¨¨¨¨¨¨¨     Å        Å
 *      ÑÄÄÄÄÄÄÄÄÖ   Å  ÑÄÄÄÄÄÄÄÄÖ                         ÑÄÄÄÄÄÄÄÄÖ
 *                   Å
 *
 *
 * target flows
 *
 *                        8ÄÄÄÄÇ  ÉÄÄÄÄ1
 *                   7         Å  Å         2
 *                   Å         Å  Å         Å
 *                   Å      ÉÄÄàÄÄàÄÄÇ      Å
 *                   ÑÄÄÄÄÄÄÜ  text  áÄÄÄÄÄÄÖ
 *                   ÉÄÄÄÄÄÄÜ        áÄÄÄÄÄÄÇ
 *                   Å      ÑÄÄâÄÄâÄÄÖ      Å
 *                   Å         Å  Å         Å
 *                   6         Å  Å         3
 *                        5ÄÄÄÄÖ  ÑÄÄÄÄ4
 *                      
 *
 *
 *
 *   standard screen grid
 *      normal  1  -  5  -  9       9 for normal use
 *      fine    Z - A * a - z      53 for bigger screens
 *
 *         1      2     3      4     5     6      7     8      9
 *         ZYXWVUTSRQPONMLKJIHGFEDCBA-abcdefghijklmnopqrstuvwxyz
 *       1z             ∑            ∑            ∑             z1
 *  tu v wx   ¨¨¨          ¨¨¨¨¨     ∑                          ≤ 
 *       2s             ∑  ¨¨¨¨¨     ∑            ∑             s2
 *  mn o pq                          ∑                          ≤ 
 *       3m ∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑∑∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑ m3
 *  gh i jk                      ¨¨¨¨¨¨¨¨                       ≤ 
 *       4f             ∑        ¨¨¨¨¨¨¨¨         ∑             f4
 *  ab c de                          ∑                          ≤ 
 *       5*∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑∑*5
 *        ≤                          ∑                          ≤ 
 *       6F             ∑            ∑            ∑             F6
 *        ≤                          ∑                          ≤ 
*       7M ∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑∑∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑  ∑ M7
*        ≤                          ∑                          ≤ 
*       8S             ∑            ∑            ∑             S8
*        ≤                          ∑                          ≤ 
*       9Z             ∑            ∑            ∑             Z9
*         ZYXWVUTSRQPONMLKJIHGFEDCBA-abcdefghijklmnopqrstuvwxyz
*         1      2     3      4     5     6      7     8      9
*
*   sizes
*     . bullet      1  x   2
*     , word        1  x   9
*     ; call-out    1  x  14
*     : long call   1  x  25
*
*     - small       2  x  14
*     ) title       2  x  25
*
*     ! warning     3    
*     ~ squarish    3    
*     = normal      3  x  25
*
*     + large       4  x  40
*
*   colors
*     ) title       white letters on magenta
*     ! warning     white letters on red
*     current of rest dark letters on light background
*     all others light letters on dark background
*     clear current    Ä Å
*     clear previous   ≤ å
*
*   targeting
*     ¥ grid        1 - 9 or Z-A*a-z
*     Ã radial      deg/dist from center
*     ° current     current xy in yVIKEYS 
*
*
*/

tNOTE  g_notes [MAX_NOTES];
char   g_nnote     = 0;

#define     DEG2RAD  (3.1415927 / 180.0)
#define     RAD2DEG  (180.0 / 3.1415927)

static char  *s_size       = ".,:;-)!~=+";
static char  *s_norm       = "123456789";
static char  *s_fine       = "ZYXWVUTSRQPONMLKJIHGFEDCBA*abcdefghijklmnopqrstuvwxyz";
static char  *s_targ       = "‘’◊÷àâÜá";
static char   s_noting     = 'y';
static char   s_part       = YVIEW_MAIN;



/*====================------------------------------------====================*/
/*===----                       little supporters                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
yview_note__untarget    (char n)
{
   /*---(target)-------------------------*/
   g_notes [n].s     = YVIEW_MAIN;
   g_notes [n].c     = '-';
   g_notes [n].xt    = 0;
   g_notes [n].yt    = 0;
   g_notes [n].xb    = 0;
   g_notes [n].yb    = 0;
   g_notes [n].xe    = 0;
   g_notes [n].ye    = 0;
   /*---(complete)-----------------------*/
   return 0;
}

char
yview_note__wipe        (char a_init, char n)
{
   /*---(text first)---------------------*/
   if (a_init != 'y' && g_notes [n].xr != '0' && g_notes [n].text != NULL) free (g_notes [n].text);
   g_notes [n].text = NULL;
   /*---(master)-------------------------*/
   g_notes [n].xr    = '0';
   g_notes [n].yr    = '0';
   g_notes [n].size  = '=';
   /*---(position)-----------------------*/
   g_notes [n].x     = 0;
   g_notes [n].y     = 0;
   g_notes [n].w     = 0;
   g_notes [n].h     = 0;
   /*---(target)-------------------------*/
   yview_note__untarget (n);
   /*---(complete)-----------------------*/
   return 0;
}

char
yview_note__find        (char xr, char yr)
{
   int         i           =    0;
   for (i = 0; i < g_nnote; ++i) {
      if (g_notes [i].xr != xr)  continue;
      if (g_notes [i].yr != yr)  continue;
      return i;
   }
   return -1;
}

char yVIEW_note_showing      (void) { if (s_noting == 'y') return 1;  return 0; }



/*====================------------------------------------====================*/
/*===----                      changing order                          ----===*/
/*====================------------------------------------====================*/
static void  o___ORDERING________o () { return; }

char
yview_note__remove      (char n)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (n < 0 || n > MAX_NOTES)  return rce;
   --rce;  if (n >= g_nnote)            return rce;
   if (g_notes [n].text != NULL)  free (g_notes [n].text);
   for (i = n; i < g_nnote; ++i) {
      /*---(master)---------*/
      g_notes [i].xr   = g_notes [i + 1].xr;
      g_notes [i].yr   = g_notes [i + 1].yr;
      g_notes [i].size = g_notes [i + 1].size;
      /*---(position)-------*/
      g_notes [i].x    = g_notes [i + 1].x;
      g_notes [i].y    = g_notes [i + 1].y;
      g_notes [i].w    = g_notes [i + 1].w;
      g_notes [i].h    = g_notes [i + 1].h;
      g_notes [i].text = g_notes [i + 1].text;
      /*---(target)---------*/
      g_notes [i].s    = g_notes [i + 1].s;
      g_notes [i].c    = g_notes [i + 1].c;
      g_notes [i].xt   = g_notes [i + 1].xt;
      g_notes [i].yt   = g_notes [i + 1].yt;
      g_notes [i].xb   = g_notes [i + 1].xb;
      g_notes [i].yb   = g_notes [i + 1].yb;
      g_notes [i].xe   = g_notes [i + 1].xe;
      g_notes [i].ye   = g_notes [i + 1].ye;
      /*---(done)-----------*/
      if (i + 1 < MAX_NOTES)  yview_note__wipe ('y', i + 1);
   }
   --g_nnote;
   return 0;
}

char
yview_note__totop       (char n)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (n < 0 || n > MAX_NOTES)  return rce;
   --rce;  if (n >= g_nnote)            return rce;
   /*---(master)------------*/
   g_notes [g_nnote].xr   = g_notes [n].xr;
   g_notes [g_nnote].yr   = g_notes [n].yr;
   g_notes [g_nnote].size = g_notes [n].size;
   g_notes [g_nnote].text = g_notes [n].text;
   /*---(position)----------*/
   g_notes [g_nnote].x    = g_notes [n].x;
   g_notes [g_nnote].y    = g_notes [n].y;
   g_notes [g_nnote].w    = g_notes [n].w;
   g_notes [g_nnote].h    = g_notes [n].h;
   /*---(target)------------*/
   g_notes [g_nnote].s    = g_notes [n].s;
   g_notes [g_nnote].c    = g_notes [n].c;
   g_notes [g_nnote].xt   = g_notes [n].xt;
   g_notes [g_nnote].yt   = g_notes [n].yt;
   g_notes [g_nnote].xb   = g_notes [n].xb;
   g_notes [g_nnote].yb   = g_notes [n].yb;
   g_notes [g_nnote].xe   = g_notes [n].xe;
   g_notes [g_nnote].ye   = g_notes [n].ye;
   /*---(done)--------------*/
   g_notes [n].text = NULL;
   ++g_nnote;
   yview_note__remove   (n);
   return 0;
}

char
yview_note__tobot       (char n)
{
   char        rce         =  -10;
   int         i           =    0;
   --rce;  if (n < 0 || n > MAX_NOTES)  return rce;
   --rce;  if (n >= g_nnote)            return rce;
   for (i = g_nnote; i > 0; --i) {
      /*---(master)---------*/
      g_notes [i].xr   = g_notes [i - 1].xr;
      g_notes [i].yr   = g_notes [i - 1].yr;
      g_notes [i].size = g_notes [i - 1].size;
      g_notes [i].text = g_notes [i - 1].text;
      /*---(position)-------*/
      g_notes [i].x    = g_notes [i - 1].x;
      g_notes [i].y    = g_notes [i - 1].y;
      g_notes [i].w    = g_notes [i - 1].w;
      g_notes [i].h    = g_notes [i - 1].h;
      /*---(target)---------*/
      g_notes [i].s    = g_notes [i - 1].s;
      g_notes [i].c    = g_notes [i - 1].c;
      g_notes [i].xt   = g_notes [i - 1].xt;
      g_notes [i].yt   = g_notes [i - 1].yt;
      g_notes [i].xb   = g_notes [i - 1].xb;
      g_notes [i].yb   = g_notes [i - 1].yb;
      g_notes [i].xe   = g_notes [i - 1].xe;
      g_notes [i].ye   = g_notes [i - 1].ye;
      /*---(done)-----------*/
      g_notes [n].text = NULL;
   }
   ++g_nnote;
   /*---(master)------------*/
   g_notes [0].xr   = g_notes [n + 1].xr;
   g_notes [0].yr   = g_notes [n + 1].yr;
   g_notes [0].size = g_notes [n + 1].size;
   g_notes [0].text = g_notes [n + 1].text;
   /*---(position)----------*/
   g_notes [0].x    = g_notes [n + 1].x;
   g_notes [0].y    = g_notes [n + 1].y;
   g_notes [0].w    = g_notes [n + 1].w;
   g_notes [0].h    = g_notes [n + 1].h;
   /*---(target)------------*/
   g_notes [0].s    = g_notes [n + 1].s;
   g_notes [0].c    = g_notes [n + 1].c;
   g_notes [0].xt   = g_notes [n + 1].xt;
   g_notes [0].yt   = g_notes [n + 1].yt;
   g_notes [0].xb   = g_notes [n + 1].xb;
   g_notes [0].yb   = g_notes [n + 1].yb;
   g_notes [0].xe   = g_notes [n + 1].xe;
   g_notes [0].ye   = g_notes [n + 1].ye;
   /*---(done)--------------*/
   g_notes [n].text = NULL;
   yview_note__remove   (n + 1);
   return 0;
}

char
yview_note__move        (char n, char xr, char yr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
   char        s, x, y;
   char        x_dup       =   -1;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_value   ("n"         , n);
   --rce;  if (n < 0 || n > MAX_NOTES) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (n >= g_nnote) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_dup  = yview_note__find (xr, yr);
   DEBUG_YVIEW   yLOG_complex ("note"      , "%c, %c, %2d", xr, yr, x_dup);
   --rce;  if (x_dup >=  0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s = g_notes [n].size;
   x = g_notes [n].xr;
   y = g_notes [n].yr;
   rc = yview_note__size   (n, xr, yr, s);
   if (rc < 0)  yview_note__size   (n, x, y, s);
   yview_note__retarg (n);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return rc;
}



/*====================------------------------------------====================*/
/*===----                        mass updates                          ----===*/
/*====================------------------------------------====================*/
static void  o___MASS____________o () { return; }

char
yview_note__purge       (char a_init)
{
   int         i           =    0;
   for (i = 0; i < MAX_NOTES; ++i) {
      yview_note__wipe (a_init, i);
   }
   g_nnote = 0;
   return 0;
}

char
yview_note__purgeish    (void)
{
   int         i           =    0;
   for (i = 0; i < g_nnote; ++i) {
      if (g_notes [i].size == ')')  continue;
      if (g_notes [i].size == '!')  continue;
      yview_note__remove   (i);
      i = 0;
   }
   return 0;
}

char
yview_note__resize      (void)
{
   int         i           =    0;
   for (i = 0; i < g_nnote; ++i) {
      yview_note__size (i, g_notes [i].xr, g_notes [i].yr, g_notes [i].size);
   }
   return 0;
}

char
yview_note_init         (void)
{
   return yview_note__purge ('y');
}



/*====================------------------------------------====================*/
/*===----                     adding/changing content                  ----===*/
/*====================------------------------------------====================*/
static void  o___CONTENT_________o () { return; }

char
yview_note__x           (short a_left, short a_wide, uchar w, char xr, short *x)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *p           = NULL;
   int         l           =    0;
   int         c           =    0;
   float       a           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_spoint  (x);
   --rce;  if (x == NULL) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_schar   (xr);
   --rce;  if ((p = strchr (s_norm, xr)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("norm");
      l  = strlen (s_norm) - 1;
      c  = p - s_norm;
      a = c * (1.0 / l);
   } else if  ((p = strchr (s_fine, xr)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("fine");
      l  = strlen (s_fine) - 1;
      c  = p - s_fine;
      a  = c * (1.0 / l);
   } else {
      DEBUG_YVIEW   yLOG_snote   ("unknown");
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_sint    (a_left);
   DEBUG_YVIEW   yLOG_sint    (a_wide);
   *x  = trunc (a_left + (a_wide * a) - (w * a));
   DEBUG_YVIEW   yLOG_sint    (*x);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

short
yview_note__y           (short a_bott, short a_tall, uchar h, char yr, short *y)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *p           = NULL;
   int         l           =    0;
   int         c           =    0;
   float       a           =    0;
   float       b           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_spoint  (y);
   --rce;  if (y == NULL) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_schar   (yr);
   --rce;  if ((p = strchr (s_norm, yr)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("norm");
      l  = strlen (s_norm) - 1;
      c  = p - s_norm;
      a  = 1 - (c * (1.0 / l));
   } else if  ((p = strchr (s_fine, yr)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("fine");
      l  = strlen (s_fine) - 1;
      c  = p - s_fine;
      a  = c * (1.0 / l);
   } else {
      DEBUG_YVIEW   yLOG_snote   ("unknown");
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   b = 1 - a;
   DEBUG_YVIEW   yLOG_sint    (a_bott);
   DEBUG_YVIEW   yLOG_sint    (a_tall);
   if (myVIEW.env == YVIEW_OPENGL) {
      *y  = trunc (a_bott + (a_tall * a) + (h * b));
   } else {
      *y  = trunc (a_bott - (a_tall * a) - (h * b));
   }
   DEBUG_YVIEW   yLOG_sint    (*y);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_note__size        (char n, char xr, char yr, char a_size)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   short       x_left, x_wide, x_bott, x_tall;
   short       x_xlen, x_ylen;
   char       *p           = NULL;
   int         l           =    0;
   int         c           =    0;
   float       a, b;
   short       x, y;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(get environment)----------------*/
   DEBUG_YVIEW   yLOG_char    ("env"       , myVIEW.env);
   /*---(defaults)-----------------------*/
   g_notes [n].size = '=';
   g_notes [n].xr   = '0';
   g_notes [n].x    = 0;
   g_notes [n].xb   = 0;
   g_notes [n].yr   = '0';
   g_notes [n].y    = 0;
   g_notes [n].xb   = 0;
   /*---(defense)------------------------*/
   --rce;  if (strchr (YVIEW_ENVS, myVIEW.env) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_value   ("n"         , n);
   --rce;  if (n < 0 || n >= MAX_NOTES) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(size)---------------------------*/
   switch (myVIEW.env) {
   case YVIEW_OPENGL :
      switch (a_size) {  /* single row/line    */
      case '.'  : g_notes [n].w =  20; g_notes [n].h =  20;  break; /*  2 chars */
      case ','  : g_notes [n].w =  80; g_notes [n].h =  20;  break; /*  9 chars */
      case ';'  : g_notes [n].w = 120; g_notes [n].h =  20;  break; /* 15 chars */
      case ':'  : g_notes [n].w = 190; g_notes [n].h =  20;  break; /* 25 chars */
      }
      switch (a_size) {  /* double row/line    */
      case '-'  : g_notes [n].w = 120; g_notes [n].h =  35;  break; /* 15 chars */
      case ')'  : g_notes [n].w = 190; g_notes [n].h =  35;  break; /* 25 chars */
      }
      switch (a_size) {  /* triple row/line    */
      case '~'  : g_notes [n].w = 155; g_notes [n].h =  48;  break; /* 20 chars */
      case '!'  : g_notes [n].w = 155; g_notes [n].h =  48;  break; /* 20 chars */
      case '='  : g_notes [n].w = 190; g_notes [n].h =  48;  break; /* 25 chars */
      }
      switch (a_size) {  /* quadruple row/line    */
      case '+'  : g_notes [n].w = 250; g_notes [n].h =  62;  break; /* 40 chars */
      }
      break;
   case YVIEW_CURSES :
      switch (a_size) {  /* single row/line    */
      case '.'  : g_notes [n].w =   3; g_notes [n].h =   1;  break;
      case ','  : g_notes [n].w =   9; g_notes [n].h =   1;  break;
      case ';'  : g_notes [n].w =  15; g_notes [n].h =   1;  break;
      case ':'  : g_notes [n].w =  25; g_notes [n].h =   1;  break;
      }
      switch (a_size) {  /* double row/line    */
      case '-'  : g_notes [n].w =  15; g_notes [n].h =   2;  break;
      case ')'  : g_notes [n].w =  31; g_notes [n].h =   2;  break;
      }
      switch (a_size) {  /* triple row/line    */
      case '~'  : g_notes [n].w =  19; g_notes [n].h =   3;  break;
      case '!'  : g_notes [n].w =  19; g_notes [n].h =   3;  break;
      case '='  : g_notes [n].w =  25; g_notes [n].h =   3;  break;
      }
      switch (a_size) {  /* quadruple row/line    */
      case '+'  : g_notes [n].w =  41; g_notes [n].h =   4;  break;
      }
      break;
   }
   DEBUG_YVIEW   yLOG_complex  ("size"      , "%4dw, %4dh", g_notes [n].w, g_notes [n].h);
   /*---(note window)--------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_size"    , a_size);
   --rce;  if (strchr (s_size, a_size) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yVIEW_size   (YVIEW_MAIN  , NULL, &x_left, &x_xlen, &x_bott, &x_ylen);
   yVIEW_size   (YVIEW_WINDOW, NULL, NULL   , &x_wide, NULL   , &x_tall);
   switch (s_part) {
   case YVIEW_WINDOW   :
      x_left  = 0;
      if (myVIEW.env == YVIEW_OPENGL)  x_bott  = 0;
      else                             x_bott  = x_tall - 1;
      break;
   case YVIEW_MAIN     :
      x_wide  = x_xlen;
      x_tall  = x_ylen;
      break;
   }
   if (myVIEW.env == YVIEW_CURSES)  x_bott += 1;
   DEBUG_YVIEW   yLOG_complex  ("area"      , "%c, %4dl, %4dw, %4db, %4dt", s_part, x_left, x_wide, x_bott, x_tall);
   /*---(vertical)-----------------------*/
   DEBUG_YVIEW   yLOG_value   ("yr"        , yr);
   rc  = yview_note__y (x_bott, x_tall, g_notes [n].h, yr, &y);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("can not interpret yr");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(horizontal)---------------------*/
   DEBUG_YVIEW   yLOG_value   ("xr"        , xr);
   rc = yview_note__x (x_left, x_wide, g_notes [n].w, xr, &x);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("can not interpret xr");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(save values)--------------------*/
   g_notes [n].size = a_size;
   g_notes [n].xr   = xr;
   g_notes [n].x    = x;
   g_notes [n].yr   = yr;
   g_notes [n].y    = y;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvikeys_note__grid      (char n, short xt, short yt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   short       x_left, x_wide, x_bott, x_tall;
   int         x_inc , x_bump, y_inc , y_bump;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_char    ("xt"        , xt);
   --rce;  if (xt == 0 || strchr (s_fine, xt) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_char    ("yt"        , yt);
   --rce;  if (xt == 0 || strchr (s_fine, yt) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   if (xt == '-' || yt == '-' || myVIEW.env == YVIEW_CURSES) {
      g_notes [n].xb = g_notes [n].yb = 0;
      g_notes [n].xe = g_notes [n].ye = 0;
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(total size)---------------------*/
   yVIEW_bounds (YVIEW_MAIN, NULL, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);
   DEBUG_YVIEW   yLOG_complex  ("main"      , "%4dl, %4dw, %4db, %4dt", x_left, x_wide, x_bott, x_tall);
   /*---(horizontal)---------------------*/
   g_notes [n].xb = g_notes [n].x + g_notes [n].w * 0.50;
   x_inc  = x_wide / 25;
   x_bump = x_inc * 0.50;
   g_notes [n].xe = x_left + (tolower (xt) - 'a') * x_inc;
   if (xt != tolower (xt))    g_notes [n].xe += x_bump;
   /*---(vertical)-----------------------*/
   g_notes [n].yb = g_notes [n].y - g_notes [n].h * 0.50;
   y_inc  = x_tall / 25;
   x_bump = y_inc * 0.50;
   g_notes [n].ye = x_bott + x_tall - (tolower (yt) - 'a') * y_inc;
   if (yt != tolower (yt))    g_notes [n].ye -= x_bump;
   /*---(complete)-----------------------*/
   g_notes [n].c = '¥';
   /*---(report-out)---------------------*/
   DEBUG_YVIEW   yLOG_complex  ("endpoint"  , "%4dx, %4dy, %4dx, %4dy", g_notes [n].xb, g_notes [n].yb, g_notes [n].xe, g_notes [n].ye);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yvikeys_note__radial    (char n, short xt, short yt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   short       x_left, x_wide, x_bott, x_tall;
   int         x_inc , x_bump, y_inc , y_bump;
   uchar      *x_valid     = "-abcdefghijklmnopqrstuvwxyz";
   float       x_rad       =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_value   ("xt"        , xt);
   --rce;  if (xt <= 0 || xt > 360) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_char    ("yt"        , yt);
   --rce;  if (xt == 0 || strchr (x_valid, yt) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(default)------------------------*/
   if (xt == 0 || yt == '-' || myVIEW.env == YVIEW_CURSES) {
      g_notes [n].xb = g_notes [n].yb = 0;
      g_notes [n].xe = g_notes [n].ye = 0;
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(total size)---------------------*/
   yVIEW_bounds (YVIEW_MAIN, NULL, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);
   DEBUG_YVIEW   yLOG_complex  ("main"      , "%4dl, %4dw, %4db, %4dt", x_left, x_wide, x_bott, x_tall);
   /*---(vertical)-----------------------*/
   g_notes [n].yb = g_notes [n].y - g_notes [n].h * 0.50;
   x_tall /= 2.0;
   y_inc  = x_tall / 25;
   y_bump = y_inc * 0.25;
   x_rad  = (yt - 'a') * y_inc - y_bump;
   /*---(horizontal)---------------------*/
   g_notes [n].xb = g_notes [n].x + g_notes [n].w * 0.50;
   g_notes [n].xe = x_rad * cos ((90 - xt) * DEG2RAD);
   g_notes [n].ye = x_rad * sin ((90 - xt) * DEG2RAD);
   /*---(complete)-----------------------*/
   g_notes [n].c = '†';
   /*---(report-out)---------------------*/
   DEBUG_YVIEW   yLOG_complex  ("endpoint"  , "%4dx, %4dy, %4dx, %4dy", g_notes [n].xb, g_notes [n].yb, g_notes [n].xe, g_notes [n].ye);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__settarg     (char n, char *p)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =   -1;
   int         x_len       =    0;
   char        u           [LEN_LABEL] = "";
   char        x_type      =  '-';
   short       xt          =  '-';
   short       yt          =  '-';
   short       xb, yb;
   short       xe, ye;
   short       x_left, x_wide, x_bott, x_tall;
   short       xd, yd;
   char        s           =  '-';
   float       x_nudge     =  0.0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   g_notes [n].s    = YVIEW_MAIN;
   g_notes [n].c    = '∑';
   g_notes [n].xt   = '∑';
   g_notes [n].yt   = '∑';
   g_notes [n].xb   = 0;
   g_notes [n].yb   = 0;
   g_notes [n].xe   = 0;
   g_notes [n].ye   = 0;
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_point   ("p"         , p);
   --rce;  if (p == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(prepare)------------------------*/
   strlcpy (u, p, LEN_LABEL);
   x_len = strlen (u);
   DEBUG_YVIEW   yLOG_complex ("tail"      , "%2d[%s]", x_len, u);
   if (x_len != 3) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   x_type = u [0];;
   DEBUG_YVIEW   yLOG_char    ("x_type"    , x_type);
   --rce;  if (x_type == 0 || strchr ("‘’◊÷àâÜá", x_type) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_note    ("good");
   xt     = u [1];
   yt     = u [2];
   /*---(get bounds)---------------------*/
   /*> switch (myVIEW.env) {                                                                                  <* 
    *> case YVIEW_OPENGL :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("opengl environment");                                                  <* 
    *>    if (strchr ("‘’◊÷", x_type) != NULL) {                                                              <* 
    *>       DEBUG_YVIEW   yLOG_note    ("main window type");                                                 <* 
    *>       yVIEW_bounds (YVIEW_MAIN  , NULL, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);   <* 
    *>       s = YVIEW_MAIN;                                                                                  <* 
    *>    } else {                                                                                            <* 
    *>       DEBUG_YVIEW   yLOG_note    ("full window type");                                                 <* 
    *>       yVIEW_bounds (YVIEW_WINDOW, NULL, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);   <* 
    *>       s = YVIEW_WINDOW;                                                                                <* 
    *>    }                                                                                                   <* 
    *>    break;                                                                                              <*/
   /*> case YVIEW_CURSES :                                                            <*/
   DEBUG_YVIEW   yLOG_note    ("curses environment");
   if (strchr ("‘’◊÷", x_type) != NULL) {
      DEBUG_YVIEW   yLOG_note    ("main window type");
      yVIEW_size   (YVIEW_MAIN  , NULL, &x_left, &x_wide, &x_bott, &x_tall);
      s = YVIEW_MAIN;
   } else {
      DEBUG_YVIEW   yLOG_note    ("full window type");
      yVIEW_size   (YVIEW_WINDOW, NULL, &x_left, &x_wide, &x_bott, &x_tall);
      s = YVIEW_WINDOW;
   }
   /*> break;                                                                      <*/
   /*> }                                                                              <*/
   /*> DEBUG_YVIEW   yLOG_complex ("coord"     , "%4dl %4dw %4db %4dt", x_left, x_wide, x_bott, x_tall);   <*/
   /*---(fix types)-------------------*/
   /*> switch (x_type) {                                                              <* 
    *> case 'à' :  x_type = '‘';  break;                                              <* 
    *> case 'â' :  x_type = '’';  break;                                              <* 
    *> case 'Ü' :  x_type = '◊';  break;                                              <* 
    *> case 'á' :  x_type = '÷';  break;                                              <* 
    *> }                                                                              <*/
   /*> DEBUG_YVIEW   yLOG_char    ("x_type*"   , x_type);                             <*/
   /*---(calc target)-----------------*/
   if (myVIEW.env == YVIEW_OPENGL)  x_nudge = x_wide * 0.015;
   rc = yview_note__x (x_left + x_nudge, x_wide - 1 - x_nudge * 2.0, 0, xt, &xe);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_char    ("xt fail"   , xt);
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (myVIEW.env == YVIEW_OPENGL)  x_nudge = x_tall * 0.015;
   rc = yview_note__y (x_bott + x_nudge, x_tall - 1 - x_nudge * 2.0, 0, yt, &ye);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_char    ("yt fail"   , yt);
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_complex ("target"    , "%4dx, %4dy", xe, ye);
   /*---(get diffs)-------------------*/
   if (myVIEW.env == YVIEW_CURSES) {
      DEBUG_YVIEW   yLOG_note    ("curses quadrents");
      xd = g_notes [n].x - xe;
      yd = g_notes [n].y - ye;
      DEBUG_YVIEW   yLOG_complex ("diff"      , "%4dx, %4dy", xd, yd);
      if (strchr ("‘’àâ", x_type) != NULL) {
         if (xd < 0) {
            if (yd < 0)  x_type = '4';
            else         x_type = '1';
         } else {
            if (yd < 0)  x_type = '5';
            else         x_type = '8';
         }
      } else {
         if (xd < 0) {
            if (yd < 0)  x_type = '3';
            else         x_type = '2';
         } else {
            if (yd < 0)  x_type = '6';
            else         x_type = '7';
         }
      }
   } else {
      DEBUG_YVIEW   yLOG_note    ("opengl quadrents");
      xd = xe - g_notes [n].x;
      yd = ye - g_notes [n].y;
      DEBUG_YVIEW   yLOG_complex ("diff"      , "%4dx, %4dy", xd, yd);
      if (strchr ("‘’àâ", x_type) != NULL) {
         if (xd > 0) {
            if (yd < 0)  x_type = '4';
            else         x_type = '1';
         } else {
            if (yd < 0)  x_type = '5';
            else         x_type = '8';
         }
      } else {
         if (xd > 0) {
            if (yd < 0)  x_type = '3';
            else         x_type = '2';
         } else {
            if (yd < 0)  x_type = '6';
            else         x_type = '7';
         }
      }
   }
   DEBUG_YVIEW   yLOG_char    ("x_type"    , x_type);
   /*---(set)-------------------------*/
   switch (x_type) {
   case '1' :
      DEBUG_YVIEW   yLOG_note    ("1 type -- up and right");
      yb = g_notes [n].y - 1;
      if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));
      else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));
      break;
   case '2' :
      DEBUG_YVIEW   yLOG_note    ("2 type -- right and up");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;
      else                             yb = g_notes [n].y;
      xb = g_notes [n].x + g_notes [n].w;
      break;
   case '3' :
      DEBUG_YVIEW   yLOG_note    ("3 type -- right and down");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;
      else                             yb = g_notes [n].y + g_notes [n].h - 1;
      xb = g_notes [n].x + g_notes [n].w;
      break;
   case '4' :
      DEBUG_YVIEW   yLOG_note    ("4 type -- down and right");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h;
      else                             yb = g_notes [n].y + g_notes [n].h;
      if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));
      else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));
      break;
   case '5' :
      DEBUG_YVIEW   yLOG_note    ("5 type -- down and left");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h;
      else                             yb = g_notes [n].y + g_notes [n].h;
      if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));
      else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));
      break;
   case '6' :
      DEBUG_YVIEW   yLOG_note    ("6 type -- left and up");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;
      else                             yb = g_notes [n].y + g_notes [n].h - 1;
      xb = g_notes [n].x - 1;
      break;
   case '7' :
      DEBUG_YVIEW   yLOG_note    ("7 type -- left and up");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;
      else                             yb = g_notes [n].y;
      xb = g_notes [n].x - 1;
      break;
   case '8' :
      DEBUG_YVIEW   yLOG_note    ("8 type -- up and right");
      yb = g_notes [n].y - 1;
      if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));
      else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));
      break;
   }
   DEBUG_YVIEW   yLOG_complex ("begin"     , "%4dx, %4dy", xb, yb);
   /*---(adjust)----------------------*/
   /*> if (strchr ("‘’", x_type) != NULL) {                                        <* 
    *>    xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));                  <* 
    *>    yb = g_notes [n].y + trunc (0.5 * (g_notes [n].h - 1));                  <* 
    *>    yb = g_notes [n].y - 1;                                                  <* 
    *> } else {                                                                    <* 
    *> }                                                                           <* 
    *> yb = g_notes [n].y + trunc (0.5 * (g_notes [n].h - 1));                     <*/
   /*> DEBUG_YVIEW   yLOG_complex ("ready"     , "%c %c %c", x_type, xt, yt);         <*/
   /*> yvikeys_note__grid   (n, xt, yt);                                           <*/
   /*---(update)-------------------------*/
   if (rc >= 0) {
      g_notes [n].s    = s;
      g_notes [n].c    = x_type;
      g_notes [n].xt   = xt;
      g_notes [n].yt   = yt;
      g_notes [n].xb   = xb;
      g_notes [n].yb   = yb;
      g_notes [n].xe   = xe;
      g_notes [n].ye   = ye;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__retarg      (char n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        t           [LEN_LABEL] = "";
   switch (g_notes [n].c) {
   case '¥' :
      sprintf (t, "%c%c%c", g_notes [n].c, g_notes [n].xt, g_notes [n].yt);
      break;
   case '†' :
      sprintf (t, "%c%d%c", g_notes [n].c, g_notes [n].xt, g_notes [n].yt);
      break;
   }
   yview_note__settarg (n, t);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                        main driver                           ----===*/
/*====================------------------------------------====================*/
static void  o___DRIVER__________o () { return; }

char
yview_note_add          (char a_part, char a_xr, char a_yr, char a_size, char *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        x_text      [LEN_RECD]  = "";
   char       *v           = NULL;
   char       *p           = NULL;
   int         l           =    0;
   char        n           =   -1;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_point   ("a_text"    , a_text);
   --rce;  if (a_text == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_text);
   DEBUG_YVIEW   yLOG_point   ("l"         , l);
   --rce;  if (l < 1) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   strlcpy (x_text, a_text, LEN_RECD);
   DEBUG_YVIEW   yLOG_info    ("x_text"    , x_text);
   /*---(check context)------------------*/
   --rce;  switch (a_part) {
   case YVIEW_MAIN     :
   case YVIEW_WINDOW   :
      s_part = a_part;
      break;
   default             :
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
      break;
   }
   /*---(prepare)------------------------*/
   p = strrchr (x_text, ' ');
   DEBUG_YVIEW   yLOG_point   ("p"         , p);
   if (p != NULL) {
      l = strlen (p);
      DEBUG_YVIEW   yLOG_value   ("l"         , l);
      if (l == 4) {
         DEBUG_YVIEW   yLOG_char    ("p[1]"      , p [1]);
         if (strchr (s_targ, p [1]) != NULL)  {
            v = p + 1;;
            p [0]  = '\0';   /* trim from text */
         } else v = NULL;
      } else v = NULL;
   } else v = NULL;
   DEBUG_YVIEW   yLOG_point   ("v"         , v);
   /*---(find note)----------------------*/
   n  = yview_note__find (a_xr, a_yr);
   DEBUG_YVIEW   yLOG_complex ("note"      , "%c, %c, %2d", a_xr, a_yr, n);
   if (n <  0)  n = g_nnote;
   DEBUG_YVIEW   yLOG_value   ("n"         , n);
   /*---(append/change note)-------------*/
   rc = yview_note__size (n, a_xr, a_yr, a_size);
   DEBUG_YVIEW   yLOG_char    ("size"      , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(update text)--------------------*/
   if (g_notes [n].text != NULL)  free (g_notes [n].text);
   strltrim (x_text, ySTR_BOTH, LEN_RECD);
   g_notes [n].text = strdup (x_text);
   if (n == g_nnote)  ++g_nnote;
   rc = yview_note__totop   (n);
   /*---(targeting)----------------------*/
   yview_note__untarget (n);
   if (v == NULL) {
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   rc = yview_note__settarg (n, v);
   DEBUG_YVIEW   yLOG_char    ("settarg"   , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__direct      (char *a_all, char a_part)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        n           =    0;
   int         x_len       =    0;
   char        u           [LEN_RECD]  = "";
   char       *v           = NULL;
   char       *p           = NULL;
   char        x_type      =  '-';
   char        xr          =  '-';
   char        yr          =  '-';
   char        x_size      =  '=';
   short       xt          =  '-';
   short       yt          =  '-';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_point   ("a_all"     , a_all);
   --rce;  if (a_all == NULL || a_all [0] == '\0') {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_info    ("a_all"     , a_all);
   x_len = strlen (a_all);
   DEBUG_YVIEW   yLOG_value   ("x_len"     , x_len);
   /*---(singles)------------------------*/
   --rce;  if (x_len == 1) {
      DEBUG_YVIEW   yLOG_char    ("single"    , a_all [0]);
      switch (a_all [0])  {
      case '#'  :
         DEBUG_YVIEW   yLOG_note    ("selected a full purge");
         rc = yview_note__purge ('-');
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return rc;
         break;
      case '/'  :
         DEBUG_YVIEW   yLOG_note    ("selected all but title purge");
         rc = yview_note__purgeish ();
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return rc;
         break;
      case '!'  :
         DEBUG_YVIEW   yLOG_note    ("display all notes");
         s_noting = 'y';
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      case '%'  :
         DEBUG_YVIEW   yLOG_note    ("hide all notes");
         s_noting = '-';
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return 0;
         break;
      default   :
         DEBUG_YVIEW   yLOG_note    ("unknown single char option");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
   }
   /*---(setup)--------------------------*/
   xr = a_all [0];
   yr = a_all [1];
   n  = yview_note__find (xr, yr);
   DEBUG_YVIEW   yLOG_complex ("note"      , "%c, %c, %2d", xr, yr, n);
   /*---(doubles)------------------------*/
   --rce;  if (x_len == 2) {
      if (n <  0) {
         DEBUG_YVIEW   yLOG_note    ("note not found for on-top");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = yview_note__totop   (n);
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(triples)------------------------*/
   --rce;  if (x_len == 3) {
      if (n <  0) {
         DEBUG_YVIEW   yLOG_note    ("note not found for deletion");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      switch (a_all [2]) {
      case '#' :
         DEBUG_YVIEW   yLOG_note    ("delete a note");
         rc = yview_note__remove   (n);
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return rc;
         break;
      default  :
         DEBUG_YVIEW   yLOG_note    ("unknown triple char option");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
         break;
      }
   }
   /*---(prepare)------------------------*/
   x_size = a_all [2];
   strlcpy (u, a_all + 3, LEN_RECD);
   /*---(triples)------------------------*/
   --rce;  if (x_len == 5 && a_all [2] == '>') {
      if (n <  0) {
         DEBUG_YVIEW   yLOG_note    ("note not found for moving");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = yview_note__move   (n, u [0], u [1]);
      if (rc >= 0)  yview_note__totop   (n);
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return rc;
   }
   /*---(add a note)---------------------*/
   rc = yview_note_add (a_part, xr, yr, x_size, u);
   DEBUG_YVIEW   yLOG_value   ("add"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*> v = a_all + 2;                                                                 <* 
    *> p = strrchr (u, ' ');                                                          <* 
    *> DEBUG_YVIEW   yLOG_point   ("p"         , p);                                  <* 
    *> if (p != NULL) {                                                               <* 
    *>    DEBUG_YVIEW   yLOG_char    ("p[0]"      , p [1]);                           <* 
    *>    if (strchr (s_targ, p [1]) != NULL)  {                                      <* 
    *>       v = p + 1;;                                                              <* 
    *>       p [0]  = '\0';   /+ trim from text +/                                    <* 
    *>    } else v = NULL;                                                            <* 
    *> } else v = NULL;                                                               <* 
    *> DEBUG_YVIEW   yLOG_point   ("v"         , v);                                  <* 
    *> /+---(find note)----------------------+/                                       <* 
    *> DEBUG_YVIEW   yLOG_char    ("x_size"    , x_size);                             <* 
    *> --rce;  if (strchr (s_size, x_size) == NULL) {                                 <* 
    *>    DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> if (n <  0)  n = g_nnote;                                                      <* 
    *> DEBUG_YVIEW   yLOG_value   ("n"         , n);                                  <* 
    *> /+---(append/change note)-------------+/                                       <* 
    *> rc = yview_note__size (n, xr, yr, x_size);                                     <* 
    *> DEBUG_YVIEW   yLOG_char    ("size"      , rc);                                 <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <* 
    *> if (g_notes [n].text != NULL)  free (g_notes [n].text);                        <* 
    *> g_notes [n].text = strdup (u);                                                 <* 
    *> if (n == g_nnote)  ++g_nnote;                                                  <* 
    *> rc = yview_note__totop   (n);                                                  <* 
    *> /+---(targeting)----------------------+/                                       <* 
    *> if (v == NULL) {                                                               <* 
    *>    DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                  <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <* 
    *> rc = yview_note__settarg (n, v);                                               <* 
    *> DEBUG_YVIEW   yLOG_char    ("settarg"   , rc);                                 <* 
    *> --rce;  if (rc < 0) {                                                          <* 
    *>    DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                             <* 
    *>    return rce;                                                                 <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char yVIEW_note_direct  (char *a_all)  { return yview_note__direct (a_all, YVIEW_MAIN);   }
char yVIEW_note_directw (char *a_all)  { return yview_note__direct (a_all, YVIEW_WINDOW); }



/*====================------------------------------------====================*/
/*===----                         data access                          ----===*/
/*====================------------------------------------====================*/
static void  o___ACCESSS_________o () { return; }

char
yVIEW_note_data         (char n, uchar *m, uchar *s, short *x, short *y, uchar *w, uchar *h, uchar *t, uchar *c, short *xb, short *yb, short *xe, short *ye)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        x_name      [LEN_LABEL] = "";
   /*---(defense)------------------------*/
   --rce;  if (n < 0 || n > MAX_NOTES)  return rce;
   --rce;  if (n >= g_nnote)            return rce;
   /*---(top note)-----------------------*/
   if (m   != NULL)  *m  = g_nnote - 1;
   /*---(top-left)-----------------------*/
   if (s   != NULL)  *s  = g_notes [n].size;
   if (x   != NULL)  *x  = g_notes [n].x;
   if (y   != NULL)  *y  = g_notes [n].y;
   /*---(size)---------------------------*/
   if (w   != NULL)  *w  = g_notes [n].w;
   if (h   != NULL)  *h  = g_notes [n].h;
   /*---(text)---------------------------*/
   if (t   != NULL) {
      if (g_notes [n].text == NULL)  strlcpy (t, ""              , LEN_HUND);
      else                           strlcpy (t, g_notes [n].text, LEN_HUND);
   }
   /*---(target)-------------------------*/
   if (c   != NULL)  *c  = g_notes [n].c;
   if (xb  != NULL)  *xb = g_notes [n].xb;
   if (yb  != NULL)  *yb = g_notes [n].yb;
   if (xe  != NULL)  *xe = g_notes [n].xe;
   if (ye  != NULL)  *ye = g_notes [n].ye;
   /*---(complete)-----------------------*/
   return 0;
}



/*====================------------------------------------====================*/
/*===----                          unit testing                        ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yview_note__unit        (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   int         i           =    0;
   int         c           =    0;
   char        s           [LEN_HUND]  = "";
   char        t           [LEN_HUND]  = "";
   /*---(preprare)-----------------------*/
   strlcpy  (unit_answer, "NOTE unit        : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "count"          ) == 0) {
      for (i = 0; i < MAX_NOTES; ++i) {
         if (g_notes [i].xr == '0')  strcat (t, "∑");
         else                        strcat (t, "œ");
      }
      snprintf (unit_answer, LEN_FULL, "NOTE count       : %2d  Â%sÊ", g_nnote, t);
   }
   else if (strcmp (a_question, "entry"          ) == 0) {
      if (n < 0 || n > MAX_NOTES)     snprintf (unit_answer, LEN_FULL, "NOTE entry  (%2s) : ∑ ∑ ∑    ∑x    ∑y   ∑w  ∑h  ∑ÂÊ                   ∑,   ∑  ∑ ∑    ∑        ∑,   ∑", "--");
      else if (g_notes [n].xr == '0') snprintf (unit_answer, LEN_FULL, "NOTE entry  (%2d) : ∑ ∑ ∑    ∑x    ∑y   ∑w  ∑h  ∑ÂÊ                   ∑,   ∑  ∑ ∑    ∑        ∑,   ∑", n);
      else {
         if (g_notes [n].text != NULL)  sprintf  (t, "%2dÂ%.15sÊ", strlen (g_notes [n].text), g_notes [n].text);
         else                           strcpy   (t, " ∑ÂÊ");
         switch (g_notes [n].c) {
         case '‘' : case '’' : case '◊' : case '÷' : 
            sprintf (s, "%c %4dx %4dy to %4dx:%c %4dy:%c", g_notes [n].c, g_notes [n].xb, g_notes [n].yb, g_notes [n].xe, g_notes [n].xt, g_notes [n].ye, g_notes [n].yt);
            break;
         case '1' : case '2' : case '3' : case '4' :
         case '5' : case '6' : case '7' : case '8' :
            sprintf (s, "%c %4dx %4dy to %4dx:%c %4dy:%c", g_notes [n].c, g_notes [n].xb, g_notes [n].yb, g_notes [n].xe, g_notes [n].xt, g_notes [n].ye, g_notes [n].yt);
            break;
         default  :
            /*> sprintf (s, "%c %4dx %4dy to %4dx:%c %4dy:%c", g_notes [n].c, g_notes [n].xb, g_notes [n].yb, g_notes [n].xe, g_notes [n].xt, g_notes [n].ye, g_notes [n].yt);   <*/
            sprintf (s, "%c    ∑x    ∑y       ∑x ∑    ∑y ∑"  , g_notes [n].c);
            break;
         }
         snprintf (unit_answer, LEN_FULL, "NOTE entry  (%2d) : %c %c %c %4dx %4dy %3dw %2dh %-19.19s %s", n, g_notes [n].xr, g_notes [n].yr, g_notes [n].size, g_notes [n].x, g_notes [n].y, g_notes [n].w, g_notes [n].h, t, s);
      }
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}
