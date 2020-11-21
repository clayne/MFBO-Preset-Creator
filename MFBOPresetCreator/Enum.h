﻿#pragma once

enum class BodyNameVersion
{
  CBBE_3BBB_3BA_1_40 = 0,
  CBBE_3BBB_3BA_1_50 = 1,
  CBBE_3BBB_3BA_1_51_and_1_52 = 2,
  CBBE_SMP_3BBB_1_2_0 = 3
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
