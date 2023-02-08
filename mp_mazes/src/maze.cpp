/* Your code here! */
#include "maze.h"
using namespace cs225;
using namespace std;

void SquareMaze::makeMaze(int width,int height){   
    width_=width;
    height_=height;
    int length=width*height; 
    if(!maze.set.empty()){
        maze.set.clear();
        wall.clear();
    }
    maze.addelements(length);
    wall.resize(length);
    int count=0;
    while(count<length-1){
        int position=rand()%length;
        int direction=rand()%2;
        int curr=maze.find(position);
        if(direction==1){//right
            if((position+1)%width!=0 && wall[position].right){
                int right=maze.find(position+1);
                if(right!=curr){
                    wall[position].right=false;
                    maze.setunion(position,position+1);
                    count++;
                }
            }
        }else{//down
            if(length-(position+1)>=width && wall[position].down){
                int down=maze.find(position+width);
                if(down!=curr){
                    wall[position].down=false;
                    maze.setunion(position,position+width);
                    count++;
                }
            }
        }
    }
}

bool SquareMaze::canTravel(int x,int y,int dir ){
    int position=y*width_+x;
    bool exist=true;
    switch(dir){
        case 0:
            exist=wall[position].right;
        break;
        case 1:
            exist=wall[position].down;
        break;
        case 2:
            if(x!=0){
                exist=wall[position-1].right;
            }
        break;
        case 3:
            if(y!=0){
                exist=wall[position-width_].down;
            }
        break;
    }
    return !exist;
}

PNG * SquareMaze::drawMaze()const{
    int new_width=width_*10 +1;
    int new_height=height_*10 +1;
    PNG* image=new PNG(new_width,new_height); 
    for(auto x=0;x<new_width;x++){
        if(x>0&&x<10){
            continue;
        }
        image->getPixel(x,0).l=0;
    }
    for(auto y=0;y<new_height;y++){
        image->getPixel(0,y).l=0;
    }
    for(auto x=0;x<width_;x++){
        for(auto y=0;y<height_;y++){
            bool right=wall[y*width_+x].right;
            bool down=wall[y*width_+x].down;
            for(auto k=0;k<=10;k++){
                if(down){
                   image->getPixel(x*10+k, (y+1)*10).l=0;  
                }
                if(right){
                    image->getPixel((x+1)*10,y*10+k).l=0;
                }
            }

        }
    }
    return image;
}

PNG * SquareMaze::drawMazeWithSolution(){
    PNG* image=drawMaze();
    vector<int> directions=solveMaze();
    pair<int,int> start(5,5);
    image->getPixel(start.first,start.second)=HSLAPixel(0,1,0.5,1);
    for (auto i : directions){
        for(auto k=0;k<10;k++){
            switch (i){
            case 0:
            start.first+=1;//right
                break;
            case 1:
            start.second+=1;//dowm
                break;
            case 2:
            start.first-=1;//left
                break;
            case 3:
            start.second-=1;//up
                break;
            }
            image->getPixel(start.first,start.second)=HSLAPixel(0,1,0.5,1);
        }
    }
    int x=start.first-4;
    int y=start.second+5;
    for(auto k=0;k<9;k++){
        image->getPixel(x+k,y)=HSLAPixel();
    }
    return image;
}

void SquareMaze::setWall(int x, int y, int dir, bool exist){
    int position=y*width_+x;
    if(dir==0){
        wall[position].right=exist;
    }else{
        wall[position].down=exist;
    }
}

vector<tuple<int,int,int>> SquareMaze::adjacent_pair(pair<int,int> index,map<pair<int,int>,bool> visited){
    vector<tuple<int,int,int>> adjacent;
    for(auto i=0;i<4;i++){
        auto new_index=index;
        int x,y=0;
        if(canTravel(index.first,index.second,i)){
            x=(i==0||i==2)? ((i==0)? 1:-1):0;
            y=(i==1||i==3)? ((i==1)? 1:-1):0;
            new_index.first+=x;
            new_index.second+=y;
            if(!visited[new_index]){
                adjacent.push_back(make_tuple(new_index.first,new_index.second,i));
            }
        }
    }
    return adjacent;
}

void SquareMaze::sub_direction(map<pair<int,int>,bool>& visited,vector<vector<int>>& mul_routes,vector<int> route,pair<int,int> start,int dir){
    if(dir>-1){
        route.push_back(dir);
    }
    int position=start.second*width_+start.first;
    int length=width_*height_;
    if(length-position<=width_){
        mul_routes.push_back(route);
    }    
    visited[start]=true;
    vector<tuple<int,int,int>> adjacent;
    for(auto i=0;i<4;i++){
        auto new_index=start;
        if(canTravel(start.first,start.second,i)){
            new_index.first+=(i==0||i==2)? ((i==0)? 1:-1):0;
            new_index.second+=(i==1||i==3)? ((i==1)? 1:-1):0;
            if(!visited[new_index]){
                adjacent.push_back(make_tuple(new_index.first,new_index.second,i));
            }
        }
    }
    for(auto data:adjacent){
        pair<int,int> new_index(get<0>(data),get<1>(data));
        sub_direction(visited,mul_routes,route,new_index,get<2>(data));
    }
}
vector<int> SquareMaze::solveMaze(){
    map<pair<int,int>,bool> visited;
    vector<vector<int>> mul_routes;
    vector<int> route;
    pair<int,int> index(0,0);
    sub_direction(visited,mul_routes,route,index,-1);
    vector<int> answer{};
    for(auto i : mul_routes){
        if(i.size()>=answer.size()){
            answer=i;
        }
    }
    return answer;
}

