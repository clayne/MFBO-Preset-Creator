#pragma once

#include "Enum.h"
#include <QObject>
#include <QString>
#include <QStringList>

class DataLists : public QObject
{
  Q_OBJECT

public:
  // Lists for bodies names and versions
  static QStringList getBodiesNamesVersions();
  static QStringList getBodiesNames();
  static QStringList getVersionsFromBodyName(BodyName aBody);
  static BodyNameVersion getBodyNameVersion(BodyName aBody, int aRelativeVersion);
  static std::pair<int, int> getSplittedNameVersionFromBodyVersion(BodyNameVersion aBodyVersion);

  // Other data lists
  static QStringList getWindowOpeningModes();
  static QStringList getAppThemes();
  static QStringList getLanguages();
  static QStringList getAssistedConversionActions();

private:
  DataLists(){};
};
