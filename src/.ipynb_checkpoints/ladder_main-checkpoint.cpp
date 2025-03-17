#include "ladder.h"

int main(int argc, char* argv[]) {
    if (argc == 1) {
        // No arguments: run the test cases
        verify_word_ladder();
    } else if (argc == 4) {
        // Arguments provided: generate word ladder
        std::string begin_word = argv[1];
        std::string end_word = argv[2];
        std::string filename = argv[3];
        std::set<std::string> word_list;
        load_words(word_list, filename);
        std::vector<std::string> ladder = generate_word_ladder(begin_word, end_word, word_list);
        print_word_ladder(ladder);
    } else {
        // Incorrect number of arguments
        error("", "", "Usage: ./ladder_main [begin_word end_word filename]");
    }
    return 0;
}