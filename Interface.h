
#define size(a) (sizeof(a) / sizeof(a[0]))

WINDOW *janelaPrincipal, *janelaFormulario, *janelaMenu;
FORM *formulario;
FIELD **campo;
MENU *menu;
ITEM **items;

bool botao;
bool sair;
bool atual[4]={false,false,false,false};
bool form = false;
void exibirMenu(int linhas, int colunas, int y, int x, char **opcoes,int qtOpcoes){
	int cy = 0;
	int cx = 1; 
	int tmp;
	WINDOW *janela;
	
	
	janelaPrincipal = newwin(linhas, colunas, y, x);
	assert(janelaPrincipal != NULL);
	box(janelaPrincipal, 0, 0);

	items = malloc(sizeof(ITEM *) * (qtOpcoes+1));
	assert(items);

	for(int i = 0; i < qtOpcoes; i++) {
		items[i] = new_item(opcoes[i], "");
		assert(items[i] != NULL);
	}
	items[qtOpcoes] = NULL;
	menu = new_menu(items);
	janelaMenu = derwin(janelaPrincipal, 3, colunas-2, linhas-4, 1);
	assert(menu != NULL && janelaMenu != NULL);
	box(janelaMenu, 0, 0);
	set_menu_win(menu,janelaMenu);
	set_menu_format(menu, 1, qtOpcoes);
	tmp = menu->fcols * (menu->namelen + menu->spc_rows);
	tmp--;
	janela = derwin(janelaMenu, 1, tmp, 1, (colunas-3-tmp)/2);
	assert(janela != NULL);
	set_menu_sub(menu, janela);
	set_menu_mark(menu, "");


	assert(post_menu(menu) == E_OK);
	botao = true;
	pos_menu_cursor(menu);
}
void exibirInicio(int linhas, int colunas, int y, int x){
	mvprintw(x,y,"FUP GYN");
}
void exibirFormulario(int linhas, int colunas, int y, int x, char **campos,int qtCampos){
	int cy = 0;
	int cx = 1; 
	int tmp;
	WINDOW *janela;
	
	campo = malloc(sizeof(FIELD *) * (qtCampos+1));
	assert(campo);

	for (int i = 0; i < qtCampos; i++) {
		campo[i] = new_field(1, 20, cy, cx, 0, 0);
		assert(campo[i] != NULL);
		set_field_buffer(campo[i], 0, campos[i]);

		if (i % 2 == 1) {
			cy = cy+1;
			cx = 1;
		
			
			set_field_back(campo[i], A_UNDERLINE); 
			
			if(i > 4)
				set_field_type(campo[i], TYPE_NUMERIC,2,0.0,1000.0);
		} else {
			cx = 50;
			field_opts_off(campo[i], O_ACTIVE);	
			//field_opts_on(campo[i], O_ACTIVE);
			//field_opts_on(campo[i], TYPE_NUMERIC);
		
		}
	}

	campo[qtCampos] = NULL;
	formulario = new_form(campo);
	assert(formulario != NULL);
	janelaFormulario = derwin(janelaPrincipal, linhas-5, colunas-2, 1, 1);
	box(janelaFormulario, 0, 0);
	assert(formulario != NULL && janelaFormulario != NULL);
	set_form_win(formulario, janelaFormulario);
	janela = derwin(janelaFormulario, formulario->rows+1, formulario->cols+1, 1, 1);
	assert(janela != NULL);
	set_form_sub(formulario, janela);
	assert(post_form(formulario) == E_OK);
	form = true;
}
void removerPopup(void){
	unpost_menu(menu);
	if(form){
	
		unpost_form(formulario);

		for (int i = 0; campo[i] != NULL; i++) {
			free_field(campo[i]);
		}

		
		free_form(formulario);
		delwin(janelaFormulario);
		form = false;

	}
	for (int i = 0; items[i] != NULL; i++) {
			free_item(items[i]);
	}
		free_menu(menu);
		delwin(janelaMenu);
		delwin(janelaPrincipal);	
	
}
void voltarMenu(int i){
	removerPopup();
	char *opcoes[]= {"Cadastrar","Atualizar","Remover","Buscar","Sair"};
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
	atual[i] = false;
}
void verificaAtual(char *nome){
	if(atual[0]){
		controleCadastro(nome);
	}else if(atual[1]){
		controleAtualiza(nome);
	}else if(atual[2]){
		controleRemove(nome);
	}else if(atual[3]){
		controleBuscar(nome);
	}
}
void controleOpcoes(ITEM *item){
	char *nome = item_name(item);
    if (strcmp(nome, "Cadastrar") == 0 ) {
		exibirCadastroForm();
	}else if(strcmp(nome,"Atualizar") == 0){
		exibirAtualizarForm();
	}else if(strcmp(nome,"Remover") == 0){
		exibirRemoverForm();
	}else if(strcmp(nome,"Buscar") == 0){
		exibirBuscarForm();
	}else if (strcmp(nome, "Sair") == 0){
		sair = true;
	}else{
		verificaAtual(nome);
	}
	nome = NULL;
	refresh();
}
void trocaBotao(void){
	
	form_driver(formulario, REQ_PREV_FIELD);
	form_driver(formulario, REQ_NEXT_FIELD);

	menu_driver(menu, REQ_FIRST_ITEM);
	botao = true;
	set_menu_fore(menu, A_REVERSE); 
}
void controlador(int ch){
	switch (ch) {
		case KEY_DOWN:
		if(form){
			if (botao)
				break;

			if (formulario->current == campo[formulario->maxfield-1])
				trocaBotao();
			else
				form_driver(formulario, REQ_NEXT_FIELD);
			break;
		}
		case KEY_UP:
		if(form){
			if (botao) {
				botao = false;
				set_menu_fore(menu, A_NORMAL); 
			} else
				form_driver(formulario, REQ_PREV_FIELD);
			break;
		}
		case KEY_LEFT:
			if (botao)
				menu_driver(menu, REQ_LEFT_ITEM);
			else
				form_driver(formulario, REQ_LEFT_FIELD);
			break;

		case KEY_RIGHT:
			if (botao)
				menu_driver(menu, REQ_RIGHT_ITEM);
			else
				form_driver(formulario, REQ_RIGHT_FIELD);
			break;

		case 10:
			if (!botao)
				trocaBotao();
			else
				
				controleOpcoes(current_item(menu));
				
			break;

		default:
			if (!botao)
				form_driver(formulario, ch);

			break;

	}

	if (botao)
		pos_menu_cursor(menu);
	else
		pos_form_cursor(formulario);

	wrefresh(janelaPrincipal);
}