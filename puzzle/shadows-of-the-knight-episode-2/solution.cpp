#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Axis{
    
    Axis(int currentPosition, int maxPosition): position_(currentPosition), maxPosition_(maxPosition), minPosition_(0){}
    
    void calculateDirection();
    void calculatePosition();
    void jump(const Axis& axis);
    void calculateMaxMin();
    
private:
    
    int position_;
    int direction_;
    int minPosition_;
    int maxPosition_;
    char status_; //Gadget readings after the last jump
    
    void setMaxMinWarmer();
    void setMaxMinColder();
    void setMaxMinSame();
    
};

void Axis::calculateDirection(){
    direction_ = (position_ > (maxPosition_ - position_)) ? -1 : 1;
}

//Coordinates for the next jump
void Axis::calculatePosition(){
    if(direction_ == 1){
        position_ = maxPosition_ - (position_ - minPosition_);
    }
    else{
        position_ = minPosition_ + (maxPosition_ - position_);
    }
}

void Axis::jump(const Axis& axis){
    string bombDir;
    static bool thisX = true;
    if(thisX){
        cout << position_ << " " << axis.position_ << endl;
    }
    else{
        cout << axis.position_ << " " << position_ << endl;
    }
    thisX = !thisX;
    cin >> bombDir; cin.ignore();
    status_ = bombDir.at(0);
}

void Axis::calculateMaxMin(){
    switch(status_){
    case 'W': //Jumped closer to the bomb
        setMaxMinWarmer();
        break;
    case 'C'://Jumped further from the bomb
        setMaxMinColder();
        break;
    case 'S':
        setMaxMinSame();
        break;
    default:
        break; 
    }
}

void Axis::setMaxMinWarmer(){ 
    int center = (maxPosition_ + minPosition_)/ 2;
    direction_ == -1 ? maxPosition_ = center - (maxPosition_ + minPosition_ +1)%2 : minPosition_ = center + (maxPosition_ + minPosition_+1)%2;
}

void Axis::setMaxMinColder(){ 
    int center = (maxPosition_ + minPosition_)/ 2;
    direction_ == -1 ? minPosition_ = center + (maxPosition_ + minPosition_ +1)%2 : maxPosition_ = center - (maxPosition_ + minPosition_+1)%2;
}

void Axis::setMaxMinSame(){
    int center = (maxPosition_ + minPosition_)/ 2;
    maxPosition_ = center;
    minPosition_ = center;
}


void findBomb(vector<Axis>& coords)
{
    for(int i = 0; i < 2; ++i){
        coords.at(i).calculateDirection(); 
        coords.at(i).calculatePosition(); 
        coords.at(i).jump(coords.at((i+1)%2)); // x&y or y&x
        coords.at(i).calculateMaxMin();
    }
}

int main()
{
    int W; // width of the building.
    int H; // height of the building.
    cin >> W >> H; cin.ignore();
    int N; // maximum number of turns before game over.
    cin >> N; cin.ignore();
    int X0;
    int Y0;
    cin >> X0 >> Y0; cin.ignore();
    string bombDir;
    cin >> bombDir;
    
    vector<Axis> coords {{X0, W-1}, {Y0, H-1}};
    
    // game loop
    while (1) {        
        findBomb(coords);
    }
}
