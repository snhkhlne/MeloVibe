#include <iostream>
#include <vector>
#include <string>
#include <limits>
#include <cstdlib>

#include "Song.h"
#include "Artist.h"
#include "User.h"
#include "Blend.h"
#include "Playlist.h"
#include "Search.h"

using namespace std;


// ============================================================
//                     VIBEFLOW
//                 MAIN APPLICATION
// ============================================================

class VibeFlow
{
private:

    vector<Song*> songs;
    vector<Artist*> artists;
    vector<User*> users;
    vector<Playlist*> playlists;

    Search searchEngine;
    Blend blendEngine;

    User* currentUser = nullptr;


    // --------------------------------------------------------
    // Utility
    // --------------------------------------------------------

    void clearScreen()
    {
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif
    }


    void pauseScreen()
    {
        cout << "\n";
        cout << "Press ENTER to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    void header(const string& title, const string& subtitle = "")
    {
        cout << "\n";
        cout << "╔══════════════════════════════════════════════════╗\n";
        cout << "║";

        int spaces = 50 - static_cast<int>(title.length());

        if (spaces < 0)
            spaces = 0;

        int left = spaces / 2;
        int right = spaces - left;

        cout << string(left, ' ')
             << title
             << string(right, ' ')
             << "║\n";

        cout << "╚══════════════════════════════════════════════════╝\n";

        if (!subtitle.empty())
        {
            cout << "\n";
            cout << "        " << subtitle << "\n";
        }
    }


    int getChoice(int min, int max)
    {
        int choice;

        while (true)
        {
            cout << "\nChoose → ";

            if (cin >> choice && choice >= min && choice <= max)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return choice;
            }

            cout << "Hmm. That wasn't one of the options. Humanity survives.\n";

            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }


    // --------------------------------------------------------
    // SAMPLE DATA
    // --------------------------------------------------------

    void loadArtists()
    {
        /*
         * IMPORTANT:
         * Replace these constructors with the EXACT constructors
         * Member 1 creates in Artist.h.
         *
         * This section is deliberately kept separate so that
         * changing the library does not affect the UI.
         */


        // Example structure:
        //
        // artists.push_back(
        //     new Artist(
        //         "Lata Mangeshkar",
        //         "India",
        //         "Indian",
        //         "Playback",
        //         "Legendary Indian playback singer."
        //     )
        // );


        /*
         * TEMPORARY PLACEHOLDER:
         *
         * Once Member 1 sends Artist's constructor,
         * put the actual objects here.
         */
    }


    void loadSongs()
    {
        /*
         * Same idea here.
         *
         * Example:
         *
         * songs.push_back(
         *     new Song(
         *         "Kesariya",
         *         "Arijit Singh",
         *         "Pritam",
         *         "Amitabh Bhattacharya",
         *         "Brahmastra",
         *         2022,
         *         "songs/kesariya.mp3"
         *     )
         * );
         */

    }


    void loadUsers()
    {
        /*
         * Example:
         *
         * users.push_back(new User("SnehaOnBeat"));
         * users.push_back(new User("SrushtiOnBeat"));
         * users.push_back(new User("AanyaMelody"));
         */

    }


    void connectSongsToArtists()
    {
        /*
         * Once Member 1's Artist::addSong() is available,
         * connect songs with their artists here.
         *
         * Example:
         *
         * arijit->addSong(kesariya);
         */
    }


    // --------------------------------------------------------
    // WELCOME
    // --------------------------------------------------------

    void welcome()
    {
        clearScreen();

        cout << "\n";
        cout << "╔══════════════════════════════════════════════════╗\n";
        cout << "║                                                  ║\n";
        cout << "║              🎧  V I B E F L O W  🎧            ║\n";
        cout << "║                                                  ║\n";
        cout << "║       YOUR MUSIC. YOUR PEOPLE. YOUR VIBE.       ║\n";
        cout << "║                                                  ║\n";
        cout << "╚══════════════════════════════════════════════════╝\n";

        cout << "\n";
        cout << "       \"Every playlist tells a story.\"\n";
        cout << "\n";

        cout << "Loading your soundscape";

        for (int i = 0; i < 3; i++)
        {
            cout << ".";
        }

        cout << "\n";
    }


    // --------------------------------------------------------
    // USER SELECTION
    // --------------------------------------------------------

    void selectUser()
    {
        if (users.empty())
        {
            cout << "\nNo users available yet.\n";
            return;
        }

        header(
            "🎀 YOUR VIBEFLOW ID",
            "Choose your account to enter your music world."
        );

        for (size_t i = 0; i < users.size(); i++)
        {
            cout << "\n";
            cout << "  " << i + 1
                 << ". ✨ "
                 << users[i]->getUserName();
        }

        cout << "\n  " << users.size() + 1 << ". 🚪 Exit\n";

        int choice = getChoice(1, users.size() + 1);

        if (choice == static_cast<int>(users.size()) + 1)
        {
            currentUser = nullptr;
            return;
        }

        currentUser = users[choice - 1];

        cout << "\n";
        cout << "✨ Welcome back, "
             << currentUser->getUserName()
             << "!\n";

        pauseScreen();
    }


    // --------------------------------------------------------
    // HOME
    // --------------------------------------------------------

    void home()
    {
        while (currentUser != nullptr)
        {
            clearScreen();

            cout << "\n";
            cout << "╔══════════════════════════════════════════════════╗\n";
            cout << "║                                                  ║\n";
            cout << "║              🎧  V I B E F L O W               ║\n";
            cout << "║                                                  ║\n";
            cout << "╚══════════════════════════════════════════════════╝\n";

            cout << "\n";
            cout << "        Hey, "
                 << currentUser->getUserName()
                 << " 👋\n";

            cout << "\n";
            cout << "   \"What are we listening to today?\"\n";

            cout << "\n";
            cout << "   ┌──────────────────────────────────────────┐\n";
            cout << "   │  🎤  1. Explore Artists                  │\n";
            cout << "   │  🎵  2. Browse Songs                     │\n";
            cout << "   │  🔍  3. Search                           │\n";
            cout << "   │  💕  4. Create a Blend                   │\n";
            cout << "   │  ❤️  5. Your Favorites                   │\n";
            cout << "   │  📂  6. Your Playlists                   │\n";
            cout << "   │  🚪  7. Log Out                          │\n";
            cout << "   └──────────────────────────────────────────┘\n";

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
                    currentUser = nullptr;
                    break;
            }
        }
    }


    // ========================================================
    //                      ARTISTS
    // ========================================================

    void artistsMenu()
    {
        while (true)
        {
            clearScreen();

            header(
                "🎤 ARTISTS",
                "Meet the voices behind your favorite songs."
            );

            cout << "\n";
            cout << "   🇮🇳  1. Indian Artists\n";
            cout << "   🌎  2. International Artists\n";
            cout << "   ↩️  3. Back\n";

            int choice = getChoice(1, 3);

            if (choice == 3)
                return;

            string category;

            if (choice == 1)
                category = "Indian";
            else
                category = "International";

            vector<Artist*> results =
                searchEngine.searchCategory(artists, category);

            displayArtistList(results);
        }
    }


    void displayArtistList(const vector<Artist*>& list)
    {
        clearScreen();

        if (list.empty())
        {
            header("🎤 ARTISTS");

            cout << "\nNo artists found in this category.\n";
            pauseScreen();
            return;
        }

        string category = list[0]->getCategory();

        if (category == "Indian")
        {
            header(
                "🇮🇳 INDIAN ARTISTS",
                "Voices that made memories."
            );
        }
        else
        {
            header(
                "🌎 INTERNATIONAL ARTISTS",
                "Sounds from around the world."
            );
        }

        for (size_t i = 0; i < list.size(); i++)
        {
            cout << "\n";
            cout << "   " << i + 1
                 << ". 🎤 "
                 << list[i]->getName();
        }

        cout << "\n";
        cout << "   " << list.size() + 1
             << ". ↩️ Back\n";

        int choice = getChoice(1, list.size() + 1);

        if (choice == static_cast<int>(list.size()) + 1)
            return;

        showArtist(list[choice - 1]);
    }


    void showArtist(Artist* artist)
    {
        clearScreen();

        header(
            "🎤 " + artist->getName(),
            "Artist Profile"
        );

        cout << "\n";
        cout << "   Category  → "
             << artist->getCategory();

        cout << "\n";
        cout << "   Country   → "
             << artist->getCountry();

        cout << "\n";
        cout << "   Genre     → "
             << artist->getGenre();

        cout << "\n\n";
        cout << "   📖 ABOUT\n";
        cout << "   " << artist->getBiography() << "\n";

        cout << "\n";
        cout << "   🎵 SONGS\n";

        vector<Song*> artistSongs = artist->getSongs();

        if (artistSongs.empty())
        {
            cout << "   No songs available.\n";
        }
        else
        {
            for (size_t i = 0; i < artistSongs.size(); i++)
            {
                cout << "\n   "
                     << i + 1
                     << ". "
                     << artistSongs[i]->getTitle();
            }
        }

        cout << "\n";
        pauseScreen();
    }


    // ========================================================
    //                        SONGS
    // ========================================================

    void songsMenu()
    {
        clearScreen();

        header(
            "🎵 SONG LIBRARY",
            "Pick something that matches your mood."
        );

        if (songs.empty())
        {
            cout << "\nYour library is empty.\n";
            pauseScreen();
            return;
        }

        for (size_t i = 0; i < songs.size(); i++)
        {
            cout << "\n";
            cout << "   " << i + 1
                 << ". 🎵 "
                 << songs[i]->getTitle()
                 << " — "
                 << songs[i]->getArtist();
        }

        cout << "\n";
        cout << "   " << songs.size() + 1
             << ". ↩️ Back\n";

        int choice = getChoice(1, songs.size() + 1);

        if (choice == static_cast<int>(songs.size()) + 1)
            return;

        showSong(songs[choice - 1]);
    }


    void showSong(Song* song)
    {
        clearScreen();

        header(
            "🎵 " + song->getTitle(),
            "Song Information"
        );

        cout << "\n";
        cout << "   🎤 Artist    → "
             << song->getArtist();

        cout << "\n";
        cout << "   🎼 Composer  → "
             << song->getComposer();

        cout << "\n";
        cout << "   ✍️ Lyricist  → "
             << song->getLyricist();

        cout << "\n";
        cout << "   💿 Album     → "
             << song->getAlbum();

        cout << "\n";
        cout << "   📅 Year      → "
             << song->getYear();

        cout << "\n";

        pauseScreen();
    }


    // ========================================================
    //                        SEARCH
    // ========================================================

    void searchMenu()
    {
        clearScreen();

        header(
            "🔍 SEARCH",
            "Find a song or artist."
        );

        cout << "\n";
        cout << "Search → ";

        string query;
        getline(cin, query);

        if (query.empty())
            return;

        vector<Song*> songResults =
            searchEngine.searchSong(songs, query);

        vector<Artist*> artistResults =
            searchEngine.searchArtist(artists, query);

        clearScreen();

        header(
            "🔍 SEARCH RESULTS",
            "Results for: " + query
        );

        cout << "\n";
        cout << "   🎤 ARTISTS\n";

        if (artistResults.empty())
        {
            cout << "   No artists found.\n";
        }
        else
        {
            for (size_t i = 0; i < artistResults.size(); i++)
            {
                cout << "   "
                     << i + 1
                     << ". "
                     << artistResults[i]->getName()
                     << "\n";
            }
        }

        cout << "\n";
        cout << "   🎵 SONGS\n";

        if (songResults.empty())
        {
            cout << "   No songs found.\n";
        }
        else
        {
            for (size_t i = 0; i < songResults.size(); i++)
            {
                cout << "   "
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


    // ========================================================
    //                         BLEND
    // ========================================================

    void blendMenu()
    {
        if (users.size() < 2)
        {
            clearScreen();

            header(
                "💕 CREATE BLEND",
                "Two people. One playlist."
            );

            cout << "\n";
            cout << "You need at least two users to create a Blend.\n";

            pauseScreen();
            return;
        }

        while (true)
        {
            clearScreen();

            header(
                "💕 CREATE BLEND",
                "Music is better when shared."
            );

            cout << "\n";
            cout << "   Your account:\n";
            cout << "   → "
                 << currentUser->getUserName()
                 << "\n";

            cout << "\n";
            cout << "   Who do you want to blend with? 👀\n";

            vector<User*> availableUsers;

            for (User* user : users)
            {
                if (user != currentUser)
                {
                    availableUsers.push_back(user);
                }
            }

            for (size_t i = 0; i < availableUsers.size(); i++)
            {
                cout << "\n   "
                     << i + 1
                     << ". ✨ "
                     << availableUsers[i]->getUserName();
            }

            cout << "\n";
            cout << "   "
                 << availableUsers.size() + 1
                 << ". ↩️ Back\n";

            int choice =
                getChoice(1, availableUsers.size() + 1);

            if (choice == static_cast<int>(availableUsers.size()) + 1)
                return;

            createBlend(availableUsers[choice - 1]);
        }
    }


    void createBlend(User* otherUser)
    {
        clearScreen();

        header(
            "💕 CREATE BLEND",
            "Finding your musical chemistry..."
        );

        cout << "\n";
        cout << "   "
             << currentUser->getUserName()
             << "\n";

        cout << "            ×\n";

        cout << "   "
             << otherUser->getUserName()
             << "\n";

        cout << "\n";
        cout << "   🎧 Comparing your favorites...\n";

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

        header(
            "💕 " + currentUser->getUserName()
            + " × "
            + otherUser->getUserName(),
            "Your musical chemistry"
        );

        cout << "\n";
        cout << "   ❤️ YOU BOTH LIKE\n";

        if (common.empty())
        {
            cout << "\n   No common songs yet.";
        }
        else
        {
            for (size_t i = 0; i < common.size(); i++)
            {
                cout << "\n   "
                     << i + 1
                     << ". "
                     << common[i]->getTitle()
                     << " — "
                     << common[i]->getArtist();
            }
        }

        cout << "\n\n";
        cout << "   🎵 YOUR BLEND\n";

        if (combined.empty())
        {
            cout << "\n   No songs available.";
        }
        else
        {
            for (size_t i = 0; i < combined.size(); i++)
            {
                cout << "\n   "
                     << i + 1
                     << ". "
                     << combined[i]->getTitle()
                     << " — "
                     << combined[i]->getArtist();
            }
        }

        cout << "\n\n";
        cout << "   ▶ 1. Play Blend\n";
        cout << "   🎵 2. View Songs\n";
        cout << "   💾 3. Save Blend as Playlist\n";
        cout << "   ↩️ 4. Back\n";

        int choice = getChoice(1, 4);

        switch (choice)
        {
            case 1:
                playBlend(combined);
                break;

            case 2:
                displayBlendSongs(combined);
                break;

            case 3:
                saveBlendAsPlaylist(
                    currentUser->getUserName()
                    + " × "
                    + otherUser->getUserName(),
                    combined
                );
                break;

            case 4:
                return;
        }
    }


    void displayBlendSongs(const vector<Song*>& songsList)
    {
        clearScreen();

        header(
            "🎵 YOUR BLEND",
            "The playlist created for both of you."
        );

        for (size_t i = 0; i < songsList.size(); i++)
        {
            cout << "\n";
            cout << "   "
                 << i + 1
                 << ". "
                 << songsList[i]->getTitle()
                 << " — "
                 << songsList[i]->getArtist();
        }

        cout << "\n";

        pauseScreen();
    }


    void playBlend(const vector<Song*>& songsList)
    {
        /*
         * MUSIC PLAYER INTEGRATION GOES HERE.
         *
         * Once Member 2 gives you MusicPlayer.h,
         * create/use the MusicPlayer object here.
         *
         * Example:
         *
         * player.setQueue(songsList);
         * player.play();
         */

        clearScreen();

        header(
            "🎧 BLEND PLAYBACK",
            "Your shared soundtrack starts here."
        );

        if (songsList.empty())
        {
            cout << "\nNo songs to play.\n";
        }
        else
        {
            cout << "\n";
            cout << "Now playing your Blend...\n\n";

            cout << "♪ "
                 << songsList[0]->getTitle()
                 << "\n";

            cout << "   "
                 << songsList[0]->getArtist()
                 << "\n";
        }

        pauseScreen();
    }


    void saveBlendAsPlaylist(
        const string& name,
        const vector<Song*>& songsList)
    {
        Playlist* playlist =
            new Playlist(name);

        for (Song* song : songsList)
        {
            playlist->addSong(song);
        }

        playlists.push_back(playlist);

        cout << "\n";
        cout << "💾 Blend saved as:\n";
        cout << "   " << name << "\n";

        pauseScreen();
    }


    // ========================================================
    //                      FAVORITES
    // ========================================================

    void favoritesMenu()
    {
        clearScreen();

        header(
            "❤️ YOUR FAVORITES",
            "The songs you keep coming back to."
        );

        vector<Song*> favorites =
            currentUser->getFavorites();

        if (favorites.empty())
        {
            cout << "\n";
            cout << "Your favorites are empty.\n";
            cout << "Go find some music. Humanity depends on it.\n";

            pauseScreen();
            return;
        }

        for (size_t i = 0; i < favorites.size(); i++)
        {
            cout << "\n";
            cout << "   ❤️ "
                 << i + 1
                 << ". "
                 << favorites[i]->getTitle()
                 << " — "
                 << favorites[i]->getArtist();
        }

        cout << "\n";

        pauseScreen();
    }


    // ========================================================
    //                       PLAYLISTS
    // ========================================================

    void playlistMenu()
    {
        while (true)
        {
            clearScreen();

            header(
                "📂 YOUR PLAYLISTS",
                "A folder full of musical decisions."
            );

            if (playlists.empty())
            {
                cout << "\n";
                cout << "No playlists yet.\n";
            }
            else
            {
                for (size_t i = 0; i < playlists.size(); i++)
                {
                    cout << "\n";
                    cout << "   📂 "
                         << i + 1
                         << ". "
                         << playlists[i]->getName();
                }
            }

            cout << "\n\n";
            cout << "   ↩️ "
                 << (playlists.size() + 1)
                 << ". Back\n";

            int choice =
                getChoice(1, playlists.size() + 1);

            if (choice == static_cast<int>(playlists.size()) + 1)
                return;

            playlists[choice - 1]->displayPlaylist();

            pauseScreen();
        }
    }


public:

    // ========================================================
    //                       START APP
    // ========================================================

    void run()
    {
        welcome();

        // Load project data
        loadArtists();
        loadSongs();
        loadUsers();
        connectSongsToArtists();

        pauseScreen();

        while (true)
        {
            clearScreen();

            selectUser();

            if (currentUser == nullptr)
            {
                clearScreen();

                cout << "\n";
                cout << "╔══════════════════════════════════════════════════╗\n";
                cout << "║                                                  ║\n";
                cout << "║       🎧 Thanks for vibing with VibeFlow 🎧     ║\n";
                cout << "║                                                  ║\n";
                cout << "║              See you next time. 💜              ║\n";
                cout << "║                                                  ║\n";
                cout << "╚══════════════════════════════════════════════════╝\n";

                return;
            }

            home();
        }
    }
};


// ============================================================
//                         MAIN
// ============================================================

int main()
{
    VibeFlow app;

    app.run();

    return 0;
}
