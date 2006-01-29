#include "XMiLog.h"
#include <cstdio>


using namespace std;


namespace {
   const string htmlFile("log.html");
   const string logTitle("A sample log");
}


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
   if (!(fp = fopen(htmlFile.c_str(), "w")))
   {
      fprintf(stderr, "Error: could not open log file %s for writing\n", htmlFile.c_str()); 
      return 1;
   }
   fprintf(fp, htmlLog.c_str());
   fclose(fp);
   printf("A HTML version of this log has been saved to 'log.html'\n");
   return 0;
}