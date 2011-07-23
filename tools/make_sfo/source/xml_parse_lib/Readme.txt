XML Parse Lib - A set of routines for parsing and generating XML.

For Documentation and Usage Notes, see:
	http://xmlparselib.sourceforge.net/

Files:
  Readme.txt - This file.
  xml_parse_lib.h - Headers.  (Structures, data-types, & routine prototypes.)
  xml_parse_lib.c - Core XML-parsing functions.
  unit_convertors.c - Convenience routines for accepting, checking, or
			converting common units.
  xml_xsd_checker.c - Preliminary schema checker.

A directory of tests and examples is included under "tests_and_examples":
  app.c  - Simple stream-oriented (parse as-you-go) XML file reader
	   application.
  test_general_parser.c  - Reads XML-files into XML-tree and writes 
	   them back out from tree.
  test_general_xml_generator.c  - Generates XML files for testing.
  test_xml_token_traverser.c - Example of traversing an xml-tree, after
	   reading an xml-file into xml-tree.

Instructions for compiling and running the tests/examples are included
within the comment header of each program.

Public Low-level functions:
   xml_parse( fileptr, tag, content, maxlen, linenum );
   xml_grab_tag_name( tag, name, maxlen );
   xml_grab_attrib( tag, name, value, maxlen );
Public Higher-level functions:
   Xml_Read_File( filename );
   Xml_Write_File( filename, xml_tree );

Throughout this library, all text and program source files assume tabs 
are 8-spaces.

Xml_Parse_Lib.c - MIT License:
Copyright (C) 2001, Carl Kindman
Permission is hereby granted, free of charge, to any person obtaining 
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including   
without limitation the rights to use, copy, modify, merge, publish,   
distribute, sublicense, and/or sell copies of the Software, and to    
permit persons to whom the Software is furnished to do so, subject to 
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF    
MERCHANTABILITY, FITNESS FOR PARTICULAR PURPOSE AND NONINFRINGEMENT.  
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY  
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,  
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.  

Version history:
 v0.63 - Unified handling of white-space between tags.
 	 Added reformat_xml.c utility to tests_and_examples.
 v0.62 - Strengthened xml_grab_tag_name routine.
 v0.61 - Fixed potential erroneous warning message that could occur
	 when parsing ampersand escaped phrases.
 v0.60 - Added handling of escaped numeric symbols (&#000;) and (&#x00;).
 v0.52 - Handles un-escaped ampersands and tag-names with no space
         before a trailing slash more gracefully.
 v0.51 - Switched from strncpy to xml_strncpy for safety + speed.
 v0.50 - Code clean-up, stream-lining, additional comments.
 v0.04 - Some minor improvements of the examples.
 v0.03 - Updated license header to MIT License.
 v0.02 - Initial release.

Carl Kindman 4-23-2011     carlkindman@yahoo.com       
