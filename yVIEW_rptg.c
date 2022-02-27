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
      DEBUG_YVIEW   yLOG_complex (g_parts [i].name, "%c %c %c, %4dl %4dw %4db %4dt, %c %4dx %4dl %4dy %4dl", g_parts [i].abbr, g_parts [i].own, g_parts [i].on, g_parts [i].left, g_parts [i].wide, g_parts [i].bott, g_parts [i].tall, g_parts [i].anchor, g_parts [i].xmin, g_parts [i].xlen, g_parts [i].ymin, g_parts [i].ylen);
   }
   /*---(complete)-----------------------*/
   DEBUG_YVIEW   yLOG_exit    (__FUNCTION__);
   return 0;
}
