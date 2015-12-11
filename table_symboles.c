#include "table_symboles.h"


Symbole *symb_add_debut(Symbole **liste, int ident, char *valeur) //Ajout en début de liste
{
	Symbole *item, *tmp;
	item = (Symbole*)malloc(sizeof(Symbole));
	item->id = ident;
	item->nom = valeur;
	item->attr = NULL;
	item->suivant = *liste;
	*liste = item;
	return item;
}

Symbole *symb_add_fin(Symbole **liste, int ident, char *valeur) //Ajout en fin de liste
{
	Symbole *item, *tmp;
	item = (Symbole*)malloc(sizeof(Symbole));
	item->id = ident;
	item->nom = valeur;
	item->attr = NULL;
	item->suivant = NULL;
	if(*liste == NULL)
	{
		*liste = item;
	}
	else
	{
		tmp = *liste;
		while(tmp->suivant != NULL)
		{
			tmp = tmp->suivant;
		}
		tmp->suivant = item;
	}
	return item;
}


void *symb_add_fin2(Symbole **liste, Symbole *symb) //Ajout en fin de liste
{
	Symbole *tmp;
	if(*liste == NULL)
	{
		*liste = symb;
	}
	else
	{
		tmp = *liste;
		while(tmp->suivant != NULL)
		{
			tmp = tmp->suivant;
		}
		tmp->suivant = symb;
	}
}


void suppr_symb(Symbole **liste, char *nom) //Supprime le dernier symbole du nom passé en argument
{
	Symbole *tmp;
	Symbole *precedent;
	if(!strcmp((*liste)->nom, nom))
	{
		*liste = (*liste)->suivant;
	}
	else
	{
		tmp = *liste;
		while(tmp != NULL)
		{
			if(!strcmp(tmp->nom, nom)) //Si c'est le symbole recherché
			{
				precedent->suivant = tmp->suivant;
			}
			precedent = tmp;
			tmp = tmp->suivant;
		}
	}
}


void add_liste_complete(Symbole **lst, Symbole *liste) //Liste de tous les symboles
{
	Symbole *tmp = liste;
	Symbole *new, *tmp_lst;
	while(tmp != NULL)
	{
		new = (Symbole*)malloc(sizeof(Symbole));
		new->id = tmp->id;
		new->nom = tmp->nom;
		new->attr = tmp->attr;
		new->suivant = NULL;
		if(*lst == NULL)
		{
			*lst = new;
		}
		else
		{
			tmp_lst = *lst;
			while(tmp_lst->suivant != NULL)
			{
				tmp_lst = tmp_lst->suivant;
			}
			tmp_lst->suivant = new;
		}
		tmp = tmp->suivant;
	}
}


void aff_liste(Symbole *lst)
{
	Symbole *tmp = lst;
	printf("Liste: \n");
	while(tmp != NULL)
	{
		printf("%d ", tmp->id);
		if(!tmp->id)
		{
			printf("Constructeur %s\n", tmp->nom);
		} 
		else printf("Identifiant %s\n", tmp->nom);
		tmp = tmp->suivant;
	}
}

void add_attr(Symbole *symb, int id, char *type) //Ajout en fin de liste
{
	if(symb != NULL)
	{
		Attribut *attr, *tmp;
		attr = (Attribut*)malloc(sizeof(Attribut));
		attr->id = id;
		attr->type = type;
		attr->suivant = NULL;
		if(symb->attr == NULL)
		{
			symb->attr = attr;
		}
		else
		{
			tmp = symb->attr;
			while(tmp->suivant != NULL)
			{
				tmp = tmp->suivant;
			}
			tmp->suivant = attr;
		}
	}
}


Symbole *creer_symb(int ident, char *valeur)
{
	Symbole *item;
	item = (Symbole*)malloc(sizeof(Symbole));
	item->id = ident;
	item->nom = valeur;
	item->attr = NULL;
	item->suivant = NULL;
	return item;
}


void symb_vider(Symbole **liste)
{
	*liste = NULL;
}


void symb_aff(FILE *fp, Symbole *liste) //Affiche les symboles
{
	Attribut *attr;
	Symbole *tmp_liste = liste;
	int champ_no;
	while(tmp_liste != NULL)
	{
		champ_no = 1;
		if(tmp_liste->id) //Si identifiant
		{
			fprintf(fp, "/** Type %s **/\n", tmp_liste->nom);
			fprintf(fp, "union %s {\n", tmp_liste->nom);
		}
		else //Si constructeur
		{
			fprintf(fp, "/* Constructeur %s */\n", tmp_liste->nom);
			fprintf(fp, "struct %s {\n", tmp_liste->nom);
		}
		attr = tmp_liste->attr;
		while(attr != NULL)
		{
			if(is_id(liste, attr) == 1) //Si l'attribut correspond à un id
			{ 
				fprintf(fp, "\tunion %s *champ_%d;\n", translate(attr->type), champ_no);
			}
			else if(is_id(liste, attr) == 2) //Si l'attribut correspond à un cons
			{
				fprintf(fp, "\tstruct %s *champ_%d;\n", translate(attr->type), champ_no);
			}
			else
			{
				fprintf(fp, "\t%s champ_%d;\n", translate(attr->type), champ_no);
			}
			champ_no++;
			attr = attr->suivant;
		}
		fprintf(fp, "};\n");
		tmp_liste = tmp_liste->suivant;
	}
}


int existe(Symbole *liste, char *nom) //Retourne vrai si le type ou constructeur existe deja
{
	int res = 0;
	Symbole *tmp = liste;
	while(tmp != NULL)
	{
		if(tmp->id == 0 && !strcmp(tmp->nom, nom))
		{
			printf("Le constructeur %s existe deja!\n", tmp->nom);
			return 1;
		} 
		else if(tmp->id == 1 && !strcmp(tmp->nom, nom))
		{
			printf("L'identifiant %s existe deja!\n", tmp->nom);
			return 1;
		} 
		tmp = tmp->suivant;
	}
	return res;
}


int is_id(Symbole *liste, Attribut *attr) //Renvoi si l'attribut correpond à un id, un cons ou autre
{
	int res = 0;
	Symbole *tmp = liste;
	while(tmp != NULL)
	{
		if(tmp->id && !strcmp(tmp->nom, attr->type)) //Si ID
		{
			return 1;
		}
		else if(!tmp->id && !strcmp(tmp->nom, attr->type)) //Si CONS
		{
			return 2;
		}
		tmp = tmp->suivant;
	}
	return res;
}

void typedefs_aff(FILE *fp, Symbole *liste) //Affiche les typedefs
{
	fprintf(fp, "/* Typedefs */\n");
	while(liste != NULL)
	{
		if(liste->id) //Si identifiant
		{
			fprintf(fp, "typedef union %s %s;\n", liste->nom, liste->nom);
		}
		else //Si constructeur
		{
			fprintf(fp, "typedef struct %s %s;\n", liste->nom, liste->nom);
		}
		liste = liste->suivant;
	}
}


char *translate(char *val) //Modifie le type passé en argument en un type compatible C
{
	char *s;
	s = val;
	if(!strcmp(val, "string"))
	{
		strcpy(s, "char *");
	}
	else if(!strcmp(val, "bool"))
	{
		strcpy(s, "int");
	}
	return s;
}



void make_c(FILE *fp, Symbole *liste) //Fichier .c
{
	Symbole *tmp_lst = liste;
	Attribut *tmp;
	int no_attr;
	while(tmp_lst != NULL)
	{
		if(!tmp_lst->id) //Si constructeur
		{
			fprintf(fp, "/* Constructeur %s */\n", tmp_lst->nom);
			fprintf(fp, "%s *make_%s(", tmp_lst->nom, tmp_lst->nom);
			tmp = tmp_lst->attr;
			no_attr = 1;
			while(tmp != NULL)
			{
				if(tmp->suivant != NULL) //Si ce n'est pas le dernier element
				{
					if(is_id(liste, tmp) == 1)
					{
						fprintf(fp, "%s *arg_%d, ", tmp->type, no_attr);
					}
					else
					{
						fprintf(fp, "%s arg_%d, ", tmp->type, no_attr);
					}
				}
				else
				{
					if(is_id(liste, tmp) == 1)
					{
						fprintf(fp, "%s *arg_%d)", tmp->type, no_attr);
					}
					else
					{
						fprintf(fp, "%s arg_%d)", tmp->type, no_attr);
					}
				}
				no_attr++;
				tmp = tmp->suivant;
			}
			fprintf(fp, "\n{\n\t%s *new = malloc(sizeof(%s));\n", tmp_lst->nom, tmp_lst->nom);
			fprintf(fp, "\tif(new == NULL) return NULL;\n");
			tmp = tmp_lst->attr;
			no_attr = 1;
			while(tmp != NULL)
			{
				fprintf(fp, "\tnew->champ_%d = arg_%d;\n", no_attr, no_attr);
				no_attr++;
				tmp = tmp->suivant;
			}
			fprintf(fp, "\treturn new;\n}\n");
			
		}
		else //Il s'agit d'un id
		{
			fprintf(fp, "/* Type %s */\n", tmp_lst->nom);
			tmp = tmp_lst->attr;
			no_attr = 1;
			while(tmp != NULL)
			{
				fprintf(fp, "%s *make_%s_of_%s(%s *arg)\n", tmp_lst->nom, tmp_lst->nom, tmp->type, tmp->type);
				fprintf(fp, "{\n\t%s *new = malloc(sizeof(%s));\n", tmp_lst->nom, tmp_lst->nom);
				fprintf(fp, "\tif(new == NULL) return NULL;\n");
				fprintf(fp, "\tnew->champ_%d = arg;\n", no_attr);
				fprintf(fp, "\treturn new;\n}\n");
				no_attr++;
				tmp = tmp->suivant;
			}
		}
		tmp_lst = tmp_lst->suivant;
	}
}




FILE *creer_fichier_h(char *nom)
{
	FILE *fp;
	char *tmp_nom_fichier;
	tmp_nom_fichier = (char*)malloc(sizeof(char)*strlen(nom));
	strcpy(tmp_nom_fichier, nom);
	fp = fopen(strcat(tmp_nom_fichier, ".h"), "w");
	return fp;
}


FILE *creer_fichier_c(char *nom)
{
	FILE *fp;
	char *tmp_nom_fichier;
	tmp_nom_fichier = (char*)malloc(sizeof(char)*strlen(nom));
	strcpy(tmp_nom_fichier, nom);
	fp = fopen(strcat(tmp_nom_fichier, ".c"), "w");
	return fp;
}


void ecrit_fichier_h(FILE *fp, Symbole *liste)
{
	symb_aff(fp, liste);
	typedefs_aff(fp, liste);
}


void ecrit_fichier_c(FILE *fp, Symbole *liste)
{
	make_c(fp, liste);
}



Symbole *find_type_from_Constructeur(Symbole *liste, char *nom) //Retrouve le type selon un constructeur donné
{
	Symbole *tmp = liste;
	Attribut *attr;
	Symbole *retour = NULL;
	while(tmp != NULL)
	{
		attr = tmp->attr;
		while(attr != NULL)
		{
			if(!strcmp(attr->type, nom)) //Si c'est le symbole recherché
			{
				retour = tmp;
			}
			attr = attr->suivant;
		}
		tmp = tmp->suivant;
	}
	return retour;
}

void ecrit_fichiers(char *nom, Symbole *liste_complete, Symbole **liste)
{
	Symbole *tmp = *liste;
	Symbole *type;
	Attribut *attr, *tmp_attr;
	FILE *fp1, *fp2;
	int error = 0;
	while(tmp != NULL)
	{
		if(existe(liste_complete, tmp->nom)) //Si le symbole existe déjà
		{
			if(tmp->id) //Si id
			{
				suppr_symb(liste, tmp->nom); //Supprime le type
				type = tmp;
				if(type != NULL)
				{
					attr = type->attr;
					while(attr != NULL)
					{
						suppr_symb(liste, attr->type); //Et ses attributs
						attr = attr->suivant;
					}
				}

			}
			else //Si constructeur
			{
				type = find_type_from_Constructeur(*liste, tmp->nom);
				if(type != NULL)
				{
					suppr_symb(liste, type->nom); //Supprime le type
					attr = type->attr;
					while(attr != NULL)
					{
						suppr_symb(liste, attr->type); //Et ses attributs
						attr = attr->suivant;
					}
				}
			}
			error = 1;
		}
		else //Si le symbole n'existe pas encore
		{
			attr = tmp->attr;
			while(attr != NULL)
			{
				if(attr->id && !type_existe(liste_complete, attr->type) && !type_existe(*liste, attr->type)) //Si l'attribut est un identifiant et qu'il n'a pas été déclaré
				{
					printf("Le type %s n'a pas été déclaré.\n", attr->type);
					type = find_type_from_Constructeur(*liste, tmp->nom);
					if(type != NULL)
					{
						suppr_symb(liste, type->nom); //Supprime le type
						tmp_attr = type->attr;
						while(tmp_attr != NULL)
						{
							suppr_symb(liste, tmp_attr->type); //Et ses attributs
							tmp_attr = tmp_attr->suivant;
						}
					}
					error = 1;
				}
				attr = attr->suivant;
			}
		}
		tmp = tmp->suivant;
	}
	if(!error) //Si aucune erreur rencontrée
	{
		fp1 = creer_fichier_h(nom);
		fp2 = creer_fichier_c(nom);
		ecrit_fichier_h(fp1, *liste);
		ecrit_fichier_c(fp2, *liste);
	}
}



int type_existe(Symbole *liste, char *nom) //Renvoi 1 si le type a été défini
{
	Symbole *tmp = liste;
	Attribut *attr;
	int existe = 0;
	while(tmp != NULL)
	{
		if(!strcmp(tmp->nom, nom))
		{
			existe = 1;
		}
		tmp = tmp->suivant;
	}
	return existe;
}


