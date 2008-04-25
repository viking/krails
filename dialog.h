#ifndef __DIALOG_H
#define __DIALOG_H

#include <qvbox.h>
#include <qhbox.h>
#include <qlabel.h>
#include <qdir.h>
#include <kdirselectdialog.h>
#include <kcombobox.h>
#include <kpushbutton.h>
#include <klineedit.h>
#include <kapplication.h>
#include <kurl.h>
#include <dcopref.h>

class RailsDialog : public QVBox
{
  Q_OBJECT
public:
  RailsDialog( QWidget * parent = 0, const char * name = 0, WFlags f = 0 );
  ~RailsDialog();

  KComboBox *cbRailsApp;

private slots:
  void go();
  void changeDir();

private:
  void findApplications();
  void setupSession( QString name, QString subpath = QString::null, QString exec = QString::null );
  void newSession( QString name, QString subpath = QString::null, QString exec = QString::null );

  QHBox *hbox0, *hbox1, *hbox2;
  QLabel *label0, *label1;
  KLineEdit *leRailsDir;
  KPushButton *btnGo, *btnCancel, *btnDir;

  QString railsPath, appDir;
  QCString dcopService;
  DCOPRef konsole, session;
};

#endif
