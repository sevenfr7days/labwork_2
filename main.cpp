#include <iostream>
#include <fstream>


void size_counter(std::string(path)) {
    std::ifstream file;
    file.open(std::string(path), std::ifstream::ate | std::ifstream::binary);
    std::streamoff size = file.tellg();
    file.close();
    std::cout << "File size in bytes: " << size << std::endl;
}

void words_counter(std::string(path)) {
    std::ifstream fin;
    std::string str;
    int words = 0;
    fin.open(std::string(path));
    while (getline(fin, str)) {
        bool is_string = false;
        for (int i = 0; i < str.size(); i++) {
            if (str[i] == ' ' || str[i] == '\n') {
                if (is_string) {
                    words++;
                }
                is_string = false;
            } else {
                is_string = true;
            }
        }
        if (is_string) {
            words++;
        }
    }
    fin.close();
    std::cout << "Count of words: " << words << std::endl;
}

void lines_counter(std::string(path)) {
    int lines = 0;
    std::ifstream fin;
    std::string str;
    fin.open(std::string(path));
    while (getline(fin, str)) {
        lines++;
    }
    std::cout << "Count of lines: " << lines << std::endl;
}

int main(int argc, char *argv[]) {
    std::string path;
    std::string options[argc - 2];

    if (argc == 2) {
        path = argv[1];
        size_counter(path);
        words_counter(path);
        lines_counter(path);
    }
    int ix = 0;
    if (argc >= 3) {
        int point = 0;
        for (int i = 1; i < argc; i++) {
            std::ifstream file(argv[i]);
            if (file.is_open()) {
                path = argv[i];
                point = i;
                std::cout << point << std::endl;
            } else {
                options[ix++] = argv[i];
            }
        }
        for (int i = 0; i < argc - 1; i++) {
            if (options[i].length() == 2) {
                if (options[i] == "-l") {
                    lines_counter(path);
                } else if (options[i] == "-c") {
                    size_counter(path);
                } else if (options[i] == "-w") {
                    words_counter(path);
                }
            } else if (options[i].length() > 2) {
                if (options[i][0] == '-' & options[i][1] == '-') {
                    if (options[i] == "--lines") {
                        lines_counter(path);
                    } else if (options[i] == "--bytes") {
                        size_counter(path);
                    } else if (options[i] == "--words") {
                        words_counter(path);
                    }
                } else if (options[i][0] == '-' & options[i][1] != '-') {
                    for (int j = 1; j < options[i].length() + 1; j++) {
                        char command = options[i][j];
                        if (command == 'l') {
                            lines_counter(path);
                        } else if (command == 'c') {
                            size_counter(path);
                        } else if (command == 'w') {
                            words_counter(path);
                        }
                    }
                }

            }
        }
    }
    return 0;
}