#ifndef COS_COS_DOCSTR_H
#define COS_COS_DOCSTR_H

/*
 o---------------------------------------------------------------------o
 |
 | COS doc string
 |
 o---------------------------------------------------------------------o
 |
 | C Object System
 |
 | Copyright (c) 2006+ Laurent Deniau, laurent.deniau@cern.ch
 |
 | For more information, see:
 | http://cern.ch/laurent.deniau/cos.html
 |
 o---------------------------------------------------------------------o
 |
 | This file is part of the C Object System framework.
 |
 | The C Object System is free software; you can redistribute it and/or
 | modify it under the terms of the GNU Lesser General Public License
 | as published by the Free Software Foundation; either version 3 of
 | the License, or (at your option) any later version.
 |
 | The C Object System is distributed in the hope that it will be
 | useful, but WITHOUT ANY WARRANTY; without even the implied warranty
 | of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 |
 | See <http://www.gnu.org/licenses> for more details.
 |
 o---------------------------------------------------------------------o
 |
 | $Id: docstr.h,v 1.2 2010/03/14 08:58:12 ldeniau Exp $
 |
*/

#ifndef COS_COS_COS_H
#error "COS: use <cos/cos/cos.h> instead of <cos/cos/docstr.h>"
#endif

/* NOTE-USER: source code documentation system

  DocStr markers aim to preserve line and tabulation formatting after macro
  expansion. They are removed/expanded by the COS document generator to
  generate properly indented reStructuredText format. The DocStr markers are:

  '' simple quote (expand to ')
  "" simple double quote (expand to ")
  "  literal text keeping its formatting (closed by another "). It is useful
     to insert complex reST formatted text like tables. The enclosing quotes
     will be removed by the doc generator.
  \\ simple backslash (expand to \)
  \  simple newline (expand to \n)
  \> increment current indentation
  \< decrement current indentation
  \^ reset     current indentation
  \p alias for . (dot) when the later doesn't work
  .  (dot) start a paragraph at current indentation (expand to \n\n\t{n})
  .. idem . but automatically increment the current indentation if
        the next character (after the space) is not _
        the next marker is not ..
  [*+-]|#.|@. (item) idem . if preceded by a :punct: (before the space)

  Examples:
  ---------

  defdoc(Nil, "Nil", classref(Nil),
    This is the root of predicate classes.
    
    . Nil and classes deriving from Nil cannot have instance, also called
      class-objects from which properties and predicates derive.
   
    . Use Nil (instead of (OBJ)0) if you mean "no-object" or "not-an-object".
      Remember, messages cannot be sent to (OBJ)0, but they can be sent (and
      traced) when sent to Nil.
   
    . Use Null (instead of Nil or (OBJ)0) if you mean "no-data" object.
      Messages can be sent (and traced) to Null and will be ignored.
  );
 
  defdoc(DocStrFmt, "DocStr.Format", 0,
    Docstr plain text format:
    -------------------------
    
    . docstr waits for plain text, not C quoted string! This is much
      easier to read and to write than documentation in a C string.
    
    . The syntax of docstr tries to preserve the line and column
      indentation even after the macro expansion which removes all
      this information using some specific markers (see above for
      the list).

    . A dot starts a new paragraph. The text in a docstr must be
      formatted after the reStructuredText text format (the target
      format) where indentation matters.
      
    . In some cases, docstr will increase/decrease the current indentation
      automatically to keep the definition of new explicit markup list
      simple.
      
    . In some cases, docstr will interpret some of the reST marker to 
      keep the definition of new list item (for example) simple.
  );
  
  -- the reStructuredText doc generator is not yet implemented --

  It should provide:
  for each project (program, shared lib)
    - a table of modules (including dependencies)
    - a table of all classes
    - a table of all generics
    - a table of all properties
  for each module
    - a table of all generic
    - a table of all classes
    - a table of all properties
  for each generic
    - a link to generic's class if not Generic
    - a list of all its methods
  for each classes
    - a link to the super classes
    - all its methods
  for each defmethod
    - links to its generic and classes
  for each component (class, generic, method, property)
    - a link to the source code
    - the doc (reStructuredText)
    
  Remark:
  docstr documentation is removed in release mode to save space and privacy
  of the documentation (a PDF can be created by running the program itself).
*/

/* docstr keywords:
 */
#ifdef  COS_DISABLE_ALL
#define COS_DISABLE_defdoc
#endif

#ifndef COS_DISABLE_defdoc
#define defdoc(...) COS_DOC_DEF(__VA_ARGS__)
#endif

/***********************************************************
 * Implementation
 */

COS_CLS_DEF(MetaDocStr,Object)
  STR ref; // module/section/textref
  OBJ obj; // component or metaref (e.g. function and types)
  STR doc; // doc string (reStructuredText)
COS_CLS_END

#ifdef COS_RELEASE

#define COS_DOC_DEF(TAG,REF,OBJ,...) \
   /* encode tag into rc */ \
   {{{ 0, cos_tag_docstr }}, \
   REF, OBJ, 0 /* no doc */ } \

#else

#define COS_DOC_DEF(TAG,REF,OBJ,...) \
struct MetaDocStr COS_DOC_NAME(TAG) = { \
   /* encode tag into rc */ \
   {{{ 0, cos_tag_docstr }}, \
   REF, OBJ, #__VA_ARGS__ } \
}

#endif

#endif // COS_COS_DOCSTR_H
