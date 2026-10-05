#include "Blend.h"
#include <iostream>

using namespace std;

vector<Song*> Blend::findCommonSongs(
    const User& user1,
    const User& user2)
{
    commonSongs.clear();

    vector<Song*> favorites1 = user1.getFavorites();
    vector<Song*> favorites2 = user2.getFavorites();

    for (Song* song1 : favorites1)
    {
        if (song1 == nullptr)
        {
            continue;
        }

        for (Song* song2 : favorites2)
        {
            if (song2 == nullptr)
            {
                continue;
            }

            // Same Song object = same song
            if (song1 == song2)
            {
                commonSongs.push_back(song1);
                break;
            }
        }
    }

    return commonSongs;
}


vector<Song*> Blend::combineSongs(
    const User& user1,
    const User& user2)
{
    combinedSongs.clear();

    vector<Song*> favorites1 = user1.getFavorites();
    vector<Song*> favorites2 = user2.getFavorites();

    // Add User 1 songs
    for (Song* song : favorites1)
    {
        if (song != nullptr)
        {
            combinedSongs.push_back(song);
        }
    }

    // Add User 2 songs if not already present
    for (Song* song2 : favorites2)
    {
        if (song2 == nullptr)
        {
            continue;
        }

        bool alreadyExists = false;

        for (Song* song1 : combinedSongs)
        {
            if (song1 == song2)
            {
                alreadyExists = true;
                break;
            }
        }

        if (!alreadyExists)
        {
            combinedSongs.push_back(song2);
        }
    }

    return combinedSongs;
}


void Blend::displayBlend(
    const User& user1,
    const User& user2)
{
    cout << "\n========================================\n";
    cout << "          💕 YOUR BLEND\n";
    cout << "========================================\n";

    cout << user1.getUserName()
         << " X "
         << user2.getUserName()
         << "\n";

    // Find common songs
    findCommonSongs(user1, user2);

    cout << "\n❤️ You Both Like:\n";

    if (commonSongs.empty())
    {
        cout << "No common songs.\n";
    }
    else
    {
        for (size_t i = 0; i < commonSongs.size(); ++i)
        {
            cout << i + 1 << ". "
                 << commonSongs[i]->getTitle()
                 << " - "
                 << commonSongs[i]->getArtist()
                 << endl;
        }
    }

    // Create combined playlist
    combineSongs(user1, user2);

    cout << "\n🎵 Your Blend Playlist:\n";

    if (combinedSongs.empty())
    {
        cout << "No songs available.\n";
    }
    else
    {
        for (size_t i = 0; i < combinedSongs.size(); ++i)
        {
            cout << i + 1 << ". "
                 << combinedSongs[i]->getTitle()
                 << " - "
                 << combinedSongs[i]->getArtist()
                 << endl;
        }
    }

    cout << "========================================\n";
}


vector<Song*> Blend::getCommonSongs() const
{
    return commonSongs;
}


vector<Song*> Blend::getCombinedSongs() const
{
    return combinedSongs;
}