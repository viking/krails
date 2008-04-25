#include "dialog.h"

RailsDialog::RailsDialog( QWidget *parent, const char *name, WFlags f )
  : QVBox(parent, name, f)
{
  railsPath = QDir::homeDirPath() + "/rails";
  setSpacing(5);

  hbox0      = new QHBox( this );
  label0     = new QLabel( "Rails directory:", hbox0 );
  leRailsDir = new KLineEdit( railsPath, hbox0 );
  btnDir     = new KPushButton( "Change", hbox0 );
  leRailsDir->setReadOnly(true);
  hbox0->setSpacing(5);

  hbox1      = new QHBox( this );
  label1     = new QLabel( "Rails application:", hbox1 );
  cbRailsApp = new KComboBox( hbox1 );
  hbox1->setSpacing(5);

  hbox2     = new QHBox( this );
  btnGo     = new KPushButton( "Go", hbox2 );
  btnCancel = new KPushButton( "Cancel", hbox2 );
  hbox2->setSpacing(5);

  connect(btnGo, SIGNAL(clicked()), SLOT(go()));
  connect(btnCancel, SIGNAL(clicked()), kapp, SLOT(quit()));
  connect(btnDir, SIGNAL(clicked()), SLOT(changeDir()));

  findApplications();
}

RailsDialog::~RailsDialog()
{
  delete cbRailsApp;
  delete label1;
  delete hbox1;

  delete btnGo;
  delete btnCancel;
  delete hbox2;
}

void RailsDialog::go()
{
  int errcode, pid;
  QString error;

  QString app = cbRailsApp->currentText();
  appDir = railsPath + "/" + app;

  // fire up konsole
  QString konsoleName( "konsole-script" );
  errcode = KApplication::startServiceByDesktopName( konsoleName, QString::null, &error, &dcopService, &pid );
  konsole.setRef( dcopService, "konsole" );
  session.setRef( dcopService, "session-1" );

  setupSession("spec-dev", "spec");
  newSession("spec");
  newSession("dev1");
  newSession("dev2");
  newSession("dev3");
  newSession("cnsl", "", "script/console");
  newSession("log", "log", "tail -f test.log");
  newSession("db");
  newSession("srv", "", "script/server webrick");
  
  if (QFile::exists(appDir + "/vendor/rails"))
    newSession("src", "vendor/rails");
  else
    newSession("src", "/usr/lib/ruby/gems/1.8/gems");

  newSession("misc");

  kapp->quit();
}

void RailsDialog::changeDir()
{
  KURL url = KDirSelectDialog::selectDirectory(railsPath, true, this, "Select Rails Directory:");
  if (url.isEmpty()) {
    return;
  }
  railsPath = url.path();
  leRailsDir->setText(railsPath);
  findApplications();
}

// find rails applications
void RailsDialog::findApplications()
{
  cbRailsApp->clear();
  QDir railsDir( railsPath );
  QStringList files = railsDir.entryList();
  for ( QStringList::Iterator it = files.begin(); it != files.end(); ++it ) {
    if ( *it == "." || *it == ".." )
      continue;

    QFileInfo info( railsPath + "/" + *it );
    if (info.isDir()) {
      cbRailsApp->insertItem( *it );
    }
  }
}

void RailsDialog::setupSession( QString name, QString subpath, QString exec )
{
  session.send( "renameSession", name );
  session.send( "sendSession", "cd " + appDir + "/" + subpath );
  session.send( "sendSession", "clear" );

  if (!exec.isEmpty())
    session.send( "sendSession", exec );
}

void RailsDialog::newSession( QString name, QString subpath, QString exec )
{
  QString sessionName;
  DCOPReply result = konsole.call( "newSession" );
  result.get(sessionName);
  session.setRef( dcopService, sessionName.utf8() );
  setupSession( name, subpath, exec );
}
