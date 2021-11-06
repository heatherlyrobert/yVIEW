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
   myVIEW.env = '-';
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
   char        rc          =    0;
   tPARTS     *p           = NULL;
   /*---(preprare)-----------------------*/
   strlcpy  (unit_answer, "VIEW unit        : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "size"           )   == 0) {
      rc = yview_by_abbr   (a_index, &p, NULL);
      if (rc >= 0)  snprintf (unit_answer, LEN_FULL, "VIEW %-12.12s: %c %4dL %4dW %4dB %4dT  §  %c %c %5.2f %5dx %5dX %5dy %5dY %5dz %5dZ", p->name, p->on, p->left, p->wide, p->bott, p->tall, p->orient, chrvisible (p->anchor), p->magn, p->xmin, p->xmin + p->xlen, p->ymin, p->ymin + p->ylen, p->zmin, p->zmin + p->zlen);
      else          snprintf (unit_answer, LEN_FULL, "VIEW n/a         : ·    ·L    ·W    ·B    ·T  §  · ·     ·f     ·x     ·X     ·y     ·Y     ·z     ·Z");
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}


