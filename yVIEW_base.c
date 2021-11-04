/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



tMY         myVIEW;



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
yVIEW_init              (void)
{
   yview_parts_init ();
   return 0;
}

char
yVIEW_wrap              (void)
{
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
   yVIEW_init ();
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
   yURG_name  ("edit"         , YURG_ON);
   yURG_name  ("ystr"         , YURG_ON);
   yURG_name  ("ymode"        , YURG_ON);
   yURG_name  ("mode"         , YURG_ON);
   yURG_name  ("cmds"         , YURG_ON);
   DEBUG_CMDS  yLOG_info     ("yVIEW"     , yVIEW_version   ());
   yVIEW_init ();
   return 0;
}

char       /*----: stop logging ----------------------------------------------*/
yview__unit_end          (void)
{
   DEBUG_CMDS  yLOG_enter   (__FUNCTION__);
   yVIEW_wrap   ();
   DEBUG_CMDS  yLOG_exit    (__FUNCTION__);
   yLOGS_end    ();
   return 0;
}

char*        /*-> tbd --------------------------------[ leaf   [gs.520.202.40]*/ /*-[01.0000.00#.#]-*/ /*-[--.---.---.--]-*/
yVIEW__unit             (char *a_question, char a_index)
{
   char        n;
   /*---(preprare)-----------------------*/
   strlcpy  (unit_answer, "VIEW unit        : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "size"           )   == 0) {
      n = yview_by_abbr   (a_index, NULL, NULL);
      snprintf (unit_answer, LEN_FULL, "VIEW %-12.12s: on %c, left %4d, wide %4d, bott %4d, tall %4d", g_parts [n].name, g_parts [n].on, g_parts [n].left, g_parts [n].wide, g_parts [n].bott, g_parts [n].tall);
   }
   else if (strcmp (a_question, "bounds"         )   == 0) {
      n = yview_by_abbr   (a_index, NULL, NULL);
      snprintf (unit_answer, LEN_FULL, "VIEW %-12.12s: an %c, xmin %4d, xmax %4d, ymin %4d, ymax %4d", g_parts [n].name, g_parts [n].anchor, g_parts [n].xmin, g_parts [n].xmin + g_parts [n].xlen, g_parts [n].ymin, g_parts [n].ymin + g_parts [n].ylen);
   }
   if      (strcmp (a_question, "active"         )   == 0) {
      n = yview_by_abbr   (a_index, NULL, NULL);
      snprintf (unit_answer, LEN_FULL, "VIEW active      : %-12.12s, on %c", g_parts [n].name, g_parts [n].on);
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


