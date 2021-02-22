Exemplos e exercícios de programação paralela (threads) da disciplina de Sistemas de Alto Desempenho (Poli - 2020)

Aula 1 e 2: Paralelismo com C baixo nível
Aula 3 - 5: Paralelismo utilizando a linguagem cpar. 
	    Para utilizar a cpar basta copiar os arquivos em cpar-2020 para o diretorio que se deseja trabalhar e executar compilar-copar <nome_do_arquivo>
Aula 6 - 8: Paralelismo utilizando OpenMp.
	    Para compilar
            gcc -o <nome_do_arquivo> <nome_do_arquivo>.c -fopenmp
	    Funciona em windows instalando as bibliotecas pthreads no mingw
		
	    *obs: A biblioteca <sys\time.h> só funciona em linux. Alternativa: time.h (exemplo.bib.time.c no diretorio do projeto)
	    *obs2: O vsCode reclama da biblioteca #include <unistd.h> mas compila
	    *obs3: Para medir tempo com OpenMP não é necessário utilizar o time.h. A biblioteca OpenMp tem uma função que mede o tempo.
			double start_time, run_time;
			start_time = omp_get_wtime(); 
			run_time = omp_get_wtime() - start_time;
    			printf("Tempo total: %f s)\n", run_time); 
Aula 7 - 11: Paralelismo utilizando <mpi.h>