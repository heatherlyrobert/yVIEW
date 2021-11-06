/*============================----beg-of-source---============================*/
#ifndef yVIEW
#define yVIEW yes



typedef  unsigned char        uchar;
typedef  const char           cchar;
typedef  const int            cint;


#define      YVIEW_OPENGL      'g'
#define      YVIEW_CURSES      'c'


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

#define      YVIEW_RIGHT       'r'
#define      YVIEW_OFFICE      'o'

#define      YVIEW_DEPTH       '3'
#define      YVIEW_FLAT        'O'
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
#define      YVIEW_UPSBEG      'a'
#define      YVIEW_UPSCEN      't'
#define      YVIEW_UPSEND      'u'
#define      YVIEW_UPS         "atu"

#define      YVIEW_MIDALL      'm'
#define      YVIEW_MIDLEF      '4'
#define      YVIEW_MIDBEG      's'
#define      YVIEW_MIDCEN      '5'
#define      YVIEW_MIDEND      'e'
#define      YVIEW_MIDRIG      '6'
#define      YVIEW_MIDS        "4s5e6"

#define      YVIEW_LOWALL      'j'
#define      YVIEW_LOWBEG      'd'
#define      YVIEW_LOWCEN      'b'
#define      YVIEW_LOWEND      'z'
#define      YVIEW_LOWS        "dbz"

#define      YVIEW_BOTALL      'b'
#define      YVIEW_BOTLEF      '7'
#define      YVIEW_BOTCEN      '8'
#define      YVIEW_BOTRIG      '9'
#define      YVIEW_BOTS        "789"

#define      YVIEW_ALLFUL      'f'
#define      YVIEW_ALLLEF      'l'
#define      YVIEW_ALLCEN      'c'
#define      YVIEW_ALLRIG      'r'

#define      YVIEW_LEFS        "147"
#define      YVIEW_BEGS        "asd"
#define      YVIEW_CENS        "2t5b8"
#define      YVIEW_ENDS        "uez"
#define      YVIEW_RIGS        "369"

#define      YVIEW_LOC_MENU    "0123456789atusedbz"
#define      YVIEW_LOC_FLOAT   "tkmjb"
#define      YVIEW_LOC_HIST    "flcr"
#define      YVIEW_LOC_NORM    "0123456789"


/*345678901-12345678901-12345678901-12345678901-12345678901-12345678901-123456*/
/*---(base)-----------------*/
char*       yVIEW_version           (void);
char        yVIEW_init              (void);
char        yVIEW_wrap              (void);
char*       yVIEW__unit             (char *a_question, char a_index);

char        yVIEW_switch_add        (char a_part, char *a_opt, void *a_source, char *a_desc);
char        yVIEW_resize            (cint a_wide, cint a_tall, cint a_alt);

char        yVIEW_defsize           (char a_part, short a_wide, short a_tall);


#endif
/*============================----end-of-source---============================*/
