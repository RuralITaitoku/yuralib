#include <vector>
#include <sqlite3.h>
#include <iostream>

#pragma once



class yura_sqlite {
    private:
        sqlite3 *db;
    public:
        enum ErrorCode {
            OK = 0,
            ERR_OPEN = 1,
            ERR_SQL = 2,
        };
        std::string err_msg;
    
        yura_sqlite();
        ~yura_sqlite();
    
        int open(const char *file_name);
        std::string sqltext(const std::string& sql);
        int create_table(const std::string &table_name
                        , const std::vector<std::string> &columns);
        int insert(const std::string &table_name
                        , const std::vector<std::string> &columns
                        , const std::vector<std::string> &values);
        int insert(const std::string &table_name
                        , const std::vector<std::string> &columns
                        , const std::vector<std::vector<std::string> > &values);
        int update(const std::string &table_name
                , const std::vector<std::string> &columns
                , const std::vector<std::string> &values
                , const std::string &where);
    
    
        int exec(const std::string &sql
                        , const std::vector<std::vector<std::string> > &values);
        int exec(const std::string &sql);
        int select(const std::string &sql, 
                    std::vector<std::vector<std::string> > &result_data);
        void close();
    };
    