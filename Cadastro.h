void exibirCadastroForm(){
			
		char *opcoes[] = {"CANCELA","CONFIRMA"};
		exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, 2);
		char *campos[] = {"Nome:"," ", 
						  "Sexo (0 F, 1 M):"," ", 
						  "Peso:"," ", 
						  "Altura em cm"," ",
						  "Braço Direito"," ",
						  "Braço Esquerdo"," ",
						  "Perna Direita"," ",
						  "Perna Esquerda"," ",
						  "Panturrilha Direita"," ",
						  "Panturrilha Esquerda"," ",
						  "Abdomen"," ",
						  "Cintura"," ",
						  "Peito"," "};
		
		exibirFormulario(24, 80, (LINES-25)/2, (COLS-81)/2, campos, size(campos));
		atual[0] = true;
}

void confirmaCadastro(){
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
	Pessoa *nova = novaPessoa(field_buffer(campo[1],0),atoi(field_buffer(campo[2],0)),medidas,treino,atoi(field_buffer(campo[3],0)));
	cadastrarPessoa(sistema,nova);
	float imc = calculaImc(medidas->peso,medidas->altura);
	char cond[40];
	condicaoImc(imc,nova->sexo,cond);
    
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
	mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "Usuário Cadastrado:");			
	mvwprintw(janelaFormulario, ((LINES-25)/2)+1, (COLS-80)/2,"%s",nova->nome);
	mvwprintw(janelaFormulario,((LINES-25)/2)+2, (COLS-80)/2,"Seu imc é :%.2f ele está %s",imc,cond);
	refresh();
		
}

void controleCadastro(char *nome){
	if(strcmp(nome, "CANCELA") == 0 ){
		voltarMenu(0);
	}else if(strcmp(nome,"CONFIRMA") == 0){
		confirmaCadastro();	
	}else if(strcmp(nome,"VOLTAR") == 0){
		voltarMenu(0);
	}
}