#include "pch.h"
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
            tree(entry, level + 1);
        }
        else if (entry.is_regular_file()) {
            files++;
            std::string line;
            std::fstream reader;
            reader.open(entry);

            for (lines = 0; std::getline(reader, line); lines++);

            reader.close();
        }
        else
            continue;

        total_lines += lines;
    }

    TOTAL_FILES += files;
    TOTAL_LINES += total_lines;
}

void app() {
    std::string sciezka = "test.txt";

    std::cout << "----------" << std::endl;
    tree(sciezka);

    std::cout << "Total number of files: " << TOTAL_FILES << std::endl;
    std::cout << "Total number of lines: " << TOTAL_LINES << std::endl;
}

TEST(TestCaseName, TestName) {
  EXPECT_EQ(1, 1);
  EXPECT_TRUE(true);
}

TEST(TotalNumberTests, TotalFilesTest) {
    EXPECT_EQ(0, TOTAL_FILES);
}

TEST(TotalNumberTests, TotalLinesTest) {
    EXPECT_EQ(0, TOTAL_LINES);
}

int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}