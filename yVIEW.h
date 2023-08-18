/*============================----beg-of-source---============================*/
#ifndef yVIEW
#define yVIEW yes

#include    <ySTR_solo.h>


typedef  unsigned char        uchar;
typedef  const char           cchar;
typedef  const int            cint;


#define      YVIEW_LEAVE       -1

#define      YVIEW_OPENGL      'g'
#define      YVIEW_CURSES      'c'
#define      YVIEW_ENVS        "gc"


/*---(normal)-------------------------*/
#define      YVIEW_TITLE       't'
#define      YVIEW_BUFFER      'b'
#define      YVIEW_FORMULA     'f'
#define      YVIEW_NAV         'n'
#define      YVIEW_MAIN        'm'
#define      YVIEW_ALT         'a'
#define      YVIEW_PROGRESS    'p'
#define      YVIEW_MODES       'x'
#define      YVIEW_STATUS      's'
#define      YVIEW_COMMAND     'c'
#define      YVIEW_DETAILS     'd'
#define      YVIEW_RIBBON      'r'
#define      YVIEW_VERSION     'v'
#define      YVIEW_KEYS        'k'
/*---(specialty)----------------------*/
#define      YVIEW_WINDOW      'W'
#define      YVIEW_CURSOR      'C'
#define      YVIEW_GRID        'G'
#define      YVIEW_OVERLAY     'O'
#define      YVIEW_LAYERS      'L'
#define      YVIEW_FLOAT       'F'
#define      YVIEW_BACK        'B'
#define      YVIEW_XAXIS       'X'
#define      YVIEW_YAXIS       'Y'
#define      YVIEW_HISTORY     'H'
#define      YVIEW_MENUS       'M'
#define      YVIEW_NOTES       'N'
#define      YVIEW_MASK        'Z'

#define      YVIEW_FULLSCR     "FHMNZ"

/*
 *  DEPTH   is opengl/3d window
 *  FLAT    is curses/opengl 2d window
 *  FLATISH is curses/opengl 2d overlay layer (clear background)
 *
 */
#define      YVIEW_DEPTH       '3'
#define      YVIEW_FLAT        'O'
#define      YVIEW_FLATISH     'F'
#define      YVIEW_DISABLE     'X'


#define      YVIEW_AUTO        'a'
#define      YVIEW_CUSTOM      'c'


#define      YVIEW_ALLALL      '0'

#define      YVIEW_TOPALL      't'
#define      YVIEW_TOPLEF      '1'
#define      YVIEW_TOPCEN      '2'
#define      YVIEW_TOPRIG      '3'
#define      YVIEW_TOPS        "123"

#define      YVIEW_UPSALL      'k'
#define      YVIEW_UPSBEG      'A'
#define      YVIEW_UPSCEN      'T'
#define      YVIEW_UPSEND      'U'
#define      YVIEW_UPS         "ATU"

#define      YVIEW_MIDALL      'm'
#define      YVIEW_MIDLEF      '4'
#define      YVIEW_MIDBEG      'S'
#define      YVIEW_MIDCEN      '5'
#define      YVIEW_MIDEND      'E'
#define      YVIEW_MIDRIG      '6'
#define      YVIEW_MIDS        "4S5E6"

#define      YVIEW_LOWALL      'j'
#define      YVIEW_LOWBEG      'D'
#define      YVIEW_LOWCEN      'B'
#define      YVIEW_LOWEND      'Z'
#define      YVIEW_LOWS        "DBZ"

#define      YVIEW_BOTALL      'b'
#define      YVIEW_BOTLEF      '7'
#define      YVIEW_BOTCEN      '8'
#define      YVIEW_BOTRIG      '9'
#define      YVIEW_BOTS        "789"

#define      YVIEW_HIDDEN      'X'

#define      YVIEW_ALLFUL      'f'
#define      YVIEW_ALLLEF      'l'
#define      YVIEW_ALLCEN      'c'
#define      YVIEW_ALLRIG      'r'

#define      YVIEW_LEFS        "147"
#define      YVIEW_BEGS        "asd"
#define      YVIEW_CENS        "2t5b8"
#define      YVIEW_ENDS        "uez"
#define      YVIEW_RIGS        "369"

#define      YVIEW_LOC_MENU    "tkmjb0123456789ATUSEDBZX"
#define      YVIEW_LOC_FLOAT   "tkmjb0123456789ATUSEDBZX"
#define      YVIEW_LOC_HIST    "flcr"
#define      YVIEW_LOC_NORM    "0123456789"


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yVIEW_version           (void);
char        yVIEW_init              (char a_env, char *a_title, char *a_ver, void *a_cleanse, void *a_prep, void *a_cursor, void *a_refresh);
char        yVIEW_init_after        (void);
char        yVIEW_resize            (short a_wide, short a_tall, short a_alt);
char        yVIEW_wrap              (void);
char*       yVIEW__unit             (char *a_question, char a_index);


char        yVIEW_layout            (char *a_name);
char        yVIEW_switch_add        (char a_part, char *a_opt, char *a_terse, void *a_source, char *a_desc);
char        yVIEW_switch            (char *a_name, char *a_opt);
char        yVIEW_loc_float         (char a_loc);
char        yVIEW_loc_history       (char a_loc);
char        yVIEW_loc_menu          (char a_loc);

char        yVIEW_full              (char a_part, char a_type, char a_anchor, char a_major, char a_minor, void *a_drawer);
char        yVIEW_simple            (char a_part, char a_major, char a_minor, void *a_drawer);
char        yVIEW_menus             (void *a_drawer);
char        yVIEW_color_set         (char a_part, char a_major, char a_minor);
char        yVIEW_color             (char a_abbr, char a_minor, float a_alpha);
char        yVIEW_color_back        (char a_abbr);
char        yVIEW_color_clear       (char a_abbr);
char        yVIEW_color_font        (char a_abbr);

char        yVIEW_env               (void);
char        yVIEW_defsize           (char a_part, short a_wide, short a_tall);
char        yVIEW_size              (char a_part, char *a_on, short *a_left, short *a_wide, short *a_bott, short *a_tall);
char        yVIEW_bounds            (char a_part, char *a_type, char *a_anchor, short *a_xmin, short *a_xmax, short *a_xlen, short *a_ymin, short *a_ymax, short *a_ylen);
char        yVIEW_showing           (char a_part);
char        yVIEW_anchor            (char a_part);

char        yVIEW_curses            (char a_part, char *r_name, char *r_on, char *r_source, char *r_text, char *r_orient, short *r_left, short *r_wide, short *r_bott, short *r_tall);
char        yVIEW_opengl            (char a_part, char *r_name, char *r_on, char *r_source, char *r_text, char *a_type, char *a_anchor, short *a_xmin, short *a_xmax, short *a_xlen, short *a_ymin, short *a_ymax, short *a_ylen);

char        yVIEW_keys              (char *a_text);
char        yVIEW_modes             (char *a_text);
char        yVIEW_command           (char *a_text);

char        yVIEW_draw              (void);

char        yVIEW_debug_list        (void);

char        yVIEW_note_direct       (char *a_all);
char        yVIEW_note_directw      (char *a_all);
char        yVIEW_note_showing      (void);
char        yVIEW_note_data         (char n, uchar *m, uchar *s, short *x, short *y, short *w, short *h, uchar t [LEN_RECD], uchar *c, short *xb, short *yb, short *xe, short *ye);
char        yVIEW_note_colors       (char *a_curr, char *a_prev, char *a_lcurr, char *a_lprev);
char        yVIEW_notes_debug       (void);
char*       yVIEW_note_entry        (char n);

char        yVIEW_hist_new          (char a_mode, uchar *a_text);
char        yVIEW_hist_header       (short a_wide, char *a_entry);
char        yVIEW_hist_footer       (short a_wide, char *a_entry);
char        yVIEW_hist_entry        (short a_wide, char *a_entry);
char        yVIEW_hist_push         (void);
char        yVIEW_hist_pop          (void);
int         yVIEW_hist_count        (void);
char        yVIEW_hist_cursor       (char a_move, int *r_index);
char        yVIEW_hist_direct       (char b_text [LEN_RECD]);

#endif
/*============================----end-of-source---============================*/
