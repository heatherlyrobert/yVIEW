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
   myVIEW.note_line == 'k';
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
   /*---(hook to yVIHUB)-----------------*/
   yVIHUB_from_yVIEW (yVIEW_keys, yVIEW_modes, yVIEW_switch_add);
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

char
yVIEW_init_after        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   yMODE_after_set  (FMOD_VIEW);
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
   DEBUG_YVIEW   yLOG_note    ("--------------------------------------");
   DEBUG_YVIEW   yLOG_note    ("OVERLAY MAIN ELEMENTS");
   for (i = 0; i < myVIEW.npart; ++i) {
      yview_by_index (i, &p, NULL);
      if (p == NULL)  continue;
      DEBUG_YVIEW   yLOG_complex ("part"      , "%-12.12s, %c, %c, %c, %-10.10p", p->name, p->own, p->on, p->type, p->drawer);
      if (p->own != OWN_OVERLAY) {
         DEBUG_YVIEW   yLOG_note    ("skipping, not main overlay");
      } else if (p->on != 'y') {
         DEBUG_YVIEW   yLOG_note    ("hidden, not currently on");
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
   /*---(on top of window)---------------*/
   DEBUG_YVIEW   yLOG_note    ("--------------------------------------");
   DEBUG_YVIEW   yLOG_note    ("OVERLAY WINDOW ELEMENTS");
   for (i = 0; i < myVIEW.npart; ++i) {
      yview_by_index (i, &p, NULL);
      if (p == NULL)  continue;
      DEBUG_YVIEW   yLOG_complex ("part"      , "%-12.12s, %c, %c, %c, %-10.10p", p->name, p->own, p->on, p->type, p->drawer);
      if (p->own != OWN_WINDOW && p->own != OWN_FLOAT) {
         DEBUG_YVIEW   yLOG_note    ("skipping, not window overlay or float");
      } else if (p->on != 'y') {
         DEBUG_YVIEW   yLOG_note    ("hidden, not currently on");
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
   DEBUG_YVIEW   yLOG_note    ("--------------------------------------");
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

