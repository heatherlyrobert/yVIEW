/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



#define      MAX_LAYOUT        10
typedef struct cLAYOUT   tLAYOUT;
struct cLAYOUT {
   char        name        [LEN_LABEL];     /* title for layout               */
   char        parts       [LEN_DESC ];     /* selection of elements          */
   char        desc        [LEN_DESC ];     /* explanation of layout          */
};
static const tLAYOUT   s_layouts [] = {
   /*---name------    tv bf nLY Xmap dr xsck G FMH  ,  12345678901234567890123456789012345678901234567890  */
   { "ANSWER_KEY"  , "tv bf nLY Xmap dr xsck G FMH" , "answer key to order and spacing"                      },
   { "min"         , "-- -- --- -m-- -- ---- - FMH" , "smallest footprint, least elements showing"           },
   { "starter"     , "-- -- --- -m-- -- --ck - FMH" , "little footprint for new applications"                },
   { "work"        , "tv -- --- -m-- -- xsck - FMH" , "more balanced display of common elements"             },
   { "rob"         , "tv -- --- -m-- -- xsc- - FMH" , "more balanced display of common elements"             },
   { "max"         , "tv bf n-- -m-p dr xsck - FMH" , "everything displays at one time"                      },
   { "ycolor"      , "tv bf n-- -map -r xsck - FMH" , "more balanced display of common elements"             },
   { "gyges"       , "-- -f --Y Xm-- -- xsck - FMH" , "prepared for gyges spreadsheet"                       },
   { "everything"  , "tv bf n-Y Xmap dr xsck - FMH" , "everything displays at one time"                      },
   { ""            , "-- -- --- ---- -- ---- - FMH" , ""                                                     },
};
static int  s_nlayout   = MAX_LAYOUT;

#define      MAX_OPTION      50
typedef  struct  cOPTION    tOPTION;
struct cOPTION  {
   char        part;
   char        terse       [LEN_SHORT];
   char        opt         [LEN_LABEL];
   void       *source;
   char        desc        [LEN_DESC ];
};
tOPTION  s_options [MAX_OPTION ] = {
   { YVIEW_STATUS  , "mod"   , "mode"         , yMODE_status           , "display the mode stack"                   },
   { YVIEW_STATUS  , "key"   , "keylog"       , yKEYS_keylog_status    , "displays keystroke history"               },
   { YVIEW_STATUS  , "log"   , "logger"       , yKEYS_logger_status    , "displays logging statistics"              },
   { YVIEW_STATUS  , "loo"   , "loop"         , yKEYS_loop_status      , "displays main looping statistics"         },
   { YVIEW_STATUS  , "rec"   , "record"       , yMACRO_rec_status      , "details of current macro recording"       },
   { YVIEW_STATUS  , "exe"   , "execute"      , yMACRO_exe_status      , "details of single macro playback"         },
   { YVIEW_STATUS  , "mex"   , "multiexe"     , yMACRO_mex_status      , "details of layered macro playback"        },
   /*> { YVIEW_STATUS  , "script"       , "script"       , yMACRO_script_status   , "details of script playback"               },   <*/
   /*> { YVIEW_STATUS  , "empty"        , "empty"        , VIEW_status_default    , "empty status display"        },                               <* 
    *> { YVIEW_STATUS  , "xmap"         , "xmap"         , yvikeys_map_xstatus    , "x-axis position details"     },                               <* 
    *> { YVIEW_STATUS  , "ymap"         , "ymap"         , yvikeys_map_ystatus    , "y-axis position details"     },                               <* 
    *> { YVIEW_STATUS  , "treg"         , "treg"         , yvikeys_sreg_status    , "displays contents of treg"   },                               <* 
    *> { YVIEW_STATUS  , "words"        , "words"        , SOURCE_status_words    , "displays word breaks"        },                               <* 
    *> { YVIEW_STATUS  , "select"       , "select"       , yvikeys_sreg_status_sel, "displays selection status"   },                               <* 
    *> { YVIEW_STATUS  , "visual"       , "visual"       , yvikeys_visu_status    , "visual selection in map"     },                               <* 
    *> { YVIEW_STATUS  , "file"         , "file"         , yvikeys_file_status    , "file, control, and version"  },                               <* 
    *> { YVIEW_STATUS  , "regs"         , "regs"         , yvikeys_mreg_status    , "current register information"},                               <* 
    *> { YVIEW_STATUS  , "delay"        , "delay"        , yvikeys_delay_status   , "main loop timing settings"   },                               <* 
    *> { YVIEW_STATUS  , "prog"         , "prog"         , yvikeys_prog_status    , "progress bar playing"        },                               <* 
    *> { YVIEW_STATUS  , "main"         , "main"         , yvikeys_main_status    , "main loop timing results"    },                               <* 
    *> { YVIEW_STATUS  , "file"         , "file"         , yvikeys_file_status    , "current fully qualified file name and default location"  },   <* 
    *> { YVIEW_STATUS  , "version"      , "version"      , yvikeys_vers_status    , "current file verion control status, number and text"     },   <* 
    *> { YVIEW_STATUS  , "mark"         , "mark"         , yvikeys_mark_status    , "details of mark environment"                },                <* 
    *> { YVIEW_STATUS  , "hint"         , "hint"         , yvikeys_hint_status    , "details of hint environment"              },                  <* 
    *> { YVIEW_STATUS  , "search"       , "search"       , yvikeys_srch_status    , "details of search environment"            },                  <* 
    *> { YVIEW_STATUS  , "sreg"         , "sreg"         , yvikeys_sreg_status    , "details of current source register" },                        <* 
    *> { YVIEW_STATUS  , "sundo"        , "sundo"        , yvikeys_sundo_status   , "source editing undo stack" },                                 <* 
    *> { YVIEW_GRID    , "norm"         , "norm"         , VIEW__grid_normal      , "traditional cross-hatch grid" },                              <* 
    *> { YVIEW_GRID    , "zoom"         , "zoom"         , VIEW__grid_zoom        , "zoom/targeting grid"          },                              <* 
    *> { YVIEW_STATUS  , "visual"       , "visual"       , yvikeys_visu_status    , "details of visual selection"  },                              <*/
   { NULL            , ""             , ""             , NULL                   , ""                            },
};
static int  s_noption  = MAX_OPTION;



/*====================------------------------------------====================*/
/*===----                          full layouts                        ----===*/
/*====================------------------------------------====================*/
static void  o___FULL____________o () { return; }

char
yview_layout_init       (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   /*---(screen layouts)-----------------*/
   s_nlayout = 0;
   for (i = 0; i < MAX_LAYOUT; ++i) {
      if (s_layouts [i].name [0] == 0)  break;
      ++s_nlayout;
   }
   /*---(element options)----------------*/
   s_noption = 0;
   for (i = 0; i < MAX_OPTION; ++i) {
      if (s_options [i].part     == 0)  break;
      ++s_noption;
   }
   /*---(complete)-----------------------*/
   return 0;
}

char
yview_layout            (char *a_name)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   char        i           =    0;
   char        n           =   -1;
   int         x_len       =    0;
   uchar       x_ch        =    0;
   uchar       x_key       =    0;
   tPARTS     *p           = NULL;
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*> DEBUG_PROG   yLOG_complex ("origs"     , "%3dw, %3dt, %3da", s_orig_wide, s_orig_tall, s_alt_wide);   <*/
   /*---(defense)------------------------*/
   DEBUG_GRAF   yLOG_point   ("a_name"    , a_name);
   --rce;  if (a_name == NULL || a_name [0] == '\0') {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_name"    , a_name);
   /*---(find the layout)----------------*/
   for (i = 0; i < s_nlayout; ++i) {
      DEBUG_GRAF   yLOG_info    ("check"     , s_layouts [i].name);
      if (s_layouts [i].name [0] != a_name [0])         continue;
      if (strcmp (s_layouts [i].name, a_name) != 0)     continue;
      n = i;
      break;
   }
   DEBUG_GRAF   yLOG_value   ("result"    , n);
   --rce;  if (n < 0) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   /*---(clear the parts)----------------*/
   yview_clear ();
   /*---(set parts)----------------------*/
   x_len = strlen (s_layouts [n].parts);
   for (i = 0; i < x_len; ++i) {
      x_ch  = s_layouts [n].parts [i];
      x_key = s_layouts [0].parts [i];
      if (x_key == ' ' || x_key == '-')   continue;
      yview_by_abbr (x_key, &p, NULL);
      if (p == NULL)                      continue;
      if (x_ch == x_key && p->on != 'X')  p->on = 'y';
      if (x_ch == ' ' || x_ch == '-')     p->on = '-';
   }
   /*---(reset)--------------------------*/
   /*> yvikeys_sizes_resize ('r');                                                    <*/
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}



/*====================------------------------------------====================*/
/*===----                      individual elements                     ----===*/
/*====================------------------------------------====================*/
static void  o___ELEMENTS________o () { return; }

char
yVIEW_switch_add        (char a_part, char *a_opt, void *a_source, char *a_desc)
{
   /*> /+---(locals)-----------+-----+-----+-+/                                                 <* 
    *> char        rce         =  -10;                                                          <* 
    *> char        x_on        =  '-';                                                          <* 
    *> char        i           =    0;                                                          <* 
    *> char        n           =   -1;                                                          <* 
    *> char        a           =   -1;                                                          <* 
    *> /+---(header)-------------------------+/                                                 <* 
    *> DEBUG_GRAF   yLOG_enter   (__FUNCTION__);                                                <* 
    *> /+---(defense)------------------------+/                                                 <* 
    *> n = yvikeys_view__abbr (a_part);                                                         <* 
    *> --rce;  if (n < 0) {                                                                     <* 
    *>    DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> /+> DEBUG_GRAF   yLOG_info    ("name"      , s_parts [n].name);                    <+/   <* 
    *> /+> DEBUG_GRAF   yLOG_char    ("abbr"      , s_parts [n].abbr);                    <+/   <* 
    *> --rce;  if (a_opt == NULL) {                                                             <* 
    *>    DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_GRAF   yLOG_info    ("a_opt"     , a_opt);                                         <* 
    *> --rce;  if (a_source == NULL) {                                                          <* 
    *>    DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);                                        <* 
    *>    return rce;                                                                           <* 
    *> }                                                                                        <* 
    *> DEBUG_GRAF   yLOG_point   ("a_source"  , a_source);                                      <* 
    *> /+---(add)----------------------------+/                                                 <* 
    *> s_options [s_noption].part   = a_part;                                                   <* 
    *> strlcpy (s_options [s_noption].opt, a_opt, LEN_LABEL);                                   <* 
    *> s_options [s_noption].source = a_source;                                                 <* 
    *> if (a_desc != NULL)  strlcpy (s_options [s_noption].desc, a_desc, LEN_LABEL);            <* 
    *> ++s_noption;                                                                             <* 
    *> DEBUG_GRAF   yLOG_value   ("s_noption" , s_noption);                                     <* 
    *> /+---(complete)-----------------------+/                                                 <* 
    *> DEBUG_GRAF   yLOG_exit    (__FUNCTION__);                                                <* 
    *> return 0;                                                                                <*/
}

char
yview__switch_linked    (tPARTS *p)
{
   tPARTS     *a           = NULL;
   tPARTS     *x_ind       = NULL;
   tPARTS     *x_dep       = NULL;
   DEBUG_GRAF   yLOG_senter  (__FUNCTION__);
   /*---(get alternate)------------------*/
   switch (p->abbr) {
   case YVIEW_TITLE    :  yview_by_abbr (YVIEW_VERSION, &a, NULL);  break;
   case YVIEW_STATUS   :  yview_by_abbr (YVIEW_MODES  , &a, NULL);  break;
   case YVIEW_COMMAND  :  yview_by_abbr (YVIEW_KEYS   , &a, NULL);  break;
   case YVIEW_VERSION  :  yview_by_abbr (YVIEW_TITLE  , &a, NULL);  break;
   case YVIEW_MODES    :  yview_by_abbr (YVIEW_STATUS , &a, NULL);  break;
   case YVIEW_KEYS     :  yview_by_abbr (YVIEW_COMMAND, &a, NULL);  break;
   case YVIEW_NAV      :  yview_by_abbr (YVIEW_LAYERS , &a, NULL);  break;
   case YVIEW_LAYERS   :  yview_by_abbr (YVIEW_NAV    , &a, NULL);  break;
   default   :
                            DEBUG_GRAF   yLOG_snote   ("not a target");
                            DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
                            return 0;;
   }
   /*---(handle switching)---------------*/
   switch (p->abbr) {
   case YVIEW_TITLE    : case YVIEW_STATUS   : case YVIEW_COMMAND  :
      DEBUG_GRAF   yLOG_snote   ("independent");
      if      (p->on == '-' && a->on == 'y')  a->on = '-';
      break;
   case YVIEW_VERSION  : case YVIEW_MODES    : case YVIEW_KEYS     :
      DEBUG_GRAF   yLOG_snote   ("dependent");
      if      (a->on == 'X')                  p->on = '-';
      else if (p->on == 'y' && a->on == '-')  a->on = 'y';
      break;
   case YVIEW_NAV      : case YVIEW_LAYERS   :
      DEBUG_GRAF   yLOG_snote   ("either/or");
      if      (p->on == 'y' && a->on == 'y')  a->on = '-';
      break;
   }
   DEBUG_GRAF   yLOG_sexit   (__FUNCTION__);
   return 0;
}

char
yview_switch            (char *a_name, char *a_opt)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rce         =  -10;
   tPARTS     *p           = NULL;
   char        x_on        =  '-';
   char        i           =    0;
   char        n           =   -1;
   char        x_good      =  '-';
   /*---(header)-------------------------*/
   DEBUG_GRAF   yLOG_enter   (__FUNCTION__);
   /*---(defense)------------------------*/
   yview_by_name (a_name, &p, NULL);
   --rce;  if (p == NULL) {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   --rce;  if (a_opt == NULL || a_opt [0] == '\0') {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_info    ("a_opt"     , a_opt);
   --rce;  if (p->on == 'X') {
      if (strcmp (a_opt, "enable" ) != 0) {
         DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
         return rce;
      }
   }
   /*---(set the flag)-------------------*/
   DEBUG_GRAF   yLOG_char    ("current"   , p->on);
   x_on = p->on;
   if        (strcmp (a_opt, "hide"   ) == 0) {
      p->on  = '-';
      x_good = 'y';
   } else if (strcmp (a_opt, "show"   ) == 0) {
      p->on  = 'y';
      x_good = 'y';
   } else if (strcmp (a_opt, "enable" ) == 0) {
      p->on  = 'y';
      x_good = 'y';
   } else if (strcmp (a_opt, "disable") == 0) {
      p->on  = 'X';
      x_good = 'y';
   } else {
      for (i = 0; i < s_noption; ++i) {
         if (s_options [i].part == NULL)                   break;
         if (s_options [i].part != p->abbr)       continue;
         if (strcmp (s_options [i].opt, a_opt ) != NULL && strcmp (s_options [i].terse, a_opt) != NULL)  continue;
         p->on     = 'y';
         p->source = s_options [i].source;
         x_good    = 'y';
         break;
      }
   }
   DEBUG_GRAF   yLOG_char    ("x_good"    , x_good);
   --rce;  if (x_good != 'y') {
      DEBUG_GRAF   yLOG_exitr   (__FUNCTION__, rce);
      return rce;
   }
   DEBUG_GRAF   yLOG_char    ("new"       , p->on);
   DEBUG_GRAF   yLOG_point   ("source"    , p->source);
   /*---(handle linkages)----------------*/
   yview__switch_linked     (p);
   /*---(resize)-------------------------*/
   /*> if (x_on != p->on) {                                                           <* 
    *>    DEBUG_GRAF   yLOG_note    ("must resize");                                  <* 
    *>    yvikeys_sizes_resize ('r');                                                 <* 
    *>    myVIKEYS.redraw = 'y';                                                      <* 
    *> }                                                                              <*/
   /*---(complete)-----------------------*/
   DEBUG_GRAF   yLOG_exit    (__FUNCTION__);
   return 0;
}