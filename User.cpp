
#include "User.h"

// Default Constructor
User::User()
{
    userId = 0;
    userName = "";
}

// Parameterized Constructor
User::User(int id, string name)
{
    userId = id;
    userName = name;
}

// Get User ID
int User::getUserId() const
{
    return userId;
}

// Get User Name
string User::getUserName() const
{
    return userName;
}

// Get Favorite Songs
vector<Song*> User::getFavorites() const
{
    return favoriteSongs;
}

// Add Favorite Song
void User::addFavorite(Song* song)
{
    if (song == nullptr)
    {
        return;
    }

    // Check if song is already in favorites
    for (Song* s : favoriteSongs)
    {
        if (s == song)
        {
            cout << "Song already in favorites!" << endl;
            return;
        }
    }

    favoriteSongs.push_back(song);

    cout << "Song added to favorites!" << endl;
}

// Remove Favorite Song
void User::removeFavorite(string title)
{
    for (auto it = favoriteSongs.begin();
         it != favoriteSongs.end();
         ++it)
    {
        if (*it != nullptr &&
            (*it)->getTitle() == title)
        {
            favoriteSongs.erase(it);

            cout << "Song removed from favorites!" << endl;
            return;
        }
    }

    cout << "Song not found in favorites!" << endl;
}

// Display Favorite Songs
void User::displayFavorites() const
{
    cout << "\n----- FAVORITE SONGS -----\n";
    cout << "User: " << userName << endl;

    if (favoriteSongs.empty())
    {
        cout << "No favorite songs yet!" << endl;
        return;
    }

    for (size_t i = 0; i < favoriteSongs.size(); ++i)
    {
        if (favoriteSongs[i] != nullptr)
        {
            cout << i + 1 << ". "
                 << favoriteSongs[i]->getTitle()
                 << " - "
                 << favoriteSongs[i]->getArtist()
                 << endl;
        }
    }
}