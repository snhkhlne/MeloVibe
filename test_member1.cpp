#include <iostream>
#include "Song.h"
#include "Artist.h"
#include "User.h"

using namespace std;

int main() {

    // =========================
    // ARIJIT SINGH
    // =========================

    Song darkhaast(
        "Darkhaast", "Arijit Singh",
        "", "", "", 2016,
        "songs/ArijitSingh/Darkhaast.mp3"
    );

    Song Haareya(
        "Haareya", "Arijit Singh",
        "", "", "", 2017,
        "songs/ArijitSingh/Haareya.mp3"
    );

    Song gehraHua(
        "Gehra Hua", "Arijit Singh",
        "", "", "", 2025,
        "songs/ArijitSingh/GehraHua.mp3"
    );

    Artist arijit(
        "Arijit Singh", "India", "Bollywood, Pop"
    );

    arijit.addSong(&darkhaast);
    arijit.addSong(&Haareya);
    arijit.addSong(&gehraHua);


    // =========================
    // ASHA BHOSLE
    // =========================

    Song yehRaaten(
        "Yeh Raaten Yeh Mausam", "Asha Bhosle",
        "", "", "", 1958,
        "songs/AshaBhosle/YehRaatenYehMausam.mp3"
    );

    Song abhiNaJao(
        "Abhi Na Jao Chhod Kar", "Asha Bhosle",
        "", "", "", 1961,
        "songs/AshaBhosle/AbhiNaJaoChhodKar.mp3"
    );

    Song churaLiya(
        "Chura Liya Hai Tumne Jo Dil Ko", "Asha Bhosle",
        "", "", "", 1973,
        "songs/AshaBhosle/ChuraLiyaHaiTumneJoDilKo.mp3"
    );

    Artist asha(
        "Asha Bhosle", "India", "Indian Film Music"
    );

    asha.addSong(&yehRaaten);
    asha.addSong(&abhiNaJao);
    asha.addSong(&churaLiya);


    // =========================
    // LATA MANGESHKAR
    // =========================

    Song ajibDastan(
        "Ajib Dastan Hai Yeh", "Lata Mangeshkar",
        "", "", "", 1960,
        "songs/LataMangeshkar/AjibDastanHaiYeh.mp3"
    );

    Song bahonMein(
        "Bahon Mein Chale Aao", "Lata Mangeshkar",
        "", "", "", 1973,
        "songs/LataMangeshkar/BahonMeinChaleAao.mp3"
    );

    Song lagJaGale(
        "Lag Ja Gale", "Lata Mangeshkar",
        "", "", "", 1964,
        "songs/LataMangeshkar/LagJaGale.mp3"
    );

    Artist lata(
        "Lata Mangeshkar", "India", "Indian Film Music"
    );

    lata.addSong(&ajibDastan);
    lata.addSong(&bahonMein);
    lata.addSong(&lagJaGale);


    // =========================
    // SHREYA GHOSHAL
    // =========================

    Song pal(
        "Pal", "Shreya Ghoshal",
        "", "", "", 2018,
        "songs/ShreyaGhoshal/Pal.mp3"
    );

    Song saibo(
        "Saibo", "Shreya Ghoshal",
        "", "", "", 2011,
        "songs/ShreyaGhoshal/Saibo.mp3"
    );

    Song samjhawan(
        "Samjhawan", "Shreya Ghoshal",
        "", "", "", 2014,
        "songs/ShreyaGhoshal/Samjhawan.mp3"
    );

    Artist shreya(
        "Shreya Ghoshal", "India", "Indian Pop, Film Music"
    );

    shreya.addSong(&pal);
    shreya.addSong(&saibo);
    shreya.addSong(&samjhawan);


    // =========================
    // ARIANA GRANDE
    // =========================

    Song bloodline(
        "Bloodline", "Ariana Grande",
        "", "", "", 2019,
        "songs/ArianaGrande/Bloodline.mp3"
    );

    Song supernatural(
        "Supernatural", "Ariana Grande",
        "", "", "", 2024,
        "songs/ArianaGrande/Supernatural.mp3"
    );

    Song weCantBeFriends(
        "We Can't Be Friends", "Ariana Grande",
        "", "", "", 2024,
        "songs/ArianaGrande/WeCantBeFriends.mp3"
    );

    Artist ariana(
        "Ariana Grande", "United States", "Pop"
    );

    ariana.addSong(&bloodline);
    ariana.addSong(&supernatural);
    ariana.addSong(&weCantBeFriends);


    // =========================
    // TAYLOR SWIFT
    // =========================

    Song cruelSummer(
        "Cruel Summer", "Taylor Swift",
        "", "", "", 2019,
        "songs/TaylorSwift/CruelSummer.mp3"
    );

    Song opalite(
        "Opalite", "Taylor Swift",
        "", "", "", 2025,
        "songs/TaylorSwift/Opalite.mp3"
    );

    Song antiHero(
        "Anti-Hero", "Taylor Swift",
        "", "", "", 2022,
        "songs/TaylorSwift/AntiHero.mp3"
    );

    Artist taylor(
        "Taylor Swift", "United States", "Pop"
    );

    taylor.addSong(&cruelSummer);
    taylor.addSong(&opalite);
    taylor.addSong(&antiHero);


    // =========================
    // DISPLAY ALL ARTISTS
    // =========================

    cout << "\n===== ARIJIT SINGH =====\n";
    arijit.displayArtist();
    arijit.displaySongs();

    cout << "\n===== ASHA BHOSLE =====\n";
    asha.displayArtist();
    asha.displaySongs();

    cout << "\n===== LATA MANGESHKAR =====\n";
    lata.displayArtist();
    lata.displaySongs();

    cout << "\n===== SHREYA GHOSHAL =====\n";
    shreya.displayArtist();
    shreya.displaySongs();

    cout << "\n===== ARIANA GRANDE =====\n";
    ariana.displayArtist();
    ariana.displaySongs();

    cout << "\n===== TAYLOR SWIFT =====\n";
    taylor.displayArtist();
    taylor.displaySongs();


    // =========================
    // USER FAVORITES
    // =========================

    User user1(101, "Swara");

   user1.addFavorite(&darkhaast);
user1.addFavorite(&Haareya);
    user1.addFavorite(&samjhawan);
    user1.addFavorite(&saibo);
    user1.addFavorite(&supernatural);
    user1.addFavorite(&cruelSummer);

    cout << "\n===== USER FAVORITES =====\n";
    user1.displayFavorites();

    return 0;
}