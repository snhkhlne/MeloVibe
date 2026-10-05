#include "UI.h"

#include <iostream>
#include <limits>
#include <cstdlib>

using namespace std;

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
    cout << "\n\n";
    cout << "        Press ENTER to continue...";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

void UI::printHeader(const string& title, const string& subtitle)
{
    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║                                                      ║\n";
    cout << "║";

    int width = 52;
    int spaces = width - static_cast<int>(title.length());

    if (spaces < 0)
        spaces = 0;

    int left = spaces / 2;
    int right = spaces - left;

    cout << string(left, ' ')
         << title
         << string(right, ' ')
         << "║\n";

    cout << "║                                                      ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";

    if (!subtitle.empty())
    {
        cout << "\n";
        cout << "        " << subtitle << "\n";
    }
}

int UI::getChoice(int minimum, int maximum)
{
    int choice;

    while (true)
    {
        cout << "\n        Choose → ";

        if (cin >> choice && choice >= minimum && choice <= maximum)
        {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return choice;
        }

        cout << "\n        That option doesn't exist. "
             << "The menu remains stubbornly unchanged.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void UI::welcomeScreen()
{
    clearScreen();

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║                                                      ║\n";
    cout << "║                🎧  V I B E F L O W  🎧              ║\n";
    cout << "║                                                      ║\n";
    cout << "║          YOUR MUSIC. YOUR PEOPLE. YOUR VIBE.         ║\n";
    cout << "║                                                      ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";

    cout << "\n";
    cout << "        \"Every playlist tells a story.\"\n";
    cout << "\n";
    cout << "        Building your soundscape";

    for (int i = 0; i < 3; ++i)
        cout << ".";

    cout << "\n";
}

void UI::userSelection()
{
    while (true)
    {
        clearScreen();

        printHeader(
            "🎀 YOUR VIBEFLOW ID",
            "Choose the account that owns this soundtrack."
        );

        if (users->empty())
        {
            cout << "\n        No users have been added yet.\n";
            pauseScreen();
            return;
        }

        cout << "\n";

        for (size_t i = 0; i < users->size(); ++i)
        {
            cout << "        "
                 << i + 1
                 << ". ✨ "
                 << (*users)[i]->getUserName()
                 << "\n";
        }

        cout << "\n        "
             << users->size() + 1
             << ". 🚪 Exit\n";

        int choice = getChoice(
            1,
            static_cast<int>(users->size()) + 1
        );

        if (choice == static_cast<int>(users->size()) + 1)
        {
            currentUser = nullptr;
            return;
        }

        currentUser = (*users)[choice - 1];

        clearScreen();

        printHeader(
            "✨ WELCOME BACK",
            "Your music world is waiting."
        );

        cout << "\n";
        cout << "        🎧 "
             << currentUser->getUserName()
             << ", you're in.\n";

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
        cout << "╔══════════════════════════════════════════════════════╗\n";
        cout << "║                  🎧 VIBEFLOW                         ║\n";
        cout << "╚══════════════════════════════════════════════════════╝\n";

        cout << "\n        Hey, "
             << currentUser->getUserName()
             << " 👋\n";

        cout << "\n        What are we listening to today?\n";

        cout << "\n";
        cout << "        ┌──────────────────────────────────────────┐\n";
        cout << "        │  🎤  1. Explore Artists                 │\n";
        cout << "        │  🎵  2. Browse Songs                    │\n";
        cout << "        │  🔍  3. Search                          │\n";
        cout << "        │  💕  4. Create a Blend                  │\n";
        cout << "        │  ❤️  5. Your Favorites                  │\n";
        cout << "        │  📂  6. Your Playlists                  │\n";
        cout << "        │  🚪  7. Log Out                         │\n";
        cout << "        └──────────────────────────────────────────┘\n";

        int choice = getChoice(1, 7);

        switch (choice)
        {
            case 1:
                artistsMenu();
                break;

            case 2:
                songsMenu();
                break;

            case 3:
                searchMenu();
                break;

            case 4:
                blendMenu();
                break;

            case 5:
                favoritesMenu();
                break;

            case 6:
                playlistMenu();
                break;

            case 7:
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

        printHeader(
            "🎤 ARTISTS",
            "Discover the people behind the music."
        );

        cout << "\n";
        cout << "        🇮🇳  1. Indian Artists\n";
        cout << "        🌎  2. International Artists\n";
        cout << "        ↩️  3. Back\n";

        int choice = getChoice(1, 3);

        if (choice == 3)
            return;

        if (choice == 1)
            artistCategoryMenu("Indian");
        else
            artistCategoryMenu("International");
    }
}

void UI::artistCategoryMenu(const string& category)
{
    clearScreen();

    string heading;

    if (category == "Indian")
        heading = "🇮🇳 INDIAN ARTISTS";
    else
        heading = "🌎 INTERNATIONAL ARTISTS";

    printHeader(
        heading,
        "Choose an artist and enter their musical world."
    );

    vector<Artist*> results =
        searchEngine.searchCategory(*artists, category);

    /*
     * Your current Artist class does not contain a category field.
     * Therefore, for compatibility with the exact files supplied,
     * category filtering is based on country:
     *
     * Indian         -> country == "India"
     * International  -> country != "India"
     *
     * This fallback is used below instead of calling getCategory().
     */

    results.clear();

    for (Artist* artist : *artists)
    {
        if (artist == nullptr)
            continue;

        string country = artist->getCountry();

        if (category == "Indian" && country == "India")
            results.push_back(artist);

        if (category == "International" && country != "India")
            results.push_back(artist);
    }

    if (results.empty())
    {
        cout << "\n        No artists found in this category.\n";
        pauseScreen();
        return;
    }

    cout << "\n";

    for (size_t i = 0; i < results.size(); ++i)
    {
        cout << "        "
             << i + 1
             << ". 🎤 "
             << results[i]->getName()
             << "\n";
    }

    cout << "\n        "
         << results.size() + 1
         << ". ↩️ Back\n";

    int choice = getChoice(
        1,
        static_cast<int>(results.size()) + 1
    );

    if (choice == static_cast<int>(results.size()) + 1)
        return;

    artistDetails(results[choice - 1]);
}

void UI::artistDetails(Artist* artist)
{
    if (artist == nullptr)
        return;

    clearScreen();

    printHeader(
        "🎤 " + artist->getName(),
        "Artist Profile"
    );

    cout << "\n";
    cout << "        🌍 Country : "
         << artist->getCountry() << "\n";

    cout << "        🎼 Genre   : "
         << artist->getGenre() << "\n";

    cout << "\n        🎵 SONGS\n";
    cout << "        ─────────────────────────────────────────\n";

    vector<Song*> artistSongs = artist->getSongs();

    if (artistSongs.empty())
    {
        cout << "        No songs have been linked yet.\n";
    }
    else
    {
        for (size_t i = 0; i < artistSongs.size(); ++i)
        {
            if (artistSongs[i] == nullptr)
                continue;

            cout << "        "
                 << i + 1
                 << ". "
                 << artistSongs[i]->getTitle()
                 << "\n";
        }
    }

    pauseScreen();
}

void UI::songsMenu()
{
    while (true)
    {
        clearScreen();

        printHeader(
            "🎵 SONG LIBRARY",
            "A collection of questionable emotional decisions."
        );

        if (songs->empty())
        {
            cout << "\n        No songs are available yet.\n";
            pauseScreen();
            return;
        }

        cout << "\n";

        for (size_t i = 0; i < songs->size(); ++i)
        {
            if ((*songs)[i] == nullptr)
                continue;

            cout << "        "
                 << i + 1
                 << ". 🎵 "
                 << (*songs)[i]->getTitle()
                 << " — "
                 << (*songs)[i]->getArtist()
                 << "\n";
        }

        cout << "\n        "
             << songs->size() + 1
             << ". ↩️ Back\n";

        int choice = getChoice(
            1,
            static_cast<int>(songs->size()) + 1
        );

        if (choice == static_cast<int>(songs->size()) + 1)
            return;

        songDetails((*songs)[choice - 1]);
    }
}

void UI::songDetails(Song* song)
{
    if (song == nullptr)
        return;

    while (true)
    {
        clearScreen();

        printHeader(
            "🎵 " + song->getTitle(),
            "Song Information"
        );

        cout << "\n";
        cout << "        🎤 Artist   : "
             << song->getArtist() << "\n";

        cout << "        🎼 Composer : "
             << song->getComposer() << "\n";

        cout << "        ✍️ Lyricist : "
             << song->getLyricist() << "\n";

        cout << "        💿 Album    : "
             << song->getAlbum() << "\n";

        cout << "        📅 Year     : "
             << song->getYear() << "\n";

        cout << "\n        ─────────────────────────────────────────\n";
        cout << "        ▶ 1. Play Song\n";
        cout << "        ❤️ 2. Add to Favorites\n";
        cout << "        ↩️ 3. Back\n";

        int choice = getChoice(1, 3);

        if (choice == 1)
        {
            musicPlayer.playSong(
                song->getTitle(),
                song->getFilePath()
            );
            pauseScreen();
        }
        else if (choice == 2)
        {
            currentUser->addFavorite(song);
            pauseScreen();
        }
        else
        {
            return;
        }
    }
}

void UI::searchMenu()
{
    clearScreen();

    printHeader(
        "🔍 SEARCH",
        "Type a song title or artist name."
    );

    cout << "\n        Search → ";

    string query;
    getline(cin, query);

    if (query.empty())
        return;

    vector<Song*> songResults =
        searchEngine.searchSong(*songs, query);

    vector<Artist*> artistResults =
        searchEngine.searchArtist(*artists, query);

    clearScreen();

    printHeader(
        "🔍 SEARCH RESULTS",
        "Results for: " + query
    );

    cout << "\n        🎤 ARTISTS\n";
    cout << "        ─────────────────────────────────────────\n";

    if (artistResults.empty())
    {
        cout << "        No artists found.\n";
    }
    else
    {
        for (size_t i = 0; i < artistResults.size(); ++i)
        {
            cout << "        "
                 << i + 1
                 << ". "
                 << artistResults[i]->getName()
                 << "\n";
        }
    }

    cout << "\n        🎵 SONGS\n";
    cout << "        ─────────────────────────────────────────\n";

    if (songResults.empty())
    {
        cout << "        No songs found.\n";
    }
    else
    {
        for (size_t i = 0; i < songResults.size(); ++i)
        {
            cout << "        "
                 << i + 1
                 << ". "
                 << songResults[i]->getTitle()
                 << " — "
                 << songResults[i]->getArtist()
                 << "\n";
        }
    }

    pauseScreen();
}

void UI::blendMenu()
{
    if (users->size() < 2)
    {
        clearScreen();

        printHeader(
            "💕 CREATE BLEND",
            "Two people. One soundtrack."
        );

        cout << "\n        At least two users are needed.\n";
        pauseScreen();
        return;
    }

    clearScreen();

    printHeader(
        "💕 CREATE BLEND",
        "Your favorites are about to meet."
    );

    cout << "\n        Your account:\n";
    cout << "        → "
         << currentUser->getUserName()
         << "\n";

    cout << "\n        Who do you want to blend with? 👀\n";

    vector<User*> availableUsers;

    for (User* user : *users)
    {
        if (user != nullptr && user != currentUser)
            availableUsers.push_back(user);
    }

    for (size_t i = 0; i < availableUsers.size(); ++i)
    {
        cout << "\n        "
             << i + 1
             << ". ✨ "
             << availableUsers[i]->getUserName();
    }

    cout << "\n\n        "
         << availableUsers.size() + 1
         << ". ↩️ Back\n";

    int choice = getChoice(
        1,
        static_cast<int>(availableUsers.size()) + 1
    );

    if (choice == static_cast<int>(availableUsers.size()) + 1)
        return;

    createBlend(availableUsers[choice - 1]);
}

void UI::createBlend(User* otherUser)
{
    if (otherUser == nullptr)
        return;

    clearScreen();

    printHeader(
        "💕 CREATE BLEND",
        "Finding your musical chemistry..."
    );

    cout << "\n";
    cout << "        "
         << currentUser->getUserName()
         << "\n";

    cout << "\n              ×\n\n";

    cout << "        "
         << otherUser->getUserName()
         << "\n";

    cout << "\n        🎧 Comparing your favorites...\n";

    vector<Song*> common =
        blendEngine.findCommonSongs(
            *currentUser,
            *otherUser
        );

    vector<Song*> combined =
        blendEngine.combineSongs(
            *currentUser,
            *otherUser
        );

    clearScreen();

    string blendName =
        currentUser->getUserName()
        + " × "
        + otherUser->getUserName();

    printHeader(
        "💕 YOUR BLEND",
        blendName
    );

    cout << "\n        ❤️ YOU BOTH LIKE\n";
    cout << "        ─────────────────────────────────────────\n";

    if (common.empty())
    {
        cout << "        No common songs yet.\n";
    }
    else
    {
        for (size_t i = 0; i < common.size(); ++i)
        {
            cout << "        "
                 << i + 1
                 << ". "
                 << common[i]->getTitle()
                 << " — "
                 << common[i]->getArtist()
                 << "\n";
        }
    }

    cout << "\n        🎵 YOUR BLEND\n";
    cout << "        ─────────────────────────────────────────\n";

    if (combined.empty())
    {
        cout << "        No songs available.\n";
    }
    else
    {
        for (size_t i = 0; i < combined.size(); ++i)
        {
            cout << "        "
                 << i + 1
                 << ". "
                 << combined[i]->getTitle()
                 << " — "
                 << combined[i]->getArtist()
                 << "\n";
        }
    }

    cout << "\n";
    cout << "        ▶ 1. Play Blend\n";
    cout << "        🎵 2. View Songs\n";
    cout << "        💾 3. Save as Playlist\n";
    cout << "        ↩️ 4. Back\n";

    int choice = getChoice(1, 4);

    if (choice == 1)
    {
        blendPlayer(combined, blendName);
    }
    else if (choice == 2)
    {
        clearScreen();

        printHeader(
            "🎵 BLEND TRACKLIST",
            "The songs you somehow agreed on."
        );

        for (size_t i = 0; i < combined.size(); ++i)
        {
            cout << "\n        "
                 << i + 1
                 << ". "
                 << combined[i]->getTitle()
                 << " — "
                 << combined[i]->getArtist();
        }

        pauseScreen();
    }
    else if (choice == 3)
    {
        Playlist* playlist =
            new Playlist(blendName);

        for (Song* song : combined)
            playlist->addSong(song);

        playlists->push_back(playlist);

        cout << "\n        💾 Blend saved as:\n";
        cout << "        " << blendName << "\n";

        pauseScreen();
    }
}

void UI::blendPlayer(const vector<Song*>& blendSongs,
                     const string& blendName)
{
    if (blendSongs.empty())
    {
        cout << "\n        There are no songs to play.\n";
        pauseScreen();
        return;
    }

    vector<MusicPlayer::Track> queue;

    for (Song* song : blendSongs)
    {
        if (song == nullptr)
            continue;

        MusicPlayer::Track track;
        track.title = song->getTitle();
        track.filePath = song->getFilePath();

        queue.push_back(track);
    }

    musicPlayer.setQueue(queue);

    if (!queue.empty())
    {
        musicPlayer.playSong(
            queue[0].title,
            queue[0].filePath
        );
    }

    while (true)
    {
        clearScreen();

        printHeader(
            "🎧 BLEND PLAYER",
            blendName
        );

        cout << "\n        ♪ Now Playing\n";

        string currentTitle =
            musicPlayer.getCurrentTitle();

        if (currentTitle.empty())
            cout << "        Nothing is playing.\n";
        else
            cout << "        " << currentTitle << "\n";

        cout << "\n";
        cout << "        ┌────────────────────────────────────┐\n";
        cout << "        │  1. ⏸ Pause                       │\n";
        cout << "        │  2. ▶ Resume                      │\n";
        cout << "        │  3. ⏭ Next                        │\n";
        cout << "        │  4. ⏮ Previous                    │\n";
        cout << "        │  5. 🔊 Volume                     │\n";
        cout << "        │  6. 🔀 Shuffle ON                 │\n";
        cout << "        │  7. 🔁 Repeat ON                  │\n";
        cout << "        │  8. ⏹ Stop & Back                 │\n";
        cout << "        └────────────────────────────────────┘\n";

        int choice = getChoice(1, 8);

        switch (choice)
        {
            case 1:
                musicPlayer.pause();
                pauseScreen();
                break;

            case 2:
                musicPlayer.resume();
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
                cout << "\n        Volume (0-100) → ";
                float volume;

                if (cin >> volume)
                {
                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n'
                    );

                    musicPlayer.setVolume(volume);
                }
                else
                {
                    cin.clear();
                    cin.ignore(
                        numeric_limits<streamsize>::max(),
                        '\n'
                    );
                }

                pauseScreen();
                break;
            }

            case 6:
                musicPlayer.setShuffle(true);
                pauseScreen();
                break;

            case 7:
                musicPlayer.setRepeat(true);
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

        printHeader(
            "❤️ YOUR FAVORITES",
            "The songs you keep coming back to."
        );

        vector<Song*> favorites =
            currentUser->getFavorites();

        if (favorites.empty())
        {
            cout << "\n        Your favorites are empty.\n";
            cout << "        Go find something worth obsessing over.\n";
            pauseScreen();
            return;
        }

        cout << "\n";

        for (size_t i = 0; i < favorites.size(); ++i)
        {
            if (favorites[i] == nullptr)
                continue;

            cout << "        ❤️ "
                 << i + 1
                 << ". "
                 << favorites[i]->getTitle()
                 << " — "
                 << favorites[i]->getArtist()
                 << "\n";
        }

        cout << "\n        "
             << favorites.size() + 1
             << ". ↩️ Back\n";

        int choice = getChoice(
            1,
            static_cast<int>(favorites.size()) + 1
        );

        if (choice == static_cast<int>(favorites.size()) + 1)
            return;

        Song* selected = favorites[choice - 1];

        clearScreen();

        printHeader(
            "❤️ FAVORITE SONG",
            selected->getTitle()
        );

        cout << "\n        ▶ 1. Play\n";
        cout << "        🗑 2. Remove from Favorites\n";
        cout << "        ↩️ 3. Back\n";

        int action = getChoice(1, 3);

        if (action == 1)
        {
            musicPlayer.playSong(
                selected->getTitle(),
                selected->getFilePath()
            );
            pauseScreen();
        }
        else if (action == 2)
        {
            currentUser->removeFavorite(
                selected->getTitle()
            );
            pauseScreen();
        }
    }
}

void UI::playlistMenu()
{
    while (true)
    {
        clearScreen();

        printHeader(
            "📂 YOUR PLAYLISTS",
            "A carefully organized pile of musical decisions."
        );

        if (playlists->empty())
        {
            cout << "\n        No playlists yet.\n";
        }
        else
        {
            cout << "\n";

            for (size_t i = 0; i < playlists->size(); ++i)
            {
                if ((*playlists)[i] == nullptr)
                    continue;

                cout << "        📂 "
                     << i + 1
                     << ". "
                     << (*playlists)[i]->getName()
                     << "\n";
            }
        }

        cout << "\n        "
             << playlists->size() + 1
             << ". ↩️ Back\n";

        int choice = getChoice(
            1,
            static_cast<int>(playlists->size()) + 1
        );

        if (choice == static_cast<int>(playlists->size()) + 1)
            return;

        Playlist* playlist =
            (*playlists)[choice - 1];

        clearScreen();

        printHeader(
            "📂 PLAYLIST",
            playlist->getName()
        );

        vector<Song*> playlistSongs =
            playlist->getSongs();

        if (playlistSongs.empty())
        {
            cout << "\n        Playlist is empty.\n";
        }
        else
        {
            for (size_t i = 0; i < playlistSongs.size(); ++i)
            {
                if (playlistSongs[i] == nullptr)
                    continue;

                cout << "\n        "
                     << i + 1
                     << ". "
                     << playlistSongs[i]->getTitle()
                     << " — "
                     << playlistSongs[i]->getArtist();
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

    cout << "\n";
    cout << "╔══════════════════════════════════════════════════════╗\n";
    cout << "║                                                      ║\n";
    cout << "║       🎧 Thanks for vibing with VibeFlow 🎧          ║\n";
    cout << "║                                                      ║\n";
    cout << "║                  See you next time. 💜               ║\n";
    cout << "║                                                      ║\n";
    cout << "╚══════════════════════════════════════════════════════╝\n";
}
