/* -------------------------------------------------------------------------
 Test_general_parser.c - A simple example of calling re-usable xml-parsing
  library for general-purpose xml-parsing.  Reads xml-file(s) on command-line
  into token-tree, then generates new xml-file from token-tree.
  Always writes output to file called: "test_out2.xml".

 Compile:
  cc -g -O test_general_parser.c -lm -o test_general_parser.exe

 Run:
  ./test_general_parser.exe  yourxmlfile.xml
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
  
   printf("Writing file 'test_out2.xml'.\n");
   Xml_Write_File( "test_out2.xml", rootobj );

   j++;
  }

 return 0;
}
