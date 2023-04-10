//
// Created by rudri on 10/11/2020.
//


#include "tuit.h"
#include <fstream>
using namespace std;


void question_1(){}

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

Tuit &Tuit::add_element(Element *e) {
    elements.push_back(e);
    return *this;
}

Tuit &Tuit::add_reply(Tuit r) {
    replies.push_back(r);
    return *this;
}

void Tuit::show(ostream &os) {
    os<<"====================\n";
    os<<"@"<<user_name<<'\n';
    os<<text<<'\n';
    os<<"--------------------\n";
    for(auto element:elements){
        element->show(cout);
    }
}

void Tuit::save_to(std::string file_name) {

}

void Tuit::load(std::string file_name) {

    //std::string path = file_name;
    std::ifstream tuitFile;

    tuitFile.open("C:\\Dev\\progra3\\semana2\\prog3_unit1_tuit_v2023_1_template_FORK\\file1.txt");

    
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

                temp.push_back(line.substr(pos, idx-pos));
                idx++;
                pos = idx;

            }
        }
        temp.push_back(line.substr(pos));
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
                    opciones.push_back(thr[elm][3].substr(pos, idx - pos));
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
                        opciones.push_back(thr[j][3].substr(pos, idx - pos));
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
    tuit.show(out);

    for(auto reply:tuit.replies){
        reply.show(out);
    }
    return out;
}



