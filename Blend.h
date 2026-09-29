#ifndef BLEND_H
#define BLEND_H

#include <vector>
#include "Song.h"
#include "User.h"

using namespace std;

class Blend
{
private:
    vector<Song*> commonSongs;
    vector<Song*> combinedSongs;

public:

    // Find songs liked by both users
    vector<Song*> findCommonSongs(
        const User& user1,
        const User& user2
    );

    // Create combined Blend playlist
    vector<Song*> combineSongs(
        const User& user1,
        const User& user2
    );

    // Create and display Blend
    void displayBlend(
        const User& user1,
        const User& user2
    );

    // Get songs for MusicPlayer
    vector<Song*> getCommonSongs() const;
    vector<Song*> getCombinedSongs() const;
};

#endif