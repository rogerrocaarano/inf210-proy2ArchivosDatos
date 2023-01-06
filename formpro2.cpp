//---------------------------------------------------------------------------

#include <vcl.h>

#pragma hdrstop

#include "formpro2.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent *Owner)
        : TForm(Owner) {
}

//---------------------------------------------------------------------------
void __fastcall TForm1::FormCreate(TObject *Sender) {
    nomIdxCod = "cod.idx";
    nomIdxNom = "mom.idx";
    nomArch = "Alumnos.dat";
    fstream f(nomArch.c_str(), ios::in | ios::binary);
    if (f.fail()) {
        fstream f(nomArch.c_str(), ios::out | ios::binary);
    }
    f.close();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Edit1Exit(TObject *Sender) {
    bool hallado = false;
    RegAlumno reg;
    Word codi;
    codi = StrToInt(Edit1->Text);
    fstream f(nomArch.c_str(), ios::in | ios::binary);
    if (f.is_open()) {
        do {//busca el codigo en el archivo
            f.read((char *) &reg, sizeof(reg));
            hallado = (reg.cod == codi) && (reg.mark != '*');
        } while (!hallado && !f.eof());
        if (hallado) {//si lo encuentra, pone los datos en pantalla
            Edit2->Text = reg.nom;
            Edit3->Text = reg.dir;
            MaskEdit1->Text = IntToStr(reg.fecha.dia)
                              + '/' + IntToStr(reg.fecha.mes) + '/' + IntToStr(reg.fecha.a�o);
            Edit2->SetFocus();
        } else {//sino, limpia la pantalla
            Edit2->Text = "";
            Edit3->Text = "";
            MaskEdit1->Text = "";
        }
    }
    f.close();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender) {
    bool hallado = false;
    AnsiString cad;
    RegAlumno reg, regNuevo;
    regNuevo.mark = '0';//no marcado para borrar
    regNuevo.cod = StrToInt(Edit1->Text);
    cad = Edit2->Text;
    strcpy(regNuevo.nom, cad.c_str());
    cad = Edit3->Text;
    strcpy(regNuevo.dir, cad.c_str());
    cad = MaskEdit1->Text;
    regNuevo.fecha.dia = StrToInt(cad.SubString(1, 2));
    regNuevo.fecha.mes = StrToInt(cad.SubString(4, 2));
    regNuevo.fecha.a�o = StrToInt(cad.SubString(7, 4));
    fstream f(nomArch.c_str(), ios::in | ios::out | ios::binary);
    if (f.is_open()) {
        do {
            f.read((char *) &reg, sizeof(reg));
            hallado = (reg.cod == regNuevo.cod) && (reg.mark != '*');
        } while (!hallado && !f.eof());
        if (hallado)
            f.seekg(-sizeof(reg), ios::cur);
        else
            f.seekg(0, ios::end);
        f.write((char *) &regNuevo, sizeof(regNuevo));
        Edit1->Text = "";
        Edit2->Text = "";
        Edit3->Text = "";
        MaskEdit1->Text = "";
        Edit1->SetFocus();
    }
    f.close();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender) {
    bool hallado = false;
    RegAlumno reg;
    Word cod;
    reg.mark = '0';
    cod = StrToInt(Edit1->Text);
    fstream f(nomArch.c_str(), ios::in | ios::out | ios::binary);
    if (f.is_open()) {
        do {
            f.read((char *) &reg, sizeof(reg));
            hallado = (reg.cod == cod) && (reg.mark != '*');
        } while (!hallado && !f.eof());
        if (hallado) {
            reg.mark = '*';//marcado como borrado
            f.seekg(-sizeof(reg), ios::cur);
            f.write((char *) &reg, sizeof(reg));
            //Limpiar();
            Edit1->Text = "";
            Edit2->Text = "";
            Edit3->Text = "";
            MaskEdit1->Text = "";
            Edit1->SetFocus();
        }
    }
    f.close();
}

//---------------------------------------------------------------------------
// Funci�n para crear el archivo de �ndice por c�digo:
void __fastcall TForm1::porcodigo1Click(TObject *Sender) {
    RegAlumno reg;
    RegIdxCod regIdx;
    // Abrir el archivo �ndice por c�digo en modo escritura, ios::trunc
    // elimina el contenido que haya tenido previamente este archivo.
    fstream i(nomIdxCod.c_str(), ios::out | ios::trunc | ios::binary);
    // Abrir el archivo de datos en modo lectura.
    fstream f(nomArch.c_str(), ios::in | ios::binary);
    if (f.fail() || i.fail()) {
        return;
    }
    while (!f.eof()) {
        // La posici�n vendr� dada por el valor actual del puntero de lectura.
        regIdx.pos = f.tellp();
        // Leer un registro.
        f.read((char *) &reg, sizeof(reg));
        if (!f.eof() && reg.mark != '*') {
            // Si no llegamos al fin de archivo o leemos la marca de borrado,
            // podemos escribir el c�digo en el archivo �ndice.
            regIdx.cod = reg.cod;
            i.write((char *) &regIdx, sizeof(regIdx));
        }
    }
    // Cerrar los archivos:
    f.close();
    i.close();
}

//---------------------------------------------------------------------------
// Habilitar navegaci�n por c�digo:
void __fastcall TForm1::Button_navIdxClick(TObject *Sender) {
    // Abrir el �ndice y el archivo de datos en modo lectura:
    pf = new fstream(nomArch.c_str(), ios::in | ios::binary);
    pIdx = new fstream(nomIdxCod.c_str(), ios::in | ios::binary);
    if (pf->fail() || pIdx->fail()) {
        delete (pf);
        delete (pIdx);
        return;
    }
    // Declarar como variables un objeto de registro del �ndice por c�digo y
    // otro para un registro de alumno.
    RegIdxCod reg_idx;
    RegAlumno reg_data;
    // Habilitar los botones de navegaci�n:
    Button_NavIdx_fin->Enabled = true;
    Button_NavIdx_sig->Enabled = true;
    Button_navIdx->Enabled = false;

    // Leer y mostrar el primer registro del �ndice
    pIdx->read((char *) &reg_idx, sizeof(RegIdxCod));
    if (!pIdx->eof()) {
        pf->seekg(reg_idx.pos, ios::beg);
        pf->read((char *) &reg_data, sizeof(RegAlumno));
        Edit1->Text = reg_data.cod;
        Edit2->Text = reg_data.nom;
        Edit3->Text = reg_data.dir;
        MaskEdit1->Text = IntToStr(reg_data.fecha.dia) + "/"
                          + IntToStr(reg_data.fecha.mes) + "/" + IntToStr(reg_data.fecha.a�o);
    }
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button_NavIdx_finClick(TObject *Sender) {
    pf->close();
    pIdx->close();
    delete (pf);
    delete (pIdx);
    Button_NavIdx_fin->Enabled = false;
    // Botones para navegaci�n por c�digo
    Button_NavIdx_ant->Enabled = false;
    Button_NavIdx_sig->Enabled = false;
    Button_navIdx->Enabled = true;
    // Botones para navegaci�n por nombre
    Button_NavNombre_ant->Enabled = false;
    Button_NavNombre_sig->Enabled = false;
    Button_NavNombre->Enabled = true;
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button_NavIdx_sigClick(TObject *Sender) {
    // Declarar dos variables de tipo registro
    RegIdxCod reg_idx; // Para el �ndice
    RegAlumno reg_data; // Para el archivo de datos
    // Al presionar el bot�n se leer� el siguiente elemento del �ndice
    pIdx->read((char *) &reg_idx, sizeof(RegIdxCod));
    // Si el bot�n de retroceso est� deshabilitado, habilitarlo:
    if (!Button_NavIdx_ant->Enabled) {
        Button_NavIdx_ant->Enabled = true;
    }
    // Mover el puntero de lectura del archivo de datos a la posici�n
    // almacenada en el �ndice y leer los datos del registro.
    pf->seekg(reg_idx.pos, ios::beg);
    pf->read((char *) &reg_data, sizeof(RegAlumno));
    // Verificar la posici�n actual del puntero:
    std::streampos current_pos = pIdx->tellg();
    std::streampos end_pos = pIdx->seekg(0, ios::end).tellg();
    if (current_pos == end_pos) {
        // Deshabilitar el bot�n de avance:
        Button_NavIdx_sig->Enabled = false;
    } else {
        // Devolver el puntero de lectura a la posici�n actual.
        pIdx->seekg(current_pos);
    }
    // Mostrar los datos en la inferfaz.
    Edit1->Text = reg_data.cod;
    Edit2->Text = reg_data.nom;
    Edit3->Text = reg_data.dir;
    MaskEdit1->Text = IntToStr(reg_data.fecha.dia) + "/"
                      + IntToStr(reg_data.fecha.mes) + "/" + IntToStr(reg_data.fecha.a�o);
}

//---------------------------------------------------------------------------
void __fastcall TForm1::Button_NavIdx_antClick(TObject *Sender) {
    // Declarar dos variables de tipo registro
    RegIdxCod reg_idx; // Para el �ndice
    RegAlumno reg_data; // Para el archivo de datos
    // Al presionar el bot�n se leer� el anterior elemento del �ndice
    pIdx->seekg(-2 * sizeof(RegIdxCod), ios::cur);
    pIdx->read((char *) &reg_idx, sizeof(RegIdxCod));
    // Si el bot�n de avance est� deshabilitado, habilitarlo:
    if (!Button_NavIdx_sig->Enabled) {
        Button_NavIdx_sig->Enabled = true;
    }
    // Mover el puntero de lectura de el archivo de datos a la posici�n
    // almacenada en el �ndice y leer los datos del registro.
    pf->seekg(reg_idx.pos, ios::beg);
    pf->read((char *) &reg_data, sizeof(RegAlumno));
    // Verificar la posici�n actual del puntero:
    std::streampos current_pos = pIdx->tellg();
    std::streampos end_pos = pIdx->seekg(sizeof(RegIdxCod), ios::beg).tellg();
    if (current_pos == end_pos) {
        // Deshabilitar el bot�n de retroceso:
        Button_NavIdx_ant->Enabled = false;
    } else {
        // Devolver el puntero de lectura a la posici�n actual.
        pIdx->seekg(current_pos);
    }
    // Mostrar los datos en la inferfaz.
    Edit1->Text = reg_data.cod;
    Edit2->Text = reg_data.nom;
    Edit3->Text = reg_data.dir;
    MaskEdit1->Text = IntToStr(reg_data.fecha.dia) + "/"
                      + IntToStr(reg_data.fecha.mes) + "/" + IntToStr(reg_data.fecha.a�o);
}

//---------------------------------------------------------------------------
// Ordenamiento por c�digo de los registros del �ndice:
void __fastcall TForm1::porcodigo2Click(TObject *Sender) {
    // Obtener el n�mero de elementos en el archivo �ndice:
    fstream idx(nomIdxCod.c_str(), ios::in | ios::out | ios::binary);
    if (idx.fail()) {
        return;
    }
    int n = sizeof(idx) / sizeof(RegIdxCod);
    RegIdxCod reg_i, reg_j; // Variables de registro.

    // Algoritmo InsertionSort para archivos
    // El algoritmo compara el c�digo del reg_i y reg_j
    // y ordena de menor a mayor.
    for (int i = 1; i < n; i++) {
        idx.seekg(i * sizeof(RegIdxCod), ios::beg);
        idx.read((char *) &reg_i, sizeof(RegIdxCod));
        int j = i - 1;
        idx.seekg(j * sizeof(RegIdxCod), ios::beg);
        idx.read((char *) &reg_j, sizeof(RegIdxCod));
        // Ordenar los registros anteriores a reg_i del archivo:
        while (j >= 0 && reg_j.cod > reg_i.cod) {
            idx.seekp((j + 1) * sizeof(RegIdxCod), ios::beg);
            idx.write((char *) &reg_j, sizeof(RegIdxCod));
            j--;
            if (j >= 0) {
                idx.seekg(j * sizeof(RegIdxCod), ios::beg);
                idx.read((char *) &reg_j, sizeof(RegIdxCod));
            }

        }
        idx.seekp((j + 1) * sizeof(RegIdxCod), ios::beg);
        idx.write((char *) &reg_i, sizeof(RegIdxCod));
    }
    idx.close();
}

//---------------------------------------------------------------------------
void TForm1::nomToUpcase() {
    //Abrir el archivo de datos en modo lectura/escritura
    fstream f(nomArch.c_str(), ios::in | ios::out | ios::binary);
    if (!f.is_open())
        return;

    //Leer un registro
    RegAlumno reg;
    int i = 0;
    while (f.read((char *) &reg, sizeof(reg))) {
        // Modificar nom y pasar a mayusculas
        AnsiString str = reg.nom;
        str = str.UpperCase();
        // Crear un registro temporal
        RegAlumno modificado;
        modificado.mark = reg.mark;
        modificado.cod = reg.cod;
        strcpy(modificado.nom, str.c_str());
        strcpy(modificado.dir, reg.dir);
        modificado.fecha = reg.fecha;
        // Mover el cursor de escritura al punto de insersi�n
        f.seekp(i * sizeof(modificado), std::ios::beg);
        // Escribir el nuevo registro en el archivo
        f.write((char *) &modificado, sizeof(modificado));
        // Mover el cursor de lectura al siguiente registro
        i++;
        f.seekg(i * sizeof(modificado), std::ios::beg);
    }
    f.close();
}

void __fastcall TForm1::Button_ActualizarClick(TObject *Sender) {
    nomToUpcase();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pornombre1Click(TObject *Sender) {
    RegAlumno reg;
    RegIdxNom regIdx;
    // Abrir el archivo �ndice por nombre en modo escritura, ios::trunc
    // elimina el contenido que haya tenido previamente este archivo.
    fstream i(nomIdxNom.c_str(), ios::out | ios::trunc | ios::binary);
    // Abrir el archivo de datos en modo lectura.
    fstream f(nomArch.c_str(), ios::in | ios::binary);
    if (f.fail() || i.fail()) {
        return;
    }
    while (!f.eof()) {
        // La posici�n vendr� dada por el valor actual del puntero de lectura.
        regIdx.pos = f.tellp();
        // Leer un registro.
        f.read((char *) &reg, sizeof(reg));
        if (!f.eof() && reg.mark != '*') {
            // Si no llegamos al fin de archivo o leemos la marca de borrado,
            // podemos escribir el c�digo en el archivo �ndice.
            strcpy(regIdx.nom, reg.nom);
            i.write((char *) &regIdx, sizeof(regIdx));
        }
    }
    // Cerrar los archivos:
    f.close();
    i.close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_NavNombreClick(TObject *Sender) {
    // Abrir el �ndice y el archivo de datos en modo lectura:
    pf = new fstream(nomArch.c_str(), ios::in | ios::binary);
    pIdx = new fstream(nomIdxNom.c_str(), ios::in | ios::binary);
    if (pf->fail() || pIdx->fail()) {
        delete (pf);
        delete (pIdx);
        return;
    }
    // Declarar como variables un objeto de registro del �ndice por c�digo y
    // otro para un registro de alumno.
    RegIdxNom reg_idx;
    RegAlumno reg_data;
    // Habilitar los botones de navegaci�n:
    Button_NavIdx_fin->Enabled = true;
    Button_NavNombre_sig->Enabled = true;
    Button_NavNombre->Enabled = false;

    // Leer y mostrar el primer registro del �ndice
    pIdx->read((char *) &reg_idx, sizeof(RegIdxNom));
    if (!pIdx->eof()) {
        pf->seekg(reg_idx.pos, ios::beg);
        pf->read((char *) &reg_data, sizeof(RegAlumno));
        Edit1->Text = reg_data.cod;
        Edit2->Text = reg_data.nom;
        Edit3->Text = reg_data.dir;
        MaskEdit1->Text = IntToStr(reg_data.fecha.dia) + "/" + IntToStr(reg_data.fecha.mes)
                          + "/" + IntToStr(reg_data.fecha.a�o);
    }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_NavNombre_antClick(TObject *Sender) {
// Declarar dos variables de tipo registro
    RegIdxNom reg_idx; // Para el �ndice
    RegAlumno reg_data; // Para el archivo de datos
    // Al presionar el bot�n se leer� el anterior elemento del �ndice
    pIdx->seekg(-2 * sizeof(RegIdxNom), ios::cur);
    pIdx->read((char *) &reg_idx, sizeof(RegIdxNom));
    // Si el bot�n de avance est� deshabilitado, habilitarlo:
    if (!Button_NavNombre_sig->Enabled) {
        Button_NavNombre_sig->Enabled = true;
    }
    // Mover el puntero de lectura del archivo de datos a la posici�n
    // almacenada en el �ndice y leer los datos del registro.
    pf->seekg(reg_idx.pos, ios::beg);
    pf->read((char *) &reg_data, sizeof(RegAlumno));
    // Verificar la posici�n actual del puntero:
    std::streampos current_pos = pIdx->tellg();
    std::streampos end_pos = pIdx->seekg(sizeof(RegIdxNom), ios::beg).tellg();
    if (current_pos == end_pos) {
        // Deshabilitar el bot�n de retroceso:
        Button_NavNombre_ant->Enabled = false;
    } else {
        // Devolver el puntero de lectura a la posici�n actual.
        pIdx->seekg(current_pos);
    }
    // Mostrar los datos en la inferfaz.
    Edit1->Text = reg_data.cod;
    Edit2->Text = reg_data.nom;
    Edit3->Text = reg_data.dir;
    MaskEdit1->Text = IntToStr(reg_data.fecha.dia) + "/"
                      + IntToStr(reg_data.fecha.mes) + "/" + IntToStr(reg_data.fecha.a�o);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button_NavNombre_sigClick(TObject *Sender) {
// Declarar dos variables de tipo registro
    RegIdxNom reg_idx; // Para el �ndice
    RegAlumno reg_data; // Para el archivo de datos
    // Al presionar el bot�n se leer� el siguiente elemento del �ndice
    pIdx->read((char *) &reg_idx, sizeof(RegIdxNom));
    // Si el bot�n de retroceso est� deshabilitado, habilitarlo:
    if (!Button_NavNombre_ant->Enabled) {
        Button_NavNombre_ant->Enabled = true;
    }
    // Mover el puntero de lectura del archivo de datos a la posici�n
    // almacenada en el �ndice y leer los datos del registro.
    pf->seekg(reg_idx.pos, ios::beg);
    pf->read((char *) &reg_data, sizeof(RegAlumno));
    // Verificar la posici�n actual del puntero:
    std::streampos current_pos = pIdx->tellg();
    std::streampos end_pos = pIdx->seekg(0, ios::end).tellg();
    if (current_pos == end_pos) {
        // Deshabilitar el bot�n de avance:
        Button_NavNombre_sig->Enabled = false;
    } else {
        // Devolver el puntero de lectura a la posici�n actual.
        pIdx->seekg(current_pos);
    }
    // Mostrar los datos en la inferfaz.
    Edit1->Text = reg_data.cod;
    Edit2->Text = reg_data.nom;
    Edit3->Text = reg_data.dir;
    MaskEdit1->Text = IntToStr(reg_data.fecha.dia) + "/"
                      + IntToStr(reg_data.fecha.mes) + "/" + IntToStr(reg_data.fecha.a�o);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::pornombre2Click(TObject *Sender) {
    // Obtener el n�mero de elementos en el archivo �ndice:
    fstream idx(nomIdxNom.c_str(), ios::in | ios::out | ios::binary);
    if (idx.fail()) {
        return;
    }
    int n = sizeof(idx) / sizeof(RegIdxNom);
    RegIdxNom reg_i, reg_j; // Variables de registro.

    // Algoritmo InsertionSort para archivos
    // El algoritmo compara el nombre del reg_i y reg_j
    // y ordena de menor a mayor.
    for (int i = 1; i < n; i++) {
        idx.seekg(i * sizeof(RegIdxNom), ios::beg);
        idx.read((char *) &reg_i, sizeof(RegIdxNom));
        int j = i - 1;
        idx.seekg(j * sizeof(RegIdxNom), ios::beg);
        idx.read((char *) &reg_j, sizeof(RegIdxNom));
        // Ordenar los registros anteriores a reg_i del archivo:
        while (j >= 0 && reg_j.nom[0] > reg_i.nom[0]) {
            idx.seekp((j + 1) * sizeof(RegIdxNom), ios::beg);
            idx.write((char *) &reg_j, sizeof(RegIdxNom));
            j--;
            if (j >= 0) {
                idx.seekg(j * sizeof(RegIdxNom), ios::beg);
                idx.read((char *) &reg_j, sizeof(RegIdxNom));
            }
        }
        idx.seekp((j + 1) * sizeof(RegIdxNom), ios::beg);
        idx.write((char *) &reg_i, sizeof(RegIdxNom));
    }
    idx.close();
}
//---------------------------------------------------------------------------

