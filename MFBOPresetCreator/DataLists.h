#pragma once

#include "qstring.h"
#include "qstringlist.h"
#include "stdafx.h"

class DataLists : public QObject
{
  Q_OBJECT

public:
  static QStringList getBodiesNameVersions();
  static QStringList getWindowOpeningModes();
  static QStringList getAppThemes();
  static QStringList getLanguages();
  static QStringList getAssistedConversionActions();

private:
  DataLists(){};
};
