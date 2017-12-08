void exibirCadastroForm(){
	char *opcoes[] = {"CANCELA","CONFIRMA"};
	char *campos[] = {"Nome:"," ", 
						  "Sexo (0 F, 1 M):"," ", 
						  "Peso:"," ", 
						  "Altura em metros"," ",
						  "Braço Direito"," ",
						  "Braço Esquerdo"," ",
						  "Perna Direita"," ",
						  "Perna Esquerda"," ",
						  "Panturrilha Direita"," ",
						  "Panturrilha Esquerda"," ",
						  "Abdomen"," ",
						  "Cintura"," ",
						  "Peito"," "};
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, 2);
    exibirFormulario(24, 80, (LINES-25)/2, (COLS-81)/2, campos, size(campos));
	atual[0] = true;
}
void confirmaCadastro(){
	char *objetivo[14];
	Treino *treino;
	Pessoa *nova;
	float imc;
	char cond[40];
	char *opcoes[]= {"VOLTAR"};
	
	

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
					
		
	
	defineObjetivo(sistema,medidas,atoi(field_buffer(campo[2],0)),objetivo);
	nova = novaPessoa(field_buffer(campo[1],0),atoi(field_buffer(campo[2],0)),medidas,atoi(field_buffer(campo[3],0)));
	nova->treino = geraTreino(sistema,objetivo);
	
	strcpy(nova->objetivo,objetivo);
	cadastrarPessoa(sistema,nova);

	imc = calculaImc(medidas->peso,medidas->altura);
	
	condicaoImc(imc,nova->sexo,cond);
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
	apagaForm();
	mvwprintw(janelaFormulario,(LINES-25)/2, (COLS-80)/2, "Usuário Cadastrado:");			
	mvwprintw(janelaFormulario, ((LINES-25)/2)+1, (COLS-80)/2,"%s",nova->nome);
	mvwprintw(janelaFormulario,((LINES-25)/2)+2, (COLS-80)/2,"Seu imc é :%.2f ele está %s",imc,cond);
	mvwprintw(janelaFormulario, ((LINES-25)/2)+3, (COLS-80)/2,"Objetivo: %s",objetivo);
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