#ifndef ARTIST_H
#define ARTIST_H

#include "Song.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Artist
{
private:
    string name;
    string country;
    string genre;
    vector<Song*> songs;

public:
    Artist();

    Artist(string n, string c, string g);

    string getName() const;
    string getCountry() const;
    string getGenre() const;

    vector<Song*> getSongs() const;

    void addSong(Song* song);
    void displayArtist() const;
    void displaySongs() const;
};

#endif