#include "includes.h"
/*
	FRANGO -> Fup Ncurses GYM Aplication
*/
int main(){	
	char *opcoes[]= {"Cadastrar","Atualizar","Remover","Buscar","Sair"};
	sistema = novoSistema();
	int ch;
	initscr();
	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	exibirMenu(24, 80, (LINES-25)/2, (COLS-81)/2, opcoes, size(opcoes));
	exibirInicio(24,80,(LINES)/2, (COLS)/2);
	refresh();
	wrefresh(janelaPrincipal);
	wrefresh(janelaFormulario);
	wrefresh(janelaMenu);
	while ((ch = getch()) != KEY_F(10)){
		controlador(ch);
		if(sair) break;
	}
	removerPopup();
	endwin();

	return 0;
}
