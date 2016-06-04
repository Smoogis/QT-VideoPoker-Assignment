///////////////////////////////////////////////////////////////////////
// File:  Hand.cpp
// Author:
// This assignment represents my own work and is in accordance with the College Academic Policy
//
// Copyright (c) 2013 All Right Reserved by Dave Burchill
// Contributors:
// Description:  cemo ctor and dtor
//
// Date: Sept 2013
//
// Revisions:
//
/////////////////////////////////////////////////////////////////


#include "Hand.h"

#include <iostream>
#include <algorithm>
#include <iomanip>
#include "Card.h"
#include "Deck.h"

const std::map<PokerHand, int> Hand::paySheet = {
    {PokerHand::ROYAL_FLUSH, 250},
    {PokerHand::STRAIGHT_FLUSH, 50},
    {PokerHand::FOUR_OF_A_KIND, 25},
    {PokerHand::FULL_HOUSE, 9},
    {PokerHand::FLUSH, 6},
    {PokerHand::STRAIGHT, 4},
    {PokerHand::THREE_OF_A_KIND, 3},
    {PokerHand::TWO_PAIR, 2},
    {PokerHand::JACKS_OR_BETTER, 1},
    {PokerHand::NADA, 0}
};

const std::map<PokerHand, std::string> Hand::handNames = {
    {PokerHand::ROYAL_FLUSH, "Royal Flush"},
    {PokerHand::STRAIGHT_FLUSH, "Straight Flush"},
    {PokerHand::FOUR_OF_A_KIND, "Four of a Kind"},
    {PokerHand::FULL_HOUSE, "Full House"},
    {PokerHand::FLUSH, "Flush"},
    {PokerHand::STRAIGHT, "Straight"},
    {PokerHand::THREE_OF_A_KIND, "Three of a Kind"},
    {PokerHand::TWO_PAIR, "Two Pair"},
    {PokerHand::JACKS_OR_BETTER, "Pair of Jacks or Better"},
    {PokerHand::NADA, "Nada"}
};


Hand::Hand()
{}

Hand::~Hand()
{
    //std::cout << "\nHand - Destruct\n";
}

int Hand::payOut() const
{
    auto it = paySheet.find(rank());
    if (it == paySheet.end())
    {
        throw std::runtime_error("Pay Sheet Problem");
    }
    return it->second;  //return payout amount from paysheet
}

std::string Hand::toString() const
{

    auto it = handNames.find(rank());
    if (it == handNames.end())
    {
        throw std::runtime_error("Hand name table problem");
    }
    return it->second;
}


void Hand::dealNewHand(Deck &deck)
{
    clearHand();
    for (int i=0;i<5;i++)
    {
        addCard(deck.dealCard());
        _drawCard.push_back(true);  //new hand set draw to no for each new card
    }
}

void Hand::clearHand()
{
    // remove all cards, reset faceCount vector
    _hand.clear();      //cards in hand
    _drawCard.clear();  //cards in hand to draw

}

void Hand::addCard(CardPtr card)
{
    _hand.push_back(card);
}

void Hand::showPayTable() const
{
    for (auto i : paySheet)
    {
        std::cout << std::setw(25) << handNames.find(i.first)->second << "   " << paySheet.find(i.first)->second << std::endl;
    }
}

// display hand to stdo
void Hand::showDraw()
{

    //
    do
    {
        system("cls");
        // Display current draw choices
        for (unsigned i = 0; i < _hand.size(); ++i)
            std::cout  << i+1 << ": " << _hand[i]->toString() << (_drawCard[i] ? " (Draw)" : " (Hold)")  << '\n';

    } while (chooseDraw()); //change draw choices

}

void Hand::print() const
{
    system("cls");

    for (unsigned i = 0; i < _hand.size(); ++i)
        std::cout  << i+1 << ": " << _hand[i]->toString() << '\n';
}

bool Hand::chooseDraw() // return true when done making changes
{
    std::cout << "\nEnter card number (1-5) to change Draw/Hold (P) to play:";

    char c;
    do
    {
        c = toupper(std::cin.get());
        switch (c)
        {
            case 'P':

               return false; //done making changes
                break;

            case '1':
                _drawCard[0] = !_drawCard[0];
                break;

            case '2':
                _drawCard[1] = !_drawCard[1];
                break;

            case '3':
                _drawCard[2] = !_drawCard[2];
                break;

            case '4':
                _drawCard[3] = !_drawCard[3];
                break;

            case '5':
                _drawCard[4] = !_drawCard[4];
                break;

            default:
                break;

        }
    } while (c != '1' && c != '2' && c != '3' && c != '4' && c != '5');

    return true;
}

void Hand::drawCards(Deck &deck)
{
    for (size_t i=0;i<_drawCard.size();i++)
    {
        if (_drawCard[i])
        {
            _hand[i] = deck.dealCard();
        }
    }
}
void Hand::removeCard(int index)
{
    _hand.erase(_hand.begin()+index-1);
}



///////////////////////////////////////////////////////////////
// scoring methods
///////////////////////////////////////////////////////////////

bool Hand::isRoyalFlush() const
{
    if (isStraightFlush())
    {
        return std::none_of(_hand.begin(),
                           _hand.end(),
                           [](CardPtr e){
                               return (e->_face < Face::TEN && e->_face != Face::ACE);
                           }
                           );
    }
    return false;
}


bool Hand::isStraightFlush() const
{
    return (isStraight() && isFlush());
}

bool Hand::isFourOfAKind() const
{
    std::map<Face, int> faces;
    for (auto cptr : _hand)
        faces[cptr->_face]++;

    return std::any_of(
        faces.begin(),
        faces.end(),
        [](std::pair<Face, int> e) {return e.second == 4; });

}

bool Hand::isFullHouse() const
{
    return (isPair() && isThreeOfAKind());
}

bool Hand::isFlush() const
{
    Suit suit = _hand[0]->_suit;

    return std::all_of(_hand.begin(),
                       _hand.end(),
                       [suit](CardPtr e){
                           return (e->_suit == suit);}
                );
}

bool Hand::isStraight() const
{

    // create a temp set of faces to examine
    // for straights. if it's a straight the min and max elements
    // must be four appart (ie, 5-1 = 4)
    // if there is an ace add it to the array as 0 and KING + 1 so
    // it can be used as high or low

    std::set<Face> faces;
    for (auto cptr : _hand)
        faces.insert(cptr->_face);

    // no pairs, triples or four of a kind
    if(faces.size() != _hand.size())
        return false;

    auto result = std::minmax_element(faces.begin(), faces.end());

    // if min and max are hand.size apart, it must be a straight
    if (static_cast<int>(*result.second) - static_cast<int>(*result.first) == _hand.size() - 1)
        return true;

    // still could be an ace high straight
    return ( std::all_of(faces.begin(), faces.end(), [](Face f)
    {
        switch (f)
        {
        case Face::ACE:
        case Face::TEN:
        case Face::JACK:
        case Face::QUEEN:
        case Face::KING:
            return true;
        default:
            return false;
        }
    }));

}

bool Hand::isThreeOfAKind() const
{
    std::map<Face, int> faces;
    for (auto cptr : _hand)
        faces[cptr->_face]++;

    return std::any_of(faces.begin(),
                       faces.end(),
                       [](std::pair<Face, int> e){return e.second == 3;});
}


bool Hand::isTwoPair() const
{
    std::map<Face, int> faces;
    for (auto cptr : _hand)
        faces[cptr->_face]++;

    return (2 == std::count_if(faces.begin(),
                               faces.end(),
                               [](std::pair<Face,int> e){return e.second == 2;} )
            );


}

bool Hand::isJacksOrBetter() const
{
    std::map<Face, int> faces;
    for (auto cptr : _hand)
        faces[cptr->_face]++;

    return std::any_of(faces.begin(),
                       faces.end(),
                       [](std::pair<Face,int> e){
                           return (e.second == 2 && e.first >= Face::JACK);
                       }
    );

}

bool Hand::isPair() const
{
    std::map<Face, int> faces;
    for (auto cptr : _hand)
        faces[cptr->_face]++;

    return std::any_of(faces.begin(),
        faces.end(),
        [](std::pair<Face, int> e) {return e.second == 2; });
}




PokerHand Hand::rank() const
{
     if (isRoyalFlush())
         return PokerHand::ROYAL_FLUSH;
     if (isStraightFlush())
         return PokerHand::STRAIGHT_FLUSH;
     if (isFourOfAKind())
         return PokerHand::FOUR_OF_A_KIND;
     if (isFullHouse())
         return PokerHand::FULL_HOUSE;
     if (isFlush())
         return PokerHand::FLUSH;
     if (isStraight())
         return PokerHand::STRAIGHT;
     if (isThreeOfAKind())
         return PokerHand::THREE_OF_A_KIND;
     if (isTwoPair())
         return PokerHand::TWO_PAIR;
     if (isJacksOrBetter())
         return PokerHand::JACKS_OR_BETTER;


    return PokerHand::NADA;
}
