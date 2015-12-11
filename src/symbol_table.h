#ifndef H_TABLE_SYMBOLES
#define H_TABLE_SYMBOLES

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Attribut {
	int id; //1 = id, 0 = type atomique
	char *type;
	struct Attribut *suivant;
};

struct Symbole {
	int id; //1 = id, 0 = constructeur
	char *nom;
	struct Attribut *attr; //Attribut(s) du symbole
	struct Symbole *suivant;
};

typedef struct Attribut Attribut;
typedef struct Symbole Symbole;

Symbole *symb_add_debut(Symbole **liste, int ident, char *valeur);
Symbole *symb_add_fin(Symbole **liste, int ident, char *valeur);
void *symb_add_fin2(Symbole **liste, Symbole *symb);
void add_liste_complete(Symbole **lst, Symbole *liste);
void aff_liste(Symbole *lst);
void add_attr(Symbole *symb, int id, char *type);
int cons_existe(Symbole *liste, char *nom);
int is_id(Symbole *liste, Attribut *attr);
Symbole *creer_symb(int ident, char *valeur);
void symb_vider(Symbole **liste);
void symb_aff(FILE *fp, Symbole *liste);
void typedefs_aff(FILE *fp, Symbole *liste);
char *translate(char *val);
void make_c(FILE *fp, Symbole *liste);
FILE *creer_fichier_h(char *nom);
FILE *creer_fichier_c(char *nom);
void ecrit_fichier_h(FILE *fp, Symbole *liste);
void ecrit_fichier_c(FILE *fp, Symbole *liste);
void ecrit_fichiers(char *nom, Symbole *liste_complete, Symbole **liste);

#endif
