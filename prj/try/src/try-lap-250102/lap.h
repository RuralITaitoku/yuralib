/************************************************************************
*
*  lap.h
   version 1.0 - 21 june 1996
   author  Roy Jonker, MagicLogic Optimization Inc.

   header file for LAP
*
      pyLAPJV by Harold Cooper (hbc@mit.edu)
      2004-08-13:
          -- fixed Jonker's function declarations to actually use row, col,
             and cost types
          -- row, col, and cost now based on basic types
*
**************************************************************************/
#include<vector>

/*************** CONSTANTS  *******************/


extern double lap(const std::vector<std::vector<double>>& assigncost
         , std::vector<int>& rowsol
         , std::vector<int>& colsol
         , std::vector<double>& u
         , std::vector<double>&v);
