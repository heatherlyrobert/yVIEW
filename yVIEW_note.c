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
 */
/*
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
 *     ^ command     1  x  56
 *
 *     - small       2  x  14
 *     ) title       2  x  25
 *
 *     ! warning     3    
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

static char  *s_norm       = "123456789";
static char  *s_fine       = "ZYXWVUTSRQPONMLKJIHGFEDCBA5abcdefghijklmnopqrstuvwxyz";
static char  *s_targ       = "‘’◊÷àâÜá";
static char   s_noting     = 'y';
static char   s_part       = YVIEW_MAIN;


/*
 *  opengl is loosely 6.5 * curses width = wide
 *
 */
static struct {
   char        abbr;                        /* identifier/abbreviation        */
   char        terse       [LEN_TERSE];     /* short name                     */
   short       ch, cw, CW;                  /* curses dimensions (and OLD)    */
   short       gh, gw, GW;                  /* opengl dimensions (and OLD)    */
} s_sizes [LEN_LABEL] = {
   /*  a    --terse--     ----curses----   ----opengl---- */
   {  '~', "stealth"  ,     1,   1,   1,     1,   1,   1  },
   /*  a    --terse--     ----curses----   ----opengl---- */
   {  '.', "bullet"   ,     1,   3,   3,    20,  20,  20  },
   {  ',', "word"     ,     1,   9,   9,    20,  60,  60  },
   {  ';', "call-out" ,     1,  14,  15,    20, 100, 120  },
   {  ':', "long-call",     1,  25,  25,    20, 160, 190  },
   {  '^', "command"  ,     1,  56,  57,    20, 360, 350  },
   /*  a    terse----     ----curses---    ----opengl---- */
   {  '-', "small"    ,     2,  15,  15,    35, 100, 120  },
   {  ')', "title"    ,     2,  30,  31,    35, 190, 190  }, /* special color/treatment */
   /*  a    terse----     ----curses----   ----opengl---- */
   {  '!', "warning"  ,     3,  20,  19,    48, 130, 155  }, /* special color           */
   {  '=', "normal"   ,     3,  25,  25,    48, 160, 190  },
   /*  a    terse----     ----curses----   ----opengl---- */
   {  '+', "large"    ,     4,  40,  41,    62, 260, 250  },
   {  '|', "gridline" ,     0,   0,   0,     0,   0,   0  }, /* pseudo overlay          */
   /*  a    terse----     ----curses----   ----opengl---- */
   {  'x', "testing"  ,     0,   0,   0,     0,   0,   0  },
   {   0 , ""         ,     0,   0,   0,     0,   0,   0  },
};
static char   s_valid      [LEN_LABEL] = "";



/*====================------------------------------------====================*/
/*===----                       little supporters                      ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
yview_note__untarget    (char n)
{
   /*---(target)-------------------------*/
   g_notes [n].st    = YVIEW_MAIN;
   g_notes [n].xt    = '-';
   g_notes [n].yt    = '-';
   g_notes [n].xb    = 0;
   g_notes [n].yb    = 0;
   g_notes [n].xe    = 0;
   g_notes [n].ye    = 0;
   g_notes [n].q     = '-';
   g_notes [n].c     = '-';
   /*---(complete)-----------------------*/
   return 0;
}

char
yview_note__wipe        (char a_init, char n)
{
   /*---(text first)---------------------*/
   if (a_init != 'y' && g_notes [n].text != NULL) free (g_notes [n].text);
   g_notes [n].text = NULL;
   /*---(master)-------------------------*/
   g_notes [n].xr    = '∑';
   g_notes [n].yr    = '∑';
   g_notes [n].size  = '∑';
   /*---(position)-----------------------*/
   g_notes [n].s     = YVIEW_MAIN;
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
   int         x_max       =    0;
   --rce;  if (n < 0 || n >= MAX_NOTES)  return rce;
   --rce;  if (n >= g_nnote)             return rce;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   if (g_notes [n].text != NULL)  free (g_notes [n].text);
   g_notes [n].text = NULL;  /* ground */
   yview_note__wipe ('-', n);
   yVIEW_notes_debug  ();
   /*---(set max)------------------------*/
   DEBUG_YVIEW   yLOG_value   ("n"         , n);
   DEBUG_YVIEW   yLOG_value   ("g_nnote"   , g_nnote);
   x_max = g_nnote - 1;
   if (x_max + 1 >= MAX_NOTES)  x_max = MAX_NOTES - 1;
   DEBUG_YVIEW   yLOG_value   ("x_max"     , x_max);
   DEBUG_YVIEW   yLOG_value   ("MAX"       , MAX_NOTES);
   for (i = n; i < x_max; ++i) {
      DEBUG_YVIEW   yLOG_complex ("copy"      , "%2d from %2d", i, i + 1);
      /*---(master)---------*/
      g_notes [i].xr   = g_notes [i + 1].xr;
      g_notes [i].yr   = g_notes [i + 1].yr;
      g_notes [i].size = g_notes [i + 1].size;
      /*---(position)-------*/
      g_notes [i].s    = g_notes [i + 1].s;
      g_notes [i].x    = g_notes [i + 1].x;
      g_notes [i].y    = g_notes [i + 1].y;
      g_notes [i].w    = g_notes [i + 1].w;
      g_notes [i].h    = g_notes [i + 1].h;
      g_notes [i].text = g_notes [i + 1].text;
      g_notes [i + 1].text = NULL; /* don't leave the ghost behind */
      /*---(target)---------*/
      g_notes [i].st   = g_notes [i + 1].st;
      g_notes [i].xt   = g_notes [i + 1].xt;
      g_notes [i].yt   = g_notes [i + 1].yt;
      g_notes [i].xb   = g_notes [i + 1].xb;
      g_notes [i].yb   = g_notes [i + 1].yb;
      g_notes [i].xe   = g_notes [i + 1].xe;
      g_notes [i].ye   = g_notes [i + 1].ye;
      g_notes [i].q    = g_notes [i + 1].q;
      g_notes [i].c    = g_notes [i + 1].c;
      /*---(done)-----------*/
      yview_note__wipe ('y', i + 1);
   }
   --g_nnote;
   yVIEW_notes_debug  ();
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__totop       (char n)
{
   char        rce         =  -10;
   int         i           =    0;
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_value   ("n"         , n);
   DEBUG_YVIEW   yLOG_value   ("MAX"       , MAX_NOTES);
   --rce;  if (n < 0 || n > MAX_NOTES) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_value   ("g_nnote"   , g_nnote);
   --rce;  if (n >= g_nnote) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (n == g_nnote - 1) {
      DEBUG_YVIEW   yLOG_note    ("already on top");
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   yVIEW_notes_debug  ();
   /*---(master)------------*/
   g_notes [g_nnote].xr   = g_notes [n].xr;
   g_notes [g_nnote].yr   = g_notes [n].yr;
   g_notes [g_nnote].size = g_notes [n].size;
   g_notes [g_nnote].text = g_notes [n].text;
   /*---(position)----------*/
   g_notes [g_nnote].s    = g_notes [n].s;
   g_notes [g_nnote].x    = g_notes [n].x;
   g_notes [g_nnote].y    = g_notes [n].y;
   g_notes [g_nnote].w    = g_notes [n].w;
   g_notes [g_nnote].h    = g_notes [n].h;
   /*---(target)------------*/
   g_notes [g_nnote].st   = g_notes [n].st;
   g_notes [g_nnote].xt   = g_notes [n].xt;
   g_notes [g_nnote].yt   = g_notes [n].yt;
   g_notes [g_nnote].xb   = g_notes [n].xb;
   g_notes [g_nnote].yb   = g_notes [n].yb;
   g_notes [g_nnote].xe   = g_notes [n].xe;
   g_notes [g_nnote].ye   = g_notes [n].ye;
   g_notes [g_nnote].q    = g_notes [n].q;
   g_notes [g_nnote].c    = g_notes [n].c;
   /*---(done)--------------*/
   g_notes [n].text = NULL;
   ++g_nnote;
   yview_note__remove   (n);
   yVIEW_notes_debug  ();
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
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
      g_notes [i].s    = g_notes [i - 1].s;
      g_notes [i].x    = g_notes [i - 1].x;
      g_notes [i].y    = g_notes [i - 1].y;
      g_notes [i].w    = g_notes [i - 1].w;
      g_notes [i].h    = g_notes [i - 1].h;
      /*---(target)---------*/
      g_notes [i].c    = g_notes [i - 1].c;
      g_notes [i].st   = g_notes [i - 1].st;
      g_notes [i].xt   = g_notes [i - 1].xt;
      g_notes [i].yt   = g_notes [i - 1].yt;
      g_notes [i].xb   = g_notes [i - 1].xb;
      g_notes [i].yb   = g_notes [i - 1].yb;
      g_notes [i].xe   = g_notes [i - 1].xe;
      g_notes [i].ye   = g_notes [i - 1].ye;
      g_notes [i].q    = g_notes [i - 1].q;
      g_notes [i].c    = g_notes [i - 1].c;
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
   g_notes [0].s    = g_notes [n + 1].s;
   g_notes [0].x    = g_notes [n + 1].x;
   g_notes [0].y    = g_notes [n + 1].y;
   g_notes [0].w    = g_notes [n + 1].w;
   g_notes [0].h    = g_notes [n + 1].h;
   /*---(target)------------*/
   g_notes [0].st   = g_notes [n + 1].st;
   g_notes [0].xt   = g_notes [n + 1].xt;
   g_notes [0].yt   = g_notes [n + 1].yt;
   g_notes [0].xb   = g_notes [n + 1].xb;
   g_notes [0].yb   = g_notes [n + 1].yb;
   g_notes [0].xe   = g_notes [n + 1].xe;
   g_notes [0].ye   = g_notes [n + 1].ye;
   g_notes [0].q    = g_notes [n + 1].q;
   g_notes [0].c    = g_notes [n + 1].c;
   /*---(done)--------------*/
   g_notes [n].text = NULL;
   yview_note__remove   (n + 1);
   return 0;
}

char
yview_note__move        (char n, char a_xr, char a_yr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        t           [LEN_LABEL] = "";
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
   x_dup  = yview_note__find (a_xr, a_yr);
   DEBUG_YVIEW   yLOG_complex ("note"      , "%c, %c, %2d", a_xr, a_yr, x_dup);
   --rce;  if (x_dup >=  0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yview_note__position (myVIEW.env, g_notes [n].s, g_notes [n].size, &(g_notes [n].w), &(g_notes [n].h), a_xr, a_yr, &(g_notes [n].s), &(g_notes [n].xr), &(g_notes [n].yr), &(g_notes [n].x), &(g_notes [n].y));
   DEBUG_YVIEW   yLOG_value   ("pos"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
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
      yview_note__position (myVIEW.env, g_notes [i].s, g_notes [i].size, &(g_notes [i].w), &(g_notes [i].h), g_notes [i].xr, g_notes [i].yr, NULL, NULL, NULL, &(g_notes [i].x), &(g_notes [i].y));
      /*> yview_note__size (i, g_notes [i].xr, g_notes [i].yr, g_notes [i].size);     <*/
   }
   return 0;
}

char
yview_note_init         (void)
{
   int         i           =    0;
   char        t           [LEN_SHORT] = "";
   strcpy (s_valid, "");
   for (i = 0; i < LEN_LABEL; ++i) {
      if (s_sizes [i].abbr == 0)  break;
      sprintf (t, "%c", s_sizes [i].abbr);
      strlcat (s_valid, t, LEN_LABEL);
   }
   yview_note__purge ('y');
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     adding/changing content                  ----===*/
/*====================------------------------------------====================*/
static void  o___CONTENT_________o () { return; }

char
yview_note__pct         (char a_type, char a_code, float *r_pct)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char       *p           = NULL;
   int         l           =    0;
   int         c           =    0;
   float       a           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   DEBUG_YVIEW   yLOG_schar   (a_type);
   DEBUG_YVIEW   yLOG_schar   (a_code);
   /*---(default)------------------------*/
   if (r_pct != NULL)  *r_pct = 0.0;
   /*---(defense)------------------------*/
   --rce;  if (a_code == 0) {
      DEBUG_YVIEW   yLOG_snote   ("null code");
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle normal)------------------*/
   --rce;  if ((p = strchr (s_norm, a_code)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("norm");
      l  = strlen (s_norm) - 1;
      c  = p - s_norm;
      a  = c * (1.0 / l);
      if (a_type == 'y')  a = 1 - a;
   }
   /*---(handle fine)--------------------*/
   else if  ((p = strchr (s_fine, a_code)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("fine");
      l  = strlen (s_fine) - 1;
      c  = p - s_fine;
      a  = c * (1.0 / l);
   }
   /*---(bad range)----------------------*/
   else {
      DEBUG_YVIEW   yLOG_snote   ("unknown");
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(save-back)----------------------*/
   DEBUG_YVIEW   yLOG_sreal   (a);
   if (r_pct != NULL)  *r_pct = a;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_note__x           (char a_env, short a_left, short a_wide, short w, char xr, short *r_xpos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   char       *p           = NULL;
   float       a           =    0;
   int         x           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(get coordinate)-----------------*/
   rc = yview_note__pct  ('x', xr, &a);
   DEBUG_YVIEW   yLOG_value   ("pct"       , rc);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(adjust range)-------------------*/
   --a_wide;
   /*---(final)--------------------------*/
   DEBUG_YVIEW   yLOG_value   ("a_left"    , a_left);
   DEBUG_YVIEW   yLOG_value   ("a_wide"    , a_wide);
   x  = trunc (a_left + (a_wide * a) - (w * a));
   DEBUG_YVIEW   yLOG_value   ("x"         , x);
   /*---(save-back)----------------------*/
   if (r_xpos != NULL)  *r_xpos = x;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__y           (char a_env, short a_bott, short a_tall, short h, char yr, short *r_ypos)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   float       a           =    0;
   float       b           =    0;
   int         y           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(get coordinate)-----------------*/
   rc = yview_note__pct  ('y', yr, &a);
   DEBUG_YVIEW   yLOG_value   ("pct"       , rc);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rc);
      return rc;
   }
   /*---(adjust range)-------------------*/
   --a_tall;
   /*---(final)--------------------------*/
   b = 1 - a;
   DEBUG_YVIEW   yLOG_value   ("a_bott"    , a_bott);
   DEBUG_YVIEW   yLOG_value   ("a_tall"    , a_tall);
   if (a_env == YVIEW_OPENGL) {
      y  = trunc (a_bott + (a_tall * a) + (h * b));
   } else {
      y  = trunc (a_bott - (a_tall * a) - (h * b));
   }
   DEBUG_YVIEW   yLOG_value   ("y"         , y);
   /*---(save-back)----------------------*/
   if (r_ypos != NULL)  *r_ypos = y;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__y_OLD       (char a_env, short a_bott, short a_tall, short h, char yr, short *y)
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
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_spoint  (y);
   --rce;  if (y == NULL) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(adjust range)-------------------*/
   --a_tall;
   /*---(handle normal)------------------*/
   DEBUG_YVIEW   yLOG_schar   (yr);
   --rce;  if ((p = strchr (s_norm, yr)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("norm");
      l  = strlen (s_norm) - 1;
      c  = p - s_norm;
      a  = 1 - (c * (1.0 / l));
   }
   /*---(handle fine)--------------------*/
   else if  ((p = strchr (s_fine, yr)) != NULL) {
      DEBUG_YVIEW   yLOG_snote   ("fine");
      l  = strlen (s_fine) - 1;
      c  = p - s_fine;
      a  = c * (1.0 / l);
   }
   /*---(bad range)----------------------*/
   else {
      DEBUG_YVIEW   yLOG_snote   ("unknown");
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(final)--------------------------*/
   b = 1 - a;
   DEBUG_YVIEW   yLOG_sint    (a_bott);
   DEBUG_YVIEW   yLOG_sint    (a_tall);
   if (a_env == YVIEW_OPENGL) {
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
yview_note__sizer       (char a_env, char a_size, char *r_size, short *r_wide, short *r_high)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   short       w, h;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_schar   (a_size);
   DEBUG_YVIEW   yLOG_snote   (s_valid);
   --rce;  if (a_size == 0 || strchr (s_valid, a_size) == NULL) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(find)---------------------------*/
   --rce;  for (i = 0; i < LEN_LABEL; ++i) {
      if (s_sizes [i].abbr == 0) {
         DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
         return rce;
      }
      if (s_sizes [i].abbr == a_size)  break;
   }
   /*---(opengl)-------------------------*/
   if (a_env == YVIEW_OPENGL) {
      w = s_sizes [i].gw;
      h = s_sizes [i].gh;
   }
   /*---(curses)-------------------------*/
   else {
      w = s_sizes [i].cw;
      h = s_sizes [i].ch;
   }
   /*---(report-out)---------------------*/
   DEBUG_YVIEW   yLOG_sint    (w);
   DEBUG_YVIEW   yLOG_sint    (h);
   /*---(save-back)----------------------*/
   if (r_size != NULL)  *r_size = a_size;
   if (r_wide != NULL)  *r_wide = w;
   if (r_high != NULL)  *r_high = h;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_note__position    (char a_env, char a_part, char a_size, short *b_wide, short *b_high, char a_xr, char a_yr, char *r_part, char *r_xr, char *r_yr, short *r_x, short *r_y)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   short       x_left, x_wide, x_bott, x_tall;
   short       x_xlen, x_ylen;
   short       x, y;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_env"     , a_env);
   DEBUG_YVIEW   yLOG_char    ("a_part"    , a_part);
   /*---(defense)------------------------*/
   --rce;  if (b_wide == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (b_high == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(get environment)----------------*/
   yVIEW_size   (YVIEW_MAIN  , NULL, &x_left, &x_xlen, &x_bott, &x_ylen);
   yVIEW_size   (YVIEW_WINDOW, NULL, NULL   , &x_wide, NULL   , &x_tall);
   DEBUG_YVIEW   yLOG_complex  ("main"      , "%c, %4dl, %4dw, %4db, %4dt"  , YVIEW_MAIN  , x_left, x_xlen, x_bott, x_ylen);
   DEBUG_YVIEW   yLOG_complex  ("window"    , "%c,        %4dw,        %4dt", YVIEW_WINDOW, x_wide, x_tall);
   switch (a_part) {
   case YVIEW_WINDOW   :
      DEBUG_YVIEW   yLOG_note    ("window relative");
      x_left  = 0;
      if (a_env == YVIEW_OPENGL)  x_bott  = 0;
      else                        x_bott  = x_tall;
      x_tall++;
      x_wide++;
      break;
   case YVIEW_MAIN     :
      DEBUG_YVIEW   yLOG_note    ("main relative");
      x_wide  = x_xlen;
      x_tall  = x_ylen;
      break;
   }
   DEBUG_YVIEW   yLOG_complex  ("area"      , "%c, %4dl, %4dw, %4db, %4dt", a_part, x_left, x_wide, x_bott, x_tall);
   /*---(guidelines)---------------------*/
   if (a_size == '|') {
      DEBUG_YVIEW   yLOG_note    ("handle gridlines");
      x = x_left;
      if (myVIEW.env == YVIEW_OPENGL) y  = x_bott;
      else                            y  = x_bott - x_tall;
      *b_wide = x_wide;
      *b_high = x_tall;
      *r_xr   = '0';
      *r_yr   = '0';
      if (r_x    != NULL)  *r_x    = x;
      if (r_y    != NULL)  *r_y    = y;
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(vertical)-----------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_yr"      , a_yr);
   rc  = yview_note__y (a_env, x_bott, x_tall, *b_high, a_yr, &y);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("can not interpret a_yr");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_value   ("y"         , y);
   /*---(horizontal)---------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_xr"      , a_xr);
   rc  = yview_note__x (a_env, x_left, x_wide, *b_wide, a_xr, &x);
   if (rc < 0) {
      DEBUG_YVIEW   yLOG_note    ("can not interpret a_xr");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_value   ("x"         , x);
   /*---(save-back)----------------------*/
   if (r_part != NULL)  *r_part = a_part;
   if (r_xr   != NULL)  *r_xr   = a_xr;
   if (r_yr   != NULL)  *r_yr   = a_yr;
   if (r_x    != NULL)  *r_x    = x;
   if (r_y    != NULL)  *r_y    = y;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*> char                                                                                                                   <* 
 *> yview_note__size        (char n, char xr, char yr, char a_size)                                                        <* 
 *> {                                                                                                                      <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                                                            <* 
 *>    char        rce         =  -10;                                                                                     <* 
 *>    char        rc          =    0;                                                                                     <* 
 *>    short       x_left, x_wide, x_bott, x_tall;                                                                         <* 
 *>    short       x_xlen, x_ylen;                                                                                         <* 
 *>    char       *p           = NULL;                                                                                     <* 
 *>    int         l           =    0;                                                                                     <* 
 *>    int         c           =    0;                                                                                     <* 
 *>    float       a, b;                                                                                                   <* 
 *>    short       x, y;                                                                                                   <* 
 *>    /+---(header)-------------------------+/                                                                            <* 
 *>    DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);                                                                          <* 
 *>    /+---(get environment)----------------+/                                                                            <* 
 *>    DEBUG_YVIEW   yLOG_char    ("env"       , myVIEW.env);                                                              <* 
 *>    /+---(defaults)-----------------------+/                                                                            <* 
 *>    g_notes [n].size = '=';                                                                                             <* 
 *>    g_notes [n].s    = s_part;                                                                                          <* 
 *>    g_notes [n].xr   = '0';                                                                                             <* 
 *>    g_notes [n].x    = 0;                                                                                               <* 
 *>    g_notes [n].xb   = 0;                                                                                               <* 
 *>    g_notes [n].yr   = '0';                                                                                             <* 
 *>    g_notes [n].y    = 0;                                                                                               <* 
 *>    g_notes [n].xb   = 0;                                                                                               <* 
 *>    /+---(defense)------------------------+/                                                                            <* 
 *>    --rce;  if (strchr (YVIEW_ENVS, myVIEW.env) == NULL) {                                                              <* 
 *>       DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
 *>       return rce;                                                                                                      <* 
 *>    }                                                                                                                   <* 
 *>    DEBUG_YVIEW   yLOG_value   ("n"         , n);                                                                       <* 
 *>    --rce;  if (n < 0 || n >= MAX_NOTES) {                                                                              <* 
 *>       DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
 *>       return rce;                                                                                                      <* 
 *>    }                                                                                                                   <* 
 *>    /+---(size)---------------------------+/                                                                            <* 
 *>    switch (myVIEW.env) {                                                                                               <* 
 *>    case YVIEW_OPENGL :                                                                                                 <* 
 *>       switch (a_size) {  /+ single row/line    +/                                                                      <* 
 *>       case '.'  : g_notes [n].w =  20; g_notes [n].h =  20;  break; /+  2 chars +/                                     <* 
 *>       case ','  : g_notes [n].w =  80; g_notes [n].h =  20;  break; /+  9 chars +/                                     <* 
 *>       case ';'  : g_notes [n].w = 120; g_notes [n].h =  20;  break; /+ 15 chars +/                                     <* 
 *>       case ':'  : g_notes [n].w = 190; g_notes [n].h =  20;  break; /+ 25 chars +/                                     <* 
 *>       case '^'  : g_notes [n].w = 350; g_notes [n].h =  20;  break; /+ 56 chars +/                                     <* 
 *>       }                                                                                                                <* 
 *>       switch (a_size) {  /+ double row/line    +/                                                                      <* 
 *>       case '-'  : g_notes [n].w = 120; g_notes [n].h =  35;  break; /+ 15 chars +/                                     <* 
 *>       case ')'  : g_notes [n].w = 190; g_notes [n].h =  35;  break; /+ 25 chars +/                                     <* 
 *>       }                                                                                                                <* 
 *>       switch (a_size) {  /+ triple row/line    +/                                                                      <* 
 *>       case '!'  : g_notes [n].w = 155; g_notes [n].h =  48;  break; /+ 20 chars +/                                     <* 
 *>       case '='  : g_notes [n].w = 190; g_notes [n].h =  48;  break; /+ 25 chars +/                                     <* 
 *>       }                                                                                                                <* 
 *>       switch (a_size) {  /+ quadruple row/line    +/                                                                   <* 
 *>       case '+'  : g_notes [n].w = 250; g_notes [n].h =  62;  break; /+ 40 chars +/                                     <* 
 *>       }                                                                                                                <* 
 *>       break;                                                                                                           <* 
 *>    case YVIEW_CURSES :                                                                                                 <* 
 *>       switch (a_size) {  /+ single row/line    +/                                                                      <* 
 *>       case '.'  : g_notes [n].w =   3; g_notes [n].h =   1;  break;                                                    <* 
 *>       case ','  : g_notes [n].w =   9; g_notes [n].h =   1;  break;                                                    <* 
 *>       case ';'  : g_notes [n].w =  15; g_notes [n].h =   1;  break;                                                    <* 
 *>       case ':'  : g_notes [n].w =  25; g_notes [n].h =   1;  break;                                                    <* 
 *>       case '^'  : g_notes [n].w =  57; g_notes [n].h =   1;  break;                                                    <* 
 *>       }                                                                                                                <* 
 *>       switch (a_size) {  /+ double row/line    +/                                                                      <* 
 *>       case '-'  : g_notes [n].w =  15; g_notes [n].h =   2;  break;                                                    <* 
 *>       case ')'  : g_notes [n].w =  31; g_notes [n].h =   2;  break;                                                    <* 
 *>       }                                                                                                                <* 
 *>       switch (a_size) {  /+ triple row/line    +/                                                                      <* 
*>       case '!'  : g_notes [n].w =  19; g_notes [n].h =   3;  break;                                                    <* 
*>       case '='  : g_notes [n].w =  25; g_notes [n].h =   3;  break;                                                    <* 
*>       }                                                                                                                <* 
*>       switch (a_size) {  /+ quadruple row/line    +/                                                                   <* 
   *>       case '+'  : g_notes [n].w =  41; g_notes [n].h =   4;  break;                                                    <* 
      *>       }                                                                                                                <* 
      *>       break;                                                                                                           <* 
      *>    }                                                                                                                   <* 
      *>    DEBUG_YVIEW   yLOG_complex  ("size"      , "%4dw, %4dh", g_notes [n].w, g_notes [n].h);                             <* 
      *>    /+---(note window)--------------------+/                                                                            <* 
      *>    DEBUG_YVIEW   yLOG_char    ("a_size"    , a_size);                                                                  <* 
      *>    DEBUG_YVIEW   yLOG_info    ("s_valid"    , s_valid);                                                                <* 
      *>    --rce;  if (strchr (s_valid, a_size) == NULL) {                                                                     <* 
         *>       DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
            *>       return rce;                                                                                                      <* 
            *>    }                                                                                                                   <* 
            *>    yVIEW_size   (YVIEW_MAIN  , NULL, &x_left, &x_xlen, &x_bott, &x_ylen);                                              <* 
            *>    yVIEW_size   (YVIEW_WINDOW, NULL, NULL   , &x_wide, NULL   , &x_tall);                                              <* 
            *>    switch (s_part) {                                                                                                   <* 
               *>    case YVIEW_WINDOW   :                                                                                               <* 
                  *>       x_left  = 0;                                                                                                     <* 
                  *>       if (myVIEW.env == YVIEW_OPENGL)  x_bott  = 0;                                                                    <* 
                  *>       else                             x_bott  = x_tall - 1;                                                           <* 
                  *>       break;                                                                                                           <* 
                  *>    case YVIEW_MAIN     :                                                                                               <* 
                  *>       x_wide  = x_xlen;                                                                                                <* 
                  *>       x_tall  = x_ylen;                                                                                                <* 
                  *>       break;                                                                                                           <* 
                  *>    }                                                                                                                   <* 
                  *>    if (myVIEW.env == YVIEW_CURSES)  x_bott += 1;                                                                       <* 
                  *>    DEBUG_YVIEW   yLOG_complex  ("area"      , "%c, %4dl, %4dw, %4db, %4dt", s_part, x_left, x_wide, x_bott, x_tall);   <* 
                  *>    if (a_size == '|') {                                                                                                <* 
                     *>       g_notes [n].x    = x_left;                                                                                       <* 
                        *>       g_notes [n].w    = x_wide;                                                                                       <* 
                        *>       g_notes [n].h    = x_tall;                                                                                       <* 
                        *>       g_notes [n].size = a_size;                                                                                       <* 
                        *>       if (myVIEW.env == YVIEW_OPENGL) g_notes [n].y    = x_bott;                                                       <* 
                        *>       else                            g_notes [n].y    = x_bott - x_tall - 1;                                          <* 
                        *>       DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                                                       <* 
                        *>       return 0;                                                                                                        <* 
                        *>    }                                                                                                                   <* 
                        *>    /+---(vertical)-----------------------+/                                                                            <* 
                        *>    DEBUG_YVIEW   yLOG_value   ("yr"        , yr);                                                                      <* 
                        *>    rc  = yview_note__y (myVIEW.env, x_bott, x_tall, g_notes [n].h, yr, &y);                                            <* 
                        *>    if (rc < 0) {                                                                                                       <* 
                           *>       DEBUG_YVIEW   yLOG_note    ("can not interpret yr");                                                             <* 
                              *>       DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
                              *>       return rce;                                                                                                      <* 
                              *>    }                                                                                                                   <* 
                              *>    /+---(horizontal)---------------------+/                                                                            <* 
                              *>    DEBUG_YVIEW   yLOG_value   ("xr"        , xr);                                                                      <* 
                              *>    rc = yview_note__x (myVIEW.env, x_left, x_wide, g_notes [n].w, xr, &x);                                             <* 
                              *>    if (rc < 0) {                                                                                                       <* 
                                 *>       DEBUG_YVIEW   yLOG_note    ("can not interpret xr");                                                             <* 
                                    *>       DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                                                                  <* 
                                    *>       return rce;                                                                                                      <* 
                                    *>    }                                                                                                                   <* 
                                    *>    /+---(save values)--------------------+/                                                                            <* 
                                    *>    g_notes [n].size = a_size;                                                                                          <* 
                                    *>    g_notes [n].xr   = xr;                                                                                              <* 
                                    *>    g_notes [n].x    = x;                                                                                               <* 
                                    *>    g_notes [n].yr   = yr;                                                                                              <* 
                                    *>    g_notes [n].y    = y;                                                                                               <* 
                                    *>    /+---(complete)-----------------------+/                                                                            <* 
                                    *>    DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                                                          <* 
                                    *>    return 0;                                                                                                           <* 
                                    *> }                                                                                                                      <*/

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
   yVIEW_bounds (YVIEW_MAIN, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);
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
   yVIEW_bounds (YVIEW_MAIN, NULL, NULL, &x_left, NULL, &x_wide, &x_bott, NULL, &x_tall);
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
yview_note__end         (char a_type, char a_xt, char a_yt, char *r_scope, short *r_xe, short *r_ye)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   short       x_left, x_wide, x_bott, x_tall;
   char        s           =  '-';
   float       x_nudge     =  0.0;
   short       xe          =    0;
   short       ye          =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(get full size)------------------*/
   DEBUG_YVIEW   yLOG_note    ("curses environment");
   if (strchr ("‘’◊÷", a_type) != NULL) {
      DEBUG_YVIEW   yLOG_note    ("main window type");
      yVIEW_size   (YVIEW_MAIN  , NULL, &x_left, &x_wide, &x_bott, &x_tall);
      s = YVIEW_MAIN;
   } else {
      DEBUG_YVIEW   yLOG_note    ("full window type");
      yVIEW_size   (YVIEW_WINDOW, NULL, &x_left, &x_wide, &x_bott, &x_tall);
      s = YVIEW_WINDOW;
   }
   /*---(calc target)-----------------*/
   if (myVIEW.env == YVIEW_OPENGL)  x_nudge = x_wide * 0.015;
   rc = yview_note__x (myVIEW.env, x_left + x_nudge, x_wide - x_nudge * 2.0, 0, a_xt, &xe);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_char    ("xt fail"   , a_xt);
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (myVIEW.env == YVIEW_OPENGL)  x_nudge = x_tall * 0.015;
   rc = yview_note__y (myVIEW.env, x_bott + x_nudge, x_tall - x_nudge * 2.0, 0, a_yt, &ye);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_char    ("yt fail"   , a_yt);
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_complex ("target"    , "%4dx, %4dy", xe, ye);
   /*---(save-back)----------------------*/
   if (r_scope != NULL)  *r_scope = s;
   if (r_xe    != NULL)  *r_xe    = xe;
   if (r_ye    != NULL)  *r_ye    = ye;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

/*
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
 *                          å  auto å
 *                     7/8  å  8/1  å  1/2
 *                          å       å
 *                  ≤≤≤≤≤≤≤≤äÄÄÄÄÄÄÄä≤≤≤≤≤≤≤≤
 *                          å       å
 *                     7/6  å nunca å  2/3
 *                    auto  å       å  auto
 *                  ≤≤≤≤≤≤≤≤äÄÄÄÄÄÄÄä≤≤≤≤≤≤≤≤
 *                          å       å
 *                     6/5  å  5/4  å  3/4
 *                          å  auto å
 *
 *
 */

char
yview_note__quad        (short a_x, short a_y, short a_wide, short a_tall, short a_xe, short a_ye, char *r_quad, short *r_cen, short *r_mid)
{
   /*---(locals)-----------+-----+-----+-*/
   short       xd, yd;
   char        x_quad      =  '-';
   short       x_rig, x_bot;
   char        qx          =    0;
   char        qy          =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(prepare)------------------------*/
   x_rig = a_x + a_wide;
   x_bot = a_y + a_tall;
   DEBUG_YVIEW   yLOG_complex ("cut-offs"  , "%4dx, %4dy, %4dw, %4dt, %4dr, %4db", a_x, a_y, a_wide, a_tall, x_rig, x_bot);
   /*---(x-quad)-------------------------*/
   if       (a_xe <  a_x)         qx = 1;
   else if  (a_xe <  x_rig)       qx = 2;
   else                           qx = 3;
   DEBUG_YVIEW   yLOG_complex ("x-quad"    , "%4dx, %d", a_xe, qx);
   /*---(x-quad)-------------------------*/
   if       (a_ye <  a_y)         qy = 1;
   else if  (a_ye <  x_bot)       qy = 2;
   else                           qy = 3;
   DEBUG_YVIEW   yLOG_complex ("y-quad"    , "%4dy, %d", a_ye, qy);
   /*---(combo)--------------------------*/
   switch (qx) {
   case 1 :
      switch (qy) {
      case 1  : x_quad = '1';      break;
      case 2  : x_quad = '4';      break;
      case 3  : x_quad = '7';      break;
      }
      break;
   case 2 :
      switch (qy) {
      case 1  : x_quad = '2';      break;
      case 2  : x_quad = '5';      break;
      case 3  : x_quad = '8';      break;
      }
      break;
   case 3 :
      switch (qy) {
      case 1  : x_quad = '3';      break;
      case 2  : x_quad = '6';      break;
      case 3  : x_quad = '9';      break;
      }
      break;
   }
   DEBUG_YVIEW   yLOG_char    ("x_quad"    , x_quad);
   /*---(save-back)----------------------*/
   if (r_quad  != NULL)  *r_quad  = x_quad;
   if (r_cen   != NULL)  *r_cen   = a_x + 0.5 * (a_wide - 1);
   if (r_mid   != NULL)  *r_mid   = a_y + 0.5 * (a_tall - 1);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__dir_OLD     (char a_type, short a_x, short a_y, short a_wide, short a_tall, short a_xe, short a_ye, char *r_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   short       xd, yd;
   char        x_dir       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_type"    , a_type);
   if (myVIEW.env == YVIEW_CURSES) {
      DEBUG_YVIEW   yLOG_note    ("curses quadrents");
      xd = a_x + (a_wide * 0.5) - a_xe;
      yd = a_y - (a_tall * 0.5) - a_ye;
      DEBUG_YVIEW   yLOG_complex ("diff"      , "%4dx, %4dy", xd, yd);
      if (strchr ("‘’àâ", a_type) != NULL) {
         if (xd < 0) {
            if (yd < 0)  x_dir = '4';
            else         x_dir = '1';
         } else {
            if (yd < 0)  x_dir = '5';
            else         x_dir = '8';
         }
      } else {
         if (xd < 0) {
            if (yd < 0)  x_dir = '3';
            else         x_dir = '2';
         } else {
            if (yd < 0)  x_dir = '6';
            else         x_dir = '7';
         }
      }
   } else {
      DEBUG_YVIEW   yLOG_note    ("opengl quadrents");
      xd = a_xe - a_x;
      yd = a_ye - a_y;
      DEBUG_YVIEW   yLOG_complex ("diff"      , "%4dx, %4dy", xd, yd);
      if (strchr ("‘’àâ", a_type) != NULL) {
         if (xd > 0) {
            if (yd < 0)  x_dir = '4';
            else         x_dir = '1';
         } else {
            if (yd < 0)  x_dir = '5';
            else         x_dir = '8';
         }
      } else {
         if (xd > 0) {
            if (yd < 0)  x_dir = '3';
            else         x_dir = '2';
         } else {
            if (yd < 0)  x_dir = '6';
            else         x_dir = '7';
         }
      }
   }
   DEBUG_YVIEW   yLOG_char    ("x_dir"    , x_dir);
   /*---(save-back)----------------------*/
   if (r_dir  != NULL)  *r_dir  = x_dir;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__dir         (char a_type, char a_quad, short a_cen, short a_mid, short a_xe, short a_ye, char *r_dir)
{
   /*---(locals)-----------+-----+-----+-*/
   short       xd, yd;
   char        x_dir       =  '-';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_type"    , a_type);
   DEBUG_YVIEW   yLOG_char    ("a_quad"    , a_quad);
   /*---(no line area)-------------------*/
   switch (a_quad) {
   case '5' :
      x_dir = 'H';  /* H for hidden */
      break;
   }
   /*---(automatic)----------------------*/
   switch (a_quad) {
   case '2' :
      if (a_xe <= a_cen)  x_dir = '8';
      else                x_dir = '1';
      break;
   case '4' :
      if (a_ye >= a_mid)  x_dir = '6';
      else                x_dir = '7';
      break;
   case '6' :
      if (a_ye >= a_mid)  x_dir = '3';
      else                x_dir = '2';
      break;
   case '8' :
      if (a_xe <= a_cen)  x_dir = '5';
      else                x_dir = '4';
      break;
   }
   /*---(automatic)----------------------*/
   switch (a_quad) {
   case '1' :
      if (strchr ("◊÷áÜ", a_type) != NULL)   x_dir = '7';
      else                                   x_dir = '8';
      break;
   case '3' :
      if (strchr ("◊÷áÜ", a_type) != NULL)   x_dir = '2';
      else                                   x_dir = '1';
      break;
   case '7' :
      if (strchr ("◊÷áÜ", a_type) != NULL)   x_dir = '6';
      else                                   x_dir = '5';
      break;
   case '9' :
      if (strchr ("◊÷áÜ", a_type) != NULL)   x_dir = '3';
      else                                   x_dir = '4';
      break;
   }
   /*---(save-back)----------------------*/
   DEBUG_YVIEW   yLOG_char    ("x_dir"    , x_dir);
   if (r_dir  != NULL)  *r_dir  = x_dir;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note__begin       (char n, char a_dir, short x_cen, short x_mid, short *r_xb, short *r_yb)
{
   /*---(locals)-----------+-----+-----+-*/
   short       xb          =    0;
   short       yb          =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(switch on type)-----------------*/
   DEBUG_YVIEW   yLOG_char    ("a_dir"     , a_dir);
   switch (a_dir) {
   case '1' :
      DEBUG_YVIEW   yLOG_note    ("1 type -- up and right");
      yb = g_notes [n].y - 1;
      xb = x_cen;
      break;
   case '2' :
      DEBUG_YVIEW   yLOG_note    ("2 type -- right and up");
      yb = x_mid;
      xb = g_notes [n].x + g_notes [n].w;
      break;
   case '3' :
      DEBUG_YVIEW   yLOG_note    ("3 type -- right and down");
      yb = x_mid;
      xb = g_notes [n].x + g_notes [n].w;
      break;
   case '4' :
      DEBUG_YVIEW   yLOG_note    ("4 type -- down and right");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h;
      else                             yb = g_notes [n].y + g_notes [n].h;
      xb = x_cen;
      break;
   case '5' :
      DEBUG_YVIEW   yLOG_note    ("5 type -- down and left");
      if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h;
      else                             yb = g_notes [n].y + g_notes [n].h;
      xb = x_cen;
      break;
   case '6' :
      DEBUG_YVIEW   yLOG_note    ("6 type -- left and down");
      yb = x_mid;
      xb = g_notes [n].x - 1;
      break;
   case '7' :
      DEBUG_YVIEW   yLOG_note    ("7 type -- left and up");
      yb = x_mid;
      xb = g_notes [n].x - 1;
      break;
   case '8' :
      DEBUG_YVIEW   yLOG_note    ("8 type -- up and right");
      yb = g_notes [n].y - 1;
      xb = x_cen;
      break;
   }
   DEBUG_YVIEW   yLOG_complex ("begin"     , "%4dx, %4dy", xb, yb);
   /*---(save-back)----------------------*/
   if (r_xb != NULL)  *r_xb = xb;
   if (r_yb != NULL)  *r_yb = yb;
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
   char        x_quad      =  '0';
   char        x_dir       =  '0';
   short       xt          =  '-';
   short       yt          =  '-';
   short       xb, yb;
   short       xe, ye;
   short       x_left, x_wide, x_bott, x_tall;
   short       xd, yd;
   char        s           =  '-';
   float       x_nudge     =  0.0;
   short       x_cen, x_mid;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defaults)-----------------------*/
   yview_note__untarget (n);
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
   rc = yview_note__end   (x_type, xt, yt, &s, &xe, &ye);
   DEBUG_YVIEW   yLOG_value   ("end"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   rc = yview_note__quad  (g_notes [n].x, g_notes [n].y, g_notes [n].w, g_notes [n].h, xe, ye, &x_quad, &x_cen, &x_mid);
   DEBUG_YVIEW   yLOG_value   ("x_quad"    , x_quad);
   /*---(get diffs)-------------------*/
   /*> if (myVIEW.env == YVIEW_CURSES) {                                              <* 
    *>    DEBUG_YVIEW   yLOG_note    ("curses quadrents");                            <* 
    *>    xd = g_notes [n].x - xe;                                                    <* 
    *>    yd = g_notes [n].y - ye;                                                    <* 
    *>    DEBUG_YVIEW   yLOG_complex ("diff"      , "%4dx, %4dy", xd, yd);            <* 
    *>    if (strchr ("‘’àâ", x_type) != NULL) {                                      <* 
    *>       if (xd < 0) {                                                            <* 
    *>          if (yd < 0)  x_type = '4';                                            <* 
    *>          else         x_type = '1';                                            <* 
    *>       } else {                                                                 <* 
    *>          if (yd < 0)  x_type = '5';                                            <* 
    *>          else         x_type = '8';                                            <* 
    *>       }                                                                        <* 
    *>    } else {                                                                    <* 
    *>       if (xd < 0) {                                                            <* 
    *>          if (yd < 0)  x_type = '3';                                            <* 
    *>          else         x_type = '2';                                            <* 
    *>       } else {                                                                 <* 
    *>          if (yd < 0)  x_type = '6';                                            <* 
    *>          else         x_type = '7';                                            <* 
    *>       }                                                                        <* 
    *>    }                                                                           <* 
    *> } else {                                                                       <* 
    *>    DEBUG_YVIEW   yLOG_note    ("opengl quadrents");                            <* 
    *>    xd = xe - g_notes [n].x;                                                    <* 
    *>    yd = ye - g_notes [n].y;                                                    <* 
    *>    DEBUG_YVIEW   yLOG_complex ("diff"      , "%4dx, %4dy", xd, yd);            <* 
    *>    if (strchr ("‘’àâ", x_type) != NULL) {                                      <* 
    *>       if (xd > 0) {                                                            <* 
    *>          if (yd < 0)  x_type = '4';                                            <* 
    *>          else         x_type = '1';                                            <* 
    *>       } else {                                                                 <* 
    *>          if (yd < 0)  x_type = '5';                                            <* 
    *>          else         x_type = '8';                                            <* 
    *>       }                                                                        <* 
    *>    } else {                                                                    <* 
    *>       if (xd > 0) {                                                            <* 
    *>          if (yd < 0)  x_type = '3';                                            <* 
    *>          else         x_type = '2';                                            <* 
    *>       } else {                                                                 <* 
    *>          if (yd < 0)  x_type = '6';                                            <* 
    *>          else         x_type = '7';                                            <* 
    *>       }                                                                        <* 
    *>    }                                                                           <* 
    *> }                                                                              <*/
   /*> DEBUG_YVIEW   yLOG_char    ("x_type"    , x_type);                             <*/
   rc = yview_note__dir   (x_type, x_quad, x_cen, x_mid, xe, ye, &x_dir);
   DEBUG_YVIEW   yLOG_value   ("x_dir"     , x_dir);
   /*---(set)-------------------------*/
   /*> switch (x_type) {                                                                             <* 
    *> case '1' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("1 type -- up and right");                                     <* 
    *>    yb = g_notes [n].y - 1;                                                                    <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));       <* 
    *>    else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));   <* 
    *>    break;                                                                                     <* 
    *> case '2' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("2 type -- right and up");                                     <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;                 <* 
    *>    else                             yb = g_notes [n].y;                                       <* 
    *>    xb = g_notes [n].x + g_notes [n].w;                                                        <* 
    *>    break;                                                                                     <* 
    *> case '3' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("3 type -- right and down");                                   <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;                 <* 
    *>    else                             yb = g_notes [n].y + g_notes [n].h - 1;                   <* 
    *>    xb = g_notes [n].x + g_notes [n].w;                                                        <* 
    *>    break;                                                                                     <* 
    *> case '4' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("4 type -- down and right");                                   <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h;                       <* 
    *>    else                             yb = g_notes [n].y + g_notes [n].h;                       <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));       <* 
    *>    else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));   <* 
    *>    break;                                                                                     <* 
    *> case '5' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("5 type -- down and left");                                    <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h;                       <* 
    *>    else                             yb = g_notes [n].y + g_notes [n].h;                       <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));       <* 
    *>    else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));   <* 
    *>    break;                                                                                     <* 
    *> case '6' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("6 type -- left and up");                                      <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;                 <* 
    *>    else                             yb = g_notes [n].y + g_notes [n].h - 1;                   <* 
    *>    xb = g_notes [n].x - 1;                                                                    <* 
    *>    break;                                                                                     <* 
    *> case '7' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("7 type -- left and up");                                      <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  yb = g_notes [n].y - g_notes [n].h / 2.0;                 <* 
    *>    else                             yb = g_notes [n].y;                                       <* 
    *>    xb = g_notes [n].x - 1;                                                                    <* 
    *>    break;                                                                                     <* 
    *> case '8' :                                                                                    <* 
    *>    DEBUG_YVIEW   yLOG_note    ("8 type -- up and right");                                     <* 
    *>    yb = g_notes [n].y - 1;                                                                    <* 
    *>    if (myVIEW.env == YVIEW_OPENGL)  xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w));       <* 
    *>    else                             xb = g_notes [n].x + trunc (0.5 * (g_notes [n].w - 1));   <* 
    *>    break;                                                                                     <* 
    *> }                                                                                             <*/
   rc = yview_note__begin (n, x_dir, x_cen, x_mid, &xb, &yb);
   DEBUG_YVIEW   yLOG_value   ("x_dir"     , x_dir);
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
      g_notes [n].st   = s;
      g_notes [n].xt   = xt;
      g_notes [n].yt   = yt;
      g_notes [n].xb   = xb;
      g_notes [n].yb   = yb;
      g_notes [n].xe   = xe;
      g_notes [n].ye   = ye;
      g_notes [n].q    = x_quad;
      g_notes [n].c    = x_dir;
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
   char        t           [LEN_RECD]  = "";
   char        s           [LEN_TERSE] = "";
   char       *v           = NULL;
   char       *p           = NULL;
   int         l           =    0;
   char        n           =   -1;
   char        x_leave     =  '-';
   char        x_dir       =  '÷';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_point   ("a_text"    , a_text);
   --rce;  if (a_text == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   l = strlen (a_text);
   DEBUG_YVIEW   yLOG_value   ("l"         , l);
   --rce;  if (strchr ("|¥", a_size) == NULL && l == 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   if (a_size == '|')  strlcpy (x_text, "guidelines", LEN_RECD);
   else                strlcpy (x_text, a_text, LEN_RECD);
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
      DEBUG_YVIEW   yLOG_note    ("check for targeting");
      DEBUG_YVIEW   yLOG_info    ("p"         , p);
      l = strlen (p);
      DEBUG_YVIEW   yLOG_complex ("prefix"    , "%d %c", l, p [1]);
      if (l == 5 && p [1] == '·' && strchr (s_targ, p [2]) != NULL)  {
         DEBUG_YVIEW   yLOG_note    ("found full window target");
         p [1] = '\0';
         --l;
         ++p;
         switch (p [1]) {
         case '÷'  :  p [1] = 'á';  break;
         case '’'  :  p [1] = 'â';  break;
         case '◊'  :  p [1] = 'Ü';  break;
         case '‘'  :  p [1] = 'à';  break;
         }
      }
      DEBUG_YVIEW   yLOG_complex ("prefix"    , "%d %c", l, p [1]);
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
   if (strchr ("&¥", a_size) == NULL) {
      rc = yview_note__sizer    (myVIEW.env, a_size, &(g_notes [n].size), &(g_notes [n].w), &(g_notes [n].h));
      DEBUG_YVIEW   yLOG_value   ("sizer"     , rc);
      --rce;  if (rc < 0) {
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      rc = yview_note__position (myVIEW.env, a_part, a_size, &(g_notes [n].w), &(g_notes [n].h), a_xr, a_yr, &(g_notes [n].s), &(g_notes [n].xr), &(g_notes [n].yr), &(g_notes [n].x), &(g_notes [n].y));
      DEBUG_YVIEW   yLOG_value   ("position"  , rc);
      --rce;  if (rc < 0) {
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      /*> g_notes [n].s  = a_part;                                                    <* 
       *> g_notes [n].xr = a_xr;                                                      <* 
       *> g_notes [n].yr = a_yr;                                                      <*/
   } 
   /*---(check text)---------------------*/
   strltrim (x_text, ySTR_BOTH, LEN_RECD);
   l = strlen (x_text);
   DEBUG_YVIEW   yLOG_complex ("text"      , "%2d Â%sÊ", l, x_text);
   if (a_size != '|' && v == NULL && l > 1 && x_text [l - 1] == '¥') {
      DEBUG_YVIEW   yLOG_note    ("leave targeting alone");
      x_leave = 'y';
      x_text [l - 1] = '\0';
      strltrim (x_text, ySTR_BOTH, LEN_RECD);
      l = strlen (x_text);
      switch (g_notes [n].c) {
      case '2' : case '3' : x_dir = '÷';  break;
      case '4' : case '5' : x_dir = '’';  break;
      case '6' : case '7' : x_dir = '◊';  break;
      case '8' : case '1' : x_dir = '‘';  break;
      }
      if (g_notes [n].st == YVIEW_MAIN) {
         sprintf (s, "%c%c%c", x_dir, g_notes [n].xt, g_notes [n].yt);
      } else {
         sprintf (s, "·%c%c%c", x_dir, g_notes [n].xt, g_notes [n].yt);
      }
      DEBUG_YVIEW   yLOG_info    ("s"         , s);
      v = s;
   }
   /*---(update text)--------------------*/
   --rce;  if (a_size == '&' && l > 0) {
      DEBUG_YVIEW   yLOG_note    ("concatinate text");
      DEBUG_YVIEW   yLOG_point   ("text"      , g_notes [n].text);
      if (g_notes [n].text != NULL) {
         sprintf (t, "%s %s", g_notes [n].text, x_text);
         strlcpy (x_text, t, LEN_RECD);
      }
   }
   else if (strcmp (x_text, "") != 0) {
      DEBUG_YVIEW   yLOG_note    ("replace text");
      DEBUG_YVIEW   yLOG_point   ("text"      , g_notes [n].text);
      if (g_notes [n].text != NULL)  free (g_notes [n].text);
      g_notes [n].text = strdup (x_text);
   }
   if (n == g_nnote)  ++g_nnote;
   rc = yview_note__totop   (n);
   n = g_nnote - 1;
   /*---(targeting)----------------------*/
   /*> yview_note__untarget (n);                                                      <*/
   if (v == NULL) {
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   DEBUG_YVIEW   yLOG_note    ("set target");
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
yview_note_update       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         n           =    0;
   char        t           [LEN_LABEL] = "";
   char        s           =  '-';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(walk)---------------------------*/
   for (n = 0; n < g_nnote; ++n) {
      s_part = g_notes [n].s;
      /*> yview_note__size    (n, g_notes [n].xr, g_notes [n].yr, g_notes [n].size);   <*/
      yview_note__position (myVIEW.env, g_notes [n].s, g_notes [n].size, &(g_notes [n].w), &(g_notes [n].h), g_notes [n].xr, g_notes [n].yr, NULL, NULL, NULL, &(g_notes [n].x), &(g_notes [n].y));
      if (g_notes [n].st == YVIEW_MAIN) {
         switch (g_notes [n].c) {
         case '2' : case '3' :    s = '÷';   break;
         case '4' : case '5' :    s = '’';   break;
         case '6' : case '7' :    s = '◊';   break;
         case '8' : case '1' :    s = '‘';   break;
         default             :    s = g_notes [n].c;  break;
         }
      } else {
         switch (g_notes [n].c) {
         case '2' : case '3' :    s = 'á';   break;
         case '4' : case '5' :    s = 'â';   break;
         case '6' : case '7' :    s = 'Ü';   break;
         case '8' : case '1' :    s = 'à';   break;
         default             :    s = g_notes [n].c;  break;
         }
      }
      sprintf (t, "%c%c%c", s, g_notes [n].xt, g_notes [n].yt);
      DEBUG_YVIEW   yLOG_complex ("settarg"   , "%c, %c, %c, %s, %c, %c", g_notes [n].c, g_notes [n].st, s, t, g_notes [n].xt, g_notes [n].yt);
      yview_note__settarg (n, t);
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
      case '|'  :
         DEBUG_YVIEW   yLOG_note    ("show note guidelines");
         yview_note_add (a_part, '0', '0', '|', "");
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
         /*> default  :                                                                  <* 
          *>    rc = yview_note_add (a_part, xr, yr, x_size, u);                         <* 
          *>    DEBUG_YVIEW   yLOG_note    ("unknown triple char option");               <* 
          *>    DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                          <* 
          *>    return rce;                                                              <* 
          *>    break;                                                                   <*/
      }
   }
   /*---(prepare)------------------------*/
   x_size = a_all [2];
   strlcpy (u, a_all + 3, LEN_RECD);
   /*---(triples)------------------------*/
   --rce;  if (x_len == 5) {
      if (a_all [2] == '>') {
         if (n <  0) {
            DEBUG_YVIEW   yLOG_note    ("note not found for moving");
            DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
            return rce;
         }
         rc = yview_note__move   (n, u [0], u [1]);
         if (rc >= 0)  yview_note__totop   (n);
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return rc;
      } else {
         if (strncmp (a_all, "ln", 2) == 0) {
            rc = yview_note_line  (a_all [3], a_all [4]);
            DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
            return rc;
         }
         if (strncmp (a_all, "bg", 2) == 0) {
            rc = yview_note_notes (a_all [3], a_all [4]);
            DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
            return rc;
         }
      }
   }
   /*---(configuration)------------------*/
   /*> --rce;  if (strncmp (a_all, "fg", 5) == 0) {                                   <* 
    *>    if (strchr ("wrgybpoc", a_all [3]                                           <* 
    *>    myVIEW.note_line = a_all [3];                                               <* 
    *>    DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                  <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*> --rce;  if (strncmp (a_all, "bg", 5) == 0) {                                   <* 
    *>    myVIEW.note_line = a_all [6];                                               <* 
    *>    DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                  <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*> --rce;  if (strncmp (a_all, "bg", 2) == 0) {                                   <* 
    *>    if (strchr ("wrgybpocWRGYBPOC", a_all [3]) == NULL) {                       <* 
    *>       DEBUG_YVIEW   yLOG_note    ("line color not ÂwrgybpocWRGYBPOCÊ");        <* 
    *>       DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);                          <* 
    *>       return rce;                                                              <* 
    *>    }                                                                           <* 
    *>    myVIEW.note_curr = a_all [3];                                               <* 
    *>    DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);                                  <* 
    *>    return 0;                                                                   <* 
    *> }                                                                              <*/
   /*---(add a note)---------------------*/
   yVIEW_notes_debug  ();
   rc = yview_note_add (a_part, xr, yr, x_size, u);
   DEBUG_YVIEW   yLOG_value   ("add"       , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yVIEW_notes_debug  ();
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
yVIEW_note_data         (char n, uchar *m, uchar *s, short *x, short *y, short *w, short *h, uchar t [LEN_HUND], uchar *c, short *xb, short *yb, short *xe, short *ye)
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

char
yview_note_line          (char a_curr, char a_prev)
{
   char        rce         =  -10;
   --rce;  if (strchr ("~" YSTR_COLORS, a_curr)  == NULL) {
      DEBUG_YVIEW   yLOG_note    ("line curr color not Â~wrgybpocWRGYBPOCÊ"); 
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr ("~" YSTR_COLORS "-:", a_prev) == NULL) {
      DEBUG_YVIEW   yLOG_note    ("line prev color not Â~wrgybpocWRGYBPOC-:Ê"); 
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   switch (a_curr) {
   case '~'  :
      myVIEW.note_lcurr = 'Y';
      break;
   default   :
      myVIEW.note_lcurr = a_curr;
      break;
   }
   switch (a_prev) {
   case '~'  :
      myVIEW.note_lprev = 'Y';
      break;
   case '-'  :
      myVIEW.note_lprev = tolower (myVIEW.note_lcurr);
      myVIEW.note_lcurr = toupper (myVIEW.note_lcurr);
      break;
   default   :
      myVIEW.note_lprev = a_prev;
      break;
   }
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_note_notes         (char a_curr, char a_prev)
{
   char        rce         =  -10;
   --rce;  if (strchr ("~" YSTR_COLORS, a_curr)  == NULL) {
      DEBUG_YVIEW   yLOG_note    ("note curr color not Â~wrgybpocWRGYBPOCÊ"); 
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (strchr ("~" YSTR_COLORS "-", a_prev) == NULL) {
      DEBUG_YVIEW   yLOG_note    ("note prev color not Â~wrgybpocWRGYBPOC-Ê"); 
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   switch (a_curr) {
   case '~'  :
      myVIEW.note_curr = 'Y';
      break;
   default   :
      myVIEW.note_curr = toupper (a_curr);
      break;
   }
   switch (a_prev) {
   case '~'  :
      myVIEW.note_prev = 'y';
      break;
   case '-'  :
      myVIEW.note_prev = tolower (myVIEW.note_curr);
      break;
   default   :
      myVIEW.note_prev = toupper (a_prev);
      break;
   }
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_note_colors (char *a_curr, char *a_prev, char *a_lcurr, char *a_lprev)
{
   if (a_curr  != NULL)  *a_curr  = myVIEW.note_curr;
   if (a_prev  != NULL)  *a_prev  = myVIEW.note_prev;
   if (a_lcurr != NULL)  *a_lcurr = myVIEW.note_lcurr;
   if (a_lprev != NULL)  *a_lprev = myVIEW.note_lprev;
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
      if (n < 0 || n >= MAX_NOTES)    snprintf (unit_answer, LEN_FULL, "NOTE entry  (%2s) : ∑ ∑ ∑    ∑x    ∑y   ∑w  ∑h  ∑ÂÊ                   ∑,   ∑  ∑ ∑    ∑        ∑,   ∑", "--");
      else if (g_notes [n].xr == '∑') snprintf (unit_answer, LEN_FULL, "NOTE entry  (%2d) : ∑ ∑ ∑    ∑x    ∑y   ∑w  ∑h  ∑ÂÊ                   ∑,   ∑  ∑ ∑    ∑        ∑,   ∑", n);
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
