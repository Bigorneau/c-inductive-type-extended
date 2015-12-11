LEX=flex
LEXOPTS=
YACC=bison
YACCOPTS=-d # Pour generer le fichier grammaire.h

LEXFILES=lexeur.lex 
YACCFILES=grammaire.y
CFILES=table_symboles.c
BINARY=traducteur

OBJETS=$(LEXFILES:%.lex=%.o) $(YACCFILES:%.y=%.o) $(CFILES:%.c=%.o)

GENERATEDFILES=$(OBJETS) $(YACCFILES:%.y=%.c) $(YACCFILES:%.y=%.h) $(LEXFILES:%.lex=%.c) $(BINARY)

$(BINARY): grammaire.c lexeur.c $(OBJETS)
	$(CC) $(CCOPTS) $(OBJETS) -o $@

grammaire.c: grammaire.y
	$(YACC) $(YACCOPTS) -o $@  $<

lexeur.c: lexeur.lex
	$(LEX)$(LEXOPTS) -o $@  $<

clean:
	-rm -rfv $(GENERATEDFILES)
