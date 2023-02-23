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
#define     P_DEPOTHER  "yCOLOR"
#define     P_DEPSOLO   "yCOLOR,YDLST"
/*········· ··········· ´·····························´········································*/
#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""
/*········· ··········· ´·····························´········································*/
#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.1-, convert to yVIHUB and new way"
#define     P_VERNUM    "2.1d"
#define     P_VERTXT    "note can create reliable target gridlines (Š).  and remove them"
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

#include    <yCOLOR.h>            /* heatherly opengl color handling          */
#include    <yCOLOR_solo.h>       /* heatherly opengl color handling          */
#include    <yDLST_solo.h>        /* heatherly double-double-list             */



#define      MAX_PARTS         30
typedef  struct  cPARTS     tPARTS;
struct cPARTS {
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
extern tPARTS  g_parts [MAX_PARTS];


#define      OVER_FULL        "GCO"
#define      OVER_WIND        "NZ"

#define      OWN_FULLY        'y'   /* only change color, text, and hiding    */
#define      OWN_PARTLY       'p'   /* change hiding, color, and drawing      */
#define      OWN_LITTLE       's'   /* change anything and everything         */
#define      OWN_MAIN         'm'   /* change anything and everything         */
#define      OWN_UNDERLAY     'u'   /* drawn before main                      */
#define      OWN_OVERLAY      'o'   /* drawn on top of main                   */
#define      OWN_WINDOW       'w'   /* drawn on top of full window            */
#define      OWN_FLOAT        'f'   /* drawn over part of full window         */
#define      OWN_DATA         '-'   /* just a data holder                     */

#define      OWN_SETUP        "ypsm"
#define      OWN_HIDE         "ypso"
#define      OWN_REANCHOR     "yp"

#define      OWN_COMPLEX      "mso"
#define      OWN_MODERATE     "msp"
#define      OWN_SIMPLE       "po"


typedef    struct    cMY    tMY;
struct cMY {
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
   char        note_line;
};
extern tMY         myVIEW;


extern char           unit_answer [LEN_FULL];



#define      MAX_NOTES     20
typedef    struct    cNOTE  tNOTE;
struct cNOTE {
   char        xr, yr, size;                /* requested pos and size         */
   char        s;                           /* main vs window on note box     */
   short       x, y;                        /* note top-left pos              */
   short       w, h;                        /* note size                      */
   char       *text;                        /* text to be displayed           */
   char        c;                           /* connector type                 */
   char        st;                          /* main vs window on target       */
   short       xt, yt;                      /* requested endpoint grid        */
   short       xb, yb;                      /* connector beginning pos        */
   short       xe, ye;                      /* connector ending pos           */
};
extern tNOTE  g_notes [MAX_NOTES];
extern char   g_nnote;






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
char        yview_by_abbr           (cchar  a_abbr, tPARTS **r_part, tPARTS **r_link);
char        yview_by_index          (int n, tPARTS **r_part, tPARTS **r_link);
char        yview_by_name           (cchar *a_name, tPARTS **r_part, tPARTS **r_link);
char        yview_by_cursor         (cchar  a_move, tPARTS **r_part, tPARTS **r_link);
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
char        yview_horz__float       (tPARTS *m, tPARTS *p);
char        yview_horz__menus       (tPARTS *m, tPARTS *p);
char        yview_horz__hist        (tPARTS *m, tPARTS *p);
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
char        yview_vert__float       (tPARTS *m, tPARTS *p);
char        yview_vert__menus       (tPARTS *m, tPARTS *p);
char        yview_vert__hist        (tPARTS *m, tPARTS *p);
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
char        yview_note__size        (char n, char xr, char yr, char a_size);
char        yview_note__retarg      (char n);
/*---(driver)---------------*/
char        yview_note_add          (char a_part, char a_xr, char a_yr, char a_size, char *a_text);
char        yview_note_update       (void);
char        yVIEW_note_direct       (char *a_all);
/*---(access)---------------*/
char        yVIEW_note_showing      (void);
char        yVIEW_note_data         (char n, uchar *m, uchar *s, short *x, short *y, short *w, short *h, uchar *t, uchar *c, short *xb, short *yb, short *xe, short *ye);
/*---(unittest)-------------*/
char*       yview_note__unit        (char *a_question, int n);
/*---(done)-----------------*/



#endif

