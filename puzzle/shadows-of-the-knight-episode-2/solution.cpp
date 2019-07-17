#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/

struct Axis{
    
    Axis(int currentPosition, int maxPosition): position_(currentPosition), maxPosition_(maxPosition), minPosition_(0), found_(maxPosition == 0){}
    
    void calculateDirection();
    void calculatePosition();
    void jump(const vector<Axis>& coords);
    void calculateMaxMin();
    bool isFound() const {return found_;}
    bool isLeaveLimits();
    int getPosition();
    void setCorrectPosition();
    
private:
    
    int position_;
    int direction_;
    int minPosition_;
    int maxPosition_;
    char status_; //Gadget readings after the last jump
    bool found_; //bomb location found
    
    void setMaxMinWarmer();
    void setMaxMinColder();
    void setMaxMinSame();
    
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

void Axis::jump(const vector<Axis>& coords){
        string bombDir;
        stringstream jumpStr;
        for_each(coords.cbegin(), coords.cend(), [&](const Axis& a){ jumpStr << " " << a.position_;});
        cout << jumpStr.str().substr(1) << endl;
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
    int center = (maxPosition_ + minPosition_) / 2;
    int stepFromTheCenter = (maxPosition_ + minPosition_ + 1) % 2;
    
    if(direction_ == -1){
        maxPosition_ = center - stepFromTheCenter;
    }
    else{ 
        minPosition_ = center + stepFromTheCenter;
    }
    if(maxPosition_ == minPosition_) 
        found_ = true; 
}

void Axis::setMaxMinColder(){ 
    int center = (maxPosition_ + minPosition_) / 2;
    int stepFromTheCenter = (maxPosition_ + minPosition_ + 1) % 2;
    
    if(direction_ == -1){
        minPosition_ = center + stepFromTheCenter;
    }
    else{
        maxPosition_ = center - stepFromTheCenter;
    }

    if(maxPosition_ == minPosition_) 
        found_ = true; 
}

void Axis::setMaxMinSame(){
    int center = (maxPosition_ + minPosition_)/ 2;
    maxPosition_ = center;
    minPosition_ = center;
    found_ = true; 
}

void Axis::setCorrectPosition(){
    
    if(status_ == 'C'){
        if(direction_ == 1){
            position_ = maxPosition_;
        }
        else{
            position_ = minPosition_;
        }
    }
    else{
        if(direction_ == 1){
            position_ = minPosition_;
        }
        else{
            position_ = maxPosition_;
        }
    }
}

int Axis::getPosition(){
    return position_;
}

void returnToTheArea(vector<Axis>& coords){
        bool isLeaveLimits;
        for(int i = 0; i < coords.size(); ++i){
            isLeaveLimits = coords.at(i).isLeaveLimits();
            if(isLeaveLimits) break;
        }
        // Find the optimal return point to reduce the number of jumps required.
        if(isLeaveLimits){
            stringstream jumpStr;
            for_each(coords.begin(), coords.end(), [&](Axis& axis){ 
                    axis.setCorrectPosition();
                    jumpStr << " " << axis.getPosition();
            });
            
            cout << jumpStr.str().substr(1) << endl;

            string bombDir;
            cin >> bombDir;
        }
}


void findBomb(vector<Axis>& coords){
    for(int i = 0; i < coords.size(); ++i){
        if(coords.at(i).isFound()) continue;
        coords.at(i).calculateDirection(); 
        coords.at(i).calculatePosition(); 
        coords.at(i).jump(coords); // x&y or y&x
        coords.at(i).calculateMaxMin();
    }
    
    returnToTheArea(coords);
}

int main(){
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
    while (1){        
        findBomb(coords);
    }
}
