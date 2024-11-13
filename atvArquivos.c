#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAM_VIDEOSFAV 100
#define TAM_VIDEOS 5
#define TAM_USUARIOS 5
#define TAM_NOMES 100

struct ArquivoVideo {
    int id;
    char nomeVideo[TAM_NOMES];
    char genero[TAM_NOMES];
};

struct ArquivoUsuario {
    char nomeUsuario[TAM_NOMES];
    int videosFav[TAM_VIDEOSFAV];
};

void lerStr(char *str, int tam);
void preencherZero(struct ArquivoVideo videos[], struct ArquivoUsuario usuarios[], int tam, int tam2);
void cadastrarVideo(struct ArquivoVideo videos[], int tam);

int main() {
    struct ArquivoVideo videos[TAM_VIDEOS];
    struct ArquivoUsuario usuarios[TAM_USUARIOS];
    int escolha;
    preencherZero(videos, usuarios, TAM_VIDEOS, TAM_VIDEOSFAV);
    do {
        printf("O QUE VOCE DESEJA FAZER?\n");
        printf("1 - Cadastrar video\n");
        printf("2 - Cadastrar usuario\n");
        printf("3 - Ler video especifico\n");
        printf("4 - Ler usuario especifico\n");
        printf("5 - Ler todos os videos e usuarios do sistema\n");
        printf("6 - Atualizar dados de um video\n");
        printf("7 - Atualizar dados de um usuario\n");
        printf("8 - Remover video\n");
        printf("9 - Remover usuario\n");
        printf("10 - Relatorio de videos favoritos\n");
        printf("11 - Relatorio de videos cadastrados\n");
        printf("12 - Relatorio de usuarios\n");
        printf("0 - Fechar programa\n");
        scanf("%d", &escolha);
        switch(escolha) 
        {
        case 1:
            cadastrarVideo(videos, TAM_VIDEOS);
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 11:
        case 12:
        }
    } while(escolha != 0);

    return 0;
}

void lerStr(char *str, int tam) {
    fgets(str, tam, stdin);
    int len = strlen(str);
    if (str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

void preencherZero(struct ArquivoVideo videos[], struct ArquivoUsuario usuarios[], int tam, int tam2) {
    for(int i = 0; i < tam; ++i) {
        videos[i].id = 0;
        for(int j = 0; j < tam2; ++j) {
            usuarios[i].videosFav[j] = 0;
        }
    }
}

void cadastrarVideo(struct ArquivoVideo videos[], int tam) {
    char temp[TAM_NOMES];
    int i = 0;
    while(i < tam && videos[i].id != 0) {
        ++i;
    }
    if(i == tam) {
        printf("Limite de vídeo atingido.\n");
        return;
    }
    printf("CADASTRO VIDEO\n");
    printf("Video ID: ");
    scanf("%d", &videos[i].id);
    lerStr(temp, TAM_NOMES);
    printf("Nome do video: ");
    lerStr(videos->nomeVideo, TAM_NOMES);
    printf("Genero: ");
    lerStr(videos->genero, TAM_NOMES);
    FILE *arqVideos = fopen("ArquivoVideos.bin", "ab");
    if(arqVideos == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    if (fwrite(&videos[i], sizeof(struct ArquivoVideo), 1, arqVideos) != 1) {
        printf("Erro ao escrever no arquivo.\n");
    }

    fclose(arqVideos);
}