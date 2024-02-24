#pragma once
#include <iostream>
#include <string>
#include "../Data.hpp"
#include "../Client.hpp"
#include "../SoundMaker.hpp"

using namespace std;

class Icons{
  public:
  inline static const std::string PLAY = "resource/Octicons-playback-play.svg";
  inline static const std::string PAUSE = "resource/Octicons-playback-pause.svg";
  inline static const std::string PREV = "resource/Fast_backward_font_awesome.svg";
  inline static const std::string NEXT = "resource/Fast_forward_font_awesome.svg";
  inline static const std::string SHUFFLE = "resource/shuffle.svg";
  inline static const std::string TOFAVOURITE = "resource/directory_favorites-2.png";
  inline static const std::string UNFAVOURITE = "resource/directory_favorites-remove-2.png";
  inline static const std::string TOLIST = "resource/directory_open_file_mydocs-4.png";
  inline static const std::string DOWNLOAD = "resource/download.svg";
  inline static const std::string DELETE = "resource/trash-can.svg";
  inline static const std::string MOREVERT = "resource/more_vert.svg";
  inline static const std::string SETTINGS = "resource/settings.svg";
};