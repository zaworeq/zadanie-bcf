#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>


int TOTAL_FILES = 0;
int TOTAL_LINES = 0;


namespace fs = std::filesystem;


void tree(const fs::path& sciezka, int level = 0) {
    int files = 0;
    int lines = 0;
    int total_lines = lines, total_files = files;

    for (const auto& entry : fs::directory_iterator(sciezka)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_directory()) {
            //std::cout << std::setw(level * 3) << "" << filenameStr << '\n';
            tree(entry, level + 1);
        }
        else if (entry.is_regular_file()) {
            files++;
            std::string line;
            std::fstream reader;
            reader.open(entry);

            for (lines = 0; std::getline(reader, line); lines++);

            reader.close();

            //std::cout << std::setw(level * 3) << "" << filenameStr << ", size " << entry.file_size() << " bytes\n";
        }
        else
            continue;
        //std::cout << std::setw(level * 3) << "" << " [?]" << filenameStr << '\n';

    //std::cout << std::setw(level * 3) << "number of files: " << files << std::endl;
    //std::cout << std::setw(level * 3) << "number of lines: " << lines << std::endl;
    //std::cout << std::setw(level * 3) << "----------" << std::endl;

        total_lines += lines;
    }

    TOTAL_FILES += files;
    TOTAL_LINES += total_lines;

}


int main()
{
    std::string sciezka;

    std::cout << "Provide a path:\n";  // I use a path for "test" directory, which is in app folder
    std::cin >> sciezka;

    std::cout << "----------" << std::endl;
    tree(sciezka);

    std::cout << "Total number of files: " << TOTAL_FILES << std::endl;
    std::cout << "Total number of lines: " << TOTAL_LINES << std::endl;

    std::cin.get();
}