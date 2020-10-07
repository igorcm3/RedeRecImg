//---------------------------------------------------------------------------

#ifndef frmPrincipalH
#define frmPrincipalH
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Menus.hpp>
#include <Vcl.ComCtrls.hpp>
#include <Vcl.ExtCtrls.hpp>
#include <System.SysUtils.hpp>
#include <System.Variants.hpp>
#include <VCLTee.Chart.hpp>
#include <VCLTee.Series.hpp>
#include <VclTee.TeeGDIPlus.hpp>
#include <VCLTee.TeEngine.hpp>
#include <VCLTee.TeeProcs.hpp>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
using namespace std;
//---------------------------------------------------------------------------

class Thread : public TThread
{
	private:
	protected:
		void __fastcall Execute();

	public:
		__fastcall Thread(bool CreateSuspended);
};

class TFormPrincipal : public TForm
{
__published:	// IDE-managed Components
	TPageControl *tbiTreinamento;
	TTabSheet *tbiClassificacao;
	TTabSheet *TabSheet2;
	TGroupBox *gbDesenho;
	TButton *btnReconhecerSalvar;
	TSplitter *Splitter1;
	TListBox *listboxClassificacao;
	TPaintBox *pnDesenho;
	TChart *Chart1;
	TFastLineSeries *Series1;
	TFastLineSeries *Series4;
	TMemo *meTreinamento;
	TButton *btnIniciarTreinamento;
	TButton *btnCancelarTreinamento;
	TGroupBox *gbAcoes;
	TRadioButton *rbReconhecer;
	TRadioButton *rbSalvarParaTreinamento;
	TEdit *eNomeArquivo;
	TGroupBox *cgClassificacao;
	TLabel *Label1;
	TLabel *Label2;
	TRadioButton *rbSalvarParaValidacao;
	TLabel *Label3;
	TShape *Shape16;
	TShape *Shape17;
	TShape *Shape18;
	TShape *Shape19;
	void __fastcall pnDesenhoMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pnDesenhoPaint(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall pnDesenhoMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall pnDesenhoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnReconhecerSalvarClick(TObject *Sender);
	void __fastcall btnIniciarTreinamentoClick(TObject *Sender);
	void __fastcall btnCancelarTreinamentoClick(TObject *Sender);
	void __fastcall rbReconhecerClick(TObject *Sender);
	void __fastcall rbSalvarParaTreinamentoClick(TObject *Sender);
	void __fastcall rbSalvarParaValidacaoClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFormPrincipal(TComponent* Owner);
	Graphics::TBitmap *DrawingBoard;
	Boolean IsDrawing;
	AnsiString FPathSalvarMatriz;

    // Métodos
	unsigned char* read_bmp(char *fname,int* _w, int* _h);
	void __fastcall bitmapParaMatrizPixels(AnsiString _AFileName);
	float funcao_ativacao(float net, int funcao, float a);
	float derivada(float net, int funcao, float a);
	void __fastcall AtualizaGrafico();
	void __fastcall carregarValoresTreinamento();
	void __fastcall carregarValoresValidacao();
	void __fastcall ajustarAcoes();
	void __fastcall classificar();
};


//---------------------------------------------------------------------------
extern PACKAGE TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------
#endif
