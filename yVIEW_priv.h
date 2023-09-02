/*============================----beg-of-source---============================*/
#ifndef yVIEW_priv
#define yVIEW_priv yes


/*===[[ HEADER BEG ]]=========================================================*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*········· ··········· ´·····························´········································*/
#define     P_NAME      "yVIEW"
/*········· ··········· ´·····························´········································*/
#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "windor/view management"
#define     P_PURPOSE   ""
/*········· ··········· ´·····························´········································*/
#define     P_NAMESAKE  "iapetus-progonos (progenitor)"
#define     P_PRONOUNCE ""
#define     P_HERITAGE  "titan and father of prometheus, protector of mankind"
#define     P_BRIEFLY   ""
#define     P_IMAGERY   ""
#define     P_REASON    ""
/*········· ··········· ´·····························´········································*/
#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT
/*········· ··········· ´·····························´········································*/
#define     P_HOMEDIR   "/home/system/yVIEW.vimish_view_management"
#define     P_BASENAME  "yVIEW"
#define     P_FULLPATH  "/usr/local/lib64/libyVIEW"
#define     P_SUFFIX    "···"
#define     P_CONTENT   "···"
/*········· ··········· ´·····························´········································*/
#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_COMPILER  "gcc 11.3.0"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
/*········· ··········· ´·····························´········································*/
#define     P_DEPSTDC   "stdio,stdlib,string,math,time"
#define     P_DEPEXTEND "···"
#define     P_DEPCORE   "yURG,yLOG,ySTR"
#define     P_DEPVIKEYS "yVIHUB,yMODE,yKEYS"
#define     P_DEPOTHER  ""
#define     P_DEPSOLO   "yCOLOR,yDLST"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.1-, convert to yVIHUB and new way"
#define     P_VERNUM    "2.1o"
#define     P_VERTXT    "small fix to ySRC_switch_add to allow longer terses"
/*········· ··········· ´·····························´········································*/
#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"
/*········· ··········· ´·····························´········································*/
/*--------- 12345678901 ´123456789-123456789-123456789-123456789-123456789-123456789-123456789-*/
/*                      ´·········1·········2·········3·········4·········5·········6·········7*/
/*===[[ HEADER END ]]=========================================================*/



/*---(ansi-c standard)-------------------*/
#include    <stdio.h>             /* clibc  standard input/output             */
#include    <stdlib.h>            /* clibc  standard general purpose          */
#include    <string.h>            /* clibc  standard string handling          */
#include    <math.h>              /* clibc  standard math library             */
#include    <time.h>              /* clibc  time related functions            */
/*---(custom)----------------------------*/
#include    <yURG.h>              /* heatherly urgent processing              */
#include    <yLOG.h>              /* heatherly program logging                */
#include    <ySTR.h>              /* heatherly string processing              */

#include    <yVIHUB.h>
#include    <yKEYS.h>             /* heatherly vi-keys key handling           */
#include    <yMODE.h>             /* heatherly vi-keys mode tracking          */

#include    <yPARSE.h>

#include    <yCOLOR_solo.h>       /* heatherly opengl color handling          */
#include    <yDLST_solo.h>        /* heatherly double-double-list             */



#define      YVIEW_MAX_PARTS         30
typedef  struct  cYVIEW_PARTS     tYVIEW_PARTS;
struct cYVIEW_PARTS {
   /*---(main)-----------------*/
   cchar       abbr;                        /* short name of screen element   */
   cchar       name        [LEN_LABEL];     /* name of screen element         */
   cchar       own;                         /* controlled entirely by yVIKEYS */
   char        on;                          /* show or hide y/n               */
   /*---(horizontal)-----------*/
   cchar       horz;                        /* evaluation order left-to-right */
   cchar       nox;                         /* do not add to x cumulatives    */
   cchar       x_tie;                       /* tie to another field in x-axis */
   short       def_wide;                    /* default width                  */
   short       wide;                        /* screen width                   */
   short       left;                        /* screen left                    */
   /*---(vertical)-------------*/
   cchar       vert;                        /* evaluation order bottom-to-top */
   cchar       noy;                         /* do not add to y cumulatives    */
   cchar       y_tie;                       /* tie to another field in y-axis */
   cchar       under;                       /* fall below buffer/formula      */
   short       def_tall;                    /* default height                 */
   short       tall;                        /* screen height                  */
   short       bott;                        /* screen bottom                  */
   /*---(shared drawing)-------*/
   cchar       defs;                        /* changable defaults (w/t/B)     */
   char        (*source) (char, short, char*);   /* content source            */
   char        text        [LEN_RECD];      /* optional text                  */
   char        (*drawer) (void);            /* drawing function               */
   /*---(curses drawing)-------*/
   cchar       orient;                      /* curses orientation of text     */
   /*---(opengl drawing)-------*/
   char        type;                        /* ortho vs 3d                    */
   char        mgmt;                        /* auto vs custom setup           */
   uchar       anchor;                      /* fixed point for resizing       */
   char        cmajor;                      /* major color group              */
   char        cminor;                      /* color accent                   */
   short       xmin;                        /* x-coord minimum                */
   short       xlen;                        /* x-coord range                  */
   short       ymin;                        /* y-coord minimum                */
   short       ylen;                        /* y-coord range                  */
   short       zmin;                        /* z-coord minimum                */
   short       zlen;                        /* z-coord range                  */
   /*---(other)----------------*/
   cchar       desc        [LEN_DESC ];     /* explanation of element         */
   /*---(done)-----------------*/
};
extern tYVIEW_PARTS  gVIEW_parts [YVIEW_MAX_PARTS];


#define      YVIEW_OVER_FULL        "GCO"
#define      YVIEW_OVER_WIND        "NZ"

#define      YVIEW_OWN_FULLY        'y'   /* only change color, text, and hiding    */
#define      YVIEW_OWN_PARTLY       'p'   /* change hiding, color, and drawing      */
#define      YVIEW_OWN_LITTLE       's'   /* change anything and everything         */
#define      YVIEW_OWN_MAIN         'm'   /* change anything and everything         */
#define      YVIEW_OWN_UNDERLAY     'u'   /* drawn before main                      */
#define      YVIEW_OWN_OVERLAY      'o'   /* drawn on top of main                   */
#define      YVIEW_OWN_WINDOW       'w'   /* drawn on top of full window            */
#define      YVIEW_OWN_FLOAT        'f'   /* drawn over part of full window         */
#define      YVIEW_OWN_DATA         '-'   /* just a data holder                     */

#define      YVIEW_OWN_SETUP        "ypsm"
#define      YVIEW_OWN_HIDE         "ypso"
#define      YVIEW_OWN_REANCHOR     "yp"

#define      YVIEW_OWN_COMPLEX      "mso"
#define      YVIEW_OWN_MODERATE     "msp"
#define      YVIEW_OWN_SIMPLE       "po"


typedef    struct    cYVIEW_MY    tYVIEW_MY;
struct cYVIEW_MY {
   char        env;                         /* curses vs opengl               */
   char        npart;                       /* total number of window parts   */
   short       orig_wide;
   short       orig_tall;
   short       main_wide;
   short       main_tall;
   short       alt_wide;
   short       full_wide;
   short       full_tall;
   char        loc_float;
   char        loc_menu;
   char        loc_hist;
   char        s_wide;
   char        s_size;
   char        prog_full;
   char        note_curr;
   char        note_prev;
   char        note_lcurr;
   char        note_lprev;
   char        p_formula;
   char        redraw;
};
extern tYVIEW_MY         myVIEW;


extern char           unit_answer [LEN_FULL];



#define      YVIEW_MAX_NOTES     30
typedef    struct    cYVIEW_NOTE  tYVIEW_NOTE;
struct cYVIEW_NOTE {
   char        xr, yr, size;                /* requested pos and size         */
   char        s;                           /* main vs window on note box     */
   short       x, y;                        /* note top-left pos              */
   short       w, h;                        /* note size                      */
   char       *text;                        /* text to be displayed           */
   char        st;                          /* main vs window on target       */
   char        xt, yt;                      /* requested endpoint grid        */
   short       xb, yb;                      /* connector beginning pos        */
   short       xe, ye;                      /* connector ending pos           */
   char        q;                           /* connector end quad             */
   char        c;                           /* connector type                 */
};
extern tYVIEW_NOTE  gVIEW_notes [YVIEW_MAX_NOTES];
extern char   gVIEW_nnote;






/*===[[ yVIEW_base.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yview_init              (void);
/*---(unittest)-------------*/
char        yview__unit_quiet       (void);
char        yview__unit_loud        (void);
char        yview__unit_end         (void);
char        yview__unit_cleanse     (void);
char        yview__unit_prep        (char a_abbr);
char        yview__unit_draw        (void);
char        yview__unit_cursor      (void);
char        yview__unit_refresh     (void);
/*---(done)-----------------*/



/*===[[ yVIEW_parts.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(program)--------------*/
char        yview_parts_init        (void);
/*---(search)---------------*/
char        yview_by_abbr           (cchar  a_abbr, tYVIEW_PARTS **r_part, tYVIEW_PARTS **r_link);
char        yview_by_index          (int n, tYVIEW_PARTS **r_part, tYVIEW_PARTS **r_link);
char        yview_by_name           (cchar *a_name, tYVIEW_PARTS **r_part, tYVIEW_PARTS **r_link);
char        yview_by_cursor         (cchar  a_move, tYVIEW_PARTS **r_part, tYVIEW_PARTS **r_link);
char*       yview_parts_name        (cchar n);
/*---(defaults)-------------*/
char        yview_factory           (cchar a_env);
char        yview_clear             (void);
/*---(anchoring)------------*/
char        yview_anchor_calc       (char a_abbr);
char        yview_anchor_calc_all   (void);
char        yview_get_anchor        (char a_abbr);
char        yview_set_anchor        (char a_abbr, char a_anchor);
/*---(done)-----------------*/



/*===[[ yVIEW_horz.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(detail)---------------*/
char        yview_horz_fixed        (void);
char        yview_horz_auto         (cint a_wide, cint a_alt);
char        yview_horz_var          (void);
char        yview_horz_link         (void);
char        yview_horz__float       (tYVIEW_PARTS *m, tYVIEW_PARTS *p);
char        yview_horz__menus       (tYVIEW_PARTS *m, tYVIEW_PARTS *p);
char        yview_horz__hist        (tYVIEW_PARTS *m, tYVIEW_PARTS *p);
char        yview_horz_float        (void);
char        yview_horz_final        (void);
/*---(coords)---------------*/
char        yview_horz_coords       (void);
char        yview_horz_overlay      (void);
/*---(driver)---------------*/
char        yview_horz              (cint a_wide, cint a_alt);
/*---(done)-----------------*/



/*===[[ yVIEW_vert.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(detail)---------------*/
char        yview_vert_fixed        (void);
char        yview_vert_auto         (cint a_tall);
char        yview_vert_var          (void);
char        yview_vert_link         (void);
char        yview_vert__float       (tYVIEW_PARTS *m, tYVIEW_PARTS *p);
char        yview_vert__menus       (tYVIEW_PARTS *m, tYVIEW_PARTS *p);
char        yview_vert__hist        (tYVIEW_PARTS *m, tYVIEW_PARTS *p);
char        yview_vert_float        (void);
char        yview_vert_final        (void);
char        yview_vert_flip         (void);
/*---(coords)---------------*/
char        yview_vert_coords       (void);
char        yview_vert_overlay      (void);
/*---(driver)---------------*/
char        yview_vert              (cint a_tall);
/*---(done)-----------------*/



/*===[[ yVIEW_layout.c ]]=====================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yview_layout_init       (void);



/*===[[ yVIEW_conf.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(support)--------------*/
char        yview_conf_text         (char a_part, char *a_text);
/*---(sizing)---------------*/
char        yview_update            (void);
/*---(done)-----------------*/



/*===[[ yVIEW_note.c ]]=======================================================*/
/*··········>·······················>·········································*/
/*---(support)--------------*/
char        yview_note__find        (char xr, char yr);
/*---(ordering)-------------*/
char        yview_note__remove      (char n);
char        yview_note__totop       (char n);
char        yview_note__tobot       (char n);
char        yview_note__move        (char n, char xr, char yr);
/*---(mass)-----------------*/
char        yview_note__purge       (char a_init);
char        yview_note__purgeish    (void);
char        yview_note__resize      (void);
char        yview_note_init         (void);
/*---(content)--------------*/
char        yview_note__pct         (char a_type, char a_code, float *r_pct);
char        yview_note__x           (char a_env, short a_left, short a_wide, short w, char xr, short *x);
char        yview_note__y           (char a_env, short a_bott, short a_tall, short h, char yr, short *y);
char        yview_note__sizer       (char a_env, char a_size, char *r_size, short *r_wide, short *r_high);
char        yview_note__position    (char a_env, char a_part, char a_size, short *b_wide, short *b_high, char xr, char yr, char *r_part, char *r_xr, char *r_yr, short *r_x, short *r_y);
/*> char        yview_note__size        (char n, char xr, char yr, char a_size);      <*/
char        yview_note__end         (char a_type, char a_xt, char a_yt, char *r_scope, short *r_xe, short *r_ye);
char        yview_note__quad        (short a_x, short a_y, short a_wide, short a_tall, short a_xe, short a_ye, char *r_quad, short *a_cen, short *a_mid);
char        yview_note__dir         (char a_type, char a_quad, short a_cen, short a_mid, short a_xe, short a_ye, char *r_dir);
/*> char        yview_note__dir_OLD     (char a_type, short a_x, short a_y, short w, short h, short a_xe, short a_ye, char *r_dir);   <*/
char        yview_note__begin       (char n, char a_dir, short x_cen, short x_mid, short *r_xb, short *r_yb);
char        yview_note__retarg      (char n);
/*---(driver)---------------*/
char        yview_note__parse_text  (char a_source [LEN_RECD], char *r_concat, char r_text [LEN_RECD], char *r_scope, char r_target [LEN_TERSE]);
char        yview_note_add          (char a_part, char a_xr, char a_yr, char a_size, char a_text [LEN_RECD]);
char        yview_note_add_OLD      (char a_part, char a_xr, char a_yr, char a_size, char *a_text);
char        yview_note_update       (void);
char        yVIEW_note_direct       (char *a_all);
/*---(access)---------------*/
char        yVIEW_note_showing      (void);
char        yVIEW_note_data         (char n, uchar *m, uchar *s, short *x, short *y, short *w, short *h, uchar *t, uchar *c, short *xb, short *yb, short *xe, short *ye);
char        yview_note_line         (char a_curr, char a_prev);
char        yview_note_notes        (char a_curr, char a_prev);
char        yVIEW_note_colors       (char *a_curr, char *a_prev, char *a_lcurr, char *a_lprev);
char        yVIEW_redraw            (char *a_redraw);
/*---(unittest)-------------*/
char*       yview_note__unit        (char *a_question, int n);
/*---(done)-----------------*/

char        yview_notes_dump        (void *f);



/*===[[ yVIEW_note.c ]]=======================================================*/
/*··········>·······················>·········································*/
/*---(support)--------------*/
char        yview_hist__switcher    (char a_mode, char a_force);
/*---(marks)----------------*/
char        yview_hist__valid       (char a_abbr);
char        yview_hist__unmark      (uchar a_mark);
char        yview_hist__mark        (uchar a_mark);
/*---(memory)---------------*/
char        yVIEW_hist_new          (char a_mode, uchar *a_text);
char        yview_hist__purge       (char a_mode);
/*---(program)--------------*/
char        yview_hist_init         (void);
/*---(search)---------------*/
char        yVIEW_hist_cursor      (char a_move, int *r_index);
char        yview_hist__index       (int a_index);
char        yview_hist__find        (uchar *a_text);
char        yview_hist__marked      (uchar a_mark);
char        yview_hist__roll        (void);
/*---(display)--------------*/
char        yVIEW_hist_header       (short a_wide, char *a_entry);
char        yVIEW_hist_footer       (short a_wide, char *a_entry);
char        yVIEW_hist_entry        (short a_wide, char *a_entry);
char        yview_hist__force       (int a_count, int a_ran, int a_found);
/*---(mode)-----------------*/
char        yview_hist_prepper      (void);
char        yview_hist__biggies     (char a_major, char a_minor);
char        yview_hist__escaped     (char a_major, char *b_minor);
char        yview_hist__marking     (char a_major, char a_minor);
char        yview_hist__cursoring   (char a_major, char a_minor);
char        yview_hist_umode        (char a_major, char a_minor);
char        yVIEW_hist_direct       (char b_text [LEN_RECD]);
/*---(unittest)-------------*/
char*       yview_hist__unit        (char *a_question, int n);
/*---(done)-----------------*/



char        yview_formula_init      (void);
char        yview_formula_min       (void);
char        yview_formula_small     (void);
char        yview_formula_label     (void);
char        yview_formula_format    (void);
char        yview_formula_max       (void);


#endif

