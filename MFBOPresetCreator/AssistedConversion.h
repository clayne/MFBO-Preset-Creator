#pragma once

#include "DataLists.h"
#include "Enum.h"
#include "Struct.h"
#include "Utils.h"
#include "stdafx.h"
#include <utility>

class AssistedConversion : public QDialog
{
  Q_OBJECT

public:
  explicit AssistedConversion(QWidget* parent, const Struct::Settings& aSettings);

private:
  const Struct::Settings mSettings;

  void setWindowProperties();
  void initializeGUI();
  void setupInterface(QGridLayout& aLayout);

  std::vector<std::pair<QString, QString>> scanForFilesByExtension(const QString& aRootDir, const QString& aFileExtension);

private slots:
  void chooseInputDirectory();
  void launchSearchProcess();
};
