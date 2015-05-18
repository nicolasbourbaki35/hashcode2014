#include <vector>
#include <fstream>
#include <iostream>
#include <sstream>

using Out = std::vector<std::vector<char> >;

int main(int argc, char ** argv)
{
    if(argc < 3)
    {
        std::cout << "Usage: \n\t" << argv[0] << " : " << " <program_file> <height> <width>" << std::endl;
        exit (0);
    }
    
    std::ifstream f(argv[1]);

    int HEIGHT = atoi(argv[2]);
    int WIDTH = atoi(argv[3]);

    Out o;
    o.resize(HEIGHT);
    for(auto &v : o)
    {
        v.assign(WIDTH, '.');
    }

    if (f.is_open())
    {
        std::string line;
    
        std::getline(f, line); 
    
        while (std::getline(f, line))
        {
            if (line.find("Paint") == 0 )
            {
                auto open = line.find('(');
                auto close = line.find(')');
                auto params = line.substr(open+1, close - open -1);
                std::vector<int> p;                

                std::stringstream ss(params);
                int iii;
                while(ss >> iii)
                {
                    p.push_back(iii);
                    if (ss.peek() == ',')
                        ss.ignore();
                }

                int i0 = p[0];
                int j0 = p[1];
                int s0 = p[2];
                
                for (int i = 0; i<2*s0+1; i++)
                {
                    for (int j = 0; j<2*s0+1; j++)
                    {
                        o[i0 - (2*s0 + 1) / 2  + i][j0 - (2*s0 + 1) / 2 + j] = '#';
                    }
                }
            }
            else if (line.find("Clear") == 0 )
            {
                auto open = line.find('(');
                auto close = line.find(')');
                auto params = line.substr(open+1, close - open -1);
                
                std::vector<int> p;                

                std::stringstream ss(params);
                int iii;
                while(ss >> iii)
                {
                    p.push_back(iii);
                    if (ss.peek() == ',')
                        ss.ignore();
                }         
                
                int i0 = p[0];
                int j0 = p[1];

                o[i0][j0] = '.';                
            }
        }
    }
    
    std::cout << HEIGHT << " " << WIDTH << std::endl;
    for (auto & l : o)
    {
        for(auto & c : l)
        {
            std::cout << (char)c; 
        }

        std::cout << std::endl; 
    } 
}

