#include "UI.h"

#include <iostream>
#include <limits>
#include <cstdlib>
#include <string>
#include <vector>

using namespace std;

/*
    Modern terminal UI for MeloVibe.
    Drop-in replacement for the existing UI.cpp.
    UI.h and the other project classes remain unchanged.
*/

namespace
{
    const string LINE = "==============================================================";
    const string THIN = "--------------------------------------------------------------";

    void printSection(const string& title)
    {
        cout << "\n+" << LINE << "+\n";
        cout << "| " << title;
        int padding = 60 - static_cast<int>(title.size());
        if (padding < 0) padding = 0;
        cout << string(padding, ' ') << "|\n";
        cout << "+" << LINE << "+\n";
    }

    void printRow(int number, const string& tag,
                  const string& title, const string& extra = "")
    {
        string text = "[" + to_string(number) + "] " + tag + "  " + title;
        if (!extra.empty())
            text += "  |  " + extra;

        const int width = 58;
        if (static_cast<int>(text.size()) > width)
            text = text.substr(0, width - 3) + "...";

        cout << "  " << text << string(width - text.size(), ' ') << "\n";
    }

    bool isFavorite(const vector<Song*>& favorites, Song* song)
    {
        if (song == nullptr) return false;

        for (Song* favorite : favorites)
        {
            if (favorite == song) return true;
            if (favorite != nullptr &&
                favorite->getTitle() == song->getTitle())
                return true;
        }
        return false;
    }
}

UI::UI(vector<Song*>& songList,
       vector<Artist*>& artistList,
       vector<User*>& userList,
       vector<Playlist*>& playlistList)
{
    songs = &songList;
    artists = &artistList;
    users = &userList;
    playlists = &playlistList;
    currentUser = nullptr;
}

void UI::clearScreen()
{
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void UI::pauseScreen()
{
    cout << "\n  Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void UI::printHeader(const string& title, const string& subtitle)
{
    cout << "\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  |  MELOVIBE                                                |\n";
    cout << "  +----------------------------------------------------------+\n";
    cout << "  |  " << title;

    int padding = 56 - static_cast<int>(title.size());
    if (padding < 0) padding = 0;
    cout << string(padding, ' ') << "|\n";
    cout << "  +----------------------------------------------------------+\n";

    if (!subtitle.empty())
        cout << "  " << subtitle << "\n";
}

int UI::getChoice(int minimum, int maximum)
{
    int choice;

    while (true)
    {
        cout << "\n  Enter choice [" << minimum << "-" << maximum << "]: ";

        if (cin >> choice && choice >= minimum && choice <= maximum)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "\n  Invalid choice. Please enter a number from "
             << minimum << " to " << maximum << ".\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void UI::welcomeScreen()
{
    clearScreen();

    cout << "\n\n";
    cout << "       +------------------------------------------------+\n";
    cout << "       |                                                |\n";
    cout << "       |              M E L O V I B E                   |\n";
    cout << "       |                                                |\n";
    cout << "       |        YOUR MUSIC. YOUR VIBE.                  |\n";
    cout << "       |                                                |\n";
    cout << "       +------------------------------------------------+\n";
    cout << "\n";
    cout << "       Tune in. Find your sound. Blend your taste.\n";
    cout << "       A compact C++ music experience for discovery,\n";
    cout << "       playback, favorites and shared playlists.\n";
    cout << "\n";
}

void UI::userSelection()
{
    while (true)
    {
        clearScreen();
        printHeader("SELECT PROFILE", "Choose the user who is entering MeloVibe.");

        if (users->empty())
        {
            cout << "\n  No users are available.\n";
            pauseScreen();
            return;
        }

        cout << "\n  AVAILABLE PROFILES\n";
        cout << "  " << THIN << "\n";

        for (size_t i = 0; i < users->size(); ++i)
        {
            if ((*users)[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "USER", (*users)[i]->getUserName());
        }

        cout << "\n";
        printRow(static_cast<int>(users->size() + 1), "EXIT", "Close MeloVibe");

        int choice = getChoice(1, static_cast<int>(users->size()) + 1);

        if (choice == static_cast<int>(users->size()) + 1)
        {
            currentUser = nullptr;
            return;
        }

        if ((*users)[choice - 1] == nullptr) continue;

        currentUser = (*users)[choice - 1];

        clearScreen();
        printHeader("WELCOME BACK", "Your music dashboard is ready.");
        cout << "\n  Signed in as: " << currentUser->getUserName() << "\n";
        pauseScreen();
        return;
    }
}

void UI::homeMenu()
{
    while (currentUser != nullptr)
    {
        clearScreen();

        cout << "\n";
        cout << "  +----------------------------------------------------------+\n";
        cout << "  |                       MELOVIBE                           |\n";
        cout << "  +----------------------------------------------------------+\n";
        cout << "  |  Welcome, " << currentUser->getUserName();
        int padding = 47 - static_cast<int>(currentUser->getUserName().size());
        if (padding < 0) padding = 0;
        cout << string(padding, ' ') << "|\n";
        cout << "  +----------------------------------------------------------+\n";

        cout << "\n  MUSIC DASHBOARD\n";
        cout << "  " << THIN << "\n";
        printRow(1, "ARTIST", "Explore Artists");
        printRow(2, "SONG", "Browse Song Library");
        printRow(3, "SEARCH", "Search Music");
        printRow(4, "BLEND", "Create a Music Blend");
        printRow(5, "FAV", "Your Favorites");
        printRow(6, "LIST", "Your Playlists");
        printRow(7, "PLAYER", "Open Music Player");
        printRow(8, "EXIT", "Log Out");

        int choice = getChoice(1, 8);

        switch (choice)
        {
            case 1: artistsMenu(); break;
            case 2: songsMenu(); break;
            case 3: searchMenu(); break;
            case 4: blendMenu(); break;
            case 5: favoritesMenu(); break;
            case 6: playlistMenu(); break;
            case 7:
            {
                if (musicPlayer.getCurrentTitle().empty())
                {
                    clearScreen();
                    printHeader("MUSIC PLAYER", "Nothing is playing");
                    cout << "\n  Start a song from the library first.\n";
                    pauseScreen();
                    break;
                }

                while (true)
                {
                    clearScreen();
                    printHeader("MUSIC PLAYER", musicPlayer.getCurrentTitle());
                    cout << "\n  PLAYER CONTROLS\n  " << THIN << "\n";
                    printRow(1, "PAUSE", "Pause");
                    printRow(2, "RESUME", "Resume");
                    printRow(3, "NEXT", "Next Track");
                    printRow(4, "PREV", "Previous Track");
                    printRow(5, "VOLUME", "Set Volume");
                    printRow(6, "SHUFFLE", "Shuffle ON");
                    printRow(7, "SHUFFLE", "Shuffle OFF");
                    printRow(8, "REPEAT", "Repeat ON");
                    printRow(9, "REPEAT", "Repeat OFF");
                    printRow(10, "STOP", "Stop Playback");
                    printRow(11, "BACK", "Return to Home");

                    int pc = getChoice(1, 11);
                    switch (pc)
                    {
                        case 1: musicPlayer.pause(); break;
                        case 2: musicPlayer.resume(); break;
                        case 3: musicPlayer.next(); break;
                        case 4: musicPlayer.previous(); break;
                        case 5:
                        {
                            cout << "\n  Volume [0-100]: ";
                            float v;
                            if (cin >> v)
                            {
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                if (v < 0) v = 0;
                                if (v > 100) v = 100;
                                musicPlayer.setVolume(v);
                                cout << "  Volume set to " << v << "%.\n";
                            }
                            else
                            {
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cout << "  Invalid volume.\n";
                            }
                            pauseScreen();
                            break;
                        }
                        case 6: musicPlayer.setShuffle(true); cout << "\n  Shuffle enabled.\n"; pauseScreen(); break;
                        case 7: musicPlayer.setShuffle(false); cout << "\n  Shuffle disabled.\n"; pauseScreen(); break;
                        case 8: musicPlayer.setRepeat(true); cout << "\n  Repeat enabled.\n"; pauseScreen(); break;
                        case 9: musicPlayer.setRepeat(false); cout << "\n  Repeat disabled.\n"; pauseScreen(); break;
                        case 10: musicPlayer.stop(); pauseScreen(); break;
                        case 11: goto exitPlayerMenu;
                    }
                }
                exitPlayerMenu:
                break;
            }
            case 8:
                musicPlayer.stop();
                currentUser = nullptr;
                break;
        }
    }
}

void UI::artistsMenu()
{
    while (true)
    {
        clearScreen();
        printHeader("ARTIST DISCOVERY", "Choose a name. Then explore the tracks behind it.");
        cout << "\n";
        printRow(1, "INDIA", "Indian Artists");
        printRow(2, "WORLD", "International Artists");
        printRow(3, "BACK", "Return to Dashboard");

        int choice = getChoice(1, 3);
        if (choice == 3) return;
        if (choice == 1) artistCategoryMenu("Indian");
        else artistCategoryMenu("International");
    }
}

void UI::artistCategoryMenu(const string& category)
{
    clearScreen();

    string title = category == "Indian" ? "INDIAN ARTISTS" : "INTERNATIONAL ARTISTS";
    printHeader(title, "Three signature tracks. One artist profile.");

    vector<Artist*> results;

    for (Artist* artist : *artists)
    {
        if (artist == nullptr) continue;
        string country = artist->getCountry();

        if (category == "Indian" && country == "India")
            results.push_back(artist);
        if (category == "International" && country != "India")
            results.push_back(artist);
    }

    if (results.empty())
    {
        cout << "\n  No artists found in this category.\n";
        pauseScreen();
        return;
    }

    cout << "\n  ARTIST DIRECTORY\n";
    cout << "  " << THIN << "\n";

    for (size_t i = 0; i < results.size(); ++i)
        printRow(static_cast<int>(i + 1), "ARTIST", results[i]->getName());

    cout << "\n";
    printRow(static_cast<int>(results.size() + 1), "BACK", "Return");

    int choice = getChoice(1, static_cast<int>(results.size()) + 1);
    if (choice == static_cast<int>(results.size()) + 1) return;
    artistDetails(results[choice - 1]);
}

void UI::artistDetails(Artist* artist)
{
    if (artist == nullptr) return;

    clearScreen();
    printHeader(artist->getName(), "Artist Profile");

    cout << "\n  Country : " << artist->getCountry() << "\n";
    cout << "  Genre   : " << artist->getGenre() << "\n";

    cout << "\n  SONGS BY THIS ARTIST\n";
    cout << "  " << THIN << "\n";

    vector<Song*> artistSongs = artist->getSongs();

    if (artistSongs.empty())
        cout << "  No songs have been linked yet.\n";
    else
    {
        for (size_t i = 0; i < artistSongs.size(); ++i)
        {
            if (artistSongs[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "SONG", artistSongs[i]->getTitle());
        }
    }

    pauseScreen();
}

void UI::songsMenu()
{
    while (true)
    {
        clearScreen();
        printHeader("SONG LIBRARY", "18 tracks. Six artists. One library.");

        if (songs->empty())
        {
            cout << "\n  No songs are available.\n";
            pauseScreen();
            return;
        }

        cout << "\n  TRACKLIST\n";
        cout << "  " << THIN << "\n";

        for (size_t i = 0; i < songs->size(); ++i)
        {
            if ((*songs)[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "PLAY", (*songs)[i]->getTitle(), (*songs)[i]->getArtist());
        }

        cout << "\n";
        printRow(static_cast<int>(songs->size() + 1), "BACK", "Return");

        int choice = getChoice(1, static_cast<int>(songs->size()) + 1);
        if (choice == static_cast<int>(songs->size()) + 1) return;
        songDetails((*songs)[choice - 1]);
    }
}

void UI::songDetails(Song* song)
{
    if (song == nullptr) return;

    while (true)
    {
        clearScreen();
        printHeader(song->getTitle(), "Song Information");

        cout << "\n  DETAILS\n";
        cout << "  " << THIN << "\n";
        cout << "  Artist   : " << song->getArtist() << "\n";
        cout << "  Composer : " << song->getComposer() << "\n";
        cout << "  Lyricist : " << song->getLyricist() << "\n";
        cout << "  Album    : " << song->getAlbum() << "\n";
        cout << "  Year     : " << song->getYear() << "\n";

        cout << "\n  ACTIONS\n";
        cout << "  " << THIN << "\n";
        printRow(1, "PLAY", "Play Song");
        printRow(2, "FAV", "Add to Favorites");
        printRow(3, "BACK", "Return");

        int choice = getChoice(1, 3);

        if (choice == 1)
        {
            if (!musicPlayer.playSong(song->getTitle(), song->getFilePath()))
                cout << "\n  Could not start the song. Check the audio file path.\n";
            else
                cout << "\n  Now playing: " << song->getTitle() << "\n";
            pauseScreen();
        }
        else if (choice == 2)
        {
            vector<Song*> favorites = currentUser->getFavorites();

            clearScreen();
            printHeader("FAVORITES", song->getTitle());

            if (isFavorite(favorites, song))
            {
                cout << "\n  This track is already in your Favorites.\n";
                cout << "  No duplicate entry was created.\n";
            }
            else
            {
                currentUser->addFavorite(song);
                cout << "\n  Track added to Favorites.\n";
            }
            pauseScreen();
        }
        else return;
    }
}

void UI::searchMenu()
{
    clearScreen();
    printHeader("SEARCH", "Search the library in seconds.");

    cout << "\n  Search: ";
    string query;
    getline(cin, query);
    if (query.empty()) return;

    vector<Song*> songResults = searchEngine.searchSong(*songs, query);
    vector<Artist*> artistResults = searchEngine.searchArtist(*artists, query);

    clearScreen();
    printHeader("SEARCH RESULTS", "Query: " + query);

    cout << "\n  ARTISTS\n";
    cout << "  " << THIN << "\n";

    if (artistResults.empty())
        cout << "  No matching artists found.\n";
    else
    {
        for (size_t i = 0; i < artistResults.size(); ++i)
        {
            if (artistResults[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "ARTIST", artistResults[i]->getName());
        }
    }

    cout << "\n  SONGS\n";
    cout << "  " << THIN << "\n";

    if (songResults.empty())
        cout << "  No matching songs found.\n";
    else
    {
        for (size_t i = 0; i < songResults.size(); ++i)
        {
            if (songResults[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "SONG", songResults[i]->getTitle(), songResults[i]->getArtist());
        }
    }

    pauseScreen();
}

void UI::blendMenu()
{
    if (users->size() < 2)
    {
        clearScreen();
        printHeader("CREATE BLEND", "A blend needs at least two users.");
        cout << "\n  At least two users are required.\n";
        pauseScreen();
        return;
    }

    clearScreen();
    printHeader("CREATE BLEND", "Two tastes. One shared queue.");

    cout << "\n  CURRENT USER\n";
    cout << "  " << THIN << "\n";
    cout << "  " << currentUser->getUserName() << "\n";

    vector<User*> availableUsers;
    for (User* user : *users)
        if (user != nullptr && user != currentUser)
            availableUsers.push_back(user);

    cout << "\n  CHOOSE A USER\n";
    cout << "  " << THIN << "\n";

    for (size_t i = 0; i < availableUsers.size(); ++i)
        printRow(static_cast<int>(i + 1), "USER", availableUsers[i]->getUserName());

    cout << "\n";
    printRow(static_cast<int>(availableUsers.size() + 1), "BACK", "Return");

    int choice = getChoice(1, static_cast<int>(availableUsers.size()) + 1);
    if (choice == static_cast<int>(availableUsers.size()) + 1) return;
    createBlend(availableUsers[choice - 1]);
}

void UI::createBlend(User* otherUser)
{
    if (otherUser == nullptr) return;

    clearScreen();
    printHeader("YOUR BLEND", currentUser->getUserName() + " + " + otherUser->getUserName());

    cout << "\n  COMBINING MUSIC TASTES...\n";
    cout << "  " << THIN << "\n";

    vector<Song*> common = blendEngine.findCommonSongs(*currentUser, *otherUser);
    vector<Song*> combined = blendEngine.combineSongs(*currentUser, *otherUser);

    cout << "\n  SONGS YOU BOTH LIKE\n";
    cout << "  " << THIN << "\n";

    if (common.empty())
        cout << "  No common songs found.\n";
    else
    {
        for (size_t i = 0; i < common.size(); ++i)
        {
            if (common[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "MATCH", common[i]->getTitle(), common[i]->getArtist());
        }
    }

    cout << "\n  COMBINED BLEND\n";
    cout << "  " << THIN << "\n";

    if (combined.empty())
        cout << "  No songs available.\n";
    else
    {
        for (size_t i = 0; i < combined.size(); ++i)
        {
            if (combined[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "TRACK", combined[i]->getTitle(), combined[i]->getArtist());
        }
    }

    cout << "\n  ACTIONS\n";
    cout << "  " << THIN << "\n";
    printRow(1, "PLAY", "Play Blend");
    printRow(2, "VIEW", "View Blend Songs");
    printRow(3, "SAVE", "Save as Playlist");
    printRow(4, "BACK", "Return");

    int choice = getChoice(1, 4);
    string blendName = currentUser->getUserName() + " + " + otherUser->getUserName();

    if (choice == 1)
    {
        blendPlayer(combined, blendName);
    }
    else if (choice == 2)
    {
        clearScreen();
        printHeader("BLEND TRACKLIST", blendName);

        if (combined.empty())
            cout << "\n  No songs in this blend.\n";
        else
        {
            for (size_t i = 0; i < combined.size(); ++i)
            {
                if (combined[i] == nullptr) continue;
                printRow(static_cast<int>(i + 1), "TRACK", combined[i]->getTitle(), combined[i]->getArtist());
            }
        }
        pauseScreen();
    }
    else if (choice == 3)
    {
        Playlist* playlist = new Playlist(blendName);
        for (Song* song : combined)
            if (song != nullptr) playlist->addSong(song);
        playlists->push_back(playlist);

        clearScreen();
        printHeader("PLAYLIST SAVED", blendName);
        cout << "\n  " << THIN << "\n";
        cout << "  TRACKS ADDED: " << combined.size() << "\n";
        cout << "  " << THIN << "\n";

        for (size_t i = 0; i < combined.size(); ++i)
        {
            if (combined[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "TRACK", combined[i]->getTitle());
        }

        cout << "  " << THIN << "\n";
        cout << "  Saved to Your Playlists.\n";
        pauseScreen();
    }
}

void UI::blendPlayer(const vector<Song*>& blendSongs,
                     const string& blendName)
{
    if (blendSongs.empty())
    {
        cout << "\n  There are no songs to play.\n";
        pauseScreen();
        return;
    }

    vector<MusicPlayer::Track> queue;

    for (Song* song : blendSongs)
    {
        if (song == nullptr) continue;
        MusicPlayer::Track track;
        track.title = song->getTitle();
        track.filePath = song->getFilePath();
        queue.push_back(track);
    }

    musicPlayer.setQueue(queue);

    if (!queue.empty())
    {
        if (!musicPlayer.playSong(queue[0].title, queue[0].filePath))
        {
            cout << "\n  Unable to start the first track.\n";
            pauseScreen();
            return;
        }
    }

    while (true)
    {
        clearScreen();
        printHeader("NOW PLAYING", blendName);

        string currentTitle = musicPlayer.getCurrentTitle();

        cout << "\n  CURRENT TRACK\n";
        cout << "  " << THIN << "\n";
        cout << "  " << (currentTitle.empty() ? "Nothing is playing." : currentTitle) << "\n";

        cout << "\n  PLAYER CONTROLS\n";
        cout << "  " << THIN << "\n";
        printRow(1, "PAUSE", "Pause");
        printRow(2, "PLAY", "Resume");
        printRow(3, "NEXT", "Next Track");
        printRow(4, "PREV", "Previous Track");
        printRow(5, "VOL", "Set Volume");
        printRow(6, "SHUF", "Shuffle ON");
        printRow(7, "REPEAT", "Repeat ON");
        printRow(8, "STOP", "Stop and Return");

        int choice = getChoice(1, 8);

        switch (choice)
        {
            case 1:
                musicPlayer.pause();
                cout << "\n  Playback paused.\n";
                pauseScreen();
                break;
            case 2:
                musicPlayer.resume();
                cout << "\n  Playback resumed.\n";
                pauseScreen();
                break;
            case 3:
                musicPlayer.next();
                pauseScreen();
                break;
            case 4:
                musicPlayer.previous();
                pauseScreen();
                break;
            case 5:
            {
                cout << "\n  Volume (0-100): ";
                float volume;
                if (cin >> volume)
                {
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    if (volume < 0) volume = 0;
                    if (volume > 100) volume = 100;
                    musicPlayer.setVolume(volume);
                    cout << "  Volume set to " << volume << "%.\n";
                }
                else
                {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "  Invalid volume.\n";
                }
                pauseScreen();
                break;
            }
            case 6:
                musicPlayer.setShuffle(true);
                cout << "\n  Shuffle enabled.\n";
                pauseScreen();
                break;
            case 7:
                musicPlayer.setRepeat(true);
                cout << "\n  Repeat enabled.\n";
                pauseScreen();
                break;
            case 8:
                musicPlayer.stop();
                return;
        }
    }
}

void UI::favoritesMenu()
{
    while (true)
    {
        clearScreen();
        printHeader("YOUR FAVORITES", "Songs you have saved for quick access.");

        vector<Song*> favorites = currentUser->getFavorites();

        if (favorites.empty())
        {
            cout << "\n  No favorite songs yet.\n";
            cout << "  Add songs from the Song Library.\n";
            pauseScreen();
            return;
        }

        cout << "\n  FAVORITE TRACKS\n";
        cout << "  " << THIN << "\n";

        for (size_t i = 0; i < favorites.size(); ++i)
        {
            if (favorites[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "FAV", favorites[i]->getTitle(), favorites[i]->getArtist());
        }

        cout << "\n";
        printRow(static_cast<int>(favorites.size() + 1), "BACK", "Return");

        int choice = getChoice(1, static_cast<int>(favorites.size()) + 1);
        if (choice == static_cast<int>(favorites.size()) + 1) return;

        Song* selected = favorites[choice - 1];
        if (selected == nullptr) continue;

        clearScreen();
        printHeader("FAVORITE SONG", selected->getTitle());
        cout << "\n";
        printRow(1, "PLAY", "Play Song");
        printRow(2, "REMOVE", "Remove from Favorites");
        printRow(3, "BACK", "Return");

        int action = getChoice(1, 3);

        if (action == 1)
        {
            if (!musicPlayer.playSong(selected->getTitle(), selected->getFilePath()))
                cout << "\n  Unable to play this song.\n";
            else
                cout << "\n  Now playing: " << selected->getTitle() << "\n";
            pauseScreen();
        }
        else if (action == 2)
        {
            currentUser->removeFavorite(selected->getTitle());
            cout << "\n  Removed from favorites.\n";
            pauseScreen();
        }
    }
}

void UI::playlistMenu()
{
    while (true)
    {
        clearScreen();
        printHeader("YOUR PLAYLISTS", "Saved Blend collections.");

        if (playlists->empty())
        {
            cout << "\n  No playlists yet.\n";
            cout << "  Create a Blend and save it as a playlist.\n";
            pauseScreen();
            return;
        }

        cout << "\n  PLAYLIST COLLECTION\n";
        cout << "  " << THIN << "\n";

        for (size_t i = 0; i < playlists->size(); ++i)
        {
            if ((*playlists)[i] == nullptr) continue;
            printRow(static_cast<int>(i + 1), "LIST", (*playlists)[i]->getName());
        }

        cout << "\n";
        printRow(static_cast<int>(playlists->size() + 1), "BACK", "Return");

        int choice = getChoice(1, static_cast<int>(playlists->size()) + 1);
        if (choice == static_cast<int>(playlists->size()) + 1) return;

        Playlist* playlist = (*playlists)[choice - 1];
        if (playlist == nullptr) continue;

        clearScreen();
        printHeader(playlist->getName(), "Playlist Details");

        vector<Song*> playlistSongs = playlist->getSongs();

        cout << "\n  TRACKS\n";
        cout << "  " << THIN << "\n";

        if (playlistSongs.empty())
            cout << "  Playlist is empty.\n";
        else
        {
            for (size_t i = 0; i < playlistSongs.size(); ++i)
            {
                if (playlistSongs[i] == nullptr) continue;
                printRow(static_cast<int>(i + 1), "TRACK", playlistSongs[i]->getTitle(), playlistSongs[i]->getArtist());
            }
        }

        pauseScreen();
    }
}

void UI::run()
{
    welcomeScreen();
    pauseScreen();

    while (true)
    {
        userSelection();
        if (currentUser == nullptr)
            break;
        homeMenu();
    }

    clearScreen();

    cout << "\n\n";
    cout << "       +------------------------------------------------+\n";
    cout << "       |                                                |\n";
    cout << "       |             THANK YOU FOR USING                |\n";
    cout << "       |                    MELOVIBE                    |\n";
    cout << "       |                                                |\n";
    cout << "       |                 See you again!                 |\n";
    cout << "       |                                                |\n";
    cout << "       +------------------------------------------------+\n";
    cout << "\n";
}
