#include "config.h"

ConfigHandler::ConfigHandler(RailsDialog *p) :
  QXmlDefaultHandler()
{
  parent = p;
}

bool ConfigHandler::startDocument()
{
  inConf = false;
  return true;
}

bool ConfigHandler::startElement( const QString &, const QString &, const QString &name, const QXmlAttributes &attrs )
{
  if (inConf && name == "tab") {
    for(int i = 0; i < attrs.count(); i++) {
      if (attrs.localName(i) == "name")
        tName = attrs.value(i);
      else if (attrs.localName(i) == "dir")
        tDir = attrs.value(i);
      else if (attrs.localName(i) == "command")
        tCommand = attrs.value(i);
    }
  }
  else if ( name == "krails" ) {
    inConf = true;
  }

  return true;
}


bool ConfigHandler::endElement( const QString&, const QString&, const QString &name )
{
  if (name == "krails")
    inConf = false;
  else if (name == "tab") {
    if (!tName.isNull()) {
      parent->newSession(tName, tDir, tCommand);
    }
    tName = tDir = tCommand = QString::null;
  }

  return true;
}
