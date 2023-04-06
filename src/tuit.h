//
// Created by rudri on 10/11/2020.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#ifndef PROG3_UNIT1_TUIT_V2023_1_TUIT_H
#define PROG3_UNIT1_TUIT_V2023_1_TUIT_H


void question_1();
class Element{
private:
    int id = 0;
public:
    //Constructor
    Element() = default;
    explicit Element(int _id): id(_id){};

    //Methods
    virtual void show(std::ostream& os) = 0;
};

class Tuit{
private:
    std::string user_name;
    std::string text;
    std::vector<Element*> elements;
    std::vector<Tuit> replies;
public:
    //Constructors
    Tuit()=default;
    Tuit(std::string _user_name, std::string _text): text(_text), user_name(std::move(_user_name)){};

    //Methods
    Tuit& add_element(Element* e);
    Tuit& add_reply(Tuit r);
    void show(std::ostream& os);

    void save_to(std::string file_name);
    void load(std::string file_name);

    friend std::ostream& operator<<(std::ostream& out, Tuit& tuit);
    friend std::istream& operator>>(std::istream& in, Tuit& tuit);
    friend std::ifstream in(std::string filename);

};


class Media:public Element{
private:
    std::string file_name;
public:
    Media()=default;
    Media(int _id, std::string filename) : Element(_id), file_name(filename){};

    //Methods
    void  show(std::ostream& os) override;
};

class Emoji: public Element{
private:
    int size=0;
    std::string simbol;
public:
    //Constructors
    Emoji() = default;
    Emoji(int _id, std::string _simbol, int _sz): Element(_id), simbol(_simbol), size(_sz){};


    //Methods
    void show(std::ostream& os) override;
};

class Poll : public Element{
private:
    std::string title;
    std::vector<std::string> choices;
    int days = 0;
    int hours = 0;
    int minutes = 0;

public:
    //Constructor
    Poll() = default;
    Poll(int _id, std::string _title, std::vector<std::string> _choices, int _days, int hours, int minutes);


    //methods
    void show (std::ostream& os) override;
};
#endif //PROG3_UNIT1_TUIT_V2023_1_TUIT_H
