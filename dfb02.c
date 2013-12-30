#include <stdio.h>
 
#include <unistd.h>
#include <directfb.h>
 
 
 
static IDirectFB *dfb = NULL;
static IDirectFBSurface *sur = NULL;
/*

	Blit( *this, *source,*rect,x,y) 

*/

 
static int width = 0;
static int height = 0;
 
 
 
static IDirectFBSurface *logo = NULL;
 
 #define DFBCHECK(x...)                                         \
	{	\
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
 
             int i;
 	char *path="./1.png";
//	 	char *path="/home/wj/test/pngtest.png";

             DFBSurfaceDescription dsc;
 
             IDirectFBImageProvider *provider;
 
 
 
             DFBCHECK(DirectFBInit (&argc, &argv));
 
             DFBCHECK(DirectFBCreate(&dfb));
 
            DFBCHECK(dfb->SetCooperativeLevel(dfb, DFSCL_FULLSCREEN));
 
             dsc.flags = DSDESC_CAPS;
             dsc.caps = DSCAPS_PRIMARY | DSCAPS_FLIPPING;
 
             DFBCHECK(dfb->CreateSurface(dfb, &dsc, &sur));
 
             DFBCHECK(sur->GetSize(sur, &width, &height));
 	     printf("get surface size Width: %d, Height: %d\n", width, height);        

 
 
        DFBCHECK(dfb->CreateImageProvider(dfb,path ,  &provider) );
 
             DFBCHECK(provider->GetSurfaceDescription(provider, &dsc));
 
             DFBCHECK(dfb->CreateSurface(dfb, &dsc, &logo));
 
             DFBCHECK(provider->RenderTo(provider, logo, NULL));
 
 
 
             provider->Release(provider);
 
 
  	     printf("get dsc.height:%d    [%d]\n", dsc.height,(height - dsc.height) / 2);        

             for(i = -dsc.width; i < width; i++)
 
             {
 
                           DFBCHECK(sur->FillRectangle(sur, 0, 0, width, height));
 
                           DFBCHECK(sur->Blit(sur, logo, NULL, i, (height - dsc.height) / 2));
                          //  DFBCHECK(sur->Blit(sur, logo, NULL, i, 10));

                           DFBCHECK(sur->Flip(sur, NULL, DSFLIP_WAITFORSYNC));
 
 
 
             }
 
             logo->Release(logo);
 
             sur->Release(sur);
 
             dfb->Release(dfb);
 
 
 
             return 23;
 
}

