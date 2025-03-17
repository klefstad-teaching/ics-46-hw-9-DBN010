#include "ladder.h"
#include <cmath>

void error(string word1, string word2, string msg){
	std::cout << word1 << word2 << msg << std::endl;
}

bool edit_distance_within(const std::string& str1, const std::string& str2, int d){
	int len1 = str1.size();
	int len2 = str2.size();

	if(std::abs(len1 - len2) > d){
		return false;
	}

	int i = 0, j = 0, edits = 0;

	while(i < len1 && j < len2){
		if(str1[i] != str2[j]){
			if(++edits > d){
				return false;
			}

			if(len1 > len2){
				++i;
			}

			else if(len1 < len2){
				++j;
			}
			else{
				++i;
				++j;
			}
		}
		else{
			++i;
			++j;
		}
	}

	edits += (len1 - i) + (len2 - j);
	return edits <= d;
}

bool is_adjacent(const string& word1, const string& word2){
	return edit_distance_within(word1, word2, 1);
}

vector<string> generate_word_ladder(const string& begin_word, const string& end_word, const set<string>& word_list){
	queue<vector<string>> ladder_queue;
	set<string> visited;

	ladder_queue.push({begin_word});
	visited.insert(begin_word);

	while(!ladder_queue.empty()){
		vector<string> current_ladder = ladder_queue.front();
		ladder_queue.pop();

		string last_word = current_ladder.back();

		for(const string& word : word_list){
			if(is_adjacent(last_word, word) && visited.find(word) == visited.end()){
				vector<string> new_ladder = current_ladder;
				new_ladder.push_back(word);

				if(word == end_word){
					return new_ladder;
				}

				visited.insert(word);
				ladder_queue.push(new_ladder);
			}
		}
	}
	return {};
}

void load_words(set<string>& word_list, const string& file_name){
	ifstream file(file_name);
	if(!file){
		error("", "", "Could not open file");
		return;
	}
	string word;
	while(file >> word){
		word_list.insert(word);
	}
	file.close();
}

void print_word_ladder(const vector<string>& ladder){
	if(ladder.empty()){
		error("", "", "No word ladder found.");
		return;
	}
	cout << "Word ladder found: ";
	for(size_t i = 0; i < ladder.size(); ++i){
		cout << ladder[i] << " ";
	}
	cout << endl;
}

#define my_assert(e) {cout << #e << ((e) ? " passed": " failed") << endl;}
void verify_word_ladder(){
	set<string> word_list;
	load_words(word_list, "words.txt");
	my_assert(generate_word_ladder("cat", "dog", word_list).size() == 4);
	my_assert(generate_word_ladder("marty", "curls", word_list).size() == 6);
    my_assert(generate_word_ladder("code", "data", word_list).size() == 6);
    my_assert(generate_word_ladder("work", "play", word_list).size() == 6);
    my_assert(generate_word_ladder("sleep", "awake", word_list).size() == 8);
    my_assert(generate_word_ladder("car", "cheat", word_list).size() == 4);
}
