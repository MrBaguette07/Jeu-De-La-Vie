#include <algorithm>

#include "jeuLogique.h"

int Voisins(int** grille, const int& nombreLigne, const int& nombreColonne, const int& ligneIdx, const int& colonneIdx)
{
    int sum = 0;
    for (int y = std::max(ligneIdx-1, 0); y < std::min(ligneIdx+2, nombreLigne); ++y)
    {
        for (int x = std::max(colonneIdx-1, 0); x < std::min(colonneIdx+2, nombreColonne); ++x)
        {
            sum += grille[y][x] & 1;
        }
    }
    return sum -= grille[ligneIdx][colonneIdx] & 1;
}

void Generation(int** grille, const int& nombreLigne, const int& nombreColonne)
{
    for (int ligneIdx = 0; ligneIdx < nombreLigne; ++ligneIdx)
    {
        for (int colonneIdx = 0; colonneIdx < nombreColonne; ++colonneIdx)
        {
            int ns = Voisins(grille, nombreLigne, nombreColonne, ligneIdx, colonneIdx);
            if ((ns | grille[ligneIdx][colonneIdx]) == 3)
            {
                grille[ligneIdx][colonneIdx] |= 2;
            }
        }
    }

    for (int ligneIdx = 0; ligneIdx < nombreLigne; ++ligneIdx)
    {
        for (int colonneIdx = 0; colonneIdx < nombreColonne; ++colonneIdx)
        {
            grille[ligneIdx][colonneIdx] >>= 1;
        }
    }
}
