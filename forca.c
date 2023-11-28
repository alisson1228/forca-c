#include <stdio.h>
#include <stdlib.h>
#include <time.h>

enum direcao {DIREITO, ESQUERDO, CIMA, BAIXO};

int str_len(char str[]);

void printforca(char forca[][9], int tentativas, int erros);

void printespacos(char palavra[], int letras, char espacos[]);

void printtela(char forca[][9], char palavra[], int letras, char espacos[], int tentativas, int erros);

void tentar(char forca[][9], char palavra[], int letras, char espacos[], int *tentativas, int *erros);

void errou(char forca[][9], int erros);

void cabeca(char forca[][9]);

void tronco(char forca[][9]);

void menbros(char forca[][9], enum direcao vertical, enum direcao horizontal);

int validar(char palavra[], char espacos[], int letras);

void startpalavra(char palavra[]);

int main() {

    char palavra[30];
    int tentativas = 0;
    int erros = 0;

    startpalavra(palavra);

    int letras = str_len(palavra) - 1;
    char espacos[letras];

    for(int i = 0; i < letras; i++) {
        espacos[i] = ' ';
    }

    char forca[9][9] = {
        " ______  ",
        "|     |  ",
        "|        ",
        "|        ",
        "|        ",
        "|        ",
        "|        ",
        "|        ",
        "|        "
    };

    do {
        printtela(forca, palavra, letras, espacos, tentativas, erros);

        if (erros == 6) {
            printf("Você perdeu! A palavra era: %s\n", palavra);
            break;
        } else if (validar(palavra, espacos, letras) == 1) {
            printf("Parabéns! Você adivinhou a palavra!\n");
            break;
        } else {
            tentar(forca, palavra, letras, espacos, &tentativas, &erros);
        }

    } while (1);

}

void startpalavra(char palavra[]) {
    srand(time(NULL));

    FILE *arquivo;
    int nivel;
    int line = (rand() % 40) + 1;

    printf("JOGO DA FORCA\n1) Facil\n2) Medio\n3) Dificil\n\nescolha um nivel: ");

    scanf("%d", &nivel);

    switch(nivel) {
        case 1:
            arquivo = fopen("facil.txt", "r");
            break;
        case 2:
            arquivo = fopen("medio.txt", "r");
            break;
        case 3:
            arquivo = fopen("dificil.txt", "r");
            break;
    }


    for(int i = 0; i < line; i++){
        fgets(palavra, 30, arquivo);
    }

    fclose(arquivo);
}

int str_len(char str[]) {
    int i = 0;
    int cont = 0;

    while (str[i] != '\0') {
        if(str[i] >= 0 && str[i] <= 127) {
            i++;
            cont++;
        } else {
            i += 2;
            cont++;
        }

    }

    return cont;
}

int validar(char palavra[], char espacos[], int letras) {
    for(int i = 0; i < letras; i++) {
        if(palavra[i] != espacos[i]) {
            return 0;
        }
    }

    return 1;
}

void printforca(char forca[][9], int tentativas, int erros) {
    for(int i = 0; i < 9; i++) {
        printf("   ");
        for(int j = 0; j < 9; j++) {
            printf("%c", forca[i][j]);
        }

        if(i == 1) {
            printf("        Tentativas: %d\n", tentativas);
        } else if(i == 2) {
            printf("        Erros: %d\n", erros);
        } else {
            printf("\n");
        }

    }
}

void printespacos(char palavra[], int letras, char espacos[]) {

     for (int i = 0; i < letras; i++) {
        if (espacos[i] == ' ') {
            printf("_ ");
        } else {
            printf("%c ", espacos[i]);
        }
    }
    printf("\n");
}

void printtela(char forca[][9], char palavra[], int letras, char espacos[], int tentativas, int erros) {
    system("clear");

    printforca(forca, tentativas, erros);

    printf("\n        ");

    printespacos(palavra, letras, espacos);

    printf("\n");
}

void tentar(char forca[][9], char palavra[], int letras, char espacos[], int *tentativas, int *erros) {
    char letra;
    int acertou = 0;

    printf("Digite uma letra: ");
    scanf(" %c", &letra);

    for (int i = 0; i < letras; i++) {
        if (palavra[i] == letra) {
            espacos[i] = letra;
            acertou = 1;
        }
    }

    if (acertou == 0) {
        (*erros)++;
        errou(forca, *erros);
    }
    (*tentativas)++;
}

void errou(char forca[][9], int erros) {
    switch(erros) {
        case 1:
            cabeca(forca);
            break;

        case 2:
            tronco(forca);
            break;

        case 3:
            menbros(forca, DIREITO, CIMA);
            break;

        case 4:
            menbros(forca, ESQUERDO, CIMA);
            break;

        case 5:
            menbros(forca, DIREITO, BAIXO);
            break;

        case 6:
            menbros(forca, ESQUERDO, BAIXO);
            break;
    }
}

void cabeca(char forca[][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(i == 2 && j == 5) {
                forca[i][j] = '/';
            } else if(i == 2 && (j == 6)) {
                forca[i][j] = ' ';
            } else if(i == 2 && j == 7) {
                forca[i][j] = '\\';
            } else if(i == 3 && (j == 5)) {
                forca[i][j] = '\\';
            }else if(i == 3 && j == 6) {
                forca[i][j] = ' ';
            } else if(i == 3 && j == 7) {
                forca[i][j] = '/';
            }
        }
    }
}

void tronco(char forca[][9]) {
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if((i == 4 || i == 5 || i == 6) && j == 6) {
                forca[i][j] = '|';
            }
        }
    }
}

void menbros(char forca[][9], enum direcao vertical, enum direcao horizontal) {
    char part;
    int post1;
    int post2;
    int post3;
    int post4;

    switch(vertical) {
        case DIREITO:
            part = '\\';
            post1 = 7;
            post2 = 8;
            break;
        case ESQUERDO:
            part = '/';
            post1 = 5;
            post2 = 4;
            break;
    }

    switch(horizontal) {
        case CIMA:
            post3 = 4;
            post4 = 5;
            break;
        case BAIXO:
            post3 = 7;
            post4 = 8;
            break;
    }

    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            if(i == post3 && j == post1) {
                forca[i][j] = part;
            } else if(i == post4 && j == post2) {
                forca[i][j] = part;
            }
        }
    }
}
