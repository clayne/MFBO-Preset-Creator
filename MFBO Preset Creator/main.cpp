﻿#include "MFBOPresetCreator.h"
#include "Utils.h"

#include <QtWidgets/QApplication>
#include <QIcon>

int main(int argc, char* argv[])
{
  // Create the main GUI
  QApplication lMainApplication(argc, argv);
  lMainApplication.setApplicationDisplayName("MFBOPC v." + Utils::getProgramVersion());
  lMainApplication.setApplicationVersion(Utils::getProgramVersion());
  lMainApplication.setWindowIcon(QIcon(":/software/icon"));

  // Create the main window
  MFBOPresetCreator lMainWindow;
  return lMainApplication.exec();
}
