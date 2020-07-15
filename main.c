#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <time.h>

#define NUMERODEOPCOES 10

typedef struct node
{
    int Linha;
    int Coluna;
    int RedPixel;
    int GreenPixel;
    int BluePixel;
    struct node *next;
} Tnode;

char identificador[3]="P3";

int MaxLin=0, MaxCol=0, MaxPixel=0;

Tnode *Final;

int MENU()
{
    int opcao = 1, input ;

    printf("\n\n");

    printf("**** PhotoShop ****");
    printf("\n1 - Carregar Imagem");
    printf("\n2 - Criar Imagem Aleatória");
    printf("\n3 - Preto e Branco");
    printf("\n4 - Inverter Cores");
    printf("\n5 - Filtro Sépia");
    printf("\n6 - Filtro Rio");
    printf("\n7 - Aumenta contraste");
    printf("\n8 - Histograma (Tem que estar em preto e branco)");
    printf("\n9 - Salvar Imagem");
    printf("\n10 - Sair");
    printf("\n\nSelecione uma opção: ");

    scanf("%d",&opcao);

    return opcao;
}

Tnode *InsereNaListaLigada(Tnode *Imagem, int Linha, int Coluna, int RedPixel, int GreenPixel, int BluePixel)
{
    if(Imagem == NULL)
    {
        Imagem = calloc(1, sizeof(Tnode));
        Final = Imagem;
        Imagem->Linha = Linha;
        Imagem->Coluna = Coluna;
        Imagem->next = NULL;
        Imagem->RedPixel = RedPixel;
        Imagem->GreenPixel = GreenPixel;
        Imagem->BluePixel = BluePixel;
    }
    else
    {
        Final -> next = calloc(1, sizeof(Tnode));
        Final = Final -> next;
        Final -> Linha = Linha;
        Final -> Coluna = Coluna;
        Final -> next = NULL;
        Final->RedPixel = RedPixel;
        Final->GreenPixel = GreenPixel;
        Final->BluePixel = BluePixel;
    }
    return Imagem;
}

Tnode *CarregaImagem(Tnode *Imagem, char File[])
{
    int RedPixel;
    int GreenPixel;
    int BluePixel;

    FILE *txt = fopen(File, "r+");

    fscanf(txt, "%s\n", identificador);
    fscanf(txt, "%d %d \n", &MaxCol, &MaxLin );
    fscanf(txt, "%d \n", &MaxPixel);

    for (int i = 0 ; i < MaxLin && !feof(txt) ; i++)
    {
        for (int j = 0 ; j < MaxCol && !feof(txt) ; j++)
        {
            fscanf(txt, "%d \n",&RedPixel);
            fscanf(txt, "%d \n",&GreenPixel);
            fscanf(txt, "%d \n",&BluePixel);
            Imagem = InsereNaListaLigada(Imagem, i, j, RedPixel, GreenPixel, BluePixel);
        }
    }
    fclose(txt);
    return Imagem;
}

void PretoBranco(Tnode *Imagem)
{
    Tnode *tmp;

    tmp = Imagem;
    int cinza;

    while (tmp -> next != Final)
    {
        cinza = (tmp -> RedPixel + tmp -> GreenPixel + tmp ->BluePixel)/3;

        tmp -> RedPixel = cinza;
        tmp -> GreenPixel = cinza;
        tmp -> BluePixel = cinza;
        tmp = tmp -> next;
    }
}

void InverteCor (Tnode *Imagem)
{
    Tnode *tmp;

    tmp = Imagem;

    while (tmp -> next != Final)
    {
        tmp -> RedPixel = (-1)*(tmp ->RedPixel) + 255;
        tmp -> GreenPixel = (-1)*(tmp ->GreenPixel) + 255;
        tmp -> BluePixel = (-1)*(tmp ->BluePixel) + 255;
        tmp = tmp -> next;
    }
}

void Sepia (Tnode *Imagem)
{
    Tnode *tmp;

    tmp = Imagem;

    while (tmp -> next != Final)
    {
        tmp -> RedPixel = (1)*(tmp ->RedPixel);
        tmp -> GreenPixel = (0.6)*(tmp ->GreenPixel);
        tmp -> BluePixel = (0.3)*(tmp ->BluePixel);
        tmp = tmp -> next;
    }
}

void Rio (Tnode *Imagem)
{
    Tnode *tmp;

    tmp = Imagem;

    while (tmp -> next != Final)
    {
        tmp -> RedPixel = (0.7)*(tmp ->RedPixel);
        tmp -> GreenPixel = (0.9)*(tmp ->GreenPixel);
        tmp -> BluePixel = (1)*(tmp ->BluePixel);
        tmp = tmp -> next;
    }
}

void Contraste (Tnode *Imagem, float porcentagem)
{
    printf("Ainda não está funcionando =(");
    fflush(stdin);
    getchar();
}

void HistogramaPretoeBranco (Tnode *Imagem)
{
    char SaveFile[30]="", Formato[5]=".txt";

    int contador = 0, i = 0;

    printf("Qual o nome do arquivo para salvar os dados?:");
    scanf("%s",SaveFile);
    strcat(SaveFile,Formato);

    FILE *histograma = fopen(SaveFile,"w+");

    Tnode *tmp;

    for ( i = 0 ; i <= 255 ; i++)
    {
        tmp = Imagem;
        contador = 0;
        while (tmp -> next != Final)
        {
            if (tmp -> RedPixel == i)
            {
                contador ++;
            }
            tmp = tmp -> next;
        }
        fprintf(histograma,"%d\t%d\n",i,contador);
    }
    fclose(histograma);
}

Tnode *CriaImagemAleatoria(Tnode *Imagem)
{
    Imagem = NULL;

    srand(time(NULL));

    int i = 0, j = 0, Red, Green, Blue, entro = 0;

    char SaveFile[30]="", Formato[5]=".ppm";

    MaxPixel = 255;

    printf("Como vai chamar sua nova imagem?:");
    scanf("%s",SaveFile);
    strcat(SaveFile,Formato);

    printf("Qual o tamanho da imagem que você quer criar?\n");
    printf("Coluna : ");
    scanf("%d",&MaxCol);
    printf("Linha : ");
    scanf("%d",&MaxLin);

    FILE *novaimagem = fopen(SaveFile,"w+");

    fprintf(novaimagem,"P3\n");
    fprintf(novaimagem,"%d %d\n",MaxCol,MaxLin);
    fprintf(novaimagem,"255\n");

    for (i = 0 ; i < MaxLin ; i++)
    {
        for(j = 0 ; j < MaxCol ; j++)
        {
            Red = rand() % 255;
            Green = rand() % 255;
            Blue = rand() % 255;

            Imagem = InsereNaListaLigada(Imagem, i, j, Red, Green, Blue);

            fprintf(novaimagem,"%d\n",Red);
            fprintf(novaimagem,"%d\n",Green);
            fprintf(novaimagem,"%d\n",Blue);
        }
    }
    fclose(novaimagem);
    return Imagem;
}

void DescarregaNovaImagem(Tnode *Imagem, char File[])
{
    Tnode *percorre;

    percorre = Imagem;

    FILE *novotxt = fopen(File, "w+");

    fprintf (novotxt,"%s \n",identificador);
    fprintf (novotxt,"%d %d \n", MaxCol, MaxLin );
    fprintf (novotxt,"%d \n",MaxPixel);

    for (int i = 0 ; i < MaxLin ; i++)
    {
        for (int j = 0 ; j < MaxCol ; j++)
        {
                fprintf(novotxt, "%d \n",percorre->RedPixel);
                fprintf(novotxt, "%d \n",percorre->GreenPixel);
                fprintf(novotxt, "%d \n",percorre->BluePixel);
                if ( percorre->next != NULL )
                    percorre = percorre -> next;
        }
    }
    fclose(novotxt);
}

void main()
{
    Tnode *Imagem = NULL;

    char ReadFile[30]="", SaveFile[30]="", Formato[5]=".ppm";

    int option;

    setlocale(LC_ALL, "Portuguese" );

    do
    {
        option = MENU();

        printf("\n\n");

        if (option  == 1)
        {
            printf("Nome da imagem para ler (Não precisa colocar a extensão): ");

            Imagem = NULL;

            scanf("%s",ReadFile);
            strcat(ReadFile,Formato);

            Imagem = CarregaImagem(Imagem,ReadFile);
            if(Imagem != NULL )
            {
                printf("\nImagem carregada com sucesso!");
                fflush(stdin);
                getchar();
            }
            else
            {
                printf("\nNão foi possivel carregar a imagem =(");
                exit(0);
            }
        }

        else if (option  == 2)
        {
            Imagem = CriaImagemAleatoria(Imagem);
        }

        else if (option  == 3)
        {
            PretoBranco(Imagem);
        }

        else if (option  == 4)
        {
            InverteCor(Imagem);
        }

        else if (option  == 5)
        {
            Sepia(Imagem);
        }

        else if (option  == 6)
        {
            Rio(Imagem);
        }

        else if (option  == 7)
        {
            float porcentagem;

            printf("\n\n");
            Contraste(Imagem,porcentagem);
        }

        else if (option  == 8)
        {
            HistogramaPretoeBranco(Imagem);
        }

        else if (option  == 9)
        {
            char resposta;

            printf("Nome da nova imagem (Não precisa colocar a extensão): ");

            scanf("%s",SaveFile);
            strcat(SaveFile,Formato);

            DescarregaNovaImagem(Imagem,SaveFile);
        }
        else if (option  == 10)
        {
            exit(0);
        }
    }
    while( 1 == 1 );
}
