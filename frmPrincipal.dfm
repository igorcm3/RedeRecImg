object FormPrincipal: TFormPrincipal
  Left = 0
  Top = 0
  Caption = 'FormPrincipal'
  ClientHeight = 452
  ClientWidth = 662
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  OnCreate = FormCreate
  PixelsPerInch = 96
  TextHeight = 13
  object tbiTreinamento: TPageControl
    Left = 0
    Top = 0
    Width = 662
    Height = 452
    ActivePage = tbiClassificacao
    Align = alClient
    TabOrder = 0
    ExplicitWidth = 613
    ExplicitHeight = 333
    object tbiClassificacao: TTabSheet
      Caption = 'Classifica'#231#227'o'
      ExplicitLeft = 8
      ExplicitTop = 28
      ExplicitWidth = 605
      ExplicitHeight = 381
      DesignSize = (
        654
        424)
      object Splitter1: TSplitter
        Left = 368
        Top = 29
        Width = 2
        Height = 343
        Align = alNone
        Color = clSilver
        ParentColor = False
      end
      object Label1: TLabel
        Left = 400
        Top = 29
        Width = 202
        Height = 60
        Alignment = taCenter
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = 'Classifica'#231#227'o'
        ExplicitWidth = 153
        ExplicitHeight = 17
      end
      object gbDesenho: TGroupBox
        Left = 16
        Top = 24
        Width = 304
        Height = 317
        Caption = 'Desenho'
        TabOrder = 0
        object pnDesenho: TPaintBox
          Left = 2
          Top = 15
          Width = 300
          Height = 300
          Align = alClient
          OnMouseDown = pnDesenhoMouseDown
          OnMouseMove = pnDesenhoMouseMove
          OnMouseUp = pnDesenhoMouseUp
          OnPaint = pnDesenhoPaint
          ExplicitLeft = -20
          ExplicitTop = 24
          ExplicitWidth = 261
          ExplicitHeight = 184
        end
      end
      object btnReconhecer: TButton
        Left = 16
        Top = 347
        Width = 304
        Height = 25
        Caption = 'Reconhecer'
        TabOrder = 1
        OnClick = btnReconhecerClick
      end
      object ListBox1: TListBox
        Left = 424
        Top = 48
        Width = 178
        Height = 324
        ItemHeight = 13
        Items.Strings = (
          '0 - 0%'
          '1 - 0%'
          '2 - 0%'
          '3 - 0%'
          '4 - 0%'
          '5 - 0%'
          '6 - 0%'
          '7 - 0%'
          '8 - 0%'
          '9 - 0%')
        TabOrder = 2
      end
    end
    object TabSheet2: TTabSheet
      Caption = 'Treiamento'
      ImageIndex = 1
      ExplicitWidth = 605
      ExplicitHeight = 305
    end
  end
end
