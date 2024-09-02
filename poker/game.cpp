#include <iostream>
#include <array>
#include <string>
#include <algorithm>
#include <limits>

#include "Random.h"

namespace Settings{
    // The dealer repeatedly draws until they reach a score of 17 or more,
    // at which point they must stop drawing.
    constexpr int minDealerScore {17};

    // if the dealer/player goes over a score of 21, they bust and other wins immediately.
    constexpr int maxBustScore {21};

}

struct Card
{
    enum Rank
    {
        rank_ace,
        rank_2,
        rank_3,
        rank_4,
        rank_5,
        rank_6,
        rank_7,
        rank_8,
        rank_9,
        rank_10,
        rank_jack,
        rank_queen,
        rank_king,

        max_ranks,
    };

    enum Suit
    {
        suit_clubs,
        suit_diamonds,
        suit_hearts,
        suit_spades,

        max_suits,
    };

    Rank m_rank{};
    Suit m_suit{};

    static constexpr int deckSize {52};

    static constexpr std::array allRanks { 
        rank_ace, rank_2, rank_3, rank_4, rank_5, rank_6, rank_7, rank_8, rank_9, 
        rank_10, rank_jack, rank_queen, rank_king,
    };

    static constexpr std::array allSuits {
        suit_clubs,
        suit_diamonds,
        suit_hearts,
        suit_spades,
    };

    friend std::ostream& operator<<(std::ostream& out, const Card& card)
    {
        static constexpr std::array rankDefinations {'A', '2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K'};
        static constexpr std::array suitsDefinations {'C', 'D', 'H', 'S'};

        out << rankDefinations[card.m_rank] << suitsDefinations[card.m_suit] << ' ';
        return out;
    }

     int value() const
    {
        static constexpr std::array rankValues { 11, 2, 3, 4, 5, 6, 7, 8, 9, 10, 10, 10, 10 };
        return rankValues[m_rank];
    }
};

class Deck
{
    public: 
        explicit Deck() : m_cards{}
        {
            for (std::size_t i {0}; i < Card::allSuits.size(); ++i)
                for (std::size_t j {0}; j < Card::allRanks.size(); ++j)
                    m_cards[i*j]  = { Card::allRanks[j], Card::allSuits[i] };
        }

        const Card dealCard();
        void shuffle();

    private:
        std::array<Card, Card::deckSize> m_cards {};
        std::size_t m_currentCardIndex {0};
};

// dealCard returns the next card in the deck by value.
const Card Deck::dealCard() {
    if (m_currentCardIndex >= Card::deckSize)
        m_currentCardIndex = 0;
    else 
        ++m_currentCardIndex;

    return m_cards[m_currentCardIndex];
}

// Shuffle it reorganizes the deck and reset the tracking card index back to zero.
void Deck::shuffle()
{
    m_currentCardIndex = 0;
    std::shuffle(m_cards.begin(), m_cards.end(), Random::mt);
}

struct Player
{
    int score{};
};

bool isPlayerHits()
{
    std::cout << "(h) to hit, or (s) to stand: ";
    char input{};

    while(true)
    {
        std::cin >> input;

        if (!std::cin)
            std::cin.clear();

        if (!std::cin.eof() && std::cin.peek() != '\n')
            input = {};
        
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        if (input == 'h')
            return true;
        else if (input == 's')
            return false;
        else
            std::cout << "Invalid input used. Please Try Again!: ";
    }

}

bool playBlackJack(Deck& deck, Player& dealer, Player& randPlayer)
{
    dealer.score += deck.dealCard().value(); // Dealer round One
    randPlayer.score += deck.dealCard().value(); // Me round One
    dealer.score += deck.dealCard().value(); // Dealer round Two

    std::cout << "The dealer is showing: " << dealer.score << '\n';
    std::cout << "You have score: " << randPlayer.score << '\n';

    // Rand player repeatedly “hit” or “stand”.
    // “hits”, gets another card and whose value added to their total score.
    // “stands”, their turn is over, and their score is calculated based on the
    // cards they have been dealt.

    Card flippedCard {};

    // Player cannot draw more cards after they have a score of more than 21. 
    while(randPlayer.score < Settings::maxBustScore && isPlayerHits())
    {
        flippedCard = deck.dealCard();
        randPlayer.score += flippedCard.value();

        std::cout << "You were dealt " << flippedCard 
                    << ". You now have: " << randPlayer.score << '\n';
    }

    if (randPlayer.score > Settings::maxBustScore)
    {
        std::cout << "You went bust!\n";
        return false;
    }

    // Dealer flipping cards till they have a score of more 17.
    while(dealer.score < Settings::minDealerScore) {
        flippedCard = deck.dealCard();
        dealer.score += flippedCard.value();

        std::cout << "The dealer flips a " << flippedCard 
                    <<". They now have: " << dealer.score << '\n';
    }

    if (dealer.score > Settings::maxBustScore)
    {
        std::cout << "The dealer went bust!\n";
        return true;
    }
    return randPlayer.score > dealer.score;
}


int main()
{
    Deck deck{};
    deck.shuffle();
    deck.shuffle();
    deck.shuffle();

    Player dealer{};
    Player randomPlayer{};

    if (playBlackJack(deck, dealer, randomPlayer))
        std::cout << "You win!\n";
    else 
        std::cout << "You lose!\n";

    return 0;
}