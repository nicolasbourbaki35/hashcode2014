#include "Validator.h"

#include <iostream>
#include <fstream>

const char HASH = '#';
const char POINT = '.';

bool Validator::validate(Program const & program)
{
    return true;
}

bool Validator::exportToTga(std::string const & path, Table const & table)
{
    auto i=0u, j = 0u;
    TGAImage image(table[0].size(), table.size(), 1);
    
    for(auto line : table)
    {
        for (auto c: line)
        {
            if(c == true)
            {
                image.set(i,j, TGAColor(128,128,128));
            }
            ++j;  
        }
        ++i;
    }
    image.write_tga_file(path.c_str());
    return true;
}
   
bool Validator::loadInput(std::string const & path, Table & table)
{
    try
    {
        std::ifstream f(path);
        
        if (f.is_open())
        {
            uint32_t width, height;
            
            f >> width >> height;
           
            std::cout << " Loading file " << path << " width=" << width << " height=" << height << std::endl;
            
            table.resize(height);       

            std::string line;
            int current_line = 0;

            while (std::getline(f, line) && current_line<height)
            {
                if (line.length() != width)
                {
                    std::cerr << " Line " << height << " wrong length " << line.length() << ". Expected length " << width << std::endl;
                    return  false;
                }
                
                uint32_t column = 0;
                for(auto c : line)
                {
                    if (c == HASH)
                    {
                        table.at(current_line).push_back(true);    
                    }
                    else if (c == POINT)
                    {
                        table.at(current_line).push_back(false); 
                    }
                    else
                    {
                        std::cerr << "Wrong character " << c << " at " << line << " : " << column;
                    }
                    column++;
                }

                current_line++;
            }
        }
        else
        {
            std::cerr << "Input file " << path << " not found";
            return false;
        }
    }
    catch (std::exception & ex)
    {
        std::cerr << "Exception: " << ex.what() << std::endl;
        return false;
    }
    return true;
}
