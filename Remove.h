void exibirRemoverForm();
void confirmaRemove();
void controleRemove(char *nome);

Pessoa *pessoa;

void exibirRemoverForm(){
	char *opcoes[] = {"CANCELA","BUSCAR"};
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, 2);
	char *campos[] = {"Nome:"," " };
	exibirFormulario(24, 80, (LINES)/2, (COLS-81)/2, campos, size(campos));
	atual[2] = true;
}
void confirmaRemove(){

	pessoa = buscarPessoaNome(sistema,field_buffer(campo[1],0));

	char *opcoes[]= {"VOLTAR","REMOVER"};
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
	if(pessoa != NULL){
		mvwprintw(janelaFormulario,2, (COLS-60)/2, "Usuário Encontrado:");			
		mvwprintw(janelaFormulario,3, (COLS-60)/2,"Nome :%s",pessoa->nome);
		mvwprintw(janelaFormulario,4, (COLS-60)/2,"Sexo : %s",pessoa->sexo == 0 ? "Feminino" : "Masculino");
		mvwprintw(janelaFormulario,5, (COLS-60)/2,"Peso : %.2f",pessoa->medidas->peso);
		mvwprintw(janelaFormulario,6, (COLS-60)/2,"Altura : %.2f",pessoa->medidas->altura);
		mvwprintw(janelaFormulario,7, (COLS-60)/2,"IMC : %.2f",pessoa->imc);
		mvwprintw(janelaFormulario,8, (COLS-60)/2,"Objetivo: %s",pessoa->objetivo);
		mvwprintw(janelaFormulario,9, (COLS-60)/2,"EXERCICIO");		
		int colunas = 10;
		
		
	}else{
		mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "Usuário Não Encontrado:");			
	}
	refresh();
}
void controleRemove(char *nome){
	if(strcmp(nome, "CANCELA") == 0 ){
		voltarMenu(2);
	}else if(strcmp(nome,"BUSCAR") == 0){
		confirmaRemove();	
	}else if(strcmp(nome,"VOLTAR") == 0){
		voltarMenu(2);
	}else if(strcmp(nome,"REMOVER")== 0){
		
		removerPessoa(sistema,pessoa->matricula);
		char *opcoes[]= {"VOLTAR"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
		apagaForm();
		mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "Usuário Removido");
	}
}