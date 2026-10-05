#ifndef UI_H
#define UI_H

#include <string>
#include <vector>

#include "Song.h"
#include "Artist.h"
#include "User.h"
#include "Blend.h"
#include "Playlist.h"
#include "Search.h"
#include "MusicPlayer.h"

class UI
{
private:
    std::vector<Song*>* songs;
    std::vector<Artist*>* artists;
    std::vector<User*>* users;
    std::vector<Playlist*>* playlists;

    Search searchEngine;
    Blend blendEngine;
    MusicPlayer musicPlayer;

    User* currentUser;

    void clearScreen();
    void pauseScreen();
    void printHeader(const std::string& title,
                     const std::string& subtitle = "");
    int getChoice(int minimum, int maximum);

    void welcomeScreen();
    void userSelection();
    void homeMenu();

    void artistsMenu();
    void artistCategoryMenu(const std::string& category);
    void artistDetails(Artist* artist);

    void songsMenu();
    void songDetails(Song* song);

    void searchMenu();

    void blendMenu();
    void createBlend(User* otherUser);
    void blendPlayer(const std::vector<Song*>& blendSongs,
                     const std::string& blendName);

    void favoritesMenu();
    void playlistMenu();

public:
    UI(std::vector<Song*>& songList,
       std::vector<Artist*>& artistList,
       std::vector<User*>& userList,
       std::vector<Playlist*>& playlistList);

    void run();
};

#endif
