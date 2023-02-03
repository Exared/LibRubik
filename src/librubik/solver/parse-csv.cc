#include "parse-csv.hh"

#include <fstream>
#include <iostream>
#include <sstream>

namespace rubik::solver
{
    std::vector<std::vector<std::string>> parse_csv(const std::string& f)
    {
        std::ifstream input;
        input.open(f);
        if (!input.is_open())
        {
            throw std::ios_base::failure("Error opening file");
        }
        std::string line;
        std::string word;
        std::vector<std::vector<std::string>> res;
        while (std::getline(input, line))
        {
            std::vector<std::string> vec;
            std::stringstream iss(line);
            while (std::getline(iss, word, ','))
            {
                vec.push_back(word);
            }
            res.push_back(vec);
        }
        return res;
    }

} // namespace rubik::solver
