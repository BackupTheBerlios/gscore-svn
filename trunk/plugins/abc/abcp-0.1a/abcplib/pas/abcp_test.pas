unit abcp_test;

interface

uses
  abcp, Windows, Messages, SysUtils, Variants, Classes, Graphics, Controls, Forms,
  Dialogs, StdCtrls, ExtCtrls;

type
  Tfrm_abc = class(TForm)
    Panel1: TPanel;
    txt_abc: TMemo;
    lst_toks: TListBox;
    Panel2: TPanel;
    Panel3: TPanel;
    Label1: TLabel;
    btn_scan: TButton;
    Label2: TLabel;
    btn_clear: TButton;
    procedure btn_scanClick(Sender: TObject);
    procedure btn_clearClick(Sender: TObject);
  private
    { Private declarations }
  public
    { Public declarations }
  end;

var
  frm_abc: Tfrm_abc;

implementation

{$R *.dfm}

function handler(h:pointer):integer; cdecl;
  var i:integer;
begin
   i:=frm_abc.lst_toks.Items.Add( abcStateName(abcState(h)) + '    ' +
                                  abcTokenName(abcToken(h)) + '    ' +
                                  abcString(h));
   handler:=0;
end;

procedure Tfrm_abc.btn_scanClick(Sender: TObject);
 var r: integer;
begin
  r := abcScanString(PChar(txt_abc.Text),@handler)
end;


procedure Tfrm_abc.btn_clearClick(Sender: TObject);
begin
  lst_toks.Items.Clear;
end;

end.
