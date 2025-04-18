#include <stdlib.h>
#include <stdio.h>
#include <sys/stat.h>

//create ram disk
#define setISOFile		"/xport/camdata/iso.set"
#define setApertureFile		"/xport/camdata/aperture.set"
#define setIntervalFile		"/xport/camdata/interval.set"
#define setShutterFile		"/xport/camdata/shutter.set"
#define setPMFile		"/xport/camdata/pm.set"
#define setFMFile		"/xport/camdata/fm.set"
#define setEVFile		"/xport/camdata/ev.set"
#define setJQFile		"/xport/camdata/jq.set"
#define setWBFile		"/xport/camdata/wb.set"

#define takeFile		"/xport/camdata/take"
#define focusFile		"/xport/camdata/focus"
#define flashformatFile		"/xport/camdata/flashformat"

#define startvidFile		"/xport/camdata/startvid"
#define stopvidFile		"/xport/camdata/stopvid"

#define infoISOFile		"/xport/camdata/iso.nfo"
#define infoApertureFile	"/xport/camdata/aperture.nfo"
#define infoShutterFile		"/xport/camdata/shutter.nfo"
#define infoPMFile		"/xport/camdata/pm.nfo"
#define infoFMFile		"/xport/camdata/fm.nfo"
#define infoEVFile		"/xport/camdata/ev.nfo"
#define infoJQFile		"/xport/camdata/jq.nfo"
#define infoWBFile		"/xport/camdata/wb.nfo"
#define infoVidFile		"/xport/camdata/vid.nfo"
#define infoRemainPhotosFile	"/xport/camdata/remainphotos.nfo"
#define infoZoomFile		"/xport/camdata/zoom.nfo"


#define listISOFile		"/xport/camdata/iso.list"
#define listApertureFile	"/xport/camdata/aperture.list"
#define listShutterFile		"/xport/camdata/shutter.list"
#define listPMFile		"/xport/camdata/pm.list"
#define listEVFile		"/xport/camdata/ev.list"
#define listJQFile		"/xport/camdata/jq.list"
#define listFMFile		"/xport/camdata/fm.list"
#define listWBFile		"/xport/camdata/wb.list"

#define lvFile			"/xport/camdata/cap.jpg"
#define tmplvFile		"/xport/camdata/captmp.jpg"

#define infoStatusFile		"/xport/camdata/status.txt"
#define tmpFile			"/xport/camdata/tmp.txt"


int readfl (char* fn)
{
   struct stat ffstat;
   int i;
   FILE *inf = NULL;
   inf = fopen(fn, "r");
   if (inf==NULL)
      {
      return -1;
      }
   fscanf(inf,"%i",&i);
   fclose(inf);

   unlink(fn);
   return i;
}


void writefl (char* fn, int val)
{
//   printf("WFILE: %s, %i", fn, val);
   FILE *inf = NULL;
   inf = fopen(tmpFile, "w");
   if (!inf) return;
   fprintf(inf,"%i\n",val);
   fclose(inf);
   rename(tmpFile, fn);
}


void writelist (char* fn, char** strings, int num)
{
   struct stat ffstat;
   int x;
   if (stat(fn,&ffstat)==0) 
      return;
   
   FILE *inf = NULL;
   inf = fopen(tmpFile, "w");
   if (!inf) return;
   for(x=0; x<num; x++)
   {
      fprintf(inf,"%i %s\n",x,strings[x]);
   }
   fclose(inf);
   rename(tmpFile, fn);

}
