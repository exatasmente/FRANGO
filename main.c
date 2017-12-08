#include "includes.h"
/*
	FRANGO -> Fup Ncurses GYM Aplication
*/
int main(){	
	// Opções do Menu Inicial
	char *opcoes[]= {"Cadastrar","Atualizar","Remover","Buscar","Sair"};

	//Aloca memória para o sistema
	sistema = novoSistema();

	//entrada do usuário
	int ch;
	//inicializa a biblioteca Ncurses
	initscr();
	
	noecho();
	cbreak();
	keypad(stdscr, TRUE);

	//Prepara a exibição do menu inicial
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
	exibirInicio();
	mvwprintw(janelaFormulario,18, 26,"FUP Ncurses GYN Application");
	mvwprintw(janelaFormulario,18, 74,"v0.1");
	//atualiza a tela aṕos a exibição do menu
	refresh();
	wrefresh(janelaPrincipal);
	wrefresh(janelaFormulario);
	wrefresh(janelaMenu);

	//loop que controla as entradas do usuário no menu e formulários
	while(ch =getch()){
		mvwprintw(janelaFormulario,18, 26,"FUP Ncurses GYN Application");
		mvwprintw(janelaFormulario,18, 74,"v0.1");
		wrefresh(janelaFormulario);
		controlador(ch);
		if(sair)
			 break;
	}

	//apaga as janelas da memória
	removerPopup();
	
	//finaliza a biblioteca Ncurses
	endwin();

	return 0;
}
