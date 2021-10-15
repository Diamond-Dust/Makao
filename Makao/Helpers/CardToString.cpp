#include "CardToString.h"

#include "../CardRanks/Valet.h"
#include "../CardRanks/Ace.h"

std::string cSuitToString(cSuit suit)
{
    std::string name = "";
    switch (suit) {
        case cSuit::Clovers:
            name += "Clovers";
            break;
        case cSuit::Hearts:
            name += "Hearts";
            break;
        case cSuit::Tiles:
            name += "Tiles";
            break;
        case cSuit::Spades:
            name += "Spades";
            break;
    }
    return name;
}

std::string cRankToString(cRank rank)
{
    std::string name = "";
    switch (rank) {
        case cRank::Ace:
            name += "Ace";
            break;
        case cRank::Two:
            name += "Two";
            break;
        case cRank::Three:
            name += "Three";
            break;
        case cRank::Four:
            name += "Four";
            break;
        case cRank::Five:
            name += "Five";
            break;
        case cRank::Six:
            name += "Six";
            break;
        case cRank::Seven:
            name += "Seven";
            break;
        case cRank::Eight:
            name += "Eight";
            break;
        case cRank::Nine:
            name += "Nine";
            break;
        case cRank::Ten:
            name += "Ten";
            break;
        case cRank::Valet:
            name += "Valet";
            break;
        case cRank::Queen:
            name += "Queen";
            break;
        case cRank::King:
            name += "King";
            break;
    }
    return name;
}

std::string cardToString(Card* card)
{
    std::string name = "";
    
    name += cRankToString(card->Rank);

    name += " of ";

    name += cSuitToString(card->Suit);

    Ace* ace_ptr;
    Valet* valet_ptr;
    switch (card->Rank) {
        case cRank::Ace:
            name += " desiring ";
            ace_ptr = dynamic_cast<Ace*>(card);
            name += cSuitToString((*ace_ptr).getDesiredSuit());
            break;
        case cRank::Valet:
            name += " desiring ";
            valet_ptr = dynamic_cast<Valet*>(card);
            name += cRankToString((*valet_ptr).getDesiredRank());
            break;
    }

    return name;
}
