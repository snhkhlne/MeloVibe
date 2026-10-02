
#include "Song.h"

// Default Constructor
Song::Song() {
    title = "";
    artist = "";
    composer = "";
    lyricist = "";
    album = "";
    year = 0;
    filePath = "";
}

// Parameterized Constructor
Song::Song(string t, string a, string c,
           string l, string al, int y, string f) {
    title = t;
    artist = a;
    composer = c;
    lyricist = l;
    album = al;
    year = y;
    filePath = f;
}

// Get Song Title
string Song::getTitle() const {
    return title;
}

// Get Artist Name
string Song::getArtist() const {
    return artist;
}

// Get Composer
string Song::getComposer() const {
    return composer;
}

// Get Lyricist
string Song::getLyricist() const {
    return lyricist;
}

// Get Album or Movie
string Song::getAlbum() const {
    return album;
}

// Get Release Year
int Song::getYear() const {
    return year;
}

// Get MP3 File Path
string Song::getFilePath() const {
    return filePath;
}

// Display Complete Song Information
void Song::displaySongInfo() const {
    cout << "\n----- SONG INFORMATION -----\n";
    cout << "Title: " << title << endl;
    cout << "Artist: " << artist << endl;
    cout << "Composer: " << composer << endl;
    cout << "Lyricist: " << lyricist << endl;
    cout << "Album/Movie: " << album << endl;
    cout << "Year: " << year << endl;
    cout << "File Path: " << filePath << endl;
}