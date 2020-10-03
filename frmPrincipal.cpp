//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "frmPrincipal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------
__fastcall TFormPrincipal::TFormPrincipal(TComponent* Owner)
	: TForm(Owner)
{
}
//---------------------------------------------------------------------------




void __fastcall TFormPrincipal::pnDesenhoMouseMove(TObject *Sender, TShiftState Shift,
          int X, int Y)
{
   /* Desenho no painel  */
   int i = High(FPosicoes)+1;
   SetLength(FPosicoes,i+1);
   FPosicoes[i]->X = X;
   FPosicoes[i]->y = Y;
   pnDesenho->Invalidate;
}
//---------------------------------------------------------------------------

void __fastcall TFormPrincipal::pnDesenhoPaint(TObject *Sender)
{
   /*	int K := High(FPosicoes);

   if K < 0 then

      Exit;

   with PaintBox1.Canvas do

   begin

      with FPosicoes[0] do

         Ellipse(X-2, Y-2, X+2, Y+2);

      if K > 0 then

      begin

         with FPosicoes[K] do

            Ellipse(X-2, Y-2, X+2, Y+2);

         with FPosicoes[0] do

            MoveTo(X, Y);

         for K := 1 to K do

            LineTo(FPosicoes[K].x, FPosicoes[K].y);

         end;

	  end;
      */
}
//---------------------------------------------------------------------------

