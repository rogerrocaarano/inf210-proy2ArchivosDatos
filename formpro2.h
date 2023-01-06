//---------------------------------------------------------------------------

#ifndef formpro2H
#define formpro2H
//---------------------------------------------------------------------------
#include <System.Classes.hpp>
#include <Vcl.Controls.hpp>
#include <Vcl.StdCtrls.hpp>
#include <Vcl.Forms.hpp>
#include <Vcl.Mask.hpp>
#include <Vcl.Menus.hpp>
#include <FStream>
//---------------------------------------------------------------------------
struct TFecha {
  byte dia;
  byte mes;
  Word año;
};
struct RegAlumno {
  char mark; //marca de borrado
  Word cod;
  char nom[21];//cadena de 20 caracteres
  char dir[21];//cadena de 20 caracteres
  TFecha fecha;
};
struct RegIdxCod{
  Word cod; //codigo del alumno

  // std::streampos es el tipo de dato que devuelve la función tellp, es una
  // mejor práctica utilizar el tipo de dato real en lugar de Cardinal.

  //posicion en el archivos de datos de alumno
  //  Cardinal pos;
  std::streampos pos;
};

struct RegIdxNom {
	char nom[21];
	std::streampos pos;
};

class TForm1 : public TForm
{
__published:	// IDE-managed Components
	TMaskEdit *MaskEdit1;
	TLabel *Label2;
	TLabel *Label3;
	TLabel *Label4;
	TLabel *Label5;
	TEdit *Edit1;
	TEdit *Edit2;
	TEdit *Edit3;
	TButton *Button1;
	TButton *Button2;
	TMainMenu *MainMenu1;
	TMenuItem *indices1;
	TMenuItem *ordenar1;
	TMenuItem *porcodigo1;
	TMenuItem *pornombre1;
	TMenuItem *porcodigo2;
	TMenuItem *pornombre2;
	TButton *Button_NavIdx_fin;
	TButton *Button_NavIdx_ant;
	TButton *Button_NavIdx_sig;
	TButton *Button_navIdx;
	TButton *Button_Actualizar;
	TButton *Button_NavNombre;
	TButton *Button_NavNombre_ant;
	TButton *Button_NavNombre_sig;
	void __fastcall FormCreate(TObject *Sender);
	void __fastcall Edit1Exit(TObject *Sender);
	void __fastcall Button1Click(TObject *Sender);
	void __fastcall Button2Click(TObject *Sender);
	void __fastcall porcodigo1Click(TObject *Sender);
	void __fastcall Button_navIdxClick(TObject *Sender);
	void __fastcall Button_NavIdx_finClick(TObject *Sender);
	void __fastcall Button_NavIdx_sigClick(TObject *Sender);
	void __fastcall Button_NavIdx_antClick(TObject *Sender);
	void __fastcall porcodigo2Click(TObject *Sender);
	void __fastcall Button_ActualizarClick(TObject *Sender);
	void __fastcall pornombre1Click(TObject *Sender);
	void __fastcall Button_NavNombreClick(TObject *Sender);
	void __fastcall Button_NavNombre_antClick(TObject *Sender);
	void __fastcall Button_NavNombre_sigClick(TObject *Sender);
	void __fastcall pornombre2Click(TObject *Sender);
private:	// User declarations
	AnsiString nomArch, nomIdxCod, nomIdxNom, activeIdx;
	fstream *pf, *pIdx;
public:		// User declarations
	__fastcall TForm1(TComponent* Owner);
	void nomToUpcase();

};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
