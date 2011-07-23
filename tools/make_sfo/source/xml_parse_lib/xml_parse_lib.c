/*************************************************************************/
/* XML Parse Lib - A set of routines for parsing and generating	XML.	 */
/* 									 */
/* For Documentation and Usage Notes, see:				 */
/*				http://xmlparselib.sourceforge.net/	 */
/*									 */
/* Public Low-level functions:						 */
/*	xml_parse( fileptr, tag, content, maxlen, linenum );		 */
/*	xml_grab_tag_name( tag, name, maxlen );				 */
/*	xml_grab_attrib( tag, name, value, maxlen );			 */
/* Public Higher-level functions:					 */
/*	Xml_Read_File( filename );					 */
/*	Xml_Write_File( filename, xml_tree );				 */
/*									 */
/* Xml_Parse_Lib.c - MIT License:					 */
/*  Copyright (C) 2001, Carl Kindman					 */
/* Permission is hereby granted, free of charge, to any person obtaining */
/* a copy of this software and associated documentation files (the	 */
/* "Software"), to deal in the Software without restriction, including	 */
/* without limitation the rights to use, copy, modify, merge, publish,	 */
/* distribute, sublicense, and/or sell copies of the Software, and to	 */
/* permit persons to whom the Software is furnished to do so, subject to */
/* the following conditions:						 */
/* 									 */
/* The above copyright notice and this permission notice shall be 	 */
/* included in all copies or substantial portions of the Software.	 */
/* 									 */
/* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, 	 */
/* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF	 */
/* MERCHANTABILITY, FITNESS FOR PARTICULAR PURPOSE AND NONINFRINGEMENT.	 */
/* IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  */
/* CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,	 */
/* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE	 */
/* SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.		 */
/* 									 */
/*  Carl Kindman 8-21-2001     carlkindman@yahoo.com			 */
/*  8-15-07 - Changed from strncpy to xml_strncpy for safety & speed.	 */
/*  10-2-07 - Changed to gracefully handle un-escaped ampersands.	 */
/*  11-19-08 - Added handling of escaped characters (&#xxxx).		 */
/*************************************************************************/

#include <stdlib.h>
#include <string.h>
#include "xml_parse_lib.h"

float xml_parse_version=1.0;

/*.......................................................................
  . XML_NEXT_WORD - accepts a line of text, and returns with the        .
  . next word in that text in the third parameter, the original line    .
  . is shortened from the beginning so that the word is removed.        .
  . If the line encountered is empty, then the word returned will be    .
  . empty.                                                              .
  . NEXTWORD can parse on an arbitrary number of delimiters, and it 	.
  . returns everthing that was cut away in the second parameter.	.
  .......................................................................*/
void Xml_Next_Word( char *line, char *word, int maxlen, char *delim )
{
 int i=0, j=0, m=0, flag=1;

 while ((line[i]!='\0') && (flag))   /* Eat away preceding garbage */
  {
   j = 0;
   while ((delim[j]!='\0') && (line[i]!=delim[j]))  j = j + 1;
   if (line[i]==delim[j])  i++;  else  flag = 0;
  }
 maxlen--;
 while ((line[i]!='\0') && (m < maxlen) && (!flag))  /* Copy the word until the next delimiter. */
  {
   word[m++] = line[i++];
   if (line[i]!='\0')
    {
     j = 0;
     while ((delim[j]!='\0') && (line[i]!=delim[j]))  j = j + 1;
     if (line[i]==delim[j])  flag = 1;
    }
  }
 j = 0;			 /* Shorten line. */
 while (line[i]!='\0') line[j++] = line[i++];
 line[j] = '\0';	 /* Terminate the char-strings. */
 word[m] = '\0';
}


/********************************************************************************/
/* xml_strncpy - Copy src string to dst string, up to maxlen characters.	*/
/* Safer and faster than strncpy, because it does not fill destination string, 	*/
/* but only copies up to the length needed.  Src string should be		*/
/* null-terminated, and must-be if its allocated length is shorter than maxlen. */
/* Up to maxlen-1 characters are copied to dst string. The dst string is always */
/* null-terminated.  The dst string should be pre-allocated to at least maxlen  */
/* bytes.  However, this function will work safely for dst arrays that are less */
/* than maxlen, as long as the null-terminated src string is known to be	*/
/* shorter than the allocated length of dst, just like regular strcpy.		*/
/********************************************************************************/
void xml_strncpy( char *dst, const char *src, int maxlen )
{ 
  int j=0, oneless;
  oneless = maxlen - 1;
  while ((j < oneless) && (src[j] != '\0')) { dst[j] = src[j];  j++; }
  dst[j] = '\0';
}


void xml_remove_leading_trailing_spaces( char *word )
{
 int i=0, j=0;
 while ((word[i]!='\0') && ((word[i]==' ') || (word[i]=='\t') || (word[i]=='\n') || (word[i]=='\r')))
  i = i + 1;
 do { word[j++] = word[i++]; } while (word[i-1]!='\0');
 j = j - 2;
 while ((j>=0) && ((word[j]==' ') || (word[j]=='\t') || (word[j]=='\n') || (word[j]=='\r')))
  j = j - 1;
 word[j+1] = '\0';
}


void xml_escape_symbols( char *phrase, int maxlen )
{ /* Replace any ampersand (&), quotes ("), or brackets (<,>), with XML escapes. */
  int j=0, k, m, n;
  n = strlen(phrase);
  do
   {
    if (phrase[j]=='&') 
     {
      k = n + 4;  m = n;  n = n + 4;
      if (n > maxlen) {printf("xml_Parse: MaxStrLen %d exceeded.\n",maxlen); return;}
      do phrase[k--] = phrase[m--]; while (m > j);
      j++;  phrase[j++] = 'a';  phrase[j++] = 'm';  phrase[j++] = 'p';  phrase[j++] = ';';
     } else
    if (phrase[j]=='"') 
     {
      k = n + 5;  m = n;  n = n + 5;
      if (n > maxlen) {printf("xml_Parse: MaxStrLen %d exceeded.\n",maxlen); return;}
      do phrase[k--] = phrase[m--]; while (m > j);
      phrase[j++] = '&';  phrase[j++] = 'q';  phrase[j++] = 'u';  phrase[j++] = 'o';  phrase[j++] = 't';  phrase[j++] = ';';
     } else
    if (phrase[j]=='<') 
     {
      k = n + 3;  m = n;  n = n + 3;
      if (n > maxlen) {printf("xml_Parse: MaxStrLen %d exceeded.\n",maxlen); return;}
      do phrase[k--] = phrase[m--]; while (m > j);
      phrase[j++] = '&';  phrase[j++] = 'l';  phrase[j++] = 't';  phrase[j++] = ';';
     } else
    if (phrase[j]=='>') 
     {
      k = n + 3;  m = n;  n = n + 3;
      if (n > maxlen) {printf("xml_Parse: MaxStrLen %d exceeded.\n",maxlen); return;}
      do phrase[k--] = phrase[m--]; while (m > j);
      phrase[j++] = '&';  phrase[j++] = 'g';  phrase[j++] = 't';  phrase[j++] = ';';
     } else j++;
   }
  while (phrase[j] != '\0');
}


int xml_ishexadecimal( char ch, int *hex, int *sum )	/* Return true if character is a numeric or hexadeximal symbol, else zero. */
{							/* If numeric, capture value and set hex true if hex or false if base-10. */
 if (ch < '0') return 0;
 if (*hex)  *sum = 16 * *sum;  else  *sum = 10 * *sum;
 if (ch <= '9') { *sum = *sum + ch - 48;  return 1; }
 if (ch < 'A') return 0;
 if ((*hex) && (ch <= 'F')) { *sum = *sum + ch - 55;  return 1; }
 if ((ch == 'X') && (*hex != 1) && (*sum == 0)) { *hex = 1;  return 1; }
 if (ch < 'a') return 0;
 if ((*hex) && (ch <= 'f')) { *sum = *sum + ch - 87;  return 1; }
 if ((ch == 'x') && (*hex != 1) && (*sum == 0)) { *hex = 1;  return 1; } else return 0;
}


void xml_restore_escapes( char *phrase )
{ /* Replace any xml-escapes for (&), quotes ("), or brackets (<,>), with original symbols. */
  int j=0, k, m, n;

  n = strlen(phrase);
  if (n == 0) return;
  do
   {
    if (phrase[j]=='&') 
     {
      switch (phrase[j+1])
       {
        case 'a':   /* &amp; */
	  j++;  m = j;  k = j + 4;
	  if (k > n) {printf("xml_Parse: String ends prematurely after ampersand '%s'.\n",phrase); return;}
	  // if (strncmp( &(phrase[j]), "amp;", 4 ) != 0) {printf("xml_Parse: Unexpected &-escape '%s'.\n",phrase); return;}
	  n = n - 4;
	  do phrase[m++] = phrase[k++]; while (phrase[k-1] != '\0');
	 break;
        case 'q':   /* &quot; */
	  phrase[j++] = '"';
	  m = j;  k = j + 5;
	  if (k > n) {printf("xml_Parse: String ends prematurely after ampersand '%s'.\n",phrase); return;}
	  // if (strncmp( &(phrase[j]), "quot;", 5 ) != 0) {printf("xml_Parse: Unexpected &-escape '%s'.\n",phrase); return;}
	  n = n - 5;
	  do phrase[m++] = phrase[k++]; while (phrase[k-1] != '\0');
	 break;
        case 'l':   /* &lt; */
	  phrase[j++] = '<';
	  m = j;  k = j + 3;
	  if (k > n) {printf("xml_Parse: String ends prematurely after ampersand '%s'.\n",phrase); return;}
	  // if (strncmp( &(phrase[j]), "lt;", 3 ) != 0) {printf("xml_Parse: Unexpected &-escape '%s'.\n",phrase); return;}
	  n = n - 3;
	  do phrase[m++] = phrase[k++]; while (phrase[k-1] != '\0');
	 break;
        case 'g':   /* &gt; */
	  phrase[j++] = '>';
	  m = j;  k = j + 3;
	  if (k > n) {printf("xml_Parse: String ends prematurely after ampersand '%s'.\n",phrase); return;}
	  // if (strncmp( &(phrase[j]), "gt;", 3 ) != 0) {printf("xml_Parse: Unexpected &-escape '%s'.\n",phrase); return;}
	  n = n - 3;
	  do phrase[m++] = phrase[k++]; while (phrase[k-1] != '\0');
	 break;
	case '#':   /* &#0000; */
	  { int hex=0, sum = 0;
	   k = j + 2;
	   while ((k < j + 6) && (k < n) && (phrase[k] != ';') && (xml_ishexadecimal( phrase[k], &hex, &sum )))  k++;
	   if ((k > n) || (phrase[k] != ';'))
	    {printf("xml_Parse: String ends prematurely after ampersand '%s'.\n",phrase); return;}
	   phrase[j++] = sum;  m = j;  k++;
	   do phrase[m++] = phrase[k++]; while (phrase[k-1] != '\0');
          }
	 break;
	default: printf("xml_Parse: Unexpected char (%c) follows ampersand (&) in xml. (phrase='%s')\n", phrase[j+1], phrase );  j++;
       } 
     } else j++;
   }
  while (phrase[j] != '\0');
}



/************************************************************************/
/* XML_GRAB_TAG_NAME - This routine gets the tag-name, and shortens the	*/
/*  xml-tag by removing it from the tag-string.  Use after calling 	*/
/*  xml_parse to get the next tag-string from a file.  			*/
/*  If the tag is just a closing-tag, it will return "/".		*/
/*  Use in combination with xml_grab_attribute to parse any following	*/
/*  attributes within the tag-string.					*/
/* Inputs:	tag - String as read by xml_parse.		 	*/
/*		malen - Maximum length of returned name that can be 	*/
/*			returned.  (Buffer-size.)			*/
/* Output:	name - Character string.				*/
/************************************************************************/
void xml_grab_tag_name( char *tag, char *name, int maxlen )
{
 int j; 
 Xml_Next_Word( tag, name, maxlen, " \t\n\r");
 j = strlen(name);
 if ((j > 1) && (name[j-1] == '/'))	/* Check for case where slash was attached to end of tag-name. */
  {
   name[j-1] = '\0';	/* Move slash back to tag. */
   j = strlen(tag);
   do { tag[j+1] = tag[j];  j--; } while (j >= 0);
   tag[0] = '/';
  }
}



/************************************************************************/
/* XML_GRAB_ATTRIBVALUE - This routine grabs the next name-value pair	*/
/*  within an xml-tag, if any.  Use after calling xml_parse and 	*/
/*  xml_grab_tag_name, to get the following tag attribute string.  Then */
/*  call this sequentially to grab each 				*/
/*  		name = "value" 						*/
/*  attribute pair, if any, until exhausted.  If the tag is closed by 	*/
/*  "/", the last name returned will be "/" and the value will be empty.*/
/*  This routine expands any escaped symbols in the value-string before */
/*  returning. 								*/
/* Inputs:	tag - String as read by xml_parse.		 	*/
/*		malen - Maximum length of returned name or value that 	*/
/*			can be returned.  (Buffer-sizes.)		*/
/* Outputs:	name - Character string.				*/
/*		value - Character string.				*/
/************************************************************************/
void xml_grab_attrib( char *tag, char *name, char *value, int maxlen )
{ 
 int j=0, k=0;

 Xml_Next_Word( tag, name, maxlen, " \t=\n\r");	 /* Get the next attribute's name. */
 /* Now get the attribute's value-string. */
 /* Sequence up to first quote.  Expect only white-space and equals-sign. */
 while ((tag[j]!='\0') && (tag[j]!='\"'))
  {
   if ((tag[j]!=' ') && (tag[j]!='\t') && (tag[j]!='\n') && (tag[j]!='\r') && (tag[j]!='='))
    printf("xml error: unexpected char before attribute value quote '%s'\n", tag);
   j++;
  }
 if (tag[j]=='\0')  { value[0] = '\0';  tag[0] = '\0';  return; }
 if (tag[j++]!='\"')
  { printf("xml error: missing attribute value quote '%s'\n", tag); tag[0] = '\0'; value[0] = '\0'; return;}
 while ((tag[j]!='\0') && (tag[j]!='\"')) { value[k++] = tag[j++]; } 
 value[k] = '\0';
 if (tag[j]!='\"') printf("xml error: unclosed attribute value quote '%s'\n", tag);  else j++;
 xml_restore_escapes( value );
 /* Now remove the attribute (name="value") from the original tag-string. */
 k = 0;
 do tag[k++] = tag[j++]; while (tag[k-1] != '\0');
}



/****************************************************************/
/* XML_PARSE - This routine finds the next <xxx> tag, and grabs	*/
/*	it, and then grabs whatever follows, up to the next tag.*/
/*	It returns the tag and its following contents.		*/
/*	It cleans any trailing white-space from the contents.	*/
/*  This routine is intended to be called iteratively, to parse	*/
/*  XML-formatted data.  Specifically, it pulls tag-string of	*/
/*  each tag (<...>) and content-string between tags (>...<).	*/
/* Inputs:							*/
/*	fileptr - Opened file pointer to read from.		*/
/*	malen - Maximum length of returned tag or content that  */
/*		can be returned.  (Buffer-sizes.)		*/
/* Outputs:							*/
/*	tag - Char string of text between next <...> brackets. 	*/
/*	content - Char string of text after > up to next < 	*/
/*		  bracket. 					*/
/****************************************************************/
void xml_parse( FILE *fileptr, char *tag, char *content, int maxlen, int *lnn )
{
 int i;  char ch;

 /* Get up to next tag. */
 do { ch = getc(fileptr);  if (ch=='\n') (*lnn)++; } while ((!feof(fileptr)) && (ch != '<'));

 i = 0; 	/* Grab this tag. */
 do 
  { do { tag[i] = getc(fileptr);  if (tag[i]=='\n') tag[i] = ' '; }
    while ((tag[i]=='\r') && (!feof(fileptr)));  i=i+1; 
    if ((i==3) && (tag[0]=='!') && (tag[1]=='-') && (tag[2]=='-'))
     { /*Filter_comment.*/
       i = 0;
       do { ch = getc(fileptr); if (ch=='-') i = i + 1; else if ((ch!='>') || (i==1)) i = 0; } 
       while ((!feof(fileptr)) && ((i<2) || (ch!='>')));
       do { ch = getc(fileptr);  if (ch=='\n') (*lnn)++; } while ((!feof(fileptr)) && (ch != '<'));
       i = 0;
     } /*Filter_comment.*/
  } while ((!feof(fileptr)) && (i < maxlen) && ((i == 0) || (tag[i-1] != '>')));
 if (i==0) i = 1;
 tag[i-1] = '\0';

 i = 0; 	/* Now grab contents until next tag. */
 do
  { do  content[i] = getc(fileptr);  while ((content[i]=='\r') && (!feof(fileptr)));
    if (content[i]==10) (*lnn)++; i=i+1;
  }
 while ((!feof(fileptr)) && (i < maxlen) && (content[i-1] != '<'));
 ungetc( content[i-1], fileptr );
 if (i==0) i = 1;
 content[i-1] = '\0';

 /* Clean-up contents by removing trailing white-spaces, and restoring any escaped characters. */
 xml_remove_leading_trailing_spaces( tag );
 xml_remove_leading_trailing_spaces( content );
 xml_restore_escapes( content );
}








Xml_name_value_pair *new_xml_attribute( char *name, char *value )
{
 Xml_name_value_pair *newattr;
 newattr = (Xml_name_value_pair *)malloc(sizeof(Xml_name_value_pair));
 newattr->name = strdup(name);
 newattr->value = strdup(value);
 newattr->nxt = 0;
 return newattr;
}

Xml_object *new_xml_object( char *tag, char *contents )
{
 Xml_object *newobj;
 newobj = (Xml_object *)calloc(1,sizeof(Xml_object));
 newobj->tag = strdup(tag);
 newobj->contents = strdup(contents);
 return newobj;
}


/* -- Private support structure and routines. -- */
 struct xml_private_stack *xml_stack_freelist=0;

 struct xml_private_stack *new_xml_stack_item( struct xml_private_stack *parent, Xml_object *newtag )
 {
  struct xml_private_stack *newptr;
  if (xml_stack_freelist==0) newptr = (struct xml_private_stack *)malloc(sizeof(struct xml_private_stack));
  else 
   {
    newptr = xml_stack_freelist;
    xml_stack_freelist = xml_stack_freelist->parent;
   }
  newptr->parent = parent;
  newptr->current_object = newtag;
  newptr->last_child = 0;
  return newptr;
 }

 void xml_private_free_stack_item( struct xml_private_stack *item )
 {
  item->parent = xml_stack_freelist;
  xml_stack_freelist = item;
 }


 /* -- Xml Tree structures and functions. -- */
 struct xml_private_tree *xml_tree_init()
 {
  struct xml_private_tree *newtree;
  newtree = (struct xml_private_tree *)calloc(1,sizeof(struct xml_private_tree));
  newtree->current_parent = new_xml_stack_item(0,0);  /* Set the root tag level. */
  return newtree;
 }

 void xml_tree_add_tag( struct xml_private_tree *xml_tree, char *tagname )
 {
  Xml_object *newtag;
  newtag = new_xml_object( tagname, "" );
  if (xml_tree->root_object == 0) xml_tree->root_object = newtag;
  else
   {
    if (xml_tree->current_parent->last_child == 0)
     xml_tree->current_parent->current_object->children = newtag;
    else xml_tree->current_parent->last_child->nxt = newtag;
    newtag->parent = xml_tree->current_parent->current_object;
   }
  xml_tree->current_parent->last_child = newtag;
  xml_tree->lastattrib = 0;
 }

 void xml_tree_add_contents( struct xml_private_tree *xml_tree, char *contents )
 {
  if (xml_tree->current_parent->last_child == 0) {printf("xml: Error, attempt to add contents with no tag. (%s)\n",contents); return;}
  if ((xml_tree->current_parent->last_child->contents != 0) && (xml_tree->current_parent->last_child->contents[0] != '\0'))
   printf("xml: Warning, Overwriting contents (%s) with (%s).\n", xml_tree->current_parent->last_child->contents, contents);
  xml_tree->current_parent->last_child->contents = strdup(contents);
 }

 void xml_tree_add_attribute( struct xml_private_tree *xml_tree, char *name, char *value )
 {
  Xml_name_value_pair *newattrib;
  if (xml_tree->current_parent->last_child == 0) {printf("xml: Error, attempt to add attributes with no tag. (%s=%s)\n",name,value); return;}
  newattrib = new_xml_attribute( name, value );
  if (xml_tree->lastattrib==0) xml_tree->current_parent->last_child->attributes = newattrib;
  else xml_tree->lastattrib->nxt = newattrib;
  xml_tree->lastattrib = newattrib;
 }

 void xml_tree_begin_children( struct xml_private_tree *xml_tree )
 {
  if ((! xml_tree) || (! xml_tree->current_parent) || (! xml_tree->current_parent->last_child))
    { printf("xml: Error, attempt to add children to tagless tree.\n");  return; }
  xml_tree->current_parent = new_xml_stack_item( xml_tree->current_parent, xml_tree->current_parent->last_child );
 }

 void xml_tree_end_children( struct xml_private_tree *xml_tree )
 {
  struct xml_private_stack *old_tag;
  if ((!xml_tree) || (xml_tree->current_parent->current_object==0))
   {printf("Xml Error: Attempt to end-children with no tag.\n");  return;}
  old_tag = xml_tree->current_parent;
  xml_tree->current_parent = xml_tree->current_parent->parent;
  xml_private_free_stack_item( old_tag );
  if (xml_tree->current_parent==0) {printf("Xml Error: Too many end-children levels encountered.\n"); return;}
 }

Xml_object *xml_tree_cleanup( struct xml_private_tree **xml_tree )
{
 Xml_object *root_object;
 struct xml_private_stack *old_tag;
 if (*xml_tree == 0) {printf("xml: Warning, empty xml tree on cleanup.\n"); return 0;}
 root_object = (*xml_tree)->root_object;
 xml_private_free_stack_item( (*xml_tree)->current_parent );
 while (xml_stack_freelist != 0)	/* Cleanup temporary variables. */
  { old_tag = xml_stack_freelist;  xml_stack_freelist = xml_stack_freelist->parent;  free(old_tag); }
 *xml_tree = 0;
 return root_object;
}


void xml_tree_start_traverse( struct xml_private_tree **xml_tree, Xml_object *roottag,
			     char *tag, char *contents, int maxlen )
{
 *xml_tree = (struct xml_private_tree *)calloc(1,sizeof(struct xml_private_tree));
 (*xml_tree)->traverse_node = roottag;
 if (roottag != 0) 
  {
   xml_strncpy(tag, (*xml_tree)->traverse_node->tag, maxlen);
   xml_strncpy(contents, (*xml_tree)->traverse_node->contents, maxlen);
   (*xml_tree)->traverse_attrib = roottag->attributes;
  }
 (*xml_tree)->traverse_parent = 0;
}

int xml_tree_get_next_tag( struct xml_private_tree *xml_tree, char *tag, char *contents, int maxlen )
{
 if (xml_tree==0) 
  {printf("Error: xml_tree_get_next_tag called on empty tree, or beyond tree.\n");  tag[0] = '\0';  contents[0] = '\0';  return 0; }
 if (xml_tree->traverse_node != 0) 
   xml_tree->traverse_node = xml_tree->traverse_node->nxt;
 if (xml_tree->traverse_node != 0)
  {
   xml_strncpy(tag, xml_tree->traverse_node->tag, maxlen);
   xml_strncpy(contents, xml_tree->traverse_node->contents, maxlen);
   xml_tree->traverse_attrib = xml_tree->traverse_node->attributes;
   return 1;
  } else { tag[0] = '\0';  contents[0] = '\0';  return 0; }
}

int xml_tree_get_next_attribute( struct xml_private_tree *xml_tree, char *name, char *value, int maxlen )
{
 if (xml_tree->traverse_attrib != 0)
  {
   xml_strncpy(name, xml_tree->traverse_attrib->name, maxlen);
   xml_strncpy(value, xml_tree->traverse_attrib->value, maxlen);
   xml_tree->traverse_attrib = xml_tree->traverse_attrib->nxt;
   return 1;
  } else { name[0] = '\0';  value[0] = '\0';  return 0; }
}

int xml_tree_descend_to_child( struct xml_private_tree **xml_tree, char *tag, char *contents, int maxlen  )
{
 struct xml_private_tree *newitem;
 if ((*xml_tree)->traverse_node->children != 0)
  {
   newitem = (struct xml_private_tree *)calloc(1,sizeof(struct xml_private_tree));
   newitem->traverse_node = (*xml_tree)->traverse_node->children;
   newitem->traverse_attrib = newitem->traverse_node->attributes;
   newitem->traverse_parent = *xml_tree;
   xml_strncpy(tag, newitem->traverse_node->tag, maxlen);
   xml_strncpy(contents, newitem->traverse_node->contents, maxlen);
   *xml_tree = newitem;
   return 1;
  }
 else { tag[0] = '\0';  contents[0] = '\0';  return 0; }
}

void xml_tree_ascend( struct xml_private_tree **xml_tree )
{ struct xml_private_tree *old;
 if (*xml_tree != 0)
  {
   old = *xml_tree;
   *xml_tree = (*xml_tree)->traverse_parent;
   free( old );
  }
}

/* -- End Private structure and routines. -- */




/********************************************************/
/* Xml_Read_File - 					*/
/********************************************************/
Xml_object *Xml_Read_File( char *fname )
{
 FILE *infile;
 int lnn=0;
 char *tag, *attrib, *value, *contents;
 Xml_object *newtag, *roottag=0;
 Xml_name_value_pair *newattrib, *lastattrib;
 lastattrib = NULL ;
 struct xml_private_stack *current_parent, *old_tag;	/* Current_parent points to parent of current children. */


 infile = fopen(fname,"r");
 if (infile==0) {printf("XML Error: Cannot open input file '%s'.\n",fname); return 0;}
 current_parent = new_xml_stack_item(0,0);  /* Set the root tag level. */
 tag = (char *)malloc(XML_MAX_STRLEN);
 attrib = (char *)malloc(XML_MAX_STRLEN);
 value = (char *)malloc(XML_MAX_STRLEN);
 contents = (char *)malloc(XML_MAX_STRLEN);
 xml_parse( infile, tag, contents, XML_MAX_STRLEN, &lnn ); 
 while (!feof(infile))
  { /*next_tag*/
    xml_grab_tag_name( tag, attrib, XML_MAX_STRLEN );

    if (attrib[0]=='/')		/* If tag begins with "/", then go-up (pop-stack after comparing tag). */
     { /*pop-stack*/
       if ((current_parent->current_object==0) || (strcasecmp(current_parent->current_object->tag,&(attrib[1]))!=0))
	{printf("Xml Error: Mismatching closing tag '%s'. Aborting.\n",attrib); free(tag); free(attrib); free(value); free(contents); return 0;}
       old_tag = current_parent;
       current_parent = current_parent->parent;
       xml_private_free_stack_item( old_tag );
       if (current_parent==0)
	{printf("Xml Error: extra closing tag '%s'. Aborting.\n",attrib); free(tag); free(attrib); free(value); free(contents); return 0;}
     } /*pop-stack*/
    else
     { /*Open-tag*/
      newtag = new_xml_object( attrib, contents );
      if (roottag == 0)	roottag = newtag;
      else
       {
	if (current_parent->last_child == 0)  current_parent->current_object->children = newtag;
	else current_parent->last_child->nxt = newtag;
        newtag->parent = current_parent->current_object;
       }
      current_parent->last_child = newtag;

      xml_grab_attrib( tag, attrib, value, XML_MAX_STRLEN );	/* Accept the attributes within tag. */
      while ((attrib[0]!='\0') && (attrib[0]!='/'))
       {
        newattrib = new_xml_attribute( attrib, value );
        if (newtag->attributes==0) newtag->attributes = newattrib; else lastattrib->nxt = newattrib;
        lastattrib = newattrib;
	xml_grab_attrib( tag, attrib, value, XML_MAX_STRLEN );
       }

      /* If tag does not end in "/", then go-down (push-stack). IE. Next tag should be a child of present tag. */
      if (attrib[0] != '/')
       {
        current_parent = new_xml_stack_item( current_parent, newtag );
       }  /* Otherwise, attaches to last child of present parent. */
     } /*Open-tag*/

    xml_parse( infile, tag, contents, XML_MAX_STRLEN, &lnn ); 
  } /*next_tag*/
 fclose(infile);
 while (xml_stack_freelist != 0)	/* Cleanup temporary variables. */
  { current_parent = xml_stack_freelist;  xml_stack_freelist = xml_stack_freelist->parent;  free(current_parent); }
 free(tag);  free(attrib);  free(value);  free(contents);
 return roottag;
}



/********************************************************/
/* Xml_Write_File - 					*/
/********************************************************/
void Xml_Write_File( char *fname, Xml_object *object )
{
 int j, k, m, level=0, maxstrlen2 = 2 * XML_MAX_STRLEN;
 Xml_name_value_pair *attrib;
 char *tmpwrd1, *tmpwrd2;
 FILE *outfile;

 tmpwrd1 = (char *)malloc(XML_MAX_STRLEN);
 tmpwrd2 = (char *)malloc(maxstrlen2);
 outfile = fopen(fname,"w");
 if (outfile==0) {printf("XML Error: Cannot open output file '%s'.\n",fname); return;}
 while (object != 0)
  {
   for (j=0; j<level; j++) fprintf(outfile,"  ");
   strcpy( tmpwrd2, object->tag );
   xml_escape_symbols( tmpwrd2, maxstrlen2 );
   fprintf(outfile,"<%s", tmpwrd2 );
   k = 0;  m = 0;
   attrib = object->attributes;
   while (attrib)
    { /*put_attribs*/
     if ((strcmp(attrib->name,"?")==0) && (attrib->value[0]=='\0'))	/* Handle special case of "?" attribute. */
      fprintf(outfile," ?");
     else
      {
       strcpy( tmpwrd1, attrib->name );
       xml_escape_symbols( tmpwrd1, XML_MAX_STRLEN );
       strcpy( tmpwrd2, attrib->value );
       xml_escape_symbols( tmpwrd2, maxstrlen2 );
       if (k > 80) { fprintf(outfile,"\n  "); for (j=0; j<level; j++) fprintf(outfile,"  ");  k = 0;  m++; }
       fprintf(outfile," %s=\"%s\"", tmpwrd1, tmpwrd2 );
       k = k + strlen(tmpwrd1) + strlen(tmpwrd2) + 4;
      }
     attrib = attrib->nxt;
    } /*put_attribs*/
   if (m>0) { fprintf(outfile,"\n"); for (j=0; j<level; j++) fprintf(outfile,"  "); }
   if (object->children == 0)
    { /*nokids*/
     if (object->contents[0] == '\0') fprintf(outfile,"/>\n");
     else
      {
       strcpy( tmpwrd1, object->tag );
       xml_escape_symbols( tmpwrd1, XML_MAX_STRLEN );
       strcpy( tmpwrd2, object->contents );
       xml_escape_symbols( tmpwrd2, maxstrlen2 );
       fprintf(outfile,">%s</%s>\n", tmpwrd2, tmpwrd1 );
      }
     if (object->nxt != 0) object = object->nxt;	/* Next. */
     else
      { /*Ascend(close)*/

       do
        {
         if (object==object->parent) {printf("Object == parent.  Circular.  Aborting.\n"); exit(1);}
	 object = object->parent;  
	 level--;
	 if ((object != 0) && (object->tag[0] != '?'))
	  {
	   for (j=0; j<level; j++) fprintf(outfile,"  ");
	   strcpy( tmpwrd2, object->tag );
	   xml_escape_symbols( tmpwrd2, maxstrlen2 );
	   fprintf(outfile,"</%s>\n", tmpwrd2 ); 	/* Show closing tag. */
	  }
	 if (level < -100) {printf("Abort due to unended looping.\n"); exit(1);}
	}
       while ((object != 0) && (object->nxt == 0));
       if ((object != 0) && (object->nxt != 0))  object = object->nxt;

      } /*Ascend(close)*/
    } /*nokids*/
   else
    { /*Descend*/
      if (object->contents[0] != '\0')
       { /*put_contents*/
	 strcpy( tmpwrd2, object->contents );
	 xml_escape_symbols( tmpwrd2, maxstrlen2 );
	 fprintf(outfile,">%s\n", tmpwrd2 );
       } /*put_contents*/
      else fprintf(outfile,">\n");
      if (object->tag[0] != '?') level++;
      object = object->children;
    }

  }
 fclose(outfile);
 free(tmpwrd1);
 free(tmpwrd2);
}



/* ============================================================== */
/* End of Re-Usable XML Parser Routines.         		  */
/* ============================================================== */

