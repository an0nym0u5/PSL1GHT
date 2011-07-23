/* -------------------------------------------------------------------------
 Reformat_xml.c - A simple example of calling re-usable xml-parsing
  library for general-purpose xml-parsing.  Reads xml-file(s) on command-line
  into token-tree, then saves out token-tree to same file, and in the 
  process, formats it to nominal indenting style.

 Compile:
  cc -g -O reformat_xml.c -lm -o reformat_xml

 Run:
  ./reformat_xml  yourxmlfile.xml
 -------------------------------------------------------------------------
*/

#include <stdio.h>

#include "../xml_parse_lib.c"


int main( int argc, char **argv )
{
 int j=1;
 Xml_object *rootobj=0;

 while (j < argc)
  {
   printf("Reading file '%s'\n", argv[j]);
   rootobj = Xml_Read_File( argv[j] );
  
   Xml_Write_File( argv[j], rootobj );

   j++;
  }

 return 0;
}
