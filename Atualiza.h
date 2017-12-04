void exibirAtualizarForm(){
		char *opcoes[] = {"CANCELA","BUSCAR"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, 2);
		char *campos[] = {"Nome:"," " };
		exibirFormulario(24, 80, (LINES)/2, (COLS-81)/2, campos, size(campos));
		atual[1] = true;
}

void confirmaAtualiza(){
	Pessoa *pessoa;
	Medidas *medidas = novoMedidas((float)atof(field_buffer(campo[5],0)),
								   (float)atof(field_buffer(campo[7],0)),
								   atof(field_buffer(campo[9],0)),
								   atof(field_buffer(campo[11],0)),
								   atof(field_buffer(campo[13],0)),
								   atof(field_buffer(campo[15],0)),
								   atof(field_buffer(campo[17],0)),
								   atof(field_buffer(campo[19],0)),
								   atof(field_buffer(campo[21],0)),
								   atof(field_buffer(campo[23],0)),
								   atof(field_buffer(campo[25],0))
								   );
					
		
	Treino *treino;
	pessoa = novaPessoa(field_buffer(campo[1],0),atoi(field_buffer(campo[2],0)),medidas,treino,atoi(field_buffer(campo[3],0)));
	float imc = calculaImc(medidas->peso,medidas->altura);
	pessoa->imc = imc;
	char cond[40];
	condicaoImc(imc,pessoa->sexo,cond);
    atualizaCadastro(sistema,pessoa);
	char *opcoes[]= {"VOLTAR"};
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
	char *campos[] = {""};
	exibirFormulario(24, 80, (LINES-25)/2, (COLS-81)/2, campos, size(campos));
	unpost_form(formulario);
	for (int i = 0; campo[i] != NULL; i++) {
		free_field(campo[i]);
	}
	free_form(formulario);
	delwin(janelaFormulario);
	form = false;
	mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "USUARIO ATUALIZADO:");			
	mvwprintw(janelaFormulario, ((LINES-25)/2)+1, (COLS-80)/2,"%s",pessoa->nome);
	mvwprintw(janelaFormulario,((LINES-25)/2)+2, (COLS-80)/2,"Seu imc é :%.2f ele está %s",imc,cond);
	refresh();
}
void buscarAtualiza(){
	Pessoa *pessoa = buscarPessoaNome(sistema,field_buffer(campo[1],0));
	char *opcoes[]= {"VOLTAR","ATUALIZAR"};
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
	if(pessoa != NULL){
			char **dados = (char**)malloc(sizeof(char*)*12);
			for(int i = 0 ; i < 12; i++){
				dados[i] = (char*)malloc(sizeof(char)*12);
			}
			sprintf(dados[0], "%d", pessoa->sexo);
			sprintf(dados[1], "%f", pessoa->medidas->peso);
			sprintf(dados[2], "%f", pessoa->medidas->altura);
			sprintf(dados[3], "%f", pessoa->medidas->bracoDireito);
			sprintf(dados[4], "%f", pessoa->medidas->bracoEsquerdo);
			sprintf(dados[5], "%f", pessoa->medidas->pernaDireita);
			sprintf(dados[6], "%f", pessoa->medidas->pernaEsquerda);
			sprintf(dados[6], "%f", pessoa->medidas->panturrilhaDireita);
			sprintf(dados[7], "%f", pessoa->medidas->panturrilhaEsquerda);
			sprintf(dados[9], "%f", pessoa->medidas->abdomen);
			sprintf(dados[10], "%f", pessoa->medidas->cintura);
			sprintf(dados[11], "%f", pessoa->medidas->peito);
			char *campos[] = {"Nome:",pessoa->nome, 
						  "Sexo (0 F, 1 M):",dados[0], 
						  "Peso:",dados[1], 
						  "Altura em cm",dados[2],
						  "Braço Direito",dados[3],
						  "Braço Esquerdo",dados[4],
						  "Perna Direita",dados[5],
						  "Perna Esquerda",dados[6],
						  "Panturrilha Direita",dados[7],
						  "Panturrilha Esquerda",dados[8],
						  "Abdomen",dados[9],
						  "Cintura",dados[10],
						  "Peito",dados[11]};
		exibirFormulario(24, 80, (LINES-25)/2, (COLS-81)/2, campos, size(campos));	
		form = true;
	}else{
		char *opcoes[]= {"VOLTAR"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
		char *campos[] = {""};
		exibirFormulario(24, 80, (LINES-25)/2, (COLS-81)/2, campos, size(campos));
		unpost_form(formulario);
		for (int i = 0; campo[i] != NULL; i++) {
			free_field(campo[i]);
		}
		free_form(formulario);
		delwin(janelaFormulario);
		mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "Usuário Não Encontrado:");			
		form = false;
	}
	
	
}
void controleAtualiza(char *nome){
	Pessoa *pessoa;
	if(strcmp(nome, "CANCELA") == 0 ){
		voltarMenu(1);
	}else if(strcmp(nome,"BUSCAR") == 0){
		buscarAtualiza();	
	}else if(strcmp(nome,"VOLTAR") == 0){
		voltarMenu(1);
	}else if(strcmp(nome,"ATUALIZAR") == 0){
		confirmaAtualiza();
	}
}