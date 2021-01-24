﻿#include "MFBOPresetCreator.h"
#include "Utils.h"
#include "stdafx.h"

int main(int argc, char* argv[])
{
  auto currentExitCode{0};

  do
  {
    // Reset the value
    Utils::RESTART_PENDING = false;

    const auto& lAppVersion{Utils::getApplicationVersion()};

    // Create the main GUI handler
    QApplication lMainApplication(argc, argv);
    lMainApplication.setApplicationDisplayName(QString("MFBOPC (v.%1)").arg(lAppVersion));
    lMainApplication.setApplicationName("MFBOPresetCreator");
    lMainApplication.setApplicationVersion(lAppVersion);
    lMainApplication.setWindowIcon(QIcon(QPixmap(":/application/icon")));
    lMainApplication.setAttribute(Qt::AA_EnableHighDpiScaling);

    // Set the codec
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));

    // Show the splash screen
    const QPixmap lSplashScreenBackground(":/application/splashscreen");

    QSplashScreen lSplashScreen(lSplashScreenBackground.scaled(800, 450));
    lSplashScreen.showMessage(QString("MFBOPC (v.%1): Starting the application...").arg(lAppVersion), Qt::AlignBottom | Qt::AlignRight, Qt::white);
    lSplashScreen.show();
    lMainApplication.processEvents();

    // Update the message
    lSplashScreen.showMessage(QString("MFBOPC (v.%1): Reading and applying custom fonts...").arg(lAppVersion), Qt::AlignBottom | Qt::AlignRight, Qt::white);
    lMainApplication.processEvents();

    // Embed custom fonts
    QFontDatabase::addApplicationFont(":/fonts/Roboto");

    // Update the message
    lSplashScreen.showMessage(QString("MFBOPC (v.%1): Loading settings...").arg(lAppVersion), Qt::AlignBottom | Qt::AlignRight, Qt::white);
    lMainApplication.processEvents();

    // Read settings file
    auto lSettings{Utils::loadSettingsFromFile()};

    // Update the message
    lSplashScreen.showMessage(QString("MFBOPC (v.%1): Applying translation files...").arg(lAppVersion), Qt::AlignBottom | Qt::AlignRight, Qt::white);
    lMainApplication.processEvents();

    // Apply custom language and translation
    auto lLanguageToSet{Utils::getShortLanguageNameFromEnum(static_cast<int>(lSettings.language))};
    auto lTranslator{new QTranslator()};
    if (lTranslator->load(QString(":/translations/mfbopc_%1.qm").arg(lLanguageToSet)))
    {
      lMainApplication.installTranslator(lTranslator);
    }

    // Apply default Qt language and translation
    auto lQtBaseTranslator{new QTranslator()};
    if (lQtBaseTranslator->load("qt_" + lLanguageToSet + ".qm", QLibraryInfo::location(QLibraryInfo::TranslationsPath)))
    {
      lMainApplication.installTranslator(lQtBaseTranslator);
    }

    // Update the message
    lSplashScreen.showMessage(QString("MFBOPC (v.%1): Creating the main window...").arg(lAppVersion), Qt::AlignBottom | Qt::AlignRight, Qt::white);
    lMainApplication.processEvents();

    // Create and show the main window
    MFBOPresetCreator lMainWindow(lSettings);

    // Make the splash screen disappear when the main window is displayed
    lSplashScreen.finish(&lMainWindow);

    // Launch the application
    currentExitCode = lMainApplication.exec();
  } while (currentExitCode == Utils::EXIT_CODE_REBOOT);

  return currentExitCode;
}
