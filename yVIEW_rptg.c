/*============================---beg-of-source---============================*/
/*---(headers)---------------------------*/
#include    "yVIEW.h"
#include    "yVIEW_priv.h"


static char s_entry  [LEN_FULL] = "";

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
      if (g_notes [i].text != NULL) {
         l = strlen (g_notes [i].text);
         if (l > 60)  sprintf (t, "%2då%-.60s>", l, g_notes [i].text);
         else         sprintf (t, "%2då%-.60sæ", l, g_notes [i].text);
      } else {
         strcpy (t, " ·åæ");
      }
      DEBUG_YVIEW   yLOG_complex ("note"      , "%2d  %c %c %c %c  %4dx %4dy %4dw %4dh  %-64.64s  %c %c  %4dx %4dy  %4dx %4dy  %4dx %4dy  "   , i, g_notes [i].s, g_notes [i].xr, g_notes [i].yr, g_notes [i].size, g_notes [i].x, g_notes [i].y, g_notes [i].w, g_notes [i].h, t, g_notes [i].c, g_notes [i].st, g_notes [i].xt, g_notes [i].yt, g_notes [i].xb, g_notes [i].yb, g_notes [i].xe, g_notes [i].ye);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}

char*
yVIEW_note_entry     (char n)
{
   char        t           [LEN_HUND]  = "";
   char        s           [LEN_HUND]  = "";
   int         l           =    0;
   strcpy (s_entry, "(not-exist)");
   if (n < 0  || n >= g_nnote)   return s_entry;
   sprintf (s, "%2d  %c %c %c %c  "   , n, g_notes [n].s, g_notes [n].xr, g_notes [n].yr, g_notes [n].size);
   strlcpy (s_entry, s, LEN_FULL);
   sprintf (s, "%4dx %4dy %4dw %4dh  ", g_notes [n].x, g_notes [n].y, g_notes [n].w, g_notes [n].h);
   strlcat (s_entry, s, LEN_FULL);
   l = strlen (g_notes [n].text);
   if (l > 60)  sprintf (t, "%2då%-.60s>", l, g_notes [n].text);
   else         sprintf (t, "%2då%-.60sæ", l, g_notes [n].text);
   sprintf (s, "%-64.64s  ", t);
   strlcat (s_entry, s, LEN_FULL);
   sprintf (s, "%c %c %c %c %c  "   , g_notes [n].q, g_notes [n].c, g_notes [n].st, g_notes [n].xt, g_notes [n].yt);
   strlcat (s_entry, s, LEN_FULL);
   sprintf (s, "%4dx %4dy  %4dx %4dy", g_notes [n].xb, g_notes [n].yb, g_notes [n].xe, g_notes [n].ye);
   strlcat (s_entry, s, LEN_FULL);
   return s_entry;
}

char 
yview_notes_dump         (void *f)
{
   /*---(locals)-----------+-----+-----+-*/
   char        rc          =    0;
   FILE       *x_file      = NULL;
   int         i           =    0;
   int         l           =    0;
   char        t           [LEN_HUND]  = "";
   /*---(prepare)------------------------*/
   x_file = f;
   /*---(hints)--------------------------*/
   fprintf (f, "## vikeys note detail inventory\n");
   fprintf (f, "\n");
   fprintf (f, "#@ parsing    åÏ-··Ï·Ï·Ï·Ï··Ï---··Ï---··Ï---··Ï---···Ï---------------------------------------------------------------··Ï·Ï·Ï·Ï·Ï··Ï---··Ï---···Ï---··Ï---·æ\n");
   fprintf (f, "#@ titles     åno··m·x·y·s··x·····y·····w·····h······content···························································q·c·m·x·y··xb····yb·····xe····ye···æ\n");
   fprintf (f, "\n");
   /*---(header)-------------------------*/
   fprintf (f, "##··---note-------------------------------------------------------------------------------------------··---target--------------------------\n");
   fprintf (f, "##··m·x·y·s··-xpos·-ypos·-wide·-tall··---content------------------------------------------------------··q·c·m·x·y··-xbeg·-ybeg··-xend·-yend\n");
   /*---(print)--------------------------*/
   for (i = 0; i < g_nnote; ++i) {
      /*> if (i % 25 == 0)  fprintf (f, "\n#--  k  name----------------  title--  content  ´\n");   <*/
      if (i %  5 == 0)  fprintf (f, "\n");
      fprintf (f, "%2d  %c %c %c %c  "   , i, g_notes [i].s, g_notes [i].xr, g_notes [i].yr, g_notes [i].size);
      fprintf (f, "%4dx %4dy %4dw %4dh  ", g_notes [i].x, g_notes [i].y, g_notes [i].w, g_notes [i].h);
      l = strlen (g_notes [i].text);
      if (l > 60)  sprintf (t, "%2då%-.60s>", l, g_notes [i].text);
      else         sprintf (t, "%2då%-.60sæ", l, g_notes [i].text);
      fprintf (f, "%-64.64s  ", t);
      fprintf (f, "%c %c %c %c %c  "   , g_notes [i].q, g_notes [i].c, g_notes [i].st, g_notes [i].xt, g_notes [i].yt);
      fprintf (f, "%4dx %4dy  %4dx %4dy", g_notes [i].xb, g_notes [i].yb, g_notes [i].xe, g_notes [i].ye);
      fprintf (f, "\n");
   }
   /*---(footer)-------------------------*/
   fprintf (f, "\n");
   fprintf (f, "##··m·x·y·s··-xpos·-ypos·-wide·-tall··---content------------------------------------------------------··q·c·m·x·y··-xbeg·-ybeg··-xend·-yend\n");
   fprintf (f, "##··---note-------------------------------------------------------------------------------------------··---target--------------------------\n");
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
