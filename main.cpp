#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <qrect.h>
#include <qcstring.h>
#include <qstring.h>
#include "dialog.h"

static const char description[] =
I18N_NOOP("KDE Rails Development");

static const char version[] = "0.1";

static KCmdLineOptions options[] =
{
  { "working-dir <dir>", "directory to look for apps", 0 },
  { "tab-conf <file>", "XML configuration file", 0 },
  { "app-name <name>", "application name", 0 },
  KCmdLineLastOption
};

int main( int argc, char **argv )
{
  KAboutData about("krails", I18N_NOOP("krails"), version, description, KAboutData::License_GPL, "(C) 2008 Jeremy Stephens", 0, 0, "jeremy.stephens@vanderbilt.edu");
  about.addAuthor( "Jeremy Stephens", 0, "jeremy.stephens@vanderbilt.edu" );
  KCmdLineArgs::init(argc, argv, &about);
  KCmdLineArgs::addCmdLineOptions(options);
  KApplication app;

  KCmdLineArgs *args = KCmdLineArgs::parsedArgs();
  QCString rDir  = args->getOption("working-dir");
  QCString rConf = args->getOption("tab-conf");
  QCString rApp  = args->getOption("app-name");

  int flags = Qt::WStyle_Customize | Qt::WStyle_Title | Qt::WStyle_NormalBorder & ~(Qt::WStyle_Maximize);
  RailsDialog* dialog = new RailsDialog( 0, "Rails Development Helper", flags, rDir, rConf, rApp );

  dialog->adjustSize();
  QRect rect = QApplication::desktop()->geometry();
  dialog->move(rect.center() - dialog->rect().center());

  app.setMainWidget( dialog );
  dialog->show();
  return app.exec();
}
