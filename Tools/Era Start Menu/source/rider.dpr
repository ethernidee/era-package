program Rider;

uses
  Forms,
  RiderMain in 'RiderMain.pas' {Main};

{$R *.res}

begin
  Application.Initialize;
  Application.CreateForm(TMain, Main);
  Application.Run;
end.
