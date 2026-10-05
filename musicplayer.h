#ifndef MUSICPLAYER_H
#define MUSICPLAYER_H

#include <SFML/Audio.hpp>
#include <string>
#include <vector>
#include <cstddef>

class MusicPlayer
{
public:

    // Represents one song in the playback queue
    struct Track
    {
        std::string title;
        std::string filePath;
    };

    // Constructor
    MusicPlayer();

    // Basic playback
    bool playSong(const std::string& title,
                  const std::string& filePath);

    void pause();
    void resume();
    void stop();

    // Queue
    void setQueue(const std::vector<Track>& newQueue);

    void next();
    void previous();

    // Volume
    void setVolume(float newVolume);
    float getVolume() const;

    // Shuffle
    void setShuffle(bool enabled);

    // Repeat current song
    void setRepeat(bool enabled);

    // Status
    bool isPlaying() const;
    std::string getCurrentTitle() const;

    // Automatically move to next song
    // when current song finishes
    void update();

private:

    // SFML music object
    sf::Music music;

    // Playback queue
    std::vector<Track> queue;

    // Current position in queue
    std::size_t currentIndex;

    // Current volume
    float volume;

    // Playback modes
    bool shuffleEnabled;
    bool repeatEnabled;

    // True when a song has been started
    bool hasActiveSong;
};

#endif