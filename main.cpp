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
#include "MusicPlayer.h"

using namespace std;

class VibeFlow
{
private:
    vector<Song*> songs;
    vector<Artist*> artists;
    vector<User*> users;
    vector<Playlist*> playlists;

    Search searchEngine;
    Blend blendEngine;
    MusicPlayer musicPlayer;
    User* currentUser = nullptr;

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
        cout << "\n  Press ENTER to continue...";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    void header(const string& title, const string& subtitle = "")
    {
        cout << "\n+================================================+\n";
        cout << "|";
        int width = 48;
        int pad = width - static_cast<int>(title.length());
        if (pad < 0) pad = 0;
        cout << string(pad / 2, ' ') << title
             << string(pad - pad / 2, ' ') << "|\n";
        cout << "+================================================+\n";
        if (!subtitle.empty()) cout << "  " << subtitle << "\n";
    }

    int choice(int min, int max)
    {
        int n;
        while (true)
        {
            cout << "\n  Choose -> ";
            if (cin >> n && n >= min && n <= max)
            {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return n;
            }
            cout << "  Invalid choice. Even the menu has standards.\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    void loadData()
    {
        Artist* arijit = new Artist("Arijit Singh", "India", "Bollywood");
        Artist* shreya = new Artist("Shreya Ghoshal", "India", "Indian Playback");
        Artist* taylor = new Artist("Taylor Swift", "USA", "Pop");
        Artist* ed = new Artist("Ed Sheeran", "UK", "Pop");

        artists = { arijit, shreya, taylor, ed };

        songs.push_back(new Song("Kesariya", "Arijit Singh", "Pritam",
            "Amitabh Bhattacharya", "Brahmastra", 2022, "audio/kesariya.mp3"));
        songs.push_back(new Song("Tum Kya Mile", "Arijit Singh", "Pritam",
            "Amitabh Bhattacharya", "Rocky Aur Rani Kii Prem Kahaani", 2023, "audio/tum_kya_mile.mp3"));
        songs.push_back(new Song("Param Sundari", "Shreya Ghoshal", "A.R. Rahman",
            "Amitabh Bhattacharya", "Mimi", 2021, "audio/param_sundari.mp3"));
        songs.push_back(new Song("Cruel Summer", "Taylor Swift", "Taylor Swift",
            "Taylor Swift", "Lover", 2019, "audio/cruel_summer.mp3"));
        songs.push_back(new Song("Perfect", "Ed Sheeran", "Ed Sheeran",
            "Ed Sheeran", "Divide", 2017, "audio/perfect.mp3"));

        users.push_back(new User(1, "SnehaOnBeat"));
        users.push_back(new User(2, "SrushtiOnBeat"));
        users.push_back(new User(3, "AanyaMelody"));

        users[0]->addFavorite(songs[0]);
        users[0]->addFavorite(songs[3]);
        users[0]->addFavorite(songs[4]);
        users[1]->addFavorite(songs[0]);
        users[1]->addFavorite(songs[2]);
        users[1]->addFavorite(songs[4]);
        users[2]->addFavorite(songs[1]);
        users[2]->addFavorite(songs[3]);

        for (Song* s : songs)
            for (Artist* a : artists)
                if (s->getArtist() == a->getName())
                    a->addSong(s);
    }

    void welcome()
    {
        clearScreen();
        cout << "\n";
        cout << "              V I B E F L O W\n";
        cout << "       YOUR MUSIC. YOUR PEOPLE. YOUR VIBE.\n\n";
        cout << "       +--------------------------------+\n";
        cout << "       |      EVERY SONG HAS A STORY     |\n";
        cout << "       +--------------------------------+\n\n";
        cout << "  Building your soundscape...\n";
    }

    void selectUser()
    {
        clearScreen();
        header("YOUR VIBEFLOW ID", "Choose your account to enter.");
        for (size_t i = 0; i < users.size(); ++i)
            cout << "\n  " << i + 1 << ". " << users[i]->getUserName();
        cout << "\n  " << users.size() + 1 << ". Exit\n";

        int c = choice(1, static_cast<int>(users.size()) + 1);
        if (c == static_cast<int>(users.size()) + 1)
        {
            currentUser = nullptr;
            return;
        }
        currentUser = users[c - 1];
        cout << "\n  Welcome back, " << currentUser->getUserName() << "!\n";
        pauseScreen();
    }

    void home()
    {
        while (currentUser)
        {
            clearScreen();
            header("V I B E F L O W", "Your music space");
            cout << "\n  Hey, " << currentUser->getUserName() << ".\n";
            cout << "\n  +------------------------------------------+\n";
            cout << "  |  1. Explore Artists                      |\n";
            cout << "  |  2. Browse Songs                         |\n";
            cout << "  |  3. Search                               |\n";
            cout << "  |  4. Create a Blend                       |\n";
            cout << "  |  5. Your Favorites                       |\n";
            cout << "  |  6. Your Playlists                       |\n";
            cout << "  |  7. Music Player                         |\n";
            cout << "  |  8. Log Out                              |\n";
            cout << "  +------------------------------------------+\n";

            switch (choice(1, 8))
            {
                case 1: artistsMenu(); break;
                case 2: songsMenu(); break;
                case 3: searchMenu(); break;
                case 4: blendMenu(); break;
                case 5: favoritesMenu(); break;
                case 6: playlistMenu(); break;
                case 7: playerMenu(); break;
                case 8: musicPlayer.stop(); currentUser = nullptr; break;
            }
        }
    }

    void artistsMenu()
    {
        while (true)
        {
            clearScreen();
            header("ARTISTS", "Meet the voices behind the songs.");
            cout << "\n  1. Indian Artists\n";
            cout << "  2. International Artists\n";
            cout << "  3. All Artists\n";
            cout << "  4. Back\n";
            int c = choice(1, 4);
            if (c == 4) return;

            vector<Artist*> result;
            for (Artist* a : artists)
            {
                if (c == 3 || (c == 1 && a->getCountry() == "India") ||
                    (c == 2 && a->getCountry() != "India"))
                    result.push_back(a);
            }

            clearScreen();
            header("ARTIST DIRECTORY", "Choose an artist.");
            for (size_t i = 0; i < result.size(); ++i)
                cout << "\n  " << i + 1 << ". " << result[i]->getName()
                     << " [" << result[i]->getGenre() << "]";
            cout << "\n  " << result.size() + 1 << ". Back\n";
            int x = choice(1, static_cast<int>(result.size()) + 1);
            if (x == static_cast<int>(result.size()) + 1) continue;
            artistDetails(result[x - 1]);
        }
    }

    void artistDetails(Artist* artist)
    {
        clearScreen();
        header(artist->getName(), "Artist profile");
        cout << "\n  Country : " << artist->getCountry();
        cout << "\n  Genre   : " << artist->getGenre() << "\n";
        vector<Song*> list = artist->getSongs();
        cout << "\n  SONGS\n";
        if (list.empty()) cout << "\n  No songs connected.\n";
        else for (size_t i = 0; i < list.size(); ++i)
            cout << "\n  " << i + 1 << ". " << list[i]->getTitle();
        cout << "\n";
        pauseScreen();
    }

    void songsMenu()
    {
        while (true)
        {
            clearScreen();
            header("SONG LIBRARY", "Pick your soundtrack.");
            for (size_t i = 0; i < songs.size(); ++i)
                cout << "\n  " << i + 1 << ". " << songs[i]->getTitle()
                     << " - " << songs[i]->getArtist();
            cout << "\n  " << songs.size() + 1 << ". Back\n";
            int c = choice(1, static_cast<int>(songs.size()) + 1);
            if (c == static_cast<int>(songs.size()) + 1) return;
            songDetails(songs[c - 1]);
        }
    }

    void songDetails(Song* song)
    {
        clearScreen();
        header(song->getTitle(), "Song information");
        cout << "\n  Artist   : " << song->getArtist();
        cout << "\n  Composer : " << song->getComposer();
        cout << "\n  Lyricist : " << song->getLyricist();
        cout << "\n  Album    : " << song->getAlbum();
        cout << "\n  Year     : " << song->getYear() << "\n";
        cout << "\n  1. Play Song\n  2. Add to Favorites\n  3. Back\n";
        int c = choice(1, 3);
        if (c == 1) playCollection({song}, "NOW PLAYING");
        else if (c == 2)
        {
            currentUser->addFavorite(song);
            pauseScreen();
        }
    }

    void searchMenu()
    {
        clearScreen();
        header("SEARCH", "Find a song or artist.");
        cout << "\n  Search -> ";
        string q;
        getline(cin, q);
        if (q.empty()) return;

        vector<Song*> sr = searchEngine.searchSong(songs, q);
        vector<Artist*> ar = searchEngine.searchArtist(artists, q);

        clearScreen();
        header("SEARCH RESULTS", "Results for: " + q);
        cout << "\n  ARTISTS\n";
        if (ar.empty()) cout << "  No artists found.\n";
        else for (size_t i = 0; i < ar.size(); ++i)
            cout << "  " << i + 1 << ". " << ar[i]->getName() << "\n";

        cout << "\n  SONGS\n";
        if (sr.empty()) cout << "  No songs found.\n";
        else for (size_t i = 0; i < sr.size(); ++i)
            cout << "  " << i + 1 << ". " << sr[i]->getTitle()
                 << " - " << sr[i]->getArtist() << "\n";
        pauseScreen();
    }

    void blendMenu()
    {
        clearScreen();
        header("CREATE BLEND", "Two people. One soundtrack.");
        vector<User*> available;
        for (User* u : users) if (u != currentUser) available.push_back(u);
        cout << "\n  Your account -> " << currentUser->getUserName() << "\n";
        cout << "\n  Choose someone to Blend with:\n";
        for (size_t i = 0; i < available.size(); ++i)
            cout << "\n  " << i + 1 << ". " << available[i]->getUserName();
        cout << "\n  " << available.size() + 1 << ". Back\n";
        int c = choice(1, static_cast<int>(available.size()) + 1);
        if (c == static_cast<int>(available.size()) + 1) return;
        showBlend(available[c - 1]);
    }

    void showBlend(User* other)
    {
        vector<Song*> common = blendEngine.findCommonSongs(*currentUser, *other);
        vector<Song*> combined = blendEngine.combineSongs(*currentUser, *other);

        clearScreen();
        header("YOUR BLEND", currentUser->getUserName() + " x " + other->getUserName());

        cout << "\n  YOU BOTH LIKE\n";
        if (common.empty()) cout << "\n  No common songs yet.\n";
        else for (size_t i = 0; i < common.size(); ++i)
            cout << "\n  " << i + 1 << ". " << common[i]->getTitle()
                 << " - " << common[i]->getArtist();

        cout << "\n\n  YOUR BLEND\n";
        if (combined.empty()) cout << "\n  No songs available.\n";
        else for (size_t i = 0; i < combined.size(); ++i)
            cout << "\n  " << i + 1 << ". " << combined[i]->getTitle()
                 << " - " << combined[i]->getArtist();

        cout << "\n\n  1. Play Blend\n  2. Save as Playlist\n  3. Back\n";
        int c = choice(1, 3);
        if (c == 1) playCollection(combined, "BLEND PLAYBACK");
        else if (c == 2)
        {
            Playlist* p = new Playlist(currentUser->getUserName() + " x " + other->getUserName());
            for (Song* s : combined) p->addSong(s);
            playlists.push_back(p);
            cout << "\n  Blend saved as a playlist.\n";
            pauseScreen();
        }
    }

    void favoritesMenu()
    {
        while (true)
        {
            clearScreen();
            header("YOUR FAVORITES", "The songs you keep coming back to.");
            vector<Song*> fav = currentUser->getFavorites();
            if (fav.empty())
            {
                cout << "\n  No favorites yet.\n";
                pauseScreen();
                return;
            }
            for (size_t i = 0; i < fav.size(); ++i)
                cout << "\n  " << i + 1 << ". " << fav[i]->getTitle()
                     << " - " << fav[i]->getArtist();
            cout << "\n  " << fav.size() + 1 << ". Back\n";
            int c = choice(1, static_cast<int>(fav.size()) + 1);
            if (c == static_cast<int>(fav.size()) + 1) return;
            clearScreen();
            header("FAVORITE SONG", fav[c - 1]->getTitle());
            cout << "\n  1. Play\n  2. Remove\n  3. Back\n";
            int x = choice(1, 3);
            if (x == 1) playCollection({fav[c - 1]}, "NOW PLAYING");
            else if (x == 2)
            {
                currentUser->removeFavorite(fav[c - 1]->getTitle());
                pauseScreen();
            }
        }
    }

    void playlistMenu()
    {
        while (true)
        {
            clearScreen();
            header("YOUR PLAYLISTS", "A folder full of musical decisions.");
            if (playlists.empty()) cout << "\n  No playlists yet. Save a Blend to create one.\n";
            else for (size_t i = 0; i < playlists.size(); ++i)
                cout << "\n  " << i + 1 << ". " << playlists[i]->getName();
            cout << "\n\n  " << playlists.size() + 1 << ". Back\n";
            int c = choice(1, static_cast<int>(playlists.size()) + 1);
            if (c == static_cast<int>(playlists.size()) + 1) return;
            Playlist* p = playlists[c - 1];
            vector<Song*> list = p->getSongs();
            clearScreen();
            header(p->getName(), "Playlist");
            for (size_t i = 0; i < list.size(); ++i)
                cout << "\n  " << i + 1 << ". " << list[i]->getTitle()
                     << " - " << list[i]->getArtist();
            cout << "\n\n  1. Play Playlist\n  2. Back\n";
            if (choice(1, 2) == 1) playCollection(list, "PLAYLIST PLAYBACK");
        }
    }

    void prepareQueue(const vector<Song*>& list)
    {
        vector<MusicPlayer::Track> queue;
        for (Song* s : list)
            if (s) queue.push_back({s->getTitle(), s->getFilePath()});
        musicPlayer.setQueue(queue);
    }

    void playCollection(const vector<Song*>& list, const string& title)
    {
        if (list.empty())
        {
            cout << "\n  Nothing to play.\n";
            pauseScreen();
            return;
        }
        prepareQueue(list);
        clearScreen();
        header(title, list[0]->getTitle());
        if (!musicPlayer.playSong(list[0]->getTitle(), list[0]->getFilePath()))
            cout << "\n  Check that the audio file exists at the configured path.\n";
        playerMenu();
    }

    void playerMenu()
    {
        while (true)
        {
            cout << "\n\n  +------------------------------------------+\n";
            cout << "  | MUSIC PLAYER                             |\n";
            cout << "  +------------------------------------------+\n";
            cout << "  Current : " << musicPlayer.getCurrentTitle() << "\n";
            cout << "  Volume  : " << musicPlayer.getVolume() << "%\n";
            cout << "\n  1. Pause\n  2. Resume\n  3. Next\n  4. Previous\n";
            cout << "  5. Set Volume\n  6. Shuffle ON\n  7. Shuffle OFF\n";
            cout << "  8. Repeat ON\n  9. Repeat OFF\n  10. Stop\n  11. Back\n";
            int c = choice(1, 11);
            switch (c)
            {
                case 1: musicPlayer.pause(); break;
                case 2: musicPlayer.resume(); break;
                case 3: musicPlayer.next(); break;
                case 4: musicPlayer.previous(); break;
                case 5:
                {
                    cout << "\n  Volume (0-100) -> ";
                    float v;
                    if (cin >> v)
                    {
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        musicPlayer.setVolume(v);
                    }
                    else
                    {
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        cout << "  Invalid volume.\n";
                    }
                    break;
                }
                case 6: musicPlayer.setShuffle(true); break;
                case 7: musicPlayer.setShuffle(false); break;
                case 8: musicPlayer.setRepeat(true); break;
                case 9: musicPlayer.setRepeat(false); break;
                case 10: musicPlayer.stop(); break;
                case 11: return;
            }
            musicPlayer.update();
        }
    }

public:
    void run()
    {
        welcome();
        loadData();
        pauseScreen();

        while (true)
        {
            selectUser();
            if (!currentUser) break;
            home();
        }

        musicPlayer.stop();
        clearScreen();
        cout << "\n+================================================+\n";
        cout << "|          THANKS FOR VIBING WITH US            |\n";
        cout << "|              See you next time.               |\n";
        cout << "+================================================+\n";
    }
};

int main()
{
    VibeFlow app;
    app.run();
    return 0;
}
