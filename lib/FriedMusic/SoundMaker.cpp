#include "SoundMaker.hpp"

void SoundMaker::vlcEventProcessor(const struct libvlc_event_t *p_event, void *p_data)
{
  for (StandartGlobalUser listener : ((SoundMaker *)p_data)->listeners)
  {
    switch (p_event->type)
    {
    case libvlc_MediaPlayerMediaChanged:
      listener.onMediaPlayerMediaChanged();
      break;
    case libvlc_MediaPlayerNothingSpecial:
      listener.onMediaPlayerNothingSpecial();
      break;
    case libvlc_MediaPlayerOpening:
      listener.onMediaPlayerOpening();
      break;
    case libvlc_MediaPlayerBuffering:
      listener.onMediaPlayerBuffering();
      break;
    case libvlc_MediaPlayerPlaying:
      listener.onMediaPlayerPlaying();
      break;
    case libvlc_MediaPlayerPaused:
      listener.onMediaPlayerPaused();
      break;
    case libvlc_MediaPlayerStopped:
      listener.onMediaPlayerStopped();
      break;
    case libvlc_MediaPlayerForward:
      listener.onMediaPlayerForward();
      break;
    case libvlc_MediaPlayerBackward:
      listener.onMediaPlayerBackward();
      break;
    case libvlc_MediaPlayerStopping:
    // test it before use
      listener.onMediaPlayerMediaChanged();
      break;
    case libvlc_MediaPlayerEncounteredError:
      listener.onMediaPlayerEncounteredError();
      break;
    case libvlc_MediaPlayerTimeChanged:
      listener.onMediaPlayerTimeChanged();
      break;
    case libvlc_MediaPlayerPositionChanged:
      listener.onMediaPlayerPositionChanged();
      break;
    case libvlc_MediaPlayerLengthChanged:
      listener.onMediaPlayerLengthChanged();
      break;
    case libvlc_MediaPlayerVout:
      listener.onMediaPlayerVout();
      break;
    case libvlc_MediaPlayerESAdded:
      listener.onMediaPlayerESAdded();
      break;
    case libvlc_MediaPlayerESDeleted:
      listener.onMediaPlayerESDeleted();
      break;
    case libvlc_MediaPlayerESSelected:
      listener.onMediaPlayerESSelected();
      break;
    case libvlc_MediaPlayerCorked:
      listener.onMediaPlayerCorked();
      break;
    case libvlc_MediaPlayerUncorked:
      listener.onMediaPlayerUncorked();
      break;
    case libvlc_MediaPlayerMuted:
      listener.onMediaPlayerMuted();
      break;
    case libvlc_MediaPlayerUnmuted:
      listener.onMediaPlayerUnmuted();
      break;
    case libvlc_MediaPlayerAudioVolume:
      listener.onMediaPlayerAudioVolume();
      break;
    case libvlc_MediaPlayerAudioDevice:
      listener.onMediaPlayerAudioDevice();
      break;
    }
  }
}

