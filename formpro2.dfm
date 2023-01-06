object Form1: TForm1
  Left = 0
  Top = 0
  Caption = 'Form1'
  ClientHeight = 184
  ClientWidth = 367
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  Menu = MainMenu1
  OnCreate = FormCreate
  TextHeight = 13
  object Label2: TLabel
    Left = 7
    Top = 13
    Width = 33
    Height = 13
    Caption = 'C'#243'digo'
  end
  object Label3: TLabel
    Left = 7
    Top = 44
    Width = 37
    Height = 13
    Caption = 'Nombre'
  end
  object Label4: TLabel
    Left = 7
    Top = 75
    Width = 43
    Height = 13
    Caption = 'Direcci'#243'n'
  end
  object Label5: TLabel
    Left = 7
    Top = 106
    Width = 96
    Height = 13
    Caption = 'fecha de nacimiento'
  end
  object MaskEdit1: TMaskEdit
    Left = 109
    Top = 103
    Width = 73
    Height = 21
    EditMask = '!99/99/0000;1;_'
    MaxLength = 10
    TabOrder = 3
    Text = '  /  /    '
  end
  object Edit1: TEdit
    Left = 61
    Top = 10
    Width = 121
    Height = 21
    TabOrder = 0
    OnExit = Edit1Exit
  end
  object Edit2: TEdit
    Left = 61
    Top = 41
    Width = 121
    Height = 21
    TabOrder = 1
  end
  object Edit3: TEdit
    Left = 61
    Top = 72
    Width = 121
    Height = 21
    TabOrder = 2
  end
  object Button1: TButton
    Left = 7
    Top = 141
    Width = 75
    Height = 25
    Caption = 'guardar'
    TabOrder = 4
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 109
    Top = 141
    Width = 75
    Height = 25
    Caption = 'eliminar'
    TabOrder = 5
    OnClick = Button2Click
  end
  object Button_NavIdx_fin: TButton
    Left = 288
    Top = 70
    Width = 75
    Height = 25
    Caption = 'fin'
    Enabled = False
    TabOrder = 6
    OnClick = Button_NavIdx_finClick
  end
  object Button_NavIdx_ant: TButton
    Left = 287
    Top = 8
    Width = 35
    Height = 25
    Caption = '<<'
    DoubleBuffered = False
    Enabled = False
    ParentDoubleBuffered = False
    TabOrder = 7
    OnClick = Button_NavIdx_antClick
  end
  object Button_NavIdx_sig: TButton
    Left = 328
    Top = 8
    Width = 35
    Height = 25
    Caption = '>>'
    Enabled = False
    TabOrder = 8
    OnClick = Button_NavIdx_sigClick
  end
  object Button_navIdx: TButton
    Left = 205
    Top = 8
    Width = 76
    Height = 25
    Caption = 'NavCodigo'
    TabOrder = 9
    OnClick = Button_navIdxClick
  end
  object Button_Actualizar: TButton
    Left = 205
    Top = 141
    Width = 75
    Height = 25
    Caption = 'Actualizar'
    TabOrder = 10
    OnClick = Button_ActualizarClick
  end
  object Button_NavNombre: TButton
    Left = 205
    Top = 39
    Width = 75
    Height = 25
    Caption = 'Button_NavNombre'
    TabOrder = 11
    OnClick = Button_NavNombreClick
  end
  object Button_NavNombre_ant: TButton
    Left = 286
    Top = 39
    Width = 35
    Height = 25
    Caption = '<<'
    DoubleBuffered = False
    Enabled = False
    ParentDoubleBuffered = False
    TabOrder = 12
    OnClick = Button_NavNombre_antClick
  end
  object Button_NavNombre_sig: TButton
    Left = 327
    Top = 39
    Width = 35
    Height = 25
    Caption = '>>'
    Enabled = False
    TabOrder = 13
    OnClick = Button_NavNombre_sigClick
  end
  object MainMenu1: TMainMenu
    Left = 304
    Top = 112
    object indices1: TMenuItem
      Caption = 'indices'
      object porcodigo1: TMenuItem
        Caption = 'por codigo'
        OnClick = porcodigo1Click
      end
      object pornombre1: TMenuItem
        Caption = 'por nombre'
        OnClick = pornombre1Click
      end
    end
    object ordenar1: TMenuItem
      Caption = 'ordenar'
      object porcodigo2: TMenuItem
        Caption = 'por codigo'
        OnClick = porcodigo2Click
      end
      object pornombre2: TMenuItem
        Caption = 'por nombre'
        OnClick = pornombre2Click
      end
    end
  end
end
