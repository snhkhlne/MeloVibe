#include "Search.h"
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;


// Convert string to lowercase
string toLowerCase(string text)
{
    transform(
        text.begin(),
        text.end(),
        text.begin(),
        [](unsigned char c)
        {
            return tolower(c);
        }
    );

    return text;
}


// Search Song
vector<Song*> Search::searchSong(
    const vector<Song*>& songs,
    const string& query)
{
    vector<Song*> results;

    string searchText = toLowerCase(query);

    for (Song* song : songs)
    {
        if (song == nullptr)
        {
            continue;
        }

        string title = toLowerCase(song->getTitle());

        if (title.find(searchText) != string::npos)
        {
            results.push_back(song);
        }
    }

    return results;
}


// Search Artist
vector<Artist*> Search::searchArtist(
    const vector<Artist*>& artists,
    const string& query)
{
    vector<Artist*> results;

    string searchText = toLowerCase(query);

    for (Artist* artist : artists)
    {
        if (artist == nullptr)
        {
            continue;
        }

        string artistName = toLowerCase(artist->getName());

        if (artistName.find(searchText) != string::npos)
        {
            results.push_back(artist);
        }
    }

    return results;
}


// Search Category
vector<Artist*> Search::searchCategory(
    const vector<Artist*>& artists,
    const string& category)
{
    vector<Artist*> results;

    string searchCategoryText =
        toLowerCase(category);

    for (Artist* artist : artists)
    {
        if (artist == nullptr)
        {
            continue;
        }

        string artistCategory =
            toLowerCase(artist->getCategory());

        if (artistCategory == searchCategoryText)
        {
            results.push_back(artist);
        }
    }

    return results;
}


// Display Song Results
void Search::displaySongResults(
    const vector<Song*>& results)
{
    cout << "\n=================================\n";
    cout << "          SEARCH RESULTS\n";
    cout << "=================================\n";

    if (results.empty())
    {
        cout << "No songs found.\n";
        return;
    }

    for (size_t i = 0; i < results.size(); ++i)
    {
        cout << i + 1 << ". "
             << results[i]->getTitle()
             << " - "
             << results[i]->getArtist()
             << endl;
    }
}


// Display Artist Results
void Search::displayArtistResults(
    const vector<Artist*>& results)
{
    cout << "\n=================================\n";
    cout << "          ARTIST RESULTS\n";
    cout << "=================================\n";

    if (results.empty())
    {
        cout << "No artists found.\n";
        return;
    }

    for (size_t i = 0; i < results.size(); ++i)
    {
        cout << i + 1 << ". "
             << results[i]->getName()
             << " - "
             << results[i]->getCategory()
             << endl;
    }
}