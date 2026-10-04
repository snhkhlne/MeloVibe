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
    string category;
    string genre;
    string biography;
    vector<Song*> songs;

public:

    Artist();

    Artist(string n, string c, string g);

    string getName() const;
    string getCountry() const;
    string getGenre() const;

    string getCategory() const;
    string getBiography() const;

    vector<Song*> getSongs() const;

    void addSong(Song* song);

    void displayArtist() const;
    void displaySongs() const;
};

#endifs
