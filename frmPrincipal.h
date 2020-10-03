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
 // #include <System.Graphic.hpp>
//---------------------------------------------------------------------------
class TFormPrincipal : public TForm
{
__published:	// IDE-managed Components
	TPageControl *tbiTreinamento;
	TTabSheet *tbiClassificacao;
	TTabSheet *TabSheet2;
	TGroupBox *GroupBox1;
	TButton *Button1;
	TSplitter *Splitter1;
	TListBox *ListBox1;
	TLabel *Label1;
	TPaintBox *pnDesenho;
	void __fastcall pnDesenhoMouseMove(TObject *Sender, TShiftState Shift, int X, int Y);
	void __fastcall pnDesenhoPaint(TObject *Sender);

private:	// User declarations
public:		// User declarations
	__fastcall TFormPrincipal(TComponent* Owner);
	//FPosicoes : array of TPoint;
	TPoint *FPosicoes;
};
//---------------------------------------------------------------------------
extern PACKAGE TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------
#endif
