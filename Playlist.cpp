#include "Playlist.h"
#include <iostream>

using namespace std;

Playlist::Playlist()
{
    playlistName = "Untitled Playlist";
}

Playlist::Playlist(string name)
{
    playlistName = name;
}

void Playlist::createPlaylist(string name)
{
    playlistName = name;
    songs.clear();
}

void Playlist::addSong(Song* song)
{
    if (song == nullptr)
    {
        return;
    }

    // Prevent duplicate songs
    for (Song* existingSong : songs)
    {
        if (existingSong == song)
        {
            cout << "Song is already in the playlist.\n";
            return;
        }
    }

    songs.push_back(song);

    cout << song->getTitle()
         << " added to "
         << playlistName << ".\n";
}

void Playlist::removeSong(Song* song)
{
    if (song == nullptr)
    {
        return;
    }

    for (auto it = songs.begin(); it != songs.end(); ++it)
    {
        if (*it == song)
        {
            songs.erase(it);

            cout << song->getTitle()
                 << " removed from "
                 << playlistName << ".\n";

            return;
        }
    }

    cout << "Song not found in playlist.\n";
}

void Playlist::displayPlaylist() const
{
    cout << "\n=================================\n";
    cout << "       " << playlistName << "\n";
    cout << "=================================\n";

    if (songs.empty())
    {
        cout << "Playlist is empty.\n";
        return;
    }

    for (size_t i = 0; i < songs.size(); ++i)
    {
        cout << i + 1 << ". "
             << songs[i]->getTitle()
             << " - "
             << songs[i]->getArtist()
             << endl;
    }
}

string Playlist::getName() const
{
    return playlistName;
}

vector<Song*> Playlist::getSongs() const
{
    return songs;
}

bool Playlist::isEmpty() const
{
    return songs.empty();
}