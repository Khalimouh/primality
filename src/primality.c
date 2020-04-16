#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>
#include <time.h>

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

	// La taille de H
	size_t lenH = strlen(H);
	// Square and multiply
	for (unsigned int i = 1; i < lenH; i++)
	{	// R = R*R
		mpz_mul(R, R, R);
		// R = R mod n
		mpz_mod(R, R, n);
		//
		if(H[i] - 48){
			// R = R * x 
			mpz_mul(R, R, Ri);
			// R = R mod n
			mpz_mod(R, R, n);
		}
	}

	mpz_clear(Ri);
}

void random_a(mpz_t a, mpz_t n, int seed){
	// Initialiser
	gmp_randstate_t state;
	gmp_randinit_default(state);

	// seed
	gmp_randseed_ui(state, (unsigned int)time(0) + seed);
	/* Pour générer un entier a tel que  1 <  a  <= N-1
	 * Il faut génerer un nombre aléatoire entre [0, N-3]
	 * et ajouter 2 au résultat.
	*/
	mpz_sub_ui(n,n,3);
	//
	mpz_urandomm(a, state, n);
	mpz_add_ui(a,a,2);

	//
	mpz_add_ui(n,n,3);
	// Free memory
	gmp_randclear(state);
}

int fermat_test(mpz_t n, int k){
	// Initialisation des variables
	mpz_t a;
	mpz_t n_1;
	mpz_init(a);
	mpz_init(n_1);
	// Calculer N-1 = exposant
	mpz_sub_ui(n_1, n, 1);
	// Convertir exposant en binaire
	char * H = mpz_get_str(NULL, 2, n_1);

	for (int i = 0; i < k; i++)
	{	
		// Générer un entier a aléatoirement
		random_a(a, n, i);
		// Calculer a = a^n-1 mod n
		square_and_multiply(a, n, H);
		// Verifier resultat
		// retourner 0 si a == 1
		if( mpz_cmp_ui(a, 1) != 0) {
			return 0;
		} 
	}

	//free memory
	mpz_clear(a);
	mpz_clear(n_1);

	return 1;
}

int main(int argc, char const *argv[])
{	
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
	if(fermat_test(n, atoi(argv[2])))
			printf("Oui\n");
	else	printf("Non\n");
	// Free memory
	//free(H);
	//mpz_clear(a);
	mpz_clear(n);
	//mpz_clear(exp);
	return 0;
}