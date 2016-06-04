///////////////////////////////////////////////////////////////////////
// File:  Hand.h
// Author:
// This assignment represents my own work and is in accordance with the College Academic Policy
//
// Copyright (c) 2013 All Right Reserved by Dave Burchill
// Contributors:
// Description:
// Hand class holds the cards in the current hand, and knows the rules to rank hand and claculate payout
//
// Date: Sept 2013
//
// Revisions:
//
/////////////////////////////////////////////////////////////////


#ifndef HAND_H
#define HAND_H

#include <string>
#include <vector>
#include <map>
#include <memory>



// forward definitions
struct Card;
using CardPtr = std::shared_ptr<Card>;
class Deck;


enum class PokerHand {ROYAL_FLUSH, STRAIGHT_FLUSH, FOUR_OF_A_KIND, FULL_HOUSE, FLUSH, STRAIGHT, THREE_OF_A_KIND, TWO_PAIR, JACKS_OR_BETTER, NADA};

class Hand
{
public:

    Hand();
    ~Hand();

    std::string toString() const;
    PokerHand rank() const;       // return the rank of the current hand
    void showPayTable() const;
    int payOut() const;            // pay out for this hand

    void dealNewHand(Deck &deck);
    void addCard(CardPtr card);
    void clearHand();
    void addCard(Deck &deck);
    void showDraw();
    bool chooseDraw();
    void drawCards(Deck &);
    void removeCard(int index); //remove card at index
    void print() const;


    //////////////////////////////////////////
    // scoring methods
    //
    //  to be implemented using algorithms
    //////////////////////////////////////////

    bool isRoyalFlush() const;
    bool isStraightFlush() const;
    bool isFourOfAKind() const;
    bool isFullHouse() const;
    bool isFlush() const;
    bool isStraight() const;
    bool isThreeOfAKind() const;
    bool isTwoPair() const;
    bool isJacksOrBetter() const;
    bool isPair() const;


private:
    std::vector<CardPtr> _hand; // current hand
    std::vector<bool> _drawCard;        // draw or hold flag

    // static maps to hold pay sheet and hand names, must be populated in implementation (.cpp) file.
    static const std::map<PokerHand, int> paySheet;
    static const std::map<PokerHand, std::string> handNames;
};

#endif
