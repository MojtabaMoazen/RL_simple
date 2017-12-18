
#include <vector>
#include <random>
#include <iostream>
//#include <cstdlib>
using namespace std;



struct value_reward{
    double Q,R;
};
value_reward array[9][9];
const double gomma=0.9;
const double alpha=0.1;
int maze[3][3]={{0,2,0},
                {0,0,0},
                {1,0,0}};
void findQ();

bool rechgoal(int randomnumber);
void  printQ();
void printdirection();
void init();

vector<int> find_action(int randomnnumber);

void pintR();

int main() {
    init();
    findQ();
    printQ();
    printdirection();
}


void printdirection(){
    for (int i=0;i<9;i++){
        int max=0;
        int index;
        for(int j=0;j<9;j++){
            if (array[i][j].Q>max) {
                max = array[i][j].Q;
                index=j;
            }
        }
        cout<<"  az   "<<i<<"   be   "<<index<<endl;
    }

}
void findQ(){
    srand(time(NULL));
    for (int i=0;i<10000;i++){

        int randomnumber=rand()%9;
            while(!rechgoal(randomnumber)){
                vector<int> s;
                s.clear();
                for (int i=0;i<9;i++){
                    if (array[randomnumber][i].R != -1) {//momken ha :\\ye ja ridi
                        s.push_back(i);
                    }
                }

            vector <int > action_possible=s;
            int random_index=rand()%action_possible.size();
            int action=action_possible.at(random_index);
                double  max=0;
                vector <int > action_possible2=find_action(action);
                for (int i=0;i<action_possible2.size();i++){
                    double next_valu = array[action][i].Q;
                    if (next_valu > max)
                        max = next_valu;
                }
                array[randomnumber][action].Q=array[randomnumber][action].Q+ alpha*(array[randomnumber][action].R + gomma *max - array[randomnumber][action].Q);
            randomnumber=action;
//            cout<<randomnumber<<endl;
//            for (int i ;i<action_possible.size();i++){
//                cout<<"this is i "<<action_possible.size()<<endl;
//                cout<<"this is vector "<<action_possible.at(i);
//            }

        }

    }





}


void init(){

    int i,j;
    for (int k = 0; k < 9; k++) {
        i = k / 3;
        j = k - i * 3;


        for (int s = 0; s < 9; s++) {
            array[k][s].R = -1;
        }


        if (maze[i][j] !=2) {


            int left = j - 1;
            if (left >= 0) {

                int target = i * 3 + left;
                if (maze[i][left] == 0 ) {
                    array[k][target].R = 0;
                } else if (maze[i][left] == 2) {
                    array[k][target].R = 100;
                } else {
                    array[k][target].R = -5;//tale
                }
            }
            int down = i + 1;
            if (down < 3) {
                int target = down * 3 + j;
                if (maze[down][j] == 0) {
                    array[k][target].R = 0;
                } else if (maze[down][j] ==2) {
                    array[k][target].R = 100;
                } else {
                    array[k][target].R = -5;
                }
            }
            int right = j + 1;
            if (right < 3) {
                int target = i * 3 + right;
                if (maze[i][right] == 0) {
                    array[k][target].R = 0;
                } else if (maze[i][right]==2) {
                    array[k][target].R = 100;
                } else {
                    array[k][target].R = -5;
                }
            }
            int up = i - 1;
            if (up >= 0) {
                int target = up * 3 + j;
                if (maze[up][j] == 0) {
                    array[k][target].R = 0;
                } else if (maze[up][j] == 2) {
                    array[k][target].R = 100;
                } else {
                    array[k][target].R = -5;
                }
            }
        }
    }
    pintR();






}

void pintR() {

    cout<<"R is : "<<endl;
    for (int i=0;i<9;i++){
        cout<<"from "<<i<<":";
        for (int j=0;j<9;j++){
            cout<<array[i][j].R<<"    ";
        }
        cout<<endl;
    }
}

vector<int > find_action(int randomnnumber){
    vector<int> s;
    s.clear();
    for (int i=0;i<9;i++){
        if (array[randomnnumber][i].R != -1) {//momken ha :\\ye ja ridi
            s.push_back(i);
        }
    }
    return s;


}
void  printQ(){
        cout<<"Q is : "<<endl;
        for (int i=0;i<9;i++){
            cout<<"from "<<i<<":";
            for (int j=0;j<9;j++){
                cout<<array[i][j].Q<<"  ";
            }
                cout<<endl;
        }
}

bool rechgoal(int randomnumber) {
    int i=randomnumber/3;
    int j=randomnumber-i*3;
    if (maze[i][j]==2){
//        cout<<"reaching fuckkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk"<<endl;
        return true;
    }
    else {
        return false;
    }
    }