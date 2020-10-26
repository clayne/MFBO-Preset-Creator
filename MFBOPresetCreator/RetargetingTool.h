﻿#pragma once

#include "DataLists.h"
#include "Enum.h"
#include "Struct.h"
#include "Utils.h"
#include "stdafx.h"

class RetargetingTool : public QDialog
{
  Q_OBJECT

public:
  RetargetingTool(QWidget* parent);

protected:
  void closeEvent(QCloseEvent* aEvent) override;
  void reject();

private:
  Struct::Settings mSettings;

  void setWindowProperties();
  void initializeGUI();
  void setupInterface(QGridLayout& aLayout);
  void refreshUI();

private slots:
  void chooseInputDirectory();
  void chooseBackupDirectory();
  void updateBackupPreview();
  void switchBackupState();
  void launchUpDownGradeProcess();
};