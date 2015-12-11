%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "symbol_table.h"


  extern int yylineno;
  extern char * yytext;
  extern FILE* yyin;
  extern void yyerror(char const *);
  
  char *nom_fichier;
  Symbole *liste_complete = NULL, *liste, *id_courant, *symb_courant = NULL;
  int nb_attr = 0;
  FILE *fp1 = NULL, *fp2 = NULL;
%}

/* Les symboles terminaux */
%token <str> IDENT
%token <str> CONSTRUCTEUR
%token <str> TYPE 
%token <str> TYPE_ATOMIQUE OF AND EQ STAR OR END

%union {
	char* str;
	int num;
}

/* L'axiome, ou symbole de depart */ 
%start definitions


%% 

/* Section grammaire */

definitions: definition { ecrit_fichiers(nom_fichier, liste_complete, &liste); add_liste_complete(&liste_complete, liste); liste = NULL; } | definition { ecrit_fichiers(nom_fichier, liste_complete, &liste); add_liste_complete(&liste_complete, liste); liste = NULL; } definitions
definition: TYPE defs_mutuelles END
	| TYPE defs_mutuelles error {printf("Symbole de fin de definition manquant (;).\n");} | error {printf("Symbole de debut de definition manquant (TYPE).\n");} defs_mutuelles END | TYPE  error {printf("Definition incorrecte.\n");} END
defs_mutuelles: une_def autres_defs
autres_defs: | AND une_def autres_defs
	|  error {printf("Symbole manquant/incorrect (and).\n");} une_def autres_defs
une_def: def_simple | def_inductive
def_simple: IDENT EQ { nom_fichier = $1; id_courant = creer_symb(1, $1); } type_simple { symb_add_fin2(&liste, id_courant); }
	|  error {printf("Identifiant manquant/incorrect.\n");} EQ type_simple | IDENT  error {printf("Symbole d'egalite manquant/incorrect.\n");} type_simple
def_inductive: IDENT EQ { nom_fichier = $1; id_courant = creer_symb(1, $1); } type_inductif { symb_add_fin2(&liste, id_courant); }
	|  error {printf("Identifiant manquant/incorrect.\n");} EQ type_inductif | IDENT  error {printf("Symbole d'egalite manquant/incorret.\n");} type_inductif
type_simple: IDENT { add_attr(id_courant, 1, $1); } | TYPE_ATOMIQUE { add_attr(id_courant, 0, $1); }
	|  error {printf("Type simple manquant/incorrect, il faut que un identifiant ou un type atomique.\n");}
type_inductif: somme
	| error {printf("Type inductif manquant/incorrect.\n");}
somme: terme reste_somme
reste_somme: | OR terme reste_somme
	|  error {printf("Symbole d'inductivite manquant/incorrect (|).\n");} terme reste_somme
terme: constructeur arg_of_constr
arg_of_constr: | OF produit
	|  error {printf("Symbole de definition manquant/incorrect (of).\n");} produit
produit: facteur reste_produit
reste_produit: | STAR facteur reste_produit
	|  error {printf("Symbole de produit manquant/incorrect (*).\n");} facteur reste_produit
facteur: IDENT { add_attr(symb_courant, 1, $1); } | TYPE_ATOMIQUE { add_attr(symb_courant, 0, $1); }
	|  error {printf("Facteur d'un produit manquant/incorrect. Il faut un identifiant ou un type atomique.\n");}
constructeur: CONSTRUCTEUR { symb_courant = symb_add_fin(&liste, 0, $1); add_attr(id_courant, 0, $1); }
	|  error {printf("Constructeur manquant/incorrect.\n");}
%%

/* Le code additionnel */

void yyerror(char const *str)
{
	printf("Erreur, Ligne : %d\n",yylineno);
  //exit(EXIT_FAILURE);
}



int 
main(int argc, char* argv[])
{
  if ( argc > 1 ) {
    if((yyin = fopen( argv[1], "r" ))==NULL)
    {
		printf("Erreur d'ouverture du fichier.\n");
		exit(EXIT_FAILURE);
    }
    yyparse();
    aff_liste(liste_complete);
    fclose(yyin);
  }
  else 
  {
	printf("usage: %s fichier.tic\n", argv[0]);
	exit(EXIT_FAILURE);
  }

  exit(EXIT_SUCCESS);
}
