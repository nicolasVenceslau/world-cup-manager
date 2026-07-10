#include "manager.h"

void initializeDefaultData()
{

    FILE *fUser = fopen("../database/users.txt", "r");
    int hasAdmin = 0;

    if (fUser != NULL)
    {
        char line[250];
        while (fgets(line, sizeof(line), fUser))
        {
            if (strncmp(line, "admin,", 6) == 0)
            {
                hasAdmin = 1;
                break;
            }
        }
        fclose(fUser);
    }

    if (hasAdmin == 0)
    {
        fUser = fopen("../database/users.txt", "a");
        if (fUser)
        {
            fprintf(fUser, "admin,admin123,1,0,Administrator,System\n");
            fclose(fUser);
        }
    }

    FILE *fTeams = fopen("../database/teams.txt", "r");
    if (fTeams != NULL)
    {
        fclose(fTeams);
        return;
    }

    fTeams = fopen("../database/teams.txt", "w");
    fprintf(fTeams,
            "1,Argentina,91,0,0,0,3\n"
            "2,France,91,0,0,0,2\n"
            "3,Spain,89,0,0,0,1\n"
            "4,England,85,0,0,0,1\n"
            "5,Portugal,88,0,0,0,0\n"
            "6,Brazil,89,0,0,0,5\n"
            "7,Morocco,82,0,0,0,0\n"
            "8,Netherlands,85,0,0,0,0\n"
            "9,Germany,85,0,0,0,4\n"
            "10,Belgium,85,0,0,0,0\n"
            "11,Croatia,83,0,0,0,0\n"
            "12,Italy,77,0,0,0,4\n" 
            "13,Mexico,79,0,0,0,0\n"
            "14,Colombia,80,0,0,0,0\n"
            "15,USA,79,0,0,0,0\n"
            "16,Senegal,79,0,0,0,0\n"
            "17,Japan,79,0,0,0,0\n"
            "18,Uruguay,78,0,0,0,2\n"
            "19,Switzerland,80,0,0,0,0\n"
            "20,Denmark,80,0,0,0,0\n"
            "21,South Korea,77,0,0,0,0\n"
            "22,Australia,75,0,0,0,0\n"
            "23,Iran,75,0,0,0,0\n"
            "24,Austria,80,0,0,0,0\n"
            "25,Nigeria,78,0,0,0,0\n"
            "26,Turkey,78,0,0,0,0\n"
            "27,Norway,78,0,0,0,0\n"
            "28,Ecuador,78,0,0,0,0\n"
            "29,Egypt,76,0,0,0,0\n"
            "30,Ivory Coast,77,0,0,0,0\n"
            "31,Algeria,76,0,0,0,0\n"
            "32,Canada,76,0,0,0,0\n");
    fclose(fTeams);

  FILE *fPlayers = fopen("../database/players.txt", "w");

    
    fprintf(fPlayers,
            "1,0,1,Lionel Messi,38,ATA,86,0,0,0,0,0,0\n"
            "2,0,1,Lautaro Martínez,28,ATA,88,0,0,0,0,0,0\n"
            "3,0,1,Emiliano Martínez,33,GK,87,0,0,0,0,0,0\n"
            "4,0,1,Alexis Mac Allister,27,MED,86,0,0,0,0,0,0\n"
            "5,0,1,Enzo Fernández,25,MED,84,0,0,0,0,0,0\n"
            "6,0,1,Julián Álvarez,26,ATA,86,0,0,0,0,0,0\n"
            "7,0,1,Cristian Romero,28,DEF,87,0,0,0,0,0,0\n"
            "8,0,1,Rodrigo de Paul,32,MED,84,0,0,0,0,0,0\n"
            "9,0,1,Lisandro Martínez,28,DEF,84,0,0,0,0,0,0\n"
            "10,0,1,Alejandro Garnacho,21,ATA,82,0,0,0,0,0,0\n"
            "11,0,1,Nahuel Molina,28,DEF,82,0,0,0,0,0,0\n"
            "12,0,1,Exequiel Palacios,27,MED,83,0,0,0,0,0,0\n"
            "13,0,1,Nicolás González,28,ATA,81,0,0,0,0,0,0\n"
            "14,0,1,Nicolás Tagliafico,33,DEF,80,0,0,0,0,0,0\n"
            "15,0,1,Giovani Lo Celso,30,MED,81,0,0,0,0,0,0\n"
            "16,0,1,Facundo Buonanotte,21,MED,80,0,0,0,0,0,0\n"
            "17,0,1,Lucas Beltrán,25,ATA,80,0,0,0,0,0,0\n"
            "18,0,1,Valentin Carboni,21,MED,79,0,0,0,0,0,0\n"
            "19,0,1,Nehuén Pérez,25,DEF,79,0,0,0,0,0,0\n"
            "20,0,1,Walter Benítez,33,GK,79,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "21,0,2,Kylian Mbappé,27,ATA,91,0,0,0,0,0,0\n"
            "22,0,2,William Saliba,25,DEF,88,0,0,0,0,0,0\n"
            "23,0,2,Antoine Griezmann,35,MED,85,0,0,0,0,0,0\n"
            "24,0,2,Aurélien Tchouaméni,26,MED,86,0,0,0,0,0,0\n"
            "25,0,2,Eduardo Camavinga,23,MED,85,0,0,0,0,0,0\n"
            "26,0,2,Mike Maignan,30,GK,87,0,0,0,0,0,0\n"
            "27,0,2,Ousmane Dembélé,29,ATA,85,0,0,0,0,0,0\n"
            "28,0,2,Theo Hernández,28,DEF,86,0,0,0,0,0,0\n"
            "29,0,2,Dayot Upamecano,27,DEF,84,0,0,0,0,0,0\n"
            "30,0,2,Jules Koundé,27,DEF,85,0,0,0,0,0,0\n"
            "31,0,2,Warren Zaïre-Emery,20,MED,82,0,0,0,0,0,0\n"
            "32,0,2,Bradley Barcola,23,ATA,83,0,0,0,0,0,0\n"
            "33,0,2,Ibrahima Konaté,27,DEF,84,0,0,0,0,0,0\n"
            "34,0,2,Marcus Thuram,28,ATA,84,0,0,0,0,0,0\n"
            "35,0,2,Randal Kolo Muani,27,ATA,82,0,0,0,0,0,0\n"
            "36,0,2,Adrien Rabiot,31,MED,83,0,0,0,0,0,0\n"
            "37,0,2,Kingsley Coman,30,ATA,83,0,0,0,0,0,0\n"
            "38,0,2,Michael Olise,24,ATA,83,0,0,0,0,0,0\n"
            "39,0,2,Lucas Hernández,30,DEF,82,0,0,0,0,0,0\n"
            "40,0,2,Brice Samba,32,GK,81,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "41,0,3,Rodri,29,MED,91,0,0,0,0,0,0\n"
            "42,0,3,Lamine Yamal,18,ATA,86,0,0,0,0,0,0\n"
            "43,0,3,Pedri,23,MED,86,0,0,0,0,0,0\n"
            "44,0,3,Nico Williams,23,ATA,85,0,0,0,0,0,0\n"
            "45,0,3,Dani Olmo,28,MED,85,0,0,0,0,0,0\n"
            "46,0,3,Gavi,21,MED,84,0,0,0,0,0,0\n"
            "47,0,3,Unai Simon,29,GK,86,0,0,0,0,0,0\n"
            "48,0,3,Dani Carvajal,34,DEF,85,0,0,0,0,0,0\n"
            "49,0,3,Robin Le Normand,29,DEF,84,0,0,0,0,0,0\n"
            "50,0,3,Alex Grimaldo,30,DEF,85,0,0,0,0,0,0\n"
            "51,0,3,Pau Torres,29,DEF,84,0,0,0,0,0,0\n"
            "52,0,3,Fabian Ruiz,30,MED,85,0,0,0,0,0,0\n"
            "53,0,3,Martin Zubimendi,27,MED,84,0,0,0,0,0,0\n"
            "54,0,3,Mikel Oyarzabal,29,ATA,83,0,0,0,0,0,0\n"
            "55,0,3,Alvaro Morata,33,ATA,82,0,0,0,0,0,0\n"
            "56,0,3,Pau Cubarsi,19,DEF,82,0,0,0,0,0,0\n"
            "57,0,3,Marc Cucurella,27,DEF,82,0,0,0,0,0,0\n"
            "58,0,3,David Raya,30,GK,84,0,0,0,0,0,0\n"
            "59,0,3,Alex Baena,24,MED,82,0,0,0,0,0,0\n"
            "60,0,3,Pedro Porro,26,DEF,83,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "61,0,4,Jude Bellingham,22,MED,90,0,0,0,0,0,0\n"
            "62,0,4,Harry Kane,32,ATA,90,0,0,0,0,0,0\n"
            "63,0,4,Bukayo Saka,24,ATA,88,0,0,0,0,0,0\n"
            "64,0,4,Phil Foden,26,MED,88,0,0,0,0,0,0\n"
            "65,0,4,Declan Rice,27,MED,87,0,0,0,0,0,0\n"
            "66,0,4,Cole Palmer,24,MED,86,0,0,0,0,0,0\n"
            "67,0,4,Trent Alexander-Arnold,27,DEF,86,0,0,0,0,0,0\n"
            "68,0,4,John Stones,32,DEF,85,0,0,0,0,0,0\n"
            "69,0,4,Jordan Pickford,32,GK,84,0,0,0,0,0,0\n"
            "70,0,4,Kyle Walker,36,DEF,83,0,0,0,0,0,0\n"
            "71,0,4,Ollie Watkins,30,ATA,84,0,0,0,0,0,0\n"
            "72,0,4,Anthony Gordon,25,ATA,83,0,0,0,0,0,0\n"
            "73,0,4,Jack Grealish,30,ATA,83,0,0,0,0,0,0\n"
            "74,0,4,Kobbie Mainoo,21,MED,82,0,0,0,0,0,0\n"
            "75,0,4,Marc Guehi,25,DEF,83,0,0,0,0,0,0\n"
            "76,0,4,Levi Colwill,23,DEF,82,0,0,0,0,0,0\n"
            "77,0,4,Rico Lewis,21,DEF,81,0,0,0,0,0,0\n"
            "78,0,4,Ezri Konsa,28,DEF,82,0,0,0,0,0,0\n"
            "79,0,4,Conor Gallagher,26,MED,81,0,0,0,0,0,0\n"
            "80,0,4,Aaron Ramsdale,28,GK,81,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "81,0,5,Cristiano Ronaldo,41,ATA,82,0,0,0,0,0,0\n"
            "82,0,5,Vitinha,26,MED,86,0,0,0,0,0,0\n"
            "83,0,5,Bruno Fernandes,31,MED,88,0,0,0,0,0,0\n"
            "84,0,5,Rúben Dias,29,DEF,88,0,0,0,0,0,0\n"
            "85,0,5,Bernardo Silva,31,MED,87,0,0,0,0,0,0\n"
            "86,0,5,Rafael Leão,27,ATA,86,0,0,0,0,0,0\n"
            "87,0,5,Diogo Costa,26,GK,86,0,0,0,0,0,0\n"
            "88,0,5,Nuno Mendes,23,DEF,85,0,0,0,0,0,0\n"
            "89,0,5,João Neves,21,MED,83,0,0,0,0,0,0\n"
            "90,0,5,João Cancelo,32,DEF,83,0,0,0,0,0,0\n"
            "91,0,5,Diogo Dalot,27,DEF,84,0,0,0,0,0,0\n"
            "92,0,5,Gonçalo Inácio,24,DEF,83,0,0,0,0,0,0\n"
            "93,0,5,Pedro Neto,26,ATA,82,0,0,0,0,0,0\n"
            "94,0,5,Francisco Conceição,23,ATA,82,0,0,0,0,0,0\n"
            "95,0,5,Gonçalo Ramos,24,ATA,81,0,0,0,0,0,0\n"
            "96,0,5,João Félix,26,ATA,81,0,0,0,0,0,0\n"
            "97,0,5,Tomás Araújo,24,DEF,80,0,0,0,0,0,0\n"
            "98,0,5,Francisco Trincão,26,ATA,80,0,0,0,0,0,0\n"
            "99,0,5,Matheus Nunes,27,MED,80,0,0,0,0,0,0\n"
            "100,0,5,Renato Veiga,22,DEF,79,0,0,0,0,0,0\n");

   
    fprintf(fPlayers,
            "101,0,6,Vinicius Junior,25,ATA,90,0,0,0,0,0,0\n"
            "102,0,6,Alisson,33,GK,89,0,0,0,0,0,0\n"
            "103,0,6,Ederson,32,GK,88,0,0,0,0,0,0\n"
            "104,0,6,Bruno Guimaraes,28,MED,86,0,0,0,0,0,0\n"
            "105,0,6,Gabriel Magalhaes,28,DEF,86,0,0,0,0,0,0\n"
            "106,0,6,Marquinhos,32,DEF,85,0,0,0,0,0,0\n"
            "107,0,6,Raphinha,29,ATA,85,0,0,0,0,0,0\n"
            "108,0,6,Bremer,29,DEF,85,0,0,0,0,0,0\n"
            "109,0,6,Neymar,34,ATA,84,0,0,0,0,0,0\n"
            "110,0,6,Lucas Paqueta,28,MED,83,0,0,0,0,0,0\n"
            "111,0,6,Casemiro,34,MED,82,0,0,0,0,0,0\n"
            "112,0,6,Gabriel Martinelli,25,ATA,83,0,0,0,0,0,0\n"
            "113,0,6,Endrick,19,ATA,81,0,0,0,0,0,0\n"
            "114,0,6,Luiz Henrique,25,ATA,82,0,0,0,0,0,0\n"
            "115,0,6,Rayan,19,ATA,80,0,0,0,0,0,0\n"
            "116,0,6,Igor Thiago,24,ATA,81,0,0,0,0,0,0\n"
            "117,0,6,Matheus Cunha,27,ATA,82,0,0,0,0,0,0\n"
            "118,0,6,Danilo Santos,25,MED,81,0,0,0,0,0,0\n"
            "119,0,6,Roger Ibanez,27,DEF,81,0,0,0,0,0,0\n"
            "120,0,6,Leo Pereira,30,DEF,81,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "121,0,7,Brahim Diaz,26,ATA,84,0,0,0,0,0,0\n"
            "122,0,7,Achraf Hakimi,27,DEF,85,0,0,0,0,0,0\n"
            "123,0,7,Yassine Bounou,35,GK,84,0,0,0,0,0,0\n"
            "124,0,7,Noussair Mazraoui,28,DEF,83,0,0,0,0,0,0\n"
            "125,0,7,Nayef Aguerd,30,DEF,82,0,0,0,0,0,0\n"
            "126,0,7,Sofyan Amrabat,29,MED,81,0,0,0,0,0,0\n"
            "127,0,7,Azzedine Ounahi,26,MED,81,0,0,0,0,0,0\n"
            "128,0,7,Bilal El Khannouss,22,MED,80,0,0,0,0,0,0\n"
            "129,0,7,Ayoub El Kaabi,32,ATA,81,0,0,0,0,0,0\n"
            "130,0,7,Soufiane Rahimi,30,ATA,80,0,0,0,0,0,0\n"
            "131,0,7,Chadi Riad,22,DEF,80,0,0,0,0,0,0\n"
            "132,0,7,Ayyoub Bouaddi,18,MED,78,0,0,0,0,0,0\n"
            "133,0,7,Ismael Saibari,25,MED,80,0,0,0,0,0,0\n"
            "134,0,7,Abde Ezzalzouli,24,ATA,80,0,0,0,0,0,0\n"
            "135,0,7,Issa Diop,29,DEF,79,0,0,0,0,0,0\n"
            "136,0,7,Neil El Aynaoui,24,MED,78,0,0,0,0,0,0\n"
            "137,0,7,Anass Salah-Eddine,24,DEF,78,0,0,0,0,0,0\n"
            "138,0,7,Zakaria El Ouahdi,24,DEF,78,0,0,0,0,0,0\n"
            "139,0,7,Munir El Kajoui,37,GK,77,0,0,0,0,0,0\n"
            "140,0,7,Chemsdine Talbi,21,ATA,77,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "141,0,8,Virgil van Dijk,34,DEF,89,0,0,0,0,0,0\n"
            "142,0,8,Frenkie de Jong,29,MED,86,0,0,0,0,0,0\n"
            "143,0,8,Xavi Simons,23,MED,85,0,0,0,0,0,0\n"
            "144,0,8,Cody Gakpo,27,ATA,85,0,0,0,0,0,0\n"
            "145,0,8,Jeremie Frimpong,25,DEF,85,0,0,0,0,0,0\n"
            "146,0,8,Matthijs de Ligt,26,DEF,84,0,0,0,0,0,0\n"
            "147,0,8,Nathan Ake,31,DEF,84,0,0,0,0,0,0\n"
            "148,0,8,Micky van de Ven,25,DEF,84,0,0,0,0,0,0\n"
            "149,0,8,Bart Verbruggen,23,GK,82,0,0,0,0,0,0\n"
            "150,0,8,Tijjani Reijnders,27,MED,83,0,0,0,0,0,0\n"
            "151,0,8,Donyell Malen,27,ATA,83,0,0,0,0,0,0\n"
            "152,0,8,Ryan Gravenberch,24,MED,84,0,0,0,0,0,0\n"
            "153,0,8,Joshua Zirkzee,25,ATA,82,0,0,0,0,0,0\n"
            "154,0,8,Lutsharel Geertruida,25,DEF,82,0,0,0,0,0,0\n"
            "155,0,8,Teun Koopmeiners,28,MED,83,0,0,0,0,0,0\n"
            "156,0,8,Brian Brobbey,24,ATA,81,0,0,0,0,0,0\n"
            "157,0,8,Joey Veerman,27,MED,81,0,0,0,0,0,0\n"
            "158,0,8,Stefan de Vrij,34,DEF,81,0,0,0,0,0,0\n"
            "159,0,8,Mark Flekken,33,GK,80,0,0,0,0,0,0\n"
            "160,0,8,Quinten Timber,25,MED,81,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "161,0,9,Florian Wirtz,23,MED,88,0,0,0,0,0,0\n"
            "162,0,9,Jamal Musiala,23,MED,88,0,0,0,0,0,0\n"
            "163,0,9,Kai Havertz,27,ATA,86,0,0,0,0,0,0\n"
            "164,0,9,Antonio Rudiger,33,DEF,87,0,0,0,0,0,0\n"
            "165,0,9,Joshua Kimmich,31,MED,86,0,0,0,0,0,0\n"
            "166,0,9,Leroy Sane,30,ATA,85,0,0,0,0,0,0\n"
            "167,0,9,Marc-Andre ter Stegen,34,GK,88,0,0,0,0,0,0\n"
            "168,0,9,Jonathan Tah,30,DEF,84,0,0,0,0,0,0\n"
            "169,0,9,Nico Schlotterbeck,26,DEF,84,0,0,0,0,0,0\n"
            "170,0,9,David Raum,28,DEF,83,0,0,0,0,0,0\n"
            "171,0,9,Aleksandar Pavlovic,22,MED,83,0,0,0,0,0,0\n"
            "172,0,9,Maximilian Mittelstadt,29,DEF,82,0,0,0,0,0,0\n"
            "173,0,9,Pascal Gross,35,MED,81,0,0,0,0,0,0\n"
            "174,0,9,Niclas Fullkrug,33,ATA,82,0,0,0,0,0,0\n"
            "175,0,9,Deniz Undav,29,ATA,82,0,0,0,0,0,0\n"
            "176,0,9,Maximilian Beier,23,ATA,81,0,0,0,0,0,0\n"
            "177,0,9,Chris Fuhrich,28,ATA,81,0,0,0,0,0,0\n"
            "178,0,9,Robert Andrich,31,MED,82,0,0,0,0,0,0\n"
            "179,0,9,Alexander Nubel,29,GK,81,0,0,0,0,0,0\n"
            "180,0,9,Waldemar Anton,29,DEF,81,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "181,0,10,Thibaut Courtois,34,GK,89,0,0,0,0,0,0\n"
            "182,0,10,Kevin De Bruyne,34,MED,89,0,0,0,0,0,0\n"
            "183,0,10,Romelu Lukaku,33,ATA,83,0,0,0,0,0,0\n"
            "184,0,10,Jeremy Doku,24,ATA,83,0,0,0,0,0,0\n"
            "185,0,10,Leandro Trossard,31,ATA,83,0,0,0,0,0,0\n"
            "186,0,10,Amadou Onana,24,MED,83,0,0,0,0,0,0\n"
            "187,0,10,Youri Tielemans,29,MED,82,0,0,0,0,0,0\n"
            "188,0,10,Charles De Ketelaere,25,ATA,82,0,0,0,0,0,0\n"
            "189,0,10,Arthur Theate,26,DEF,81,0,0,0,0,0,0\n"
            "190,0,10,Zeno Debast,22,DEF,80,0,0,0,0,0,0\n"
            "191,0,10,Maxim De Cuyper,25,DEF,79,0,0,0,0,0,0\n"
            "192,0,10,Koni De Winter,24,DEF,79,0,0,0,0,0,0\n"
            "193,0,10,Timothy Castagne,30,DEF,80,0,0,0,0,0,0\n"
            "194,0,10,Dodi Lukebakio,28,ATA,79,0,0,0,0,0,0\n"
            "195,0,10,Alexis Saelemaekers,26,MED,79,0,0,0,0,0,0\n"
            "196,0,10,Hans Vanaken,33,MED,78,0,0,0,0,0,0\n"
            "197,0,10,Axel Witsel,37,MED,77,0,0,0,0,0,0\n"
            "198,0,10,Senne Lammens,23,GK,77,0,0,0,0,0,0\n"
            "199,0,10,Mike Penders,20,GK,76,0,0,0,0,0,0\n"
            "200,0,10,Diego Moreira,21,ATA,76,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "201,0,11,Josko Gvardiol,24,DEF,86,0,0,0,0,0,0\n"
            "202,0,11,Luka Modric,40,MED,80,0,0,0,0,0,0\n"
            "203,0,11,Mateo Kovacic,32,MED,83,0,0,0,0,0,0\n"
            "204,0,11,Marcelo Brozovic,33,MED,80,0,0,0,0,0,0\n"
            "205,0,11,Dominik Livakovic,31,GK,82,0,0,0,0,0,0\n"
            "206,0,11,Mario Pasalic,31,MED,81,0,0,0,0,0,0\n"
            "207,0,11,Andrej Kramaric,34,ATA,80,0,0,0,0,0,0\n"
            "208,0,11,Lovro Majer,28,MED,81,0,0,0,0,0,0\n"
            "209,0,11,Josip Stanisic,26,DEF,81,0,0,0,0,0,0\n"
            "210,0,11,Josip Sutalo,26,DEF,80,0,0,0,0,0,0\n"
            "211,0,11,Martin Baturina,23,MED,81,0,0,0,0,0,0\n"
            "212,0,11,Luka Sucic,23,MED,80,0,0,0,0,0,0\n"
            "213,0,11,Ivan Perisic,37,ATA,76,0,0,0,0,0,0\n"
            "214,0,11,Ante Budimir,34,ATA,78,0,0,0,0,0,0\n"
            "215,0,11,Josip Brekalo,27,ATA,77,0,0,0,0,0,0\n"
            "216,0,11,Borna Sosa,28,DEF,78,0,0,0,0,0,0\n"
            "217,0,11,Marin Pongracic,28,DEF,78,0,0,0,0,0,0\n"
            "218,0,11,Nikola Vlasic,28,MED,78,0,0,0,0,0,0\n"
            "219,0,11,Nediljko Labrovic,26,GK,76,0,0,0,0,0,0\n"
            "220,0,11,Igor Matanovic,23,ATA,77,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "221,0,12,Alessandro Bastoni,27,DEF,87,0,0,0,0,0,0\n"
            "222,0,12,Nicolo Barella,29,MED,87,0,0,0,0,0,0\n"
            "223,0,12,Gianluigi Donnarumma,27,GK,88,0,0,0,0,0,0\n"
            "224,0,12,Federico Dimarco,28,DEF,85,0,0,0,0,0,0\n"
            "225,0,12,Federico Chiesa,28,ATA,83,0,0,0,0,0,0\n"
            "226,0,12,Guglielmo Vicario,29,GK,84,0,0,0,0,0,0\n"
            "227,0,12,Giorgio Scalvini,22,DEF,83,0,0,0,0,0,0\n"
            "228,0,12,Riccardo Calafiori,24,DEF,83,0,0,0,0,0,0\n"
            "229,0,12,Davide Frattesi,26,MED,83,0,0,0,0,0,0\n"
            "230,0,12,Gianluca Scamacca,27,ATA,82,0,0,0,0,0,0\n"
            "231,0,12,Lorenzo Pellegrini,29,MED,82,0,0,0,0,0,0\n"
            "232,0,12,Mateo Retegui,27,ATA,81,0,0,0,0,0,0\n"
            "233,0,12,Destiny Udogie,23,DEF,83,0,0,0,0,0,0\n"
            "234,0,12,Manuel Locatelli,28,MED,81,0,0,0,0,0,0\n"
            "235,0,12,Giacomo Raspadori,26,ATA,80,0,0,0,0,0,0\n"
            "236,0,12,Moise Kean,26,ATA,80,0,0,0,0,0,0\n"
            "237,0,12,Samuele Ricci,24,MED,81,0,0,0,0,0,0\n"
            "238,0,12,Andrea Cambiaso,26,DEF,81,0,0,0,0,0,0\n"
            "239,0,12,Raoul Bellanova,26,DEF,80,0,0,0,0,0,0\n"
            "240,0,12,Alex Meret,29,GK,80,0,0,0,0,0,0\n");

   
    fprintf(fPlayers,
            "241,0,13,Santiago Gimenez,25,ATA,81,0,0,0,0,0,0\n"
            "242,0,13,Edson Alvarez,28,MED,81,0,0,0,0,0,0\n"
            "243,0,13,Hirving Lozano,30,ATA,79,0,0,0,0,0,0\n"
            "244,0,13,Luis Chavez,30,MED,78,0,0,0,0,0,0\n"
            "245,0,13,Johan Vasquez,27,DEF,78,0,0,0,0,0,0\n"
            "246,0,13,Luis Malagon,29,GK,78,0,0,0,0,0,0\n"
            "247,0,13,Cesar Montes,29,DEF,77,0,0,0,0,0,0\n"
            "248,0,13,Orbelin Pineda,30,MED,77,0,0,0,0,0,0\n"
            "249,0,13,Julian Quinones,29,ATA,77,0,0,0,0,0,0\n"
            "250,0,13,Jorge Sanchez,28,DEF,76,0,0,0,0,0,0\n"
            "251,0,13,Gerardo Arteaga,27,DEF,76,0,0,0,0,0,0\n"
            "252,0,13,Carlos Rodriguez,29,MED,76,0,0,0,0,0,0\n"
            "253,0,13,Uriel Antuna,28,ATA,76,0,0,0,0,0,0\n"
            "254,0,13,Erick Sanchez,26,MED,76,0,0,0,0,0,0\n"
            "255,0,13,Henry Martin,33,ATA,75,0,0,0,0,0,0\n"
            "256,0,13,Cesar Huerta,25,ATA,75,0,0,0,0,0,0\n"
            "257,0,13,Israel Reyes,26,DEF,75,0,0,0,0,0,0\n"
            "258,0,13,Jesus Angulo,28,DEF,75,0,0,0,0,0,0\n"
            "259,0,13,Julio Gonzalez,35,GK,74,0,0,0,0,0,0\n"
            "260,0,13,Marcel Ruiz,25,MED,75,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "261,0,14,Luis Diaz,29,ATA,84,0,0,0,0,0,0\n"
            "262,0,14,Daniel Munoz,30,DEF,80,0,0,0,0,0,0\n"
            "263,0,14,Jhon Duran,22,ATA,82,0,0,0,0,0,0\n"
            "264,0,14,Jefferson Lerma,31,MED,80,0,0,0,0,0,0\n"
            "265,0,14,James Rodriguez,34,MED,80,0,0,0,0,0,0\n"
            "266,0,14,Jhon Arias,28,MED,80,0,0,0,0,0,0\n"
            "267,0,14,Davinson Sanchez,30,DEF,80,0,0,0,0,0,0\n"
            "268,0,14,Richard Rios,26,MED,79,0,0,0,0,0,0\n"
            "269,0,14,Carlos Cuesta,27,DEF,78,0,0,0,0,0,0\n"
            "270,0,14,Jhon Lucumi,27,DEF,79,0,0,0,0,0,0\n"
            "271,0,14,Camilo Vargas,37,GK,78,0,0,0,0,0,0\n"
            "272,0,14,Rafael Borre,30,ATA,77,0,0,0,0,0,0\n"
            "273,0,14,Mateus Uribe,35,MED,76,0,0,0,0,0,0\n"
            "274,0,14,Luis Sinisterra,27,ATA,78,0,0,0,0,0,0\n"
            "275,0,14,Juan Fernando Quintero,33,MED,76,0,0,0,0,0,0\n"
            "276,0,14,Yaser Asprilla,22,MED,78,0,0,0,0,0,0\n"
            "277,0,14,Johan Mojica,33,DEF,75,0,0,0,0,0,0\n"
            "278,0,14,Kevin Castano,25,MED,76,0,0,0,0,0,0\n"
            "279,0,14,Deiver Machado,32,DEF,75,0,0,0,0,0,0\n"
            "280,0,14,Devis Vasquez,28,GK,75,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "281,0,15,Christian Pulisic,27,ATA,83,0,0,0,0,0,0\n"
            "282,0,15,Folarin Balogun,24,ATA,79,0,0,0,0,0,0\n"
            "283,0,15,Weston McKennie,27,MED,79,0,0,0,0,0,0\n"
            "284,0,15,Antonee Robinson,28,DEF,80,0,0,0,0,0,0\n"
            "285,0,15,Tyler Adams,27,MED,78,0,0,0,0,0,0\n"
            "286,0,15,Matt Turner,31,GK,76,0,0,0,0,0,0\n"
            "287,0,15,Chris Richards,26,DEF,78,0,0,0,0,0,0\n"
            "288,0,15,Timothy Weah,26,ATA,78,0,0,0,0,0,0\n"
            "289,0,15,Yunus Musah,23,MED,78,0,0,0,0,0,0\n"
            "290,0,15,Giovanni Reyna,23,MED,77,0,0,0,0,0,0\n"
            "291,0,15,Sergino Dest,25,DEF,77,0,0,0,0,0,0\n"
            "292,0,15,Johnny Cardoso,23,MED,78,0,0,0,0,0,0\n"
            "293,0,15,Malik Tillman,24,MED,78,0,0,0,0,0,0\n"
            "294,0,15,Ricardo Pepi,23,ATA,77,0,0,0,0,0,0\n"
            "295,0,15,Mark McKenzie,27,DEF,75,0,0,0,0,0,0\n"
            "296,0,15,Joe Scally,23,DEF,76,0,0,0,0,0,0\n"
            "297,0,15,Brenden Aaronson,25,MED,75,0,0,0,0,0,0\n"
            "298,0,15,Haji Wright,28,ATA,76,0,0,0,0,0,0\n"
            "299,0,15,Patrick Schulte,25,GK,75,0,0,0,0,0,0\n"
            "300,0,15,Miles Robinson,29,DEF,74,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "301,0,16,Sadio Mane,34,ATA,82,0,0,0,0,0,0\n"
            "302,0,16,Kalidou Koulibaly,34,DEF,80,0,0,0,0,0,0\n"
            "303,0,16,Nicolas Jackson,24,ATA,81,0,0,0,0,0,0\n"
            "304,0,16,Pape Matar Sarr,23,MED,81,0,0,0,0,0,0\n"
            "305,0,16,Idrissa Gueye,36,MED,76,0,0,0,0,0,0\n"
            "306,0,16,Edouard Mendy,34,GK,80,0,0,0,0,0,0\n"
            "307,0,16,Ismaila Sarr,28,ATA,78,0,0,0,0,0,0\n"
            "308,0,16,Abdou Diallo,30,DEF,76,0,0,0,0,0,0\n"
            "309,0,16,Habib Diarra,22,MED,78,0,0,0,0,0,0\n"
            "310,0,16,Iliman Ndiaye,26,ATA,77,0,0,0,0,0,0\n"
            "311,0,16,Lamine Camara,22,MED,78,0,0,0,0,0,0\n"
            "312,0,16,Moussa Niakhate,30,DEF,77,0,0,0,0,0,0\n"
            "313,0,16,Formose Mendy,25,DEF,75,0,0,0,0,0,0\n"
            "314,0,16,Pathé Ciss,32,MED,75,0,0,0,0,0,0\n"
            "315,0,16,Nampalys Mendy,33,MED,74,0,0,0,0,0,0\n"
            "316,0,16,Boulaye Dia,29,ATA,77,0,0,0,0,0,0\n"
            "317,0,16,Aonana Seck,24,DEF,74,0,0,0,0,0,0\n"
            "318,0,16,Cherif Ndiaye,30,ATA,75,0,0,0,0,0,0\n"
            "319,0,16,Mory Diaw,32,GK,75,0,0,0,0,0,0\n"
            "320,0,16,Abdoulaye Seck,34,DEF,74,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "321,0,17,Takefusa Kubo,25,ATA,82,0,0,0,0,0,0\n"
            "322,0,17,Kaoru Mitoma,29,ATA,82,0,0,0,0,0,0\n"
            "323,0,17,Wataru Endo,33,MED,80,0,0,0,0,0,0\n"
            "324,0,17,Takumi Minamino,31,MED,79,0,0,0,0,0,0\n"
            "325,0,17,Hiroki Ito,27,DEF,80,0,0,0,0,0,0\n"
            "326,0,17,Takehiro Tomiyasu,27,DEF,80,0,0,0,0,0,0\n"
            "327,0,17,Ko Itakura,29,DEF,79,0,0,0,0,0,0\n"
            "328,0,17,Zion Suzuki,23,GK,75,0,0,0,0,0,0\n"
            "329,0,17,Ritsu Doan,28,ATA,79,0,0,0,0,0,0\n"
            "330,0,17,Hidemasa Morita,31,MED,80,0,0,0,0,0,0\n"
            "331,0,17,Reo Hatate,28,MED,78,0,0,0,0,0,0\n"
            "332,0,17,Ayase Ueda,27,ATA,77,0,0,0,0,0,0\n"
            "333,0,17,Kyogo Furuhashi,31,ATA,77,0,0,0,0,0,0\n"
            "334,0,17,Keito Nakamura,25,ATA,77,0,0,0,0,0,0\n"
            "335,0,17,Yukinari Sugawara,25,DEF,78,0,0,0,0,0,0\n"
            "336,0,17,Koki Machida,28,DEF,77,0,0,0,0,0,0\n"
            "337,0,17,Ao Tanaka,27,MED,76,0,0,0,0,0,0\n"
            "338,0,17,Daichi Kamada,29,MED,78,0,0,0,0,0,0\n"
            "339,0,17,Keisuke Osako,26,GK,74,0,0,0,0,0,0\n"
            "340,0,17,Kuryu Matsuki,23,MED,74,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "341,0,18,Federico Valverde,27,MED,88,0,0,0,0,0,0\n"
            "342,0,18,Darwin Nunez,26,ATA,82,0,0,0,0,0,0\n"
            "343,0,18,Ronald Araujo,27,DEF,85,0,0,0,0,0,0\n"
            "344,0,18,Manuel Ugarte,25,MED,82,0,0,0,0,0,0\n"
            "345,0,18,Rodrigo Bentancur,28,MED,82,0,0,0,0,0,0\n"
            "346,0,18,Nicolas de la Cruz,29,MED,80,0,0,0,0,0,0\n"
            "347,0,18,Sergio Rochet,33,GK,80,0,0,0,0,0,0\n"
            "348,0,18,Mathias Olivera,28,DEF,79,0,0,0,0,0,0\n"
            "349,0,18,Jose Maria Gimenez,31,DEF,80,0,0,0,0,0,0\n"
            "350,0,18,Facundo Pellistri,24,ATA,78,0,0,0,0,0,0\n"
            "351,0,18,Giorgian de Arrascaeta,32,MED,79,0,0,0,0,0,0\n"
            "352,0,18,Facundo Torres,26,ATA,77,0,0,0,0,0,0\n"
            "353,0,18,Sebastian Caceres,26,DEF,77,0,0,0,0,0,0\n"
            "354,0,18,Matias Vina,28,DEF,77,0,0,0,0,0,0\n"
            "355,0,18,Guillermo Varela,33,DEF,75,0,0,0,0,0,0\n"
            "356,0,18,Maximiliano Araujo,26,ATA,77,0,0,0,0,0,0\n"
            "357,0,18,Brian Rodriguez,26,ATA,76,0,0,0,0,0,0\n"
            "358,0,18,Luciano Rodriguez,22,ATA,76,0,0,0,0,0,0\n"
            "359,0,18,Santiago Mele,28,GK,75,0,0,0,0,0,0\n"
            "360,0,18,Emiliano Toranza,26,MED,75,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "361,0,19,Manuel Akanji,30,DEF,84,0,0,0,0,0,0\n"
            "362,0,19,Granit Xhaka,33,MED,84,0,0,0,0,0,0\n"
            "363,0,19,Gregor Kobel,28,GK,87,0,0,0,0,0,0\n"
            "364,0,19,Yann Sommer,37,GK,81,0,0,0,0,0,0\n"
            "365,0,19,Denis Zakaria,29,MED,81,0,0,0,0,0,0\n"
            "366,0,19,Remo Freuler,34,MED,79,0,0,0,0,0,0\n"
            "367,0,19,Breel Embolo,29,ATA,79,0,0,0,0,0,0\n"
            "368,0,19,Dan Ndoye,25,ATA,80,0,0,0,0,0,0\n"
            "369,0,19,Ruben Vargas,27,ATA,78,0,0,0,0,0,0\n"
            "370,0,19,Michel Aebischer,29,MED,78,0,0,0,0,0,0\n"
            "371,0,19,Fabian Schar,34,DEF,80,0,0,0,0,0,0\n"
            "372,0,19,Nico Elvedi,29,DEF,78,0,0,0,0,0,0\n"
            "373,0,19,Ricardo Rodriguez,33,DEF,76,0,0,0,0,0,0\n"
            "374,0,19,Silvan Widmer,33,DEF,75,0,0,0,0,0,0\n"
            "375,0,19,Zeki Amdouni,25,ATA,77,0,0,0,0,0,0\n"
            "376,0,19,Noah Okafor,26,ATA,77,0,0,0,0,0,0\n"
            "377,0,19,Fabian Rieder,24,MED,77,0,0,0,0,0,0\n"
            "378,0,19,Cedric Zesiger,27,DEF,75,0,0,0,0,0,0\n"
            "379,0,19,Leonidas Stergiou,24,DEF,75,0,0,0,0,0,0\n"
            "380,0,19,Vincent Sierro,30,MED,76,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "381,0,20,Rasmus Hojlund,23,ATA,81,0,0,0,0,0,0\n"
            "382,0,20,Andreas Christensen,30,DEF,83,0,0,0,0,0,0\n"
            "383,0,20,Pierre-Emile Hojbjerg,30,MED,81,0,0,0,0,0,0\n"
            "384,0,20,Christian Eriksen,34,MED,78,0,0,0,0,0,0\n"
            "385,0,20,Joachim Andersen,30,DEF,81,0,0,0,0,0,0\n"
            "386,0,20,Kasper Schmeichel,39,GK,77,0,0,0,0,0,0\n"
            "387,0,20,Morten Hjulmand,26,MED,82,0,0,0,0,0,0\n"
            "388,0,20,Alexander Bah,28,DEF,80,0,0,0,0,0,0\n"
            "389,0,20,Jonas Wind,27,ATA,79,0,0,0,0,0,0\n"
            "390,0,20,Victor Nelsson,27,DEF,78,0,0,0,0,0,0\n"
            "391,0,20,Jannik Vestergaard,33,DEF,77,0,0,0,0,0,0\n"
            "392,0,20,Joakim Maehle,29,DEF,78,0,0,0,0,0,0\n"
            "393,0,20,Yussuf Poulsen,32,ATA,76,0,0,0,0,0,0\n"
            "394,0,20,Matt O'Riley,25,MED,81,0,0,0,0,0,0\n"
            "395,0,20,Gustav Isaksen,25,ATA,77,0,0,0,0,0,0\n"
            "396,0,20,Albert Gronbaek,25,MED,78,0,0,0,0,0,0\n"
            "397,0,20,Mads Hermansen,25,GK,79,0,0,0,0,0,0\n"
            "398,0,20,Victor Kristiansen,23,DEF,77,0,0,0,0,0,0\n"
            "399,0,20,Mikkel Damsgaard,25,MED,76,0,0,0,0,0,0\n"
            "400,0,20,Patrick Dorgu,21,DEF,78,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "401,0,21,Heung-min Son,33,ATA,87,0,0,0,0,0,0\n"
            "402,0,21,Min-jae Kim,29,DEF,84,0,0,0,0,0,0\n"
            "403,0,21,Kang-in Lee,25,MED,82,0,0,0,0,0,0\n"
            "404,0,21,Hee-chan Hwang,30,ATA,80,0,0,0,0,0,0\n"
            "405,0,21,In-beom Hwang,29,MED,79,0,0,0,0,0,0\n"
            "406,0,21,Hyeon-woo Jo,34,GK,76,0,0,0,0,0,0\n"
            "407,0,21,Jae-sung Lee,33,MED,76,0,0,0,0,0,0\n"
            "408,0,21,Gue-sung Cho,28,ATA,75,0,0,0,0,0,0\n"
            "409,0,21,Young-woo Seol,27,DEF,75,0,0,0,0,0,0\n"
            "410,0,21,Seung-hyun Jung,32,DEF,73,0,0,0,0,0,0\n"
            "411,0,21,Jin-su Kim,34,DEF,72,0,0,0,0,0,0\n"
            "412,0,21,Woo-yeong Jeong,26,MED,74,0,0,0,0,0,0\n"
            "413,0,21,Hyun-seok Hong,27,MED,74,0,0,0,0,0,0\n"
            "414,0,21,Ji-soo Kim,21,DEF,73,0,0,0,0,0,0\n"
            "415,0,21,Jun-ho Bae,22,MED,74,0,0,0,0,0,0\n"
            "416,0,21,Min-kyu Joo,36,ATA,73,0,0,0,0,0,0\n"
            "417,0,21,Sungi Bum,28,GK,72,0,0,0,0,0,0\n"
            "418,0,21,Myung-jae Lee,32,DEF,72,0,0,0,0,0,0\n"
            "419,0,21,Sang-ho Na,29,ATA,72,0,0,0,0,0,0\n"
            "420,0,21,Hyun-ju Lee,23,MED,73,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "421,0,22,Mathew Ryan,34,GK,76,0,0,0,0,0,0\n"
            "422,0,22,Harry Souttar,27,DEF,76,0,0,0,0,0,0\n"
            "423,0,22,Alessandro Circati,22,DEF,76,0,0,0,0,0,0\n"
            "424,0,22,Jackson Irvine,33,MED,74,0,0,0,0,0,0\n"
            "425,0,22,Connor Metcalfe,26,MED,73,0,0,0,0,0,0\n"
            "426,0,22,Craig Goodwin,34,ATA,74,0,0,0,0,0,0\n"
            "427,0,22,Nestory Irankunda,20,ATA,74,0,0,0,0,0,0\n"
            "428,0,22,Kusini Yengi,27,ATA,72,0,0,0,0,0,0\n"
            "429,0,22,Kye Rowles,28,DEF,72,0,0,0,0,0,0\n"
            "430,0,22,Jordan Bos,23,DEF,73,0,0,0,0,0,0\n"
            "431,0,22,Keanu Baccus,28,MED,71,0,0,0,0,0,0\n"
            "432,0,22,Aiden O'Neill,27,MED,71,0,0,0,0,0,0\n"
            "433,0,22,Mitchell Duke,35,ATA,70,0,0,0,0,0,0\n"
            "434,0,22,Martin Boyle,33,ATA,72,0,0,0,0,0,0\n"
            "435,0,22,Lewis Miller,25,DEF,70,0,0,0,0,0,0\n"
            "436,0,22,Gethin Jones,30,DEF,70,0,0,0,0,0,0\n"
            "437,0,22,Joe Gauci,25,GK,72,0,0,0,0,0,0\n"
            "438,0,22,Riley McGree,27,MED,73,0,0,0,0,0,0\n"
            "439,0,22,Samuel Silvera,25,ATA,70,0,0,0,0,0,0\n"
            "440,0,22,Cameron Burgess,30,DEF,71,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "441,0,23,Mehdi Taremi,33,ATA,80,0,0,0,0,0,0\n"
            "442,0,23,Sardar Azmoun,31,ATA,77,0,0,0,0,0,0\n"
            "443,0,23,Alireza Jahanbakhsh,32,ATA,74,0,0,0,0,0,0\n"
            "444,0,23,Saman Ghoddos,32,MED,74,0,0,0,0,0,0\n"
            "445,0,23,Alireza Beiranvand,33,GK,75,0,0,0,0,0,0\n"
            "446,0,23,Saeid Ezatolahi,29,MED,73,0,0,0,0,0,0\n"
            "447,0,23,Milad Mohammadi,32,DEF,72,0,0,0,0,0,0\n"
            "448,0,23,Shoja Khalilzadeh,37,DEF,70,0,0,0,0,0,0\n"
            "449,0,23,Hossein Kanaani,32,DEF,72,0,0,0,0,0,0\n"
            "450,0,23,Ramin Rezaeian,36,DEF,71,0,0,0,0,0,0\n"
            "451,0,23,Mehdi Torabi,31,MED,72,0,0,0,0,0,0\n"
            "452,0,23,Ali Gholizadeh,30,MED,72,0,0,0,0,0,0\n"
            "453,0,23,Omid Noorafkan,29,MED,71,0,0,0,0,0,0\n"
            "454,0,23,Mohammad Mohebi,27,ATA,72,0,0,0,0,0,0\n"
            "455,0,23,Payam Niazmand,31,GK,70,0,0,0,0,0,0\n"
            "456,0,23,Ehsan Hajsafi,36,DEF,70,0,0,0,0,0,0\n"
            "457,0,23,Shayesteh Seh,24,MED,69,0,0,0,0,0,0\n"
            "458,0,23,Aria Yousefi,24,DEF,69,0,0,0,0,0,0\n"
            "459,0,23,Shahriyar Moghanlou,31,ATA,71,0,0,0,0,0,0\n"
            "460,0,23,Amin Hazbavi,23,DEF,71,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "461,0,24,David Alaba,33,DEF,83,0,0,0,0,0,0\n"
            "462,0,24,Marcel Sabitzer,32,MED,82,0,0,0,0,0,0\n"
            "463,0,24,Konrad Laimer,29,MED,82,0,0,0,0,0,0\n"
            "464,0,24,Christoph Baumgartner,26,MED,81,0,0,0,0,0,0\n"
            "465,0,24,Michael Gregoritsch,32,ATA,79,0,0,0,0,0,0\n"
            "466,0,24,Kevin Danso,27,DEF,81,0,0,0,0,0,0\n"
            "467,0,24,Xaver Schlager,28,MED,80,0,0,0,0,0,0\n"
            "468,0,24,Philipp Lienhart,29,DEF,79,0,0,0,0,0,0\n"
            "469,0,24,Stefan Posch,29,DEF,79,0,0,0,0,0,0\n"
            "470,0,24,Patrick Wimmer,25,ATA,78,0,0,0,0,0,0\n"
            "471,0,24,Nicolas Seiwald,25,MED,78,0,0,0,0,0,0\n"
            "472,0,24,Alexander Prass,25,MED,77,0,0,0,0,0,0\n"
            "473,0,24,Romano Schmid,26,MED,77,0,0,0,0,0,0\n"
            "474,0,24,Max Wober,28,DEF,76,0,0,0,0,0,0\n"
            "475,0,24,Phillipp Mwene,32,DEF,75,0,0,0,0,0,0\n"
            "476,0,24,Marko Arnautovic,37,ATA,74,0,0,0,0,0,0\n"
            "477,0,24,Alexander Schlager,31,GK,76,0,0,0,0,0,0\n"
            "478,0,24,Patrick Pentz,29,GK,76,0,0,0,0,0,0\n"
            "479,0,24,Gernot Trauner,34,DEF,76,0,0,0,0,0,0\n"
            "480,0,24,Junior Adamu,25,ATA,74,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "481,0,25,Victor Osimhen,27,ATA,87,0,0,0,0,0,0\n"
            "482,0,25,Ademola Lookman,28,ATA,83,0,0,0,0,0,0\n"
            "483,0,25,Victor Boniface,25,ATA,83,0,0,0,0,0,0\n"
            "484,0,25,Alex Iwobi,30,MED,78,0,0,0,0,0,0\n"
            "485,0,25,Wilfred Ndidi,29,MED,79,0,0,0,0,0,0\n"
            "486,0,25,Calvin Bassey,26,DEF,79,0,0,0,0,0,0\n"
            "487,0,25,Samuel Chukwueze,27,ATA,78,0,0,0,0,0,0\n"
            "488,0,25,Terem Moffi,27,ATA,77,0,0,0,0,0,0\n"
            "489,0,25,Ola Aina,29,DEF,77,0,0,0,0,0,0\n"
            "490,0,25,Bright Osayi-Samuel,28,DEF,76,0,0,0,0,0,0\n"
            "491,0,25,Frank Onyeka,28,MED,75,0,0,0,0,0,0\n"
            "492,0,25,Raphael Onyedika,25,MED,77,0,0,0,0,0,0\n"
            "493,0,25,Chidozie Awaziem,29,DEF,74,0,0,0,0,0,0\n"
            "494,0,25,Semi Ajayi,32,DEF,73,0,0,0,0,0,0\n"
            "495,0,25,Zaidu Sanusi,29,DEF,74,0,0,0,0,0,0\n"
            "496,0,25,Stanley Nwabali,30,GK,75,0,0,0,0,0,0\n"
            "497,0,25,Kelechi Iheanacho,29,ATA,74,0,0,0,0,0,0\n"
            "498,0,25,Moses Simon,30,ATA,75,0,0,0,0,0,0\n"
            "499,0,25,Maduka Okoye,26,GK,75,0,0,0,0,0,0\n"
            "500,0,25,Alhassan Yusuf,25,MED,74,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "501,0,26,Hakan Calhanoglu,32,MED,85,0,0,0,0,0,0\n"
            "502,0,26,Arda Guler,21,MED,81,0,0,0,0,0,0\n"
            "503,0,26,Kenan Yildiz,21,ATA,83,0,0,0,0,0,0\n"
            "504,0,26,Baris Alper Yilmaz,26,ATA,80,0,0,0,0,0,0\n"
            "505,0,26,Ferdi Kadioglu,26,DEF,81,0,0,0,0,0,0\n"
            "506,0,26,Orkun Kokcu,25,MED,81,0,0,0,0,0,0\n"
            "507,0,26,Merih Demiral,28,DEF,79,0,0,0,0,0,0\n"
            "508,0,26,Abdulkerim Bardakci,31,DEF,78,0,0,0,0,0,0\n"
            "509,0,26,Kerem Akturkoglu,27,ATA,81,0,0,0,0,0,0\n"
            "510,0,26,Mert Gunok,37,GK,77,0,0,0,0,0,0\n"
            "511,0,26,Salih Ozcan,28,MED,76,0,0,0,0,0,0\n"
            "512,0,26,Ismail Yuksek,27,MED,77,0,0,0,0,0,0\n"
            "513,0,26,Kaan Ayhan,31,DEF,76,0,0,0,0,0,0\n"
            "514,0,26,Zeki Celik,29,DEF,75,0,0,0,0,0,0\n"
            "515,0,26,Semih Kilicsoy,20,ATA,77,0,0,0,0,0,0\n"
            "516,0,26,Okay Yokuslu,32,MED,75,0,0,0,0,0,0\n"
            "517,0,26,Cenk Ozkacar,25,DEF,74,0,0,0,0,0,0\n"
            "518,0,26,Altay Bayindir,28,GK,75,0,0,0,0,0,0\n"
            "519,0,26,Samet Akaydin,32,DEF,73,0,0,0,0,0,0\n"
            "520,0,26,Yunus Akgun,25,ATA,75,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "521,0,27,Erling Haaland,25,ATA,91,0,0,0,0,0,0\n"
            "522,0,27,Martin Odegaard,27,MED,88,0,0,0,0,0,0\n"
            "523,0,27,Alexander Sorloth,30,ATA,82,0,0,0,0,0,0\n"
            "524,0,27,Fredrik Aursnes,30,MED,81,0,0,0,0,0,0\n"
            "525,0,27,Sander Berge,28,MED,80,0,0,0,0,0,0\n"
            "526,0,27,Julian Ryerson,28,DEF,80,0,0,0,0,0,0\n"
            "527,0,27,Kristoffer Ajer,28,DEF,79,0,0,0,0,0,0\n"
            "528,0,27,Jorgen Strand Larsen,26,ATA,79,0,0,0,0,0,0\n"
            "529,0,27,Oscar Bobb,22,ATA,78,0,0,0,0,0,0\n"
            "530,0,27,Antonio Nusa,21,ATA,78,0,0,0,0,0,0\n"
            "531,0,27,Leo Skiri Ostigard,26,DEF,77,0,0,0,0,0,0\n"
            "532,0,27,Patrick Berg,28,MED,77,0,0,0,0,0,0\n"
            "533,0,27,Hugo Vetlesen,26,MED,76,0,0,0,0,0,0\n"
            "534,0,27,Andreas Schjelderup,22,ATA,76,0,0,0,0,0,0\n"
            "535,0,27,Marcus Holmgren Pedersen,25,DEF,76,0,0,0,0,0,0\n"
            "536,0,27,Birger Meling,31,DEF,75,0,0,0,0,0,0\n"
            "537,0,27,David Moller Wolfe,24,DEF,75,0,0,0,0,0,0\n"
            "538,0,27,Orjan Nyland,35,GK,75,0,0,0,0,0,0\n"
            "539,0,27,Egil Selvik,28,GK,73,0,0,0,0,0,0\n"
            "540,0,27,Stian Gregersen,31,DEF,74,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "541,0,28,Moises Caicedo,24,MED,84,0,0,0,0,0,0\n"
            "542,0,28,Piero Hincapie,24,DEF,82,0,0,0,0,0,0\n"
            "543,0,28,Pervis Estupinan,28,DEF,81,0,0,0,0,0,0\n"
            "544,0,28,Willian Pacho,24,DEF,83,0,0,0,0,0,0\n"
            "545,0,28,Kendry Paez,19,MED,78,0,0,0,0,0,0\n"
            "546,0,28,Enner Valencia,36,ATA,75,0,0,0,0,0,0\n"
            "547,0,28,Alexander Dominguez,39,GK,74,0,0,0,0,0,0\n"
            "548,0,28,Felix Torres,29,DEF,76,0,0,0,0,0,0\n"
            "549,0,28,Angelo Preciado,28,DEF,75,0,0,0,0,0,0\n"
            "550,0,28,Carlos Gruezo,31,MED,74,0,0,0,0,0,0\n"
            "551,0,28,Alan Franco,27,MED,74,0,0,0,0,0,0\n"
            "552,0,28,Jeremy Sarmiento,24,ATA,75,0,0,0,0,0,0\n"
            "553,0,28,John Yeboah,25,ATA,74,0,0,0,0,0,0\n"
            "554,0,28,Kevin Rodriguez,26,ATA,73,0,0,0,0,0,0\n"
            "555,0,28,Jose Cifuentes,27,MED,73,0,0,0,0,0,0\n"
            "556,0,28,Joel Ordonez,22,DEF,75,0,0,0,0,0,0\n"
            "557,0,28,Jhoanner Chavez,24,DEF,72,0,0,0,0,0,0\n"
            "558,0,28,Moises Ramirez,25,GK,73,0,0,0,0,0,0\n"
            "559,0,28,Jordi Caicedo,28,ATA,71,0,0,0,0,0,0\n"
            "560,0,28,Joao Ortiz,30,MED,72,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "561,0,29,Mohamed Salah,34,ATA,88,0,0,0,0,0,0\n"
            "562,0,29,Omar Marmoush,27,ATA,81,0,0,0,0,0,0\n"
            "563,0,29,Mostafa Mohamed,28,ATA,78,0,0,0,0,0,0\n"
            "564,0,29,Trézéguet,31,ATA,76,0,0,0,0,0,0\n"
            "565,0,29,Mohamed Elneny,33,MED,74,0,0,0,0,0,0\n"
            "566,0,29,Mohamed El Shenawy,37,GK,77,0,0,0,0,0,0\n"
            "567,0,29,Ahmed Hegazi,35,DEF,73,0,0,0,0,0,0\n"
            "568,0,29,Mohamed Abdelmonem,27,DEF,77,0,0,0,0,0,0\n"
            "569,0,29,Hamdi Fathi,31,MED,74,0,0,0,0,0,0\n"
            "570,0,29,Emam Ashour,28,MED,76,0,0,0,0,0,0\n"
            "571,0,29,Zizo,30,MED,75,0,0,0,0,0,0\n"
            "572,0,29,Marwan Attia,27,MED,74,0,0,0,0,0,0\n"
            "573,0,29,Mohamed Hany,30,DEF,73,0,0,0,0,0,0\n"
            "574,0,29,Mostafa Fathi,32,ATA,72,0,0,0,0,0,0\n"
            "575,0,29,Mohamed Hamdi,31,DEF,72,0,0,0,0,0,0\n"
            "576,0,29,Mostafa Shobeir,26,GK,73,0,0,0,0,0,0\n"
            "577,0,29,Yasser Ibrahim,33,DEF,72,0,0,0,0,0,0\n"
            "578,0,29,Ahmed Nabil Koka,24,MED,72,0,0,0,0,0,0\n"
            "579,0,29,Ibrahim Adel,25,ATA,73,0,0,0,0,0,0\n"
            "580,0,29,Ramy Rabia,33,DEF,71,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "581,0,30,Franck Kessie,29,MED,82,0,0,0,0,0,0\n"
            "582,0,30,Singo Wilfried,25,DEF,80,0,0,0,0,0,0\n"
            "583,0,30,Ousmane Diomande,22,DEF,82,0,0,0,0,0,0\n"
            "584,0,30,Odilon Kossounou,25,DEF,81,0,0,0,0,0,0\n"
            "585,0,30,Seko Fofana,31,MED,80,0,0,0,0,0,0\n"
            "586,0,30,Simon Adingra,24,ATA,80,0,0,0,0,0,0\n"
            "587,0,30,Sebastien Haller,31,ATA,79,0,0,0,0,0,0\n"
            "588,0,30,Ibrahim Sangare,28,MED,79,0,0,0,0,0,0\n"
            "589,0,30,Evan Ndicka,26,DEF,81,0,0,0,0,0,0\n"
            "590,0,30,Yahia Fofana,25,GK,76,0,0,0,0,0,0\n"
            "591,0,30,Karim Konate,22,ATA,78,0,0,0,0,0,0\n"
            "592,0,30,Amad Diallo,23,ATA,80,0,0,0,0,0,0\n"
            "593,0,30,Jeremie Boga,29,ATA,78,0,0,0,0,0,0\n"
            "594,0,30,Oumar Diakite,22,ATA,76,0,0,0,0,0,0\n"
            "595,0,30,Jean Michael Seri,34,MED,74,0,0,0,0,0,0\n"
            "596,0,30,Emmanuel Agbadou,29,DEF,76,0,0,0,0,0,0\n"
            "597,0,30,Ghislain Konan,30,DEF,74,0,0,0,0,0,0\n"
            "598,0,30,Badra Ali Sangare,40,GK,70,0,0,0,0,0,0\n"
            "599,0,30,Christian Kouame,28,ATA,75,0,0,0,0,0,0\n"
            "600,0,30,Lazare Amani,28,MED,75,0,0,0,0,0,0\n");

    
    fprintf(fPlayers,
            "601,0,31,Luca Zidane,28,GK,75,0,0,0,0,0,0\n"
            "602,0,31,Rayan Ait-Nouri,25,DEF,81,0,0,0,0,0,0\n"
            "603,0,31,Ramy Bensebaini,31,DEF,78,0,0,0,0,0,0\n"
            "604,0,31,Riyad Mahrez,35,ATA,80,0,0,0,0,0,0\n"
            "605,0,31,Amine Gouiri,26,ATA,78,0,0,0,0,0,0\n"
            "606,0,31,Mohamed Amoura,26,ATA,78,0,0,0,0,0,0\n"
            "607,0,31,Ismael Bennacer,28,MED,81,0,0,0,0,0,0\n"
            "608,0,31,Houssem Aouar,27,MED,77,0,0,0,0,0,0\n"
            "609,0,31,Fares Chaibi,23,MED,77,0,0,0,0,0,0\n"
            "610,0,31,Ibrahim Maza,20,MED,76,0,0,0,0,0,0\n"
            "611,0,31,Aissa Mandi,34,DEF,74,0,0,0,0,0,0\n"
            "612,0,31,Nabil Bentaleb,31,MED,76,0,0,0,0,0,0\n"
            "613,0,31,Hicham Boudaoui,26,MED,76,0,0,0,0,0,0\n"
            "614,0,31,Ramiz Zerrouki,28,MED,75,0,0,0,0,0,0\n"
            "615,0,31,Samir Chergui,26,DEF,74,0,0,0,0,0,0\n"
            "616,0,31,Jaouen Hadjam,23,DEF,73,0,0,0,0,0,0\n"
            "617,0,31,Zinedine Belaid,24,DEF,74,0,0,0,0,0,0\n"
            "618,0,31,Anis Hadj Moussa,24,ATA,75,0,0,0,0,0,0\n"
            "619,0,31,Oussama Benbot,31,GK,73,0,0,0,0,0,0\n"
            "620,0,31,Melvin Mastil,26,GK,72,0,0,0,0,0,0\n");

   
    fprintf(fPlayers,
            "621,0,32,Alphonso Davies,25,DEF,84,0,0,0,0,0,0\n"
            "622,0,32,Jonathan David,26,ATA,82,0,0,0,0,0,0\n"
            "623,0,32,Stephen Eustaquio,29,MED,80,0,0,0,0,0,0\n"
            "624,0,32,Cyle Larin,31,ATA,79,0,0,0,0,0,0\n"
            "625,0,32,Tajon Buchanan,27,MED,79,0,0,0,0,0,0\n"
            "626,0,32,Ismael Kone,23,MED,78,0,0,0,0,0,0\n"
            "627,0,32,Alistair Johnston,27,DEF,79,0,0,0,0,0,0\n"
            "628,0,32,Moise Bombito,26,DEF,78,0,0,0,0,0,0\n"
            "629,0,32,Maxime Crepeau,32,GK,76,0,0,0,0,0,0\n"
            "630,0,32,Derek Cornelius,28,DEF,76,0,0,0,0,0,0\n"
            "631,0,32,Jacob Shaffelburg,26,MED,76,0,0,0,0,0,0\n"
            "632,0,32,Richie Laryea,31,DEF,75,0,0,0,0,0,0\n"
            "633,0,32,Dayne St Clair,29,GK,74,0,0,0,0,0,0\n"
            "634,0,32,Liam Millar,26,MED,74,0,0,0,0,0,0\n"
            "635,0,32,Mathieu Choiniere,27,MED,74,0,0,0,0,0,0\n"
            "636,0,32,Jonathan Osorio,33,MED,73,0,0,0,0,0,0\n"
            "637,0,32,Joel Waterman,32,DEF,73,0,0,0,0,0,0\n"
            "638,0,32,Alfie Jones,28,DEF,74,0,0,0,0,0,0\n"
            "639,0,32,Tani Oluwaseyi,26,ATA,74,0,0,0,0,0,0\n"
            "640,0,32,Owen Goodman,23,GK,71,0,0,0,0,0,0\n");

    fclose(fPlayers);

    printf(GREEN "[!] Initial player database generated successfully!\n" RESET);
}