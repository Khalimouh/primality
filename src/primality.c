#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>


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

int	main()
{	
	//a^exp mod n
	// Initialisation des variables
	mpz_t a, n, exp;
	mpz_init_set_str(a, "4", 10);
	mpz_init_set_str(exp, "532", 10);
	mpz_init_set_str(n, "11", 10);

	// Conversion de l'exposant en binaire
	char * H = mpz_get_str(NULL, 2, exp);

	// Square and multiply
	square_and_multiply(a, n, H);

	// 
	gmp_printf("%Zd\n", a);


	// Free memory
	free(H);
	mpz_clear(a);
	mpz_clear(n);
	mpz_clear(exp);
	return 0;
}