#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>


#ifndef NULL
#define NULL (void *) 0
#endif

/*
	Algorithme Square and multiply
	\param int x : entier x 
	\param int n : modulo n
*/
void square_and_multiply(mpz_t R, mpz_t n, char * H){
	// Initialiser R
	mpz_t Ri;
	mpz_init(Ri);
	mpz_set(Ri, R);

	size_t lenH = strlen(H);						// La taille de H
	for (unsigned int i = 1; i < lenH; i++)	{		// Square and multiply
		mpz_mul(R, R, R);							// R = R*R
		mpz_mod(R, R, n);							// R = R mod n
		if(H[i] - '0'){
			mpz_mul(R, R, Ri);						// R = R * x 
			mpz_mod(R, R, n);						// R = R mod n
		}
	}
	mpz_clear(Ri);
}

void random_a(mpz_t a, mpz_t n, int seed, int min, int max){
	// Initialiser le générateur des nombres aléatoires.
	gmp_randstate_t state;
	gmp_randinit_default( state);

	// seed
	gmp_randseed_ui( state, (unsigned int)time(0) + seed);
	
	/* Pour générer un entier a tel que  min <  a  < max (N+max)
	 * Il faut génerer un nombre aléatoire entre [min, N-(min-max)]
	 * et ajouter min au résultat.
	*/
	mpz_sub_ui( n, n, min-max+1);
	//
	mpz_urandomm( a, state, n);
	mpz_add_ui( a, a, min+1);

	//
	mpz_add_ui( n, n, min-max+1);
	// Free memory
	gmp_randclear(state);
}

int fermat_test(mpz_t n, int k){
	int is_pseudo_premier = 0;
	// Initialisation des variables
	mpz_t a;
	mpz_t n_1;
	mpz_inits(a, n_1, (mpz_ptr)NULL);
	
	// Calculer N-1 = exposant
	mpz_sub_ui(n_1, n, 1);	
	// Convertir exposant (N-1) en binaire				
	char * H = mpz_get_str(NULL, 2, n_1);	

	for (int i = 0; i < k; i++)	{
		// Générer un entier a aléatoirement
		random_a(a, n, i, 1, -1);	
		// Calculer a = a^n-1 mod n			
		square_and_multiply(a, n, H);	
		// Verifier resultat de a
		// retourner 0 si a == 1		
		if( mpz_cmp_ui(a, 1) != 0) {
			// free memory			
			mpz_clears(a, n_1, (mpz_ptr)NULL);
			
			// Verifier s'il est pseudo premier
			if(is_pseudo_premier){
				gmp_printf("N = %Zd est pseudo-premier\n", n);
				return 2; // n est pseudo-premier
			}
			else {	
				gmp_printf("N = %Zd est composé\n", n);
				return 0; // n est composé.
			}
		}
		is_pseudo_premier = 1;
	}

	//free memory
	mpz_clears(a, n_1, (mpz_ptr)NULL);
	
	gmp_printf("N = %Zd est probablement premier\n", n);
	return 1; // n est probablement premier 
}

int miller_rabin_test ( mpz_t n, int k)	{
	mpz_t s, t, y, a, mod, _mod, j, s_1, y2;
	mpz_inits ( s, t, y, a, mod, _mod, j, s_1, y2, (mpz_ptr)NULL);
	
	int bool = 1;
	mpz_set_ui ( s, 0);
	mpz_sub_ui ( t, n, 1);
	
	do	{
		mpz_add_ui ( s, s, 1);
		mpz_div_ui ( t, t, 2);
		mpz_mod_ui ( mod, t, 2);
	}while ( !mpz_cmp_ui ( mod, 0));	
	
//	mpz_sub_ui ( s_1, s, 1);
	gmp_printf("n - 1 = 2^(%Zd) x %Zd\n", s, t);
	char * H = mpz_get_str(NULL, 2, t);
	for (int i = 1; i < (k+1); i++)	{
		printf ("Pour i = %d\n", i);
		random_a(a, n, i, 0, 0);
		gmp_printf ( "\tChoisir un nombre a = %Zd\n", a);
		mpz_set ( y, a);
		square_and_multiply ( y, n, H);

		mpz_add_ui ( _mod, y, 1);
		mpz_mod ( _mod, _mod, n);
		gmp_printf ( "\t y = %Zd mod %Zd / -1 mod n =  %Zd\n", y, n, _mod);
		if ( mpz_cmp_si ( y, 1) && mpz_cmp_ui (_mod, 0))	{
			mpz_set_ui ( j, 1);
			bool = 1;
			gmp_printf ( "\t Pour j = %Zd < %Zd\n", j, s);
			while ( (mpz_cmp ( j, s) < 1) && bool)	{
				//mpz_set ( y2, y);
				square_and_multiply ( y, n, "10\0");				
				gmp_printf ( "\t\t y2 = %Zd mod %Zd\n", y, n);
				
				mpz_add_ui ( _mod, y, 1);
				mpz_mod ( _mod, _mod, n);
				gmp_printf ( "\t\t -1 mod n ? = %Zd et y = %Zd\n", _mod, y);
				if ( !mpz_cmp_ui ( y, 1))	{
					mpz_clears ( s, t, y, a, mod, j, s_1, y2, (mpz_ptr)NULL);
					return 0;
				}
				if ( !mpz_cmp_ui ( _mod, 0)) bool = 0;
				mpz_add_ui ( j, j, 1); 
			} 
			if ( bool)	{
				mpz_clears ( s, t, y, a, mod, j, s_1, y2, (mpz_ptr)NULL);
				return 0;
			}
		}
	}
	mpz_clears ( s, t, y, a, mod, j, s_1, y2, (mpz_ptr)NULL);
	return 1;
}

void fermat ( int argc, char *argv[])	{
	//a^exp mod n
	// Initialisation des variables
	mpz_t n;
	//mpz_init_set_str(a, "15", 10);
	//mpz_init_set_str(exp, "532", 10);
	mpz_init_set_str(n, argv[1], 10);

	//random_a(n, a);
	// Conversion de l'exposant en binaire
	//char * H = mpz_get_str(NULL, 2, exp);

	// Square and multiply
	//square_and_multiply(a, n, H);

	// 
	//gmp_printf("%Zd\n", a);
	//if(fermat_test(n, atoi(argv[2])) == 1)
	//		printf("Oui premier\n");
	//else	printf("Non\n");
	// Free memory
	//free(H);
	//mpz_clear(a);
	mpz_clear(n);
	//mpz_clear(exp);	
}

void checkargs (int argc, int arg_n){
	if (argc != arg_n){
		fprintf(stdout, "Liste des commandes Test de primalité:\n\n"
						"-f [n] [k]: Tester si n est premier pour k fois en utilisant le test de Fermat.\n"
						"-m [n] [k]: Tester si n est premier pour k fois en utilisant le test de Miller-Rabin.\n"
						"-s [n] [exposant] [m]: Calculer (n^exp modulo m) en utilisant Square and multiply.\n"
						"-g [n]: generer un nombre aléatoire entre 0 et n-1\n");
		exit(1);
	}
}

int main(int argc, char const *argv[])	{	
	// Initialiser n
	mpz_t n;
	// Lire n
	mpz_init_set_str ( n, argv[2], 10);


	switch(argv[1][1]){
		case 'f': // Test de fermat 
			checkargs(argc, 4);
			
			fermat_test(n, atoi(argv[3]));

			break;
		case 'm': 
			checkargs(argc, 4);
			printf ("%s : %s\n", 
					argv[2], 
					miller_rabin_test ( n, atoi ( argv[3])) ? "Premier\0" : "Composé\0");
			break;
		case 's': 
			checkargs(argc, 5);
			// Initialiser n
			mpz_t exp, modulo;
			// Lire n
			mpz_init_set_str ( exp, argv[3], 10);
			mpz_init_set_str ( modulo, argv[4], 10);
			
			// Conversion de l'exposant en binaire
			char * H = mpz_get_str(NULL, 2, exp);	
			square_and_multiply(n, modulo,H);
			
			// Afficher resultat
			gmp_printf("Resultat : %Zd \n", n);
			// Free memory
			free(H);
			mpz_clears(exp, modulo, NULL);
			break;
		case 'g':
			checkargs(argc, 3);
			mpz_t a;
			mpz_init(a);
			random_a(a, n, 0, 0, 0);
			gmp_printf("Nombre aléatoire : %Zd \n", a);

			//Free memory
			mpz_clear(a);
			break;
		
		default : checkargs(argc, 6); break;

	}

	mpz_clear(n);
	return 0;
}
