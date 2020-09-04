﻿#include "MFBOPresetCreator.h"

MFBOPresetCreator::MFBOPresetCreator(QWidget* parent)
  : QMainWindow(parent)
  , mSettings(Utils::loadSettingsFromFile())
  , mMinimumFirstColmunWith(275)
{
  // Construct the GUI
  ui.setupUi(this);
  this->initializeGUI();
  this->refreshUI(mSettings);
  this->showWindow();
}

void MFBOPresetCreator::closeEvent(QCloseEvent* aEvent)
{
  auto lResult{QMessageBox::question(this, tr("Quitting"), tr("Are you sure you want to quit the software?"), QMessageBox::Yes | QMessageBox::No, QMessageBox::No)};

  if (lResult != QMessageBox::Yes)
  {
    aEvent->ignore();
  }
  else
  {
    aEvent->accept();
  }
}

void MFBOPresetCreator::initializeGUI()
{
  // Menu bar
  this->setupMenuBar();

  // Main window container
  auto lMainVertical{new QVBoxLayout(this->ui.mainContainer)};

  // Setup all the different GUI components
  this->setupBodyMeshesGUI(*lMainVertical);
  this->setupBodySlideGUI(*lMainVertical);
  this->setupOptionsGUI(*lMainVertical);
  this->setupOutputGUI(*lMainVertical);
  this->setupRemainingGUI(*lMainVertical);
}

void MFBOPresetCreator::setupMenuBar()
{
  // Keep a reference to the user theme
  auto lIconFolder{Utils::isThemeDark(mSettings.appTheme) ? QString("white") : QString("black")};

  // Construct the menu bar
  auto lMenuBar{new QMenuBar(this)};
  this->setMenuBar(lMenuBar);

  // File
  auto lFileMenu{new QMenu(tr("File"), this)};
  lMenuBar->addMenu(lFileMenu);

  // Submenu: relaunch the app
  auto lQuickRelaunch{new QAction()};
  lQuickRelaunch->setText(tr("Quick relaunch"));
  lQuickRelaunch->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_F5));
  lQuickRelaunch->setIcon(QIcon(":/" + lIconFolder + "/reload"));
  lFileMenu->addAction(lQuickRelaunch);

  // Submenu: Exit
  auto lExitAction{new QAction()};
  lExitAction->setText(tr("Exit"));
  lExitAction->setShortcut(QKeySequence(Qt::ALT + Qt::Key_F4));
  lExitAction->setIcon(QIcon(":/" + lIconFolder + "/exit"));
  lFileMenu->addAction(lExitAction);

  // Tools
  auto lToolsMenu{new QMenu(tr("Tools"), this)};
  lMenuBar->addMenu(lToolsMenu);

  // Submenu: Upgrader
  auto lUpgraderToolAction{new QAction()};
  lUpgraderToolAction->setText(tr("CBBE 3BBB Version Retargeting Tool"));
  lUpgraderToolAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_U));
  lUpgraderToolAction->setIcon(QIcon(":/" + lIconFolder + "/arrow_up"));
  lToolsMenu->addAction(lUpgraderToolAction);

  // Submenu: Settings
  auto lSettingsAction{new QAction()};
  lSettingsAction->setText(tr("Settings"));
  lSettingsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_O));
  lSettingsAction->setIcon(QIcon(":/" + lIconFolder + "/cog"));
  lToolsMenu->addAction(lSettingsAction);

  // Help
  auto lHelpMenu{new QMenu(tr("Help"), this)};
  lMenuBar->addMenu(lHelpMenu);

  // Submenu: About
  auto lAboutAction{new QAction()};
  lAboutAction->setText(tr("About"));
  lAboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_I));
  lAboutAction->setIcon(QIcon(":/" + lIconFolder + "/information"));
  lHelpMenu->addAction(lAboutAction);

  // Event binding
  connect(lQuickRelaunch, SIGNAL(triggered()), this, SLOT(quickRelaunch()));
  connect(lExitAction, SIGNAL(triggered()), this, SLOT(close()));
  connect(lUpgraderToolAction, SIGNAL(triggered()), this, SLOT(launchUpgraderTool()));
  connect(lSettingsAction, SIGNAL(triggered()), this, SLOT(showSettingsDialog()));
  connect(lAboutAction, SIGNAL(triggered()), this, SLOT(showAboutDialog()));
}

void MFBOPresetCreator::setupBodyMeshesGUI(QVBoxLayout& aLayout)
{
  // CBBE body meshes group box
  auto lMeshesGroupBox{new QGroupBox(tr("CBBE body meshes"))};
  aLayout.addWidget(lMeshesGroupBox);

  // Grid layout
  auto lMeshesGridLayout{new QGridLayout(lMeshesGroupBox)};
  lMeshesGridLayout->setColumnMinimumWidth(0, mMinimumFirstColmunWith);

  // First line
  auto lCbbe3BBBVersionLabel{new QLabel(tr("CBBE 3BBB version:"))};
  lMeshesGridLayout->addWidget(lCbbe3BBBVersionLabel, 0, 0);

  auto lCbbe3BBBVersionSelector{new QComboBox()};
  lCbbe3BBBVersionSelector->addItems(Utils::getCBBE3BBBVersions());
  lCbbe3BBBVersionSelector->setCurrentIndex(static_cast<int>(mSettings.defaultMainWindowCBBE3BBBVersion));
  lCbbe3BBBVersionSelector->setObjectName(QString("cbbe_3bbb_version"));
  lMeshesGridLayout->addWidget(lCbbe3BBBVersionSelector, 0, 1);

  // Second line
  auto lMeshesPathLabel{new QLabel(tr("Meshes path:"))};
  lMeshesGridLayout->addWidget(lMeshesPathLabel, 1, 0);

  auto lMeshesPathLineEdit{new QLineEdit("")};
  lMeshesPathLineEdit->setObjectName("meshes_path_input");
  lMeshesGridLayout->addWidget(lMeshesPathLineEdit, 1, 1);

  // Third line
  auto lLabelBeastHands{new QLabel(tr("Use beast hands?"))};
  lMeshesGridLayout->addWidget(lLabelBeastHands, 2, 0);

  auto lNeedBeastHands{new QCheckBox(tr("Check this box if the follower or NPC uses beast hands."))};
  lNeedBeastHands->setObjectName("use_beast_hands");
  lMeshesGridLayout->addWidget(lNeedBeastHands, 2, 1);

  // Fourth line
  auto lMeshestitlePreview{new QLabel(tr("Meshes names:"))};
  lMeshesGridLayout->addWidget(lMeshestitlePreview, 3, 0, 3, 1);

  auto lBodyMeshNameInput{new QLineEdit("")};
  lBodyMeshNameInput->setObjectName("body_mesh_name_input");
  lMeshesGridLayout->addWidget(lBodyMeshNameInput, 3, 1);
  lBodyMeshNameInput->setText("femalebody");
  lBodyMeshNameInput->setPlaceholderText("femalebody");

  auto lFeetMeshNameInput{new QLineEdit("")};
  lFeetMeshNameInput->setObjectName("feet_mesh_name_input");
  lMeshesGridLayout->addWidget(lFeetMeshNameInput, 4, 1);
  lFeetMeshNameInput->setText("femalefeet");
  lFeetMeshNameInput->setPlaceholderText("femalefeet");

  auto lHandsMeshNameInput{new QLineEdit("")};
  lHandsMeshNameInput->setObjectName("hands_mesh_name_input");
  lMeshesGridLayout->addWidget(lHandsMeshNameInput, 5, 1);
  lHandsMeshNameInput->setText("femalehands");
  lHandsMeshNameInput->setPlaceholderText("femalehands");

  auto lBodyMeshNameLabel1{new QLabel(tr("_0.nif/_1.nif"))};
  lMeshesGridLayout->addWidget(lBodyMeshNameLabel1, 3, 2);

  auto lBodyMeshNameLabel2{new QLabel(tr("_0.nif/_1.nif"))};
  lMeshesGridLayout->addWidget(lBodyMeshNameLabel2, 4, 2);

  auto lBodyMeshNameLabel3{new QLabel(tr("_0.nif/_1.nif"))};
  lMeshesGridLayout->addWidget(lBodyMeshNameLabel3, 5, 2);

  // Preview
  auto lLabelPreview{new QLabel()};
  lLabelPreview->setText(tr("Preview:"));
  lMeshesGridLayout->addWidget(lLabelPreview);

  auto lMeshesPreview{new QLabel()};
  lMeshesPreview->setObjectName("meshes_preview");
  lMeshesGridLayout->addWidget(lMeshesPreview);

  // Initialization functions
  this->updateMeshesPreview();

  // Event binding
  connect(lMeshesPathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(refreshAllPreviewFields(QString)));
  connect(lBodyMeshNameInput, SIGNAL(textChanged(QString)), this, SLOT(refreshAllPreviewFields(QString)));
  connect(lFeetMeshNameInput, SIGNAL(textChanged(QString)), this, SLOT(refreshAllPreviewFields(QString)));
  connect(lHandsMeshNameInput, SIGNAL(textChanged(QString)), this, SLOT(refreshAllPreviewFields(QString)));
  connect(lCbbe3BBBVersionSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(refreshAllPreviewFields(int)));
  connect(lNeedBeastHands, SIGNAL(clicked()), this, SLOT(refreshAllPreviewFields()));
}

void MFBOPresetCreator::setupBodySlideGUI(QVBoxLayout& aLayout)
{
  // BodySlide defined names group box
  auto lBodyslideGroupBox{new QGroupBox(tr("BodySlide"))};
  aLayout.addWidget(lBodyslideGroupBox);

  // Grid layout
  auto lBodyslideGridLayout{new QGridLayout(lBodyslideGroupBox)};
  lBodyslideGridLayout->setColumnMinimumWidth(0, mMinimumFirstColmunWith);

  // First line
  auto lOSPXMLNames{new QLabel(tr("Bodyslide files names:"))};
  lBodyslideGridLayout->addWidget(lOSPXMLNames, 0, 0);

  auto lOSPXMLNamesLineEdit{new QLineEdit("")};
  lOSPXMLNamesLineEdit->setObjectName("names_osp_xml_input");
  lBodyslideGridLayout->addWidget(lOSPXMLNamesLineEdit, 0, 1);

  // Second line
  auto lLabelOspXmlNames{new QLabel(tr("Preview:"))};
  lBodyslideGridLayout->addWidget(lLabelOspXmlNames, 1, 0);

  auto lPathsNamesOspXmlNames{new QLabel("")};
  lPathsNamesOspXmlNames->setObjectName("names_osp_xml_preview");
  lBodyslideGridLayout->addWidget(lPathsNamesOspXmlNames, 1, 1);

  // Third line
  auto lNamesInApp{new QLabel()};
  lNamesInApp->setTextFormat(Qt::RichText);
  lNamesInApp->setText(tr("Preset names: &#128712;"));
  lNamesInApp->setToolTip(QString(tr("This field represents the name under which the preset will be listed in the BodySlide software.")));
  lBodyslideGridLayout->addWidget(lNamesInApp, 2, 0);

  auto lNamesInAppLineEdit{new QLineEdit("")};
  lNamesInAppLineEdit->setObjectName("names_bodyslide_input");
  lBodyslideGridLayout->addWidget(lNamesInAppLineEdit, 2, 1);

  // Fourth line
  auto lLabelNamesInApp{new QLabel(tr("Preview:"))};
  lBodyslideGridLayout->addWidget(lLabelNamesInApp, 3, 0);

  auto lResultNamesInApp{new QLabel("")};
  lResultNamesInApp->setObjectName("names_bodyslide_preview");
  lBodyslideGridLayout->addWidget(lResultNamesInApp, 3, 1);

  // Initialization functions
  this->updateOSPXMLPreview(QString(""));
  this->updateBodyslideNamesPreview(QString(""));

  // Event binding
  connect(lOSPXMLNamesLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateOSPXMLPreview(QString)));
  connect(lNamesInAppLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateBodyslideNamesPreview(QString)));
}

void MFBOPresetCreator::setupOptionsGUI(QVBoxLayout& aLayout)
{
  // Custom skeleton and textures group box
  auto lOptionsGroupBox{new QGroupBox(tr("Additional options"))};
  aLayout.addWidget(lOptionsGroupBox);

  auto lOptionsGridLayout{new QGridLayout(lOptionsGroupBox)};
  lOptionsGridLayout->setColumnMinimumWidth(0, mMinimumFirstColmunWith);

  // Skeleton
  auto lLabelSkeleton{new QLabel("")};
  lLabelSkeleton->setTextFormat(Qt::RichText);
  lLabelSkeleton->setText(tr("Use a custom skeleton? &#128712;"));
  lLabelSkeleton->setToolTip(QString(tr("Note: not overriding a custom skeleton would cause breasts collision and physics to be inaccurate.")));
  lOptionsGridLayout->addWidget(lLabelSkeleton, 0, 0);

  auto lNeedCustomSkeleton{new QCheckBox(tr("Check this box if the follower or NPC uses a custom skeleton."))};
  lNeedCustomSkeleton->setObjectName("use_custom_skeleton");
  lOptionsGridLayout->addWidget(lNeedCustomSkeleton, 0, 1);

  // Skeleton path
  auto lLabelSkeletonPath{new QLabel(tr("Skeleton path:"))};
  lOptionsGridLayout->addWidget(lLabelSkeletonPath, 1, 0);

  auto lSkeletonPathLineEdit{new QLineEdit("")};
  lSkeletonPathLineEdit->setDisabled(true);
  lSkeletonPathLineEdit->setObjectName("skeleton_path_directory");
  lOptionsGridLayout->addWidget(lSkeletonPathLineEdit, 1, 1);

  // Skeleton path preview
  auto lSkeletontitlePreview{new QLabel(tr("Preview:"))};
  lOptionsGridLayout->addWidget(lSkeletontitlePreview, 2, 0);

  auto lSkeletonPathsPreview{new QLabel("")};
  lSkeletonPathsPreview->setObjectName("skeleton_path_preview");
  lOptionsGridLayout->addWidget(lSkeletonPathsPreview, 2, 1);

  // Initialization functions
  this->updateSkeletonPreview(QString(""));

  // Event binding
  connect(lNeedCustomSkeleton, SIGNAL(stateChanged(int)), this, SLOT(updateSkeletonPathState(int)));
  connect(lSkeletonPathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateSkeletonPreview(QString)));
}

void MFBOPresetCreator::setupOutputGUI(QVBoxLayout& aLayout)
{
  // Output group box
  auto lOutputGroupBox{new QGroupBox(tr("Output"))};
  aLayout.addWidget(lOutputGroupBox);

  // Grid layout
  auto lOutputGridLayout{new QGridLayout(lOutputGroupBox)};
  lOutputGridLayout->setColumnMinimumWidth(0, mMinimumFirstColmunWith);

  // First line
  auto lOutputPathLabel{new QLabel(tr("Output directory path:"))};
  lOutputGridLayout->addWidget(lOutputPathLabel, 0, 0);

  auto lOutputPathLineEdit{new QLineEdit("")};
  lOutputPathLineEdit->setReadOnly(true);
  lOutputPathLineEdit->setFocusPolicy(Qt::FocusPolicy::NoFocus);
  lOutputPathLineEdit->setObjectName("output_path_directory");
  lOutputGridLayout->addWidget(lOutputPathLineEdit, 0, 1);

  auto lOutputPathChooser{new QPushButton(tr("Choose a directory..."))};
  lOutputGridLayout->addWidget(lOutputPathChooser, 0, 2);

  // Second line
  auto lLabelSubDirectoryPath{new QLabel(tr("Output subdirectory name/path:"))};
  lOutputGridLayout->addWidget(lLabelSubDirectoryPath, 1, 0);

  auto lOutputSubpathLineEdit{new QLineEdit("")};
  lOutputSubpathLineEdit->setObjectName("output_path_subdirectory");
  lOutputGridLayout->addWidget(lOutputSubpathLineEdit, 1, 1);

  // Third line
  auto lOutputtitlePreview{new QLabel(tr("Preview:"))};
  lOutputGridLayout->addWidget(lOutputtitlePreview, 2, 0);

  auto lOutputPathsPreview{new QLabel("")};
  lOutputPathsPreview->setObjectName("output_path_preview");
  lOutputGridLayout->addWidget(lOutputPathsPreview, 2, 1);

  // Event binding
  connect(lOutputPathChooser, SIGNAL(clicked()), this, SLOT(chooseExportDirectory()));
  connect(lOutputSubpathLineEdit, SIGNAL(textChanged(QString)), this, SLOT(updateOutputPreview()));

  // Pre-filled data
  this->updateOutputPreview();
}

void MFBOPresetCreator::setupRemainingGUI(QVBoxLayout& aLayout)
{
  // Generate button
  auto lGenerateButton{new QPushButton(tr("Generate the files on my computer"))};
  aLayout.addWidget(lGenerateButton);

  // Event binding
  connect(lGenerateButton, SIGNAL(clicked()), this, SLOT(generateDirectoryStructure()));
}

void MFBOPresetCreator::showWindow()
{
  // Set the size of the window
  auto lDesktopScreen{QGuiApplication::primaryScreen()};
  QRect lScreenGeom{lDesktopScreen->availableGeometry()};

  // If the window size is correct for the user's screen
  if (mSettings.mainWindowWidth < lScreenGeom.width() && mSettings.mainWindowHeight < lScreenGeom.height())
  {
    // resize the window
    this->resize(mSettings.mainWindowWidth - 2, mSettings.mainWindowHeight - 62);
  }

  // Select the main window opening mode
  if (mSettings.mainWindowOpeningMode == WindowOpeningMode::Minimized)
  {
    this->showMinimized();

    // Make the icon in the taskbar blink
    FLASHWINFO finfo;
    finfo.cbSize = sizeof(FLASHWINFO);
    finfo.hwnd = (HWND)this->winId();
    finfo.uCount = 5;
    finfo.dwTimeout = 500;
    finfo.dwFlags = FLASHW_ALL;
    FlashWindowEx(&finfo);
  }
  else if (mSettings.mainWindowOpeningMode == WindowOpeningMode::Maximized)
  {
    this->showMaximized();
  }
  else if (mSettings.mainWindowOpeningMode == WindowOpeningMode::Windowed)
  {
    this->show();
  }

  auto lPosX{(lScreenGeom.width() - this->frameGeometry().width()) / 2 + 1};
  auto lPosY{(lScreenGeom.height() - this->frameGeometry().height()) / 2 + 31};
  this->setGeometry(QRect(lPosX, lPosY, this->geometry().width(), this->geometry().height()));
}

void MFBOPresetCreator::applyStyleSheet()
{
  auto lQSSFileName{QString("")};

  switch (mSettings.appTheme)
  {
    case GUITheme::WindowsVista:
      break;
    case GUITheme::PaperLight:
      lQSSFileName = "Paper Light by 6788";
      break;
    case GUITheme::PaperDark:
      lQSSFileName = "Paper Dark by 6788";
      break;
    case GUITheme::PaperWhiteMono:
      lQSSFileName = "Paper White Mono";
      break;
    case GUITheme::PaperBlackMono:
      lQSSFileName = "Paper Black Mono";
      break;
    default:
      break;
  }

  if (lQSSFileName.compare("") == 0)
  {
    qApp->setStyleSheet("");
  }
  else
  {
    QFile lQSSFile(":qss/" + lQSSFileName + ".qss");

    lQSSFile.open(QFile::ReadOnly);
    QString lStyleSheet{QLatin1String(lQSSFile.readAll())};

    qApp->setStyleSheet(lStyleSheet);
  }
}

void MFBOPresetCreator::refreshUI(Struct::Settings aSettings)
{
  // Apply the chosen theme
  this->applyStyleSheet();

  // Set the font properties
  QFont lFont(aSettings.fontFamily, aSettings.fontSize, -1, false);
  this->setFont(lFont);
  this->setStyleSheet("font-family: \"" + aSettings.fontFamily + "\"; font-size: " + QString::number(aSettings.fontSize) + "px;");
}

void MFBOPresetCreator::updateMeshesPreview()
{
  // Get all inut fields
  auto lMeshesPath{this->ui.mainContainer->findChild<QLineEdit*>("meshes_path_input")->text().trimmed()};
  Utils::cleanPathString(lMeshesPath);

  auto lBodyName{this->ui.mainContainer->findChild<QLineEdit*>("body_mesh_name_input")->text().trimmed()};
  auto lFeetName{this->ui.mainContainer->findChild<QLineEdit*>("feet_mesh_name_input")->text().trimmed()};
  auto lHandsName{this->ui.mainContainer->findChild<QLineEdit*>("hands_mesh_name_input")->text().trimmed()};

  // Get preview label
  auto lPreviewLabel{this->ui.mainContainer->findChild<QLabel*>("meshes_preview")};

  auto lFullPreview(QString(""));

  if (lMeshesPath == "")
  {
    lMeshesPath = "*";
  }

  if (lBodyName == "")
  {
    lBodyName = "femalebody";
  }

  if (lFeetName == "")
  {
    lFeetName = "femalefeet";
  }

  if (lHandsName == "")
  {
    lHandsName = "femalehands";
  }

  lFullPreview += QStringLiteral("[...]/Skyrim Special Edition/Data/%1/%2_0.nif\n").arg(lMeshesPath).arg(lBodyName);
  lFullPreview += QStringLiteral("[...]/Skyrim Special Edition/Data/%1/%2_1.nif\n").arg(lMeshesPath).arg(lBodyName);
  lFullPreview += QStringLiteral("[...]/Skyrim Special Edition/Data/%1/%2_0.nif\n").arg(lMeshesPath).arg(lFeetName);
  lFullPreview += QStringLiteral("[...]/Skyrim Special Edition/Data/%1/%2_1.nif\n").arg(lMeshesPath).arg(lFeetName);
  lFullPreview += QStringLiteral("[...]/Skyrim Special Edition/Data/%1/%2_0.nif\n").arg(lMeshesPath).arg(lHandsName);
  lFullPreview += QStringLiteral("[...]/Skyrim Special Edition/Data/%1/%2_0.nif").arg(lMeshesPath).arg(lHandsName);

  lPreviewLabel->setText(lFullPreview);
}

void MFBOPresetCreator::updateOutputPreview()
{
  // Get main directory
  auto lMainDirTextEdit{this->ui.mainContainer->findChild<QLineEdit*>("output_path_directory")};
  auto lMainDirectory{lMainDirTextEdit->text().trimmed()};
  Utils::cleanPathString(lMainDirectory);

  // Get subdirectory
  auto lSubDirectory{this->ui.mainContainer->findChild<QLineEdit*>("output_path_subdirectory")->text().trimmed()};
  Utils::cleanPathString(lSubDirectory);

  // Construct full path
  auto lFullPath(QString(""));
  if (lMainDirectory.length() > 0 && lSubDirectory.length() > 0)
  {
    lFullPath = lMainDirectory + "/" + lSubDirectory;
    lMainDirTextEdit->setDisabled(false);
  }
  else if (lMainDirectory.length() > 0 && lSubDirectory.length() == 0)
  {
    lFullPath = lMainDirectory;
    lMainDirTextEdit->setDisabled(false);
  }
  else
  {
    lFullPath = tr("No path given or invalid path given.");
    lMainDirTextEdit->setDisabled(true);
  }

  // Set the full path value in the preview label
  auto lOutputPathsPreview{this->ui.mainContainer->findChild<QLabel*>("output_path_preview")};
  lOutputPathsPreview->setText(lFullPath);
}

void MFBOPresetCreator::updateOSPXMLPreview(QString aText)
{
  auto lOutputPathsPreview{this->ui.mainContainer->findChild<QLabel*>("names_osp_xml_preview")};

  if (aText.trimmed().length() == 0)
  {
    aText = QString::fromStdString("*");
  }

  auto lConstructedPreviewText(
    QStringLiteral(
      "[...]/Skyrim Special Edition/Data/CalienteTools/BodySlide/SliderGroups/%1.xml\n"
      "[...]/Skyrim Special Edition/Data/CalienteTools/BodySlide/SliderSets/%1.osp")
      .arg(aText));

  lOutputPathsPreview->setText(lConstructedPreviewText);
}

void MFBOPresetCreator::updateBodyslideNamesPreview(QString aText)
{
  // Selected CBBE 3BBB version
  auto lCBBE3BBBVersionSelected{this->ui.mainContainer->findChild<QComboBox*>(QString("cbbe_3bbb_version"))->currentIndex()};

  // Beast hands
  auto lMustUseBeastHands{this->ui.mainContainer->findChild<QCheckBox*>("use_beast_hands")->isChecked()};

  // Path
  auto lOutputPathsPreview{this->ui.mainContainer->findChild<QLabel*>("names_bodyslide_preview")};

  if (aText.trimmed().length() == 0)
  {
    aText = QString::fromStdString("*");
  }

  auto lConstructedPreviewText{QString("")};

  switch (lCBBE3BBBVersionSelected)
  {
    case static_cast<int>(CBBE3BBBVersion::Version1_40):
      if (lMustUseBeastHands)
      {
        lConstructedPreviewText = QStringLiteral(
                                    "%1 - 3BBB Body Amazing\n"
                                    "%1 - Feet\n"
                                    "%1 - Beast Hands")
                                    .arg(aText);
      }
      else
      {
        lConstructedPreviewText = QStringLiteral(
                                    "%1 - 3BBB Body Amazing\n"
                                    "%1 - Feet\n"
                                    "%1 - Hands ")
                                    .arg(aText);
      }
      break;
    case static_cast<int>(CBBE3BBBVersion::Version1_50):
      if (lMustUseBeastHands)
      {
        lConstructedPreviewText = QStringLiteral(
                                    "%1 - CBBE 3BBB Body Amazing\n"
                                    "%1 - CBBE 3BBB Feet\n"
                                    "%1 - CBBE Beast Hands")
                                    .arg(aText);
      }
      else
      {
        lConstructedPreviewText = QStringLiteral(
                                    "%1 - CBBE 3BBB Body Amazing\n"
                                    "%1 - CBBE 3BBB Feet\n"
                                    "%1 - CBBE 3BBB Hands")
                                    .arg(aText);
      }
      break;
    case static_cast<int>(CBBE3BBBVersion::Version1_51_and_1_52):
      if (lMustUseBeastHands)
      {
        lConstructedPreviewText = QStringLiteral(
                                    "%1 - CBBE 3BBB Body Amazing\n"
                                    "%1 - CBBE 3BBB Feet\n"
                                    "%1 - CBBE 3BBB Hands Beast")
                                    .arg(aText);
      }
      else
      {
        lConstructedPreviewText = QStringLiteral(
                                    "%1 - CBBE 3BBB Body Amazing\n"
                                    "%1 - CBBE 3BBB Feet\n"
                                    "%1 - CBBE 3BBB Hands")
                                    .arg(aText);
      }
      break;
    default:
      lConstructedPreviewText = tr("Error while evaluating the data.");
      break;
  }

  lOutputPathsPreview->setText(lConstructedPreviewText);
}

void MFBOPresetCreator::updateSkeletonPathState(int aState)
{
  auto lSkeletonPathLineEdit{this->ui.mainContainer->findChild<QLineEdit*>("skeleton_path_directory")};
  auto lSkeletonPreview{this->ui.mainContainer->findChild<QLabel*>("skeleton_path_preview")};

  switch (aState)
  {
    case Qt::Unchecked:
      lSkeletonPathLineEdit->setDisabled(true);
      lSkeletonPreview->setDisabled(true);
      break;
    case Qt::Checked:
      lSkeletonPathLineEdit->setDisabled(false);
      lSkeletonPreview->setDisabled(false);
      break;
    default:
      break;
  }
}

void MFBOPresetCreator::updateSkeletonPreview(QString aText)
{
  auto lPathsPreview{this->ui.mainContainer->findChild<QLabel*>("skeleton_path_preview")};
  Utils::cleanPathString(aText);

  if (aText.trimmed().length() == 0)
  {
    aText = QString::fromStdString("[...]/Skyrim Special Edition/Data/*");
  }

  aText = aText + "/skeleton_female.nif";
  lPathsPreview->setText(aText);
}

void MFBOPresetCreator::chooseExportDirectory()
{
  auto lLineEdit{this->ui.mainContainer->findChild<QLineEdit*>("output_path_directory")};
  auto lPath{QFileDialog::getExistingDirectory(this, "", QStandardPaths::writableLocation(QStandardPaths::DesktopLocation))};
  lLineEdit->setText(lPath);
  this->updateOutputPreview();
}

void MFBOPresetCreator::generateDirectoryStructure()
{
  // Selected CBBE 3BBB version
  auto lCBBE3BBBVersionSelected{this->ui.mainContainer->findChild<QComboBox*>(QString("cbbe_3bbb_version"))->currentIndex()};

  // Beast hands
  auto lMustUseBeastHands{this->ui.mainContainer->findChild<QCheckBox*>("use_beast_hands")->isChecked()};

  // Body meshes path
  auto lBodyMeshesPath{this->ui.mainContainer->findChild<QLineEdit*>("meshes_path_input")->text().trimmed()};
  Utils::cleanPathString(lBodyMeshesPath);

  // Nif files names
  auto lFemaleBodyNifName{this->ui.mainContainer->findChild<QLineEdit*>("body_mesh_name_input")->text().trimmed()};
  auto lFemaleFeetNifName{this->ui.mainContainer->findChild<QLineEdit*>("feet_mesh_name_input")->text().trimmed()};
  auto lFemaleHandsNifName{this->ui.mainContainer->findChild<QLineEdit*>("hands_mesh_name_input")->text().trimmed()};

  // BodySlide names
  auto lOSPXMLNames{this->ui.mainContainer->findChild<QLineEdit*>("names_osp_xml_input")->text().trimmed()};
  auto lBodyslideSlidersetsNames{this->ui.mainContainer->findChild<QLineEdit*>("names_bodyslide_input")->text().trimmed()};

  // Options
  auto lMustCopySkeleton{this->ui.mainContainer->findChild<QCheckBox*>("use_custom_skeleton")->isChecked()};
  auto lSkeletonPath{this->ui.mainContainer->findChild<QLineEdit*>("skeleton_path_directory")->text().trimmed()};
  Utils::cleanPathString(lSkeletonPath);

  // Output paths
  auto lMainDirectory{this->ui.mainContainer->findChild<QLineEdit*>("output_path_directory")->text().trimmed()};
  auto lSubDirectory{this->ui.mainContainer->findChild<QLineEdit*>("output_path_subdirectory")->text().trimmed()};
  Utils::cleanPathString(lSubDirectory);

  // Full extract path
  auto lEntryDirectory{(lSubDirectory.length() == 0 ? lMainDirectory : (lMainDirectory + "/" + lSubDirectory))};

  // Check if the full extract path has been given by the user
  if (lEntryDirectory.length() == 0)
  {
    Utils::displayWarningMessage(tr("Error: no path given to export the files."));
    return;
  }

  // Check if the path could be valid
  if (lEntryDirectory.startsWith("/"))
  {
    Utils::displayWarningMessage(tr("Error: the path given to export the files seems to be invalid."));
    return;
  }

  // Create main directory
  if (!QDir(lEntryDirectory).exists())
  {
    // Wait to know the result of the mkdir()
    if (!QDir().mkdir(lEntryDirectory))
    {
      Utils::displayWarningMessage(tr("Error while creating the main directory: \"") + lEntryDirectory + tr("\" could not be created on your computer. Did you execute the program with limited permissions?"));
      return;
    }
  }
  else
  {
    Utils::displayWarningMessage(tr("Error while creating the main directory: \"") + lEntryDirectory + tr("\" already exists on your computer."));
    return;
  }

  // Export the meshes
  if (lBodyMeshesPath.length() == 0)
  {
    Utils::displayWarningMessage(tr("Error: no path has been given for the meshes."));
    return;
  }

  // Check if a name has been given for the OSP and XML files
  if (lOSPXMLNames.length() == 0)
  {
    Utils::displayWarningMessage(tr("Error: no name given for the BodySlide files."));
    return;
  }

  // Check if a name has been given for the presets
  if (lBodyslideSlidersetsNames.length() == 0)
  {
    Utils::displayWarningMessage(tr("Error: no name given for the slider sets (names that appear in the BodySlide software)."));
    return;
  }

  // Create the SliderGroups directory
  auto lSliderGroupsDirectory{lEntryDirectory + "/CalienteTools/BodySlide/SliderGroups"};
  if (!QDir(lSliderGroupsDirectory).exists())
  {
    QDir().mkpath(lSliderGroupsDirectory);
  }
  else
  {
    Utils::displayWarningMessage(tr("Error while creating the meshes directory: \"") + lSliderGroupsDirectory + tr("\" already exists."));
    return;
  }

  // Copy the QRC file and change the slidergroups names in the XML file
  auto lXMLPathName{lSliderGroupsDirectory + "/" + lOSPXMLNames + ".xml"};
  auto lRessourcesFolder{QString("")};

  switch (lCBBE3BBBVersionSelected)
  {
    case static_cast<int>(CBBE3BBBVersion::Version1_40):
      lRessourcesFolder = "cbbe_3bbb_1.40";
      break;
    case static_cast<int>(CBBE3BBBVersion::Version1_50):
      lRessourcesFolder = "cbbe_3bbb_1.50";
      break;
    case static_cast<int>(CBBE3BBBVersion::Version1_51_and_1_52):
      lRessourcesFolder = "cbbe_3bbb_1.51";
      break;
    default:
      Utils::displayWarningMessage(tr("Error while searching for the CBBE 3BBB version. If it happens, try restarting the program. If the error is still here after restarting the program, contact the developer."));
      return;
  }

  // Copy the XML file
  if (lMustUseBeastHands)
  {
    if (!QFile::copy(":/" + lRessourcesFolder + "/bodyslide_beast_hands_xml", lXMLPathName))
    {
      Utils::displayWarningMessage(tr("The XML file could not be created. Did you execute the program with limited permissions?"));
      return;
    }
  }
  else
  {
    if (!QFile::copy(":/" + lRessourcesFolder + "/bodyslide_xml", lXMLPathName))
    {
      Utils::displayWarningMessage(tr("The XML file could not be created. Did you execute the program with limited permissions?"));
      return;
    }
  }

  QFile lXMLFile(lXMLPathName);
  lXMLFile.setPermissions(QFile::WriteUser);

  QByteArray lTempXMLContent;

  if (lXMLFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    lTempXMLContent = lXMLFile.readAll();
    lXMLFile.close();
  }
  else
  {
    Utils::displayWarningMessage(tr("Error while trying to open the file \"") + lXMLPathName + tr("\"."));
    return;
  }

  if (lTempXMLContent.length() > 0)
  {
    if (lXMLFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
      auto lTextToParse{static_cast<QString>(lTempXMLContent)};
      lTextToParse.replace(QString("{%%bodyslide_set_name%%}"), lBodyslideSlidersetsNames);

      QTextStream lTextStream(&lXMLFile);
      lTextStream << lTextToParse;
      lTextStream.flush();

      lXMLFile.close();
    }
    else
    {
      Utils::displayWarningMessage(tr("Error while trying to open the file \"") + lXMLPathName + tr("\"."));
      return;
    }
  }
  else
  {
    Utils::displayWarningMessage(tr("Error while trying to parse the XML BodySlide file."));
    return;
  }

  // Create the SliderSets directory
  auto lSliderSetsDirectory{lEntryDirectory + "/CalienteTools/BodySlide/SliderSets"};

  if (!QDir(lSliderSetsDirectory).exists())
  {
    QDir().mkpath(lSliderSetsDirectory);
  }
  else
  {
    Utils::displayWarningMessage(tr("Error while creating the meshes directory: \"") + lSliderSetsDirectory + tr("\" already exists."));
    return;
  }

  // Copy the QRC file and change the slidergroups names in the OSP file
  auto lOSPPathName(lSliderSetsDirectory + "/" + lOSPXMLNames + ".osp");

  // Copy the OSP file
  if (lMustUseBeastHands)
  {
    if (!QFile::copy(":/" + lRessourcesFolder + "/bodyslide_beast_hands_osp", lOSPPathName))
    {
      Utils::displayWarningMessage(tr("The OSP file could not be created. Did you execute the program with limited permissions?"));
      return;
    }
  }
  else
  {
    if (!QFile::copy(":/" + lRessourcesFolder + "/bodyslide_osp", lOSPPathName))
    {
      Utils::displayWarningMessage(tr("The OSP file could not be created. Did you execute the program with limited permissions?"));
      return;
    }
  }

  QFile lOSPFile(lOSPPathName);
  lOSPFile.setPermissions(QFile::WriteUser);

  QByteArray lTempOSPContent;

  if (lOSPFile.open(QIODevice::ReadOnly | QIODevice::Text))
  {
    lTempOSPContent = lOSPFile.readAll();
    lOSPFile.close();
  }
  else
  {
    Utils::displayWarningMessage(tr("Error while trying to open the file \"") + lOSPPathName + tr("\"."));
    return;
  }

  // Replace the slider sets names
  if (lTempOSPContent.length() > 0)
  {
    if (lOSPFile.open(QIODevice::WriteOnly | QIODevice::Truncate | QIODevice::Text))
    {
      auto lTextToParse{static_cast<QString>(lTempOSPContent)};
      lTextToParse.replace(QString("{%%bodyslide_set_name%%}"), lBodyslideSlidersetsNames);
      lTextToParse.replace(QString("{%%body_output_path%%}"), lBodyMeshesPath.replace("/", "\\"));
      lTextToParse.replace(QString("{%%feet_output_path%%}"), lBodyMeshesPath.replace("/", "\\"));
      lTextToParse.replace(QString("{%%hands_output_path%%}"), lBodyMeshesPath.replace("/", "\\"));

      lTextToParse.replace(QString("{%%body_output_file%%}"), lFemaleBodyNifName.size() > 0 ? lFemaleBodyNifName : "femalebody");
      lTextToParse.replace(QString("{%%feet_output_file%%}"), lFemaleFeetNifName.size() > 0 ? lFemaleFeetNifName : "femalefeet");
      lTextToParse.replace(QString("{%%hands_output_file%%}"), lFemaleHandsNifName.size() > 0 ? lFemaleHandsNifName : "femalehands");

      QTextStream lTextStream(&lOSPFile);
      lTextStream << lTextToParse;
      lTextStream.flush();

      lOSPFile.close();
    }
    else
    {
      Utils::displayWarningMessage(tr("Error while trying to open the file \"") + lOSPPathName + tr("\"."));
      return;
    }
  }
  else
  {
    Utils::displayWarningMessage(tr("Error while trying to parse the OSP BodySlide file."));
    return;
  }

  // If the user checked the custom skeleton
  if (lMustCopySkeleton)
  {
    if (lSkeletonPath.length() > 0)
    {
      auto lSkeletonDirectory{lEntryDirectory + "/" + lSkeletonPath};
      QDir().mkpath(lSkeletonDirectory);

      if (!QFile::copy(":/ressources/skeleton_female", lSkeletonDirectory + "/" + "skeleton_female.nif"))
      {
        Utils::displayWarningMessage(tr("The skeleton file could not be created. Did you execute the program with limited permissions?"));
        return;
      }
    }
    else
    {
      Utils::displayWarningMessage(tr("Error: no path given for the custom skeleton."));
      return;
    }
  }

  // Message when the generation has completed successfully
  auto lSuccessText{QString("")};

  switch (lCBBE3BBBVersionSelected)
  {
    case static_cast<int>(CBBE3BBBVersion::Version1_40):
      lSuccessText = tr("Every file has been correctly generated, for the version 1.40 and lower of CBBE 3BBB. You can now exit the program or create another conversion! :)");
      break;
    case static_cast<int>(CBBE3BBBVersion::Version1_50):
      lSuccessText = tr("Every file has been correctly generated, for the version 1.50 of CBBE 3BBB. You can now exit the program or create another conversion! :)");
      break;
    case static_cast<int>(CBBE3BBBVersion::Version1_51_and_1_52):
      lSuccessText = tr("Every file has been correctly generated, for the version 1.51 and 1.52 of CBBE 3BBB. You can now exit the program or create another conversion! :)");
      break;
    default:
      lSuccessText = tr("Every file has been correctly generated. You can now exit the program or create another conversion! :)");
      break;
  }

  auto lReply{QMessageBox::information(this, tr("Generation successful"), lSuccessText, QMessageBox::Ok, QMessageBox::Ok)};

  if (lReply == QMessageBox::Ok)
  {
    // Open the folder where the file structure has been created
    QDesktopServices::openUrl(lEntryDirectory);
  }
}

void MFBOPresetCreator::refreshAllPreviewFields(QString aText)
{
  this->refreshAllPreviewFields();
}

void MFBOPresetCreator::refreshAllPreviewFields(int)
{
  this->refreshAllPreviewFields();
}

void MFBOPresetCreator::refreshAllPreviewFields()
{
  // Refresh the preview of the body meshes parts
  this->updateMeshesPreview();

  // Refresh the names in the bodyslide software
  auto lBodyslideSlidersetsNames{this->ui.mainContainer->findChild<QLineEdit*>("names_bodyslide_input")->text().trimmed()};
  this->updateBodyslideNamesPreview(lBodyslideSlidersetsNames);
}

void MFBOPresetCreator::quickRelaunch()
{
  qApp->exit(Settings::EXIT_CODE_REBOOT);
}

void MFBOPresetCreator::launchUpgraderTool()
{
  new UpgraderTool(this);
}

void MFBOPresetCreator::showSettingsDialog()
{
  auto lSettings{new Settings(this)};

  connect(lSettings, SIGNAL(refreshMainUI(Struct::Settings)), this, SLOT(refreshUI(Struct::Settings)));
}

void MFBOPresetCreator::showAboutDialog()
{
  // Build the description
  auto lDescription(
    QStringLiteral(
      "<h1 style=\"text-align: center; padding: 0; margin: 0; margin-right: 20px;\">About this software</h1><br />"
      "<p style=\"font-size: 12px; padding: 0; margin: 0; margin-right: 20px;\">"
      "Mitsuriou's Follower Bodies Overhaul Preset Creator (MFBOPC) is a software "
      "created by Dylan Jacquemin (also known under the nickname \"Mitsuriou\").<br />"
      "This software has been developed to be provided for free to any user that wants to use the software. <br />"
      "The totality of the source code is available on "
      "<a href=\"https://github.com/Mitsuriou/MFBO-Preset-Creator\">GitHub.com</a>."
      "<br /><br />"
      "Ressources used to make this software:<br />"
      "&bull; <a href='https://www.qt.io'>Qt</a> (free version) is used for the Graphical User Iterface (GUI).<br />"
      "&bull; All the icons were taken from <a href=\"https://materialdesignicons.com\">MaterialDesignIcons.com</a>.<br />"
      "&bull; Theme custom window themes were taken from <a href=\"https://github.com/6788-00\">6788-00's GitHub repository</a>.<br />"
      "<br />"
      "Ressources bundled in this software:<br />"
      "&bull; The BodySlide (OSP and XML) files that are generated with MFBOPC were taken from the "
      "<a href=\"https://www.nexusmods.com/skyrimspecialedition/mods/30174\">CBBE 3BBB</a> mod on NexusMod "
      "and modified by Dylan Jacquemin.<br />"
      "&bull; The \"female_skeleton.nif\" file has been taken from the "
      "<a href=\"https://www.nexusmods.com/skyrimspecialedition/mods/1988\">XP32 Maximum Skeleton Special Extended - XPMSSE</a> "
      "mod on NexusMod. The file has not been modified."
      "</p>"));

  // Construct the message box
  QMessageBox lDialog(QMessageBox::Icon::NoIcon, tr("About"), lDescription, QMessageBox::StandardButton::Close);
  lDialog.setTextFormat(Qt::RichText);
  lDialog.adjustSize();

  // Display the message box
  lDialog.exec();
}
