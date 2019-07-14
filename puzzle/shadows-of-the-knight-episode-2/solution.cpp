#include <iostream>
#include <string>
#include <vector>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Axis{
    
    Axis(bool isX, int currentPosition, int maxPosition): isX_(isX),position_(currentPosition), maxPosition_(maxPosition), minPosition_(0), found_(maxPosition == 0){}
    
    void calculateDirection();
    void calculatePosition();
    void jump(const Axis& athward);
    void calculateMaxMin();
    bool isFound() const {return found_;}
    
    friend void returnToTheArea(vector<Axis>& coords);
    
private:
    
    int position_;
    int direction_;
    int minPosition_;
    int maxPosition_;
    char status_; //Gadget readings after the last jump
    int athwartPosition_;
    bool isX_;
    bool found_; //bomb location found
    
    void setMaxMinWarmer();
    void setMaxMinColder();
    void setMaxMinSame();
    bool isLeaveLimits();
    
};

void Axis::calculateDirection(){
    direction_ = ((position_ - minPosition_) > (maxPosition_ - position_)) ? -1 : 1;
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

void Axis::jump(const Axis& athward){
        string bombDir;
        if(isX_){
            cout << position_ << " " << athward.position_ << endl;
        }
        else{
            cout << athward.position_ << " " << position_ << endl;
        }
        athwartPosition_ = athward.position_;
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

bool Axis::isLeaveLimits(){
        return position_ < minPosition_ || position_ > maxPosition_;
}

void Axis::setMaxMinWarmer(){ 
    int center = (maxPosition_ + minPosition_)/ 2;
    direction_ == -1 ? maxPosition_ = center - (maxPosition_ + minPosition_ +1)%2 : minPosition_ = center + (maxPosition_ + minPosition_+1)%2;
    if(maxPosition_ == minPosition_) 
        found_ = true; 
}

void Axis::setMaxMinColder(){ 
    int center = (maxPosition_ + minPosition_)/ 2;
    direction_ == -1 ? minPosition_ = center + (maxPosition_ + minPosition_ +1)%2 : maxPosition_ = center - (maxPosition_ + minPosition_+1)%2;
    if(maxPosition_ == minPosition_) 
        found_ = true; 
}

void Axis::setMaxMinSame(){
    int center = (maxPosition_ + minPosition_)/ 2;
    maxPosition_ = center;
    minPosition_ = center;
    found_ = true; 
}

void returnToTheArea(vector<Axis>& coords){
        bool isLeaveLimits;
        for(int i = 0; i < 2; ++i){
            isLeaveLimits = coords.at(i).isLeaveLimits();
            if(isLeaveLimits) break;
        }
        
        if(isLeaveLimits){
            for(int i = 0; i < 2; ++i){
                coords.at(i).position_ = coords.at(i).maxPosition_;
            } 
            cout << coords.at(0).position_ << " " << coords.at(1).position_ << endl;
            string bombDir;
            cin >> bombDir;
        }
}


void findBomb(vector<Axis>& coords)
{
    for(int i = 0; i < 2; ++i){
        if(coords.at(i).isFound()) continue;
        coords.at(i).calculateDirection(); 
        coords.at(i).calculatePosition(); 
        coords.at(i).jump(coords.at((i+1)%2)); // x&y or y&x
        coords.at(i).calculateMaxMin();
    }
    
    returnToTheArea(coords);
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
    
    vector<Axis> coords {{true, X0, W-1}, {false, Y0, H-1}};
    
    // game loop
    while (1) {        
        findBomb(coords);
    }
}
