﻿#pragma once

enum class BodyNameVersion
{
  CBBE_3BBB_3BA_1_40 = 0,
  CBBE_3BBB_3BA_1_50 = 1,
  CBBE_3BBB_3BA_1_51_and_1_55 = 2,
  CBBE_SMP_3BBB_1_2_0 = 3,
  BHUNP_3BBB_2_13 = 4,
  BHUNP_3BBB_Advanced_2_13 = 5,
  BHUNP_3BBB_Advanced_ver_2_2_13 = 6,
  BHUNP_BBP_2_13 = 7,
  BHUNP_BBP_Advanced_2_13 = 8,
  BHUNP_TBBP_2_13 = 9,
  BHUNP_TBBP_Advanced_2_13 = 10,
  BHUNP_3BBB_2_15 = 11,
  BHUNP_3BBB_Advanced_2_15 = 12,
  BHUNP_3BBB_Advanced_ver_2_2_15 = 13,
  BHUNP_BBP_2_15 = 14,
  BHUNP_BBP_Advanced_2_15 = 15,
  BHUNP_TBBP_2_15 = 16,
  BHUNP_TBBP_Advanced_2_15 = 17,
  BHUNP_3BBB_2_20 = 18,
  BHUNP_3BBB_Advanced_2_20 = 19,
  BHUNP_3BBB_Advanced_ver_2_2_20 = 20,
  BHUNP_BBP_2_20 = 21,
  BHUNP_BBP_Advanced_2_20 = 22,
  BHUNP_TBBP_2_20 = 23,
  BHUNP_TBBP_Advanced_2_20 = 24,
  BHUNP_3BBB_2_25 = 25,
  BHUNP_3BBB_Advanced_2_25 = 26,
  BHUNP_3BBB_Advanced_ver_2_2_25 = 27,
  BHUNP_BBP_2_25 = 28,
  BHUNP_BBP_Advanced_2_25 = 29,
  BHUNP_TBBP_2_25 = 30,
  BHUNP_TBBP_Advanced_2_25 = 31,
  CBBE_3BBB_3BA_2_00 = 32,
};

enum class BodyName
{
  CBBE_3BBB_3BA = 0,
  CBBE_SMP_3BBB = 1,
  BHUNP_3BBB = 2,
  BHUNP_3BBB_Advanced = 3,
  BHUNP_3BBB_Advanced_ver_2 = 4,
  BHUNP_BBP = 5,
  BHUNP_BBP_Advanced = 6,
  BHUNP_TBBP = 7,
  BHUNP_TBBP_Advanced = 8
};

enum class ApplicationLanguage
{
  English = 0,
  French = 1
};

enum class GUITheme
{
  WindowsVista = 0,
  PaperLight = 1,
  PaperDark = 2,
  PaperWhiteMono = 3,
  PaperBlackMono = 4,
  AlexhuszaghBreezeLight = 5,
  AlexhuszaghBreezeDark = 6,
  QuasarAppDarkStyle = 7,
  QuasarAppVisualStudioDark = 8,
  MitsuriouLightTheme = 9,
  MitsuriouDarkTheme = 10
};

enum class WindowOpeningMode
{
  Minimized = 0,
  Windowed = 1,
  Maximized = 2
};

enum class AssistedConversionRole
{
  Body = 1,
  Feet = 2,
  Hands = 3,
  Skeleton = 4
};

enum class ButtonClicked
{
  Yes = 0,
  No = 1,
  CloseWindow = 2
};