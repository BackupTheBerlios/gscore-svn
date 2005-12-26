object frm_abc: Tfrm_abc
  Left = 235
  Top = 154
  Width = 665
  Height = 530
  Caption = 'Test ABCp DLL'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Panel1: TPanel
    Left = 0
    Top = 41
    Width = 657
    Height = 455
    Align = alClient
    Caption = 'Panel1'
    TabOrder = 0
    object txt_abc: TMemo
      Left = 1
      Top = 1
      Width = 264
      Height = 453
      Align = alLeft
      Lines.Strings = (
        'X:1')
      TabOrder = 0
    end
    object lst_toks: TListBox
      Left = 289
      Top = 1
      Width = 367
      Height = 453
      Align = alClient
      ItemHeight = 13
      TabOrder = 1
    end
    object Panel2: TPanel
      Left = 265
      Top = 1
      Width = 24
      Height = 453
      Align = alLeft
      TabOrder = 2
    end
  end
  object Panel3: TPanel
    Left = 0
    Top = 0
    Width = 657
    Height = 41
    Align = alTop
    TabOrder = 1
    object Label1: TLabel
      Left = 16
      Top = 8
      Width = 85
      Height = 20
      Caption = 'ABC piece'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object Label2: TLabel
      Left = 288
      Top = 8
      Width = 59
      Height = 20
      Caption = 'Tokens'
      Font.Charset = DEFAULT_CHARSET
      Font.Color = clWindowText
      Font.Height = -16
      Font.Name = 'MS Sans Serif'
      Font.Style = [fsBold]
      ParentFont = False
    end
    object btn_scan: TButton
      Left = 208
      Top = 8
      Width = 49
      Height = 25
      Caption = 'Scan'
      TabOrder = 0
      OnClick = btn_scanClick
    end
    object btn_clear: TButton
      Left = 368
      Top = 8
      Width = 57
      Height = 25
      Caption = 'Clear'
      TabOrder = 1
      OnClick = btn_clearClick
    end
  end
end
