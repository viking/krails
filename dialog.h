#ifndef __DIALOG_H
#define __DIALOG_H

#include <qlayout.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qdir.h>
#include <qxml.h>
#include <kdirselectdialog.h>
#include <kfiledialog.h>
#include <kcombobox.h>
#include <kpushbutton.h>
#include <klineedit.h>
#include <kapplication.h>
#include <kurl.h>
#include <ksimpleconfig.h>
#include <dcopref.h>

class RailsDialog : public QWidget
{
  Q_OBJECT
public:
  RailsDialog( QWidget * parent = 0, const char * name = 0, WFlags f = 0, QString rDir = QString::null, QString rConf = QString::null, QString rApp = QString::null );
  void newSession( QString name, QString subpath = QString::null, QString exec = QString::null );

  KComboBox *cbRailsApp;

private slots:
  void go();
  void changeDir();
  void changeConf();
  void appChanged(int);

private:
  void findApplications();
  void setupSession( QString name, QString subpath = QString::null, QString exec = QString::null );

  QGridLayout *grid;
  QHBox *hbox;
  KLineEdit *leRailsDir, *leTabConf;
  KPushButton *btnGo, *btnCancel, *btnDir, *btnConf;
  KConfig *conf;

  bool saveDir, saveConf, saveApp;
  QString railsPath, appDir, tabConf, appName;
  QCString dcopService;
  DCOPRef konsole, session;
};

#include "config.h"
#endif
