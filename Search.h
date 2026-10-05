#ifndef SEARCH_H
#define SEARCH_H

#include <vector>
#include <string>
#include "Song.h"
#include "Artist.h"

using namespace std;

class Search
{
public:

    // Search by song title
    vector<Song*> searchSong(
        const vector<Song*>& songs,
        const string& query
    );

    // Search by artist name
    vector<Artist*> searchArtist(
        const vector<Artist*>& artists,
        const string& query
    );

    // Search by category
    vector<Artist*> searchCategory(
        const vector<Artist*>& artists,
        const string& category
    );

    // Display functions
    void displaySongResults(
        const vector<Song*>& results
    );

    void displayArtistResults(
        const vector<Artist*>& results
    );
};

#endif