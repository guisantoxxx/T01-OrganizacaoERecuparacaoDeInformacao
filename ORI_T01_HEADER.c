	/* ==========================================================================
	* Universidade Federal de São Carlos - Campus Sorocaba
	* Disciplina: Organização de Recuperação da Informação
	* Prof. Tiago A. Almeida
	*
	* Trabalho 01 - Indexação
	*
	* ========================================================================== *
	*   <<< IMPLEMENTE AQUI!!! COPIE E COLE O CONTEÚDO DESTE ARQUIVO NO AVA >>>
	* ========================================================================== */

	/* Bibliotecas */
	#include "ORI_T01_HEADER.h"

	/* ===========================================================================
	* ================================= FUNÇÕES ================================= */


	/* <<< COLOQUE AQUI OS DEMAIS PROTÓTIPOS DE FUNÇÕES, SE NECESSÁRIO >>> */


	/* Funções auxiliares para o qsort.
	* Com uma pequena alteração, é possível utilizá-las no bsearch, assim, evitando código duplicado.
	* */



	/* Função de comparação entre chaves do índice corredores_idx */
	int qsort_corredores_idx(const void *a, const void *b) {
		return strcmp( ( (corredores_index *)a )->id_corredor, ( (corredores_index *)b )->id_corredor);
	}

	/* Função de comparação entre chaves do índice veiculos_idx */
	int qsort_veiculos_idx(const void *a, const void *b) {
		return strcmp( ( (veiculos_index *)a)->id_veiculo, ( (veiculos_index *)b)->id_veiculo);
	}

	/* Função de comparação entre chaves do índice pistas_idx */
	int qsort_pistas_idx(const void *a, const void *b) {
		return strcmp( ( (pistas_index *)a)->id_pista, ( (pistas_index *)b)->id_pista);
	}

	/* Função de comparação entre chaves do índice corridas_idx */
	int qsort_corridas_idx(const void *a, const void *b) {
		return strcmp( ( (corridas_index *)a)->id_pista, ( (corridas_index *)b)->id_pista);
	}

	/* Funções de comparação apenas entre data de ocorrencia do índice corridas_idx */
	int qsort_data_idx(const void *a, const void *b){
		return strcmp( ( (corridas_index *)a)->ocorrencia, ( (corridas_index *)b)->ocorrencia);
	}

	/* Função de comparação entre chaves do índice nome_pista_idx */
	int qsort_nome_pista_idx(const void *a, const void *b){
		return strcmp( ( (nome_pista_index *)a)->nome, ( (nome_pista_index *)b)->nome);
	}

	/* Função de comparação entre chaves do índice preco_veiculo_idx */
	int qsort_preco_veiculo_idx(const void *a, const void *b){
		return ( ( (preco_veiculo_index *)a)->preco > ( (preco_veiculo_index *)b)->preco);
	}

	/* Função de comparação entre chaves do índice secundário de corredor_veiculos_secundario_idx */
	int qsort_corredor_veiculos_secundario_idx(const void *a, const void *b){
		return strcmp( ( (corredor_veiculos_secundario_index *)a)->chave_secundaria, ( (corredor_veiculos_secundario_index *)b)->chave_secundaria);
	}

	/* Cria o índice respectivo */
	void criar_corredores_idx() {
		if (!corredores_idx)
			corredores_idx = malloc(MAX_REGISTROS * sizeof(corredores_index));
	
		if (!corredores_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}
	
		for (unsigned i = 0; i < qtd_registros_corredores; ++i) {
			Corredor c = recuperar_registro_corredor(i);

			if (strncmp(c.id_corredor, "*|", 2) == 0)
				corredores_idx[i].rrn = -1; // registro excluído
			else
				corredores_idx[i].rrn = i;
	
			strcpy(corredores_idx[i].id_corredor, c.id_corredor);
		}
	
		qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);
		printf(INDICE_CRIADO, "corredores_idx");
	}

	void criar_veiculos_idx() {
		if(!veiculos_idx)
			veiculos_idx = malloc(MAX_REGISTROS * sizeof(veiculos_index));

		if(!veiculos_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}

		for(unsigned i = 0; i < qtd_registros_veiculos; i++) {
			Veiculo v = recuperar_registro_veiculo(i);

			if(strncmp(v.id_veiculo, "*|", 2) == 0) //se o id comeca com *|, significa que foi excluido, logo o rrn é marcado como -1
				veiculos_idx[i].rrn = -1;
			else 
				veiculos_idx[i].rrn = i;
			
			strcpy(veiculos_idx[i].id_veiculo, v.id_veiculo);
		}

		qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
		printf(INDICE_CRIADO, "veiculos_idx");

	}

	void criar_pistas_idx() {

		if(!pistas_idx)
			pistas_idx = malloc(MAX_REGISTROS * sizeof(pistas_index));

		if(!pistas_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}

		for(unsigned i = 0; i < qtd_registros_pistas; i++) {
			Pista p = recuperar_registro_pista(i);

			pistas_idx[i].rrn = i;
			strcpy(pistas_idx[i].id_pista, p.id_pista);
		}

		qsort(pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx);
		printf(INDICE_CRIADO, "pistas_idx");
	}

	void criar_corridas_idx() {
	if(!corridas_idx)
			corridas_idx = malloc(MAX_REGISTROS * sizeof(corridas_index));

		if(!corridas_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}



		for(unsigned i = 0; i < qtd_registros_corridas; i++) {
			Corrida c = recuperar_registro_corrida(i);

			strcpy(corridas_idx[i].id_pista, c.id_pista);
			strcpy(corridas_idx[i].ocorrencia, c.ocorrencia);
			corridas_idx[i].rrn = i;
		}

		qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_corridas_idx);
		printf(INDICE_CRIADO, "corridas_idx");
	}

	void criar_nome_pista_idx() {
		if(!nome_pista_idx)
			nome_pista_idx = malloc(MAX_REGISTROS * sizeof(nome_pista_idx));

		if(!nome_pista_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}

		for(unsigned i = 0; i < qtd_registros_pistas; i++) {
			Pista p = recuperar_registro_pista(i);

			strcpy(nome_pista_idx[i].nome, p.nome);
			strcpy(nome_pista_idx[i].id_pista,p.id_pista);

		}

		qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);
		printf(INDICE_CRIADO, "nome_pista_idx");
		
	}

	void criar_preco_veiculo_idx() {
		if(!preco_veiculo_idx)
			preco_veiculo_idx = malloc(MAX_REGISTROS * sizeof(preco_veiculo_index));

		if(!preco_veiculo_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}

		for(unsigned i = 0; i < qtd_registros_veiculos; i++) {
			Veiculo v = recuperar_registro_veiculo(i);

			preco_veiculo_idx[i].preco = v.preco;
			strcpy(preco_veiculo_idx[i].id_veiculo, v.id_veiculo);
		}

		qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);
		printf(INDICE_CRIADO, "preco_veiculo_idx");
	}

	void criar_corredor_veiculos_idx() {

		if(!corredor_veiculos_idx.corredor_veiculos_primario_idx)
			corredor_veiculos_idx.corredor_veiculos_primario_idx = malloc(MAX_REGISTROS  * sizeof(corredor_veiculos_primario_index));

		if(!corredor_veiculos_idx.corredor_veiculos_secundario_idx)
			corredor_veiculos_idx.corredor_veiculos_secundario_idx = malloc(MAX_REGISTROS * sizeof(corredor_veiculos_secundario_index));

		if(!corredor_veiculos_idx.corredor_veiculos_primario_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}

		if(!corredor_veiculos_idx.corredor_veiculos_secundario_idx) {
			printf(ERRO_MEMORIA_INSUFICIENTE);
			exit(1);
		}	

		//o laço verifica todos os corredores
		for(int j = 0; j < qtd_registros_corredores; j++) {
			Corredor c = recuperar_registro_corredor(j);		

			//por fim, o terceiro laço verifica os veiculos dos corredores, a fim de encontrar o veiculo do laço externo
			//assim que encontrado, a busca por esse veiculo é cessada, partindo para a proxima
			for(int k = 0; k < 3; k++) {
				if(c.veiculos[k][0] != '\0') {
					inverted_list_insert(c.veiculos[k], c.id_corredor, &corredor_veiculos_idx);
				}
			}
		}

		printf(INDICE_CRIADO, "corredor_veiculos_idx");
	}

	/* Exibe um registro com base no RRN */
	bool exibir_corredor(int rrn) {
		if (rrn < 0)
			return false;
	
		Corredor c = recuperar_registro_corredor(rrn);
	
		printf("%s, %s, %s, %s, %.2lf\n", c.id_corredor, c.nome, c.apelido, c.cadastro, c.saldo);
		return true;
	}

	bool exibir_veiculo(int rrn) {
		if(rrn < 0)
			return false;
		
		Veiculo v = recuperar_registro_veiculo(rrn);

		printf("%s, %s, %s, %s, %d, %d, %d, %.2lf\n", v.id_veiculo, v.marca, v.modelo, v.poder, v.velocidade,v.aceleracao, v.peso, v.preco);
		return true;
	}

	bool exibir_pista(int rrn) {
		if(rrn < 0)
			return false;

		Pista p = recuperar_registro_pista(rrn);

		printf("%s, %s, %d, %d, %d\n", p.id_pista, p.nome, p.dificuldade, p.distancia,p.recorde);
		return true;
	}

	bool exibir_corrida(int rrn) {
		if(rrn < 0) 
			return false;
		
		Corrida i = recuperar_registro_corrida(rrn);

		printf("%s, %s, %s, %s\n", i.id_pista,i.ocorrencia, i.id_corredores, i.id_veiculos);

		return true;
	}

	/* Recupera do arquivo o registro com o RRN informado
	* e retorna os dados nas structs corredor, Curso e Inscricao */
	Corredor recuperar_registro_corredor(int rrn) {
		Corredor c;
		char temp[TAM_REGISTRO_CORREDOR + 1], *p;
		strncpy(temp, ARQUIVO_CORREDORES + (rrn *  TAM_REGISTRO_CORREDOR) , TAM_REGISTRO_CORREDOR);
		temp[TAM_REGISTRO_CORREDOR] = '\0';

		p = strtok(temp, ";");
		strcpy(c.id_corredor, p);
		p = strtok(NULL, ";");
		strcpy(c.nome, p);
		p = strtok(NULL, ";");
		strcpy(c.apelido, p);
		p = strtok(NULL, ";");
		strcpy(c.cadastro, p);
		p = strtok(NULL, ";");
		c.saldo = atof(p);
		p = strtok(NULL, ";");

		for(int i = 0; i < QTD_MAX_VEICULO; ++i)
			c.veiculos[i][0] = '\0';

		if(p[0] != '#') {
			p = strtok(p, "|");

			for(int pos = 0; p; p = strtok(NULL, "|"), ++pos)
				strcpy(c.veiculos[pos], p);
		}

		return c;
	}

	Veiculo recuperar_registro_veiculo(int rrn) {
		Veiculo v;
		
		char temp[TAM_REGISTRO_VEICULO + 1], *p;
		strncpy(temp, ARQUIVO_VEICULOS + (rrn * TAM_REGISTRO_VEICULO), TAM_REGISTRO_VEICULO);
		temp[TAM_REGISTRO_VEICULO] = '\0';

		p = strtok(temp, ";");
		strcpy(v.id_veiculo, p);
		p = strtok(NULL, ";");
		strcpy(v.marca, p);
		p = strtok(NULL, ";");
		strcpy(v.modelo, p);
		p = strtok(NULL, ";");
		strcpy(v.poder, p);
		p = strtok(NULL, ";");
		v.velocidade = atoi(p);
		p = strtok(NULL, ";");
		v.aceleracao = atoi(p);
		p = strtok(NULL, ";");
		v.peso = atoi(p);
		p = strtok(NULL, ";");
		v.preco = atof(p);
		p = strtok(NULL, ";");
		
		return v;
	}

	Pista recuperar_registro_pista(int rrn) {
		Pista p;
		
		char temp[TAM_REGISTRO_PISTA + 1], *t;
		strncpy(temp, ARQUIVO_PISTAS + (rrn * TAM_REGISTRO_PISTA), TAM_REGISTRO_PISTA);
		temp[TAM_REGISTRO_PISTA] = '\0';

		t = strtok(temp, ";");
		strcpy(p.id_pista, t);
		t = strtok(NULL, ";");
		strcpy(p.nome, t);
		t = strtok(NULL, ";");
		p.dificuldade = atoi(t);
		t = strtok(NULL, ";");
		p.distancia = atoi(t);
		t = strtok(NULL, ";");
		p.recorde = atoi(t);
		t = strtok(NULL, ";");

		return p;
	}

	Corrida recuperar_registro_corrida(int rrn) {
		Corrida c;

		char temp[TAM_REGISTRO_CORRIDA + 1];
		strncpy(temp, ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), TAM_REGISTRO_CORRIDA);
		temp[TAM_REGISTRO_CORRIDA] = '\0';

		strncpy(c.id_pista, &temp[0], 8);

		c.id_pista[8] = '\0';

		strncpy(c.ocorrencia, &temp[8], 12);

		c.ocorrencia[12] = '\0';

		strncpy(c.id_corredores, &temp[20], 66);

		c.id_corredores[66] = '\0';

		strncpy(c.id_veiculos, &temp[86], 42);

		c.id_veiculos[42] = '\0';

		return c;
	}

	/* Escreve em seu respectivo arquivo na posição informada (RRN) */
	void escrever_registro_corredor(Corredor c, int rrn) {
		char temp[TAM_REGISTRO_CORREDOR + 1], p[100];
		temp[0] = '\0'; p[0] = '\0';

		strcpy(temp, c.id_corredor);
		strcat(temp, ";");
		strcat(temp, c.nome);
		strcat(temp, ";");
		strcat(temp, c.apelido);
		strcat(temp, ";");
		strcat(temp, c.cadastro);
		strcat(temp, ";");
		sprintf(p, "%013.2lf", c.saldo);
		strcat(temp, p);
		strcat(temp, ";");

		for(int i = 0, k = 0; i < QTD_MAX_VEICULO; ++i) {
			if(strlen(c.veiculos[i]) > 0) {
				if (k == 0)
					k = 1;
				else
					strcat(temp, "|");
				strcat(temp, c.veiculos[i]);
			}
		}
		strcat(temp, ";");

		strpadright(temp, '#', TAM_REGISTRO_CORREDOR);

		strncpy(ARQUIVO_CORREDORES + (rrn * TAM_REGISTRO_CORREDOR) , temp, TAM_REGISTRO_CORREDOR);
	}

	void escrever_registro_veiculo(Veiculo v, int rrn) {
		char temp[TAM_REGISTRO_VEICULO + 1], p[100];
		temp[0] = '\0'; p[0] = '\0';

		sprintf(p, "%07d", qtd_registros_veiculos);
		strcpy(temp, p);
		strcat(temp, ";");
		strcat(temp, v.marca);
		strcat(temp, ";");
		strcat(temp, v.modelo);
		strcat(temp, ";");
		strcat(temp, v.poder);
		strcat(temp, ";");
		sprintf(p, "%04d", v.velocidade);
		strcat(temp, p);
		strcat(temp, ";");
		sprintf(p, "%04d", v.aceleracao);
		strcat(temp, p);
		strcat(temp, ";");
		sprintf(p, "%04d", v.peso);
		strcat(temp, p);
		strcat(temp, ";");
		sprintf(p, "%013.2lf", v.preco);
		strcat(temp, p);
		strcat(temp, ";");

		strpadright(temp, '#', TAM_REGISTRO_VEICULO);
		
		strncpy(ARQUIVO_VEICULOS + (rrn * TAM_REGISTRO_VEICULO), temp, TAM_REGISTRO_VEICULO);
	}

	void escrever_registro_pista(Pista p, int rrn) {
		char temp[TAM_REGISTRO_PISTA + 1], t[100];
		temp[0] = '\0'; t[0] = '\0';

		strcpy(temp, p.id_pista);
		strcat(temp, ";");
		strcat(temp, p.nome);
		strcat(temp,";");
		sprintf(t, "%04d", p.dificuldade);
		strcat(temp, t);
		strcat(temp, ";");
		sprintf(t, "%04d", p.distancia);
		strcat(temp, t);
		strcat(temp, ";");
		sprintf(t, "%04d", p.recorde);
		strcat(temp, t);
		strcat(temp, ";");

		strpadright(temp, '#', TAM_REGISTRO_PISTA);

		strncpy(ARQUIVO_PISTAS + (rrn * TAM_REGISTRO_PISTA), temp, TAM_REGISTRO_PISTA);
	}

	void escrever_registro_corrida(Corrida i, int rrn) {
		char temp[TAM_REGISTRO_CORRIDA + 1];

		strcpy(temp, i.id_pista);
		strcat(temp, i.ocorrencia);
		strcat(temp, i.id_corredores);
		strcat(temp, i.id_veiculos);

		strncpy(ARQUIVO_CORRIDAS + (rrn * TAM_REGISTRO_CORRIDA), temp, TAM_REGISTRO_CORRIDA);
	}

	/* Funções principais */
	void cadastrar_corredor_menu(char *id_corredor, char *nome, char *apelido){

		corredores_index index;
		index.rrn = 0;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found;
		found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

		if(found != NULL) {
			printf(ERRO_PK_REPETIDA, found->id_corredor);
			return;
		}	
		
		char data[TAM_DATETIME];

		current_datetime(data);

		Corredor c;

		strcpy(c.apelido, apelido);
		strcpy(c.id_corredor, id_corredor);
		strcpy(c.nome, nome);
		strcpy(c.cadastro, data);
		c.saldo = 0.0;

		for(int i = 0; i < 3; i++) {
			c.veiculos[i][0] = '\0';
		}

		escrever_registro_corredor(c, qtd_registros_corredores);

		
		//salva o indice do registro
		strcpy(corredores_idx[qtd_registros_corredores].id_corredor, id_corredor);
		corredores_idx[qtd_registros_corredores].rrn = qtd_registros_corredores;

		qtd_registros_corredores++;

		qsort(corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx);

		printf(SUCESSO);

		
	}

	void remover_corredor_menu(char *id_corredor) {

		corredores_index index;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);	

		if(found == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		//define os primeiros dois digitos do registro como *|,ou seja, removido
		ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR] = '*';
		ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + 1] = '|';

		found->rrn = -1;

		printf(SUCESSO);

	}

	void adicionar_saldo_menu(char *id_corredor, double valor) {

		corredores_index index;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

		if(found == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		if(valor <= 0) {
			printf(ERRO_VALOR_INVALIDO);
			return;
		}

		char temp[TAM_REGISTRO_CORREDOR], *p;
		strncpy(temp, ARQUIVO_CORREDORES + (found->rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
		temp[TAM_REGISTRO_CORREDOR] = '\0';
		

		int tam = 0;

		p = strtok(temp, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;

		int fim = tam + 13;

		char valorString[14];

		char valorOriginalString[14];

		strncpy(valorOriginalString, ARQUIVO_CORREDORES + tam + (found->rrn * TAM_REGISTRO_CORREDOR), 13);

		double valorOriginal = strtod(valorOriginalString, NULL);

		valor += valorOriginal;

		sprintf(valorString, "%013.2lf", valor);

		for(int i = 0; tam < fim; tam++, i++) {
			ARQUIVO_CORREDORES[tam + found->rrn * TAM_REGISTRO_CORREDOR] = valorString[i];
		}
		
		printf(SUCESSO);

	}

	void adicionar_saldo(char *id_corredor, double valor, bool flag){
		
		corredores_index index;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

		if(found == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		if(valor <= 0) {
			printf(ERRO_VALOR_INVALIDO);
			return;
		}

		char temp[TAM_REGISTRO_CORREDOR], *p;
		strncpy(temp, ARQUIVO_CORREDORES + (found->rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
		temp[TAM_REGISTRO_CORREDOR] = '\0';
		

		int tam = 0;

		p = strtok(temp, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;

		int fim = tam + 13;

		char valorString[14];

		char valorOriginalString[14];

		strncpy(valorOriginalString, ARQUIVO_CORREDORES + tam + (found->rrn * TAM_REGISTRO_CORREDOR), 13);

		double valorOriginal = strtod(valorOriginalString, NULL);

		valor += valorOriginal;

		sprintf(valorString, "%013.2lf", valor);

		for(int i = 0; tam < fim; tam++, i++) {
			ARQUIVO_CORREDORES[tam + found->rrn * TAM_REGISTRO_CORREDOR] = valorString[i];
		}
	}

	void comprar_veiculo_menu(char *id_corredor, char *id_veiculo) {
		corredores_index index;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

		if(found == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		Corredor c = recuperar_registro_corredor(found->rrn);

		char temp[TAM_REGISTRO_CORREDOR], *p;
		strncpy(temp, ARQUIVO_CORREDORES + (found->rrn * TAM_REGISTRO_CORREDOR), TAM_REGISTRO_CORREDOR);
		temp[TAM_REGISTRO_CORREDOR] = '\0';

		int tam = 0;

		p = strtok(temp, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;
		p = strtok(NULL, ";");
		tam += strlen(p) + 1;

		char valorString[14];

		veiculos_index index1;
		strcpy(index1.id_veiculo, id_veiculo);
		veiculos_index *found1 = busca_binaria((void*)&index1, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

		if(found1 == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		Veiculo v = recuperar_registro_veiculo(found1->rrn);

		if(v.preco > c.saldo) {
			printf(ERRO_SALDO_NAO_SUFICIENTE);
			return;
		}

		for(int i = 0; i < 3; i++) {
			if(strcmp(c.veiculos[i], v.modelo) == 0) {
				printf(ERRO_VEICULO_REPETIDO, c.id_corredor, v.id_veiculo);
				return;
			}
		}

		sprintf(valorString, "%013.2lf", c.saldo - v.preco);

		strncpy(&ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam], valorString, 13);

		tam += 13;

		tam++;

		int cont = 0;

		for(int i = 0;i < 3; i++) {
			if(c.veiculos[i][0] != '\0') {
				cont++;
			}
		}

		if(cont == 0) {
			int i;

			for(i = 0; i < strlen(v.modelo); i++) {
				ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam + i] = v.modelo[i];
			}
			ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam + i] = ';';
		}
		else if(cont == 1) {
			

			for(;ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam] != ';'; tam++);

			ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam] = '|';

			tam++;

			int j;

			for(j = 0; j < strlen(v.modelo); j++) {
				ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam + j] = v.modelo[j];
			}

			ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam + j] = ';';
		}
		else{
			for(; ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam] != '#';  tam++);

			tam--;

			ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam] = '|';

			tam++;

			int k;

			for(k = 0; k < strlen(v.modelo); k++) {
				ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam + k] = v.modelo[k];
			}

			ARQUIVO_CORREDORES[found->rrn * TAM_REGISTRO_CORREDOR + tam + k] = ';';


		}

		inverted_list_insert(v.modelo, c.id_corredor, &corredor_veiculos_idx);

		printf(SUCESSO);

	}

	void cadastrar_veiculo_menu(char *marca, char *modelo, char *poder, int velocidade, int aceleracao, int peso, double preco) {
		Veiculo v;

		char p[100];
		sprintf(p, "%07d", qtd_registros_veiculos);

		veiculos_index index;
		strcpy(index.id_veiculo, p);
		veiculos_index *found = busca_binaria((void*)&index, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

		if (found != NULL) {
			printf(ERRO_PK_REPETIDA, found->id_veiculo);
			return;
		}

		strcpy(v.marca,marca);
		strcpy(v.modelo, modelo);
		strcpy(v.poder,poder);
		v.velocidade = velocidade;
		v.aceleracao = aceleracao;
		v.peso = peso;
		v.preco = preco;

		escrever_registro_veiculo(v, qtd_registros_veiculos);
		


		strcpy(veiculos_idx[qtd_registros_veiculos].id_veiculo, p);
		veiculos_idx[qtd_registros_veiculos].rrn = qtd_registros_veiculos;

		strcpy(preco_veiculo_idx[qtd_registros_veiculos].id_veiculo, p);
		preco_veiculo_idx[qtd_registros_veiculos].preco = preco;
		

		qtd_registros_veiculos++;

		qsort(veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx);
		qsort(preco_veiculo_idx, qtd_registros_veiculos, sizeof(preco_veiculo_index), qsort_preco_veiculo_idx);

		printf(SUCESSO);

	}

	void cadastrar_pista_menu(char *nome, int dificuldade, int distancia, int recorde){

		nome_pista_index index;
		strcpy(index.nome, nome);
		nome_pista_index *found = busca_binaria((void*)&index, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, false, 0);

		if (found != NULL) {
			printf(ERRO_PK_REPETIDA, found->nome);
			return;
		}

		Pista p;
		char t[TAM_ARQUIVO_PISTAS];

		sprintf(t, "%08d", qtd_registros_pistas);

		strcpy(p.id_pista, t);
		strcpy(p.nome, nome);
		p.dificuldade = dificuldade;
		p.distancia = distancia;
		p.recorde = recorde;

		escrever_registro_pista(p, qtd_registros_pistas);

		strcpy(pistas_idx[qtd_registros_pistas].id_pista, t);
		pistas_idx[qtd_registros_pistas].rrn = qtd_registros_pistas;

		strcpy(nome_pista_idx[qtd_registros_pistas].id_pista, t);
		strcpy(nome_pista_idx[qtd_registros_pistas].nome, nome);

		qtd_registros_pistas++;

		qsort(nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx);

		
		
		printf(SUCESSO);

	}

	void executar_corrida_menu(char *id_pista, char *ocorrencia, char *id_corredores, char *id_veiculos) {
		Corrida i;

		strcpy(i.id_pista, id_pista);
		strcpy(i.id_corredores, id_corredores);
		strcpy(i.id_veiculos, id_veiculos);
		strcpy(i.ocorrencia, ocorrencia);

		char aux[TAM_ID_PISTA + 200];

		strcpy(aux, ocorrencia);
		strcat(aux, id_pista);
		
		pistas_index index1;
		strcpy(index1.id_pista, id_pista);
		pistas_index *found1 = busca_binaria((void*)&index1, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_data_idx, false, 0);

		if(found1 == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		Pista p = recuperar_registro_pista(found1->rrn);

		double premio_total = 6 * (TX_FIXA * p.dificuldade);

		Corredor c[6];
		Veiculo v[6];


		//salva os corredores e veiculos da corrida
		for(int i = 0, tam = 0, tam_vei = 0; i < 6; i++, tam += 11, tam_vei += 7) {
			

			strncpy(c[i].id_corredor, id_corredores + tam, 11);
			c[i].id_corredor[11] = '\0';

			strncpy(v[i].id_veiculo, id_veiculos + tam_vei, 7);
			v[i].id_veiculo[7] = '\0';
			

		}

		veiculos_index index2;
		corredores_index index3;

		//faz buscas, verificando se esses corredores e veiculos existem nos registros		
		for(int i = 0; i < 6; i++) {
			strcpy(index2.id_veiculo, v[i].id_veiculo);
			veiculos_index *found2 = busca_binaria((void*)&index2, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

			if(found2 == NULL) {
				printf(ERRO_REGISTRO_NAO_ENCONTRADO);
				return;
			}

			strcpy(index3.id_corredor,c[i].id_corredor);
			corredores_index *found3 = busca_binaria((void*)&index3,corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

			if(found3 == NULL) {
				printf(ERRO_REGISTRO_NAO_ENCONTRADO);
				return;
			}

		}

		//verifica se ja ha uma corrida com a mesma chave composta
		corridas_index index;
		strcpy(index.ocorrencia, ocorrencia);
		corridas_index *found = busca_binaria((void*)&index, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_data_idx, false, 0);

		if(found != NULL) {
			if(strcmp(found->id_pista, id_pista ) == 0) {
				printf(ERRO_PK_REPETIDA, aux);
				return;
			}
		}

		int retorno = 0;

		//laço que verifica todos os veiculos,buscando-os na lista secundaria para encontrar o primeiro indice de corredor na primaria
		for(int i = 0; i < 6; i++) {
			veiculos_index index4;
			strcpy(index4.id_veiculo, v[i].id_veiculo);
			veiculos_index *found4 = busca_binaria((void*)&index4, veiculos_idx, qtd_registros_veiculos, sizeof(veiculos_index), qsort_veiculos_idx, false, 0);

			int flag = 0;

			Veiculo V = recuperar_registro_veiculo(found4->rrn);

			int ind;

			bool achou = inverted_list_secondary_search(&ind, false, V.modelo, &corredor_veiculos_idx);

			//caso o veiculo esteja na secundaria, ele busca e salva todos os corredores que possuem esse veiculo na primaria, afim de encontar aquele designado a ele na corrida
			if(achou) {
				char ids[MAX_REGISTROS][TAM_ID_CORREDOR];

				int aux;

				int qtd = inverted_list_primary_search(ids, false, ind, &aux, &corredor_veiculos_idx);

				//se o corredor especifico estiver na lista, entao a flag é 1, significando que aquele corredor contem o veiculo que foi passado para ele na corrida
				for(int j = 0; j < qtd; j++) {
					if(strcmp(ids[j], c[i].id_corredor) == 0) {
						flag = 1;
					}
				}
			}

			if(flag == 0) {
				printf(ERRO_CORREDOR_VEICULO, c[i].id_corredor,v[i].id_veiculo);
				retorno = 1;
			}

		}

		if(retorno == 1) {
			return;
		}
		

		
		escrever_registro_corrida(i, qtd_registros_corridas);
		
		strcpy(corridas_idx[qtd_registros_corridas].id_pista, id_pista);
		strcpy(corridas_idx[qtd_registros_corridas].ocorrencia, ocorrencia);
		corridas_idx[qtd_registros_corridas].rrn = qtd_registros_corridas;

		qtd_registros_corridas++;
		
		qsort(corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_data_idx);

		adicionar_saldo(c[0].id_corredor, 0.4 * premio_total, false);
		adicionar_saldo(c[1].id_corredor, 0.3 * premio_total, false);
		adicionar_saldo(c[2].id_corredor, 0.2 * premio_total, false);

		printf(SUCESSO);
		
	}

	/* Busca */
	void buscar_corredor_id_menu(char *id_corredor) {
		corredores_index index;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, true, 0);
		if (found == NULL || found->rrn < 0)
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		else
			exibir_corredor(found->rrn);
	}

	void buscar_pista_id_menu(char *id_pista) {
		pistas_index index;
		strcpy(index.id_pista, id_pista);
		pistas_index *found = busca_binaria((void*)&index, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true,0);

		if(found == NULL || found->rrn < 0) 
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
		else
			exibir_pista(found->rrn);
	}

	void buscar_pista_nome_menu(char *nome_pista) {
		//primeiro faz a busca pela chave secundaria
		nome_pista_index index;
		strcpy(index.nome, nome_pista);
		nome_pista_index *found = busca_binaria((void*)&index, nome_pista_idx, qtd_registros_pistas, sizeof(nome_pista_index), qsort_nome_pista_idx, true, 0);

		if(found == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}
		
		//depois de encontrada,é feita pela chave primaria
		pistas_index index2;
		strcpy(index2.id_pista, found->id_pista);
		pistas_index *found2 = busca_binaria((void*)&index2, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, true, 0);

		if(found2 == NULL) {
			printf(ERRO_REGISTRO_NAO_ENCONTRADO);
			return;
		}

		//depois de encontrar o id atraves da chave secundaria, busco o rrn na primaria
		pistas_index index1;
		strcpy(index1.id_pista, found->id_pista);
		pistas_index *found1 = busca_binaria((void*)&index1, pistas_idx, qtd_registros_pistas, sizeof(pistas_index), qsort_pistas_idx, false, 0);

		//apos encontrar o rrn, exibo a pista
		exibir_pista(found1->rrn);
	}

	/* Listagem */
	void listar_corredores_id_menu() {
		if (qtd_registros_corredores == 0)
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
		else 
			for (unsigned int i = 0; i < qtd_registros_corredores; i++)
				exibir_corredor(corredores_idx[i].rrn);
	}

	void listar_corredores_modelo_menu(char *modelo){
		int result;

		bool found = inverted_list_secondary_search(&result, false, modelo, &corredor_veiculos_idx);

		if(found == false) {
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
			return;
		}

		char registros[MAX_REGISTROS][TAM_ID_CORREDOR];

		for(int i = 0; i < MAX_REGISTROS; i++) {
			registros[i][0] = '\0';
		}

		int idx;

		int qtd = inverted_list_primary_search(registros, true, result, &idx, &corredor_veiculos_idx);

		//cria um vetor de corredores
		corredores_index c[MAX_REGISTROS];

		//salva os ids encontradosno vetor e depois ordena
		for(int i = 0; i < qtd; i++) {
			strcpy(c[i].id_corredor, registros[i]);
		}

		qsort(c, qtd, sizeof(corredores_index), qsort_corredores_idx);

		//com o vetor ja ordenado, ele busca o rrn pelo id e exibe o corredor
		for(int i = 0; i < qtd; i++) {
			corredores_index index;
			strcpy(index.id_corredor, c[i].id_corredor);
			corredores_index *found1 = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

			exibir_corredor(found1->rrn);
		}
	}

	void listar_veiculos_compra_menu(char *id_corredor) {
		corredores_index index;
		strcpy(index.id_corredor, id_corredor);
		corredores_index *found = busca_binaria((void*)&index, corredores_idx, qtd_registros_corredores, sizeof(corredores_index), qsort_corredores_idx, false, 0);

		if(found == NULL) {
			printf(AVISO_NENHUM_REGISTRO_ENCONTRADO);
			return;
		}

		Corredor c = recuperar_registro_corredor(found->rrn);

		for(int i = 0; i < qtd_registros_veiculos; i++) {
			if(preco_veiculo_idx[i].preco <= c.saldo) {
				veiculos_index index1;
				strcpy(index1.id_veiculo, preco_veiculo_idx[i].id_veiculo);
				veiculos_index *found = busca_binaria((void*)&index1, veiculos_idx, qtd_registros_veiculos,sizeof(veiculos_index),qsort_veiculos_idx, false,0);

				exibir_veiculo(found->rrn);
			}
		}
		
	}

	void listar_corridas_periodo_menu(char *data_inicio, char *data_fim) {
		corridas_index i;
		strcpy(i.ocorrencia, data_inicio);
		corridas_index *found = busca_binaria((void*)&i, corridas_idx, qtd_registros_corridas, sizeof(corridas_index), qsort_data_idx, true, -1);

		if(found != NULL) {
			exibir_corrida(found->rrn);
		} 

	}

	/* Liberar espaço */
	void liberar_espaco_menu() {

		//verifica todos os registros,procurando um com rrn -1
		for(int i = 0;i < qtd_registros_corredores; i++) {
			//caso um registro com rrn -1 seja encontrado,eleo remove arrastando os outros registros para a esquerda
			if(corredores_idx[i].rrn == -1) {
				for(int j = i; j < qtd_registros_corredores - 1; j++) {
					corredores_idx[j].rrn = corredores_idx[j + 1].rrn;
					
					strcpy(corredores_idx[j].id_corredor, corredores_idx[j + 1].id_corredor);
				}
			}
			corredores_idx[i].rrn--;	
		}

		int cont = 0;

		//o indice size começa no primeiro registro, e vai pulando de registro em registro ate verificar todos
		for(int i = 0, size = 0; i < qtd_registros_corredores; i++, size += TAM_REGISTRO_CORREDOR) {

			//se os dois primeiros caracteres do registro corresponderem ao marcador de remocao,o registro é removido fisicamente
			if(ARQUIVO_CORREDORES[size] == '*' && ARQUIVO_CORREDORES[size + 1] == '|') {
				cont ++;

				//nesse laço, ele substitiu os caracteres do registro especifico pelo resto do  arquivo,"puxando" o arquivo
				for(int j = size, k = size + TAM_REGISTRO_CORREDOR ; k <= strlen(ARQUIVO_CORREDORES); j++, k++) {
					ARQUIVO_CORREDORES[j] = ARQUIVO_CORREDORES[k];
				}

				//quando ocorre uma remocao, é preciso diminuir o size,pos o proximo registro tambem pode ser um removido, e se nao diminuir,ira pular essa verificacao 
				//o size no fim deve igualar o tamanho do arquivo, se o arquivo diminue,o size tambem
				size -= TAM_REGISTRO_CORREDOR;
			}
		}

		//a quantidade é diminuida pelo numero de registros removidos
		qtd_registros_corredores -= cont;

		printf(SUCESSO);
	}

	/* Imprimir arquivos de dados */
	void imprimir_arquivo_corredores_menu() {
		if (qtd_registros_corredores == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else
			printf("%s\n", ARQUIVO_CORREDORES);
	}

	void imprimir_arquivo_veiculos_menu() {
		if (qtd_registros_veiculos == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else
			printf("%s\n", ARQUIVO_VEICULOS);
	}

	void imprimir_arquivo_pistas_menu() {
		if (qtd_registros_pistas == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else
			printf("%s\n", ARQUIVO_PISTAS);
	}

	void imprimir_arquivo_corridas_menu() {
		if (qtd_registros_corridas == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else
			printf("%s\n", ARQUIVO_CORRIDAS);
	}

	/* Imprimir índices primários */
	void imprimir_corredores_idx_menu() {
		if (corredores_idx == NULL || qtd_registros_corredores == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else
			for (unsigned i = 0; i < qtd_registros_corredores; ++i)
				printf("%s, %d\n", corredores_idx[i].id_corredor, corredores_idx[i].rrn);
	}

	void imprimir_veiculos_idx_menu() {
		if(veiculos_idx == NULL || qtd_registros_veiculos == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else
			for(unsigned i = 0; i < qtd_registros_veiculos; i++)
				printf("%s, %d\n", veiculos_idx[i].id_veiculo, veiculos_idx[i].rrn);
	}

	void imprimir_pistas_idx_menu() {
		if(pistas_idx == NULL || qtd_registros_pistas == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else
			for(unsigned i = 0; i < qtd_registros_pistas; i++)
				printf("%s, %d\n", pistas_idx[i].id_pista, pistas_idx[i].rrn);
	}

	void imprimir_corridas_idx_menu() {
		if(corridas_idx == NULL || qtd_registros_corridas == 0)
			printf(ERRO_ARQUIVO_VAZIO);
		else	
			for(unsigned i = 0; i < qtd_registros_corridas;i++) {
				printf("%s, %s, %d\n", corridas_idx[i].ocorrencia, corridas_idx[i].id_pista, corridas_idx[i].rrn);
			}
	}

	/* Imprimir índices secundários */
	void imprimir_nome_pista_idx_menu() {
		for(unsigned i = 0;i < qtd_registros_pistas; i++) {
			char aux[TAM_MAX_NOME_PISTA];

			strcpy(aux, nome_pista_idx[i].nome);

			strupr(aux);

			printf("%s, %s\n", aux, nome_pista_idx[i].id_pista);
		}
	}

	void imprimir_preco_veiculo_idx_menu() {
		for(unsigned i = 0; i < qtd_registros_veiculos; i++) {
			printf("%.2lf, %s\n", preco_veiculo_idx[i].preco, preco_veiculo_idx[i].id_veiculo);
		}
	}


	void imprimir_corredor_veiculos_secundario_idx_menu() {
		for(int i = 0; i < corredor_veiculos_idx.qtd_registros_secundario; i++) {
			char temp[TAM_MAX_MODELO];

			strcpy(temp, corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].chave_secundaria);

			strupr(temp);

			printf("%s, %d\n", temp, corredor_veiculos_idx.corredor_veiculos_secundario_idx[i].primeiro_indice);
		}
	}

	void imprimir_corredor_veiculos_primario_idx_menu(){
		for(int i = 0; i < corredor_veiculos_idx.qtd_registros_primario; i++) {
			printf("%s, %d\n", corredor_veiculos_idx.corredor_veiculos_primario_idx[i].chave_primaria, corredor_veiculos_idx.corredor_veiculos_primario_idx[i].proximo_indice);
		}
	}

	/* Liberar memória e encerrar programa */
	void liberar_memoria_menu() {
		free(corredores_idx);
		free(veiculos_idx);
		free(pistas_idx);
		free(corridas_idx);
		free(nome_pista_idx);
		free(preco_veiculo_idx);
		free(corredor_veiculos_idx.corredor_veiculos_secundario_idx);
		free(corredor_veiculos_idx.corredor_veiculos_primario_idx);
	}

	void inverted_list_insert(char *chave_secundaria, char *chave_primaria, inverted_list *t) {

		int result;

		bool found = inverted_list_secondary_search(&result, false, chave_secundaria, t);

		//se ainda nao ha o veiculo especifico no indice secundario, ele cria um secundario e salva o veiculo, tambem cria um primario para o veiculo
		if(found == false) {
			t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].primeiro_indice = t->qtd_registros_primario;
			strcpy(t->corredor_veiculos_secundario_idx[t->qtd_registros_secundario].chave_secundaria, chave_secundaria);

			t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
			strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);

			t->qtd_registros_secundario++;				
		}
		//se ja ha um secundario, ele procura o ultimo registro primario que contem o veiculo, atualiza os indices,e adiciona um novo indice para o novo registro primario
		else {
			int final;
			char resultado[MAX_REGISTROS][TAM_ID_CORREDOR];

			inverted_list_primary_search(resultado, false, result, &final, t);

			t->corredor_veiculos_primario_idx[final].proximo_indice =  t->qtd_registros_primario;

			strcpy(t->corredor_veiculos_primario_idx[t->qtd_registros_primario].chave_primaria, chave_primaria);
			t->corredor_veiculos_primario_idx[t->qtd_registros_primario].proximo_indice = -1;
		}


		t->qtd_registros_primario++;
		qsort(corredor_veiculos_idx.corredor_veiculos_secundario_idx, corredor_veiculos_idx.qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx);

	}

	bool inverted_list_secondary_search(int *result, bool exibir_caminho, char *chave_secundaria, inverted_list *t) {
		corredor_veiculos_secundario_index index;
		strcpy(index.chave_secundaria, chave_secundaria);
		corredor_veiculos_secundario_index *found = busca_binaria((void*)&index, t->corredor_veiculos_secundario_idx, t->qtd_registros_secundario, sizeof(corredor_veiculos_secundario_index), qsort_corredor_veiculos_secundario_idx, exibir_caminho, 0);


		if(found == NULL) {
			return false;
		}
		else {
			*result = found->primeiro_indice;
			return true;
		}
	}

	int inverted_list_primary_search(char result[][TAM_ID_CORREDOR], bool exibir_caminho, int indice, int *indice_final, inverted_list *t) {
		int cont = 0;

		char caminho[100000];

		char aux[100000];

		strcpy(caminho, "Registros percorridos:");

		//enquanto nao se acha um registro com proximo indice de -1,significa que ha um proximo registro, e o indice atualiza para o indice desse proximo

		while(t->corredor_veiculos_primario_idx[indice].proximo_indice != -1) {
			strcat(caminho, " ");
			sprintf(aux, "%d", indice);
			strcat(caminho, aux);
			strcpy(result[cont], t->corredor_veiculos_primario_idx[indice].chave_primaria);
			cont++;
			indice = t->corredor_veiculos_primario_idx[indice].proximo_indice;
		}

		*indice_final = indice;

		//adiciona o ultimo indice percorrido ao caminho
		strcat(caminho, " ");
		sprintf(aux, "%d", indice);
		strcat(caminho, aux);

		strcpy(result[cont], t->corredor_veiculos_primario_idx[indice].chave_primaria);

		if(exibir_caminho == true) {
			printf("%s\n", caminho);
		}

		cont++;

		return cont;
	}


	void* busca_binaria_com_reps(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int posicao_caso_repetido, int retorno_se_nao_encontrado) {
		
		int inicio, fim, meio;
		char cam[MAX_REGISTROS] = "Registros percorridos:";

		
		int cont_repetido = 0;
		int ind_repetidos[MAX_REGISTROS];
		inicio = 0;
		fim = nmemb - 1;

		while(inicio <= fim) {
			if((fim - inicio + 1) % 2 == 0) {
				meio = ((fim + inicio) / 2) + 1; // se for par, a mediana é sempre mais a direita
			}
			else {
				meio = (fim + inicio) / 2;
			}

			char aux_num[MAX_REGISTROS];
			sprintf(aux_num, "%d", meio);

			strcat(cam, " ");
			strcat(cam, aux_num);

			if(compar(key, base0 + meio * size) > 0) {
				inicio = meio  + 1;
			}
			else if(compar(key, base0 + meio * size) < 0) {
				fim = meio  - 1;
			}
			else {
				//apos encontrar o  elemento, ele verifica  se ha outros repetidos, faz isso veriificando as proximidades do elemento encontrado, ate encontrar um diferente que quebre essa busca
				ind_repetidos[cont_repetido] = meio;
				cont_repetido++;

				int antes = meio - 1;

				while(antes >= inicio && compar(key, base0 + antes * size) == 0) {
					cont_repetido++;
					antes--;
				}

				int depois = meio + 1;

				while(depois <= fim && compar(key, base0 + depois * size) == 0) {
					cont_repetido++;
					depois++;
				}

				break;
			}
		}

		

		if(exibir_caminho == true) {
			printf("%s\n", cam);
		}

		if(cont_repetido == 1) {
			return (void *)((const char*)base0 + meio * size);
		}

		if(cont_repetido > 1) {
			if(posicao_caso_repetido ==  - 1) {
				return (void *)((const char*)base0 + (ind_repetidos[0]) * size);
			}
			else if(posicao_caso_repetido == 0) {
				return (void *)((const char*)base0 + (ind_repetidos[cont_repetido / 2]) * size);
			}
			else {
				return (void *)((const char*)base0 + (ind_repetidos[cont_repetido + 1]) * size);
			}
		}
		else if(cont_repetido == 0){
			if(retorno_se_nao_encontrado == 0) {
				return NULL;
			}
			else if(retorno_se_nao_encontrado == -1) {
				return (void *)((const char*)base0 + (meio - 1) * size);
			}
			else {
				return (void *)((const char*)base0 + (meio + 1) * size);
			}
		}

		return NULL;
	}

	void* busca_binaria(const void *key, const void *base0, size_t nmemb, size_t size, int (*compar)(const void *, const void *), bool exibir_caminho, int retorno_se_nao_encontrado) {
		return busca_binaria_com_reps(key, base0, nmemb, size, compar, exibir_caminho, 0, retorno_se_nao_encontrado);
	}

	char *strpadright(char *str, char pad, unsigned size){
		for (unsigned i = strlen(str); i < size; ++i)
			str[i] = pad;
		str[size] = '\0';
		return str;
	}
	char *strupr(char *str){
		for (char *p = str; *p; ++p)
			*p = toupper(*p);
		return str;
	}
	char *strlower(char *str){
		for (char *p = str; *p; ++p)
			*p = tolower(*p);
		return str;
	}