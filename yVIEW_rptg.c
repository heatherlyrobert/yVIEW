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
   DEBUG_YVIEW   yLOG_value   ("npart"     , myVIEW.npart);
   for (i = 0; i < myVIEW.npart; ++i) {
      DEBUG_YVIEW   yLOG_complex (gVIEW_parts [i].name, "%c %c %c %c, %4dl %4dw %4db %4dt, %c %2d %2d %4dx %4dw %4dX %4dy %4dt %4dY", gVIEW_parts [i].abbr, gVIEW_parts [i].own, gVIEW_parts [i].type, gVIEW_parts [i].on, gVIEW_parts [i].left, gVIEW_parts [i].wide, gVIEW_parts [i].bott, gVIEW_parts [i].tall, gVIEW_parts [i].anchor, gVIEW_parts [i].cmajor, gVIEW_parts [i].cminor, gVIEW_parts [i].xmin, gVIEW_parts [i].xlen, gVIEW_parts [i].xmin + gVIEW_parts [i].xlen, gVIEW_parts [i].ymin, gVIEW_parts [i].ylen, gVIEW_parts [i].ymin + gVIEW_parts [i].ylen);
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
   for (i = 0; i < gVIEW_nnote; ++i) {
      if (gVIEW_notes [i].text != NULL) {
         l = strlen (gVIEW_notes [i].text);
         if (l > 60)  sprintf (t, "%2då%-.60s>", l, gVIEW_notes [i].text);
         else         sprintf (t, "%2då%-.60sæ", l, gVIEW_notes [i].text);
      } else {
         strcpy (t, " ·åæ");
      }
      DEBUG_YVIEW   yLOG_complex ("note"      , "%2d  %c %c %c %c  %4dx %4dy %4dw %4dh  %-64.64s  %c %c  %4dx %4dy  %4dx %4dy  %4dx %4dy  "   , i, gVIEW_notes [i].s, gVIEW_notes [i].xr, gVIEW_notes [i].yr, gVIEW_notes [i].size, gVIEW_notes [i].x, gVIEW_notes [i].y, gVIEW_notes [i].w, gVIEW_notes [i].h, t, gVIEW_notes [i].c, gVIEW_notes [i].st, gVIEW_notes [i].xt, gVIEW_notes [i].yt, gVIEW_notes [i].xb, gVIEW_notes [i].yb, gVIEW_notes [i].xe, gVIEW_notes [i].ye);
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
   if (n < 0  || n >= gVIEW_nnote)   return s_entry;
   sprintf (s, "%2d  %c %c %c %c  "   , n, gVIEW_notes [n].s, gVIEW_notes [n].xr, gVIEW_notes [n].yr, gVIEW_notes [n].size);
   strlcpy (s_entry, s, LEN_FULL);
   sprintf (s, "%4dx %4dy %4dw %4dh  ", gVIEW_notes [n].x, gVIEW_notes [n].y, gVIEW_notes [n].w, gVIEW_notes [n].h);
   strlcat (s_entry, s, LEN_FULL);
   l = strlen (gVIEW_notes [n].text);
   if (l > 60)  sprintf (t, "%2då%-.60s>", l, gVIEW_notes [n].text);
   else         sprintf (t, "%2då%-.60sæ", l, gVIEW_notes [n].text);
   sprintf (s, "%-64.64s  ", t);
   strlcat (s_entry, s, LEN_FULL);
   sprintf (s, "%c %c %c %c %c  "   , gVIEW_notes [n].q, gVIEW_notes [n].c, gVIEW_notes [n].st, gVIEW_notes [n].xt, gVIEW_notes [n].yt);
   strlcat (s_entry, s, LEN_FULL);
   sprintf (s, "%4dx %4dy  %4dx %4dy", gVIEW_notes [n].xb, gVIEW_notes [n].yb, gVIEW_notes [n].xe, gVIEW_notes [n].ye);
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
   for (i = 0; i < gVIEW_nnote; ++i) {
      /*> if (i % 25 == 0)  fprintf (f, "\n#--  k  name----------------  title--  content  ´\n");   <*/
      if (i %  5 == 0)  fprintf (f, "\n");
      fprintf (f, "%2d  %c %c %c %c  "   , i, gVIEW_notes [i].s, gVIEW_notes [i].xr, gVIEW_notes [i].yr, gVIEW_notes [i].size);
      fprintf (f, "%4dx %4dy %4dw %4dh  ", gVIEW_notes [i].x, gVIEW_notes [i].y, gVIEW_notes [i].w, gVIEW_notes [i].h);
      l = strlen (gVIEW_notes [i].text);
      if (l > 60)  sprintf (t, "%2då%-.60s>", l, gVIEW_notes [i].text);
      else         sprintf (t, "%2då%-.60sæ", l, gVIEW_notes [i].text);
      fprintf (f, "%-64.64s  ", t);
      fprintf (f, "%c %c %c %c %c  "   , gVIEW_notes [i].q, gVIEW_notes [i].c, gVIEW_notes [i].st, gVIEW_notes [i].xt, gVIEW_notes [i].yt);
      fprintf (f, "%4dx %4dy  %4dx %4dy", gVIEW_notes [i].xb, gVIEW_notes [i].yb, gVIEW_notes [i].xe, gVIEW_notes [i].ye);
      fprintf (f, "\n");
   }
   /*---(footer)-------------------------*/
   fprintf (f, "\n");
   fprintf (f, "##··m·x·y·s··-xpos·-ypos·-wide·-tall··---content------------------------------------------------------··q·c·m·x·y··-xbeg·-ybeg··-xend·-yend\n");
   fprintf (f, "##··---note-------------------------------------------------------------------------------------------··---target--------------------------\n");
   /*---(complete)-----------------------*/
   return 0;
}

