#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <stdbool.h>

/* Include Files */
#include ".\inc\enum.h"  
#include ".\inc\vetores.h"
#include ".\inc\listas_encadeadas.h"
#include ".\inc\arvores_binarias.h"

#include ".\menu_defines.h"

void MainMenu();
void PrintWelcomeMsg();
void PrintGoodbyeMsg();

// Todo: jogar para utils
void Utils_Delay(int iSeconds);

int main() 
{
	PrintWelcomeMsg();
	
	MainMenu();
	
	PrintGoodbyeMsg();

	return 0;
}

void MainMenu()
{
	bool fSair = false;
	int iOpt;

	while(fSair == false)
	{
		system("cls");
		printf("==================================\n");
		printf("========= MENU PRINCIPAL =========\n");
		printf("==================================\n");

		printf("0 - Sair \n");

		scanf_s("%d", &iOpt);

		switch(iOpt)
		{
			case EXIT:
				fSair = true;
				break;

			default:
				break;
		}
	}
}

void PrintWelcomeMsg()
{
	printf("==================================\n");
	printf("======= PROJ UTILIDADES C ========\n");
	printf("========= SEJA BEM-VINDO =========\n");
	printf("==================================\n");
	Utils_Delay(2);
}

void PrintGoodbyeMsg()
{
	system("cls");
	printf("==================================\n");
	printf("============ ATE LOGO! ===========\n");
	printf("==================================\n");
	Utils_Delay(2);
}

//TODO COLOCAR EM UTILS_algo
void Utils_Delay(int iSeconds)
{
	int iMiliSeconds = 1000 * iSeconds;
	clock_t  lStartTime = clock();
	while (clock() < lStartTime + iMiliSeconds) {}
}