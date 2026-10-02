#ifndef USER_H
#define USER_H

#include "Song.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class User
{
private:
    int userId;
    string userName;
    vector<Song*> favoriteSongs;

public:
    // Constructors
    User();
    User(int id, string name);

    // Getter Functions
    int getUserId() const;
    string getUserName() const;
    vector<Song*> getFavorites() const;

    // Favorite Song Functions
    void addFavorite(Song* song);
    void removeFavorite(string title);
    void displayFavorites() const;
};

#endif
