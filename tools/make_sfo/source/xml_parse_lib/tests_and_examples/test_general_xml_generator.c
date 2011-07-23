/* -------------------------------------------------------------------------
 Test_general_xml_generator.c - A simple example of constructing arbitrary
   xml-file using re-usable xml-library.

 Compile:
  cc -g -O test_general_xml_generator.c -lm -o test_general_xml_generator.exe

 Run:
  ./test_general_xml_generator.exe
    (Produces "test_out.xml" file.)
 ---------------------------------------------------------------------------
*/

#include <stdio.h>

#include "../xml_parse_lib.c"


/*
  Create new XML by using:

   struct xml_private_tree *xml_tree_init();
   void xml_tree_add_tag( struct xml_private_tree *xml_tree, char *tagname );
   void xml_tree_add_contents( struct xml_private_tree *xml_tree, char *contents );
   void xml_tree_add_attribute( struct xml_private_tree *xml_tree, char *name, char *value );
   void xml_tree_begin_children( struct xml_private_tree *xml_tree );
   void xml_tree_end_children( struct xml_private_tree *xml_tree );
   Xml_object *xml_tree_cleanup( struct xml_private_tree **xml_tree );
   void Xml_Write_File( char *fname, Xml_object *object );
*/


int main( int argc, char **argv )
{
 int j=1;
 Xml_object *rootobj;
 struct xml_private_tree *xml_tree;

 xml_tree = xml_tree_init();	/* Initialize the tree. */

 /* Now add some objects, attributes, etc... */

 xml_tree_add_tag( xml_tree, "first_tag" );
 xml_tree_add_attribute( xml_tree, "attrib1", "value1" );
 xml_tree_add_attribute( xml_tree, "attrib2", "value2 <> &" );
 xml_tree_add_contents( xml_tree, "Some contents 1 <> &" );

 xml_tree_begin_children( xml_tree );
  xml_tree_add_tag( xml_tree, "first_child" );
  xml_tree_add_contents( xml_tree, "Some contents 11" );
  xml_tree_add_tag( xml_tree, "second_child" );
  xml_tree_add_contents( xml_tree, "Some contents 22" );
  xml_tree_add_attribute( xml_tree, "attrib21", "value21" );
  xml_tree_add_attribute( xml_tree, "attrib22", "value22" );

  xml_tree_begin_children( xml_tree );
   xml_tree_add_tag( xml_tree, "first_grand_child" );
   xml_tree_add_contents( xml_tree, "Some contents 33" );
   xml_tree_add_attribute( xml_tree, "attrib31", "value31" );

   xml_tree_add_tag( xml_tree, "second_grand_child" );
   xml_tree_add_contents( xml_tree, "Some contents 44" );
   xml_tree_add_attribute( xml_tree, "attrib41", "value41" );
  xml_tree_end_children( xml_tree );

 xml_tree_end_children( xml_tree );

 xml_tree_add_tag( xml_tree, "second_tag" );
 xml_tree_add_contents( xml_tree, "Some contents 2" );

 rootobj = xml_tree_cleanup( &xml_tree );

 Xml_Write_File( "test_out.xml", rootobj );

 printf("\nWrote 'test_out.xml'.\n");
 return 0;
}
