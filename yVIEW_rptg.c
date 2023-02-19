/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"



char
yVIEW_debug_list        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        i           =    0;
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   /*---(screen parts)-------------------*/
   for (i = 0; i < myVIEW.npart; ++i) {
      DEBUG_YVIEW   yLOG_complex (g_parts [i].name, "%c %c %c %c, %4dl %4dw %4db %4dt, %c %2d %2d %4dx %4dw %4dX %4dy %4dt %4dY", g_parts [i].abbr, g_parts [i].own, g_parts [i].type, g_parts [i].on, g_parts [i].left, g_parts [i].wide, g_parts [i].bott, g_parts [i].tall, g_parts [i].anchor, g_parts [i].cmajor, g_parts [i].cminor, g_parts [i].xmin, g_parts [i].xlen, g_parts [i].xmin + g_parts [i].xlen, g_parts [i].ymin, g_parts [i].ylen, g_parts [i].ymin + g_parts [i].ylen);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char 
yVIEW_notes_debug        (void)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   int         i           =    0;
   int         l           =    0;
   char        t           [LEN_HUND]  = "";
   /*---(header)-------------------------*/
   DEBUG_YVIEW   yLOG_enter   (__FUNCTION__);
   for (i = 0; i < g_nnote; ++i) {
      l = strlen (g_notes [i].text);
      if (l > 60)  sprintf (t, "%2då%-.60s>", l, g_notes [i].text);
      else         sprintf (t, "%2då%-.60sæ", l, g_notes [i].text);
      DEBUG_YVIEW   yLOG_complex ("note"      , "%2d  %c %c %c %c  %4dx %4dy %4dw %4dh  %-64.64s  %c %c  %4dx %4dy  %4dx %4dy  %4dx %4dy  "   , i, g_notes [i].s, g_notes [i].xr, g_notes [i].yr, g_notes [i].size, g_notes [i].x, g_notes [i].y, g_notes [i].w, g_notes [i].h, t, g_notes [i].c, g_notes [i].st, g_notes [i].xt, g_notes [i].yt, g_notes [i].xb, g_notes [i].yb, g_notes [i].xe, g_notes [i].ye);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char 
yVIEW_notes_dump         (void *f)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   FILE       *x_file      = NULL;
   int         i           =    0;
   int         l           =    0;
   char        t           [LEN_HUND]  = "";
   /*---(prepare)------------------------*/
   x_file = f;
   /*---(print)--------------------------*/
   /*> fprintf (f, "#@ parsing    åÏ--··Ï··Ï-------------------··Ï------··Ï------··æ\n");   <*/
   /*> fprintf (f, "#@ titles     åseq··k··name··················title····content··æ\n");   <*/
   /*> fprintf (f, "\n");                                                             <*/
   /*> fprintf (f, "## count = %d\n" , s_nvar);                                       <*/
   for (i = 0; i < g_nnote; ++i) {
      /*> if (i % 25 == 0)  fprintf (f, "\n#--  k  name----------------  title--  content  ´\n");   <*/
      /*> if (i %  5 == 0)  fprintf (f, "\n");                                        <*/
      fprintf (f, "%2d  %c %c %c %c  "   , i, g_notes [i].s, g_notes [i].xr, g_notes [i].yr, g_notes [i].size);
      fprintf (f, "%4dx %4dy %4dw %4dh  ", g_notes [i].x, g_notes [i].y, g_notes [i].w, g_notes [i].h);
      l = strlen (g_notes [i].text);
      if (l > 60)  sprintf (t, "%2då%-.60s>", l, g_notes [i].text);
      else         sprintf (t, "%2då%-.60sæ", l, g_notes [i].text);
      fprintf (f, "%64.64s  ", t);
      fprintf (f, "%c %c  %4dx %4dy  "   , g_notes [i].c, g_notes [i].st, g_notes [i].xt, g_notes [i].yt);
      fprintf (f, "%4dx %4dy  %4dx %4dy  %4dx %4dy", g_notes [i].xb, g_notes [i].yb, g_notes [i].xe, g_notes [i].ye);
      fprintf (f, "\n");
   }
   /*---(complete)-----------------------*/
   return 0;
}

/*> #define      MAX_NOTES     20                                                      <* 
 *> typedef    struct    cNOTE  tNOTE;                                                 <* 
 *> struct cNOTE {                                                                     <* 
 *>    char        xr, yr, size;                /+ requested pos and size         +/   <* 
 *>    char        s;                           /+ main vs window on note box     +/   <* 
 *>    short       x, y;                        /+ note top-left pos              +/   <* 
 *>    short       w, h;                        /+ note size                      +/   <* 
 *>    char       *text;                        /+ text to be displayed           +/   <* 
 *>    char        c;                           /+ connector type                 +/   <* 
 *>    char        st;                          /+ main vs window on target       +/   <* 
 *>    short       xt, yt;                      /+ requested endpoint grid        +/   <* 
 *>    short       xb, yb;                      /+ connector beginning pos        +/   <* 
 *>    short       xe, ye;                      /+ connector ending pos           +/   <* 
 *> };                                                                                 <* 
 *> extern tNOTE  g_notes [MAX_NOTES];                                                 <* 
 *> extern char   g_nnote;                                                             <*/
