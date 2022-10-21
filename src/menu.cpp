#include "menu.h"

int menu_principal(void)
{
    int escolha;

    do
    {
        cout << "\n*******************Menu Principal************************* \n"
             << "ATENCAO: Necessario gerar solucao inicial antes de refinar\n"
             << "                1. Gere solucao inicial \n"
             << "                2. Descida com Best Improvement\n"
             << "                3. Descida randomica \n"
             << "                4. LAHC \n"
             << "                0. Sair \n"
             << "                Escolha: ";
        cin >> escolha;
    } while (escolha < 0 || escolha > 4);
    return escolha;
}

/* Menu de geracao de uma solucao inicial */
int menu_solucao_inicial(void)
{
    int escolha;

    do
    {
        cout << "\n************Geracao da Solucao Inicial**************** \n"
             << "                1. Gulosa \n"
             << "                2. Aleatoria \n"
             << "                escolha: ";
        cin >> escolha;
    } while (escolha < 1 || escolha > 2);
    return escolha;
}