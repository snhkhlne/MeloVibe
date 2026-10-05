#include "MusicPlayer.h"

#include <iostream>
#include <algorithm>
#include <random>


// ======================================================
// CONSTRUCTOR
// ======================================================

MusicPlayer::MusicPlayer()
{
    currentIndex = 0;

    volume = 100.0f;

    shuffleEnabled = false;
    repeatEnabled = false;

    hasActiveSong = false;

    music.setVolume(volume);
}


// ======================================================
// PLAY SONG
// ======================================================

bool MusicPlayer::playSong(const std::string& title,
                           const std::string& filePath)
{
    // Try to open the music file
    if (!music.openFromFile(filePath))
    {
        std::cout << "\nERROR: Could not open song.\n";
        std::cout << "File: " << filePath << "\n";

        hasActiveSong = false;

        return false;
    }

    // Apply current settings
    music.setVolume(volume);

    music.setLooping(repeatEnabled);

    // Start music
    music.play();

    hasActiveSong = true;

    std::cout << "\nNow Playing: "
              << title
              << "\n";

    return true;
}


// ======================================================
// PAUSE
// ======================================================

void MusicPlayer::pause()
{
    music.pause();

    std::cout << "Music Paused.\n";
}


// ======================================================
// RESUME
// ======================================================

void MusicPlayer::resume()
{
    music.play();

    hasActiveSong = true;

    std::cout << "Music Resumed.\n";
}


// ======================================================
// STOP
// ======================================================

void MusicPlayer::stop()
{
    music.stop();

    hasActiveSong = false;

    std::cout << "Music Stopped.\n";
}


// ======================================================
// SET QUEUE
// ======================================================

void MusicPlayer::setQueue(
    const std::vector<Track>& newQueue)
{
    queue = newQueue;

    currentIndex = 0;

    std::cout << "Queue loaded with "
              << queue.size()
              << " songs.\n";
}


// ======================================================
// NEXT SONG
// ======================================================

void MusicPlayer::next()
{
    if (queue.empty())
    {
        std::cout << "Queue is empty.\n";
        return;
    }

    // Already at the last song
    if (currentIndex + 1 >= queue.size())
    {
        std::cout << "End of queue reached.\n";
        return;
    }

    // Move to next song
    currentIndex++;

    // Stop current song
    music.stop();

    // Play next song
    playSong(
        queue[currentIndex].title,
        queue[currentIndex].filePath
    );
}


// ======================================================
// PREVIOUS SONG
// ======================================================

void MusicPlayer::previous()
{
    if (queue.empty())
    {
        std::cout << "Queue is empty.\n";
        return;
    }

    // Already at first song
    if (currentIndex == 0)
    {
        std::cout << "Already at first song.\n";
        return;
    }

    // Move to previous song
    currentIndex--;

    // Stop current song
    music.stop();

    // Play previous song
    playSong(
        queue[currentIndex].title,
        queue[currentIndex].filePath
    );
}


// ======================================================
// SET VOLUME
// ======================================================

void MusicPlayer::setVolume(float newVolume)
{
    // Minimum volume
    if (newVolume < 0)
    {
        newVolume = 0;
    }

    // Maximum volume
    if (newVolume > 100)
    {
        newVolume = 100;
    }

    volume = newVolume;

    music.setVolume(volume);

    std::cout << "Volume: "
              << volume
              << "%\n";
}


// ======================================================
// GET VOLUME
// ======================================================

float MusicPlayer::getVolume() const
{
    return volume;
}


// ======================================================
// SHUFFLE
// ======================================================

void MusicPlayer::setShuffle(bool enabled)
{
    // Don't do anything if the setting is already the same
    if (enabled == shuffleEnabled)
    {
        std::cout << "Shuffle is already "
                  << (enabled ? "ON" : "OFF")
                  << ".\n";

        return;
    }

    shuffleEnabled = enabled;

    // Nothing to shuffle
    if (queue.empty())
    {
        std::cout << "Shuffle: "
                  << (shuffleEnabled ? "ON" : "OFF")
                  << "\n";

        return;
    }

    // Turn shuffle ON
    if (shuffleEnabled)
    {
        // Remember currently playing song
        Track currentTrack = queue[currentIndex];

        // Random number generator
        std::random_device rd;

        std::mt19937 generator(rd());

        // Shuffle queue
        std::shuffle(
            queue.begin(),
            queue.end(),
            generator
        );

        // Find current song after shuffling
        for (std::size_t i = 0;
             i < queue.size();
             i++)
        {
            if (queue[i].filePath ==
                currentTrack.filePath)
            {
                currentIndex = i;

                break;
            }
        }

        std::cout << "Shuffle: ON\n";

        std::cout << "Queue shuffled.\n";

        std::cout << "Current song remains: "
                  << currentTrack.title
                  << "\n";
    }
    else
    {
        std::cout << "Shuffle: OFF\n";
    }
}


// ======================================================
// REPEAT
// ======================================================

void MusicPlayer::setRepeat(bool enabled)
{
    repeatEnabled = enabled;

    // Tell SFML whether the current music should loop
    music.setLooping(repeatEnabled);

    std::cout << "Repeat: "
              << (repeatEnabled ? "ON" : "OFF")
              << "\n";
}


// ======================================================
// CHECK PLAYING STATUS
// ======================================================

bool MusicPlayer::isPlaying() const
{
    return music.getStatus()
           == sf::SoundSource::Status::Playing;
}


// ======================================================
// GET CURRENT SONG
// ======================================================

std::string MusicPlayer::getCurrentTitle() const
{
    if (queue.empty())
    {
        return "";
    }

    return queue[currentIndex].title;
}


// ======================================================
// AUTOMATIC NEXT SONG
// ======================================================

void MusicPlayer::update()
{
    // No song has been started
    if (!hasActiveSong)
    {
        return;
    }

    // If repeat is ON,
    // SFML automatically loops the song.
    if (repeatEnabled)
    {
        return;
    }

    // Check whether the song has finished
    if (music.getStatus()
        == sf::SoundSource::Status::Stopped)
    {
        // More songs available
        if (!queue.empty() &&
            currentIndex + 1 < queue.size())
        {
            currentIndex++;

            playSong(
                queue[currentIndex].title,
                queue[currentIndex].filePath
            );
        }
        else
        {
            // No more songs
            hasActiveSong = false;

            std::cout << "\nEnd of queue reached.\n";
        }
    }
}