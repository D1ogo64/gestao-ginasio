//Autores: Diogo Rebelo, Arthur Santos
//Turma: 10ºF

#include <iostream>
#include <iomanip>
#include <windows.h>
#include <unistd.h>

using namespace std;

// ================== STRUCT ==================
struct Socio {
    int id;
    string nome;
    int idade;
    string plano;
    bool ativo;
};

// ================== CONSTANTES ==================
const int MAX_SOCIOS = 100;

// ================== VARIÁVEIS GLOBAIS ==================
Socio socios[MAX_SOCIOS];
int totalSocios = 0;
int proximoID = 1;

// ================== FUNÇÕES ==================

// Menu
void menu() {
    cout << "\n+------------------------------------------+\n";
    cout << "|           GESTAO DE GINASIO              |\n";   
    cout << "+------------------------------------------+\n";
    cout << "   1. Adicionar socio\n";
    cout << "   2. Listar socios\n";
    cout << "   3. Consultar socio\n";
    cout << "   4. Alterar socio\n";
    cout << "   5. Eliminar socio\n";
    cout << "   0. Sair\n";
    cout << "+------------------------------------------+\n";
    cout << "Opcao: ";
}

// Procurar por ID
int procurarPorID(int id) {
    for (int i = 0; i < totalSocios; i++) {
        if (socios[i].id == id) {
            return i;
        }
    }
    return -1;
}

// Adicionar sócio
void adicionarSocio() {
    if (totalSocios >= MAX_SOCIOS) {
        cout << "\nLimite de socios atingido!\n";
        return;
    }

    Socio s;

    s.id = proximoID++;

    cout << "\nNome: ";
    cin.ignore();
    getline(cin, s.nome);

    cout << "\nIdade: ";
    cin >> s.idade;

    while (s.idade <= 0) {
        cout << "\nIdade invalida. Introduz novamente: ";
        cin >> s.idade;
    }

    cout << "\nTipos de plano disponiveis:\n";
    cout << "1. Plano Basico\n";
    cout << "2. Plano Intermedio\n";
    cout << "3. Plano Premium\n";

    cout << "\nPlano: ";
    cin.ignore();
    getline(cin, s.plano);

    s.ativo = true;

    socios[totalSocios++] = s;

    cout << "\nSocio adicionado com sucesso!\n";

    sleep(2);
    system("cls");
}

// Listar sócios
void listarSocios() {
    if (totalSocios == 0) {
        cout << "\nNenhum socio registado.\n";
        return;
    }

    cout << "\n===== LISTA DE SOCIOS =====\n\n";

    cout << left << setw(5) << "ID"
         << setw(20) << "Nome"
         << setw(10) << "Idade"
         << setw(15) << "Plano"
         << setw(10) << "Estado" << endl;

    cout << "-------------------------------------------------------------\n";

    for (int i = 0; i < totalSocios; i++) {
        cout << left << setw(5) << socios[i].id
             << setw(20) << socios[i].nome
             << setw(10) << socios[i].idade
             << setw(15) << socios[i].plano
             << setw(10) << (socios[i].ativo ? "Ativo" : "Inativo")
             << endl;
    }
}

// Consultar sócio
void consultarSocio() {
    int id;
    cout << "ID do socio: ";
    cin >> id;

    int pos = procurarPorID(id);

    if (pos == -1) {
        cout << "\nSocio nao encontrado.\n";
        return;
    }

    cout << "\n===== DADOS DO SOCIO =====\n";
    cout << "ID: " << socios[pos].id << endl;
    cout << "Nome: " << socios[pos].nome << endl;
    cout << "Idade: " << socios[pos].idade << endl;
    cout << "Plano: " << socios[pos].plano << endl;
    cout << "Estado: " << (socios[pos].ativo ? "Ativo" : "Inativo") << endl;
}

// Alterar sócio
void alterarSocio() {
    int id;
    cout << "ID do socio: ";
    cin >> id;

    int pos = procurarPorID(id);

    if (pos == -1) {
        cout << "\nSocio nao encontrado.\n";
        return;
    }

    cout << "Novo nome: ";
    cin.ignore();
    getline(cin, socios[pos].nome);

    cout << "Nova idade: ";
    cin >> socios[pos].idade;

    while (socios[pos].idade <= 0) {
        cout << "\nIdade invalida. Introduz novamente: ";
        cin >> socios[pos].idade;
    }

    cout << "Novo plano: ";
    cin.ignore();
    getline(cin, socios[pos].plano);

    cout << "Socio atualizado com sucesso!\n";
}

// Eliminar sócio
void eliminarSocio() {
    int id;
    cout << "ID do socio: ";
    cin >> id;

    int pos = procurarPorID(id);

    if (pos == -1) {
        cout << "Socio nao encontrado.\n";
        return;
    }

    for (int i = pos; i < totalSocios - 1; i++) {
        socios[i] = socios[i + 1];
    }

    totalSocios--;

    cout << "Socio eliminado com sucesso!\n";
}

// Função para definir o tamanho da consola
void setConsoleSize(int width, int height) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD coord = {(SHORT)width, (SHORT)height};
    SetConsoleScreenBufferSize(hConsole, coord);
    SMALL_RECT rect = {0, 0, (SHORT)(width - 1), (SHORT)(height - 1)};
    SetConsoleWindowInfo(hConsole, TRUE, &rect);
}

// ================== MAIN ==================
int main() {
    setConsoleSize(120, 40);

    int opcao;

    do {
        menu();
        cin >> opcao;

        switch (opcao) {
            case 1:
                adicionarSocio();
                break;
            case 2:
                listarSocios();
                break;
            case 3:
                consultarSocio();
                break;
            case 4:
                alterarSocio();
                break;
            case 5:
                eliminarSocio();
                break;
            case 0:
                cout << "\nA sair do programa...\n";
                break;
            default:
                cout << "\nOpcao invalida!\n";
        }

    } while (opcao != 0);

    return 0;
}