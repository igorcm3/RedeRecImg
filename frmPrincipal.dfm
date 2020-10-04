object FormPrincipal: TFormPrincipal
  Left = 0
  Top = 0
  Caption = 'RNA - Reconhecimento de n'#250'meros'
  ClientHeight = 452
  ClientWidth = 662
  Color = clWhite
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'Tahoma'
  Font.Style = []
  OldCreateOrder = False
  Position = poDesktopCenter
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
    object tbiClassificacao: TTabSheet
      Caption = 'Classifica'#231#227'o'
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
        Left = 424
        Top = 29
        Width = 61
        Height = 13
        Alignment = taCenter
        Anchors = [akLeft, akTop, akRight, akBottom]
        Caption = 'Classifica'#231#227'o'
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
          Cursor = crCross
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
      object Chart1: TChart
        Left = 3
        Top = 16
        Width = 409
        Height = 313
        Legend.Visible = False
        Title.Font.Color = clBlack
        Title.Font.Height = -16
        Title.Font.Style = [fsBold]
        Title.Text.Strings = (
          'Curva de Treinamento da Rede Neural')
        Title.Transparent = False
        BottomAxis.MinimumOffset = 3
        LeftAxis.MinimumOffset = 5
        View3D = False
        BevelOuter = bvNone
        Color = clWhite
        TabOrder = 0
        DefaultCanvas = 'TGDIPlusCanvas'
        ColorPaletteIndex = 13
        object Series1: TFastLineSeries
          SeriesColor = clRed
          ValueFormat = '#.##0,00###'
          LinePen.Color = clRed
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
        object Series4: TFastLineSeries
          SeriesColor = clBlue
          Title = 'Series2'
          LinePen.Color = clBlue
          LinePen.Width = 2
          XValues.Name = 'X'
          XValues.Order = loAscending
          YValues.Name = 'Y'
          YValues.Order = loNone
        end
      end
      object meTreinamento: TMemo
        Left = 418
        Top = 16
        Width = 215
        Height = 321
        ScrollBars = ssBoth
        TabOrder = 1
      end
      object btnIniciarTreinamento: TButton
        Left = 418
        Top = 379
        Width = 100
        Height = 22
        Caption = 'Iniciar'
        TabOrder = 2
        OnClick = btnIniciarTreinamentoClick
      end
      object btnCancelarTreinamento: TButton
        Left = 533
        Top = 378
        Width = 100
        Height = 24
        Caption = 'Cancelar'
        TabOrder = 3
        OnClick = btnCancelarTreinamentoClick
      end
    end
  end
end
