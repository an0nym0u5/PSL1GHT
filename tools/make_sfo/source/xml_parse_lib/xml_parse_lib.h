/*************************************************************************/
/* XML Parse Lib Header file - Public definitions.       		 */
/*  Library routines for parsing and generating	XML.			 */
/* 									 */
/* For Documentation and Usage Notes, see:				 */
/*				http://xmlparselib.sourceforge.net/	 */
/*									 */
/* Xml_Parse_Lib.c - MIT License:                                        */
/* Copyright (C) 2001, Carl Kindman					 */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the       */
/* "Software"), to deal in the Software without restriction, including   */
/* without limitation the rights to use, copy, modify, merge, publish,   */
/* distribute, sublicense, and/or sell copies of the Software, and to    */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:                                             */
/*									 */
/* The above copyright notice and this permission notice shall be        */
/* included in all copies or substantial portions of the Software.       */
/*									 */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,       */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    */
/* MERCHANTABILITY, FITNESS FOR PARTICULAR PURPOSE AND NONINFRINGEMENT.  */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE     */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                */
/*									 */
/*  Carl Kindman 8-21-2001     carl_kindman@yahoo.com			 */
/************************************************************************/

#define XML_MAX_STRLEN 10000

typedef struct Xml_name_value_pair
 {
   char *name, *value;
   struct Xml_name_value_pair *nxt;
 } Xml_name_value_pair;


typedef struct Xml_object
 {
   char *tag, *contents;
   Xml_name_value_pair *attributes;
   struct Xml_object *parent, *children, *nxt;
 } Xml_object;



 /*--------------------------------------------*/
 /* High-level XML file Read + Write routines. */
 /*--------------------------------------------*/

 /* Read xml file into xml token-tree. */
 Xml_object *Xml_Read_File( char *fname );

 /* Write xml token-tree out to xml file. */
 void Xml_Write_File( char *fname, Xml_object *object );



 /*----------------------------------*/
 /* Medium-level Xml Tree functions. */
 /*----------------------------------*/
 struct xml_private_stack
  {
    Xml_object  *current_object,
		*last_child;
    struct xml_private_stack *parent;
  };
 struct xml_private_tree
  {
   struct xml_private_stack *current_parent;
   struct xml_private_tree *traverse_parent;
   Xml_object *root_object, *traverse_node;
   Xml_name_value_pair *lastattrib, *traverse_attrib;
  };

 /* Functions for constructing new xml trees. */
 struct xml_private_tree *xml_tree_init();	/* Call this first. */
 void xml_tree_add_tag( struct xml_private_tree *xml_tree, char *tagname );
 void xml_tree_add_contents( struct xml_private_tree *xml_tree, char *contents );
 void xml_tree_add_attribute( struct xml_private_tree *xml_tree, char *name, char *value );
 void xml_tree_begin_children( struct xml_private_tree *xml_tree );
 void xml_tree_end_children( struct xml_private_tree *xml_tree );
 Xml_object *xml_tree_cleanup( struct xml_private_tree **xml_tree );

 /* Functions for traversing xml trees. */
 void xml_tree_start_traverse( struct xml_private_tree **xml_tree, Xml_object *roottag,
			     char *tag, char *contents, int maxlen );	/* Call this first. */
 int xml_tree_get_next_tag( struct xml_private_tree *xml_tree, char *tag, char *contents, int maxlen );
 int xml_tree_get_next_attribute( struct xml_private_tree *xml_tree, char *name, char *value, int maxlen );
 int xml_tree_descend_to_child( struct xml_private_tree **xml_tree, char *tag, char *contents, int maxlen  );
 void xml_tree_ascend( struct xml_private_tree **xml_tree );



 /*-----------------------------------*/
 /* Lower-level convenience routines. */
 /*-----------------------------------*/

 /* Get next xml-tag, attribtues, and contents from an xml-file. */
 void xml_parse( FILE *fileptr, char *tag, char *content, int maxlen, int *linenum );

 /* Pull-off tag's name. */
 void xml_grab_tag_name( char *tag, char *name, int maxlen );

 /* Pull-off next attribute name-value pair, if any, from tag-string. */
 void xml_grab_attrib( char *tag, char *name, char *value, int maxlen );

 /* Accept frequency, and/or convert units to Hz. Return 1 on success, 0 on failure. */
 int accept_frequency( char *wrd, float *freq );

 /* Accept power value, and/or convert units to Watts. Return 1 on success, 0 on failure. */
 int accept_power( char *wrd, float *pwr );

 /* Accept DeciBells value, and/or convert units to linear. Return 1 on success, 0 on failure. */
 int accept_dbvalue( char *wrd, float *value, char units );

 /* Accept distance or length value, and/or convert units to Meters. Return 1 on success, 0 on failure. */
 int accept_distance( char *wrd, float *dist );
 
 /* Accept time value, and/or convert units to Seconds. Return 1 on success, 0 on failure. */
 int accept_time( char *wrd, float *t );

 /* Accept boolean value from valid char-string answers. */
 int accept_boolean( char *word );


