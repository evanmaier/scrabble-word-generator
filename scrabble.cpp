/* scrabble.cpp
  CSC 116 - Fall 2018
 
  Complete the implementations of each of the functions below (declared in scrabble.hpp)

  Evan Maier - V00891872 - 10/23/2018
*/

#include <iostream>
#include <set>
#include <vector>
#include <map>
#include "scrabble.hpp"



ScrabbleSolver::ScrabbleSolver(){

}

void ScrabbleSolver::add_word( std::string const& word ){
if(dictionary.count(word)==0)
   {
       dictionary.insert(word);
   }else
   {
       throw std::runtime_error("word already in dictionary");
   }  
}

ScoreMap ScrabbleSolver::get_score_map(){
for(auto const& word : dictionary)
{
   scoreMap.insert({word,compute_score(word)});
}
return scoreMap;
}

ScoreMap ScrabbleSolver::find_words( TileSet const& tiles ){
ScoreMap subMap;//map of all posible words and their scores given a set of tiles
get_score_map();
for(auto const& word : dictionary)
{
   if(can_make_word(word,tiles))
   {  
       subMap.insert({word,scoreMap.at(word)});//put word and score in submap
   }
}
return subMap;
}

ScoreMap ScrabbleSolver::find_best_words( TileSet const& tiles ){
int bestScore {0};
ScoreMap bestMap;//map of best words with their scores (given a set of tiles)
ScoreMap subMap = find_words(tiles);

for(auto const& [word,score] : subMap)
{
   if(score>bestScore)
   {
       bestScore = score;
   }
}


for(auto const& [word,score] : subMap)
{
   if(score == bestScore)
   {
       bestMap.insert({word,score});
   }
}

return bestMap;
}

/* Static methods */


int ScrabbleSolver::compute_score( std::string const& word ){
int score{0}; //score to return
for(auto const& letter : word)
{
    switch (letter){
                
        case 'a': score += 1; break;
        case 'e': score += 1; break;
        case 'i': score += 1; break;
        case 'l': score += 1; break;
        case 'n': score += 1; break;
        case 'o': score += 1; break;
        case 'r': score += 1; break;
        case 's': score += 1; break;
        case 't': score += 1; break;
        case 'u': score += 1; break;     
        case 'd': score += 2; break;
        case 'g': score += 2; break;
        case 'b': score += 3; break;
        case 'c': score += 3; break;
        case 'm': score += 3; break;
        case 'p': score += 3; break;
        case 'f': score += 4; break;
        case 'h': score += 4; break;
        case 'v': score += 4; break;
        case 'w': score += 4; break;
        case 'y': score += 4; break; 
        case 'k': score += 5; break;
        case 'j': score += 8; break;
        case 'x': score += 8; break;
        case 'q': score += 10; break;
        case 'z': score += 10; break;
    }
}
return score;
}

bool ScrabbleSolver::can_make_word( std::string const& word, TileSet const& tiles ){
struct letter{
   bool isUsed{0};
   char letter;
};
std::vector<letter> letters;
{
for(auto const& tile : tiles)//makes a letter struct for each tile
{  
   letter lett{0,tile};
   letters.push_back(lett);
}
}
for(auto const& ch : word)//for each letter in word
{
   bool isFound{0};
   for(auto& lett: letters)//for each letter in letters(vector of letter structs)
   {
       if(ch==lett.letter && !lett.isUsed)
       {
           lett.isUsed=true;//mark lett as used
           isFound=true;
           break;//go to next letter of word
       }
   }
   if(!isFound)
   {
       return false;
   }
}
return true;
}

