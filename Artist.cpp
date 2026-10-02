#include "Artist.h"

// Default Constructor
Artist::Artist()
{
    name = "";
    country = "";
    genre = "";
}

// Parameterized Constructor
Artist::Artist(string n, string c, string g)
{
    name = n;
    country = c;
    genre = g;
}

// Get Artist Name
string Artist::getName() const
{
    return name;
}

// Get Country
string Artist::getCountry() const
{
    return country;
}

// Get Genre
string Artist::getGenre() const
{
    return genre;
}

// Get All Songs
vector<Song*> Artist::getSongs() const
{
    return songs;
}

// Add Song to Artist
void Artist::addSong(Song* song)
{
    if (song == nullptr)
    {
        return;
    }

    songs.push_back(song);
}

// Display Artist Information
void Artist::displayArtist() const
{
    cout << "\n----- ARTIST INFORMATION -----\n";
    cout << "Name: " << name << endl;
    cout << "Country: " << country << endl;
    cout << "Genre: " << genre << endl;
}

// Display Artist Songs
void Artist::displaySongs() const
{
    cout << "\nSongs by " << name << ":\n";

    if (songs.empty())
    {
        cout << "No songs added yet.\n";
        return;
    }

    for (int i = 0; i < songs.size(); i++)
    {
        if (songs[i] != nullptr)
        {
            cout << i + 1 << ". "
                 << songs[i]->getTitle() << endl;
        }
    }
}