/*
 *  BlendColors32 by Esa Tanskanen
 *  Fast 32-bit color mixing routines
 *  Use the BlendColors32 function if unsure
 */
 
 
// If you wish to process multiple pixels at once, use this function... //
inline unsigned long BlendColors32NoEmms( unsigned long dst, unsigned long src, unsigned long factor ) {
 static unsigned short INVERT_MASK[4] = { 0x00FF, 0x00FF, 0x00FF, 0x00FF };
 unsigned long returnParam;
 factor = 255 - factor;
 asm(
  "movd %1, %%mm0\n"
  "movd %2, %%mm1\n"
  "pxor %%mm2, %%mm2\n"
  "punpcklbw %%mm2, %%mm0\n"
  "punpcklbw %%mm2, %%mm1\n"
  
  // Get the alpha value //
  "movd %4, %%mm3\n"
  "punpcklwd %%mm3, %%mm3\n"
  "punpcklwd %%mm3, %%mm3\n"
  
  // (alpha * (source + 255 - dest))/255 + dest - alpha //
  "paddw (%3), %%mm0\n"
  "psubw %%mm1, %%mm0\n"
  "psrlw $1, %%mm0\n"
  "pmullw %%mm3, %%mm0\n"
  "psrlw $7, %%mm0\n"
  "paddw %%mm1, %%mm0\n"
  "psubw %%mm3, %%mm0\n"
  
  "packuswb %%mm0, %%mm0\n"
  "movd %%mm0, %0\n"
  : "=&a" (returnParam)
  : "rm" (dst), "rm" (src), "rm" (INVERT_MASK), "rm" (factor)
  : "memory"
 );
 return returnParam;
}


// ... but remember to call this one before you use any floats or doubles //
inline void CallEmms() {
  asm(
   "emms\n"
  );
}


// This is a shorthand to blend single pixels at a time //
inline unsigned long BlendColors32( unsigned long dst, unsigned long src, unsigned long factor ) {
 unsigned long returnParam = BlendColors32NoEmms( dst, src, factor );
 CallEmms();
 return returnParam;
}



/*
 *  AlphaBlend32 by Esa Tanskanen
 *  32-bit alpha blending routines with a global alpha value
 *  Notice that the source bitmap comes before the destination bitmap!
 */


void AlphaBlend32( BITMAP *src, BITMAP *dst, int dst_x, int dst_y, int globalAlpha ) {
   /* The following conditions must be true */
   ASSERT( src );
   ASSERT( dst );
   ASSERT( bitmap_color_depth( src ) == 32 );
   ASSERT( bitmap_color_depth( dst ) == 32 );
   
   /* Apply clipping */
   int src_x = 0;
   int src_y = 0;
   int w = src->w;
   int h = src->h;
   
   if( dst_x < 0 ) {
      w += dst_x;
      src_x -= dst_x;
      dst_x = 0;
   }
   
   if( dst_y < 0 ) {
      h += dst_y;
      src_y -= dst_y;
      dst_y = 0;
   }
   
   if( dst_x + w > dst->w ) {
      w -= dst_x + w - dst->w;
   }
   
   if( w <= 0 ) return;
   
   if( dst_y + h > dst->h ) {
      h -= dst_y + h - dst->h;
   }
   
   if( h <= 0 ) return;
   
   /* Select destination surface for reading and writing */
   acquire_bitmap( dst );
   bmp_select( dst );
   
   /* Loop through all pixels */
   for( int j = 0; j < h; j++ ) {
      unsigned int *src_ptr = ((unsigned int *)src->line[src_y+j]) + src_x;
      unsigned int dst_address = bmp_write_line( dst, dst_y+j ) + 4*dst_x;
      
      for( int i = 0; i < w; i++ ) {
         unsigned int srcColor = *src_ptr;
         /* Extract the alpha value */
         unsigned int fact = ( geta32( srcColor ) * globalAlpha ) >> 8;
         
         /* Blend the colors if required */
         if( fact != 0 ) {
            if( fact >= 255 ) bmp_write32( dst_address, srcColor );
            else bmp_write32( dst_address, BlendColors32NoEmms( *((unsigned int *) dst_address), *src_ptr, fact ));
         }
         
         /* Advance to the next pixel */
         dst_address += 4;
         src_ptr++;
      }
   }
   
   /* Finish blending */
   CallEmms();
   
   /* Finish messing with the destination bitmap */
   bmp_unwrite_line( dst );
   release_bitmap( dst );
}



/*
 *  AlphaBlend32 by Esa Tanskanen
 *  32-bit alpha blending routines
 *  Notice that the source bitmap comes before the destination bitmap!
 */


void AlphaBlend32( BITMAP *src, BITMAP *dst, int dst_x, int dst_y ) {
   /* The following conditions must be true */
   ASSERT( src );
   ASSERT( dst );
   ASSERT( bitmap_color_depth( src ) == 32 );
   ASSERT( bitmap_color_depth( dst ) == 32 );
   
   /* Apply clipping */
   int src_x = 0;
   int src_y = 0;
   int w = src->w;
   int h = src->h;
   
   if( dst_x < 0 ) {
      w += dst_x;
      src_x -= dst_x;
      dst_x = 0;
   }
   
   if( dst_y < 0 ) {
      h += dst_y;
      src_y -= dst_y;
      dst_y = 0;
   }
   
   if( dst_x + w > dst->w ) {
      w -= dst_x + w - dst->w;
   }
   
   if( w <= 0 ) return;
   
   if( dst_y + h > dst->h ) {
      h -= dst_y + h - dst->h;
   }
   
   if( h <= 0 ) return;
   
   /* Select destination surface for reading and writing */
   acquire_bitmap( dst );
   bmp_select( dst );
   
   /* Loop through all pixels */
   for( int j = 0; j < h; j++ ) {
      unsigned int *src_ptr = ((unsigned int *)src->line[src_y+j]) + src_x;
      unsigned int dst_address = bmp_write_line( dst, dst_y+j ) + 4*dst_x;
      
      for( int i = 0; i < w; i++ ) {
         unsigned int srcColor = *src_ptr;
         /* Extract the alpha value */
         unsigned int fact = geta32( srcColor );
         
         /* Blend the colors if required */
         if( fact != 0 ) {
            if( fact >= 255 ) bmp_write32( dst_address, srcColor );
            else bmp_write32( dst_address, BlendColors32NoEmms( *((unsigned int *) dst_address), *src_ptr, fact ));
         }
         
         /* Advance to the next pixel */
         dst_address += 4;
         src_ptr++;
      }
   }
   
   /* Finish blending */
   CallEmms();
   
   /* Finish messing with the destination bitmap */
   bmp_unwrite_line( dst );
   release_bitmap( dst );
}
