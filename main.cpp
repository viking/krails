#include <kapplication.h>
#include <kaboutdata.h>
#include <kcmdlineargs.h>
#include <qrect.h>
#include "dialog.h"

static const char description[] =
I18N_NOOP("KDE Rails Development");

static const char version[] = "0.1";

static KCmdLineOptions options[] =
{
  KCmdLineLastOption
};

int main( int argc, char **argv )
{
  KAboutData about("krails", I18N_NOOP("krails"), version, description, KAboutData::License_GPL, "(C) 2008 Jeremy Stephens", 0, 0, "jeremy.stephens@vanderbilt.edu");
  about.addAuthor( "Jeremy Stephens", 0, "jeremy.stephens@vanderbilt.edu" );
  KCmdLineArgs::init(argc, argv, &about);
  KCmdLineArgs::addCmdLineOptions(options);
  KApplication app;

  int flags = Qt::WStyle_Customize | Qt::WStyle_Title | Qt::WStyle_NormalBorder & ~(Qt::WStyle_Maximize);
  RailsDialog* dialog = new RailsDialog( 0, "Rails Development Helper", flags );

  dialog->adjustSize();
  QRect rect = QApplication::desktop()->geometry();
  dialog->move(rect.center() - dialog->rect().center());

  app.setMainWidget( dialog );
  dialog->show();
  return app.exec();
}
