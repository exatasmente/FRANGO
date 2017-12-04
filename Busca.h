void exibirBuscarForm(){
		char *opcoes[] = {"CANCELA","CONFIRMA"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, 2);
		char *campos[] = {"Nome:"," " };
		exibirFormulario(24, 80, (LINES)/2, (COLS-81)/2, campos, size(campos));
		atual[3] = true;
}
void confirmaBuscar(){
	
	Pessoa *pessoa = buscarPessoaNome(sistema,field_buffer(campo[1],0));

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
	if(pessoa != NULL){
		mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-60)/2, "Usuário Encontrado:");			
		mvwprintw(janelaFormulario, ((LINES-25)/2)+1, (COLS-60)/2,"Nome :%s",pessoa->nome);
		mvwprintw(janelaFormulario, ((LINES-25)/2)+2, (COLS-60)/2,"Sexo : %s",pessoa->sexo == 0 ? "Feminino" : "Masculino");
		mvwprintw(janelaFormulario, ((LINES-25)/2)+3, (COLS-60)/2,"Peso : %.2f",pessoa->medidas->peso);
		mvwprintw(janelaFormulario, ((LINES-25)/2)+4, (COLS-60)/2,"Altura : %.2f",pessoa->medidas->altura);
		mvwprintw(janelaFormulario, ((LINES-25)/2)+5, (COLS-60)/2,"IMC : %.2f",pessoa->imc);		

	}else{
		mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "Usuário Não Encontrado:");			
	}
	refresh();
}
void controleBuscar(char *nome){
	if(strcmp(nome, "CANCELA") == 0 ){
		voltarMenu(0);
	}else if(strcmp(nome,"CONFIRMA") == 0){
		confirmaBuscar();	
	}else if(strcmp(nome,"VOLTAR") == 0){
		voltarMenu(0);
	}
}