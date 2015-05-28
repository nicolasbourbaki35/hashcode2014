#include <iostream>
#include <memory>
#include <vector>
#include <fstream>
#include <unordered_set>
#include <list>

////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
class Command
{
public:
    virtual void print() = 0;
};

using CommandPtr = std::shared_ptr<Command>;

////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
class CommandPaint : public Command
{
public:
    CommandPaint(int cx, int cy, int S) : m_cx(cx), m_cy(cy), m_S(S)
    {}
    
    void print() override 
    { 
        std::cout << "Paint(" << m_cx << "," << m_cy << "," << m_S << ")" << std::endl;
    }

private:
    int m_cx, m_cy, m_S;
};


class CommandClear : public Command
{
public:
    CommandClear(int x, int y) : m_x(x), m_y(y)
    {}

    void print() override 
    { 
        std::cout << "Clear(" << m_x << "," << m_y << ")" << std::endl;
    }

private:
    int m_x, m_y;
};


////////////////////////////////////////////////////////
//
////////////////////////////////////////////////////////
class Cell
{
public:
    Cell(int x = 0, int y = 0) : m_x(x), m_y(y) {}
    Cell(int x, int y, CommandPtr c) : m_x(0), m_y(0), m_Command(c) {}

    CommandPtr command() { return m_Command; };

private:
    int m_x, m_y;
    CommandPtr m_Command;
};

using VectorCell = std::vector<Cell>;
using VectorBool = std::vector<bool>;
using Playground = std::vector<VectorBool>;
using Cells = std::vector<VectorCell>;
using Commands = std::list<CommandPtr>;

Cells      CELLS;
Commands   COMMANDS;
Playground PLAYGROUND; 

const char HASH = '#';
const char POINT = '.';
uint32_t WIDTH, HEIGHT;

bool initCells(std::string const & path)
{
    try
    {
        std::ifstream f(path);
        
        if (f.is_open())
        {
            f >> HEIGHT >> WIDTH;
            
            std::cout << " Loading file " << path << " WIDTH=" << WIDTH << " HEIGHT=" << HEIGHT << std::endl;
            
            CELLS.resize(HEIGHT);
            PLAYGROUND.resize(HEIGHT);

            std::string line;
            uint32_t current_line = 0;

            std::getline(f, line); 

            while (std::getline(f, line) && current_line<HEIGHT)
            {
                if (line.length() != WIDTH)
                {
                    std::cerr << " Line " << current_line << " wrong length " << line.length() << ". Expected length " << WIDTH << std::endl;
                    return  false;
                }
                
                uint32_t column = 0;
                for(auto c : line)
                {
                    if (c == HASH)
                    {
                        auto command = std::make_shared<CommandPaint>(current_line, column, 0);
                        COMMANDS.push_back(command);
                        CELLS.at(current_line).push_back(Cell(current_line, column, command));  
                        PLAYGROUND.at(current_line).push_back(true);
                    }
                    else if (c == POINT)
                    {
                        CELLS.at(current_line).push_back(Cell(current_line, column));  
                        PLAYGROUND.at(current_line).push_back(false);
                    }
                    else
                    {
                        std::cerr << "Wrong character " << c << " at " << line << " : " << column;
                    }
                    column++;
                }

                current_line++;
            }
            
            std::cout << "File loaded " << CELLS[0].size() << ":" << CELLS.size() << std::endl;
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

void printCommands()
{
    std::cout << COMMANDS.size() << std::endl;
    for (auto c : COMMANDS)
    {
        c->print();
    }
}

void findCurrentMetrics(uint32_t i0, uint32_t j0, uint32_t s,  uint32_t & current_number_of_commands, uint32_t & number_of_hashed_cells)
{
    current_number_of_commands = 0;
    number_of_hashed_cells = 0;

    std::unordered_set<CommandPtr> processed_commands;

    for(uint32_t i = 0; i<s; ++i)
    {
        for(uint32_t j = 0; j<s; ++j)
        {
            auto c = CELLS[i+i0][j+j0].command();
            if (c)
            {
                auto it = processed_commands.find(c);
                if(it==processed_commands.end())
                {
                    ++current_number_of_commands;
                    processed_commands.insert(c);
                }
            }
            
            if (PLAYGROUND[i+i0][j+j0] == true)
                ++number_of_hashed_cells;
        }
    }
}

void removeUnreferencedCommands()
{
    auto i = COMMANDS.begin();
    std::cout << "size_before " << COMMANDS.size();
    while (i != COMMANDS.end()) 
    {
        if (i->unique())
        {
            COMMANDS.erase(i++);
        }
        else
            ++i;
    }
    std::cout << "size_after " << COMMANDS.size()  << std::endl;
}

void updateCells(uint32_t i0, uint32_t j0, uint32_t s)
{
    auto paint_square = std::make_shared<CommandPaint>(i0 + s / 2, j0 + s / 2, (s - 1) / 2);
    COMMANDS.push_back(paint_square);

    for(uint32_t i = 0; i<s; ++i)
    {
        for(uint32_t j = 0; j<s; ++j)
        {
            if (PLAYGROUND[i+i0][j+j0] == true)
            {
                CELLS[i+i0][j+j0] = Cell(i+i0,j+j0, paint_square);
            }
            else
            {
                auto clear_cell = std::make_shared<CommandClear>(i + i0, j + j0);
                CELLS[i+i0][j+j0] = Cell(i+i0,j+j0, clear_cell);
                COMMANDS.push_back(clear_cell);
            }
        }
    }
    
}

bool resolveSubproblem(uint32_t i0, uint32_t j0, uint32_t s)
{   
    uint32_t current_number_of_commands = 0, number_of_hashed_cells = 0;
    
    findCurrentMetrics(i0, j0, s, current_number_of_commands, number_of_hashed_cells);

    uint32_t how_many_commands_i_can_do = s * s - number_of_hashed_cells + 1;
    
    if (how_many_commands_i_can_do < current_number_of_commands)
    {    
        updateCells(i0, j0, s);
        return true;
    }
    
    return false;
}



int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Usage: \n\t" << argv[0] << " : <input_file>" << std::endl;
        exit(0);
    }

    initCells(argv[1]);
    std::cout << "==================== Subproblem size  =  1" << std::endl; 
    printCommands();

    uint32_t s = 1, size = 2*s+1;

    while (size<=WIDTH && size<=HEIGHT)
    { 
        for(uint32_t i = 0 ; i<=HEIGHT-size; /*++i*/ i+=size)
        {
            for(uint32_t j = 0 ; j<=WIDTH-size; /*++j*/ j+=size)
            {
                resolveSubproblem(i, j, size);
            }
        }
        
        removeUnreferencedCommands();
        std::cout << "==================== Subproblem size  = " << 2 * s + 1 << std::endl; 
        printCommands();

        ++s;
        size = 2*s+1;
    }

    return 0;
}

