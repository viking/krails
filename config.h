#ifndef __CONFIG_H
#define __CONFIG_H

#include <qxml.h>
#include "dialog.h"

class ConfigHandler : public QXmlDefaultHandler
{
public: 
  ConfigHandler( RailsDialog *p ); 

  bool startDocument();
  bool endElement( const QString&, const QString&, const QString & );
  bool startElement( const QString&, const QString&, const QString &, const QXmlAttributes & );

private:
  bool inConf;
  QString tName, tDir, tCommand; 
  RailsDialog *parent;
};

#endif
