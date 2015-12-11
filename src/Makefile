LEX=flex
LEXOPTS=
YACC=bison
YACCOPTS=-d # Use to generated grammar.h

LEXFILES=lexer.lex
YACCFILES=grammar.y
CFILES=symbol_table.c
BINARY=translator

OBJECTS=$(LEXFILES:%.lex=%.o) $(YACCFILES:%.y=%.o) $(CFILES:%.c=%.o)

GENERATEDFILES=$(OBJECTS) $(YACCFILES:%.y=%.c) $(YACCFILES:%.y=%.h) $(LEXFILES:%.lex=%.c) $(BINARY)

$(BINARY): grammar.c lexer.c $(OBJECTS)
	-$(CC) $(CCOPTS) $(OBJECTS) -o $@

grammar.c: grammar.y
	-$(YACC) $(YACCOPTS) -o $@  $<

lexer.c: lexer.lex
	-$(LEX) $(LEXOPTS) -o $@  $<

clean:
	-rm -rf $(GENERATEDFILES)
