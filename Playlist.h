#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <string>
#include <vector>
#include "Song.h"

using namespace std;

class Playlist
{
private:
    string playlistName;
    vector<Song*> songs;

public:
    Playlist();
    Playlist(string name);

    void createPlaylist(string name);

    void addSong(Song* song);
    void removeSong(Song* song);

    void displayPlaylist() const;

    string getName() const;
    vector<Song*> getSongs() const;

    bool isEmpty() const;
};

#endif