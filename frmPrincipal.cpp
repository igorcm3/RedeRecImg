//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include "frmPrincipal.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TFormPrincipal *FormPrincipal;
//---------------------------------------------------------------------------

#pragma pack(2)
typedef struct BmpHeader {
  unsigned short  bfType;
  unsigned int bfSize;
  unsigned short  bfReserved1;
  unsigned short  bfReserved2;
  unsigned int bfOffBits;
  unsigned int biSize;
  int  biWidth;
  int  biHeight;
  unsigned short  biPlanes;
  unsigned short  biBitCount;
  unsigned int biCompression;
  unsigned int biSizeImage;
  int  biXPelsPerMeter;
  int  biYPelsPerMeter;
  unsigned int biClrUsed;
  unsigned int biClrImportant;
}BITMAPHEADER;

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
}
//---------------------------------------------------------------------------
void __fastcall TFormPrincipal::pnDesenhoMouseDown(TObject *Sender, TMouseButton Button,
		  TShiftState Shift, int X, int Y)
{
	// Botão esquerdo desenha
	// Botão direito limpa
	if (Button == mbLeft)
	{
		IsDrawing = True;
		DrawingBoard->Canvas->Pen->Color = clBlack;
		DrawingBoard->Canvas->Pen->Width = 12.0;
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

void __fastcall TFormPrincipal::btnReconhecerClick(TObject *Sender)
{
	// Salva o desenho como bitmap na pasta raiz Win32/Debug
	//DrawingBoard->SaveToFile("bitmap.bmp");

	Graphics::TBitmap *saveBoard = new Graphics::TBitmap(); // bitmap2
	TRect ARect;
	saveBoard->Width = 300;
	saveBoard->Height = 300;
	ARect = Rect(0, 0, saveBoard->Width, saveBoard->Height);
	saveBoard->Canvas->StretchDraw(ARect, DrawingBoard);
	saveBoard->SaveToFile("bitmap.bmp");
	delete saveBoard;
	testImagem();
}

void __fastcall TFormPrincipal::testImagem()
{
    // Transforma bitmap em matriz de pixels
	FILE *fp;
	fp = fopen("bitmap.txt","wt");
	BmpHeader head;
	ifstream f("bitmap.bmp", ios::binary);
	int headsize = sizeof(BmpHeader);
	f.read((char*)&head, headsize);
	int height = head.biHeight;
	int width = head.biWidth;
	int bpp = 1;
	int linesize = ((width * bpp + 301) / 302) * 4;
	int filesize = linesize * height;
	vector<unsigned char> data(filesize);
	//read color table
	uint32_t color0;
	uint32_t color1;
	uint32_t colortable[2];
	f.seekg(54);
	f.read((char*)&colortable[0], 4);
	f.read((char*)&colortable[1], 4);
	//fprintf(fp,"colortable: 0x%06X 0x%06X\n", colortable[0], colortable[1]);
	f.seekg(head.bfOffBits);
	f.read((char*)&data[0], filesize);
	for(int y = height - 1; y >= 0; y--)
	{
        for(int x = 0; x < width; x++)
		{
			int pos = y * linesize + x / 8;
			int bit = 1 << (7 - x % 8);
			int v = (data[pos] & bit) > 0;

			fprintf(fp,"%d", v);
        }
		fprintf(fp,"\n");
	}
	f.close();
	fclose(fp);
}
//---------------------------------------------------------------------------

