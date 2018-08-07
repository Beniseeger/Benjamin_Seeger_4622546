#include "stdafx.h"
#include "RandomBot.h"
#include "BuildGameField.h"
#define N     624
#define M     397

uint32_t mersenne_twister();
static void mersenne_twister_vector_init(uint32_t* const p, const int len);
static void mersenne_twister_vector_update(uint32_t* const p);

RandomBot::RandomBot(int playerid, int icon)
	: Player(playerid, icon)
{
}


RandomBot::~RandomBot()
{
}

int RandomBot::getPositionForColumn(BuildGameField *gamefield)
{
	//gibt random Zahl zurück (die irgendwie nicht random ist) 
	return mersenne_twister() % 7 + 1;
}

/*
* Initialisiere den Vektor mit Pseudozufallszahlen.
* Siehe Donald E. Knuth: The Art of Computer Programming, Band 2, 3. Ausgabe, S. 106 für geeignete Werte für den Faktor mult
*
* 2002/01/09 modifiziert von Makoto Matsumoto:
*   In der vorhergehenden Version die MSBs des Seeds haben auch nur die MSBs des Arrays beeinflusst.
*/

static void mersenne_twister_vector_init(uint32_t* const p, const int len)
{
	const uint32_t  mult = 1812433253ul;
	uint32_t        seed = 5489ul;
	int             i;

	for (i = 0; i < len; i++)
	{
		p[i] = seed;
		seed = mult * (seed ^ (seed >> 30)) + (i + 1);
	}

}

/*
* Berechne neuen Zustandsvektor aus altem Zustandsvektor
* Dies erfolgt periodisch alle N=624 Aufrufe von mersenne_twister().
* Der folgende Code stellt eine optimierte Version von
*   ...
*   for (i = 0; i < N; i++)
*     Proc3 (p[i], p[(i+1) % N], p[(i+M) % N]);
*   ...
* mit
*   void Proc3 (uint32_t &a0, uint32_t a1, uint32_t aM)
*   {
*     a0 = aM ^ (((a0 & 0x80000000) | (a1 & 0x7FFFFFFF)) >> 1) ^ A[a1 & 1];
*   }
* dar, in der die (zeitintensiven) Modulo N-Operationen vermieden werden.
*/



static void mersenne_twister_vector_update(uint32_t* const p)
{
	static const uint32_t  A[2] = { 0, 0x9908B0DF };
	int                    i = 0;
	for (; i < N - M; i++)
		p[i] = p[i + (M)] ^ (((p[i] & 0x80000000) | (p[i + 1] & 0x7FFFFFFF)) >> 1) ^ A[p[i + 1] & 1];

	for (; i < N - 1; i++)
		p[i] = p[i + (M - N)] ^ (((p[i] & 0x80000000) | (p[i + 1] & 0x7FFFFFFF)) >> 1) ^ A[p[i + 1] & 1];

	p[N - 1] = p[M - 1] ^ (((p[N - 1] & 0x80000000) | (p[0] & 0x7FFFFFFF)) >> 1) ^ A[p[0] & 1];

}



/*
* Die eigentliche Funktion:
* - beim 1. Aufruf wird der Vektor mittels mersenne_twister_vector_init() initialisiert.
* - beim 1., 625., 1249., ... Aufruf wird ein neuer Vektor mittels mersenne_twister_vector_update berechnet.
* - bei jedem Aufruf wird eine Zufallszahl aus dem Vektor bestimmt, der noch einem Tempering unterzogen wird.
*/

uint32_t mersenne_twister()
{
	static uint32_t  vektor[N];  /* Zustandsvektor */
	static int       idx = N + 1;   /* Auslese-Index; idx>N: neuer Vektor muß berechnet werden, idx=N+1: Vektor muß überhaupt erst mal initialisiert werden */
	uint32_t         e;

	if (idx >= N)
	{
		if (idx > N)
			mersenne_twister_vector_init(vektor, N);

		mersenne_twister_vector_update(vektor);
		idx = 0;
	}

	e = vektor[idx++];
	e ^= (e >> 11);             /* Tempering */
	e ^= (e << 7) & 0x9D2C5680;
	e ^= (e << 15) & 0xEFC60000;
	e ^= (e >> 18);

	return e;
}
