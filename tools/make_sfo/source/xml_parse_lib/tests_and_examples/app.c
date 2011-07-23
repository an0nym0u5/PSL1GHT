/************************************************************************/
/* Example XML Application, App.c - This example reads any XML file(s) 	*/
/* specified on the command-line when invoked.	It is a convenient 	*/
/* starting-template for writing stream-oriented (or SAX-like) parsers.	*/
/*									*/
/* Compile:								*/
/*   cc -g -O app.c -lm -o app.exe					*/
/*									*/
/* Run:									*/
/*   app.exe  myxmlfile.xml						*/
/*									*/
/************************************************************************/

#include <stdio.h>

#include "../xml_parse_lib.c"

#define MaxStr 2000



void read_xml_file( char *fname )
{
  char tag[MaxStr], contents[MaxStr], tagname[MaxStr], attrname[MaxStr], value[MaxStr];
  float x1, y1, z1, x2, y2, z2, t0, t1;
  int linum=0;
  FILE *infile=0, *outfile=0;

 infile = fopen(fname,"r");    
 if (infile==0) {printf("Error: Cannot open input file '%s'.\n",fname); exit(1);} 
 xml_parse( infile, tag, contents, MaxStr, &linum );
 while (tag[0]!='\0')
  {
   xml_grab_tag_name( tag, tagname, MaxStr );	/* Get tag name. */

   /* Add your application code here to accept tag-name, such as: */
   printf("Tag name = '%s'\n", tagname );

   xml_grab_attrib( tag, attrname, value, MaxStr );	/* Get any attributes within tag. */
   while (value[0] != '\0')
    {
     /* Add application code here to accept attribute attrname and value, such as: */
     printf(" Attribute: %s = '%s'\n", attrname, value );

     xml_grab_attrib( tag, attrname, value, MaxStr );	/* Get next attribute, if any. */
    }

   /* Add application code here to accept contents between tags, such as: */
   printf(" Contents = '%s'\n", contents );

   xml_parse( infile, tag, contents, MaxStr, &linum );	/* Get next tag, if any. */
  }
 fclose(infile);
}


int main( int argc, char *argv[] )
{
 int i, j, k, verbose=0, lnn=0;

 /* Get the command-line arguments. */
 if (argc<=1) {printf("Missing input file on command-line.\n"); exit(1);}
 j = 1;
 while (argc>j)
  { /*argument*/
    read_xml_file( argv[j] );
   j = j + 1;
  } /*argument*/
 return 0;
}
