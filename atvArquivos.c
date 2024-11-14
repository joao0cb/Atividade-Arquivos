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
    int id;
    char nomeUsuario[TAM_NOMES];
    int videosFav[TAM_VIDEOSFAV];
};

void lerStr(char *str, int tam);
void preencherZero(struct ArquivoVideo videos[], struct ArquivoUsuario usuarios[], int tam, int tam2);
void cadastrarVideo(struct ArquivoVideo videos[], int tam);
void cadastrarUsuario(struct ArquivoUsuario usuarios[], int tam);
void lerVideoEspecifico(int idVideo);
void lerUsuarioEspecifico(int idUsuario, int tam);
void lerUsuariosVideos(int tam);
void atualizarDadosVideo(int idVideo);
void atualizarDadosUsuario(int idUsuario, int tam);
void removerVideo(int idVideo);

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
            cadastrarUsuario(usuarios, TAM_USUARIOS);
        case 3:
            int idVideo;
            printf("Digite o ID do video: ");
            scanf("%d", &idVideo);
            lerVideoEspecifico(idVideo);
        case 4:
            int idUsuario;
            printf("Digite o ID do usuario: ");
            scanf("%d", &idUsuario);
            lerUsuarioEspecifico(idUsuario, TAM_VIDEOSFAV);
        case 5:
            lerUsuariosVideos(TAM_VIDEOSFAV);
        case 6:
            int idVideo;
            printf("Digite o ID do video: ");
            scanf("%d", &idVideo);
            atualizarDadosVideo(idVideo);
        case 7:
            int idUsuario;
            printf("Digite o ID do usuario: ");
            scanf("%d", &idUsuario);
            atualizarDadosUsuario(idUsuario, TAM_VIDEOSFAV);
        case 8:
            int idVideo;
            printf("Digite o ID do video que deseja remover: ");
            scanf("%d", &idVideo);
            removerVideo(idVideo);
            /*
        case 9:
        case 10:
        case 11:
        case 12:
    */
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
        usuarios[i].id = 0;
        usuarios[i].nomeUsuario[i] = '\0';
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
    lerStr(videos[i].nomeVideo, TAM_NOMES);
    printf("Genero: ");
    lerStr(videos[i].genero, TAM_NOMES);
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

void cadastrarUsuario(struct ArquivoUsuario usuarios[], int tam) {
    char temp[TAM_NOMES];
    int i = 0, idVideo, idUsuario;
    while(i < tam && usuarios[i].nomeUsuario[0] != '\0') {
        ++i;
    }
    if(i == tam) {
        printf("Limite de usuarios atingido.\n");
        return;
    }
    printf("CADASTRO USUARIO\n");
    printf("Nome do usuario: ");
    lerStr(usuarios[i].nomeUsuario, TAM_NOMES);
    printf("ID do usuario: ");
    scanf("%d", &idUsuario);
    printf("ID dos videos favoritos (Um por vez. 0 para encerrar): ");
    for(int j = 0; j < tam; ++j) {
        scanf("%d", &idVideo);
        if(idVideo == 0) {
            break;
        }
        usuarios[i].videosFav[j] = idVideo;
    }
    lerStr(temp, TAM_NOMES);
    FILE *arqUsuarios = fopen("ArquivoUsuarios.bin", "ab");
    if(arqUsuarios == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    if (fwrite(&usuarios[i], sizeof(struct ArquivoUsuario), 1, arqUsuarios) != 1) {
        printf("Erro ao escrever no arquivo.\n");
    }
    fclose(arqUsuarios);
}

void lerVideoEspecifico(int idVideo) {
    struct ArquivoVideo video;
    int encontrado = 0;
    FILE *arqVideos = fopen("ArquivoVideos.bin", "rb");
    if (arqVideos == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    while(fread(&video, sizeof(struct ArquivoVideo), 1, arqVideos)) {
        if(video.id == idVideo) {
            printf("Video encontrado.\n");
            printf("ID: %d\n", video.id);
            printf("Nome do video: %s\n", video.nomeVideo);
            printf("Genero: %s\n", video.genero);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) {
        printf("Video com o ID %d nao encontrado no arquivo.\n", video.id);
    }
    fclose(arqVideos);
}

void lerUsuarioEspecifico(int idUsuario, int tam) {
    struct ArquivoUsuario usuario;
    int encontrado = 0;
    FILE *arqUsuarios = fopen("ArquivoUsuarios.bin", "rb");
    if (arqUsuarios == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    while(fread(&usuario, sizeof(struct ArquivoUsuario), 1, arqUsuarios)) {
        if(usuario.id == idUsuario) {
            printf("Usuario encontrado.\n");
            printf("ID: %d\n", usuario.id);
            printf("Nome do video: %s\n", usuario.nomeUsuario);
            printf("Videos favoritados: ");
            for(int i = 0; i < tam && usuario.videosFav[i] != 0; i++) {
                printf("%d ", usuario.videosFav[i]);
            }
            printf("\n");
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) {
        printf("Usuario com o ID %d nao encontrado no arquivo.\n", usuario.id);
    }
    fclose(arqUsuarios);
}

void lerUsuariosVideos(int tam) {
    struct ArquivoUsuario usuario;
    struct ArquivoVideo video;

    FILE *arqUsuarios = fopen("ArquivoUsuarios.bin", "rb");
    if (arqUsuarios == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    printf("USUARIOS\n\n");
    while(fread(&usuario, sizeof(struct ArquivoUsuario), 1, arqUsuarios)) {
        if(usuario.id != 0) {
            printf("ID: %d\n", usuario.id);
            printf("Nome do usuario: %s\n", usuario.nomeUsuario);
            printf("Videos favoritados: ");
            for(int i = 0; i < tam && usuario.videosFav[i] != 0; i++) {
                printf("%d ", usuario.videosFav[i]);
            }
            printf("\n\n");
        }
    }
    fclose(arqUsuarios);

    FILE *arqVideos = fopen("ArquivoVideos.bin", "rb");
    if (arqVideos == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    printf("VIDEOS\n\n");
    while(fread(&video, sizeof(struct ArquivoVideo), 1, arqVideos)) {
        if(video.id != 0) {
            printf("ID: %d\n", video.id);
            printf("Nome do video: %s\n", video.nomeVideo);
            printf("Genero: %s\n", video.genero);
            printf("\n\n");
        }
    }
    fclose(arqVideos);

}

void atualizarDadosVideo(int idVideo) {
    struct ArquivoVideo video;
    int encontrado = 0;
    FILE *arqVideos = fopen("ArquivoVideos.bin", "rb+");
    if (arqVideos == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    while(fread(&video, sizeof(struct ArquivoVideo), 1, arqVideos)) {
        if(video.id == idVideo) {
            printf("Video encontrado. Insira os novos dados.\n");
            printf("Nome do video: ");
            lerStr(video.nomeVideo, TAM_NOMES);
            printf("Genero: ");
            lerStr(video.genero, TAM_NOMES);
            fseek(arqVideos, -sizeof(struct ArquivoVideo), SEEK_CUR);
            fwrite(&video, sizeof(struct ArquivoVideo), 1, arqVideos);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) {
        printf("Video com o ID %d nao encontrado no arquivo.\n", video.id);
    }
    fclose(arqVideos);
}

void atualizarDadosUsuario(int idUsuario, int tam) {
    struct ArquivoUsuario usuario;
    int encontrado = 0, idVideo;
    FILE *arqUsuarios = fopen("ArquivoUsuarios.bin", "rb+");
    if (arqUsuarios == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }
    while(fread(&usuario, sizeof(struct ArquivoUsuario), 1, arqUsuarios)) {
        if(usuario.id == idUsuario) {
            printf("Usuario encontrado. Insira os novos dados.\n");
            printf("Nome do usuario: ");
            lerStr(usuario.nomeUsuario, TAM_NOMES);
            printf("Genero: ");
            printf("Videos favoritados: ");
            printf("ID dos videos favoritos (Um por vez. 0 para encerrar): ");
            for(int j = 0; j < tam; ++j) {
                scanf("%d", &idVideo);
                if(idVideo == 0) {
                    break;
                }
                usuario.videosFav[j] = idVideo;
            }
            fseek(arqUsuarios, -sizeof(struct ArquivoUsuario), SEEK_CUR);
            fwrite(&usuario, sizeof(struct ArquivoUsuario), 1, arqUsuarios);
            encontrado = 1;
            break;
        }
    }
    if(!encontrado) {
        printf("Usuario com o ID %d nao encontrado no arquivo.\n", usuario.id);
    }
    fclose(arqUsuarios);
}

void removerVideo(int idVideo) {
    struct ArquivoVideo video;
    int encontrado = 0;
    FILE *arqVideos = fopen("ArquivoVideos.bin", "rb");
    if (arqVideos == NULL) {
        printf("Erro na abertura do arquivo!\n");
        return;
    }

    FILE *arqTemp = fopen("ArquivoTemp.bin", "wb");
    if (arqTemp == NULL) {
        printf("Erro ao criar arquivo temporario!\n");
        return;
    }

    while(fread(&video, sizeof(struct ArquivoVideo), 1, arqVideos)) {
        if(idVideo == video.id) {
            fwrite(&video, sizeof(struct ArquivoVideo), 1, arqTemp);
        } else {
            encontrado = 1;
        }
    }
    fclose(arqVideos);
    fclose(arqTemp);
    if(encontrado) {
        remove("ArquivoVideos.bin");
        rename("ArquivoTemp.bin", "ArquivoVideos.bin");
        printf("Video removido!\n");
    } else {
        remove("ArquivoTemp.bin");
        printf("Video com ID %d nao encontrado.\n", idVideo);
    }
}