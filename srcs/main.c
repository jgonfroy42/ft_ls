#include "../include/ft_ls.h"

int main(int ac, char *av)
{

/*
 * 1. on verif les args :
 * - soit pas d'args
 * - arg qui commence par "-" => on verifie que les options sont valides
 *   -> si faux message d'erreur et on arrête tout
 * - autres args, on verifie que le chemin est valide
 *   -> message d'erreur pour les chemins faut puis on exécute la commande pour les autres
 *
 *  2. que fait-on des args ?
 *  liste chainée de path, si vide => on prend . par défaut
 *  struct avec bool des args possibles à false par defaut

*/
	parse_args();
}
