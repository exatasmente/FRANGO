Pessoa *pessoa;
void exibirBuscarForm(){
		char *opcoes[] = {"CANCELA","CONFIRMA"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, 2);
		char *campos[] = {"Nome:"," " };
		exibirFormulario(24, 80, (LINES)/2, (COLS-81)/2, campos, size(campos));
		atual[3] = true;
}
void confirmaBuscar(){
	pessoa = buscarPessoaNome(sistema,field_buffer(campo[1],0));
	form = false;
	
	if(pessoa != NULL){
		char *condicao[20];
		condicaoImc(pessoa->imc,pessoa->sexo,condicao);
		char *opcoes[]= {"VOLTAR","EXERCICIOS"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
		apagaForm();
		mvwprintw(janelaFormulario,2, 3, "Usuário Encontrado:");			
		
		mvwprintw(janelaFormulario,3, 3,"Nome :%s",pessoa->nome);
		mvwprintw(janelaFormulario,4, 3,"Sexo : %s",pessoa->sexo == 0 ? "Feminino" : "Masculino");
		mvwprintw(janelaFormulario,5, 3,"Peso : %.2f",pessoa->medidas->peso);
		mvwprintw(janelaFormulario,6, 3,"Altura : %.2f",pessoa->medidas->altura);
		mvwprintw(janelaFormulario,7, 3,"IMC : %.2f %s",pessoa->imc,condicao);
		mvwprintw(janelaFormulario,8, 3,"Objetivo: %s",pessoa->objetivo);
		
	}else{
		char *opcoes[]= {"VOLTAR"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
		apagaForm();
		mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "Usuário Não Encontrado:");			
	}
	refresh();
}
void exibeExecicios(){
	char *opcoes[]= {"VOLTAR"};
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
	apagaForm();
	int colunas = 3;
	int linha = 1;
	char *dias[] = {"SEGUNDA","TERCA","QUARTA","QUINTA","SEXTA"};
	mvwprintw(janelaFormulario,linha, colunas,"%s",dias[0]);
	for(int j = 0 ; j < 3 ; j++){
		mvwprintw(janelaFormulario,linha+j+1, colunas,"%s : %dx%d",
		pessoa->treino->exercicios[0]->equipamentos[j]->nomeEquipamento,
		pessoa->treino->exercicios[0]->equipamentos[j]->series,
		pessoa->treino->exercicios[0]->equipamentos[j]->repeticoes
		);			
	}
	linha = 6;
	mvwprintw(janelaFormulario,linha, colunas,"%s",dias[1]);
	for(int j = 0 ; j < 3 ; j++){
		mvwprintw(janelaFormulario,linha+j+1, colunas,"%s : %dx%d",
		pessoa->treino->exercicios[1]->equipamentos[j]->nomeEquipamento,
		pessoa->treino->exercicios[1]->equipamentos[j]->series,
		pessoa->treino->exercicios[1]->equipamentos[j]->repeticoes
		);			
	}
	linha = 12;
	mvwprintw(janelaFormulario,linha, colunas,"%s",dias[2]);
	for(int j = 0 ; j < 3 ; j++){
		mvwprintw(janelaFormulario,linha+j+1, colunas,"%s : %dx%d",
		pessoa->treino->exercicios[2]->equipamentos[j]->nomeEquipamento,
		pessoa->treino->exercicios[2]->equipamentos[j]->series,
		pessoa->treino->exercicios[2]->equipamentos[j]->repeticoes
		);			
	}
	linha = 1;
	colunas = 40;
	mvwprintw(janelaFormulario,linha, colunas,"%s",dias[3]);
	for(int j = 0 ; j < 3 ; j++){
		mvwprintw(janelaFormulario,linha+j+1, colunas,"%s : %dx%d",
		pessoa->treino->exercicios[3]->equipamentos[j]->nomeEquipamento,
		pessoa->treino->exercicios[3]->equipamentos[j]->series,
		pessoa->treino->exercicios[3]->equipamentos[j]->repeticoes
		);			
	}
	linha = 6;
	mvwprintw(janelaFormulario,linha, colunas,"%s",dias[4]);
	for(int j = 0 ; j < 3 ; j++){
		mvwprintw(janelaFormulario,linha+j+1, colunas,"%s : %dx%d",
		pessoa->treino->exercicios[4]->equipamentos[j]->nomeEquipamento,
		pessoa->treino->exercicios[4]->equipamentos[j]->series,
		pessoa->treino->exercicios[4]->equipamentos[j]->repeticoes
		);			
	}
		
	
}
void controleBuscar(char *nome){
	if(strcmp(nome, "CANCELA") == 0 ){
		voltarMenu(0);
	}else if(strcmp(nome,"CONFIRMA") == 0){
		confirmaBuscar();	
	}else if(strcmp(nome,"VOLTAR") == 0){
		voltarMenu(0);
	}else if(strcmp(nome,"EXERCICIOS") == 0){
		exibeExecicios();
	}
}