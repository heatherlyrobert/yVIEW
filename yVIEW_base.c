/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



tMY         myVIEW;


static char   (*s_cursor)  (void) = NULL;
static char   (*s_cleanse) (void) = NULL;
static char   (*s_prep)    (char) = NULL;
static char   (*s_refresh) (void) = NULL;



/*====================------------------------------------====================*/
/*===----                           utility                            ----===*/
/*====================------------------------------------====================*/
static void      o___UTILITY_________________o (void) {;}

char        yVIEW_ver [200] = "";

char*        /*--> return library versioning info --------[ leaf-- [ ------ ]-*/
yVIEW_version           (void)
{
   char        t [20] = "";
#if    __TINYC__ > 0
   strncpy (t, "[tcc built  ]", 15);
#elif  __GNUC__  > 0
   strncpy (t, "[gnu gcc    ]", 15);
#elif  __HEPH__  > 0
   strncpy (t, "[hephaestus ]", 15);
#else
   strncpy (t, "[unknown    ]", 15);
#endif
   snprintf (yVIEW_ver, 100, "%s   %s : %s", t, P_VERNUM, P_VERTXT);
   return yVIEW_ver;
}



/*====================------------------------------------====================*/
/*===----                        program level                         ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yview_init              (void)
{
   yview_parts_init   ();
   yview_layout_init  ();
   s_cleanse  = NULL;
   s_prep     = NULL;
   s_cursor   = NULL;
   s_refresh  = NULL;
   yview_note_init    ();
   return 0;
}

char
yVIEW_wrap              (void)
{
   return 0;
}

char
yVIEW_init              (char a_env, char *a_title, char *a_ver, void *a_cleanse, void *a_prep, void *a_cursor, void *a_refresh)
{
   /*---(design notes)-------------------*/
   /*
    *  NO end-application calls this function.
    *
    *  the end-application calles yVICU_init() or yVIGL_init() with in-turn
    *  calls this function with the relavent data and pointers.
    */
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (!yMODE_check_prep  (FMOD_VIEW)) {
      DEBUG_YVIEW   yLOG_note    ("status is not ready for init");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(globals)------------------------*/
   myVIEW.env       = a_env;
   myVIEW.prog_full = '-';
   yview_init ();
   /*---(defaults)-----------------------*/
   rc = yview_factory (a_env);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(content)------------------------*/
   if (a_title != NULL)    yview_conf_text (YVIEW_TITLE  , a_title);
   if (a_ver   != NULL)    yview_conf_text (YVIEW_VERSION, a_ver);
   yVIEW_keys ("  ··");
   yVIEW_modes (yMODE_text ());
   /*---(cleanse)------------------------*/
   DEBUG_YVIEW   yLOG_point   ("a_cleanse" , a_cleanse);
   --rce;  if (a_cleanse == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_cleanse = a_cleanse;
   /*---(prep)---------------------------*/
   DEBUG_YVIEW   yLOG_point   ("a_prep"    , a_prep);
   --rce;  if (a_prep    == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_prep    = a_prep;
   /*---(cursor)-------------------------*/
   if (a_env == YVIEW_CURSES) {
      DEBUG_YVIEW   yLOG_point   ("a_cursor"  , a_cursor);
      --rce;  if (a_cursor  == NULL) {
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      s_cursor  = a_cursor;
   }
   /*---(refresh)------------------------*/
   DEBUG_YVIEW   yLOG_point   ("a_refresh" , a_refresh);
   --rce;  if (a_refresh == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   s_refresh = a_refresh;
   /*---(update status)------------------*/
   yMODE_init_set (FMOD_VIEW, NULL, NULL);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char  yVIEW_env  (void)  { return myVIEW.env; }

char
yVIEW_draw              (void)
{
   /*---(locals)-----------+-----+-----+-*/
   int         rc          =    0;
   tPARTS     *p           = NULL;
   short       x_cur, y_cur;
   int         i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(clear)--------------------------*/
   DEBUG_YVIEW   yLOG_point   ("s_cleanse" , s_cleanse);
   if (s_cleanse != NULL) {
      rc = s_cleanse ();
      DEBUG_YVIEW   yLOG_value   ("s_cleanse" , rc);
   }
   /*---(draw each element)--------------*/
   DEBUG_YVIEW   yLOG_point   ("s_prep"    , s_prep);
   DEBUG_YVIEW   yLOG_note    ("INDEPENDENT SCREEN ELEMENTS");
   for (i = 0; i < myVIEW.npart; ++i) {
      yview_by_index (i, &p, NULL);
      if (p == NULL)  continue;
      DEBUG_YVIEW   yLOG_complex ("part"      , "%-12.12s, %c, %c, %c, %-10.10p", p->name, p->own, p->on, p->type, p->drawer);
      if (strchr (OWN_SETUP, p->own) == NULL || p->on   != 'y') {
         DEBUG_YVIEW   yLOG_note    ("skipping, either not on or not independent");
      } else if (p->drawer == NULL) {
         DEBUG_YVIEW   yLOG_note    ("bupkiss, turned-on but not drawer assigned");
      } else {
         DEBUG_YVIEW   yLOG_note    ("ready to go, calling prep, source, and drawer");
         if (s_prep    != NULL)  s_prep (p->abbr);
         if (p->source != NULL)  p->source (myVIEW.s_size, myVIEW.s_wide, p->text);
         if (p->drawer != NULL)  p->drawer ();
      }
      /*---(done)--------------*/
   }
   /*---(find cursor)--------------------*/
   if (myVIEW.env == YVIEW_CURSES)  s_cursor ();
   /*---(on top of main)-----------------*/
   DEBUG_YVIEW   yLOG_note    ("OVERLAY SREEN ELEMENTS");
   for (i = 0; i < myVIEW.npart; ++i) {
      yview_by_index (i, &p, NULL);
      if (p == NULL)  continue;
      DEBUG_YVIEW   yLOG_complex ("part"      , "%-12.12s, %c, %c, %c, %-10.10p", p->name, p->own, p->on, p->type, p->drawer);
      if (p->own != OWN_OVERLAY || p->on     != 'y') {
         DEBUG_YVIEW   yLOG_note    ("skipping, either not on or not overlay");
      } else if (p->drawer == NULL) {
         DEBUG_YVIEW   yLOG_note    ("bupkiss, turned-on but not drawer assigned");
      } else  {
         DEBUG_YVIEW   yLOG_note    ("ready to go, calling source and drawer");
         if (s_prep    != NULL)  s_prep (p->abbr);
         if (p->source != NULL)  p->source (myVIEW.s_size, myVIEW.s_wide, NULL);
         if (p->drawer != NULL)  p->drawer ();
      }
      /*---(done)--------------*/
   }
   /*---(flush)--------------------------*/
   DEBUG_YVIEW   yLOG_point   ("s_refresh" , s_refresh);
   if (s_refresh != NULL) {
      DEBUG_YVIEW   yLOG_note    ("flush and show");
      rc = s_refresh ();
      DEBUG_YVIEW   yLOG_value   ("s_refresh" , rc);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                         unit testing                         ----===*/
/*====================------------------------------------====================*/
static void  o___UNIT_TEST_______o () { return; }

char           unit_answer [LEN_FULL];

char       /*----: set up program urgents/debugging --------------------------*/
yview__unit_quiet        (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yVIEW_unit" };
   yview_init ();
   return 0;
}

char       /*----: set up program urgents/debugging --------------------------*/
yview__unit_loud         (void)
{
   int         x_narg       = 1;
   char       *x_args [20]  = {"yVIEW_unit" };
   yURG_logger   (x_narg, x_args);
   yURG_urgs     (x_narg, x_args);
   yURG_name  ("kitchen"      , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yURG_name  ("ymode"        , YURG_ON);
   yURG_name  ("ycmd"         , YURG_ON);
   yURG_name  ("ysrc"         , YURG_ON);
   yURG_name  ("yview"        , YURG_ON);
   DEBUG_YVIEW  yLOG_info     ("yVIEW"     , yVIEW_version   ());
   yview_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yview__unit_end          (void)
{
   DEBUG_YVIEW  yLOG_enter   (__FUNCTION__);
   yVIEW_wrap   ();
   DEBUG_YVIEW  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char
yview__unit_cleanse      (void)
{
   return 0;
}

char
yview__unit_prep         (char a_abbr)
{
   return 0;
}

char
yview__unit_draw         (void)
{
   return 0;
}

char
yview__unit_cursor       (void)
{
   return 0;
}

char
yview__unit_refresh      (void)
{
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yVIEW__unit             (char *a_question, char a_index)
{
   char        rc          =    0;
   tPARTS     *p           = NULL;
   char        s           [LEN_SHORT] = "···";
   char        t           [LEN_SHORT] = "···";
   /*---(preprare)-----------------------*/
   strlcpy  (unit_answer, "VIEW unit        : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "size"           )   == 0) {
      rc = yview_by_abbr   (a_index, &p, NULL);
      if (rc >= 0) {
         if (p->source != NULL)  strcpy (s, "src");
         if (p->drawer != NULL)  strcpy (t, "drw");
         snprintf (unit_answer, LEN_FULL, "VIEW %-12.12s: %c %4dL %4dW %4dB %4dT  §  %c %c %c %5.2f %2dc %4dx %4dX %4dy %4dY %4dz %4dZ  %-3.3s %s", p->name, p->on, p->left, p->wide, p->bott, p->tall, p->orient, p->type, chrvisible (p->anchor), p->magn, p->color, p->xmin, p->xmin + p->xlen, p->ymin, p->ymin + p->ylen, p->zmin, p->zmin + p->zlen, s, t);
      } else  snprintf (unit_answer, LEN_FULL, "VIEW n/a         : ·    ·L    ·W    ·B    ·T  §  · · ·     ·f  ·c    ·x    ·X    ·y    ·Y    ·z    ·Z  ··· ···");
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


