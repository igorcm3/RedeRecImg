object FormPrincipal: TFormPrincipal
  Left = 0
  Top = 0
  Caption = 'FormPrincipal'
  ClientHeight = 333
  ClientWidth = 613
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object tbiTreinamento: TPageControl
    Left = 0
    Top = 0
    Width = 613
    Height = 333
    ActivePage = tbiClassificacao
    Align = alClient
    TabOrder = 0
    ExplicitHeight = 380
    object tbiClassificacao: TTabSheet
      Caption = 'Classifica'#231#227'o'
      ExplicitWidth = 281
      ExplicitHeight = 165
      DesignSize = (
        605
        305)
      object Splitter1: TSplitter
        Left = 328
        Top = 24
        Width = 1
        Height = 249
        Align = alNone
        Color = clSilver
        ParentColor = False
      end
      object Label1: TLabel
        Left = 400
        Top = 29
        Width = 153
        Height = 13
        Alignment = taCenter
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = 'Classifica'#231#227'o'
      end
      object GroupBox1: TGroupBox
        Left = 16
        Top = 24
        Width = 265
        Height = 201
        Caption = 'Desenho'
        TabOrder = 0
        object pnDesenho: TPaintBox
          Left = 2
          Top = 15
          Width = 261
          Height = 184
          Align = alClient
          OnMouseMove = pnDesenhoMouseMove
          OnPaint = pnDesenhoPaint
          ExplicitLeft = 152
          ExplicitTop = 80
          ExplicitWidth = 105
          ExplicitHeight = 105
        end
      end
      object Button1: TButton
        Left = 16
        Top = 248
        Width = 265
        Height = 25
        Caption = 'Reconhecer'
        TabOrder = 1
      end
      object ListBox1: TListBox
        Left = 392
        Top = 48
        Width = 161
        Height = 225
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
      ExplicitWidth = 281
      ExplicitHeight = 165
    end
  end
end
