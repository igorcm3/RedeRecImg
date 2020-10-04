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
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using namespace std;
//---------------------------------------------------------------------------
class TFormPrincipal : public TForm
{
__published:	// IDE-managed Components
	TPageControl *tbiTreinamento;
	TTabSheet *tbiClassificacao;
	TTabSheet *TabSheet2;
	TGroupBox *gbDesenho;
	TButton *btnReconhecer;
	TSplitter *Splitter1;
	TListBox *ListBox1;
	TLabel *Label1;
	TPaintBox *pnDesenho;
	void __fastcall pnDesenhoMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pnDesenhoPaint(TObject *Sender);
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall pnDesenhoMouseDown(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall pnDesenhoMouseUp(TObject *Sender, TMouseButton Button, TShiftState Shift,
          int X, int Y);
	void __fastcall btnReconhecerClick(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFormPrincipal(TComponent* Owner);
	Graphics::TBitmap *DrawingBoard;
	Boolean IsDrawing;
	int StartX, StartY;
	void __fastcall testImagem();
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------
#endif
