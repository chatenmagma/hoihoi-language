#include "ast/ast.hpp"
#include "parser/ast_builder.hpp"
#include "vm/state.hpp"
#include "compiler/compiler.hpp"

#include <iostream>
#include <fstream>

using namespace hoihoi;
using namespace std;

int run_file(const string& path_file) {
    ifstream file(path_file);

    if(!file.is_open()) {
        cerr << "The file is not exist..." << endl;
        return 1;
    }

    string source;
    string line;

    while(getline(file, line)) source += line + '\n';

    return State().execute(source);
}

int main(int argc, char** argv) {
    if(argc != 2) {
        cerr << "You must specify your file .hoi" << endl;
        return 1;
    }

    return run_file(argv[1]);
}
