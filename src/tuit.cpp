//
// Created by rudri on 10/11/2020.
//


#include "tuit.h"
#include <fstream>
using namespace std;

//Utils
std::string trim(std::string &&str){
    int first_char = 0, last_char=str.length()-1;

    for (int i = 0; i < str.length();  i++){
        if(str[i] != ' '){
            first_char = i;
            break;
        }
    }

    for (int i = str.length()-1; i>0; i--){
        if(str[i] != ' '){
            last_char = i;
            break;
        }
    }

    str = str.substr(first_char, last_char-first_char+1);
    return str;
}
void trim(std::string &str){
    int first_char = 0, last_char=str.length()-1;

    for (int i = 0; i < str.length();  i++){
        if(str[i] != ' '){
            first_char = i;
            break;
        }
    }

    for (int i = str.length()-1; i>0; i--){
        if(str[i] != ' '){
            last_char = i;
            break;
        }
    }

    str = str.substr(first_char, last_char-first_char+1);
}

//Clase Media
void Media::show(ostream &os) {
    os<<this->file_name<<'\n';
}

//Clase Emoji
void Emoji::show(ostream &os) {
    os<<this->simbol<<'\n';
}

//Clase Poll
void Poll::show(ostream &os) {
    os<<"title : "<< this->title<<'\n';
    os<<"- "<<this->choices[0]<<'\n';
    os<<"- "<<this->choices[1]<<'\n';
    os<<"- "<<this->choices[2]<<'\n';
}



//Clase Tuit
/*Tuit::Tuit(const Tuit &other) {

    text = other.text;
    user_name = other.user_name;
    for(int elem =0; elem < other.elements.size(); elem++) elements.push_back(other.elements[elem]); // Copiar elementos
    for(int tuits =0; tuits<other.replies.size(); tuits++) replies.push_back(other.replies[tuits]); // Copiar replies
}*/
/*
Tuit::Tuit(Tuit&& other) noexcept{
    text = other.text;
    other.text.clear();
    user_name = other.user_name;
    other.user_name.clear();
    for(int elem =0; elem < other.elements.size(); elem++) {
        elements.push_back(other.elements[elem]); // Copiar elementos
        other.elements[elem] = nullptr;
    }
    other.elements.clear();
    for(int tuits =0; tuits<other.replies.size(); tuits++) {
        replies.push_back(other.replies[tuits]); // Copiar replies
    }
    other.replies.clear();
}*/


Tuit &Tuit::add_element(Element *e) {
    elements.push_back(e);
    return *this;
}

Tuit &Tuit::add_reply(Tuit r) {
    replies.push_back(r);
    return *this;
}

Tuit& Tuit::show(ostream &os) {
    os<<"====================\n";
    os<<"@"<<user_name<<'\n';
    os<<text<<'\n';
    os<<"--------------------\n";
    for(auto element:elements){
        element->show(cout);
    }
    for(auto reply:replies){
        reply.show(cout);
    }
    return *this;
}

void Tuit::save_to(std::string file_name) {

}

void Tuit::load(std::string file_name) {


    std::string path =".\\" + file_name;
    std::ifstream tuitFile;


    tuitFile.open(path);
    
    if (!tuitFile.is_open()) {
        cout << "No se pudo abrir el archivo." << endl;
        return;
    }

    std::string line;

    std::vector< std::vector<std::string> > thr;

    int temp_count = 0;
    std::vector<int> replies_idx;

    while(getline(tuitFile, line)){

        int idx = 0, pos = 0;

        std::vector<std::string> temp;
        while(idx<line.length()){
            if (line[idx]!='|')idx++;
            else {
                std::string str =trim(line.substr(pos, idx-pos));
                temp.push_back(str);
                idx++;
                pos = idx;

            }
        }
        temp.push_back(trim(line.substr(pos)));
        thr.push_back(temp);

        if (temp[0] == "Tuit") replies_idx.push_back(temp_count);
        temp_count++;
    }


    this->user_name = thr[0][1];
    this->text = thr[0][2];

    //Bucle para añadir los elementos del Tuit principal
    for (int elm = 1; elm < replies_idx[1];elm++){

        if(thr[elm][0] == "Emoji"){
            Element* emoji = nullptr;
            emoji = new Emoji(stoi(thr[elm][1]), thr[elm][2], stoi(thr[elm][3]));
            this->elements.push_back(emoji);
            continue;

        }else if(thr[elm][0] == "Media"){
            Element* media = nullptr;
            media = new Media(stoi(thr[elm][1]), thr[elm][2]);
            this->elements.push_back(media);
            continue;

        }else if(thr[elm][0] == "Poll"){
            std::vector<std::string> opciones;
            int idx=0, pos =0;

            while(idx < thr[elm][3].length()){
                if (thr[elm][3][idx] != ',') idx++;
                else{
                    opciones.push_back(trim(thr[elm][3].substr(pos, idx - pos)));
                    idx++;
                    pos = idx;
                }
            }
            opciones.push_back(line.substr(pos));

            Element* poll = nullptr;
            poll = new Poll(stoi(thr[elm][1]), thr[elm][2], opciones, stoi(thr[elm][4]), stoi(thr[elm][5]), stoi(thr[elm][6]) );
            this->elements.push_back(poll);
        }
    }

    for (int i = 1; i<replies_idx.size(); i++) {
        Tuit reply(thr[replies_idx[i]][1] , thr[replies_idx[i]][2]);

        int tope ;

        i==replies_idx.size()-1 ? tope= thr.size():tope =replies_idx[i+1];
        for(int j = replies_idx[i]+1; j<tope; j++){

            if(thr[j][0] == "Emoji"){
                Element* emoji = nullptr;
                emoji = new Emoji( stoi(thr[j][1]) , thr[j][2], stoi(thr[j][3]) );
                reply.add_element(emoji);
                continue;

            }
            else if(thr[j][0] == "Media"){
                Element* media = nullptr;
                media = new Media(stoi(thr[j][1]), thr[j][2]);
                reply.add_element(media);
                continue;

            }
            else if(thr[j][0] == "Poll"){
                std::vector<std::string> opciones;
                int idx=0, pos =0;

                while(idx < thr[j][3].length()){
                    if (thr[j][3][idx] != ',') idx++;
                    else{
                        opciones.push_back(trim(thr[j][3].substr(pos, idx - pos)));
                        idx++;
                        pos = idx;
                    }
                }
                opciones.push_back(thr[j][3].substr(pos));

                Element* poll = nullptr;
                poll = new Poll(stoi(thr[j][1]), thr[j][2], opciones, stoi(thr[j][4]), stoi(thr[j][5]), stoi(thr[j][6]) );
                reply.add_element(poll);
            }
        }

        this->add_reply(reply);
    }

}


//Sobrecarga de operadores con funciones amigas
std::ostream& operator<<(std::ostream& out, Tuit& tuit){
    /*tuit.show(out);

    for(int i = 0; i<tuit.replies.size(); i++){
        tuit.replies[i].show(out);
    }*/
    tuit.show(std::cout);
    return out;
}

void operator>>(std::ifstream& in, Tuit& tuit){

    std::string line;
    std::vector<std::vector<string>> main_tuit;
    std::vector<std::vector<string>> replies_thread;
    std::vector<int> replies_idx;


    while(getline(in, line)){
        std::string dato;
        std::vector<std::string> line_data;
        std::istringstream iss(line);

        bool is_main_tuit;
        if(line.substr(0,4) == "Tuit"){
            main_tuit.empty() ? is_main_tuit = true : is_main_tuit= false;
        }

        while(getline(iss, dato, '|')){
            trim(dato);
            line_data.push_back(dato);
        }

        if(is_main_tuit){
            main_tuit.push_back(line_data);
        }else{
            replies_thread.push_back(line_data);
        }
    }

    // Añadir todos los atributos y elementos del Tuit principal
    tuit.user_name = main_tuit[0][1];
    tuit.text = main_tuit[0][2];
    for(auto elem:main_tuit){
        if (elem[0] == "Tuit")continue;

        if(elem[0] == "Emoji"){
            Element* emoji;

            emoji = new Emoji(
                    stoi(elem[1]),
                    elem[2],
                    stoi(elem[3])
                    );
            tuit.add_element(emoji);
        }
        else if (elem[0]=="Media"){
            Element* media;
            media = new Media(
                    stoi(elem[1]),
                    elem[2]
                    );
            tuit.add_element(media);
        }
        else if(elem[0]=="Poll"){
            Element* poll;

            std::string opcion;
            std::vector<string> opciones;

            istringstream iss(elem[3]);
            while(getline(iss, opcion, ',')){
                trim(opcion);
                opciones.push_back(opcion);
            }


            poll = new Poll(
                    stoi(elem[1]),
                    elem[2],
                    opciones,
                    stoi(elem[4]),
                    stoi(elem[5]),
                    stoi(elem[6])
                    );
            tuit.add_element(poll);
        }

    }

    std::vector<Tuit> reply_tuits;

    for(auto reply_line:replies_thread){

        if(reply_line[0] == "Tuit"){
            Tuit reply(reply_line[1], reply_line[2]);
            reply_tuits.push_back(reply);
        }

        else if(reply_line[0]== "Emoji"){
            Element* emoji;

            emoji = new Emoji(
                    stoi(reply_line[1]),
                    reply_line[2],
                    stoi(reply_line[3])
            );

            reply_tuits[reply_tuits.size()-1].add_element(emoji);
        }

        else if (reply_line[0]=="Media"){
            Element* media;
            media = new Media(
                    stoi(reply_line[1]),
                    reply_line[2]
            );
            reply_tuits[reply_tuits.size()-1].add_element(media);
        }
        else if(reply_line[0]=="Poll"){
            Element* poll;

            std::string opcion;
            std::vector<string> opciones;

            istringstream iss(reply_line[3]);
            while(getline(iss, opcion, ',')){
                trim(opcion);
                opciones.push_back(opcion);
            }


            poll = new Poll(
                    stoi(reply_line[1]),
                    reply_line[2],
                    opciones,
                    stoi(reply_line[4]),
                    stoi(reply_line[5]),
                    stoi(reply_line[6])
            );
            reply_tuits[reply_tuits.size()-1].add_element(poll);
        }

    }

    for(auto replies: reply_tuits){
        tuit.add_reply(replies);
    }

}


