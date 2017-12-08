// função para saber a quantidade de elementos em um vetor qualquer
#define size(a) (sizeof(a) / sizeof(a[0]))

// variavéis globais 
WINDOW *janelaPrincipal;
WINDOW *janelaFormulario;
WINDOW *janelaMenu;
FORM *formulario;
FIELD **campo;
MENU *menu;
ITEM **items;

// variavéis para controle de estado 
bool botao;
bool sair;
bool form = false;
bool atual[4]={false,false,false,false};

void exibirMenu(int linhas, int colunas, int y, int x, char **opcoes,int qtOpcoes);
void exibirFormulario(int linhas, int colunas, int y, int x, char **campos,int qtCampos);
void exibirInicio();
void apagaForm();
void removerPopup(void);
void voltarMenu(int i);
void verificaAtual(char *nome);
void controleOpcoes(ITEM *item);
void trocaBotao(void);
void controlador(int ch);

void exibirMenu(int linhas, int colunas, int y, int x, char **opcoes,int qtOpcoes){
	/*
		Procedimento exibirMenu:
		Argumentos : 
		linhas -> indica o a altura da janela
		colunas -> indica a largura da janela
		x, y -> indica a posição da janela na tela
		opcoes -> vetor de Strings com as opções do menu  
		qtOpcoes -> inteiro que indica a quantidade de opções no menu
	*/
	// variavéis auxiliares
	int cy = 0;
	int cx = 1; 
	int tmp;
	WINDOW *janela;
	/*
	1-> aloca na variavél janelaPrincipal uma nova janela com os argumentos passados para o procedimento 
			verifica através do procedimento assert se a janela foi alocada
			procedimento box() é chamado para desenhar uma caixa na tela
	*/
	janelaPrincipal = newwin(linhas, colunas, y, x);
	assert(janelaPrincipal != NULL);
	box(janelaPrincipal, 0, 0);
	
	/*
	2-> Aloca memória para o vetor de items que vão pertencer ao menu
			verifica se foi alocado corretamente
			para cada posição do vetor de items é alocado um novo elemento com os valore passados como argumento
			após alocar os itens é criado um novo menu com tais valores
	*/
	items = malloc(sizeof(ITEM *) * (qtOpcoes+1));
	assert(items);
	for(int i = 0; i < qtOpcoes; i++) {
		items[i] = new_item(opcoes[i], "");
		assert(items[i] != NULL);
	}
	items[qtOpcoes] = NULL;
	menu = new_menu(items);
	

	/*
	4-> determina onde o menu vai ser ancorado na tela
		verifica se ele foi ancorado corretamente
		desenha uma caixa na janela Menu
		define qual janela será exibida o menu
		define o formato do menu
		configura s dimensões

		altera o valor da variavél de estado "botao" para verdadeiro
	*/
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
	pos_menu_cursor(menu);
	botao = true;
}
void exibirFormulario(int linhas, int colunas, int y, int x, char **campos,int qtCampos){
	//variavéis auxiliares
	int cy = 0;
	int cx = 1; 
	int tmp;
	WINDOW *janela;
	// alloca memória para caber todos os campos passados por parâmetro para a função
	campo = malloc(sizeof(FIELD *) * (qtCampos+1));
	//verifica se foi alocado corretamente
	assert(campo);
	// laco de repetição pra preencher os valores passados por parâmetro para dentro dos campos alocados acima
	for (int i = 0; i < qtCampos; i++) {
		// instância um novo campo
		campo[i] = new_field(1, 20, cy, cx, 0, 0);
		// verifica se foi alocado corretamente
		assert(campo[i] != NULL);
		// define o valor do campo
		set_field_buffer(campo[i], 0, campos[i]);
		// caso i seja impar o campo é um expaço para preenchimento
		if (i % 2 == 1) {
			cy = cy+1;
			cx = 1;
			// define q o campo é sublinhado
			set_field_back(campo[i], A_UNDERLINE); 
			//caso i > 4 significa q os campos aṕos essa posição são do tipo float
			if(i > 4)
				// define o tipo do campo como numérico
				set_field_type(campo[i], TYPE_NUMERIC,2,0.0,1000.0);
		} else {
			// caso contrário o campo é a informação à ser preenchida
			cx = 50;
			field_opts_off(campo[i], O_ACTIVE);	
			
		
		}
	}
	//define q o ultimo campo é nulo
	campo[qtCampos] = NULL;
	//cria um novo formulário passando os campos criados acima como parâmetro
	formulario = new_form(campo);
	// define onde a janela do formulário vai aparecer e as suas dimenções
	janelaFormulario = derwin(janelaPrincipal, linhas-5, colunas-2, 1, 1);
	// desenha uma caixa na janela passada como parâmetro
	box(janelaFormulario, 0, 0);
	//verifica se as operções acima foram executadas corretamente
	assert(formulario != NULL && janelaFormulario != NULL);
	assert(formulario != NULL);
	// define em qual janela o formulário vai aparecer
	set_form_win(formulario, janelaFormulario);
	// define uma janela interna ao do formulário
	janela = derwin(janelaFormulario, formulario->rows+1, formulario->cols+1, 1, 1);
	assert(janela != NULL);
	// define que a janela acima pertence ao formulário
	set_form_sub(formulario, janela);
	//verifica se o formulário foi exibido corretamente
	assert(post_form(formulario) == E_OK);
	// altera o valor da variavél de controle para permitir a navegação entre o menu e o formulário
	form = true;
}
void exibirInicio(){
	/*
	Procedimento Responsavél por escrever na tela  a logo do programa
	*/
	apagaForm();	
	start_color();			
	init_pair(2, COLOR_RED, COLOR_BLACK);
	attron(COLOR_PAIR(1));
	mvwprintw(janelaFormulario,1, 7,"############   ############      #############   ######       ###");			
	mvwprintw(janelaFormulario,2, 7,"############   ##############    #############   ######       ###");
	mvwprintw(janelaFormulario,3, 7,"###            ###         ###   ###       ###   ###  ###     ###");
	mvwprintw(janelaFormulario,4, 7,"############   ##############    ###       ###   ###   ###    ###");
	mvwprintw(janelaFormulario,5, 7,"############   #############     #############   ###    ###   ###");
	mvwprintw(janelaFormulario,6, 7,"###            ###     ####      #############   ###     ###  ###");
	mvwprintw(janelaFormulario,7, 7,"###            ###      ###      ###       ###   ###       ######");
	mvwprintw(janelaFormulario,8, 7,"###            ###       ###     ###       ###   ###       ######");

	mvwprintw(janelaFormulario,10, 24,"###############   #############");
	mvwprintw(janelaFormulario,11, 24,"###############   #############");
	mvwprintw(janelaFormulario,12, 24,"###               ###       ###");
	mvwprintw(janelaFormulario,13, 24,"###     #######   ###       ###");
	mvwprintw(janelaFormulario,14, 24,"###     #######   ###       ###");
	mvwprintw(janelaFormulario,15, 24,"###         ###   ###       ###");
	mvwprintw(janelaFormulario,16, 24,"###############   #############");
	mvwprintw(janelaFormulario,17, 24,"###############   #############");
	
	attroff(COLOR_PAIR(1));
	
}
void apagaForm(){
	/*
	Tal procedimento apaga qualquer valor que esteja sendo exibido na janela do formulário
	*/
	char *campos[] = {""};
	exibirFormulario(24, 80, (LINES-25)/2, (COLS-81)/2, campos, size(campos));
	unpost_form(formulario);
	for (int i = 0; campo[i] != NULL; i++) {
		free_field(campo[i]);
	}
	free_form(formulario);
	delwin(janelaFormulario);
	form = false;
}
void removerPopup(void){
	/*
	Procedimento responsavél por apagar os valores contidos dentro das janelas
	*/
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
	exibirInicio();
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

		case 10: //Enter
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
