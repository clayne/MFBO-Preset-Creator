#pragma once

#include "HTTPDownloader.hpp"
#include "Struct.h"
#include "Utils.h"
#include "stdafx.h"
#include <iostream>
#include <string>

class Update : public QDialog
{
  Q_OBJECT

public:
  Update(QWidget* parent);

private:
  Struct::Settings mSettings;

  struct MemoryStruct
  {
    char* memory;
    size_t size;
  };

  void setWindowProperties();
  void initializeGUI();
  void setupInterface(QGridLayout& aLayout);
  void refreshUI();
  QString getLastAvailableVersion();
};