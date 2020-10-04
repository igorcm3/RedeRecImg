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

void __fastcall TFormPrincipal::btnReconhecerClick(TObject *Sender)
{
	// Salva o desenho como bitmap na pasta raiz Win32/Debug
	//DrawingBoard->SaveToFile("bitmap.bmp");

	Graphics::TBitmap *saveBoard = new Graphics::TBitmap(); // bitmap2
	TRect ARect;
	saveBoard->Width = 20;
	saveBoard->Height = 20;
	ARect = Rect(0, 0, saveBoard->Width, saveBoard->Height);
	saveBoard->Canvas->StretchDraw(ARect, DrawingBoard);
	saveBoard->SaveToFile("bitmap.bmp");
	delete saveBoard;
	testImagem();
	ShowMessage("Bitmap salvo com sucesso!");
}

void __fastcall TFormPrincipal::testImagem()
{
    // Transforma bitmap em matriz de pixels
	FILE *fp;
	fp = fopen("bitmap.txt","wt");
	//BmpHeader head;
	//ifstream f("bitmap.bmp", ios::binary);
	int w, h, i, j;
	unsigned char* img = read_bmp("bitmap.bmp", &w, &h);
	for(j = 0 ; j < h ; j++)
	{
		for(i = 0 ; i < w ; i++)
			fprintf(fp,"%d", img[j * w + i] ? '0' : '1' );
		fprintf(fp,"\n");
	}
	/*

	int headsize = sizeof(BmpHeader);
	f.read((char*)&head, headsize);
	int height = head.biHeight;
	int width = head.biWidth;
	int bpp = 1;
	int linesize = ((width * bpp + 31) / 32) * 4;
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
	*/
}


unsigned char* TFormPrincipal::read_bmp(char *fname,int* _w, int* _h)
{
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
    int i, j, k, rev_j;
    for(j = 0, rev_j = h - 1; j < h ; j++, rev_j--) {
        for(i = 0 ; i < w / 8; i++) {
            int fpos = j * lineSize + i, pos = rev_j * w + i * 8;
            for(k = 0 ; k < 8 ; k++)
                img[pos + (7 - k)] = (data[fpos] >> k ) & 1;
        }
    }

    free(data);
	*_w = w; *_h = h;
    return img;
}
//---------------------------------------------------------------------------

