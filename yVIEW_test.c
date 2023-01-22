/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"




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
   yURG_by_name  ("kitchen"      , YURG_ON);
   yURG_by_name  ("ystr"         , YURG_ON);
   yURG_by_name  ("ymode"        , YURG_ON);
   yURG_by_name  ("ycmd"         , YURG_ON);
   yURG_by_name  ("ysrc"         , YURG_ON);
   yURG_by_name  ("yview"        , YURG_ON);
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
         snprintf (unit_answer, LEN_FULL, "VIEW %-12.12s: %c %4dL %4dW %4dB %4dT  §  %c %c %c  %2d %1d  §  %4dx %4dX %4dy %4dY %4dz %4dZ  %-3.3s %s",
               p->name, p->on, p->left, p->wide, p->bott, p->tall,
               p->orient, p->type, chrvisible (p->anchor), p->cmajor, p->cminor,
               p->xmin, p->xmin + p->xlen, p->ymin, p->ymin + p->ylen, p->zmin, p->zmin + p->zlen, s, t);
      } else  snprintf (unit_answer, LEN_FULL, "VIEW n/a         : ·    ·L    ·W    ·B    ·T  §  · · ·   · ·  §     ·x    ·X    ·y    ·Y    ·z    ·Z  ··· ···");
   }
   /*---(complete)-----------------------*/
   return unit_answer;
}

