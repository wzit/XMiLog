#include "XMiLog.h"
#include <cstdio>


using namespace std;


namespace {
   const string htmlFile("log.html");        ///< The name of the HTML log file
   const string logTitle("A sample log");    ///< The title of the Log
}


//************************************************************************************************
/// \brief Program entrypoint
//************************************************************************************************
int main(int argc, char **argv)
{
   XMiLog log(true, "log.txt");
   for (int i = 0; i < 10; i++)
   {
      log.echo("this is an echo");
      log.warn("this is a warn");
      log.fatal("this is a fatal");
   }
   printf(log.getTextLog(true, true, logTitle.c_str()).c_str());
   string htmlLog = log.getHTMLLog(true, true, logTitle.c_str());
   FILE *fp;
#ifdef MACOS
   if (!(fp = fopen(htmlFile.c_str(), "w")))
#endif
#ifdef WIN32
   if (fopen_s(&fp, htmlFile.c_str(), "w"))
#endif
   {
      fprintf(stderr, "Error: could not open log file %s for writing\n", htmlFile.c_str()); 
      return 1;
   }
   fprintf(fp, htmlLog.c_str());
   fclose(fp);
   printf("A HTML version of this log has been saved to 'log.html'\n");
   return 0;
}