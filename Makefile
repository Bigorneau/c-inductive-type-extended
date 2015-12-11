LEX=flex
LEXOPTS=
YACC=bison
YACCOPTS=-d # Use to generated grammar.h

LEXFILES=lexeur.lex
YACCFILES=grammaire.y
CFILES=table_symboles.c
BINARY=traducteur

OBJECTS=$(LEXFILES:%.lex=%.o) $(YACCFILES:%.y=%.o) $(CFILES:%.c=%.o)

GENERATEDFILES=$(OBJECTS) $(YACCFILES:%.y=%.c) $(YACCFILES:%.y=%.h) $(LEXFILES:%.lex=%.c) $(BINARY)

$(BINARY): grammaire.c lexeur.c $(OBJECTS)
	-$(CC) $(CCOPTS) $(OBJECTS) -o $@

grammaire.c: grammaire.y
	-$(YACC) $(YACCOPTS) -o $@  $<

lexeur.c: lexeur.lex
	-$(LEX) $(LEXOPTS) -o $@  $<

clean:
	-rm -rf $(GENERATEDFILES)
