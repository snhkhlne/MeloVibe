
#ifndef SONG_H
#define SONG_H

#include <iostream>
#include <string>
using namespace std;

class Song {
private:
    string title;
    string artist;
    string composer;
    string lyricist;
    string album;
    int year;
    string filePath;

public:
    Song();

    Song(string t, string a, string c,
         string l, string al, int y, string f);

    string getTitle() const;
    string getArtist() const;
    string getComposer() const;
    string getLyricist() const;
    string getAlbum() const;
    int getYear() const;
    string getFilePath() const;

    void displaySongInfo() const;
};

#endif