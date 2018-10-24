/* scrabble_interactive.cpp

   A program which reads a file containing a list of words, then repeatedly prompts
   the user for a set of tiles, which are provided to a ScrabbleSolver instance to
   compute either all words which can be created from the tiles, or only the
   words with the highest score.

   To use this tester, compile with
     g++ -pedantic -Wall -Wextra -std=c++17 -o scrabble_interactive scrabble.cpp scrabble_interactive.cpp
   then run with the command
     scrabble_interactive mode word_file
   where mode is either "all" (compute all words for each tile set) or "best" (compute
   only the best-scoring words for each tile set).

   B. Bird - 09/26/2018
*/

#include <iostream> 
#include <fstream> 
#include <string>
#include "scrabble.hpp"



int main(int argc, char** argv){
    if (argc < 3){
        std::cout << "Usage: " << argv[0] << " mode word_file" << std::endl;
        return 1;
    }
    std::string mode = argv[1];
    std::string filename = argv[2];

    if (mode != "all" && mode != "best"){
        std::cout << "Error: mode must be either \"all\" or \"best\"" << std::endl;
        return 1;
    }

    std::ifstream word_file;
    word_file.open(filename);
    if (!word_file.is_open()) {
        std::cout << "Unable to open input file" << std::endl;
        return 1;
    }

    ScrabbleSolver solver {};

    std::string word;
    while ( word_file >> word ) {
        solver.add_word(word);
    }
    word_file.close();


    std::string tiles;
    while ( std::cin >> tiles ) {
        std::cout << "Tiles: [" << tiles << "]" << std::endl;
        auto tile_set = ScrabbleSolver::string_to_tileset(tiles);
        ScoreMap result {};
        if (mode == "all")
            result = solver.find_words(tile_set);
        else if (mode == "best")
            result = solver.find_best_words(tile_set);
        int i = 0;
        for (auto word_score_pair: result) {
            auto word = word_score_pair.first;
            auto score = word_score_pair.second;
            i++;
            std::cout << "Solution " << i << ": [" << word << "] - Score " << score << std::endl;
        }
	std::cout << std::endl;
    }
    
    return 0;
}