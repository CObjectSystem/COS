/**
 * C Object System
 * 
 *
 * Copyright 2006+ Laurent Deniau <laurent.deniau@gmail.com>
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>

static int rmlit = 0;

static void
echo_1(FILE *in, FILE *out)
{
  fputc(fgetc(in), out);
}

static void
echo_upto(FILE *in, FILE *out, int chr)
{
  int c;
 
  while ((c = fgetc(in)) != EOF) {
    fputc(c, out);
    if (c == '\\') { echo_1(in, out); continue; }
    if (c == chr ) return;
  }
}

static void
skip_1(FILE *in)
{
  fgetc(in);
}

static void
skip_upto(FILE *in, int chr)
{
  int c;
 
  while ((c = fgetc(in)) != EOF) {
    if (c == '\\') { skip_1(in); continue; }
    if (c == chr ) return;
  }
}

static void
skip_line(FILE *in)
{
  int c;
 
  while ((c = fgetc(in)) != EOF && c != '\n') ;

  ungetc(c, in);
}

static void
skip_cmt(FILE *in)
{
  int c, p;

  for(p = 0; (c = fgetc(in)) != EOF; p = c)
    if (c == '/' && p == '*')
      break;

  ungetc(' ', in);
}

static void
remove_cmt(FILE *in , FILE *out)
{
  int c;
 
  while ((c = fgetc(in)) != EOF) {
    switch(c) {
      case '\'':
      case '"' : if (rmlit) skip_upto(in, c);
                 else { fputc(c, out); echo_upto(in, out, c); }
                 break;
      case '\\': fputc(c, out); echo_1(in, out); break;
      case '/' : c = fgetc(in);
                 if (c == '/') { skip_line(in); break; }
                 if (c == '*') { skip_cmt (in); break; }
                 fputc('/', out);
      /* intentional fall through */
      default  : fputc(c  , out);
    }
  }
}

static void
help(void)
{
  fprintf(stderr, "usage: coscmt [-h] [-l] [-o outfile] [infiles]\n");
  exit(EXIT_FAILURE);
}
 
int
main(int argc, char *argv[])
{
  FILE *in  = stdin;
  FILE *out = stdout;
  int i, o = 0;
 
  for (i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      if (argv[i][1] == 0)
         continue;

      if (argv[i][1] == 'l')
        { argv[i][0] = 0; rmlit = 1; continue; }

      if (argv[i][1] == 'o')
        { argv[i][0] = 0; o = ++i; continue; }
         
      help();
    }
  }

  if (o) {
    if (argv[o][0] == '-')
      out = stdout;
      
    else {
      out = fopen(argv[o],"w");
      if (!out) {
        fprintf(stderr, "coscmt: unable to open file %s in write mode\n", argv[o]);
        exit(EXIT_FAILURE);
      }
    }

    argv[o][0] = 0;
  }

  for (i = 1; i < argc; i++) {
    if (argv[i][0] == 0)
      continue;

    if (argv[i][0] == '-')
      in = stdin;

    else {
      in = fopen(argv[i],"r");
      if (!in) {
        fprintf(stderr, "coscmt: unable to open file %s in read mode\n", argv[i]);
        exit(EXIT_FAILURE);
      }
    }

    remove_cmt(in, out);

    if (in != stdin)
      fclose(in);
  }

  if (out != stdout)
    fclose(out);

  return EXIT_SUCCESS;
}
