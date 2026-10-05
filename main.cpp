#include <iostream>
#include <vector>

#include "Song.h"
#include "Artist.h"
#include "User.h"
#include "Playlist.h"
#include "UI.h"

using namespace std;

static void loadData(vector<Song*>& songs,
                     vector<Artist*>& artists,
                     vector<User*>& users)
{
    // ---------------------------------------------------------
    // ARTISTS
    // ---------------------------------------------------------
    Artist* taylor = new Artist("Taylor Swift", "USA", "Pop");
    Artist* shreya = new Artist("Shreya Ghoshal", "India", "Playback");
    Artist* lata = new Artist("Lata Mangeshkar", "India", "Playback");
    Artist* asha = new Artist("Asha Bhosle", "India", "Playback");
    Artist* ariana = new Artist("Ariana Grande", "USA", "Pop");
    Artist* arijit = new Artist("Arijit Singh", "India", "Playback");

    artists = {taylor, shreya, lata, asha, ariana, arijit};

    // ---------------------------------------------------------
    // SONGS
    //
    // Audio files are kept directly in the MeloVibe project folder.
    // The paths below match the filenames currently used in the project.
    // ---------------------------------------------------------

    // Taylor Swift
    songs.push_back(new Song(
        "Cruel Summer", "Taylor Swift",
        "Taylor Swift / Jack Antonoff / St. Vincent",
        "Taylor Swift / Jack Antonoff / St. Vincent",
        "Lover", 2019,
        "Taylor Swift - Cruel Summer.mp3.mp3"));

    songs.push_back(new Song(
        "Opalite", "Taylor Swift",
        "Not specified", "Not specified",
        "Not specified", 0,
        "Taylor Swift - Opalite (Official HD Audio).mp3.mp3"));

    songs.push_back(new Song(
        "Anti-Hero", "Taylor Swift",
        "Taylor Swift / Jack Antonoff",
        "Taylor Swift / Jack Antonoff",
        "Midnights", 2022,
        "Taylor Swift-Anti-Hero.mp3.mp3"));

    // Shreya Ghoshal
    songs.push_back(new Song(
        "Samjhawan", "Shreya Ghoshal",
        "Sharib-Toshi", "Amitabh Bhattacharya",
        "Humpty Sharma Ki Dulhania", 2014,
        "samjhawaan.mp3"));

    songs.push_back(new Song(
        "Saibo", "Shreya Ghoshal",
        "Sachin-Jigar", "Sameer",
        "Shor in the City", 2011,
        "saibo.mp3"));

    songs.push_back(new Song(
        "Pal", "Shreya Ghoshal",
        "Javed-Mohsin", "Kunaal Vermaa",
        "Jalebi", 2018,
        "pal.mp3"));

    // Lata Mangeshkar
    songs.push_back(new Song(
        "Ajeeb Dastan Hai Yeh", "Lata Mangeshkar",
        "Shankar-Jaikishan", "Shailendra",
        "Dil Apna Aur Preet Parai", 1960,
        "ajib daatan hai yeh.mp3"));

    songs.push_back(new Song(
        "Lag Ja Gale Phir Se", "Lata Mangeshkar",
        "Madan Mohan", "Raja Mehdi Ali Khan",
        "Woh Kaun Thi?", 1964,
        "lag jaa gale phir se.mp3"));

    songs.push_back(new Song(
        "Baahon Mein Chale Jao", "Lata Mangeshkar",
        "R. D. Burman", "Majrooh Sultanpuri",
        "Anamika", 1973,
        "baahon mai chale aao.mp3"));

    // Asha Bhosle
    songs.push_back(new Song(
        "Abhi Na Jao Chhod Kar", "Asha Bhosle",
        "Jaidev", "Sahir Ludhianvi",
        "Hum Dono", 1961,
        "Abhi na jao chod kar.mp3"));

    songs.push_back(new Song(
        "Chura Liya Hai Dil Ko Jo Tumne", "Asha Bhosle",
        "R. D. Burman", "Majrooh Sultanpuri",
        "Yaadon Ki Baaraat", 1973,
        "Chura Liya Hai.mp3"));

    songs.push_back(new Song(
        "Ye Raaten Ye Mausam", "Asha Bhosle",
        "Shankar-Jaikishan", "Hasrat Jaipuri",
        "Dilli Ka Thug", 1958,
        "yeh ratien yeh mausam nadi ka kinara.mp3"));

    // Ariana Grande
    songs.push_back(new Song(
        "We Can't Be Friends", "Ariana Grande",
        "Ariana Grande / Max Martin / Ilya Salmanzadeh", "Ariana Grande",
        "eternal sunshine", 2024,
        "010 Ariana Grande - we can_t be friends (wait for yout love).mp3"));

    songs.push_back(new Song(
        "Bloodline", "Ariana Grande",
        "Ariana Grande / Max Martin / Savan Kotecha / Ilya Salmanzadeh", "Ariana Grande / Victoria Monet",
        "thank u, next", 2019,
        "Ariana_Grande_-_bloodline_Official_Audio.mp3"));

    songs.push_back(new Song(
        "Supernatural", "Ariana Grande",
        "Ariana Grande / Max Martin / Ilya Salmanzadeh", "Ariana Grande",
        "eternal sunshine", 2024,
        "ariana-grande-supernatural.mp3"));

    // Arijit Singh
    songs.push_back(new Song(
        "Gehra Hua", "Arijit Singh",
        "Not specified", "Not specified",
        "Not specified", 0,
        "gehra hua.mp3"));

    songs.push_back(new Song(
        "Haareya", "Arijit Singh",
        "Not specified", "Not specified",
        "Not specified", 0,
        "haareya.mp3"));

    songs.push_back(new Song(
        "Darkhast", "Arijit Singh",
        "Mithoon", "Sayeed Quadri",
        "Shivaay", 2016,
        "darkhaast.mp3"));

    // ---------------------------------------------------------
    // USERS
    //
    // The favorites are deliberately arranged with some overlap
    // so the two-user Blend feature has common songs to find.
    // ---------------------------------------------------------
    users.push_back(new User(1, "SnehaOnBeat"));
    users.push_back(new User(2, "SrushtiOnBeat"));
    users.push_back(new User(3, "AanyaMelody"));

    // Sneha
    users[0]->addFavorite(songs[0]);   // Cruel Summer
    users[0]->addFavorite(songs[3]);   // Samjhawan
    users[0]->addFavorite(songs[6]);   // Ajeeb Dastan Hai Yeh
    users[0]->addFavorite(songs[12]);  // We Can't Be Friends
    users[0]->addFavorite(songs[15]);  // Gehra Hua

    // Srushti
    users[1]->addFavorite(songs[0]);   // Cruel Summer
    users[1]->addFavorite(songs[4]);   // Saibo
    users[1]->addFavorite(songs[6]);   // Ajeeb Dastan Hai Yeh
    users[1]->addFavorite(songs[13]);  // Bloodline
    users[1]->addFavorite(songs[17]);  // Darkhast

    // Aanya
    users[2]->addFavorite(songs[2]);   // Anti-Hero
    users[2]->addFavorite(songs[8]);   // Baahon Mein Chale Jao
    users[2]->addFavorite(songs[11]);  // Ye Raaten Ye Mausam
    users[2]->addFavorite(songs[14]);  // Supernatural
    users[2]->addFavorite(songs[17]);  // Darkhast

    // ---------------------------------------------------------
    // LINK EACH SONG TO ITS ARTIST
    // ---------------------------------------------------------
    for (Song* song : songs)
    {
        if (song == nullptr)
            continue;

        for (Artist* artist : artists)
        {
            if (artist != nullptr &&
                song->getArtist() == artist->getName())
            {
                artist->addSong(song);
                break;
            }
        }
    }
}

int main()
{
    vector<Song*> songs;
    vector<Artist*> artists;
    vector<User*> users;
    vector<Playlist*> playlists;

    loadData(songs, artists, users);

    UI app(songs, artists, users, playlists);
    app.run();

    // Clean up objects created with new.
    for (Song* song : songs)
        delete song;

    for (Artist* artist : artists)
        delete artist;

    for (User* user : users)
        delete user;

    for (Playlist* playlist : playlists)
        delete playlist;

    return 0;
}
