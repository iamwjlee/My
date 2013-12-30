#include <stdio.h>
#include <unistd.h>

#include <directfb.h>

// entry point
static IDirectFB *g_pDirectFb = NULL;

// primary surface
static IDirectFBSurface *g_pPrimarySurface = NULL;

static int nScreenWidth = 0;
static int nScreenHeight = 0;

/*
 * An error checking macro for a call to DirectFB.
 * It is suitable for very simple apllications or tutorials.
 * In more sophisticated applications this general error checking should not be used.
 */
#define DFBCHECK(x...)                                         \
  {                                                            \
    DFBResult err = x;                                         \
                                                               \
    if (err != DFB_OK)                                         \
      {                                                        \
        fprintf( stderr, "%s <%d>:\n\t", __FILE__, __LINE__ ); \
        DirectFBErrorFatal( #x, err );                         \
      }                                                        \
  }

int main(int argc, char **argv)
{
        // create surface description
        DFBSurfaceDescription dsc;

        DFBCHECK( DirectFBInit(&argc, &argv) );

        // create super interface.
        DFBCHECK( DirectFBCreate(&g_pDirectFb) );

        DFBCHECK( g_pDirectFb->SetCooperativeLevel(g_pDirectFb, DFSCL_FULLSCREEN) );
        
        // set flags
        dsc.flags = DSDESC_CAPS;
        dsc.caps = DSCAPS_PRIMARY | DSCAPS_FLIPPING;
        
        // create surface
        DFBCHECK ( g_pDirectFb->CreateSurface(g_pDirectFb, &dsc, &g_pPrimarySurface) );

        // get surface size
        DFBCHECK ( g_pPrimarySurface->GetSize(g_pPrimarySurface, &nScreenWidth, &nScreenHeight) );
        printf("Width: %d, Height: %d\n", nScreenWidth, nScreenHeight);

        // clear surface 
        DFBCHECK ( g_pPrimarySurface->FillRectangle (g_pPrimarySurface, 0, 0, nScreenWidth, nScreenHeight) );
        
        // set surface color
        DFBCHECK ( g_pPrimarySurface->SetColor(g_pPrimarySurface, 0xff, 0x00, 0x00, 0xff) );
        
        printf("Draw Rectangle\n");

        // draw rectangle
        DFBCHECK ( g_pPrimarySurface->FillRectangle (g_pPrimarySurface, 100, 100, 440, 280) );

        printf("Update Surface\n");

        // update surface
        DFBCHECK ( g_pPrimarySurface->Flip(g_pPrimarySurface, NULL, 0) );
        
        sleep(5);

        // clean up
        g_pPrimarySurface->Release( g_pPrimarySurface );
        g_pDirectFb->Release( g_pDirectFb );

        return 0;
}
