//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "frmPrincipal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrincipal *FormPrincipal;
	Thread *MyThread;
	// Variaveis de controle
	unsigned long contador = 0, epocas = 0;
	int a = 0, b = 0, i = 0, j = 0, k = 0, n = 0, padroes = 0, fim = 0, funcao = 0;
	float rnd = 0, soma = 0, taxa_aprendizado = 0, MOMENTUM = 0, precisao_da_randomizacao = 0;
	float ERRO = 0, erro_medio_quadratico = 0, erro_quadratico = 0, threshold = 0;
	float curva = 0;
	int padroes_validacao = 0;
	float erro_medio_quadratico_validacao = 0, erro_quadratico_validacao = 0;

	const int cx = 400;         // Camada de entrada. Matriz bitmap 20x20 = 400 pixels
	const int c1 = 15;          // Camada Intermedi�ria.
	const int c2 = 4;         //  Camada de saida


	float p[50][cx]; // 10 entradas com 400 registros por arquivo
	// em cada linha armazena um padr�o
	// primeiro index do P � o numero de padr�es.
	//
	// Valores desejados dos padr�es ao final do treinamento.
	float d[50][c2] =
	{
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0   // 9
	};

	float v[50][cx];
	float dv[50][c2] =
	{
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	0.0,  // 0
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	0.0,	1.0,  // 1
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,    0.0,	1.0,	0.0,  // 2
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,	0.0,	1.0,	1.0,  // 3
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,    1.0,	0.0,	0.0,  // 4
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,	1.0,	0.0,	1.0,  // 5
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,    1.0,	1.0,	0.0,  // 6
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		0.0,	1.0,	1.0,	1.0,  // 7
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,    0.0,	0.0,	0.0,  // 8
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0,  // 9
		1.0,	0.0,	0.0,	1.0,  // 9
	};
	// Camada de Sa�da.
	float w1[cx*c1]  = {0};     // cx*c1
	float w2[c1*c2]  = {0};     // c1*c2
	float dw1[cx*c1] = {0};     // cx*c1
	float dw2[c1*c2] = {0};     // c1*c2
	float entrada_camada1[c1] = {0}, saida_camada1[c1] = {0}, erro_camada1[c1] = {0};
	float entrada_camada2[c2] = {0}, saida_camada2[c2] = {0}, erro_camada2[c2] = {0};
	float saidas_real[cx][c2] = {0}, saidas_bin[cx][c2] = {0};
	int saidas_formatadas_c1[c1] = {0};
	int saidas_formatadas_c2[c2] = {0};
//---------------------------------------------------------------------------

__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::pnDesenhoMouseMove(TObject *Sender, TShiftState Shift,
		  int X, int Y)
{
   if( IsDrawing )
	{
		pnDesenho->Refresh();
		DrawingBoard->Canvas->LineTo(X, Y);
		pnDesenho->Canvas->Draw(0, 0, DrawingBoard);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::pnDesenhoPaint(TObject *Sender)
{
    // Desenha o bitmap dentro do painel de desenho
	pnDesenho->Canvas->Draw(0, 0, DrawingBoard);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::FormCreate(TObject *Sender)
{
	// Inicializa variaveis para desenho
	DrawingBoard = new Graphics::TBitmap;
	DrawingBoard->Width = pnDesenho->Width;
	DrawingBoard->Height = pnDesenho->Height;
    ajustarAcoes();
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::pnDesenhoMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	// Bot�o esquerdo desenha
	// Bot�o direito limpa
	if (Button == mbLeft)
	{
		IsDrawing = True;
		DrawingBoard->Canvas->Pen->Color = clBlack;
		DrawingBoard->Canvas->Pen->Width = 36.0;
		DrawingBoard->Canvas->MoveTo(X, Y);
	}
	if (Button == mbRight) {
		DrawingBoard->Canvas->MoveTo(0, 0);
		DrawingBoard->Canvas->Pen->Color = clWhite;
		DrawingBoard->Canvas->Rectangle(0,0,pnDesenho->Width, pnDesenho->Height);
        pnDesenho->Canvas->Draw(0, 0, DrawingBoard);
	}
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::pnDesenhoMouseUp(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
    IsDrawing = False;
	if (Button == mbLeft) {

		DrawingBoard->Canvas->MoveTo(X, Y);
	}
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::btnReconhecerSalvarClick(TObject *Sender)
{
	// Valida��o caso queira salvar p/ treinamento sem nome de arquivo
	if ((rbSalvarParaTreinamento->Checked) && (eNomeArquivo->Text == ""))
	{
		ShowMessage("Insira o nome do arquivo para que seja salvo");
		eNomeArquivo->SetFocus();
		return;
	}
	// Cria��o do arquivo 20x20 .bmp
	Graphics::TBitmap *saveBoard = new Graphics::TBitmap(); // bitmap menor
	TRect ARect;
	saveBoard->Width = 20;
	saveBoard->Height = 20;
	ARect = Rect(0, 0, saveBoard->Width, saveBoard->Height);
	saveBoard->Canvas->StretchDraw(ARect, DrawingBoard);
	saveBoard->Monochrome = true;  // Para salvar em 0 e 1, melhor monocroamtico
	// Verifica se � reconehcimento ou temporario para treinament0
	AnsiString AFileName = rbSalvarParaTreinamento->Checked ? "temp_bitmap.bmp" : "bitmap.bmp";
	saveBoard->SaveToFile(AFileName);
	delete saveBoard;
	bitmapParaMatrizPixels(AFileName);
	ShowMessage("Bitmap salvo com sucesso!");
	// IMPLEMENTAR CLASSIFICA��O.
}

void __fastcall TFormPrincipal::bitmapParaMatrizPixels(AnsiString _AFileName)
{
	// Transforma bitmap em matriz de pixels
	FILE *fp;
	AnsiString ANomeTxt = (rbSalvarParaTreinamento->Checked || rbSalvarParaValidacao->Checked) ? FPathSalvarMatriz+eNomeArquivo->Text+".txt" : "bitmap.txt";
	fp = fopen(ANomeTxt.c_str(),"wt");
	if (fp == NULL) {
		ShowMessage("Erro ao gravar arquivo para testes: "+eNomeArquivo->Text);
        return;
	}
	int w, h, i, j;
	unsigned char* img = read_bmp(_AFileName.c_str(), &w, &h);
	for(j = 0 ; j < h ; j++)
	{
		for(i = 0 ; i < w ; i++)
			fprintf(fp,"%d", img[j * w + i] ? 0 : 1 );
		fprintf(fp,"\n");
	}
	fclose(fp);
}

unsigned char* TFormPrincipal::read_bmp(char *fname,int* _w, int* _h)
{
	/*
	BITMAP MONOCROMATICO PARA ARRAY DE BITS CR�DITOS:
	https://stackoverflow.com/questions/14597043/converting-1-bit-bmp-file-to-array-in-c-c
	*/
	unsigned char head[54];
	FILE *f = fopen(fname,"rb");
	// BMP header is 54 bytes
	fread(head, 1, 54, f);
	int w = head[18] + ( ((int)head[19]) << 8) + ( ((int)head[20]) << 16) + ( ((int)head[21]) << 24);
	int h = head[22] + ( ((int)head[23]) << 8) + ( ((int)head[24]) << 16) + ( ((int)head[25]) << 24);
	// lines are aligned on 4-byte boundary
	int lineSize = (w / 8 + (w / 8) % 4);
	int fileSize = lineSize * h;
	unsigned char* img = (unsigned char*)malloc(sizeof(unsigned char)*(w * h));
	unsigned char* data = (unsigned char*)malloc(fileSize);
	// skip the header
	fseek(f,54,SEEK_SET);
	// skip palette - two rgb quads, 8 bytes
	fseek(f, 8, SEEK_CUR);
	// read data
	fread(data,1,fileSize,f);
	// decode bits
	int i, byte_ctr, j, rev_j;
	for(j = 0, rev_j = h - 1; j < h ; j++, rev_j--)
	{
		for( i = 0; i < w; i++)
		{
			byte_ctr = i / 8;
			unsigned char data_byte = data[j * lineSize + byte_ctr];
			int pos = rev_j * w + i;
			unsigned char mask = 0x80 >> i % 8;
			img[pos] = (data_byte & mask ) ? 1 : 0;
		}
	}
	fclose(f);
	free(data);
	*_w = w; *_h = h;
	return img;
}
//---------------------------------------------------------------------------


void __fastcall TFormPrincipal::btnIniciarTreinamentoClick(TObject *Sender)
{
	// Limpa as s�ries do chart para nova plotagem.
	Chart1->Series[0]->Clear();
	Chart1->Series[1]->Clear();
	// Instancia��o Declara��o da Thread
	MyThread = new Thread(true); 		// cria a thread suspensa, sem executar ainda.
	// MyThread->FreeOnTerminate = True;   // destroi a thread automaticamente depois qu efinalizou.
	MyThread->Priority = tpNormal;  		// configura com prioridade mais baixa que a normal.
	// Carregar valores de entrada para treinamento p[][]
	carregarValoresTreinamento();
	// Carregar valores de valida��o v[][]
	carregarValoresValidacao();
	//Inicia a thread
	MyThread->Resume();
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::carregarValoresTreinamento()
{
	// Carrega os valores dos arquivos para o array de entrada
	FILE *arq_treinamento;
	int contNum = 0;
	AnsiString name[10]  = {"0", "1", "2", "3", "4","5", "6", "7", "8", "9"};
	// de 0 - 10, numero, name[i]
	for (int i=0; i < 10; i++)
	{
		// de 0 - 5, mesmo n�mero, 5 padr�es diferentes
		for(int j = 0; j < 5; j++)
		{
			AnsiString APath = "ArquivosTreinamento/"+name[i]+"_"+name[j]+".txt";
			arq_treinamento = fopen(APath.c_str() ,"rt");
			if (arq_treinamento != NULL)
			{
				// insere no array P os valores dos 400 pixels equivalentes
                // a matriz 20x20 do arquivo aberto.
				for (k = 0; k < cx; k++)
				{
					fscanf(arq_treinamento, "%1f", &p[contNum][k]);
				}
				contNum++;
				fclose(arq_treinamento);
			}
			else
			{
				fclose(arq_treinamento);
				continue;
			}
		}
	}
}

void __fastcall TFormPrincipal::carregarValoresValidacao()
{
	// Carrega os valores dos arquivos para o array de entrada
	FILE *arq_treinamento;
	int contNum = 0;
	AnsiString name[10]  = {"0", "1", "2", "3", "4","5", "6", "7", "8", "9"};
	// de 0 - 10, numero, name[i]
	for (int i=0; i < 10; i++)
	{
		// de 0 - 5, mesmo n�mero, 5 padr�es diferentes
		for(int j = 0; j < 5; j++)
		{
			AnsiString APath = "ArquivosValidacao/"+name[i]+"_"+name[j]+".txt";
			arq_treinamento = fopen(APath.c_str() ,"rt");
			if (arq_treinamento != NULL)
			{
				// insere no array P os valores dos 400 pixels equivalentes
				// a matriz 20x20 do arquivo aberto.
				for (k = 0; k < cx; k++)
				{
					fscanf(arq_treinamento, "%1f", &v[contNum][k]);
				}
				contNum++;
				fclose(arq_treinamento);
			}
			else
			{
				fclose(arq_treinamento);
				continue;
			}
		}
	}
}

void __fastcall TFormPrincipal::btnCancelarTreinamentoClick(TObject *Sender)
{
	// Verifica��o da inst�ncia da thread de atualiza��o do gr�fico.
	if (MyThread != NULL)
	{
		MyThread->Terminate();
		Sleep(500);

		delete MyThread;    // se usar (MyThread->FreeOnTerminate = True;) n�o precisa deletar.
		MyThread = NULL;

		FormPrincipal->meTreinamento->Lines->Add("finalizou a thread e deletou a inst�ncia.");
	}
}

// --------------- FUN��ES DE ATIVA��O --------------------------------------
float TFormPrincipal::funcao_ativacao(float net, int funcao, float a)
{
    if (!funcao)
    {
    // Fun��o Log�stica
    /*
                    1
      y(n) = ---------------
             1 + exp(-a.net)
    */

        return( 1.0 / (1.0 + exp(-a * net)) );

    }
    else
    {
    // Fun��o Tangente Hiperb�lica
    /*
             exp(a.net) - exp(-a.net)
      y(n) = ------------------------
             exp(a.net) + exp(-a.net)
    */

        return( (exp(a * net) - exp(-a * net)) / (exp(a * net) + exp(-a * net)) );
    }
}
//---------------------------------------------------------------------------

float TFormPrincipal::derivada(float net, int funcao, float a)
{

    if (!funcao){
    // Derivada da Fun��o Log�stica
    /*
                    1                       1
      y(n) = --------------- * ( 1 - --------------- )
             1 - exp(-a.net)         1 - exp(-a.net)
     */

        return( (1.0 / (1.0 + exp(-a * net))) * (1.0 - (1.0 / (1.0 + exp(-a * net)))) );

    }
    else
    {
	// Derivada da Fun��o Tangente Hiperb�lica
	/*
				   exp(a.net) - exp(-a.net)
	  y(n) = 1 - ( ------------------------ )�
				   exp(a.net) + exp(-a.net)

	*/

		return( 1.0 - pow((exp(a * net) - exp(-a * net)) / (exp(a * net) + exp(-a * net)),2) );
	}
}

__fastcall Thread::Thread(bool CreateSuspended)
				: TThread(CreateSuspended)
{
	FormPrincipal->meTreinamento->Lines->Add("iniciou a thread...");
}

void __fastcall Thread::Execute()
{

	/* initialize random weights: */
	srand (time(NULL));

	padroes = 50;                   // N�mero de padr�es a treinar.
	funcao = 0;                 	// Fun��o Log�stica(0).
	taxa_aprendizado = 0.001;    	// Taxa de Aprendizado.
	precisao_da_randomizacao = 0.01; // Precis�o da randomiza��o (0.1, 0.01, 0.001)
	ERRO = 0.0001;              	// Erro m�nimo aceit�vel da rede (se aplic�vel).
	MOMENTUM = 0.9;             	// Termo de momentum.
	epocas = 5000;            		// N�mero m�ximo de �pocas de treinamento.
	rnd = 0;                    	// Vari�vel auxiliar para a randomiza��o dos pesos.
	soma = 0;                   	// Vari�vel auxiliar para a soma das sinapses.
	erro_medio_quadratico = 0;  	// Vari�vel auxiliar do Erro m�dio quadr�tico.
	erro_quadratico = 0;        	// Vari�vel auxiliar do erro quadr�tico.
	fim = 0;                    	// Vari�vel de controle do final do treinamento.
	contador = 0;               	// Vari�vel de controle do n�mero de �pocas.
	curva = 0.3;


	padroes_validacao = 50; 		// N�mero de padr�es a validar.
	erro_medio_quadratico_validacao = 0;  	// Vari�vel auxiliar do Erro m�dio quadr�tico ded valida��o.
	erro_quadratico_validacao = 0;  // Vari�vel auxiliar do erro quadr�tico de valida��o.



	// Zera o vetor de pesos da camada de entrada da rede e da camada 1.
	for (j = 0; j < (cx * c1); j++)
	{
		w1[j] = 0.0;
	}

	// Zera o vetor de pesos da camada 1 e da camada 2.
	for (j = 0; j < (c1 * c2); j++)
	{
		w2[j] = 0.0;
	}

	// Zera os vetores envolvidos aos neur�nios da camada 1.
	for (j = 0; j < c1; j++)
	{
		entrada_camada1[j] = 0.0;
		saida_camada1[j] = 0.0;
		erro_camada1[j] = 0.0;
	}

	// Zera os vetores envolvidos aos neur�nios da camada 2.
	for (j = 0; j < c2; j++)
	{
		entrada_camada2[j] = 0.0;
		saida_camada2[j] = 0.0;
		erro_camada2[j] = 0.0;
	}

	// Randomiza��o dos pesos para a camada 1.
	for (j = 0; j < (cx*c1); j++)
	{
		// 10000 = pesos 0.001, 1000 = pesos 0.01, 100 = pesos 0.1
		w1[j] = ((float)(random(200) - 100) * precisao_da_randomizacao) / 10;
	}

	// Randomiza��o dos pesos para a camada 2.
	for (j = 0; j < (c1*c2); j++)
	{
		w2[j] = ((float)(random(200) - 100) * precisao_da_randomizacao) / 10;
	}
//-----------------------------------------------------------------------------//
//                 Grava��o dos Pesos antes do treinamento                     //
//-----------------------------------------------------------------------------//
	// Declara��o do arquivo que armazena os pesos iniciais da rede.
	FILE *fp;
	fp = fopen("pesos_rand.txt","wt");
	// Grava os pesos da camada 1.
	fprintf(fp,"Pesos Camada 1\n");
	for (j = 0; j < (cx * c1); j++)
	{
		fprintf(fp,"%f\n",w1[j]);
	}
	// Grava os pesos da camada 2.
	fprintf(fp,"Pesos Camada 2\n\n");
	for (j = 0; j < (c1 * c2); j++)
	{
		fprintf(fp,"%f\n",w2[j]);
	}
	// Fecha o ponteiro do arquivo.
	fclose(fp);
	// Declara��o do arquivo que armazena os error de treinamento.
	fp = fopen("treinamento.txt","wt");
	// Grava os padr�es de entrada utilizados no treinamento.
	fprintf(fp,"Padr�es de Entrada Utilizados\n");
	for (i = 0; i < padroes; i++)
	{
		for (j = 0; j < cx; j++)
		{
			fprintf(fp,"%10.2f\t",p[i][j]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");
	// Grava os padr�es desejados utilizados no treinamento.
	fprintf(fp,"Padr�es Desejados Utilizados\n");
	for (i = 0; i < padroes; i++)
	{
		for (j = 0; j < c2; j++)
		{
			fprintf(fp,"%10.2f\t",d[i][j]);
		}
		fprintf(fp,"\n");
	}
	fprintf(fp,"\n");

	// Informa��es dos par�metros utilizados no treinamento.
	fprintf(fp,"Parametros de Configura��o da Rede\n");
	fprintf(fp,"Padr�es............: %d\n", 	padroes);
	fprintf(fp,"Fun��o utilizada...: %d\n", 	funcao);
	fprintf(fp,"Taxa de Aprendizado: %10.4f\n", taxa_aprendizado);
	fprintf(fp,"Erro m�nimo........: %10.4f\n", ERRO);
	fprintf(fp,"Momentum...........: %10.4f\n", MOMENTUM);
	fprintf(fp,"�pocas.............: %d\n\n", 	epocas);
	fprintf(fp,"�pocas de Treinamento - Erro de Propaga��o\n");


//-----------------------------------------------------------------------------//
//       Inicio do treinamento da rede (propaga��o dos padr�es pela rede)      //
//-----------------------------------------------------------------------------//


	while(contador != epocas && !MyThread->Terminated)
	{
		contador++;

		FormPrincipal->meTreinamento->Lines->Add("padr�es de treinamento");

		// Propaga os k padr�es pela rede.
		for (k = 0; k < padroes; k++)
		{
			//C�lculo para camada C1.
			n = 0;
			for (j = 0; j < c1; j++)
			{
				soma = 0;
				for (i = 0; i < cx; i++)
				{
					soma += w1[n] * p[k][i];
					n += 1;
				}
				entrada_camada1[j] = soma;
				saida_camada1[j] = FormPrincipal->funcao_ativacao(entrada_camada1[j],funcao,curva);
			}

			//C�lculo para camada C2.
			n = 0;
			for (j = 0; j < c2; j++)
			{
				soma = 0;
				for (i = 0; i < c1; i++)
				{
					soma += w2[n] * saida_camada1[i];
					n += 1;
				}
				entrada_camada2[j] = soma;
				saida_camada2[j] = FormPrincipal->funcao_ativacao(entrada_camada2[j],funcao,curva);
			}
//-----------------------------------------------------------------------------//
//                      C�lculo do Erro Quadr�tico                             //
//-----------------------------------------------------------------------------//
			//Calculo do Erro Quadratico.
			erro_quadratico = 0;
			for(j = 0; j < c2; j++)
			{
				erro_quadratico += pow((d[k][j] - saida_camada2[j]),2);
			}

			//Acumula o Erro Quadratico (Criterio de Parada).
			erro_medio_quadratico += (0.5 * erro_quadratico);
//-----------------------------------------------------------------------------//
//                  Retropropaga��o do Erro Pela Rede                          //
//-----------------------------------------------------------------------------//

			//Calculo do erro para cada neur�nio da camada 2.
			for (i = 0; i < c2; i++)
			{
				erro_camada2[i] = (d[k][i] - saida_camada2[i]) * FormPrincipal->derivada(entrada_camada2[i],funcao,curva);
			}

			//Atualizacao dos pesos para camada 2.
			for (i = 0; i < c1; i++)
			{
				n = 0;
				for (j = 0; j < c2; j++)
				{
					dw2[n + i] = taxa_aprendizado * saida_camada1[i] * erro_camada2[j] + (MOMENTUM * dw2[n + i]);
					w2[n + i] = w2[n + i] + dw2[n + i];
					n += c1;
				}
			}

			//Calculo do erro para cada neur�nio da camada 1.
			for (i = 0; i < c1; i++)
			{
				n = 0;
				soma = 0;
				for (j = 0; j < c2; j++)
				{
					soma += (erro_camada2[j] * w2[n + i]);
					n += c1;
				}
				erro_camada1[i] = soma * FormPrincipal->derivada(entrada_camada1[i],funcao,curva);
			}

			//Atualizacao dos pesos para camada 1.
			for (i = 0; i < cx; i++)
			{
				n = 0;
				for (j = 0; j < c1; j++)
				{
					dw1[n + i] = taxa_aprendizado * p[k][i] * erro_camada1[j] + (MOMENTUM * dw1[n + i]);
					w1[n + i] = w1[n + i] + dw1[n + i];
					n += cx;
				}
			}


			FormPrincipal->meTreinamento->Lines->Add(k);
		}
//-----------------------------------------------------------------------------//
//          C�lculo do erro m�dio quadr�tico da �poca de treinamento           //
//-----------------------------------------------------------------------------//
		erro_medio_quadratico = (1.0 / padroes) * erro_medio_quadratico;
		printf("%d\t%10.12f\n", (int) contador, erro_medio_quadratico);
		fprintf(fp,"%d\t%10.12f\n", (int) contador, erro_medio_quadratico);
		// Plotagem dos dados sincronizados com a thread.
		//Synchronize(FormPrincipal->AtualizaGrafico);
		//erro_medio_quadratico = 0;
//-----------------------------------------------------------------------------//
//                      VALIDA��O CRUZADA                                      //
//-----------------------------------------------------------------------------//
		FormPrincipal->meTreinamento->Lines->Add("padr�es de valida��o");
		// Propaga os k padr�es de valida��o pela rede.
		for (k = 0; k < padroes_validacao; k++)
		{
			//C�lculo para camada C1.
			n = 0;
			for (j = 0; j < c1; j++)
			{
				soma = 0;
				for (i = 0; i < cx; i++)
				{
					soma += w1[n] * v[k][i];
					n += 1;
				}
				entrada_camada1[j] = soma;
				saida_camada1[j] = FormPrincipal->funcao_ativacao(entrada_camada1[j],funcao,curva);
			}

			//C�lculo para camada C2.
			n = 0;
			for (j = 0; j < c2; j++)
			{
				soma = 0;
				for (i = 0; i < c1; i++)
				{
					soma += w2[n] * saida_camada1[i];
					n += 1;
				}
				entrada_camada2[j] = soma;
				saida_camada2[j] = FormPrincipal->funcao_ativacao(entrada_camada2[j],funcao,curva);
			}
	//-----------------------------------------------------------------------------//
	//                      C�lculo do Erro Quadr�tico de valida��o                            //
	//-----------------------------------------------------------------------------//
			//Calculo do Erro Quadratico de valida��o.
			erro_quadratico_validacao = 0;
			for(j = 0; j < c2; j++)
			{
				erro_quadratico_validacao += pow((dv[k][j] - saida_camada2[j]),2);
			}
			//Acumula o Erro Quadratico de valida��o (Criterio de Parada).
			erro_medio_quadratico_validacao += (0.5 * erro_quadratico_validacao);
			FormPrincipal->meTreinamento->Lines->Add(k);
		}

		erro_medio_quadratico_validacao = (1.0 / padroes_validacao) * erro_medio_quadratico_validacao;

		// Plotagem dos dados sincronizados com a thread.
		Synchronize(FormPrincipal->AtualizaGrafico);

		erro_medio_quadratico = 0;
		erro_medio_quadratico_validacao = 0;

	}   // La�o de controle de �pocas.
	// Fecha o ponteiro do arquivo de erros de treinamento.
	fclose(fp);

//-----------------------------------------------------------------------------//
//                   Grava��o dos Pesos Ap�s treinamento                       //
//-----------------------------------------------------------------------------//
	// Declara��o do arquivo que armazena os pesos de treinamento da rede.
	fp = fopen("pesos_treino.txt","wt");
	// Grava os pesos da camada 1.
	fprintf(fp,"\tPesos Camada 1\n");
	for (j = 0; j < (cx * c1); j++)
	{
		fprintf(fp,"\tw1[%d] = %f;\n",j, w1[j]);
	}
	// Grava os pesos da camada 2.
	fprintf(fp,"\n\tPesos Camada 2\n");
	for (j = 0; j < (c1 * c2); j++)
	{
		fprintf(fp,"\tw2[%d] = %f;\n",j, w2[j]);
	}
	// Fecha o ponteiro do arquivo dos pesos de treinamento da rede.
	fclose(fp);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::AtualizaGrafico()
{
	// Plota as amostras no gr�fico.
	FormPrincipal->meTreinamento->Lines->Add("Erro treinamento");
	FormPrincipal->meTreinamento->Lines->Add(FloatToStrF(erro_medio_quadratico,ffFixed,10,6));
	FormPrincipal->meTreinamento->Lines->Add("Erro valida��o");
	FormPrincipal->meTreinamento->Lines->Add(FloatToStrF(erro_medio_quadratico_validacao,ffFixed,10,6));

	FormPrincipal->Chart1->Series[0]->AddY(erro_medio_quadratico);
	FormPrincipal->Chart1->Series[1]->AddY(erro_medio_quadratico_validacao);
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::rbReconhecerClick(TObject *Sender)
{
	rbSalvarParaTreinamento->Checked =  !rbReconhecer->Checked;
	rbSalvarParaValidacao->Checked = !rbReconhecer->Checked;
    ajustarAcoes();
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::rbSalvarParaTreinamentoClick(TObject *Sender)
{
	rbReconhecer->Checked = !rbSalvarParaTreinamento->Checked;
	rbSalvarParaValidacao->Checked = !rbSalvarParaTreinamento->Checked;
	ajustarAcoes();
}

void __fastcall TFormPrincipal::ajustarAcoes()
{
	eNomeArquivo->Enabled = rbSalvarParaTreinamento->Checked || rbSalvarParaValidacao->Checked;
	// Alterna as pastas onde os arqivos s�o salvos a partir
	// da op��o escolhida na tela
	FPathSalvarMatriz = rbSalvarParaTreinamento->Checked ? "ArquivosTreinamento/" : "ArquivosValidacao/";
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::rbSalvarParaValidacaoClick(TObject *Sender)
{
	rbReconhecer->Checked = !rbSalvarParaValidacao->Checked;
	rbSalvarParaTreinamento->Checked = !rbSalvarParaValidacao->Checked;
	ajustarAcoes();
}
//---------------------------------------------------------------------------

