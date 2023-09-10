/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"


/*===[[ HISTORY ]]============================================================*/
#define   MAX_HIST     1000
typedef struct cVIEW_HIST   tVIEW_HIST;
struct cVIEW_HIST {
   /*---(basic)-------------*/
   uchar       h_mark;                  /* if marked for quick use           */
   uchar      *h_text;                  /* command or search line used       */
   /*---(stats)-------------*/
   char        h_ran;                   /* could it execute                  */
   uchar       h_count;                 /* how many times has it been used   */
   int         h_found;                 /* what where the results            */
   /*---(list)--------------*/
   tVIEW_HIST *h_next;
   tVIEW_HIST *h_prev;
};
/*---(command history)---------*/
static tVIEW_HIST    *s_hrun      = NULL;    /* head               */
static tVIEW_HIST    *s_trun      = NULL;    /* tail               */
static tVIEW_HIST    *s_crun      = NULL;    /* current            */
static int            s_irun      = 0;       /* index              */
static int            s_nrun      = 0;       /* count              */
/*---(search history)----------*/
static tVIEW_HIST    *s_hpass     = NULL;    /* head               */
static tVIEW_HIST    *s_tpass     = NULL;    /* tail               */
static tVIEW_HIST    *s_cpass     = NULL;    /* current            */
static int            s_ipass     = 0;       /* index              */
static int            s_npass     = 0;       /* count              */
/*---(switchable)--------------*/
static tVIEW_HIST   **s_head      = &s_hrun; /* head               */
static tVIEW_HIST   **s_tail      = &s_trun; /* tail               */
static tVIEW_HIST   **s_curr      = &s_crun; /* current            */
static int           *s_index     = &s_irun; /* index              */
static int           *s_count     = &s_nrun; /* count              */
static int            s_nall      = 0;       /* full count         */
/*---(pushed)------------------*/
static tVIEW_HIST    *s_saved     = NULL;    /* current            */
static int            s_isaved    = 0;       /* index              */
/*---(current)-----------------*/
/*> static uchar   s_current   [LEN_RECD] = "";                                       <* 
 *> static int     s_len       = 0;                                                   <*/
/*---(done)--------------------*/



#define      S_HIST_MAX    100
static char  S_HIST_LIST [S_HIST_MAX];






/*====================------------------------------------====================*/
/*===----                      support functions                       ----===*/
/*====================------------------------------------====================*/
static void  o___SUPPORT_________o () { return; }

char
yview_hist__switcher    (char a_mode, char a_force)
{
   /*---(locals)-----------+-----+-----+-*/
   static char x_save      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_mode"    , a_mode);
   /*---(defense)------------------------*/
   if (a_force != 'y' && a_mode == x_save) {
      DEBUG_YVIEW   yLOG_note    ("same as last, short-cut");
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(switch)-------------------------*/
   switch (a_mode) {
   case MODE_SEARCH  :
      DEBUG_YVIEW   yLOG_note    ("switching to search");
      s_head  = &s_hpass;
      s_tail  = &s_tpass;
      s_curr  = &s_cpass;
      s_index = &s_ipass;
      s_count = &s_npass;
      break;
   case MODE_COMMAND :
   default :
      DEBUG_YVIEW   yLOG_note    ("switching to command");
      s_head  = &s_hrun;
      s_tail  = &s_trun;
      s_curr  = &s_crun;
      s_index = &s_irun;
      s_count = &s_nrun;
      break;
   }
   /*---(save)---------------------------*/
   x_save = a_mode;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      histtory marks                         ----===*/
/*====================------------------------------------====================*/
static void  o___MARKS___________o () { return; }

char 
yview_hist__valid       (char a_abbr)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_senter  (__FUNCTION__);
   /*---(check)--------------------------*/
   DEBUG_YVIEW   yLOG_snote   ("check");
   rc = ystrlchr (S_HIST_LIST, a_abbr, S_HIST_MAX);
   DEBUG_YVIEW   yLOG_sint    (rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_sexitr  (__FUNCTION__, rce);
      return rce;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_hist__unmark    (uchar a_mark)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tVIEW_HIST *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_mark"    , a_mark);
   --rce;  if (strchr (S_HIST_LIST, tolower (a_mark)) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-entries)-------------------*/
   x_curr = *s_head;
   while (x_curr != NULL) {
      DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, x_curr->h_text, x_curr, x_curr->h_next, x_curr->h_prev);
      if (a_mark == x_curr->h_mark)   x_curr->h_mark = '-';
      x_curr = x_curr->h_next;
      ++c;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__mark      (uchar a_mark)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_mark"    , a_mark);
   --rce;  if (strchr (S_HIST_LIST, a_mark) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   --rce;  if (*s_curr == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(make sure not used)-------------*/
   yview_hist__unmark (a_mark);
   /*---(mark current)-------------------*/
   (*s_curr)->h_mark = a_mark;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}




/*====================------------------------------------====================*/
/*===----                    memory allocation                         ----===*/
/*====================------------------------------------====================*/
static void  o___MEMORY__________o () { return; }

char 
yVIEW_hist_new          (char a_mode, uchar *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tVIEW_HIST *x_new       = NULL;
   char        x_tries     =    0;
   int         x_len       =    0;
   char        x_text      [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_char    ("a_mode"    , a_mode);
   rc = yview_hist__switcher (a_mode, '-');
   DEBUG_YVIEW   yLOG_value   ("switcher"  , rc);
   --rce;  if (rc < 0) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_point   ("a_text"    , a_text);
   --rce;  if (a_text == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(quick-out)----------------------*/
   if (strchr (":/", a_text [1]) == NULL) {
      --rce;  IF_MACRO_ANYTHING {
         DEBUG_YVIEW   yLOG_note    ("nothing goes to history during macros");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      ystrlcpy (x_text, a_text, LEN_RECD);
   } else {
      ystrlcpy (x_text, a_text + 1, LEN_RECD);
   }
   /*---(prepare)------------------------*/
   ystrldchg (x_text, '≤', ' ', LEN_RECD);
   DEBUG_YVIEW   yLOG_info    ("x_text"    , x_text);
   x_len = strlen (x_text);
   DEBUG_YVIEW   yLOG_value   ("x_len"     , x_len);
   --rce;  if (x_len < 1) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(find dup)-----------------------*/
   yVIEW_hist_push ();
   rc = yview_hist__find (x_text);
   if (rc >= 0) {
      ++((*s_curr)->h_count);
      rc = yview_hist__roll ();
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   yVIEW_hist_pop  ();
   /*---(allocate)-----------------------*/
   while (x_new == NULL && x_tries < 10)  {
      ++x_tries;
      x_new = (tVIEW_HIST *) malloc (sizeof (tVIEW_HIST));
   }
   DEBUG_YVIEW   yLOG_value   ("x_tries"   , x_tries);
   DEBUG_YVIEW   yLOG_point   ("x_new"     , x_new);
   --rce;  if (x_new == NULL) {
      DEBUG_YVIEW   yLOG_note    ("FAILED");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(populate)-----------------------*/
   DEBUG_YVIEW   yLOG_note    ("populate");
   x_new->h_mark     = '-';
   x_new->h_text     = strdup (x_text);
   x_new->h_count    = 1;
   x_new->h_ran      = '∑';
   x_new->h_found    = 0;
   x_new->h_next   = NULL;
   x_new->h_prev   = NULL;
   /*---(tie to master list)-------------*/
   if (*s_head == NULL) {
      DEBUG_YVIEW   yLOG_note    ("nothing in list, make first");
      *s_head           = x_new;
   } else  {
      DEBUG_YVIEW   yLOG_note    ("append to list");
      (*s_tail)->h_next = x_new;
      x_new->h_prev     = *s_tail;
   }
   *s_tail        = x_new;
   /*---(update counts)------------------*/
   ++(*s_count);
   ++s_nall;
   DEBUG_YVIEW   yLOG_value   ("s_count"   , *s_count);
   DEBUG_YVIEW   yLOG_value   ("s_nall"    , s_nall);
   /*---(update current)-----------------*/
   *s_curr  = *s_tail;
   *s_index = *s_count - 1;
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char 
yview_hist__free_curr   (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   tVIEW_HIST *x_next      = NULL;
   /*---(defense)------------------------*/
   if (*s_curr == NULL)  return rce;
   x_next = (*s_curr)->h_next;
   if (x_next == NULL)   x_next = (*s_curr)->h_prev;
   /*---(clear data)---------------------*/
   free ((*s_curr)->h_text);
   /*---(out of linked list)-------------*/
   if ((*s_curr)->h_next != NULL)   (*s_curr)->h_next->h_prev = (*s_curr)->h_prev;
   else                             *s_tail                   = (*s_curr)->h_prev;
   if ((*s_curr)->h_prev != NULL)   (*s_curr)->h_prev->h_next = (*s_curr)->h_next;
   else                             *s_head                   = (*s_curr)->h_next;
   /*---(update counts)------------------*/
   --(*s_count);
   --s_nall;
   /*---(reposition)---------------------*/
   *s_curr = x_next;
   /*---(complete)-----------------------*/
   return 0;
}

char 
yVIEW_hist_stats        (char a_rc, short a_found)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   if (*s_curr != NULL) {
      if (a_rc >= 0)  (*s_curr)->h_ran = 'y';
      else            (*s_curr)->h_ran = '-';
      (*s_curr)->h_found = a_found;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__purge       (char a_mode)
{
   /*---(locals)-----------+-----+-----+-*/
   tVIEW_HIST *x_curr      = NULL;
   tVIEW_HIST *x_next      = NULL;
   /*---(set pointer)--------------------*/
   yview_hist__switcher (a_mode, '-');
   /*---(clear history)------------------*/
   x_curr = *s_head;
   while (x_curr != NULL) {
      /*--(prepare)------------*/
      x_next = x_curr->h_next;
      /*--(ground/careful)-----*/
      x_curr->h_prev = NULL;
      x_curr->h_next = NULL;
      /*--(free memory)--------*/
      free (x_curr->h_text);
      free (x_curr);
      /*--(next)---------------*/
      x_curr = x_next;
      /*--(done)---------------*/
   }
   /*---(initialize pointers)------------*/
   *s_head  = NULL;
   *s_tail  = NULL;
   *s_curr  = NULL;
   *s_count = 0;
   s_nall   = s_nrun + s_npass;
   /*---(complete)-----------------------*/
   return 0;
}

/*====================------------------------------------====================*/
/*===----                       program level                          ----===*/
/*====================------------------------------------====================*/
static void  o___PROGRAM_________o () { return; }

char
yview_hist_init         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(macro abbrev list)--------------*/
   DEBUG_YVIEW   yLOG_note    ("initialize hist list");
   ystrlcpy (S_HIST_LIST, ""         , S_HIST_MAX);
   ystrlcat (S_HIST_LIST, YSTR_NUMBER, S_HIST_MAX);
   ystrlcat (S_HIST_LIST, YSTR_LOWER , S_HIST_MAX);
   ystrlcat (S_HIST_LIST, YSTR_UPPER , S_HIST_MAX);
   ystrlcat (S_HIST_LIST, YSTR_GREEK , S_HIST_MAX);
   DEBUG_YVIEW   yLOG_info    ("LIST"      , S_HIST_LIST);
   /*---(switchable)--------------*/
   yview_hist__switcher (MODE_COMMAND, 'y');
   /*> yvikeys_hist_text      (MODE_COMMAND, NULL);                                   <*/
   /*---(update status)------------------*/
   yMODE_init_set   (UMOD_HISTORY, yview_hist_prepper, yview_hist_umode);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist_wrap         (void)
{
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   yview_hist__purge    (MODE_COMMAND);
   yview_hist__purge    (MODE_SEARCH);
   yview_hist__switcher (MODE_COMMAND, 'y');
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                       unit testing                          ----===*/
/*====================------------------------------------====================*/
static void  o___UNITTEST________o () { return; }

char*
yview_hist__unit        (char *a_question, int n)
{
   /*---(locals)-----------+-----+-----+-*/
   char        t           [LEN_HUND ] = "";
   tVIEW_HIST *x_curr      = NULL;
   int         c           =    0;
   /*---(preprare)-----------------------*/
   ystrlcpy  (unit_answer, "HIST unit        : question not understood", LEN_FULL);
   /*---(dependency list)----------------*/
   if      (strcmp (a_question, "switch"         )   == 0) {
      if      (s_head  == NULL    )  ystrlcat (t, "h=----"  , LEN_HUND);
      else if (s_head  == &s_hrun )  ystrlcat (t, "h=CMDS"  , LEN_HUND);
      else if (s_head  == &s_hpass)  ystrlcat (t, "h=SRCH"  , LEN_HUND);
      else                           ystrlcat (t, "h=????"  , LEN_HUND);
      if      (s_tail  == NULL    )  ystrlcat (t, ", t=----", LEN_HUND);
      else if (s_tail  == &s_trun )  ystrlcat (t, ", t=CMDS", LEN_HUND);
      else if (s_tail  == &s_tpass)  ystrlcat (t, ", t=SRCH", LEN_HUND);
      else                           ystrlcat (t, ", t=????", LEN_HUND);
      if      (s_curr  == NULL    )  ystrlcat (t, ", c=----", LEN_HUND);
      else if (s_curr  == &s_crun )  ystrlcat (t, ", c=CMDS", LEN_HUND);
      else if (s_curr  == &s_cpass)  ystrlcat (t, ", c=SRCH", LEN_HUND);
      else                           ystrlcat (t, ", c=????", LEN_HUND);
      if      (s_count == NULL    )  ystrlcat (t, ", n=----", LEN_HUND);
      else if (s_count == &s_nrun )  ystrlcat (t, ", n=CMDS", LEN_HUND);
      else if (s_count == &s_npass)  ystrlcat (t, ", n=SRCH", LEN_HUND);
      else                           ystrlcat (t, ", n=????", LEN_HUND);
      snprintf (unit_answer, LEN_FULL, "HIST switch      : %s", t);
   }
   else if (strcmp (a_question, "counts"         )   == 0) {
      snprintf (unit_answer, LEN_FULL, "HIST count       : %3da, %3dc, %3ds", s_nall, s_nrun, s_npass);
   }
   else if (strcmp (a_question, "current"        ) == 0) {
      if    (*s_head == s_hrun) ystrlcpy (t, "c", LEN_LABEL);
      else                      ystrlcpy (t, "s", LEN_LABEL);
      if (*s_curr == NULL)  snprintf (unit_answer, LEN_FULL, "HIST curr %s (--) :  -  -                      -    -    -    -", t);
      else                  snprintf (unit_answer, LEN_FULL, "HIST curr %s (%2d) : %2d  %-20.20s %3dc %3dr %3df   %c", t, *s_index, strlen ((*s_curr)->h_text), (*s_curr)->h_text, (*s_curr)->h_count, (*s_curr)->h_ran, (*s_curr)->h_found, (*s_curr)->h_mark);
   }
   else if (strcmp (a_question, "command"        )   == 0 || strcmp (a_question, "search"         )   == 0) {
      if (a_question [0] == 'c') {
         ystrlcpy (t, "cmds", LEN_LABEL);
         x_curr = s_hrun;
      } else {
         ystrlcpy (t, "srch", LEN_LABEL);
         x_curr = s_hpass;
      }
      DEBUG_YVIEW   yLOG_value   ("n"         , n);
      while (x_curr != NULL) {
         DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, x_curr->h_text, x_curr, x_curr->h_next, x_curr->h_prev);
         /*> printf ("entry  %2d %-10.10s %10p %10p\n", c, x_curr->h_text, x_curr, x_curr->h_next);   <*/
         if (c == n) {
            /*> printf ("found\n");                                                   <*/
            DEBUG_YVIEW   yLOG_point   ("found"     , x_curr);
            break;
         }
         x_curr = x_curr->h_next;
         ++c;
      }
      /*> printf ("checking...%p\n", x_curr);                                         <*/
      DEBUG_YVIEW   yLOG_point   ("found"     , x_curr);
      if (x_curr == NULL)  snprintf (unit_answer, LEN_FULL, "HIST %-4.4s   (%2d) :  -  -                      -    -    -    -", t, n);
      else {
         snprintf (unit_answer, LEN_FULL, "HIST %-4.4s   (%2d) : %2d  %-20.20s %3dc %3dr %3df   %c",
               t, n, strlen (x_curr->h_text), x_curr->h_text, x_curr->h_count, x_curr->h_ran, x_curr->h_found, x_curr->h_mark);
      }
   }
   /*---(complete)-----------------------*/
   /*> printf ("%s\n", yVIKEYS__unit_answer);                                         <*/
   return unit_answer;
}



/*====================------------------------------------====================*/
/*===----                       search and finding                     ----===*/
/*====================------------------------------------====================*/
static void  o___SEARCH__________o () { return; }

char yVIEW_hist_push       (void)  { s_saved = *s_curr;   s_isaved = *s_index;   return 0; }
char yVIEW_hist_pop        (void)  { *s_curr  = s_saved;  *s_index = s_isaved;   return 0; }

int yVIEW_hist_count       (void)  { return *s_count; }

char
yVIEW_hist_cursor     (char a_move, int *r_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   char        i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_char    ("a_move"    , a_move);
   /*---(default)------------------------*/
   if (r_index != NULL)  *r_index = -1;
   /*---(defenses)-----------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_head"   , *s_head);
   --rce;  if (*s_head == NULL) {
      *s_curr  = NULL;
      *s_index = -1;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   if (*s_curr == NULL) {
      *s_curr  = *s_head;
      *s_index = 0;
      DEBUG_YVIEW   yLOG_point   ("fixed"     , *s_curr);
   }
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(handle move)--------------------*/
   DEBUG_YVIEW   yLOG_note    ("check cursor types");
   switch (a_move) {
   case YDLST_HEAD  :
      *s_curr  = *s_head;
      *s_index = 0;
      break;
   case YDLST_BPREV :
      while (*s_curr != NULL && i < 5) {
         *s_curr  = (*s_curr)->h_prev;
         --(*s_index);
         ++i;
      }
      break;
   case YDLST_PREV  :
      *s_curr  = (*s_curr)->h_prev;
      --(*s_index);
      break;
   case YDLST_CURR  :
      break;
   case YDLST_NEXT  :
      *s_curr  = (*s_curr)->h_next;
      ++(*s_index);
      break;
   case YDLST_BNEXT :
      while (*s_curr != NULL && i < 5) {
         *s_curr  = (*s_curr)->h_next;
         ++(*s_index);
         ++i;
      }
      break;
   case YDLST_TAIL :
      *s_curr  = *s_tail;
      *s_index = *s_count - 1;
      break;
   }
   /*---(safeties)-----------------------*/
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   if (*s_curr == NULL) {
      switch (a_move) {
      case YDLST_CURR  : 
         DEBUG_YVIEW   yLOG_note    ("unset current");
         *s_curr  = *s_head;
         *s_index = 0;
         rc = 1;
         break;
      case YDLST_PREV  : case YDLST_BPREV :
         DEBUG_YVIEW   yLOG_note    ("bounced off head");
         *s_curr  = *s_head;
         *s_index = 0;
         rc = 1;
         break;
      case YDLST_NEXT  : case YDLST_BNEXT :
         DEBUG_YVIEW   yLOG_note    ("bounced off tail");
         *s_curr  = *s_tail;
         *s_index = *s_count - 1;
         rc = 1;
         break;
      }
   }
   /*---(save back)----------------------*/
   if (r_index != NULL)  *r_index = *s_index;
   /*---(output)-------------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return rc;
}

char
yview_hist__index       (int a_index)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tVIEW_HIST *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_head"   , *s_head);
   --rce;  if (*s_head == NULL) {
      *s_curr  = NULL;
      *s_index = -1;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(short-cuts)---------------------*/
   DEBUG_YVIEW   yLOG_value   ("a_index"   , a_index);
   if (a_index <  0) {
      DEBUG_YVIEW   yLOG_note    ("less than min (neg) is short-cut to head");
      *s_curr  = *s_head;
      *s_index = 0;
      DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, (*s_curr)->h_text, (*s_curr), (*s_curr)->h_next, (*s_curr)->h_prev);
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   if (a_index >= *s_count) {
      DEBUG_YVIEW   yLOG_note    ("greater than max is short-cut to tail");
      *s_curr  = *s_tail;
      *s_index = *s_count - 1;
      DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, (*s_curr)->h_text, (*s_curr), (*s_curr)->h_next, (*s_curr)->h_prev);
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(walk-entries)-------------------*/
   x_curr = *s_head;
   while (x_curr != NULL) {
      DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, x_curr->h_text, x_curr, x_curr->h_next, x_curr->h_prev);
      if (c == a_index) break;
      x_curr = x_curr->h_next;
      ++c;
   }
   /*---(check result)-------------------*/
   DEBUG_YVIEW   yLOG_point   ("x_curr"    , x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set current)--------------------*/
   *s_curr  = x_curr;
   *s_index = a_index;
   /*---(output)-------------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__dup       (uchar *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tVIEW_HIST *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(walk-entries)-------------------*/
   x_curr = *s_head;
   while (x_curr != NULL) {
      DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, x_curr->h_text, x_curr, x_curr->h_next, x_curr->h_prev);
      if (a_text [0] == x_curr->h_text [0]) {
         if (strcmp (a_text, x_curr->h_text) == 0) {
         }
      }
      x_curr = x_curr->h_next;
      ++c;
   }
   /*---(check result)-------------------*/
   DEBUG_YVIEW   yLOG_point   ("x_curr"    , x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set current)--------------------*/
   *s_curr  = x_curr;
   *s_index = c;
   /*---(output)-------------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__find      (uchar *a_text)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tVIEW_HIST *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_head"   , *s_head);
   --rce;  if (*s_head == NULL) {
      *s_curr  = NULL;
      *s_index = -1;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_point   ("a_text"    , a_text);
   --rce;  if (a_text == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-entries)-------------------*/
   x_curr = *s_head;
   while (x_curr != NULL) {
      DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, x_curr->h_text, x_curr, x_curr->h_next, x_curr->h_prev);
      if (a_text [0] == x_curr->h_text [0]) {
         if (strcmp (a_text, x_curr->h_text) == 0)   break;
      }
      x_curr = x_curr->h_next;
      ++c;
   }
   /*---(check result)-------------------*/
   DEBUG_YVIEW   yLOG_point   ("x_curr"    , x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set current)--------------------*/
   *s_curr  = x_curr;
   *s_index = c;
   /*---(output)-------------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__marked    (uchar a_mark)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tVIEW_HIST *x_curr      = NULL;
   int         c           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defenses)-----------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_head"   , *s_head);
   --rce;  if (*s_head == NULL) {
      *s_curr  = NULL;
      *s_index = -1;
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_char    ("a_mark"    , a_mark);
   --rce;  if (strchr (S_HIST_LIST, a_mark) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(walk-entries)-------------------*/
   x_curr = *s_head;
   while (x_curr != NULL) {
      DEBUG_YVIEW   yLOG_complex ("entry"     , "%2d %-10.10s %10p %10p %10p", c, x_curr->h_text, x_curr, x_curr->h_next, x_curr->h_prev);
      if (a_mark == x_curr->h_mark)   break;
      x_curr = x_curr->h_next;
      ++c;
   }
   /*---(check result)-------------------*/
   DEBUG_YVIEW   yLOG_point   ("x_curr"    , x_curr);
   --rce;  if (x_curr == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(set current)--------------------*/
   *s_curr  = x_curr;
   *s_index = c;
   /*---(output)-------------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   DEBUG_YVIEW   yLOG_value   ("*s_index"  , *s_index);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__roll        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (*s_head == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (*s_curr == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(short-cut)----------------------*/
   if (*s_tail == *s_curr) {
      DEBUG_YVIEW   yLOG_note    ("already tail, nothing to do");
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(pull out of list)---------------*/
   if ((*s_curr)->h_prev != NULL)  (*s_curr)->h_prev->h_next = (*s_curr)->h_next;
   if ((*s_curr)->h_next != NULL)  (*s_curr)->h_next->h_prev = (*s_curr)->h_prev;
   /*---(fix current)--------------------*/
   if (*s_head == *s_curr)    *s_head = (*s_curr)->h_next;
   (*s_curr)->h_next  = NULL;
   (*s_curr)->h_prev  = *s_tail;
   /*---(append to end)------------------*/
   (*s_tail)->h_next  = *s_curr;
   *s_tail = *s_curr;
   /*---(update current)-----------------*/
   *s_curr  = *s_tail;
   *s_index = *s_count - 1;
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      data showing                           ----===*/
/*====================------------------------------------====================*/
static void  o___SHOW____________o () { return; }

char
yVIEW_hist_header       (short a_wide, char *a_entry)
{
   char        rce         =  -10;
   char        x_size      =  'l';
   char        x_plen      =    4;
   char        x_slen      =   17;
   int         w           =    0;
   char        l           [LEN_HUND]  = "";
   /*---(default)------------------------*/
   if (a_entry != NULL)  strcpy (a_entry, "n/a");
   /*---(defense)------------------------*/
   --rce;  if (a_entry == NULL)  return rce;
   --rce;  if (a_wide  <  20) {
      strcpy (a_entry, "-");
      return rce;
   }
   /*---(general sizing)-----------------*/
   if (a_wide > 80)  a_wide = 80;
   --rce; if (a_wide >= 60)  x_size = 'l';
   else if   (a_wide >= 40)  x_size = 'm';
   else                      x_size = 's';
   /*---(specific sizing)----------------*/
   switch (x_size) {
   case 'l'  :   x_plen =  4;  x_slen = 17;  break;
   case 'm'  :   x_plen =  4;  x_slen =  7;  break;
   case 's'  :   x_plen =  1;  x_slen =  1;  break;
   }
   w = a_wide - x_plen - x_slen;
   /*---(label)--------------------------*/
   if (&s_hrun == s_head)  strcpy (l, "---COMMAND------------------------------------------------------------------------------");
   else                    strcpy (l, "---SEARCH-------------------------------------------------------------------------------");
   /*---(create)-------------------------*/
   switch (x_size) {
   case 'l'  :
      sprintf (a_entry, "ref %*.*s -cnt -ran find m"    , w, w, l);
      break;
   case 'm'  :
      sprintf (a_entry, "ref %*.*s find m"    , w, w, l);
      break;
   case 's'  :
      sprintf (a_entry, "%*.*s m"    , w, w, l);
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yVIEW_hist_footer       (short a_wide, char *a_entry)
{
   char        rce         =  -10;
   char        x_size      =  'l';
   /*---(default)------------------------*/
   if (a_entry != NULL)  strcpy (a_entry, "n/a");
   /*---(defense)------------------------*/
   --rce;  if (a_entry == NULL)  return rce;
   --rce;  if (a_wide  <  20) {
      strcpy (a_entry, "-");
      return rce;
   }
   /*---(general sizing)-----------------*/
   if (a_wide > 80)  a_wide = 80;
   --rce; if (a_wide >= 60)  x_size = 'l';
   else if   (a_wide >= 40)  x_size = 'm';
   else                      x_size = 's';
   /*---(label)--------------------------*/
   switch (x_size) {
   case 'l'  : case 'm'  :
      ystrlpad ("¶ to choose, • to leave, _KkjJ~ to move", a_entry, '.', '|', a_wide);
      break;
   case 's'  :
      ystrlpad ("¶ pick, •, _KkjJ~"                      , a_entry, '.', '|', a_wide);
      break;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yVIEW_hist_entry        (short a_wide, char *a_entry)
{
   char        rce         =  -10;
   char        x_size      =  'l';
   char        x_pref      [LEN_HUND];
   char        x_plen      =    4;
   char        x_suff      [LEN_LABEL] = "";
   char        x_slen      =   17;
   int         w           =    0;
   char        x_len       =    0;
   short       x_found     =    0;
   char        i           [LEN_TERSE] = "";
   char        c           [LEN_TERSE] = "";
   char        r           [LEN_TERSE] = "";
   char        f           [LEN_TERSE] = "";
   char        t           [LEN_HUND]  = "";
   /*---(default)------------------------*/
   if (a_entry != NULL)  strcpy (a_entry, "n/a");
   /*---(defense)------------------------*/
   --rce;  if (*s_curr == NULL)  return rce;
   --rce;  if (a_entry == NULL)  return rce;
   --rce;  if (a_wide  <  20) {
      strcpy (a_entry, "-");
      return rce;
   }
   /*---(general sizing)-----------------*/
   if (a_wide > 80)  a_wide = 80;
   --rce; if (a_wide >= 60)  x_size = 'l';
   else if   (a_wide >= 40)  x_size = 'm';
   else                      x_size = 's';
   /*---(specific sizing)----------------*/
   switch (x_size) {
   case 'l'  :   x_plen =  4;  x_slen = 17;  break;
   case 'm'  :   x_plen =  4;  x_slen =  7;  break;
   case 's'  :   x_plen =  1;  x_slen =  1;  break;
   }
   w = a_wide - x_plen - x_slen;
   /*---(number over-runs)---------------*/
   x_found = (*s_curr)->h_found;
   if (x_found > 999)  x_found = 999;
   x_len   = strlen ((*s_curr)->h_text);
   /*---(formatting)---------------------*/
   ystrlpadn (*s_index          , i, '.', '>', 3);
   ystrlpadn ((*s_curr)->h_count, c, '.', '>', 3);
   ystrlpadn (x_found           , f, '.', '>', 3);
   if (strcmp (f, "∑∑0") == 0)  strcpy (f, "∑∑∑");
   ystrlpad  ((*s_curr)->h_text , t, '.', '<', w);
   /*---(create)-------------------------*/
   switch (x_size) {
   case 'l'  :
      sprintf (x_pref, "%s %s"         , i, t);
      sprintf (x_suff, "%sc  %c  %sf  %c", c, (*s_curr)->h_ran, f, (*s_curr)->h_mark);
      if (strcmp (c, "∑∑0") == 0)  sprintf (x_suff, "∑∑∑∑  ∑  ∑∑∑∑  %c", (*s_curr)->h_mark);
      break;
   case 'm'  :
      sprintf (x_pref, "%s %s"         , i, t);
      sprintf (x_suff, "%sf %c"        , f, (*s_curr)->h_mark);
      break;
   case 's'  :
      sprintf (x_pref, "%s"            , t);
      sprintf (x_suff, "%c"            , (*s_curr)->h_mark);
      break;
   }
   /*---(concatenate)--------------------*/
   if (w < x_len)  x_pref [strlen (x_pref) - 1] = '>';
   sprintf (a_entry, "%s %s", x_pref, x_suff);
   /*---(complete)-----------------------*/
   return 0;
}

char
yview_hist__force       (int a_count, int a_ran, int a_found)
{
   if (s_curr != NULL) {
      (*s_curr)->h_count = a_count;
      (*s_curr)->h_ran   = a_ran;
      (*s_curr)->h_found = a_found;
   }
   return 0;
}



/*====================------------------------------------====================*/
/*===----                     export/import                           ----===*/
/*====================------------------------------------====================*/
static void  o___EXIM____________o () { return; }

/*> char                                                                              <* 
 *> yview_hist_export       (uchar a_abbr)                                            <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    char        n           =   -1;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YMARK   yLOG_enter   (__FUNCTION__);                                     <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_YMARK   yLOG_char    ("a_abbr"    , a_abbr);                             <* 
 *>    n = yview_srch_index  (a_abbr);                                                <* 
 *>    --rce;  if (n <  0)  {                                                         <* 
 *>       DEBUG_YMARK   yLOG_exitr   (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(write)--------------------------+/                                       <* 
 *>    rc = ystrlexport (0, S_SRCHS [n]->text);                                        <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YMARK   yLOG_exit    (__FUNCTION__);                                     <* 
 *>    return rc;                                                                     <* 
 *> }                                                                                 <*/

/*> char                                                                              <* 
 *> yview_srch_import       (uchar a_abbr)                                            <* 
 *> {                                                                                 <* 
 *>    /+---(locals)-----------+-----+-----+-+/                                       <* 
 *>    char        rce         =  -10;                                                <* 
 *>    char        rc          =    0;                                                <* 
 *>    char        x_recd      [LEN_RECD];                                            <* 
 *>    int         n           =    0;                                                <* 
 *>    tSRCH      *x_new       = NULL;                                                <* 
 *>    /+---(header)-------------------------+/                                       <* 
 *>    DEBUG_YMARK   yLOG_enter   (__FUNCTION__);                                     <* 
 *>    /+---(defense)------------------------+/                                       <* 
 *>    DEBUG_YMARK   yLOG_char    ("a_abbr"    , a_abbr);                             <* 
 *>    n = ymark_srch_index  (a_abbr);                                                <* 
 *>    DEBUG_YMARK   yLOG_value   ("n"         , n);                                  <* 
 *>    --rce;  if (n < 0) {                                                           <* 
 *>       DEBUG_YMARK   yLOG_exitr   (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    /+---(read)---------------------------+/                                       <* 
 *>    rc = ystrlimport  (0, x_recd, NULL);                                            <* 
 *>    DEBUG_YMARK   yLOG_value   ("read"      , rc);                                 <* 
 *>    --rce;  if (rc < 0) {                                                          <* 
 *>       DEBUG_YMARK   yLOG_exitr   (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    DEBUG_YMARK   yLOG_info    ("x_recd"    , x_recd);                             <* 
 *>    /+---(save search to history)---------+/                                       <* 
 *>    rc = ymark_srch_new (x_recd, '-', &x_new);                                     <* 
 *>    DEBUG_YMARK   yLOG_point   ("x_new"     , x_new);                              <* 
 *>    --rce;  if (x_new == NULL) {                                                   <* 
 *>       DEBUG_YMARK   yLOG_exitr   (__FUNCTION__, rce);                             <* 
 *>       return rce;                                                                 <* 
 *>    }                                                                              <* 
 *>    S_SRCHS [n] = x_new;                                                           <* 
 *>    /+---(complete)-----------------------+/                                       <* 
 *>    DEBUG_YMARK   yLOG_exit    (__FUNCTION__);                                     <* 
 *>    return rc;                                                                     <* 
 *> }                                                                                 <*/



/*====================------------------------------------====================*/
/*===----                      mode handling                          ----===*/
/*====================------------------------------------====================*/
static void  o___MODE____________o () { return; }

char         /*-> allow selection of older entries ---[ ------ [ge.TQ5.25#.F9]*/ /*-[03.0000.122.R]-*/ /*-[--.---.---.--]-*/
yview_hist_prepper      (void)
{
   char        x_mode      =  '-';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(switcher)-----------------------*/
   x_mode = yMODE_curr ();
   DEBUG_YVIEW   yLOG_char    ("x_mode"    , x_mode);
   yview_hist__switcher (x_mode, '-');
   /*---(current entry)------------------*/
   DEBUG_YVIEW   yLOG_point   ("*s_curr"   , *s_curr);
   if (*s_curr != NULL)   yVIHUB_ySRC_swap ((*s_curr)->h_text);
   /*---(clear escaping)-----------------*/
   yview_hist__escaped (NULL, NULL);
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__biggies     (char a_major, char a_minor)
{
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(handle)-------------------------*/
   switch (a_minor) {
   case G_KEY_ESCAPE :
      DEBUG_YVIEW   yLOG_note    ("escape, return to map mode");
      yVIHUB_ySRC_swap ("");
      yMODE_exit ();
      yMODE_exit ();
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 1;
      break;
   case G_KEY_RETURN :
      DEBUG_YVIEW   yLOG_note    ("return, return to source mode");
      yMODE_exit ();
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 2;
      break;
   case '.'          :
      DEBUG_YVIEW   yLOG_note    ("return, but force recordable if in macro mode");
      if (*s_curr != NULL) {
         sprintf (t, "/%s", (*s_curr)->h_text);
         yVIHUB_ySRC_swap (t);
      }
      yMODE_exit ();
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 2;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__escaped     (char a_major, char *b_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   static char x_escaping  =  ' ';
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (b_minor == NULL) {
      x_escaping = ' ';
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(normal)-------------------------*/
   if (x_escaping == ' ') {
      if (*b_minor == '\\') {
         DEBUG_YVIEW   yLOG_note    ("found a leading backslash");
         x_escaping = 'µ';
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return 1;
      }
   }
   /*---(backslashed)--------------------*/
   if (x_escaping == 'µ') {
      if (*b_minor == '_') {
         DEBUG_YVIEW   yLOG_note    ("found a leading backslash/underscore");
         x_escaping = '_';
         return 2;
      }
      DEBUG_YVIEW   yLOG_note    ("converting backslash character");
      *b_minor = ychrslashed (*b_minor);
   }
   /*---(backslash/more)-----------------*/
   if (x_escaping == '_') {
      DEBUG_YVIEW   yLOG_note    ("converting backslash/underscore");
      *b_minor = ychrslashed_more (*b_minor);
   }
   /*---(reset)--------------------------*/
   x_escaping = ' ';
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__marking     (char a_major, char a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(handle first key)---------------*/
   if (a_minor != 0 && strchr ("mu'", a_minor)  != NULL) {
      DEBUG_YVIEW   yLOG_note    ("first char of mark/unmark request");
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 1;
   }
   /*---(handle second key)--------------*/
   if (a_major != 0 && strchr ("mu'", a_major)  != NULL) {
      DEBUG_YVIEW   yLOG_note    ("second char of mark/unmark request");
      switch (a_major) {
      case 'm' :
         rc = yview_hist__mark   (a_minor);
         break;
      case 'u' :
         if (a_minor == '.')   rc = yview_hist__unmark ((*s_curr)->h_mark);
         else                  rc = yview_hist__unmark (a_minor);
         break;
      case '\'' :
         rc = yview_hist__marked (a_minor);
         break;
      }
      DEBUG_YVIEW   yLOG_value   ("rc"        , rc);
      if (rc < 0)  yKEYS_set_error ();
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 2;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yview_hist__cursoring   (char a_major, char a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    1;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   --rce;  if (a_major != 0 && strchr ("∑ ", a_major) == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(handle cursoring)---------------*/
   --rce;  switch (a_minor) {
   case '_' :
      yVIEW_hist_cursor (YDLST_HEAD , NULL);
      break;
   case 'K' :
      yVIEW_hist_cursor (YDLST_BPREV, NULL);
      break;
   case 'k' :
      yVIEW_hist_cursor (YDLST_PREV , NULL);
      break;
   case 'j' :
      yVIEW_hist_cursor (YDLST_NEXT , NULL);
      break;
   case 'J' :
      yVIEW_hist_cursor (YDLST_BNEXT, NULL);
      break;
   case '~' :
      yVIEW_hist_cursor (YDLST_TAIL , NULL);
      break;
   default  :
      rc = 0;
      break;
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return rc;
}

char         /*-> allow selection of older entries ---[ ------ [ge.TQ5.25#.F9]*/ /*-[03.0000.122.R]-*/ /*-[--.---.---.--]-*/
yview_hist_umode        (char a_major, char a_minor)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        rc          =    0;
   int         x_pos       =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   DEBUG_YVIEW   yLOG_complex ("a_major"   , "%4d, %c, %c", a_major, a_major, ychrvisible (a_major));
   DEBUG_YVIEW   yLOG_complex ("a_minor"   , "%4d, %c, %c", a_minor, a_minor, ychrvisible (a_minor));
   /*---(defenses)-----------------------*/
   DEBUG_YVIEW   yLOG_char    ("mode"      , yMODE_curr ());
   --rce;  if (yMODE_not (UMOD_HISTORY)) {
      DEBUG_YVIEW   yLOG_note    ("not the correct mode");
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return rce;
   }
   /*---(biggies)------------------------*/
   rc = yview_hist__biggies (a_major, a_minor);
   DEBUG_YVIEW   yLOG_value   ("biggies"   , rc);
   if (rc > 0) {
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(escaped chars)------------------*/
   rc = yview_hist__escaped (a_major, &a_minor);
   DEBUG_YVIEW   yLOG_value   ("escaped"   , rc);
   if (rc > 0) {
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return a_major;
   }
   /*---(handle keys)--------------------*/
   rc = yview_hist__marking (a_major, a_minor);
   DEBUG_YVIEW   yLOG_value   ("marking"   , rc);
   if (rc > 0) {
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      if (rc == 1)  return a_minor;
      return 0;
   }
   /*---(handle curoring)----------------*/
   rc = yview_hist__cursoring (a_major, a_minor);
   DEBUG_YVIEW   yLOG_value   ("cursoring" , rc);
   if (rc > 0) {
      if (*s_curr != NULL)   yVIHUB_ySRC_swap ((*s_curr)->h_text);
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(delete)-------------------------*/
   if (a_minor == '#') {
      DEBUG_YVIEW   yLOG_note    ("delete current");
      rc = yview_hist__free_curr   ();
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char
yVIEW_hist_direct       (char b_text [LEN_RECD])
{
   char        rce         =  -10;
   char        rc          =    0;
   int         l           =    0;
   char        x_mode      =  ' ';
   char        t           [LEN_RECD]  = "";
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   DEBUG_YVIEW   yLOG_point   ("b_text"    , b_text);
   --rce;  if (b_text == NULL) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_YVIEW   yLOG_info    ("b_text"    , b_text);
   l = strlen (b_text);
   DEBUG_YVIEW   yLOG_value   ("l"         , l);
   --rce;  if (l < 3) {
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(check mode)---------------------*/
   if      (strncmp (b_text, "::", 2) == 0)  x_mode = MODE_COMMAND;
   else if (strncmp (b_text, "//", 2) == 0)  x_mode = MODE_SEARCH;
   --rce;  if (x_mode == ' ')  {
      DEBUG_YVIEW   yLOG_note    ("does not have :: or // prefix");
      DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   yview_hist__switcher (x_mode, '-');
   /*---(execution on mark)--------------*/
   if (l == 3 || (l == 4 && b_text [3] == '!')) {
      DEBUG_YVIEW   yLOG_note    ("three-letter short-cut");
      if (b_text [2] == '#') {
         DEBUG_YVIEW   yLOG_note    ("requested purge");
         yview_hist__purge (x_mode);
         DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
         return 0;
      }
      rc = yview_hist__marked (b_text [2]);
      --rce;  if (rc < 0) {
         DEBUG_YVIEW   yLOG_note    ("can not find mark");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      --rce;  if (*s_curr == NULL) {
         DEBUG_YVIEW   yLOG_note    ("current is null");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (b_text [3] == '!')  sprintf (b_text, "%c%s", b_text [0], (*s_curr)->h_text, LEN_RECD);
      else                    ystrlcpy (b_text, (*s_curr)->h_text, LEN_RECD);
   }
   /*---(direct save)--------------------*/
   else if (b_text [3] == '=') {
      DEBUG_YVIEW   yLOG_note    ("direct save");
      sprintf (t, "%c%c%s", b_text [0], b_text [1], b_text + 4);
      DEBUG_YVIEW   yLOG_info    ("t"         , t);
      yVIEW_hist_new (x_mode, t);
      yview_hist__mark (b_text [2]);
      --((*s_curr)->h_count);
      ystrlcpy (b_text, "", LEN_RECD);
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 0;
   }
   /*---(mark and unmark)----------------*/
   else if (strchr ("–‘—’“”", b_text [2]) != NULL && (l == 4  || (l == 5 && b_text [4] == '!'))) {
      DEBUG_YVIEW   yLOG_note    ("compounding search");
      rc = yview_hist__marked (b_text [3]);
      --rce;  if (rc < 0) {
         DEBUG_YVIEW   yLOG_note    ("can not find mark");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      --rce;  if (*s_curr == NULL) {
         DEBUG_YVIEW   yLOG_note    ("current is null");
         DEBUG_YVIEW   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
      if (b_text [4] == '!')  sprintf (t, "%c%c%c%s", b_text [0], b_text [0], b_text [2], (*s_curr)->h_text + 1);
      else                    sprintf (t, "%c%c%s"  , b_text [0], b_text [2], (*s_curr)->h_text + 1);
      DEBUG_YVIEW   yLOG_info    ("t"         , t);
      ystrlcpy (b_text, t, LEN_RECD);
      DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
      return 2;
   }
   /*---(macro forced save)--------------*/
   else {
      DEBUG_YVIEW   yLOG_note    ("macro time, but requested to history");
   }
   /*---(report-out)---------------------*/
   DEBUG_YVIEW   yLOG_info    ("b_text"    , b_text);
   /*---(ocmplete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 1;
}




