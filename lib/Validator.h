#ifndef _VALIDATOR_H_
#define _VALIDATOR_H_

#include "common.h"
#include "tgaimage.h"

class Validator
{
public:

    Validator(std::string & input_path)
    {}

    bool validate(Program const & program);

    static bool exportToTga(std::string const & path, Table const  & table);   
    static bool loadInput(std::string const & path, Table & table);

private:
    std::string m_InputPath;
    Table m_Table;
};

#endif
