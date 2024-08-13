#pragma once

# include "SparseHN.hpp"

class Shell
{
    private :
        SparseHN    _hnet;

        Shell(Shell const &a);
        Shell   &operator=(Shell const &a);

    public :
        Shell();
        ~Shell();

        void run_shell();
};