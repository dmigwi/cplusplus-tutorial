#include <iostream>
#include <algorithm>
#include <vector>
#include <string_view>
#include <string>
#include <limits>

#include "random.h"

namespace WorldList
{
    const std::vector<std::string_view> words {
        "mystery", "broccoli" , "account", "almost", "spaghetti", "opinion", "beautiful", "distance", "luggage",
    };

    const std::string_view pickRandomWord()
    {
        std::size_t index { Random::get<std::size_t>(0, words.size()-1) };
        return words[index];
    }
}

class Session
{
    public:
        explicit Session(const std::string_view& randWord = WorldList::pickRandomWord())
            : m_randWord {randWord}, m_guessedLetters{ std::vector<bool>(randWord.length()) }
        {}

        void printGameIntro() const {
            std::cout << "Welcome to C++man (a variant of Hangman)\n";
            std::cout << "To win: guess the word.  To lose: run out of pluses.\n";
        }

        void printUserInputRequest() const {
            std::cout << "\nThe word: ";

           for (std::size_t i {0}; i < m_guessedLetters.size();  ++i) 
            {
                if (m_guessedLetters[i])
                     std::cout << m_randWord[i]; 
                else
                    std::cout << '_'; 
            }

            std::cout << ". Wrong guesses: ";

            for (int k {0}; k < remainingGuesses(); ++k) 
                std::cout << '+';

            std::cout << m_wrongGuesses << '\n';
        }

        bool isAlreadyGuessed(char ch)
        {   
            bool isGuessed { false };
            for (std::size_t i {0}; i < m_randWord.size();  ++i) 
            {
                // if character matches update isGuessed accordingly.
                // Loops till the end to handle duplicates.
                if (ch == m_randWord[i])  
                    isGuessed = m_guessedLetters[i];
            }
            return isGuessed;
        }

        void updateIfGuessedCorrectly(char ch)
        {
            for (std::size_t i {0}; i < m_randWord.size();  ++i) 
            {
                // If the correctly guessed hasn't been matched, match it and exit.
                if ((ch == m_randWord[i]) && !m_guessedLetters[i]) {
                    m_guessedLetters[i] = true;

                    std::cout << "Yes, '" << ch << "' is in the word!\n";
                    return;
                } 
            }

            std::cout << "No, '" << ch << "' is not in the word!";
            m_wrongGuesses += ch;
        }

        int maxIterations() const { return m_maxIterations; }

        int remainingGuesses() const { 
            return  (m_maxIterations - static_cast<int>(m_wrongGuesses.length())); 
        }

        const std::string_view randWord() const  { return m_randWord; }

        bool isGameSolved() const { // returns true if m_guessedLetters is all true.
            return std::all_of(
                m_guessedLetters.begin(), 
                m_guessedLetters.end(), 
                [](bool v) { return v == true; });
            }

    private:
        std::string m_randWord {};
        std::vector<bool> m_guessedLetters {};
        int m_maxIterations { 5 }; // number of iteration user is allowed to keep guessing.
        std::string m_wrongGuesses {};
};

char getUserInput(Session& session)
{
    char input {};
    bool isValidRead { false };

    while(!isValidRead)
    {
        std::cout << "Enter your next letter: ";
        std::cin >> input;

        if (!std::cin) {
            std::cin.clear();
        } 
        
        if (input < 'a' || input > 'z')
            std::cout << "That wasn't a valid input.  Try again.\n"; 
        else if (session.isAlreadyGuessed(input))
            std::cout << "You already guessed that.  Try again.\n"; 
        else 
            isValidRead = true; // exit the reading loop.

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    return input;
}

int main()
{
    Session session {};
    session.printGameIntro();

    // loop until the guesses run out or the game is solved.
    while (true) {
        session.printUserInputRequest();
        session.updateIfGuessedCorrectly(getUserInput(session));

        if (session.remainingGuesses() <= 0)
        {
            std::cout << "\nYou lost! The word was: " << session.randWord() << '\n';
            break;
        }

        if (session.isGameSolved())
        {
            std::cout << "\nCongratulations!! You won! \n";
            break;
        }
    }
   
    return 0;
}