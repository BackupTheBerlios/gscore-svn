program abcptest;

uses
  Forms,
  abcp_test in 'abcp_test.pas' {frm_abc},
  abcp in 'abcp.pas';

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(Tfrm_abc, frm_abc);
  Application.Run;
end.
