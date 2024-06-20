
#ifndef LAB2_EXCEPTIONS_H
#define LAB2_EXCEPTIONS_H

#include <exception>
#include <iostream>
#include <string>

class IndexOutOfRange: public std::exception {
private:
    std::string message;
public :
    explicit IndexOutOfRange(){
        message = "Error IndexOutOfRange";
    };

    const char* what() const throw() override
    {
        return message.c_str();
    }
};

class EmptyListException: public std::exception{
private:
    std:: string message ;
public:
    explicit EmptyListException(){
        message = "Error ListIsEmpty";
    }
    const char* what()  const throw() override
    {
        return message.c_str();
    }
};

#endif //LAB2_EXCEPTIONS_H
