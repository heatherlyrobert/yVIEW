/*============================----beg-of-source---============================*/
#ifndef yVIEW_priv
#define yVIEW_priv yes



/*===[[ BEG_HEADER ]]=========================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-12345678901-*/

/*===[[ ONE_LINERS ]]=========================================================*/

#define     P_FOCUS     "RS (run-time support)"
#define     P_NICHE     "us (user control)"
#define     P_SUBJECT   "view management"
#define     P_PURPOSE   ""

#define     P_NAMESAKE  ""
#define     P_HERITAGE  ""
#define     P_IMAGERY   ""
#define     P_REASON    ""

#define     P_ONELINE   P_NAMESAKE " " P_SUBJECT

#define     P_BASENAME  "yVIEW"
#define     P_FULLPATH  "/usr/local/lib64/libyVIEW"
#define     P_SUFFIX    ""
#define     P_CONTENT   ""

#define     P_SYSTEM    "gnu/linux   (powerful, ubiquitous, technical, and hackable)"
#define     P_LANGUAGE  "ansi-c      (wicked, limitless, universal, and everlasting)"
#define     P_CODESIZE  "large       (appoximately 10,000 slocl)"
#define     P_DEPENDS   "none"

#define     P_AUTHOR    "heatherlyrobert"
#define     P_CREATED   ""

#define     P_VERMAJOR  "2.--, clean, improve, and expand"
#define     P_VERMINOR  "2.0-, complete and tie yVIKEYS back into it"
#define     P_VERNUM    "2.0a"
#define     P_VERTXT    "first separation from yVIKEYS, unit tested parts finding"

#define     P_PRIORITY  "direct, simple, brief, vigorous, and lucid (h.w. fowler)"
#define     P_PRINCIPAL "[grow a set] and build your wings on the way down (r. bradbury)"
#define     P_REMINDER  "there are many better options, but i *own* every byte of this one"

/*===[[ END_HEADER ]]=========================================================*/

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
#include    <yKEYS.h>             /* heatherly vim-ish key handling           */
#include    <yMODE.h>             /* heatherly vim-ish mode tracking          */
#include    <yMACRO.h>            /* heatherly vim-ish macro processing       */
#include    <yCMD.h>              /* heatherly vim-ish command processing     */
#include    <yCOLOR.h>            /* heatherly opengl color handling          */
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
   int         def_wide;                    /* default width                  */
   int         wide;                        /* screen width                   */
   int         left;                        /* screen left                    */
   /*---(vertical)-------------*/
   cchar       vert;                        /* evaluation order bottom-to-top */
   cchar       noy;                         /* do not add to y cumulatives    */
   cchar       y_tie;                       /* tie to another field in y-axis */
   cchar       under;                       /* fall below buffer/formula      */
   int         def_tall;                    /* default height                 */
   int         tall;                        /* screen height                  */
   int         bott;                        /* screen bottom                  */
   /*---(for std elements)-----*/
   char        orient;                      /* orientation of text            */
   char        (*source) (char*);           /* content source                 */
   char        text        [LEN_RECD];      /* optional text                  */
   /*---(special drawing)------*/
   char        (*drawer) (void);            /* drawing function               */
   char        type;                        /* ortho vs 3d                    */
   char        mgmt;                        /* auto vs custom setup           */
   uchar       anchor;                      /* fixed point for resizing       */
   int         color;                       /* background color               */
   int         xmin;                        /* x-coord minimum                */
   int         xlen;                        /* x-coord range                  */
   int         ymin;                        /* y-coord minimum                */
   int         ylen;                        /* y-coord range                  */
   int         zmin;                        /* z-coord minimum                */
   int         zlen;                        /* z-coord range                  */
   /*---(other)----------------*/
   cchar       desc        [LEN_DESC ];     /* explanation of element         */
   /*---(done)-----------------*/
};
extern tPARTS  g_parts [MAX_PARTS];


typedef    struct    cMY    tMY;
struct cMY {
   int         npart;                       /* total number of window parts   */
};
extern tMY         myVIEW;



/*===[[ yVIEW_base.c ]]=======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yview__unit_quiet       (void);
char        yview__unit_loud        (void);
char        yview__unit_end         (void);



/*===[[ yVIEW_parts.c ]]======================================================*/
/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
char        yview_parts_init        (void);
char        yview_by_abbr           (cchar  a_abbr, tPARTS **a_part, tPARTS **a_link);
char        yview_by_cursor         (cchar  a_move, tPARTS **a_part, tPARTS **a_link);
char*       yview_parts_name        (cchar n);


char        yview_horz_fixed        (void);
char        yview_horz_auto         (cint a_wide, cint a_alt);
char        yview_horz_var          (void);
char        yview_horz_link         (void);
char        yview_horz__float       (tPARTS *p, int a_left);
char        yview_horz__menus       (tPARTS *p, int a_left);
char        yview_horz__hist        (tPARTS *p, int a_left);
char        yview_horz_float        (void);
char        yview_horz_other        (void);

#endif

