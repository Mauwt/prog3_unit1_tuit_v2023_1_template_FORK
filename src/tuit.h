//
// Created by rudri on 10/11/2020.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#ifndef PROG3_UNIT1_TUIT_V2023_1_TUIT_H
#define PROG3_UNIT1_TUIT_V2023_1_TUIT_H


class Element{
private:
    int id = 0;
public:
    //Constructor
    Element() = default;
    Element(int _id): id(_id){};


    //Destructor
    virtual ~Element(){};

    //Methods
    virtual void show(std::ostream& os) = 0;
};

class Media:public Element{
private:
    std::string file_name;
public:
    Media()=default;
    Media(int _id, std::string _filename) : Element(_id), file_name(_filename){}
    Media(const Media& other) : Element(other), file_name(other.file_name) {}
    Media(Media&& other) : Element(std::move(other)), file_name(std::move(other.file_name)) {}

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
    Emoji(int _id, std::string _simbol, int _sz): Element(_id), simbol(_simbol), size(_sz){}
    //Emoji(const Emoji& other) : Element(other), size(other.size), simbol(other.simbol) {}
    Emoji(Emoji&& other) noexcept : Element(std::move(other)), size(std::move(other.size)), simbol(std::move(other.simbol)) {}



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
    Poll(int _id, std::string _title, std::vector<std::string> _choices, int _days, int _hours, int _minutes) : Element(_id),
                                                                                                                title(_title),choices(_choices),days(_days), hours(_hours), minutes(_minutes){}
    Poll(const Poll& other) : Element(other), title(other.title), choices(other.choices), days(other.days), hours(other.hours), minutes(other.minutes) {}
    Poll(Poll&& other) : Element(std::move(other)), title(std::move(other.title)), choices(std::move(other.choices)), days(std::move(other.days)), hours(std::move(other.hours)), minutes(std::move(other.minutes)) {}

    //methods
    void show (std::ostream& os) override;
};

class Tuit{
private:
    std::string user_name;
    std::string text;
    std::vector<Element*> elements; //Polimorfismo: coleccoines polimorficas -> media, emoji, poll
    std::vector<Tuit> replies;
public:
    //Constructors
    Tuit()=default;
    Tuit(std::string _user_name, std::string _text): text(_text), user_name(_user_name){};
    Tuit(const Tuit& other){
        user_name = other.user_name;
        text = other.text;

        for (const auto& elem : other.elements){
            elements.push_back(elem);
            /*if (dynamic_cast<Emoji*>(elem)){
                elements.push_back(elem);
            }
            else if (dynamic_cast<Media*>(elem)){
                elements.push_back(elem);
            }
            else if (dynamic_cast<Poll*>(elem)){
                elements.push_back(elem);
            }*/
        }

        for(const auto& reply:other.replies){
            replies.push_back(reply);
        }
    }
    Tuit(Tuit&& other) noexcept{
        user_name = std::move(other.user_name);
        text = std::move(other.text);
        elements = std::move(other.elements);
        replies = std::move(other.replies);
    }


    //Methods
    Tuit& add_element(Element* e);
    Tuit& add_reply(Tuit r);
    Tuit& show(std::ostream& os);

    void save_to(std::string file_name);
    void load(std::string file_name);

    friend std::ostream& operator<<(std::ostream& out, Tuit& tuit);
    friend void operator>>(std::ifstream& in, Tuit& tuit);

};


#endif //PROG3_UNIT1_TUIT_V2023_1_TUIT_H
