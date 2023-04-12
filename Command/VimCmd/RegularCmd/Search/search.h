#ifndef SEARCH_H
#define SEARCH_H

#include "../regularcmd.h"

class Search: public RegularCmd {
    public:
        std::string word;
        virtual ~Search() = 0;
};


/**- ? -**/
class SearchLeft: public Search {
    void executeOnce(Model &editor) const override;
};

class SearchRight: public Search {
    void executeOnce(Model &editor) const override;
};


#endif


