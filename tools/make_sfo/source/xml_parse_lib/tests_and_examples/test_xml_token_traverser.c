/* -------------------------------------------------------------------------
 Test_xml_token_traverser.c - A simple example of calling re-usable xml-parsing
  library for reading an arbitrary xml-file, and traversing through the
  tokens.  Reads xml-file(s) on command-line into token-tree, then traverses
  the tokens.

 Compile:
  cc -g -O test_xml_token_traverser.c -lm -o test_xml_token_traverser.exe

 Run:
  ./test_xml_token_traverser.exe  yourxmlfile.xml
 -------------------------------------------------------------------------
*/

#include <stdio.h>
#include "../xml_parse_lib.c"
#define maxstr 5000


void indent( int level )
{
 int j;
 for (j=0; j<level; j++) printf("  ");		/* Indent appropriate to level. */
}


void traverse( Xml_object *rootobj )
{
 struct xml_private_tree *xml_tree;
 char tag[maxstr], contents[maxstr], attrib[maxstr], value[maxstr];
 int j, level=0; 

 xml_tree_start_traverse( &xml_tree, rootobj, tag, contents, maxstr );		/* Initiate xml-traversal. */
 while (xml_tree)
  {
   indent(level);			/* Indent appropriate to level. */	
   printf("Tag='%s'\n", tag);		/* Show the tag-name. */
   while (xml_tree_get_next_attribute( xml_tree, attrib, value, maxstr ))	/* Get next attribute. */
    {					/* Show the attribtes. */
     indent(level);			/* Indent appropriate to level. */
     printf(" Attribute: %s = '%s'\n", attrib, value);
    }
   if (strlen(contents)>0)
    {					/* Show the contents. */
     indent(level);
     printf(" Contents: '%s'\n", contents);
    }

   /* Descend into this tag's children, if posible. */
   if (xml_tree_descend_to_child( &xml_tree, tag, contents, maxstr ))		/* Get children, if any. */
    level++;
   else		/* Otherwise sequence to next tag at present level. */
    {										/* Else get next tag, if any. */
     while ((xml_tree) && (! xml_tree_get_next_tag( xml_tree, tag, contents, maxstr )))
      {		/* Go up, if no more nodes at this level. */
       level--;
       xml_tree_ascend( &xml_tree );						/* Otherwise, go up. */
      }
    }
  }
}


int main( int argc, char **argv )
{
 int j=1;
 Xml_object *rootobj=0;

 while (j < argc)
  {
   printf("Reading file '%s'\n", argv[j]);
   rootobj = Xml_Read_File( argv[j] );
  
   printf("\nTraversing:\n");
   traverse( rootobj );
   j++;
  }

 return 0;
}
